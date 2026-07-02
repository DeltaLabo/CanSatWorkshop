# ADS-IVV-C-PROC-5MS — process/calculate <5 ms constraint verification

**IADT method:** Testing with supporting Analysis.

**IVV source category:** constraint.

**Selected SSIV/development scope:** ADS `v0.1`, `v0.2`, `v0.3`, and `v1.0`. Formal runtime execution applies to `v0.1`, `v0.2`, and `v1.0`; `v0.3` is a PCB-only N/A branch.

**Traceability targets:** `ADS-IVV-C-PROC-5MS` traces to the process/calculate `<5 ms` constraint, `ADS-FE-STUCK-LOOP`, `ADS-CAP-IMU`, `ADS-CAP-ATT`, and `ADS-CAP-DELIVERY` where applicable. Explicit mission/capability/use-case/feared-event elements are not yet separate source-model nodes, so the controlled ADS plan trace labels remain in use.

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
| `definition_views/ADS_IVV_C_PROC_5MS_view1_source_constraint_function_inventory.d2/png` | Inventory the versions, process/calculate functions, timing constraint, and v0.3 N/A rationale. |
| `definition_views/ADS_IVV_C_PROC_5MS_view2_timing_instrumentation_setup.d2/png` | Model timing probes, firmware instrumentation, loggers, stimulus sources, ambient/power controls, and pass/fail constraints. |
| `definition_views/ADS_IVV_C_PROC_5MS_view3_verification_functional_allocation.d2/png` | Allocate verification-only functions to the conductor, timer, logger, stimulus harness, analysis tool, and configuration authority. |
| `definition_views/ADS_IVV_C_PROC_5MS_view4_timed_execution_fault_sequence.d2/png` | Functional-chain style sequence for nominal, worst-case valid, and fault-data timing campaigns. |
| `definition_views/ADS_IVV_C_PROC_5MS_view5_evidence_traceability.d2/png` | Model evidence products, report references, deviations, limitations, and retest closure. |

## Version coverage and pass/fail rules

| Version | Model element(s) covered | Pass/fail constraints |
|---|---|---|
| `v0.1` | Runtime GPS-only prototype. Time all functions to which the `<5 ms` process/calculate constraint is assigned, including read/store, collection, and any processing/calculation wrappers implemented for the GPS/Serial0 chain. | Pass if every instrumented invocation in the accepted campaign completes in `<5 ms` after instrumentation overhead is accounted for; fail on any missing targeted function, unbounded wait, or sample `>=5 ms`. |
| `v0.2` | Runtime GPS+IMU prototype. Time angular velocity processing, acceleration processing, pitch/roll/yaw calculation, collection, and any other modeled Process/Calculate functions. | Pass if every targeted invocation is `<5 ms` across nominal, representative worst-case, and fault-data campaigns; v0.2 I2C timeout remains a separate model gap and shall not be hidden by this timing test. |
| `v0.3` | PCB-only delivery with no logical/runtime functions. | Pass/N/A if the copied v0.3 source view is reviewed and no runtime Process/Calculate behavior is modeled. |
| `v1.0` | Integrated ADS Processing/OBCC runtime. Time process/calculate functions before values are delivered to OBCC where applicable. | Pass if every targeted ADS Processing invocation is `<5 ms`, evidence is tied to the v1.0 firmware build, and timing does not invalidate GPS/IMU/attitude or OBCC delivery chains. |

## Viewpoints

- **Statistical significance:** apply the sample-count rule stated for this activity before making a formal statistical or deadline claim; otherwise classify evidence as characterization/screening only.
- **Fault hardening:** execute the activity-specific fault cases modeled in the definition views and do not accept invalid, stale, corrupt, or missing data as valid evidence.
- **Configuration control:** every report identifies ADS version/SSIV, source-view copy, hardware revision/BOM, firmware commit/build, instrumentation build, equipment IDs/calibration status, operator, and deviations.
- **Environmental context:** record ambient temperature/humidity, power conditions, and any test-specific environmental or ESD constraints before execution.

## Required execution conditions

- Record ADS version, source-view copy, hardware revision, firmware commit/build, instrumentation build, logger timebase, and timer resolution.
- Measure and subtract or bound instrumentation overhead before verdicts.
- Use `n = 59` representative samples with zero violations for any formal 95/95-style deadline planning claim; otherwise report the campaign as characterization.
- Include representative nominal data and fault-data cases that exercise worst-case branches without silently changing the modeled function allocation.

## Expected report locations

Reports should reference this modeled definition and store evidence under:

- `../results/ADS-IVV-C-PROC-5MS/v0.1/`
- `../results/ADS-IVV-C-PROC-5MS/v0.2/`
- `../results/ADS-IVV-C-PROC-5MS/v0.3/`
- `../results/ADS-IVV-C-PROC-5MS/v1.0/`

Each report shall identify referenced model views/elements, selected SSIV/version, as-tested/as-inspected configuration, raw evidence, analysis settings, actual environmental and equipment conditions, pass/fail or N/A rationale, deviations, anomalies, waivers, limitations, and retest status.

## Assumptions and residual gaps

- Firmware instrumentation hook names are report-time mapping records. The overhead allowance is selected: instrumentation overhead shall be `<=5%` of the 200 ms period or `<=5 ms`, and measured overhead must be recorded or bounded before verdicts.
- Traceability IDs remain placeholders until explicit Capella mission/capability/feared-event elements exist.

## Status

Modeled definition ready for review. Execution remains pending.
