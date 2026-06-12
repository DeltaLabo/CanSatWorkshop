# PDS & ESS v1.0 testing plan

This plan is derived from the Capella/D2 Physical Architecture views in this folder:

- `PDS_v1.0_view1_physical.d2`
- `PDS_v1.0_view2_logical.d2`
- `PDS_v1.0_view3_functional_allocation.d2`
- `PDS_v1.0_view4_power_and_protection_chain.d2`
- `PDS_v1.0_view5_battery_supervision_chain.d2`

The test scope is the CanSat Power Distribution Subsystem and Energy Storage Subsystem: 1S1P Li-ion ESS, PDS PCB, charger/protection circuit, INA219 battery monitor, 5 V / 3.3 V regulator, backplane connections, OBCC/XIAO software interactions, and the constraints shown in the views.

References and saved source files are in `references/`.

Project-wide IVV conventions, statistics, rate terminology, fault semantics, and artifact paths are defined in [`../../../../PM&SE/IVV.md`](../../../../PM&SE/IVV.md). PDS/ESS tests may impose stricter safety or protection-demonstration sample sizes than the common defaults.

## Statistical policy

Use the project-wide policy in [`../../../../PM&SE/IVV.md`](../../../../PM&SE/IVV.md) for all tests unless a stricter standard, component datasheet, or modeled safety constraint applies.

- Binary success/failure trials: if zero failures are observed in `n` independent trials, the one-sided 95% upper confidence bound on failure probability is `1 - 0.05^(1/n)`.
  - To support the model constraint `Probability < 1%` at 95% confidence: `n = 299` failure-free demanded protection trials are required.
  - If only 30 workshop trials are run with zero failures, the 95% upper bound is still about 9.5%; report it as a functional check, not a 1% statistical demonstration.
- Continuous measurements: collect at least 30 samples per condition; report min, max, mean, standard deviation, and 95% confidence interval. Hard safety limits must never be exceeded.
- Endurance reliability: one 6 h run demonstrates functionality. To demonstrate 95% probability of surviving a 6 h run with 95% confidence requires 59 failure-free 6 h runs.
- Safety: destructive Li-ion abuse tests must be performed only by an accredited lab. Local tests shall use a current-limited bench supply or battery emulator unless the test is normal charge/discharge within cell limits.

## Tests, one per scenario

| ID | Scenario | Basis | Method | Statistical / pass criteria |
|---|---|---|---|---|
| T01 | Expected use: charge ESS from external charger | Diagram constraint: 4.2 V, 0.5 A; IEC 62133 / NASA Li-ion guidance | Charge the 1S1P pack through USB-C/protection with temperature monitoring. Log charger voltage/current, battery terminal voltage, and board temperature through full CC/CV cycle. | At least 3 normal charge cycles. Every cycle: no reverse current, no swelling/heating anomaly, charge voltage never exceeds cell limit, current limited to 0.5 A nominal. |
| T02 | Expected use: 6 h continuous On-mode operation | Diagram constraint: enough for 6 h; ESA CanSat 4 h baseline | Run the assembled CanSat in representative On mode with telemetry/logging enabled until 6 h. Include expected OBCC, INA219, regulator, and backplane load. | Minimum: 3 failure-free 6 h runs for workshop acceptance. Formal 95% reliability at 95% confidence would require 59 failure-free runs; record actual confidence. |
| T03 | Expected use: switch power on and distribute regulated rails | Power chain and regulator constraint: 5 ± 0.1 V and 3.3 ± 0.1 V, 1 A | From OFF, switch ON into no-load, nominal-load, and 1 A-load cases. Measure startup overshoot, steady-state voltage, ripple, and regulator temperature. | 30 samples per load case after settling. All 5 V samples in [4.9, 5.1] V; all 3.3 V samples in [3.2, 3.4] V; no brownout or unsafe temperature. |
| T04 | Expected use: switch power off / safe de-energization | Power-off command and cut-off function | From nominal operation, command/switch OFF. Measure downstream rail decay, leakage/backfeed, and restart behavior. | 30 OFF/ON cycles. No uncontrolled restart, no downstream rail above safe off threshold after decay, no lost firmware state needed for next boot. |
| T05 | Expected use: backplane and module physical integration | Physical links: battery cable, parallel cables, backplane fixtures/headers | Assemble ESS, PDS, OBCC, and backplane. Perform continuity, polarity, connector retention, and contact-resistance checks before and after environmental tests. | 100% of required links pass continuity/polarity. Contact resistance change after T12/T13 must remain within connector/test-equipment tolerance and cause no voltage-drop failure at 1 A. |
| T06 | Expected use: OBCC collects INA219 initialization state | Battery supervision chain; logical CE pointers/returns | Boot with INA219 present. Verify XIAO/ESS Processing gets init state and OBCC receives a valid result without blocking other initialization. | 100 boot cycles. Zero missed init-state reports. If zero failures in 100 cycles, report 95% upper failure bound ≈ 3.0%. |
| T07 | Expected use: runtime voltage/current measurement collection | INA219 datasheet; NXP I2C; diagram timing constraints | Sweep battery emulator voltage and load current across expected mission range. Compare INA219-derived values to calibrated DMM/e-load reference. Measure I2C read duration and processing duration. | 30 samples per point, at least 5 voltage/current points. Error budget must be declared from shunt tolerance + INA219 grade; process functions < 5 ms; I2C read timeout setting ≤ 5 ms. |
| T08 | Feared event: I2C device absent, NACK, or stuck bus | Diagram: no blocking except comms; I2C timeout ≤ 5 ms; NXP I2C clock stretching/bus behavior | Disconnect INA219, force NACK, and simulate SDA/SCL held low using a test fixture. Verify timeout, error propagation, and continued OBCC operation. | For the 1% constraint, run 299 fault-injection trials with zero unbounded blocks. Minimum workshop check: 30 trials, zero blocking longer than 5 ms plus explicit confidence bound. |
| T09 | Feared event: overcurrent / external short on PDS output | Protection functions; IEC 62133 / UN 38.3 short-circuit themes | With a current-limited supply or battery emulator, apply overload and short-circuit cases downstream of protection/regulator. Verify detection, cut-off, and no damage. | 299 demanded trips with zero missed cut-offs to support <1% missed-trip probability at 95% confidence. During all trials, no rail exceeds safe thermal/electrical limit. |
| T10 | Feared event: overvoltage or charger fault | Protection functions; IEC 62133 overcharge themes; NASA Li-ion guidance | Use a programmable supply/battery emulator to ramp charger/battery input above nominal in controlled increments. Verify overvoltage detection and cut-off before cell or rails exceed limits. | Same demanded-protection statistics as T09. No direct Li-ion overcharge abuse locally; destructive overcharge evidence must come from certified battery/protection reports. |
| T11 | Expected recovery: restore power after cleared protection fault | Power chain `restore_power`; Aerospace/NASA system-level protection guidance | After T09/T10 trips, remove the fault and command/perform restore. Verify rails return within tolerance and OBCC resumes measurement collection. | 100 restore cycles after representative faults; zero latch-up or unsafe restart. Report 95% upper failure bound ≈ 3.0% for n=100 zero failures. |
| T12 | Feared event: hot launch-pad / thermal soak | CanSat mission guide thermal test; GEVS environmental tailoring | Operate the assembled CanSat in a thermal chamber or equivalent at 55–60 °C for 2 h, with telemetry and PDS load active. | At least 1 full system test and 3 board-level repeats if possible. During exposure: rails remain in tolerance, measurements continue, no material/connector deformation, no battery temperature violation. |
| T13 | Feared event: deployment shock / drop | CanSat guide: ~30 g drop test; ESA: withstand acceleration | Powered CanSat attached as flight configuration; perform specified 61 cm cord drop or equivalent shock test. Inspect battery mount, connectors, backplane, and telemetry continuity. | Minimum: 3 drops, including final flight configuration. Pass if no power loss, no detached parts, telemetry continues, and T05 continuity still passes. |
| T14 | Feared event: vibration loosens battery/backplane/component mounts | CanSat guide vibration test; GEVS environmental verification | Powered vibration test using random orbital sander method or tailored lab shaker. Monitor accelerometer, rails, and telemetry. Inspect solder joints/connectors afterward. | Perform all axes if practical; otherwise document orientation. Pass if no reset, no data loss, no connector loosening, and T05/T07 still pass after vibration. |
| T15 | Feared event: PCB trace overheating or excessive voltage drop at 1 A | IPC-2152 trace current capacity; regulator constraint | Drive 1 A through 5 V and 3.3 V power paths on PDS/backplane. Use thermocouple/IR camera and voltage probes at source/load. | 30 min soak at worst-case load. Temperature rise should stay within design limit, nominally ≤10–20 °C unless justified; voltage at loads remains within T03 limits. |
| T16 | Expected constraint: PCBs machinable on Carvera Air CNC | Diagram CNC constraint; IPC-style DFM evidence | Manufacture or machine a DFM coupon and one representative board. Inspect trace/clearance, drill, isolation, solderability, and shorts/opens before assembly. | 100% netlist continuity/isolation pass. Any CNC design-rule violation blocks system environmental testing until corrected. |
| T17 | Feared event: unsafe or undocumented Li-ion pack | IEC 62133, UN 38.3, NASA Li-ion guidance | Collect battery cell/pack datasheet, MSDS/SDS, UN 38.3 summary, and IEC/UL/CE safety evidence where available. Verify storage, handling, charging, and transport limits. | Documentation review must pass before powered tests. If no certification evidence is available, limit use to supervised lab testing and do not claim transport/product safety compliance. |

## Traceability to model functions and constraints

- Charging and storage: T01, T02, T17.
- Power distribution/regulation: T03, T04, T05, T11, T15.
- Protection functions (`detect_overcurrent`, `detect_overvoltage`, `cut_off_power`, `restore_power`): T09, T10, T11.
- Battery monitoring and I2C response: T06, T07, T08.
- Software timing constraints (`Process < 5 ms`, `I2C timeout ≤ 5 ms`, no blocking except comms): T06, T07, T08.
- Physical/environmental survivability: T12, T13, T14.
- PCB manufacturability: T16.

## Evidence to archive per test

For each test run, save evidence under `results/<test-id>/` inside this `tests/` folder: procedure/checklist version, model baseline, as-tested hardware/software configuration, raw voltage/current/temperature/log files, photos where applicable, pass/fail calculations including exact confidence bounds, deviations, anomalies, and retest evidence.
