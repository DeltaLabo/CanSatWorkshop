# ADS-IVV-C-UART-5MS — UART read timeout <=5 ms verification

**IADT method:** Testing with supporting Analysis.

**IVV source category:** constraint.

**Selected SSIV/development scope:** ADS `v0.1`, `v0.2`, `v0.3`, and `v1.0`. Formal UART-timeout execution applies to `v0.1`, `v0.2`, and `v1.0`; `v0.3` is PCB-only N/A for runtime UART reads.

**Traceability targets:** `ADS-IVV-C-UART-5MS` traces to the UART read timeout `<=5 ms` constraint, `ADS-CAP-GPS`, `ADS-FE-STUCK-LOOP`, and `ADS-FE-SILENT-SENSOR-FAIL`. Explicit mission/capability/use-case/feared-event elements are not yet modeled, so placeholder ADS plan IDs remain in use.

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
| `definition_views/ADS_IVV_C_UART_5MS_view1_source_constraint_interface_inventory.d2/png` | Inventory UART timeout constraints, GPS UART exchanges, affected functions, and N/A branches. |
| `definition_views/ADS_IVV_C_UART_5MS_view2_uart_fault_timing_setup.d2/png` | Model GPS simulator/fault injector, disconnect harness, timing instrumentation, loggers, and environmental constraints. |
| `definition_views/ADS_IVV_C_UART_5MS_view3_verification_functional_allocation.d2/png` | Allocate verification-only timing/fault/logging functions to actors and equipment. |
| `definition_views/ADS_IVV_C_UART_5MS_view4_deadline_fault_sequence.d2/png` | Functional-chain style sequence for valid, silent, malformed, wrong-baud, stale, and recovery cases. |
| `definition_views/ADS_IVV_C_UART_5MS_view5_evidence_traceability.d2/png` | Model raw timing evidence, fault markers, analysis outputs, report references, and deviations. |

## Version coverage and pass/fail rules

| Version | Model element(s) covered | Pass/fail constraints |
|---|---|---|
| `v0.1` | GPS UART read path from UBX-G7020-KT GPS to Loop on XIAO. | Pass if every UART read returns valid data or timeout/error in `<=5 ms` under valid, silent/disconnected, malformed, and stale cases, and stored valid data are not silently corrupted. |
| `v0.2` | Same GPS UART timeout path in the GPS+IMU prototype. | Same as v0.1; additionally record whether concurrent IMU/Loop activity affects UART deadline evidence. |
| `v0.3` | PCB-only physical UART traces but no runtime UART read function. | Pass/N/A if no UART read function or logical/functional chain is modeled in v0.3. |
| `v1.0` | Integrated GPS UART path through ADS/backplane to ADS Processing/OBCC observation point. | Pass if the integrated UART read returns data or timeout/error in `<=5 ms` and invalid/stale GPS data are not accepted as valid by ADS Processing or OBCC. |

## Viewpoints

- **Statistical significance:** apply the sample-count rule stated for this activity before making a formal statistical or deadline claim; otherwise classify evidence as characterization/screening only.
- **Fault hardening:** execute the activity-specific fault cases modeled in the definition views and do not accept invalid, stale, corrupt, or missing data as valid evidence.
- **Configuration control:** every report identifies ADS version/SSIV, source-view copy, hardware revision/BOM, firmware commit/build, instrumentation build, equipment IDs/calibration status, operator, and deviations.
- **Environmental context:** record ambient temperature/humidity, power conditions, and any test-specific environmental or ESD constraints before execution.

## Required execution conditions

- Record GPS simulator/fault injector or disconnect harness configuration, firmware build, logger timebase, and timing instrumentation overhead.
- Include valid, silent/disconnected, malformed payload, wrong baud/framing where safe, stale data, and recovery cases.
- Use `n = 59` zero-violation samples per case for any formal deadline/tolerance claim.
- Keep GPS accuracy verdicts separate from UART timeout verdicts; timeout pass does not imply position accuracy pass.

## Expected report locations

Reports should reference this modeled definition and store evidence under:

- `../results/ADS-IVV-C-UART-5MS/v0.1/`
- `../results/ADS-IVV-C-UART-5MS/v0.2/`
- `../results/ADS-IVV-C-UART-5MS/v0.3/`
- `../results/ADS-IVV-C-UART-5MS/v1.0/`

Each report shall identify referenced model views/elements, selected SSIV/version, as-tested/as-inspected configuration, raw evidence, analysis settings, actual environmental and equipment conditions, pass/fail or N/A rationale, deviations, anomalies, waivers, limitations, and retest status.

## Assumptions and residual gaps

- Exact GPS UART fault injector equipment and firmware timing hooks are TBD.
- Expected GPS data schema/freshness markers must be fixed before execution.

## Status

Modeled definition ready for review. Execution remains pending.
