# ADS-IVV-C-I2C-5MS — I2C read timeout <=5 ms verification

**IADT method:** Testing with supporting Analysis.

**IVV source category:** constraint.

**Selected SSIV/development scope:** ADS `v0.1`, `v0.2`, `v0.3`, and `v1.0`. Formal source-modeled pass/fail applies to `v1.0`; `v0.2` is included as a controlled constraint-derived **code-analysis/instrumentation branch** because I2C behavior is modeled without an explicit source-D2 `<=5 ms` timeout constraint. The user-approved resolution is to verify bounded v0.2 I2C timeout/no-blocking behavior through code review and instrumentation rather than adding convoluted v0.2 source diagrams. `v0.1` and `v0.3` are N/A.

**Traceability targets:** `ADS-IVV-C-I2C-5MS` traces to the v1.0 I2C timeout `<=5 ms` constraint, `ADS-CAP-IMU`, `ADS-CAP-ATT`, `ADS-CAP-INIT`, `ADS-FE-STUCK-LOOP`, and `ADS-FE-CORRUPT-MEASUREMENT`. Explicit mission/capability/use-case/feared-event elements are not modeled as separate source nodes, so controlled ADS plan trace labels remain in use.

**References cited in diagrams:** IVV, the ADS MBSE IVV plan `../README.md`, `ADS_MBSE_CORPUS.md`, `model_inventory.json`, and saved reference material under `../references/` or `../v0.2/tests/references/` as applicable. No external research was performed for this definition.

## Source-view copies

All D2/PNG views for the selected ADS-wide scope were copied under `source_views/` so reports can reference a stable test-definition package:

- `source_views/v0.1/` — v0.1 physical, logical, allocation, GPS, and Serial0 source views.
- `source_views/v0.2/` — v0.2 physical, logical, allocation, GPS, angular velocity, attitude, peripheral initialization, and Serial0 source views.
- `source_views/v0.3/` — v0.3 physical PCB delivery view.
- `source_views/v1.0/` — v1.0 physical, logical, allocation, GPS, angular velocity, attitude, and peripheral initialization source views.

## Test-definition views

| View | Purpose |
|---|---|
| `definition_views/ADS_IVV_C_I2C_5MS_view1_source_constraint_interface_inventory.d2/png` | Inventory v1.0 I2C timeout constraint, v0.2 gap, IMU I2C functions, and N/A branches. |
| `definition_views/ADS_IVV_C_I2C_5MS_view2_i2c_fault_timing_setup.d2/png` | Model I2C fault injector, logic analyzer/timer, IMU harness, loggers, power/ambient constraints. |
| `definition_views/ADS_IVV_C_I2C_5MS_view3_verification_functional_allocation.d2/png` | Allocate verification functions to conductor, I2C fault injector, timing tool, logger, analysis station, and configuration authority. |
| `definition_views/ADS_IVV_C_I2C_5MS_view4_deadline_fault_recovery_sequence.d2/png` | Functional-chain style sequence for ACK, NACK, invalid address, partial read, stuck bus, timeout, and recovery cases. |
| `definition_views/ADS_IVV_C_I2C_5MS_view5_evidence_traceability.d2/png` | Model timing logs, bus captures, fault markers, analysis reports, waivers, limitations, and retest closure. |

## Version coverage and pass/fail rules

| Version | Model element(s) covered | Pass/fail constraints |
|---|---|---|
| `v0.1` | No IMU/I2C behavior is modeled. | Pass/N/A if no I2C read functions or I2C timeout constraint exist in the v0.1 source views. |
| `v0.2` | IMU I2C communication is modeled, but no explicit source-D2 I2C `<=5 ms` timeout constraint is present. | Use the selected constraint-derived code-analysis/instrumentation path. Pass at definition level only if firmware source/build map or equivalent instrumentation identifies every v0.2 IMU I2C read path and evidence shows each read returns data or timeout/error in `<=5 ms` under ACK, NACK, invalid address, partial read, stuck-bus, and recovery cases; invalid/stale/no-data/timeout/fault data shall not be accepted as valid. If source/instrumentation is absent, record a controlled gap/waiver or limited characterization, not pass. |
| `v0.3` | PCB-only I2C traces with no runtime I2C read functions. | Pass/N/A if no runtime behavior is modeled. |
| `v1.0` | Formal I2C timeout constraint for integrated IMU reads through ADS Processing. | Pass if every I2C read returns data or timeout/error in `<=5 ms` under ACK, NACK, invalid address, partial read, stuck-bus, and recovery cases, with no invalid IMU data accepted as valid. |

## Viewpoints

- **Statistical significance:** apply `n = 59` zero-violation samples per formal deadline claim for the selected version/branch; otherwise classify evidence as characterization/screening only.
- **Fault hardening:** execute or explicitly disposition ACK, NACK, invalid-address, partial-read, stuck-bus, timeout, and recovery cases. Where the data is consumed by OBCC, timeout/fault/no-data shall map to a non-`VALID` status such as `TIMEOUT` or `SENSOR_FAULT` under the shared PM&SE freshness contract; old data shall not remain marked valid.
- **Configuration control:** every report identifies ADS version/SSIV, source-view copy, hardware revision/BOM, firmware commit/build, instrumentation build, equipment IDs/calibration status, operator, and deviations.
- **Environmental context:** record ambient temperature/humidity, power conditions, and any test-specific environmental or ESD constraints before execution.

## Required execution conditions

- Record IMU harness/fault-injector configuration, bus speed, pullups/power state, firmware build, logger timebase, and timing overhead.
- Use safe fault injection for NACK, invalid address, partial read, and stuck-bus simulation; record recovery actions.
- Use `n = 59` zero-violation samples per formal v1.0 or v0.2 instrumentation-branch deadline claim where applicable.
- Separate I2C timeout verdicts from angular-rate/attitude accuracy verdicts.

## Expected report locations

Reports should reference this modeled definition and store evidence under:

- `../results/ADS-IVV-C-I2C-5MS/v0.1/`
- `../results/ADS-IVV-C-I2C-5MS/v0.2/`
- `../results/ADS-IVV-C-I2C-5MS/v0.3/`
- `../results/ADS-IVV-C-I2C-5MS/v1.0/`

Each report shall identify referenced model views/elements, selected SSIV/version, as-tested/as-inspected configuration, raw evidence, analysis settings, actual environmental and equipment conditions, pass/fail or N/A rationale, deviations, anomalies, waivers, limitations, and retest status.

## Assumptions and residual gaps

- v0.2 has I2C behavior but lacks an explicit source-D2 I2C timeout constraint; the selected closure path is code-analysis/instrumentation or a controlled waiver/gap, not a cluttered source-diagram update.
- Specific I2C fault-injection equipment, firmware timing hooks, build map/symbols, and instrumentation overhead are execution prerequisites and must be recorded before pass/fail credit.

## Status

Modeled definition ready for review. Execution remains pending.
