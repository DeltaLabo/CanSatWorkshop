# AMS Blocker Closure Record — Definition Decisions

Date: 2026-07-02

## Scope

This record captures AMS definition-blocker closure decisions only. It does not execute tests, does not create execution reports, and does not claim pass/fail credit. Later issues must update the affected AMS, ADS, PM&SE, and model artifacts before any execution or closure credit is taken.

The decisions below use the AMS blocker resolution plan, `PM&SE/CON-003_Candidates_and_Definition_Blockers.md`, `PM&SE/MBSE_Test_Plan_Assessment.md`, `PM&SE/IVV.md`, the AMS README, the AMS MBSE test index, the referenced AMS activity READMEs, and `PM&SE/ADS_Blocker_Closure_Record_2026-07-02.md` as context. Where implementation details remain unknown, this record selects the conservative documented path and records follow-up.

## Shared ADS/AMS sensor-to-OBCC freshness rule

ADS and AMS shall use one shared sensor-to-OBCC freshness/status contract for v1.0 internal delivery planning:

- ADS/AMS respond to OBCC collection requests at `5 Hz` internal cadence.
- OBCC LoRa telemetry remains a separate `2 s` push cadence.
- At each `2 s` telemetry push, each required ADS/AMS sensor value shall either be fresh with age `<=400 ms` or explicitly non-valid.
- Freshness evidence shall include a timestamp, sequence, age field, or equivalent monotonic proof at the ADS/AMS-to-OBCC observation point.
- Status enum is exactly: `VALID`, `STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, `INIT_FAIL`.
- Only `VALID` may be consumed or reported as fresh data. After timeout, runtime sensor fault, or startup init failure, old values shall not remain marked `VALID`.
- Local low-level implementation codes may exist, but test definitions shall map their external ADS/AMS-to-OBCC result to the shared enum without losing fault evidence.

## Blocker decision table

| Blocker ID | Selected closure decision | Candidate / new tests | Existing-test updates | Prerequisites before execution | Closure / follow-up status |
|---|---|---|---|---|---|
| AMS-BLK-001 | Add a real temperature step-response verification for the AMS README requirement that temperature response time is `<=60 s`. Existing accuracy/exposure/timing tests are not enough by themselves. | Add `AMS-V10-TEMP-RESPONSE-60S` or an explicitly equivalent modeled step-response activity. It may be a standalone folder or a clear extension of `AMS-VV-FC-001` if the model remains readable. | Update the AMS test index and the atmospheric-measurement FC definition to reference the response-time activity; keep sunlight/airflow exposure context aligned with `AMS-VV-CON-001` as applicable. | Stable thermal source or chamber, reference thermometer, declared step definition, timestamp method, UUT/firmware/configuration IDs, ambient/exposure evidence, and response-time oracle. | Definition decision closed here; modeled test definition, D2/PNG regeneration, and execution remain follow-up. |
| AMS-BLK-002 | Use the shared ADS/AMS freshness rule above for AMS-to-OBCC internal delivery/freshness. The `5 Hz` internal collection contract and the `2 s` LoRa telemetry cadence are separate. | Add `AMS-V10-DATA-FRESHNESS` or extend `AMS-VV-API-001`, `AMS-VV-FC-001`, and `AMS-VV-FC-002` with the shared age/status rule; also track the ADS and system alignment rows listed below. | Update `AMS-VV-API-001` return/status semantics, `AMS-VV-FC-001` currentness/order checks, `AMS-VV-FC-002` init-fault status checks, `AMS-VV-CON-003` timeout/fault status mapping, and `AMS-VV-CON-004` bounded non-blocking fault propagation. | Shared contract artifact, OBCC log or harness, timestamp/sequence/age evidence, status mapping, source/API baseline, firmware build, UUT ID, and analysis script/tool versions. | Definition decision closed here; contract creation, AMS/ADS/system test-definition updates, model updates, and execution remain follow-up. |
| AMS-BLK-003 | Non-issue. AMS `v0.2` was the PCB-ready delivery baseline only; no native `v0.2` logical, CE, allocation, or functional-chain closure is required beyond the existing PCB/bring-up caveats. | None. Do not create synthetic native `v0.2` logical/CE/allocation/FC tests just for closure. | Preserve existing `AMS-V02-PCB-001` and `AMS-V02-BRINGUP-001` wording that limits claims to PCB delivery and powered reachability, not native allocation/FC closure. | Execution reports shall identify the `v0.2` PCB baseline and avoid over-claiming logical/functional closure. | Recorded as a non-issue and closed at definition level; no source D2 update required unless future stakeholders explicitly require native `v0.2` source views. |
| AMS-BLK-004 | Close at definition level by requiring complete API and non-blocking evidence: 100% getter/OBCC collection-path inventory, explicit statuses, pointer ownership/lifetime/null policy, static callable-path review, dynamic timing/non-blocking traces, and dependency on `AMS-VV-CON-003` for I2C timeout evidence. | No new behavioral candidate is required if `AMS-VV-API-001` and `AMS-VV-CON-004` are updated and executed with the full checklist. | Update `AMS-VV-API-001` checklist/status criteria and `AMS-VV-CON-004` static/dynamic callable-path criteria; cross-reference `AMS-VV-CON-003` for I2C timeout/recovery and ensure FC tests consume the same statuses. | Controlled API contract, source/build map or equivalent instrumentation, complete getter and OBCC path inventory, static-analysis output, profiler/timer traces, fault-injection evidence, and `AMS-VV-CON-003` evidence. | Definition decision closed here; execution evidence is still required and incomplete evidence remains a hold, not a pass. |
| AMS-BLK-005 | Non-issue for AMS once system-level tests are introduced. Provisional AMS trace labels are acceptable until system/source trace modeling adds explicit mission, capability, use-case, and feared-event nodes. | No AMS-only trace candidate is required. Update `SYS-END-TO-END-DATA` and related system-level planning so cross-subsystem traceability covers the same freshness/status rule. | Later PM&SE updates shall align `CON-003` and the assessment system-candidate text; AMS test READMEs can continue using provisional labels until model trace elements exist. | System-level MBSE test package, system/source trace elements or approved provisional-label policy, and final requirement-to-test closure matrix. | Recorded as a non-issue and closed for AMS definition planning; system model/test-definition follow-up remains. |

## Candidate and update register selected by this record

| Candidate / update ID | Type | Purpose | Selected definition baseline | Later implementation path |
|---|---|---|---|---|
| `AMS-V10-TEMP-RESPONSE-60S` | New AMS candidate test | Close the AMS temperature response-time requirement. | Apply a controlled temperature step to the AMS/BME280 environment and verify the reported temperature reaches the defined final/reference condition within `<=60 s`; retain raw timestamps, reference data, AMS data, exposure state, and uncertainty/deviation notes. | Prefer a standalone modeled activity if the response oracle needs its own D2 chain; otherwise extend `AMS-VV-FC-001` clearly and update the AMS test index. |
| `AMS-V10-DATA-FRESHNESS` | AMS candidate or existing-test extension | Close AMS-to-OBCC internal data freshness/rate planning. | Use the shared rule: `5 Hz` OBCC requests, `2 s` telemetry pushes, fresh age `<=400 ms` or explicit non-valid status, exact enum `VALID`/`STALE`/`NO_DATA`/`TIMEOUT`/`SENSOR_FAULT`/`INIT_FAIL`, and no old data marked valid after timeout/fault. | Prefer extending `AMS-VV-API-001`, `AMS-VV-FC-001`, `AMS-VV-FC-002`, `AMS-VV-CON-003`, and `AMS-VV-CON-004`; create a new folder only if the extensions become unclear. |
| `ADS-V10-DATA-FRESHNESS` | ADS alignment update | Align ADS v1.0 freshness/rate planning with the same ADS/AMS rule. | ADS uses the same `5 Hz` internal OBCC request/response freshness contract, `2 s` LoRa cadence separation, `<=400 ms` fresh age, six-status enum, timestamp/age evidence, and stale-valid prohibition. | Implement in later ADS issues through existing ADS OBCC-delivery, getter/API, rate, mission-window, and no-blocking tests rather than editing ADS files in this issue. |
| `SYS-END-TO-END-DATA` freshness/status update | PM&SE system candidate update | Ensure end-to-end system data validation uses the same sensor freshness/status oracle from truth/reference stimulus to DPS CSV/dashboard. | The system candidate shall require canonical payload fields, units, timestamps, freshness age, the shared six-status enum, no stale-valid behavior, and observability from ADS/AMS through OBCC LoRa to DPS storage/display. | Update `PM&SE/CON-003_Candidates_and_Definition_Blockers.md`, `PM&SE/MBSE_Test_Plan_Assessment.md`, and the future system-level MBSE test package in later issues. |
| AMS API/non-blocking evidence checklist | Existing-test update, no new candidate | Make API/getter and scheduler/no-blocking closure auditable. | `AMS-VV-API-001` and `AMS-VV-CON-004` must together provide 100% getter/OBCC collection inventory, explicit status mapping, pointer policy, static callable-path review, dynamic timing/non-blocking traces, and `AMS-VV-CON-003` dependency. | Update AMS READMEs and D2 definitions later; absence or partial evidence remains a hold during execution. |
| AMS `v0.2` native logical/CE/allocation/FC closure | Not selected | Prevent over-scoping historical `v0.2` closure. | `v0.2` remains PCB delivery plus bring-up reachability only; no native logical/CE/allocation/FC closure is created. | Preserve caveat text in planning and reports; only add native views if a future controlled decision requires them. |
| AMS provisional trace-label closure | Not selected as AMS test | Avoid creating AMS-only trace work when the issue is system/source modeling. | AMS provisional trace IDs are acceptable until system tests and source trace elements are modeled. | Update system model and requirement-to-test matrix later. |

## Existing-test update list for later issues

### AMS API, functional-chain, and constraint tests

| Existing activity | Required update |
|---|---|
| `AMS/MBSE/tests/README.md` | Add or reference `AMS-V10-TEMP-RESPONSE-60S`; record the preferred implementation path for `AMS-V10-DATA-FRESHNESS`; keep `v0.2` PCB-only disposition and provisional trace-label caveat aligned with this record. |
| `AMS-VV-API-001` | Add the shared six-status enum, age/timestamp evidence, stale-valid prohibition, 100% getter and OBCC collection-path inventory, pointer ownership/lifetime/null policy, and explicit mapping from implementation return codes to `VALID`, `STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, and `INIT_FAIL`. |
| `AMS-VV-FC-001` | Add freshness/currentness criteria for atmospheric measurement collection: OBCC receives current values in modeled order, valid values have age `<=400 ms` where freshness is claimed, non-valid values carry the shared status, and stale data is not accepted as current. Reference or incorporate the temperature response-time activity. |
| `AMS-VV-FC-002` | Align BME280 init-state and startup-fault evidence with `INIT_FAIL` and the stale-valid prohibition; prevent default/previous boot OK values from being treated as current valid status. |
| `AMS-VV-CON-003` | Map environmental I2C timeout/fault outcomes to the shared contract for external OBCC-facing status while retaining low-level evidence. Ensure no timed-out or faulted read returns old data as `VALID`. |
| `AMS-VV-CON-004` | Add the required static callable-path review, dynamic non-blocking/timing traces, bounded error/status propagation, and explicit dependency on `AMS-VV-CON-003` for I2C wait timing/recovery. |
| `AMS-VV-CON-001` | Keep sunlight/airflow exposure evidence available as context for temperature accuracy and response-time interpretation, without claiming response-time closure unless the new response oracle is present. |

### ADS freshness-alignment tests

| Existing ADS activity area | Required update |
|---|---|
| ADS OBCC-delivery / Pointers-Returns tests | Reference the shared ADS/AMS freshness rule, six-status enum, timestamp/age evidence, pointer/return ownership policy, watchdog/timeout behavior, and no stale-valid behavior. |
| ADS getter/API tests | Align getter return/status semantics to the shared enum or a controlled mapping to it; preserve implementation-specific fault detail only as subordinate evidence. |
| ADS rate/freshness tests | Treat v1.0 internal ADS-to-OBCC delivery as applicable at `5 Hz`; distinguish it from `2 s` LoRa telemetry; require age `<=400 ms` for fresh data and explicit non-valid status otherwise. |
| ADS mission-window/no-blocking tests | Use the same freshness age/status rule for sustained runs and fault cases, including timeout/fault transitions that must not leave old data marked valid. |

### PM&SE system candidate text

| PM&SE artifact area | Required update |
|---|---|
| `SYS-END-TO-END-DATA` candidate text | Add canonical payload, units, timestamps, freshness age, shared six-status enum, no stale-valid behavior, and observability from ADS/AMS through OBCC to DPS CSV/dashboard. |
| `CON-003` subsystem candidate/backlog text | Replace open AMS response/freshness blocker wording with the selected candidate/update path after the later cleanup issue updates the register. |
| `MBSE_Test_Plan_Assessment` system-test and gap text | Align `SYS-END-TO-END-DATA`, ADS/AMS rate/freshness gaps, and final next actions with this record after the detailed contract and test-definition updates exist. |

## Follow-on D2/model and artifact update list

The following work is intentionally not performed in this issue:

1. Create or update AMS D2 test-definition views for `AMS-V10-TEMP-RESPONSE-60S`, then regenerate matching PNGs.
2. Update AMS API/FC/CON D2 definition views to include the shared freshness/status contract, age/timestamp evidence, stale-valid prohibition, and evidence checklist items.
3. Create the shared ADS/AMS freshness contract artifact and reference it from IVV/test definitions in the dedicated contract issue.
4. Update ADS D2/test-definition views for OBCC delivery, getter/API, rate/freshness, mission-window, and no-blocking alignment.
5. Model the system-level `SYS-END-TO-END-DATA` test package with payload, timestamp, freshness/status, and DPS CSV/dashboard observability criteria.
6. Add source model trace elements for missions, capabilities, use cases, and feared events, or approve a controlled provisional-label policy until those elements exist.
7. Update `PM&SE/CON-003_Candidates_and_Definition_Blockers.md` and `PM&SE/MBSE_Test_Plan_Assessment.md` in the final cleanup issue after contract/test alignment.
8. Do not create native AMS `v0.2` logical, CE, allocation, or FC source views unless a later controlled decision changes the PCB-only delivery disposition.

## Residual execution-only uncertainties

- Exact temperature step method, final-value/settling definition, sample count, thermal fixture or chamber model, and response-time analysis script.
- Exact ADS/AMS API/header names, field names, status-code mapping, timestamp source, clock synchronization or monotonic-age method, and sequence/age encoding.
- OBCC harness/logging implementation, telemetry payload schema version, and DPS CSV/dashboard field mapping for system end-to-end evidence.
- UUT serial numbers, hardware revisions, firmware commits, source/build maps, symbols, instrumentation hooks, and instrumentation overhead.
- Actual equipment asset IDs, calibration certificates or function checks, tool versions, environmental limits, and lab configuration.
- Whether AMS freshness and temperature response are implemented as standalone folders or as extensions to existing AMS activities; choose the path that keeps the modeled definition clearest.
- How and when system/source trace nodes will be modeled versus retaining provisional trace labels under controlled rationale.
