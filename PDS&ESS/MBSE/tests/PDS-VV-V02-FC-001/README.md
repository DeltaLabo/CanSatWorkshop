# PDS-VV-V02-FC-001 — v0.2 measurement/reporting advancement gate

Model-based verification definition for the **PDS & ESS v0.2** advancement gate to **v0.3**. This session selected and modeled **PDS-VV-V02-FC-001** to verify charger input, INA219 measurement, XIAO ESP32-S3 I2C access, variable-getter processing, 5 Hz collection, and Serial0 logging before v0.3 protection detection is added.

## Scope and baseline

Baseline source views copied under `baseline/`:

- `PDS_v0.2_view1_physical.d2` / `.d2.png`
- `PDS_v0.2_view2_functional_allocation.d2` / `.d2.png`
- `PDS_v0.2_view3_power_chain.d2` / `.d2.png`
- `PDS_v0.2_view4_measurement_chain.d2` / `.d2.png`
- `PDS_v0.2.jpg`

Covered source elements: Charger, User, PDS Circuitboard, Protection Circuit, INA219, Regulator, Connector Terminal, XIAO ESP32-S3, 1S1P Li-Ion; USB-C, PC Out/GND, INA Out/GND, 3V3/5V/GND, I2C cables, 5V/GND, and Battery Cable physical links; INA219 measure/respond functions; XIAO init/read/process/collect/log functions; the v0.2 power and measurement chains; and the v0.2 timing/reporting constraints.

## Traceability and IADT

- Activity ID: `PDS-VV-V02-FC-001`.
- Version/gate: `PDS & ESS v0.2` advancement gate to `v0.3`.
- Primary IADT: **Testing / Demonstration**.
- Supporting IADT: **Inspection** for PC/PL/testbench presence and **Analysis** for component-exchange and allocation completeness.
- Traceability: `PDS-UC-SuperviseBattery-v0.2`, `PDS-FE-SensorBusFault-v0.2`, `PDS-UC-ProvideRegulatedPower-v0.2`, and v0.2 timing/reporting constraints.

## Generated verification views

| View | Purpose |
|---|---|
| `PDS_VV_V02_FC_001_view1_physical_measurement_testbench.d2` | PV1 testbench with the v0.2 UUT, charger/current-limited source, Serial0 logger, I2C analyzer/fault fixture, reference V/I measurement, load/source, ambient meter, evidence repository, and pass/fail constraints. |
| `PDS_VV_V02_FC_001_view2_logical_test_interfaces.d2` | PV2 component-exchange analysis for commands, charger/load/reference/environment/evidence interfaces, I2C init/read/response, Serial0 logs, timing, getter/status semantics, and fault liveness. |
| `PDS_VV_V02_FC_001_view3_functional_allocation_testbench.d2` | PV3 allocation view for source functions plus verification-only operator, equipment, harness, probe, Serial0, I2C timing, fault-injection, liveness, and evidence-capture functions. |
| `PDS_VV_V02_FC_001_view4_nominal_measurement_reporting_chain.d2` | Nominal test/demonstration chain for inspection, ambient recording, power setup, INA219 init/read/respond, XIAO processing, 5 Hz collection, Serial0 logging, reference comparison, and evidence archiving. |
| `PDS_VV_V02_FC_001_view5_i2c_timeout_no_blocking_fault_chain.d2` | Fault-hardening chain for absent INA219, NACK, stuck SDA/SCL, delayed/no-response, bounded timeout/status handling, scheduler/logging liveness, recovery, and evidence archiving. |

Rendered PNGs with the same names plus `.png` are generated in this folder.

## IVV coverage summary

| IVV source category | Elements covered | Modeled verification coverage |
|---|---|---|
| Component/link | All v0.2 PCs and PLs listed above plus verification-only harness links | 100% presence/absence inspection before powered execution; pass/fail constraints in views 1, 3, and 4. |
| Component exchange | Verification-mode I2C init/read/response, Serial0 log, charger/source/load, reference, ambient, fault-control, timing, and evidence exchanges | Presence/implementation analysis in view 2; timing and status evidence in views 4 and 5. |
| Functional allocation | Battery, Battery Charger, Power Protection, Battery monitoring, Regulator, Setup, Loop, operator/equipment/harness functions | Allocation analysis in view 3; no foreign functions allowed in source LCs except labeled verification-only hooks and harness functions. |
| Functional chain/scenario | v0.2 measurement/reporting chain and I2C fault-hardening scenarios | Testing/Demonstration chains in views 4 and 5 include stimuli, equipment, expected outputs, constraints, trace, statistical and fault-hardening viewpoints. |
| Constraint | No blocking except I2C/UART; I2C read timeout ≤5 ms; variable getter; process/calculate <5 ms; collect at 5 Hz; unused fields = 0 | Each constraint is assigned as a pass/fail condition to view 2, view 3, and at least one functional chain in views 4 or 5. |

## Pass/fail criteria

Pass only if all modeled constraints hold and evidence is archived:

1. All modeled v0.2 physical components and physical links are present, identified, undamaged, and connected according to the baseline before powered execution.
2. Charger input/source/load conditions are current-limited, stable, recorded, and compatible with the v0.2 bench campaign.
3. Ambient temperature/humidity, instrument IDs, calibration/status, harness topology, load/source setpoints, and operator decisions are recorded before repetitions.
4. INA219 voltage/current outputs are paired with reference-traceable readings; collect **n ≥ 30 paired samples per operating point** and keep results inside the declared INA219/reference uncertainty budget.
5. Serial0 logs show collection/reporting at **5 Hz**, scheduler/logging liveness, and unused frame fields set to **0**.
6. Every INA219 I2C read either succeeds or times out within **≤5 ms**.
7. Voltage/current process or calculate functions complete in **<5 ms**.
8. The variable-getter implementation documents ownership, units, freshness/age, valid/stale state, and bounded status/error results; stale values are never reported as valid.
9. No unbounded blocking occurs except modeled I2C or UART communication waits.
10. Fault trials cover absent INA219, NACK, stuck SDA/SCL, and delayed/no-response. Each trial returns bounded status, keeps the scheduler and Serial0 logging alive, classifies pass/fail, and verifies recovery after clearing the fault.
11. Timing evidence for a 95/95 deadline claim uses **59/59** representative in-limit samples per deadline; smaller sets are characterization only.

## Environment, statistical view, and fault hardening

- Ambient temperature/humidity is read by the bench operator from a dedicated ambient thermometer/hygrometer before repetitions and stored with the evidence.
- Continuous measurement accuracy uses paired INA219/reference samples with raw data retained, bias/dispersion/uncertainty reported, and `n ≥ 30` stable samples per operating point.
- Timing/deadline claims use the project IVV `59/59` in-limit planning basis for a one-sided non-parametric 95/95 claim.
- Fault injection is pass/fail by trial; absent INA219, NACK, stuck SDA/SCL, and delayed/no-response are mandatory final evidence cases.
- Real Li-ion use remains supervised and non-abuse only; a current-limited source/load or battery emulator is preferred for repeatable v0.2 development testing.

## Evidence path

Expected report/evidence path: `PDS&ESS/MBSE/tests/results/PDS-VV-V02-FC-001/`.

Minimum report content: referenced model views, baseline copied under `baseline/`, tested article ID, firmware/software commit, equipment IDs/calibration status, source/load and fault-profile settings, ambient readings, raw Serial0 logs, I2C captures, reference V/I data, paired-sample analysis, timing statistics, pass/fail rationale, deviations, anomalies, waivers, and blockers.

## Assumptions and blockers

- The issue disambiguates the selected version/activity as `PDS-VV-V02-FC-001` for PDS & ESS v0.2 advancement to v0.3; no interactive clarification was requested.
- Requested `DPS&ESS` is treated as the existing `PDS&ESS` folder.
- The v0.2 baseline has no separate PV2 logical component-exchange view; this folder models verification-only logical interfaces and does not modify the baseline.
- Exact operating points, INA219/reference error budget, acceptable ambient range, current limits, fault-injection hardware settings, calibration identifiers, and firmware/software commit remain execution-time evidence items.
- v0.2 evidence is a development advancement gate and does not substitute for v1.0 final flight acceptance evidence.
