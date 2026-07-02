# ADS-IVV-C-NOBLOCK — no-unintended-blocking constraint verification definition

**IADT method:** Analysis with supporting Testing.

**IVV source category:** constraint.

**Selected SSIV/development scope:** ADS `v0.1`, `v0.2`, `v0.3`, and `v1.0`, as selected by the orchestration issue. Runtime no-blocking verification applies to `v0.1`, `v0.2`, and `v1.0`; `v0.3` is explicitly N/A because it is a PV1-only PCB-delivery model with no logical components, component exchanges, allocations, runtime functions, or functional chains.

**Traceability targets:** constraint `No blocking operations besides I2C or UART comms`, feared event `ADS-FE-STUCK-LOOP`, and capabilities `ADS-CAP-INIT` and `ADS-CAP-DELIVERY`.

**References cited in diagrams:** IVV, ADS MBSE IVV plan `../README.md`, SW/statistics references, GPS/UBX references, and IMU/I2C references. No external research was performed for this definition.

## Source-view copies

All ADS source D2/PNG views for the selected scope were copied into this activity package:

- `source_views/v0.1/` — physical, logical, allocation, GPS position chain, Serial logging chain.
- `source_views/v0.2/` — physical, logical, allocation, GPS, angular velocity, attitude estimation, peripheral initialisation, Serial logging chains.
- `source_views/v0.3/` — physical PCB delivery view; used only for N/A rationale.
- `source_views/v1.0/` — physical, logical, allocation, GPS, angular velocity, attitude estimation, peripheral initialisation chains.

## Definition-view catalogue

| View | Purpose |
|---|---|
| `definition_views/ADS_IVV_C_NOBLOCK_view1_source_constraint_function_inventory.d2/png` | Source constraint/function inventory for `v0.1`, `v0.2`, `v1.0`, plus explicit `v0.3` N/A rationale. |
| `definition_views/ADS_IVV_C_NOBLOCK_view2_analysis_test_setup.d2/png` | Analysis/test setup with UUT selection, code/model review station, timing tool, watchdog/heartbeat instrumentation, logger, GPS and IMU fault injectors, human test conductor, power/ambient monitor, PLs/CEs, and constraints. |
| `definition_views/ADS_IVV_C_NOBLOCK_view3_verification_functional_allocation.d2/png` | Verification-only functional allocation to human operators, analysis tools, logger, fault injectors, watchdog instrumentation, environment monitor, quality authority, and UUT observation adapter. |
| `definition_views/ADS_IVV_C_NOBLOCK_view4_review_runtime_fault_sequence.d2/png` | Functional-chain-style analysis and supporting runtime fault sequence for model/code review, instrumentation, GPS/I2C fault injection, heartbeat observation, evidence analysis, and verdict. |
| `definition_views/ADS_IVV_C_NOBLOCK_view5_evidence_traceability.d2/png` | Evidence and traceability interface view linking source views, firmware/configuration source, equipment archive, analysis results, verdict, expected reports, and ADS-wide coverage update. |

All definition views were rendered to PNG with the required ELK command.

## Version coverage

| Version | Model elements covered | Pass/fail constraints |
|---|---|---|
| `v0.1` | Constraint `No blocking operations besides I2C or UART comms`; `Loop`/`Setup`; `Read and store lat, lon`; `Get UBX-G7020-KT init state`; `Get lat`; `Get lon`; `Collect measurements`; `Log via Serial0`; GPS and Serial logging chains. | Pass if complete model/source review and supporting runtime evidence show that only the modeled UART read may wait for external data, every UART read returns data or timeout/error within the modeled `<=5 ms`, non-UART functions do not block on external data, Loop heartbeat/progress remains observable under silent/malformed GPS cases, and no hidden wait state is found. Fail on any forbidden external wait, missing UART timeout/error behavior, stuck Loop, hidden wait, or unreviewed implementation path. |
| `v0.2` | v0.1 elements plus IMU I2C reads: `Read angular velocities`, `Read accelerations`, `Read field intensities`, `Respond to I2C Requests`, `Get ICM20948 init state`, `Process angular velocities`, `Process accelerations`, `Calculate pitch, roll, yaw`, init/runtime chains. | Pass if complete review shows all non-UART/non-I2C functions do not block, UART timeout `<=5 ms` is implemented, I2C blocking is bounded by timeout/error behavior, Loop progress remains observable under silent/malformed GPS and IMU NACK/stuck-bus/partial-read cases, and no hidden wait state is found. Record the missing explicit v0.2 I2C timeout constraint as a model gap; do not pass runtime I2C behavior without source or instrumentation evidence of bounded recovery. |
| `v0.3` | PV1-only PCB delivery: ADS PCB, GPS, IMU, connector, footprints, UART/I2C/3V3 traces. No runtime no-blocking model element exists. | Pass/N/A if the copied `v0.3` source view is reviewed and confirmed to contain no LC, CE, allocation, runtime functions, functional chains, or no-blocking constraint. Fail if runtime behavior is claimed from PCB traces alone or if any behavior view is found but not dispositioned. |
| `v1.0` | Constraint `No blocking operations besides I2C or UART comms`; `ADS Processing`; `OBCC`; UART GPS reads; I2C IMU reads; process/calculate/getter functions; `Collect measurements`; `Collect peripheral init states`; init/runtime chains; Pointers/Returns delivery context. | Pass if complete review and supporting runtime evidence show all non-UART/non-I2C functions do not block on external data, UART and I2C reads return data or timeout/error within modeled `<=5 ms`, ADS Processing/OBCC progress remains observable under silent/malformed GPS and IMU NACK/stuck-bus cases, Pointers/Returns do not introduce hidden waits, and no hidden wait state is found. Fail on any forbidden wait, missing timeout/error behavior, stuck ADS Processing/OBCC, stale/invalid state causing indefinite wait, or unreviewed path. |

## Pass/fail criteria

Pass requires all applicable criteria for the selected version:

1. 100% of modeled no-blocking target functions and discovered blocking/wait call sites are reviewed against the copied source views and implementation evidence.
2. Non-I2C/non-UART functions do not block while waiting for external data.
3. UART and I2C waits are confined to modeled communication functions and are bounded by timeout/error behavior; modeled `<=5 ms` UART/I2C timeout constraints are enforced where present.
4. Loop or ADS Processing heartbeat/cycle progress remains observable during nominal execution and during applicable silent/malformed GPS and I2C NACK/stuck-bus fault cases. The selected heartbeat/progress deadline is **250 ms nominal** during 5 Hz operation, with no mission-window/freshness progress gap greater than **400 ms** under fault cases unless a non-`VALID` status is reported and safe behavior is maintained.
5. Timing hooks/logging overhead is measured and is `<=5%` of the 200 ms period or `<=5 ms`, whichever is stricter for the claim being made; otherwise the timing verdict is limited/blocked or the overhead is subtracted/bounded with documented uncertainty.
6. No hidden wait state, unbounded retry loop, indefinite delay, blocking logger path, unsafe pointer/return wait, or unreported reset/stall is found.
7. If firmware source, build map, symbols, or equivalent runtime instrumentation access is absent, execution status is **blocked/limited** and no pass verdict may be claimed.

## Viewpoints

- **Statistical significance:** source/model review is complete enumeration of the targeted model functions and discovered blocking call sites, not sampling. Runtime timing evidence supports fault-hardening and deadline claims; use `n=59` zero-violation samples for any formal 95/95 deadline/timeout or heartbeat/progress claim. If no formal statistical claim is made, report runtime samples as supporting evidence only.
- **Fault hardening:** silent GPS/UART, malformed or partial GPS payload, UART timeout, stale GPS state, IMU NACK, wrong address, partial I2C read, stuck SDA/SCL/bus lock, recovery, reset/stall, logger loss, stale getter state, and hidden waits in Pointers/Returns for `v1.0`.
- **Configuration control:** each report shall name ADS version/SSIV, source-view copy, hardware revision, firmware commit/build, instrumentation build, equipment IDs/calibration status, operator/reviewer, deviations, anomalies, waivers, limitations, and retest status.
- **Environmental context:** before runtime repetitions, the human operator records bench voltage/current and ambient temperature/humidity from the modeled bench supply and ambient monitor. If these are not recorded, the run is limited for interpretation rather than silently passed.

## Required execution conditions

- Select and record one target version per execution (`v0.1`, `v0.2`, `v0.3`, or `v1.0`) and reference this definition package.
- For runtime versions, provide firmware source or equivalent instrumentation access, build map/symbols, instrumented firmware image, compiler/toolchain ID, logger timebase, watchdog/heartbeat method, timing-overhead measurement, analysis script revision, and fault-injector configuration.
- Execute or explicitly disposition nominal runtime, silent/malformed GPS, and recovery cases for `v0.1`, `v0.2`, and `v1.0`.
- Execute or explicitly disposition IMU NACK/stuck-bus/partial-read cases for `v0.2` and `v1.0`; they are N/A for `v0.1` and runtime-N/A for `v0.3`.
- Preserve raw logs, timing analysis outputs, heartbeat/progress traces, instrumentation-overhead measurements, call graph/blocking-call inventory, fault markers, environmental readings, analysis scripts/settings, deviations, anomalies, limitations, and retest data.

## Expected report locations

Reports should reference this modeled definition and store evidence under:

- `../results/ADS-IVV-C-NOBLOCK/v0.1/`
- `../results/ADS-IVV-C-NOBLOCK/v0.2/`
- `../results/ADS-IVV-C-NOBLOCK/v0.3/`
- `../results/ADS-IVV-C-NOBLOCK/v1.0/`

Each report shall identify referenced model views/elements, selected SSIV/version, as-analyzed/as-tested configuration, source/instrumentation access, actual execution conditions, raw evidence, pass/fail or N/A rationale, deviations, anomalies, waivers, limitations, and retest status.

## Status

Modeled definition ready for review. Execution remains pending.

## Assumptions and gaps

- Controlled SSIV IDs and formal capability/feared-event model elements are not present in the source D2; this definition uses the ADS-wide placeholder trace targets from `../README.md`.
- Firmware source/instrumentation access is not confirmed. A pass verdict requires such access or equivalent evidence.
- `v0.2` does not explicitly model an I2C timeout constraint; this is retained as a model gap while still requiring bounded I2C error/timeout behavior before execution can pass.
- Loop/progress heartbeat criteria are selected as 250 ms nominal and 400 ms maximum gap; instrumentation overhead allowance is selected as `<=5%` of the 200 ms period or `<=5 ms`, whichever is stricter for the claim. Exact instrumentation method and measured overhead remain execution prerequisites.
- `v1.0` has no ADS Serial0 chain; use OBCC/runtime logger evidence for progress and delivery observations.
