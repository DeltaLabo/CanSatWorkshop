# ADS-IVV-C-RATE-5HZ — internal 5 Hz collection-rate constraint verification definition

**Activity selected for this definition session:** `ADS-IVV-C-RATE-5HZ`.

**IADT method:** Testing with supporting Analysis.

**IVV source category:** constraint.

**Selected SSIV/development scope:** all ADS MBSE versions currently present: `v0.1`, `v0.2`, `v0.3`, and `v1.0`. The source-modeled `At 5 Hz` constraint verification applies to `v0.1` and `v0.2`. `v0.3` remains N/A. For `v1.0`, `ADS-V10-DATA-FRESHNESS` is the conservative planning alias/extension through this activity, `ADS-IVV-FC-OBCC-DELIVERY`, and `ADS-IVV-C-GETTER`; existing D2/model views may still carry the old v1.0 N/A rationale and require follow-up before model-level closure.

**Traceability targets:** constraint `5 Hz`, model element `Collect measurements`, GPS/collection/logging timestamps, loop timing context, `ADS-CAP-GPS`, `ADS-CAP-DELIVERY`, and feared event `ADS-FE-STUCK-LOOP`.

**References cited in diagrams:** IVV skill rules, ADS MBSE IVV plan `../README.md`, copied source views under `source_views/`, and SW/statistics references from the ADS MBSE test-plan legend. No external research was performed for this definition.

**Shared freshness contract:** v1.0 rate/freshness uses [`PM&SE/contracts/sensor_obcc_freshness_contract.md`](../../../../PM&SE/contracts/sensor_obcc_freshness_contract.md). ADS shall support OBCC requests/responses at `5 Hz` (`200 ms` nominal); `2 s` LoRa telemetry is a separate packaging cadence, not internal `5 Hz` evidence; fresh ADS data requires `status == VALID` and `age_ms <= 400 ms`; the exact enum is `VALID`, `STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, `INIT_FAIL`.

## Source-view copies

All D2 and PNG source views for the selected all-version scope were copied into this package so reports can reference a stable definition baseline:

- `source_views/v0.1/` — physical, logical, functional allocation, GPS position chain, and Serial logging chain.
- `source_views/v0.2/` — physical, logical, functional allocation, GPS, angular velocity, attitude estimation, peripheral initialisation, and Serial logging chains.
- `source_views/v0.3/` — physical PCB-delivery view used for N/A rationale.
- `source_views/v1.0/` — physical, logical, functional allocation, GPS, angular velocity, attitude estimation, and peripheral initialisation chains. These source copies still show no explicit ADS `At 5 Hz` constraint; the v1.0 freshness path is a shared-contract planning extension pending model/D2 update.

## Definition-view catalogue

| View | Purpose |
|---|---|
| `definition_views/ADS_IVV_C_RATE_5HZ_view1_source_constraint_inventory.d2/png` | Source constraint inventory showing `At 5 Hz` on `Collect measurements` for `v0.1`/`v0.2`, timing context, and N/A rationale for `v0.3` plus the legacy v1.0 N/A rationale. The v1.0 `ADS-V10-DATA-FRESHNESS` contract path is queued as D2/model follow-up. |
| `definition_views/ADS_IVV_C_RATE_5HZ_view2_timestamp_logging_setup.d2/png` | Timestamp/logging setup with selected UUT, PC serial logger/timestamping tool, optional firmware instrumentation, reference clock, human conductor, analysis script, and power/ambient monitor. |
| `definition_views/ADS_IVV_C_RATE_5HZ_view3_verification_functional_allocation.d2/png` | Verification-only functional allocation for UUT timing hooks, human operator tasks, logging, firmware instrumentation, reference timebase, analysis, power/ambient monitoring, and IVV review. |
| `definition_views/ADS_IVV_C_RATE_5HZ_view4_rate_measurement_sequence.d2/png` | Functional-chain style rate-measurement sequence from baseline selection through timestamp capture, period/gap/stale analysis, verdict, and report recording. |
| `definition_views/ADS_IVV_C_RATE_5HZ_view5_evidence_traceability_view.d2/png` | Evidence and traceability record tying source constraints, raw logs, analysis outputs, verdicts, N/A rationale, and report locations. |

## Version coverage

| Version | Coverage and applicability | Pass/fail or N/A rule |
|---|---|---|
| `v0.1` | Applies. Source views model `At 5 Hz` as a constraint on `Collect measurements` in the `Loop`; GPS getter and Serial0 logging timestamps are supporting evidence paths. | Pass only if the pre-execution tolerance gate is satisfied and the recorded collection evidence meets all selected 5 Hz criteria. Fail on missing/invalid timing evidence, mean-rate violation, per-sample period/gap violation, unflagged stale/dropped values, loop stall, unresolved timestamp/timebase problem, or unreported deviation. |
| `v0.2` | Applies. Same explicit `At 5 Hz` constraint on `Collect measurements`, with additional GPS/IMU loop timing context and Serial0 logging evidence. | Same as `v0.1`, plus record whether IMU read/process activity affects collection periods, gaps, stale/drop markers, or logger behavior. |
| `v0.3` | N/A. Source package is PV1-only PCB delivery with no logical components, component exchanges, allocation, `Collect measurements` function, functional chain, or `At 5 Hz` constraint. | Pass/N/A if source review confirms 1/1 v0.3 view has no behavior to execute and physical UART/I2C traces are not credited as collection-rate behavior. |
| `v1.0` | Applicable by `ADS-V10-DATA-FRESHNESS` planning extension for internal ADS-to-OBCC freshness. Source/D2 views still lack an explicit ADS `At 5 Hz` constraint and may show the old N/A rationale. | Do not claim model-level pass until the D2/model follow-up is made or an approved report explicitly references this Markdown extension. Strict evidence shall show `5 Hz` OBCC request/response observations, `age_ms <= 400 ms` only with `VALID`, non-`VALID` status otherwise, exact enum mapping, and no stale/no-data/timeout/fault/init-fail values marked `VALID`. |

## Pass/fail criteria

- Nominal collection/request period is **200 ms** for the modeled/shared `5 Hz` constraint.
- For v1.0 `ADS-V10-DATA-FRESHNESS`, evaluate internal ADS-to-OBCC request/response observations, not the `2 s` LoRa telemetry cadence. Telemetry frames may carry the latest ADS sample plus age/status metadata, but they are not a substitute for `5 Hz` evidence.
- Before execution, the project must select and record allowed jitter and worst-gap tolerance. If this tolerance is not fixed before execution, the rate verdict is **blocked/limited**; observed timing may be characterized but not passed by an invented after-the-fact criterion.
- Evaluate, at minimum: mean collection/request rate, every per-sample period, worst gap, stale values, dropped/duplicated records, timestamp continuity, sequence/sample IDs, `age_ms`, status, and loop-stall/backpressure indicators.
- Fresh v1.0 ADS data requires `status == VALID` and `age_ms <= 400 ms`; non-fresh or unavailable data shall be marked with one of `STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, or `INIT_FAIL` and shall not be counted as fresh valid measurement data.
- If making a formal deadline/tolerance/freshness claim, use **`n = 59` representative samples** and require every sample period/gap and age/status observation to be inside the selected limit.
- Instrumentation overhead, logger timebase resolution/drift, and clock wrap behavior must be recorded and dispositioned before accepting a pass verdict.

## Statistical and fault-hardening viewpoints

- **Statistical significance:** preserve complete campaign records. A formal deadline/tolerance claim requires `n = 59` representative samples with all samples inside the selected limit. Repeated samples on one article are timing evidence for that configuration, not population reliability evidence unless a later sampling rationale is added.
- **Fault hardening:** evaluate or explicitly disposition loop stalls, timestamp loss, stale or dropped records, duplicated sample IDs, serial/logging backpressure, clock drift/wrap, power disturbance, missing/invalid sensor values, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, and `INIT_FAIL` transitions that could mask a stuck loop or leave old data marked `VALID`.
- **Traceability:** every report shall trace the executed version to the copied source views, `Collect measurements`, constraint `5 Hz`, `ADS-CAP-GPS`, `ADS-CAP-DELIVERY`, and `ADS-FE-STUCK-LOOP`.

## Required execution conditions

- Record selected ADS version, source-view copy, hardware revision, UUT identifier, firmware commit/build, logger configuration, optional timestamp-hook configuration, and analysis script revision.
- Use a PC serial logger/timestamping tool and, if used, firmware timestamp instrumentation around `Collect measurements`. Record timestamp resolution and overhead.
- Use a reference clock/timebase for the logger. Record method, uncertainty, drift/wrap checks, and calibration/function-check status.
- Use a power/ambient monitor. Record supply voltage/current and ambient temperature/humidity before and during repetitions; equipment model/ID/calibration are pre-execution data and remain TBD until execution.
- Preserve raw UUT logs, host timestamps, internal firmware timestamps if present, sample IDs, `age_ms`, status values, stale/drop/fault/init markers, power/ambient logs, analysis scripts/settings, and any deviations or anomalies.

## Expected report locations

Reports should reference this modeled definition and store evidence under:

- `../results/ADS-IVV-C-RATE-5HZ/v0.1/`
- `../results/ADS-IVV-C-RATE-5HZ/v0.2/`
- `../results/ADS-IVV-C-RATE-5HZ/v0.3/`
- `../results/ADS-IVV-C-RATE-5HZ/v1.0/`

Each report shall identify referenced model views/elements, selected SSIV/version, as-tested or N/A configuration, raw evidence, actual equipment/environment conditions, analysis settings, pass/fail/blocked/N/A rationale, deviations, anomalies, waivers, limitations, and retest status.

## Status

Markdown freshness alignment ready for review. Execution remains pending. The principal open execution gates are selection of allowable jitter/worst-gap tolerance, ADS-specific status/field mapping to the shared enum, and model/D2 update where existing views still mark v1.0 as N/A.

## Assumptions and gaps

- Controlled SSIV identifiers are inferred from folder names, not from a separate SSIV document.
- Placeholder traceability targets (`ADS-CAP-GPS`, `ADS-CAP-DELIVERY`, `ADS-FE-STUCK-LOOP`) follow the ADS MBSE IVV plan and need confirmation if formal capability/feared-event model elements are later added.
- `v1.0` source/D2 views currently have no explicit ADS `At 5 Hz` constraint and may still show a v1.0 N/A rationale; `ADS-V10-DATA-FRESHNESS` is the documented Markdown extension path until those views are updated.
- Equipment models/IDs, reference-clock uncertainty, logger configuration, firmware timestamp-hook overhead, and environmental limits are execution-time inputs and must be recorded before test execution.
