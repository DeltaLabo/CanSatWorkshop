# CON-003 Candidate and Open Definition-Blocker Register

Assessment follow-up date: 2026-07-01

Purpose: support `CON-003` in `PM&SE/MBSE_Test_Plan_Assessment.md` by separating (1) verification activities that are still planning candidates from (2) open definition blockers that prevent unqualified execution credit.

Scope reviewed: `PM&SE/MBSE_Test_Plan_Assessment.md`, subsystem `*/MBSE/tests/README.md` plans, PDM version-local test plans, and available DPS/PDM version-local test plans.

Interpretation:

- **Candidate** means a test row is still planning-level or needs a detailed modeled verification definition before it can be treated as executable MBSE verification.
- **Definition blocker** means the test may already have a modeled definition, but a missing requirement decision, schema, oracle, tolerance, source-model update, or controlled waiver blocks unqualified pass/fail credit.
- Pure execution-evidence gaps are not exhaustively repeated here unless the missing item defines the pass/fail oracle.

## 1. Candidate definitions to create or complete

### 1.1 System-level candidates not yet modeled

These are proposed in `PM&SE/MBSE_Test_Plan_Assessment.md` §4 and are still candidate system-level MBSE tests.

| Candidate ID | Purpose | Definition work still needed |
|---|---|---|
| `SYS-FLIGHT-READINESS-CLOSURE` | Final CanSat-level readiness closure. | Create PM&SE/system test folder, closure matrix, waiver/deviation rules, final board pass/fail criteria. |
| `SYS-MISSION-REHEARSAL` | Full assembled CanSat + DPS mission sequence. | Define integrated sequence, payload/schema oracle, deployment inhibit/trigger branches, timing tolerances, evidence paths. |
| `SYS-RF-RANGE-PDR` | Final-article RF range/PDR. | Define field/RF-equivalent setup, legal radio settings, antenna/enclosure orientation, sample size, exact-binomial threshold. |
| `SYS-END-TO-END-DATA` | Truth/reference stimulus to DPS CSV/dashboard evidence. | Define canonical payload, units, timestamps, and the shared PM&SE ADS/AMS freshness/status/age rule (`5 Hz` OBCC requests, `2 s` LoRa packaging, fresh age `<=400 ms` only with `VALID`, enum `VALID`/`STALE`/`NO_DATA`/`TIMEOUT`/`SENSOR_FAULT`/`INIT_FAIL`, and no old data marked `VALID` after stale/no-data/timeout/fault/init-fail), plus cross-subsystem observability points. |
| `SYS-POWER-ENDURANCE-TRANSIENT` | Full-system power under mission load. | Define mission load profile, servo/RF/sensor transient cases, rail/current/thermal/brownout oracle. |
| `SYS-DEPLOYMENT-SAFE-LIVE` | ADS/OBCC/PDM/PDS/S&A deployment interaction. | Define safe fixture/live sequence policy, Stand-by inhibit, On trigger timing, false-success checks. |
| `SYS-ENVIRONMENTAL-REGRESSION` | Critical functions after mechanical/environmental screens. | Define approved screen levels and post-screen functional regression set. |
| `SYS-WORKSHOP-READINESS` | Educational/reproducibility closure. | Define independent-user rebuild, guide/documentation, BOM/materials-list, and workshop learning-readiness checks. |

### 1.2 Subsystem candidate backlog

| Area | Candidate activity IDs / candidate definitions | Current status | Immediate definition action |
|---|---|---|---|
| ADS | Candidate/update path: `ADS-V10-DATA-FRESHNESS` via `ADS-IVV-FC-OBCC-DELIVERY`, `ADS-IVV-C-GETTER`, and `ADS-IVV-C-RATE-5HZ` or a clear equivalent. | Shared PM&SE sensor-to-OBCC contract selects v1.0 ADS-to-OBCC `5 Hz` freshness/status semantics; existing D2/model updates and execution remain pending. | Update ADS definitions to use `5 Hz` OBCC requests, `2 s` LoRa packaging separation, fresh `age_ms <= 400 ms` only with `VALID`, the six-status enum, and no stale/timeout/fault/init-fail data marked `VALID`. |
| ADS | `ADS-IVV-C-ACCEL-3AXIS` | README-only candidate definition created for 3-axis linear acceleration units/accuracy; D2/model package and execution remain pending. | Model the candidate in D2 later and execute with six-face static gravity fixture, `m/s²`/`g` conversion, `n=59` strict samples, and guard-banded pass/fail oracle. |
| ADS | `ADS-IVV-C-HEADING-NORTH` | README-only candidate definition created for quantitative heading/north accuracy; D2/model package and execution remain pending. | Model the candidate in D2 later and execute with controlled true/magnetic north reference, magnetic-disturbance controls, `n=59` strict samples, and `<=10°` guard-banded circular-error oracle. |
| AMS | New candidate: `AMS-V10-TEMP-RESPONSE-60S` or modeled equivalent for temperature step-response `<=60 s`. | Selected candidate/update path; AMS accuracy/exposure/I2C/timing plans do not by themselves close response time, and D2/modeling plus execution remain pending. | Add a standalone step-response activity or clearly extend `AMS-VV-FC-001` with declared step definition, reference data, timestamp evidence, exposure context, and explicit `<=60 s` pass/fail criteria. |
| AMS | Candidate/update path: `AMS-V10-DATA-FRESHNESS` via `AMS-VV-API-001`, `AMS-VV-FC-001`, `AMS-VV-FC-002`, `AMS-VV-CON-003`, and `AMS-VV-CON-004` or a clear equivalent. | Shared PM&SE sensor-to-OBCC contract resolves AMS `5 Hz` freshness/status semantics; D2/modeling and execution remain pending. | Update AMS definitions to use `5 Hz` OBCC requests, separate `2 s` LoRa packaging, fresh `age_ms <= 400 ms` only with `VALID`, the six-status enum, timestamp/age evidence, and no stale/timeout/fault/init-fail data marked `VALID`. |
| DPS v1.0 | `DPS-V10-T-004` | Candidate, detailed definition required. | Define CanSat transmit-path test: near-field/final receiver, sequence oracle, radio-busy/not-ready, buffer-overrun cases. |
| DPS v1.0 | `DPS-V10-T-005` | Candidate, UI oracle required. | Define dashboard visualization oracle, payload-to-plot mapping, browser evidence, latency alert, stale/invalid-field behavior. |
| DPS v1.0 | `DPS-V10-T-006` | Candidate, fault-injection detail required. | Define forwarder restart campaign, SPI/radio/UART missing-fault injections, false-ready oracle. |
| DPS v1.0 | `DPS-V10-C-001` | Candidate, range definition required. | Define 500 m or RF-equivalent setup, PDR threshold/sample count, RSSI/SNR logging, legal settings. |
| DPS v1.0 | `DPS-V10-C-003` | Candidate, load definition required. | Define mission-duration concurrency and optional 5 Hz stress load, queue/memory/backlog/latency criteria. |
| DPS v1.0 | `DPS-V10-C-004` | Candidate, browser set TBD. | Select supported browser(s), refresh/reconnect behavior, user-operation oracle. |
| DPS v1.0 | `DPS-V10-C-005` | Candidate, filesystem oracle needed. | Define session/restart cases, filename uniqueness oracle, overwrite/checksum checks. |
| DPS v1.0 | `DPS-V10-C-006` | Candidate, threshold oracle needed. | Define timestamp source, boundary cases around `>1 s`, expected alert placement/behavior. |
| DPS v1.0 | `DPS-V10-C-008` | Candidate, UI oracle detail required. | Define the detailed layout/mapping oracle for the top-left attitude model and selected telemetry cells. |
| DPS v1.0 | `DPS-V10-C-002`, `DPS-V10-C-007` | Covered by `DPS-V10-I-001` and `DPS-V10-T-002`, respectively; optional separate sign-off only. | Retire as separate rows or keep optional constraint-specific sign-off definitions. |
| DPS v0.1 | `DPS-V01-A-001`, `DPS-V01-T-001`..`DPS-V01-T-006`, `DPS-V01-C-001`..`DPS-V01-C-007` | All rows in `DPS/MBSE/v0.1/tests/README.md` remain candidates if v0.1 closure is required. | Either defer historical v0.1 closure, or convert selected rows to detailed modeled definitions. |
| DPS v0.2 | Version-specific DPS v0.2 gates | No detailed `DPS/MBSE/v0.2/tests/README.md` found. | Create v0.2 test plan/definitions if v0.2 must be closed. |
| PDM v1.0 | `PDM-VV-PC-001`, `PDM-VV-PL-001` | Candidates; procedure definitions pending. | Model physical component/link inspection and retention/continuity procedures. |
| PDM v1.0 | `PDM-VV-CE-001`..`PDM-VV-CE-005` | Candidates; interface/API/signal/status/mechanical margin evidence pending. | Model CE analyses/tests for I2C, Pointers/Returns, PWM, status feedback, and torque margin. |
| PDM v1.0 | `PDM-VV-ALLOC-001`..`PDM-VV-ALLOC-003` | Candidates; allocation reviews pending. | Model function-to-LC and mechanical/function allocation analyses. |
| PDM v1.0 | `PDM-VV-FC-002` | Candidate; preparation scenario not represented as chain. | Model pre-launch fold/repack/place-cap/servo-close/retain scenario. |
| PDM v1.0 | `PDM-VV-FC-003` | Candidate; blocked by descent-speed requirement confirmation. | Confirm numeric terminal descent-speed limit and model drop/descent-speed verification. |
| PDM v1.0 | `PDM-VV-CON-001`..`PDM-VV-CON-007` | Candidates except coverage already embedded in `PDM-VV-FC-001`; each still needs detailed standalone definition if separate credit is desired. | Prioritize servo init/0-degree, no manual/BLE flight path, I2C timeout, process timing, no-blocking, parachute diameter, and angular-rate trigger robustness. |
| PDM v0.2 | `PDM-V02-INS-PC-PL-INVENTORY` | Candidate / coverage gap until executed. | Model or formally execute PC/PL inventory inspection. |
| PDM v0.2 | `PDM-V02-ANA-CE-INTENT` | Candidate / partially covered by BLE deployment evidence. | Model formal BLE/PWM CE intent analysis. |
| PDM v0.2 | `PDM-V02-ANA-LC-FUNC-ALLOC` | Candidate / coverage gap until formal allocation review. | Model formal allocation review. |
| PDM v0.2 | `PDM-V02-TEST-TERMINAL-SPEED` | Planned companion / gap if not executed with BLE deployment. | Decide if descent-speed measurement is inside BLE deployment run or companion activity; define oracle. |
| PDM v0.2 | `PDM-V02-ANA-CONSTRAINT-COVERAGE` | Candidate / covered in plan but not executed. | Model coverage analysis if separate closure evidence is needed. |
| PDM v0.1 | `PDM-V01-INSP-PC`, `PDM-V01-ALLOC-DSC` | Candidates, partially covered by `PDM-V01-FC-FALL`; standalone reports pending. | Decide whether standalone v0.1 inspection/allocation reports are required. |
| PDM v0.1 | `PDM-V01-GAP-PL`, `PDM-V01-GAP-CE` | Documented source-model gaps/N/A, not executable tests. | Leave as N/A/gap unless source v0.1 PL/CE views are added. |
| PDS & ESS | New candidate: regulator efficiency measurement. | Assessment flags README requirement for 95% efficiency not clearly verified. | Add efficiency campaign or update/retire requirement. |
| PDS & ESS | Most v1.0 rows are model-defined. | No broad planning-candidate backlog, but several definitions have source/model blockers listed below. | Resolve blockers before final acceptance credit. |
| OBCC | Original v1.0 candidates are mapped to gate definitions. | No remaining candidate-definition gap; the v0.x source-baseline absence is dispositioned under `OBCC-BLK-001`; execution/configuration caveats remain. | Keep target-context reporting caveats, identify actual as-tested code/configuration baselines, and close final readiness prerequisites. |
| S&A | All listed S&A activities are model-defined. | No remaining planning-candidate backlog; CE/allocation ownership gaps remain by design. | Execute `SAA-VV-CE-001`/`SAA-VV-ALLOC-001` ownership analyses and resolve holds. |

## 2. Open definition blockers

### 2.1 Cross-cutting and system-level blockers

| Blocker ID | Blocker | Blocks | Closure action |
|---|---|---|---|
| SYS-BLK-001 | Required system-level tests in §1.1 are not yet modeled. | Finished-CanSat claim and SSIV closure. | Create system-level MBSE test package and definitions. |
| SYS-BLK-002 | No requirement-to-test closure matrix exists across root README and subsystem READMEs. | CON-004 closure and final readiness review. | Build and maintain project requirement-to-test matrix. |
| SYS-BLK-003 | Closed — selected as-built hardware names for the affected configuration are frozen as `RFM96W` radio, `ICM20948` IMU, and `BME280` environmental sensor. | Validity of evidence and cross-subsystem traceability for the affected hardware. | Resolved; active BOM, docs, MBSE views, and source sketches use the selected names. ESS battery architecture is selected separately under closed `PDS-BLK-001` as `1S1P Li-Ion`. |
| SYS-BLK-004 | Partially resolved for ADS/AMS sensor freshness — the shared PM&SE sensor-to-OBCC freshness contract freezes ADS/AMS age/status semantics; broader canonical payload schema, units, DPS/OBCC field mapping, and schema versioning remain open. | End-to-end data, DPS dashboard/CSV, OBCC telemetry, ADS/AMS delivery. | Use `PM&SE/contracts/sensor_obcc_freshness_contract.md` for ADS/AMS freshness and publish the remaining controlled payload/interface schema for OBCC/DPS/system tests. |
| SYS-BLK-005 | Partially resolved for ADS/AMS freshness — ADS mission-window duration is selected as 10 min and ADS/AMS freshness max age is 400 ms; broader system cadence/frame rules and other subsystem timing tolerances remain to be harmonized. | ADS mission window, OBCC mission rehearsal, DPS concurrency/data-path tests. | Preserve the 10 min / 5 Hz / 400 ms ADS/AMS rule and define remaining project-level timing/tolerance policy before execution. |
| SYS-BLK-006 | Lab equipment availability, model IDs, calibration status, and analysis-tool versions are not unified. | Statistical/timing/accuracy/range evidence interpretation. | Build lab equipment/calibration matrix from assessment §7. |
| SYS-BLK-007 | Educational/documentation/workshop-readiness acceptance tests are not modeled. | Root README closure. | Create `SYS-WORKSHOP-READINESS` and documentation/BOM/rebuild checks. |

### 2.2 ADS blockers

| Blocker ID | Blocker | Blocks | Closure action |
|---|---|---|---|
| ADS-BLK-001 | Closed at definition level — v1.0 ADS-to-OBCC 5 Hz freshness semantics are selected by `ADS-V10-DATA-FRESHNESS` and the shared PM&SE sensor-to-OBCC contract. | No unresolved semantics blocker; ADS D2/model updates and execution evidence remain pending. | Extend/execute `ADS-IVV-FC-OBCC-DELIVERY`, `ADS-IVV-C-GETTER`, and `ADS-IVV-C-RATE-5HZ` using 5 Hz OBCC requests, 2 s LoRa packaging separation, `age_ms <=400 ms` only with `VALID`, and no stale/no-data/timeout/fault/init-fail data marked `VALID`. |
| ADS-BLK-002 | Closed at definition level — `ADS-IVV-C-ACCEL-3AXIS` defines linear acceleration units and quantitative static-accuracy criteria. | No unresolved acceleration criterion blocker; D2/model package and execution remain pending. | Model and execute `ADS-IVV-C-ACCEL-3AXIS` using `m/s²` / `g0` conversion, six-face gravity fixture, `n=59` strict samples, and selected guard-banded thresholds. |
| ADS-BLK-003 | Closed at definition level — `ADS-IVV-C-HEADING-NORTH` defines heading/north quantitative criteria. | No unresolved heading criterion blocker; D2/model package and execution remain pending. | Model and execute `ADS-IVV-C-HEADING-NORTH` with controlled true/magnetic north reference, disturbance controls, `n=59` strict samples, and `<=10°` guard-banded circular-error threshold. |
| ADS-BLK-004 | Closed at definition level — ADS mission-window duration is selected as 10 min / 600 s, with 3000 expected 5 Hz update opportunities and 400 ms maximum internal freshness gap. | `ADS-IVV-FC-MISSION-WINDOW` execution readiness criteria selected; D2/model follow-up and execution remain pending. | Execute/update `ADS-IVV-FC-MISSION-WINDOW` with the selected duration/count/gap criteria and preserve reset, stuck-loop, invalid/stale/corrupt, and field-presence rules. |
| ADS-BLK-005 | Closed at definition level — 5 Hz timing/freshness criteria are selected: 200 ms nominal period, 400 ms maximum gap/freshness age, `n=59` formal timing samples, sequence/timestamp/status evidence, and stale/drop/duplicate rules. | Rate/freshness execution remains pending. | Apply the selected criteria in `ADS-IVV-C-RATE-5HZ`, `ADS-V10-DATA-FRESHNESS`, and linked mission-window/GPS evidence. |
| ADS-BLK-006 | Closed at definition level — local Serial0 schema and parser baseline exist for v0.1/v0.2. | `ADS-IVV-FC-SERIAL` execution remains pending. | Use `ADS/MBSE/tests/schemas/ads_serial0_v0_1_v0_2.schema.json` and `ADS/MBSE/tests/tools/parse_ads_serial0.py`; reports shall identify firmware/log adapter and raw evidence. |
| ADS-BLK-007 | Closed at definition level — shared PM&SE freshness contract freezes age/status semantics; ADS-specific Pointers/Returns ownership/lifetime/API detail remains supplemental. | `ADS-IVV-FC-OBCC-DELIVERY` execution and optional ADS-specific supplement remain pending. | Reference `PM&SE/contracts/sensor_obcc_freshness_contract.md`; add ADS-specific field/API/watchdog details without redefining freshness/status. |
| ADS-BLK-008 | Closed/dispositioned — v0.2 I2C timeout is handled by a selected code-analysis/instrumentation branch or controlled gap/waiver, not by cluttering source MBSE diagrams. | Formal execution credit remains pending on source/instrumentation evidence. | Use `ADS-IVV-C-I2C-5MS` v0.2 branch with firmware source/build map or equivalent instrumentation; pass only if modeled I2C read paths return data or timeout/error in `<=5 ms`. |
| ADS-BLK-009 | Closed at definition level — no-blocking source/instrumentation, heartbeat, and overhead criteria are selected. | `ADS-IVV-C-NOBLOCK` execution remains pending. | Reports need firmware source/build map/symbols or equivalent instrumentation, 250 ms nominal heartbeat, 400 ms max progress/freshness gap, measured overhead `<=5%` of 200 ms or `<=5 ms`, and equipment/tool IDs. |
| ADS-BLK-010 | Closed at definition level — accuracy truth/reference methods and statistics are selected. | Accuracy execution remains pending with actual equipment IDs/calibration. | GPS strict pass uses GNSS simulator or surveyed/open-sky reference; phones are auxiliary/limited unless uncertainty-controlled. Gyro strict pass may use motor plus calibrated tachometer (`RPM × 6`, `n=59`, guard-banded `<30 deg/s`). |

### 2.3 AMS blocker dispositions (definition decisions closed)

| Blocker ID | Disposition | Blocks | Follow-up action |
|---|---|---|---|
| AMS-BLK-001 | Closed at definition level: temperature response-time `<=60 s` is a selected candidate/update path, not an undefined blocker. `AMS-V10-TEMP-RESPONSE-60S` or an explicitly equivalent modeled step-response activity is required. | No unresolved definition decision; AMS README response-time closure still needs modeled definition and execution evidence. | Model the response-time activity as a standalone test or clear `AMS-VV-FC-001` extension, then execute/report it before claiming closure. |
| AMS-BLK-002 | Closed at definition level by the shared PM&SE sensor-to-OBCC freshness contract. AMS uses `AMS-V10-DATA-FRESHNESS` or extensions of `AMS-VV-API-001`, `AMS-VV-FC-001`, `AMS-VV-FC-002`, `AMS-VV-CON-003`, and `AMS-VV-CON-004`; ADS uses `ADS-V10-DATA-FRESHNESS` or extensions of `ADS-IVV-FC-OBCC-DELIVERY`, `ADS-IVV-C-GETTER`, and `ADS-IVV-C-RATE-5HZ`; `SYS-END-TO-END-DATA` uses the same freshness/status/age rule. | No unresolved semantics blocker; ADS/AMS/system D2/model updates and execution evidence remain pending. | Apply the shared `5 Hz` request, `2 s` telemetry packaging, `<=400 ms` fresh age, six-status enum, timestamp/age evidence, and no-stale-valid rule in affected definitions and reports. |
| AMS-BLK-003 | Closed/dispositioned non-issue: AMS `v0.2` was PCB-ready delivery only, so no native `v0.2` logical, CE, allocation, or functional-chain closure is required beyond existing PCB/bring-up caveats. | No blocker unless a future controlled decision requires native `v0.2` source views. | Preserve PCB-only/reporting caveats; do not fabricate native `v0.2` behavior closure. |
| AMS-BLK-004 | Closed at definition level by the required API/non-blocking evidence checklist: 100% getter/OBCC collection-path inventory, explicit statuses, pointer ownership/lifetime/null policy, static callable-path review, dynamic timing/non-blocking traces, and dependency on `AMS-VV-CON-003` for I2C timeout evidence. | Execution credit for variable-getter and scheduler/no-blocking closure remains on hold until complete evidence exists. | Execute/update `AMS-VV-API-001`, `AMS-VV-CON-004`, and dependent FC/CON evidence with the full checklist; partial evidence is not a pass. |
| AMS-BLK-005 | Closed/dispositioned non-issue for AMS definition planning: provisional AMS trace IDs are acceptable pending system-level tests and source trace nodes. | No AMS-only trace blocker; system/source trace modeling and the final requirement-to-test matrix remain pending. | Model `SYS-*` tests, source mission/capability/use-case/feared-event trace elements, or a controlled provisional-label policy in later system work. |


#### 2.3.1 AMS §2.3 closure detail folded into this register

This subsection replaces the standalone `PM&SE/AMS_Blocker_Resolution_Plan_2026-07-02.md` and `PM&SE/AMS_Blocker_Closure_Record_2026-07-02.md` files. It is a definition-planning closure record only: no tests are executed here, no execution report is created, and no pass/fail credit is claimed. Later AMS, ADS, PM&SE, and model artifacts must still be updated/executed where the follow-up below says so.

**Folded execution status:** the AMS §2.3 blocker-resolution orchestration completed on 2026-07-02. The temporary AMS issue files were removed after validation. The shared ADS/AMS freshness contract, IVV reference, AMS test-documentation alignment, ADS/SYS freshness planning alignment, and PM&SE register/assessment updates are now represented in controlled repository files and commit history. Residual follow-up remains explicitly model/update/execution work, not an open AMS definition decision.

**Shared ADS/AMS sensor-to-OBCC freshness rule:** controlled by [`PM&SE/contracts/sensor_obcc_freshness_contract.md`](contracts/sensor_obcc_freshness_contract.md).

- ADS and AMS respond to OBCC collection requests at `5 Hz` internal cadence for parachute-control consumers.
- OBCC LoRa telemetry remains a separate `2 s` push cadence.
- At each `2 s` telemetry push, each required ADS/AMS sensor value shall either be fresh with age `<=400 ms` or explicitly non-valid.
- Freshness evidence shall include timestamp, sequence, age, or equivalent monotonic proof at the ADS/AMS-to-OBCC observation point.
- The external ADS/AMS-to-OBCC status enum is exactly `VALID`, `STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, `INIT_FAIL`.
- Only `VALID` may be consumed or reported as fresh data. Timeout, runtime sensor fault, startup init failure, or no-data conditions shall not leave old values marked `VALID`.
- Local implementation codes may exist, but test definitions and reports shall map them to the shared enum without losing low-level fault evidence.

##### Folded AMS candidate and update register

| Candidate / update ID | Type | Purpose | Selected definition baseline | Later implementation path |
|---|---|---|---|---|
| `AMS-V10-TEMP-RESPONSE-60S` | New AMS candidate test | Close the AMS temperature response-time requirement. | Apply a controlled temperature step to the AMS/BME280 environment and verify the reported temperature reaches the defined final/reference condition within `<=60 s`; retain raw timestamps, reference data, AMS data, exposure state, and uncertainty/deviation notes. | Prefer a standalone modeled activity if the response oracle needs its own D2 chain; otherwise extend `AMS-VV-FC-001` clearly and update the AMS test index. |
| `AMS-V10-DATA-FRESHNESS` | AMS candidate or existing-test extension | Close AMS-to-OBCC internal data freshness/rate planning. | Use the shared rule: `5 Hz` OBCC requests, `2 s` telemetry pushes, fresh age `<=400 ms` only when status is `VALID`, the six-status enum, and no old data marked valid after timeout/fault/init/no-data. | Prefer extending `AMS-VV-API-001`, `AMS-VV-FC-001`, `AMS-VV-FC-002`, `AMS-VV-CON-003`, and `AMS-VV-CON-004`; create a new folder only if the extensions become unclear. |
| `ADS-V10-DATA-FRESHNESS` | ADS alignment update | Align ADS v1.0 freshness/rate planning with the same ADS/AMS rule. | ADS uses the same `5 Hz` internal OBCC request/response freshness contract, `2 s` LoRa cadence separation, `<=400 ms` fresh age, six-status enum, timestamp/age evidence, and stale-valid prohibition. | Implement through existing ADS OBCC-delivery, getter/API, rate, mission-window, and no-blocking tests unless a standalone ADS activity becomes clearer. |
| `SYS-END-TO-END-DATA` freshness/status update | PM&SE system candidate update | Ensure end-to-end system data validation uses the same sensor freshness/status oracle from truth/reference stimulus to DPS CSV/dashboard. | Require canonical payload fields, units, timestamps, freshness age, shared six-status enum, no stale-valid behavior, and observability from ADS/AMS through OBCC LoRa to DPS storage/display. | Model this in the future system-level MBSE test package and final requirement-to-test matrix. |
| AMS API/non-blocking evidence checklist | Existing-test update, no new behavioral candidate | Make API/getter and scheduler/no-blocking closure auditable. | `AMS-VV-API-001` and `AMS-VV-CON-004` must together provide 100% getter/OBCC collection inventory, explicit status mapping, pointer ownership/lifetime/null policy, static callable-path review, dynamic timing/non-blocking traces, and `AMS-VV-CON-003` dependency. | Update AMS READMEs/D2 definitions and require complete execution evidence; partial evidence remains a hold. |
| AMS `v0.2` native logical/CE/allocation/FC closure | Not selected | Prevent over-scoping historical `v0.2` closure. | `v0.2` remains PCB delivery plus bring-up reachability only; no native logical/CE/allocation/FC closure is created. | Preserve caveat text in planning and reports; only add native views if a future controlled decision requires them. |
| AMS provisional trace-label closure | Not selected as AMS-only test | Avoid creating AMS-only trace work when the issue is system/source modeling. | AMS provisional trace IDs are acceptable until system tests and source trace elements are modeled. | Update system model and requirement-to-test matrix later. |

##### Folded existing-test update list

| Artifact / activity | Required update retained in this register |
|---|---|
| `AMS/MBSE/tests/README.md` | Add/reference `AMS-V10-TEMP-RESPONSE-60S`; record the preferred implementation path for `AMS-V10-DATA-FRESHNESS`; keep the `v0.2` PCB-only disposition and provisional trace-label caveat aligned. |
| `AMS-VV-API-001` | Include the shared six-status enum, age/timestamp evidence, stale-valid prohibition, 100% getter and OBCC collection-path inventory, pointer ownership/lifetime/null policy, and mapping from implementation return codes to `VALID`, `STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, `INIT_FAIL`. |
| `AMS-VV-FC-001` | Add freshness/currentness criteria for atmospheric measurement collection; valid fresh values have age `<=400 ms`, non-valid values carry the shared status, and stale data is not accepted as current. Reference or incorporate the temperature response-time activity. |
| `AMS-VV-FC-002` | Align BME280 init-state and startup-fault evidence with `INIT_FAIL` and the stale-valid prohibition; prevent default/previous boot OK values from being treated as current valid status. |
| `AMS-VV-CON-003` | Map environmental I2C timeout/fault outcomes to the shared contract for external OBCC-facing status while retaining low-level evidence; timed-out or faulted reads must not return old data as `VALID`. |
| `AMS-VV-CON-004` | Add static callable-path review, dynamic non-blocking/timing traces, bounded error/status propagation, and explicit dependency on `AMS-VV-CON-003` for I2C wait timing/recovery. |
| `AMS-VV-CON-001` | Keep sunlight/airflow exposure evidence available as context for temperature accuracy and response-time interpretation, without claiming response-time closure unless the response oracle is present. |
| ADS OBCC-delivery / getter / rate / mission-window / no-blocking tests | Reference the shared ADS/AMS freshness rule, status enum, timestamp/age evidence, pointer/return policy where applicable, watchdog/timeout behavior, `5 Hz` internal delivery separated from `2 s` LoRa telemetry, and no stale-valid behavior. |
| `SYS-END-TO-END-DATA` | Add canonical payload, units, timestamps, freshness age, shared six-status enum, no stale-valid behavior, and observability from ADS/AMS through OBCC to DPS CSV/dashboard. |

##### Folded follow-on D2/model and execution work

The following work is intentionally not closed by this register update:

1. Create or update AMS D2 test-definition views for `AMS-V10-TEMP-RESPONSE-60S`, then regenerate matching PNGs.
2. Update AMS API/FC/CON D2 definition views to include the shared freshness/status contract, age/timestamp evidence, stale-valid prohibition, and evidence checklist items.
3. Complete ADS D2/test-definition updates for OBCC delivery, getter/API, rate/freshness, mission-window, and no-blocking alignment where old v1.0 N/A rate rationale remains.
4. Model the system-level `SYS-END-TO-END-DATA` package with payload, timestamp, freshness/status, and DPS CSV/dashboard observability criteria.
5. Add source model trace elements for missions, capabilities, use cases, and feared events, or approve a controlled provisional-label policy until those elements exist.
6. Do not create native AMS `v0.2` logical, CE, allocation, or FC source views unless a later controlled decision changes the PCB-only delivery disposition.
7. Execute the selected tests and archive reports before claiming pass/fail credit.

##### Folded residual execution-only uncertainties

- Exact temperature step method, final-value/settling definition, sample count, thermal fixture or chamber model, and response-time analysis script.
- Exact ADS/AMS API/header names, field names, status-code mapping, timestamp source, clock synchronization or monotonic-age method, and sequence/age encoding.
- OBCC harness/logging implementation, telemetry payload schema version, and DPS CSV/dashboard field mapping for system end-to-end evidence.
- UUT serial numbers, hardware revisions, firmware commits, source/build maps, symbols, instrumentation hooks, and instrumentation overhead.
- Actual equipment asset IDs, calibration certificates or function checks, tool versions, environmental limits, and lab configuration.
- Whether AMS freshness and temperature response are implemented as standalone folders or extensions to existing AMS activities; choose the path that keeps the modeled definition clearest.
- How and when system/source trace nodes will be modeled versus retaining provisional trace labels under controlled rationale.

### 2.4 DPS blockers

| Blocker ID | Blocker | Blocks | Closure action |
|---|---|---|---|
| DPS-BLK-001 | Multiple DPS v1.0 rows remain planning candidates (`T-004`, `T-005`, `T-006`, `C-001`, `C-003`, `C-004`, `C-005`, `C-006`, `C-008`). | DPS v1.0 definition completeness. | Convert candidate rows to detailed modeled definitions. |
| DPS-BLK-002 | Closed — obsolete RH dashboard/payload field removed from the OBCC frame table and DPS dashboard model/test baselines. | Dashboard/CSV/payload closure. | Resolved; no placeholder was added and the OBCC payload was not expanded. |
| DPS-BLK-003 | Closed — dashboard top-left attitude model selected and README/model/tests aligned. | `DPS-V10-T-005` / `DPS-V10-C-008`. | Resolved; detailed UI oracle work remains under `DPS-BLK-001` / `DPS-BLK-006`. |
| DPS-BLK-004 | PV2 CE-03 UART direction is Forwarder -> Decoder, but command/uplink uses Decoder -> Forwarder. | `DPS-V10-T-002` unqualified pass and CE analysis. | Update model to bidirectional CE or approve waiver/disposition. |
| DPS-BLK-005 | RF/range/PDR conditions are not fixed: range site/RF-equivalent setup, legal settings, antennas, PDR threshold, independence/statistics. | `DPS-V10-C-001`, `SYS-RF-RANGE-PDR`. | Define RF campaign and exact-binomial acceptance method. |
| DPS-BLK-006 | UI/browser/CSV/latency test oracles are missing. | `DPS-V10-T-005`, `C-004`, `C-005`, `C-006`, `C-008`. | Define browser set, UI automation/oracle, filesystem/checksum oracle, latency timestamp oracle. |
| DPS-BLK-007 | Concurrency load and mission-duration stress profile are not defined. | `DPS-V10-C-003`. | Define frame rate/duration, queues, memory, backlog, p95 latency acceptance. |
| DPS-BLK-008 | Earlier delivery versions are not detailed consistently. | DPS v0.1/v0.2 closure if needed. | Either defer historical gates or add v0.1/v0.2 detailed definitions. |
| DPS-BLK-009 | Formal mission/capability/use-case/feared-event trace elements are absent. | Controlled traceability. | Confirm provisional trace labels or add trace model elements. |

DPS-BLK-003 closure note: the selected top-left dashboard model renders CanSat attitude from pitch/roll/yaw.
Altitude remains a two-dimensional telemetry plot/value in DPS dashboard artifacts.

### 2.5 OBCC blockers

| Blocker ID | Blocker | Blocks | Closure action |
|---|---|---|---|
| OBCC-BLK-001 | Closed — dispositioned as a lifecycle/modeling non-issue: OBCC versions may jump from `v0.x` to `v1.0`; OBCC is mostly software-dependent and was not complex enough to require incremental source-model deliveries; no v0.x source baselines will be fabricated. | No blocker; historical gates remain target-context-only unless execution reports bind them to actual code/configuration baselines. | Resolved; preserve target-context caveats and require reports to identify actual code/configuration baselines and acknowledge target-context-only model references where applicable. |
| OBCC-BLK-002 | Final readiness pass requires mission rehearsal closure. | `OBCC-V10-FLIGHT-001` final PASS. | Execute/disposition `OBCC-V09-GATE-001` before final readiness board. |
| OBCC-BLK-003 | Payload schema, command schema, radio settings, firmware/configuration IDs, and any as-tested configuration identifiers beyond the selected `RFM96W`/`ICM20948`/`BME280` names are not frozen. | Telemetry/command/RF evidence validity. | Freeze as-tested configuration before execution. |
| OBCC-BLK-004 | Emergency-deploy policy, descent-state observability criteria, safe/error-state behavior, and actuator status semantics need confirmation. | Runtime fault handling, mission rehearsal, deployment safety. | Define cross-subsystem policy with PDM/ADS/PM&SE and update affected tests. |
| OBCC-BLK-005 | Telemetry cadence tolerance, range/PDR evidence, payload-schema traceability, and RF settings/evidence details require disposition; RF module naming is selected as `RFM96W`. | OBCC telemetry/range gate and DPS alignment. | Confirm cadence tolerance, final frame schema, radio settings/configuration, and range/PDR plan. |
| OBCC-BLK-006 | Runtime fault telemetry-gap bound (`<=4 s`) and trace/stress load profile/tool IDs require confirmation. | `OBCC-V06-GATE-001` timing/fault-hardening claims. | Confirm or tailor degradation allowance and record trace/stress tools/load profiles. |

### 2.6 PDS & ESS blockers

| Blocker ID | Blocker | Blocks | Closure action |
|---|---|---|---|
| PDS-BLK-001 | Closed — final ESS battery architecture is frozen as `1S1P Li-Ion`; README, BOM, MBSE, and tests now align on the selected single-cell pack architecture. | No longer blocks on battery-architecture conflict; PDS/ESS and system power acceptance still depend on the remaining non-battery PDS blockers. | Resolved; preserve `1S1P Li-Ion` in execution reports and do not claim final power acceptance until the other PDS blockers are closed. |
| PDS-BLK-002 | INA219 I2C CE is implied but missing from source logical view. | Final CE completeness, `PDS-VV-FC-002`, `PDS-VV-CON-007`. | Update source model or approve controlled justification/waiver. |
| PDS-BLK-003 | 95% regulator efficiency requirement is not clearly verified. | PDS regulated-rail requirement closure. | Add efficiency measurement campaign or update requirement. |
| PDS-BLK-004 | On-mode load/current budget and 6h endurance profile remain campaign-defined. | `PDS-VV-CON-002`, system power/endurance. | Freeze representative load profile, logging cadence, thermal envelope. |
| PDS-BLK-005 | Master switch/accessibility hardware detail is not explicit in the physical source model. | Allocation/external actor safe power-off closure. | Update source model/interface definition or approve waiver path. |
| PDS-BLK-006 | Li-ion safety documents, charger model/certification, and cell safety evidence are prerequisites. | Final powered charge acceptance. | Collect datasheet/SDS/UN38.3/limits and certified charger evidence. |
| PDS-BLK-007 | Carvera Air DFM rule-set closure and deviation records are required. | `PDS-VV-CON-009` pass. | Record trace/space/drill/annular/isolation/milling/thickness/keepout rules and dispositions. |
| PDS-BLK-008 | Protection probability setpoints, independence rationale, and demand-trial evidence are not fixed; source meaning of `<1%` remains ambiguous. | `PDS-VV-CON-003` formal claim. | Confirm conservative missed-demand interpretation or revise requirement; define setpoints/sample plan. |
| PDS-BLK-009 | Rail-test nominal load, thermal, and settling parameters require campaign confirmation. | `PDS-VV-CON-004`. | Define no-load/nominal/1 A cases, thermal limits, settling/ripple treatment. |

### 2.7 PDM blockers

| Blocker ID | Blocker | Blocks | Closure action |
|---|---|---|---|
| PDM-BLK-001 | Most PDM v1.0 rows remain planning candidates except `PDM-VV-FC-001`. | PDM v1.0 definition completeness. | Model candidate rows in §1.2 before execution credit. |
| PDM-BLK-002 | v1.0 terminal descent-speed numeric requirement is not explicit. | `PDM-VV-FC-003`, terminal-speed closure, system deployment safety. | Confirm limit, e.g. historical `11 m/s max` or updated CanSat guidance value, and add source constraint/test. |
| PDM-BLK-003 | Emergency-deploy/lost-observability policy is not explicit. | No-blocking/fault logic and OBCC/PDM deployment safety. | Define policy ownership, triggers, inhibit conditions, safe/error behavior. |
| PDM-BLK-004 | Servo status semantics for Trigger -> PDM Processing need confirmation. | `PDM-VV-CE-004`, no-false-success deployment closure. | Define feedback/status oracle for success/failure/jam/no-open. |
| PDM-BLK-005 | `PDM-VV-FC-001` still needs final UUT ID, hardware revision, firmware build, IMU stimulus/replay set, environmental limits, equipment IDs, and statistical claim type. | Execution readiness of the only modeled v1.0 PDM definition. | Freeze as-tested configuration and predeclare stimulus/statistical method. |
| PDM-BLK-006 | v0.2 BLE deployment power validity thresholds and terminal-speed evidence linkage are unresolved. | v0.2 BLE/manual deployment closure. | Define PDS/battery/boost/servo voltage/current thresholds and whether terminal-speed is in-run or companion evidence. |
| PDM-BLK-007 | v0.1 fall-test mass estimate/tolerance and measurement method must be fixed for execution. | v0.1 fall-test interpretation. | Record final mass estimate/tolerance, video/time-distance calibration, wind/environment acceptance. |

### 2.8 S&A blockers

| Blocker ID | Blocker | Blocks | Closure action |
|---|---|---|---|
| SAA-BLK-001 | Baseline S&A has no component exchanges; backplane rails/pin interfaces/testpoints/SPI/I2C/UART are implied only. | S&A CE closure. | Execute `SAA-VV-CE-001`; cross-reference subsystem CE models or update S&A model. |
| SAA-BLK-002 | Baseline S&A has no logical components/functions/allocations. | S&A allocation/ownership closure. | Execute `SAA-VV-ALLOC-001`; assign owner/disposition for every integration function. |
| SAA-BLK-003 | Drop/vibration/landing/environmental screen levels, surfaces, axes/orientations, durations, and success criteria are not approved. | `SAA-VV-CON-001`, `SAA-VV-CON-005`, system environmental regression. | Approve tailored environmental screen plan and post-screen checks. |
| SAA-BLK-004 | Envelope/mass authority needs confirmation: `122 mm` height vs stricter references; `<350 ±0.1 g` interpretation. | Envelope/mass acceptance. | Confirm final height and mass acceptance policy before measurement credit. |
| SAA-BLK-005 | Backplane pinout, loads, I2C mode/capacitance/rise-time targets, IPC/DFM class are not frozen. | Backplane, rail, and fast-line tests. | Freeze pinout/load/signal-integrity/DFM criteria and update evidence matrices. |
| SAA-BLK-006 | Print material/profile, screw torque, proof-load/pull values are not source-defined. | Assembly/printing and retention closure. | Define work instructions or record controlled rationale/waiver. |
| SAA-BLK-007 | Movement thresholds for battery, PCB, backplane, and connector retention screens are assumed but not released. | `SAA-VV-CON-005` pass. | Release movement/witness-mark thresholds; absent thresholds cause hold/fail on visible movement. |
