# PDS-VV-CON-004 — Regulated rail supply constraint test definition

Model-based verification definition for the PDS & ESS v1.0 constraint `[C] Supply both 5±0.1 V and 3.3±0.1 V, 1 A`.

- **SSIV/version:** PDS & ESS v1.0 **final flight acceptance**. Earlier versions are protoflight/development baselines and are out of scope for this folder.
- **IADT method:** Testing.
- **IVV source category:** Constraint, with functional-chain/scenario coverage of the PDS v1.0 power and protection chain.
- **Traceability:** constraint above; `PDS-UC-ProvideRegulatedPower`; `PDS-FE-RailBrownout`.
- **Model elements under test:** `[LC] Regulator`; `[F] Regulate voltage`; regulator/backplane power path; PDS v1.0 power and protection chain.
- **References:** IVV, PDS-R2, PDS-R6, PDS-R8.

## Baseline views

The `baseline/` folder is a local copy of all PDS & ESS v1.0 source D2/PNG views used to derive this definition:

- `PDS_v1.0_view1_physical.d2` and `.png`
- `PDS_v1.0_view2_logical.d2` and `.png`
- `PDS_v1.0_view3_functional_allocation.d2` and `.png`
- `PDS_v1.0_view4_power_and_protection_chain.d2` and `.png`
- `PDS_v1.0_view5_battery_supervision_chain.d2` and `.png`

## Definition views

| View | File | Purpose |
|---|---|---|
| PV1 physical testbench | `PDS_VV_CON_004_view1_physical_testbench.d2` | UUT power path, external current-limited battery emulator, rail loads, probes, thermal/ambient instrumentation. |
| PV2 logical test interfaces | `PDS_VV_CON_004_view2_logical_test_interfaces.d2` | Logical rail-test interfaces, measurement/status exchanges, and verification-only interface components. |
| PV3 functional allocation | `PDS_VV_CON_004_view3_functional_allocation_testbench.d2` | Allocation of verification functions to the regulator/backplane path, instruments, operator, and evidence host. |
| Functional chain | `PDS_VV_CON_004_view4_nominal_load_sweep_chain.d2` | No-load, nominal-load, and 1 A load sweep for both 5 V and 3V3 rails. |
| Functional chain | `PDS_VV_CON_004_view5_transient_fault_hardening_chain.d2` | Startup, load-step transient, brownout/reset observation, thermal observation, and safe fault-hardening scope. |

Each D2 file is rendered to a matching `.d2.png` in this folder.

## Pass/fail constraints

Pass only if all of the following are true for the as-tested configuration:

1. **Load cases:** no-load, campaign-declared nominal-load, and 1 A-load cases are executed for both the 5 V and 3V3 rails using programmable loads or an equivalent calibrated load bank.
2. **Sampling/statistical significance:** at each load case, collect at least `n ≥ 30` settled voltage samples per rail. Retain raw data and compute bias, spread, confidence interval, and expanded uncertainty. A limit is met only when the measured voltage plus/minus expanded uncertainty remains inside the rail limit.
3. **Voltage limits:** 5 V rail remains in `[4.9, 5.1] V`; 3V3 rail remains in `[3.2, 3.4] V` for all accepted settled samples, including uncertainty.
4. **Brownout/reset:** no OBCC/PDS brownout, reset, uncontrolled restart, or loss of required power state occurs during load cases, startup, or load-step checks.
5. **Startup/transient:** startup overshoot and load transients are recorded. After the allowed settling window, rails meet the same voltage limits. Placeholder settling windows are `≤100 ms` after startup and `≤50 ms` after load step; both are campaign-configurable.
6. **Safety:** no unsafe regulator/PCB temperature, uncontrolled current, smoke, swelling, latch-up, connector heating, or unexpected protection cut-off occurs.

## Environmental and setup conditions

- Use a **battery emulator/current-limited bench supply**, not a real Li-ion cell, for this constraint test unless a later campaign explicitly approves cell use.
- Record ambient temperature and humidity before each repetition or load sweep.
- Configure and record bench-supply voltage/current limits before applying power.
- Use calibrated DMM/DAQ and oscilloscope/logger channels; record calibration status or uncertainty assumptions in the evidence.
- Monitor regulator or PCB temperature with a thermocouple or IR camera.
- Keep destructive Li-ion abuse, short-circuit abuse, transport certification, and accredited safety-standard testing out of scope for this activity.

## Evidence path

Store execution evidence under `PDS&ESS/MBSE/tests/results/PDS-VV-CON-004/` (`../results/PDS-VV-CON-004/` relative to this definition folder), including:

- raw voltage/current/ripple/temperature/ambient logs,
- oscilloscope screenshots or waveform files for startup and load steps,
- programmable-load profiles and bench-supply settings,
- calibration records or uncertainty budgets,
- photos of physical setup/probe points,
- as-tested configuration notes and deviations from this model definition,
- pass/fail report referencing these model views.

## Assumptions and caveats

- The campaign is final flight acceptance; exact nominal-load values, final thermal limit, and final settling windows are still campaign parameters to record in the report.
- The modeled 1 A requirement is interpreted as an individual rail-load requirement to be checked for both rails; if the campaign later defines aggregate loading differently, record the deviation.
- This is workshop/subsystem verification evidence unless a later campaign defines independence, sample size, and environmental levels sufficient for a stronger qualification claim.
