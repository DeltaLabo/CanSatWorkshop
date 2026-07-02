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
| DPS v1.0 | `DPS-V10-T-005` | Candidate; selected UI/CSV/latency/layout oracle exists, detailed definition required. | Define dashboard visualization using `DPS/MBSE/tests/DPS-V10_UI_CSV_Latency_Oracles.md`: payload-to-plot mapping, browser evidence, latency alert, stale/invalid-field behavior. |
| DPS v1.0 | `DPS-V10-T-006` | Candidate, fault-injection detail required. | Define forwarder restart campaign, SPI/radio/UART missing-fault injections, false-ready oracle. |
| DPS v1.0 | `DPS-V10-C-001` | Candidate; selected RF/range/PDR baseline exists, detailed definition required. | Define 500 m horizontal LOS or RF-equivalent setup, selected radio/antenna settings, `N=300`, `k>=279`, RSSI/SNR logging, legal/site prerequisites using `DPS/MBSE/tests/DPS-V10_RF_Range_Concurrency_Parameters.md`. |
| DPS v1.0 | `DPS-V10-C-003` | Candidate; selected concurrency/load baseline exists, detailed definition required. | Define 10 min flight-cadence run and optional 20 min 5 Hz synthetic/serial stress with bounded queue/memory/backlog and p95 latency criteria using `DPS/MBSE/tests/DPS-V10_RF_Range_Concurrency_Parameters.md`. |
| DPS v1.0 | `DPS-V10-C-004` | Candidate; browser/evidence policy selected, detailed definition and implementation evidence required. | Apply selected primary Chrome/Chromium strict-credit policy; current Tkinter-only implementation remains HOLD/limited for browser credit until a browser entry point exists. |
| DPS v1.0 | `DPS-V10-C-005` | Candidate; selected CSV/session oracle exists, detailed definition required. | Define session/restart cases, no-overwrite filename uniqueness oracle, monotonic rows, overwrite/checksum/content checks using `DPS/MBSE/tests/DPS-V10_UI_CSV_Latency_Oracles.md`. |
| DPS v1.0 | `DPS-V10-C-006` | Candidate; selected latency threshold oracle exists, detailed definition required. | Define monotonic timestamp source, boundary cases around `1.0 s`, top-alert behavior for `>1.0 s`, no-alert for `<=1.0 s`, and invalid timestamp handling. |
| DPS v1.0 | `DPS-V10-C-008` | Candidate; selected UI layout oracle exists, detailed definition required. | Define detailed `4x4` layout/mapping using the selected top-left attitude model and selected v1.0 telemetry cells from `DPS/MBSE/tests/DPS-V10_UI_CSV_Latency_Oracles.md`. |
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
| PDS & ESS | New candidate: `PDS-VV-CON-010` regulator-efficiency validation for the README 3.3 V and 5 V rail requirements at `1 A` / `95%` efficiency. | Candidate queued at definition-planning level; detailed modeled definition and execution remain pending, and no test has been executed. | Promote/model `PDS-VV-CON-010` only after measurement topology, instrumentation, load cases, uncertainty/guard-band treatment, thermal limits, and evidence paths are defined. |
| PDS & ESS | Most other v1.0 rows are model-defined. | No broad planning-candidate backlog; remaining items are source-model/interface follow-ons or campaign/execution prerequisites listed in §2.6. | Keep final acceptance and execution credit pending until source follow-ons, campaign parameters, and evidence are closed. |
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

#### 2.2.1 ADS §2.2 closure detail folded into this register

This subsection replaces the former standalone ADS blocker closure record. It is a definition-planning closure record only: no tests are executed here, no execution report is created, and no pass/fail credit is claimed. Later ADS, AMS, PM&SE, and model artifacts must still be updated/executed where the follow-up below says so.

**Folded execution status:** the ADS §2.2 blocker-resolution orchestration completed at definition-planning level on 2026-07-02. Temporary ADS issue files were removed after validation. The shared ADS/AMS freshness contract, Serial0 schema/parser baseline, ADS freshness alignment, acceleration/heading candidates, timing/no-blocking updates, and PM&SE register/assessment updates are now represented in controlled repository files and commit history. Residual follow-up remains explicitly D2/model/update/execution work, not an open ADS definition decision.

**ADS shared sensor-to-OBCC freshness rule:** controlled by [`PM&SE/contracts/sensor_obcc_freshness_contract.md`](contracts/sensor_obcc_freshness_contract.md).

- ADS v1.0 uses `ADS-V10-DATA-FRESHNESS` as the candidate/alias implemented by explicit extensions of `ADS-IVV-FC-OBCC-DELIVERY`, `ADS-IVV-C-GETTER`, and `ADS-IVV-C-RATE-5HZ`; no new standalone ADS folder is required unless those extensions become unclear.
- ADS shall make update records/slots available to OBCC at `5 Hz` (`200 ms` nominal) for the 10 min mission window.
- OBCC LoRa telemetry remains a separate `2 s` push cadence; it may carry the latest ADS record plus age/status metadata, but it is not the internal `5 Hz` evidence.
- Fresh ADS data requires `status == VALID`, required fields finite/in range, and `age_ms <= 400 ms`.
- The external ADS/AMS-to-OBCC status enum is exactly `VALID`, `STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, `INIT_FAIL`.
- `STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, and `INIT_FAIL` conditions shall not leave old ADS data marked `VALID`; old values may be carried only as non-`VALID` with age/status evidence.
- ADS `Pointers`/`Returns` ownership, lifetime, API names, return-code mapping, and watchdog implementation remain ADS-specific supplemental detail and shall reference the shared PM&SE contract.
- `SYS-END-TO-END-DATA` shall use the same shared freshness rule as the sensor freshness oracle for ADS/AMS age/status fields and stale/error behavior.

##### Folded ADS candidate and update register

| Candidate / update ID | Type | Purpose | Selected definition baseline | Later implementation path |
|---|---|---|---|---|
| `ADS-V10-DATA-FRESHNESS` | ADS alignment update / alias through existing tests | Close v1.0 ADS-to-OBCC internal delivery-rate/freshness. | ADS shall provide a `5 Hz` internal OBCC request/response path for the 10 min mission window using the shared PM&SE contract: `2 s` LoRa telemetry remains separate, fresh age is `<=400 ms` only with `VALID`, the exact six-status enum is used, and stale/no-data/timeout/fault/init-fail values are not marked `VALID`. | Implement through `ADS-IVV-FC-OBCC-DELIVERY`, `ADS-IVV-C-GETTER`, `ADS-IVV-C-RATE-5HZ`, mission-window, and no-blocking tests unless a standalone activity becomes clearer. D2/model follow-up remains where old v1.0 N/A rationale remains. |
| `ADS-IVV-C-ACCEL-3AXIS` | New README-only ADS candidate test | Close acceleration quantity, units, sign, and static accuracy. | Use `m/s²` as the comparison unit, convert raw `g` with `g0 = 9.80665 m/s²`, reject `deg/s²` as an acceleration oracle, use a six-face static gravity fixture, and require `n = 59` all-within-limit samples per face for strict claims with the selected guard-banded thresholds. | Model the candidate in D2 later and execute with UUT/firmware/equipment IDs, uncertainty guard band, axis/sign convention, and retained raw logs. |
| `ADS-IVV-C-HEADING-NORTH` | New README-only ADS candidate test | Close north/heading quantitative acceptance. | Use a non-magnetic fixture/site and a surveyed true-north line or calibrated magnetic reference with declination correction; test stable headings near 0°, 90°, 180°, and 270° with `n = 59` all-within-limit samples per heading for strict claims; require circular heading error plus expanded uncertainty `<=10°`. | Model the candidate in D2 later or explicitly fold it into `ADS-IVV-FC-ATT`; execution must include calibration state, local disturbance survey, timestamp correlation, and invalid/disturbed marker handling. |
| Serial0 schema/parser baseline | Definition artifact for existing test | Close the v0.1/v0.2 Serial0 schema/parser blocker. | Use `ADS/MBSE/tests/schemas/ads_serial0_v0_1_v0_2.schema.json` and `ADS/MBSE/tests/tools/parse_ads_serial0.py` as the controlled local baseline; reports must identify firmware/log adapter and retain raw evidence. | Keep as an artifact for `ADS-IVV-FC-SERIAL`; no additional mission-behavior candidate is selected solely for the parser. |
| ADS-specific `Pointers`/`Returns` supplement | Optional definition artifact | Preserve ADS API/ownership/watchdog detail without redefining freshness. | Any ADS-specific field schema, pointer ownership/lifetime, return/error-code mapping, and watchdog implementation shall reference the shared PM&SE freshness/status contract. | Create only if needed for execution clarity; do not create a contradictory ADS-only freshness rule. |

##### Folded existing ADS test update list

| Artifact / activity | Required update/status retained in this register |
|---|---|
| `ADS-IVV-C-RATE-5HZ` | Use the `ADS-V10-DATA-FRESHNESS` branch for v1.0. Retain `200 ms` nominal period, `3000` expected internal update opportunities over 10 min, jitter/sample rule, worst-gap rule, stale/drop/duplicate criteria, contract age/status evidence, no stale/no-data/timeout/fault/init-fail data marked `VALID`, and instrumentation-overhead handling. Keep `2 s` LoRa telemetry separate from internal `5 Hz` evidence. |
| `ADS-IVV-FC-MISSION-WINDOW` | Use the 10 min mission window, 3000 expected internal update opportunities at 5 Hz, mandatory field/marker presence, no reset/brownout/stuck-loop acceptance, no unrecovered peripheral failure, invalid/stale/corrupt marker handling, and maximum ADS internal delivery gap `<=400 ms`. |
| `ADS-IVV-FC-SERIAL` | Reference the controlled Serial0 schema/parser/campaign baseline for v0.1/v0.2: port/baud/framing, fields, units, validity/stale/error markers, parser version, expected count/campaign duration, and raw-byte retention. Keep v0.3/v1.0 N/A rationale. |
| `ADS-IVV-FC-OBCC-DELIVERY` | Reference the shared PM&SE freshness contract for `5 Hz` delivery/freshness, `<=400 ms` age, exact six-status enum, telemetry age/status, and no-old-data-as-`VALID` behavior after stale/no-data/timeout/fault/init-fail conditions. Add ADS-specific watchdog thresholds, pointer ownership/lifetime, return/error-code mapping, and null/dangling/stale/corrupt/slow-call fault cases as needed. |
| `ADS-IVV-C-GETTER` | Map ADS getter/process/collector validity and return/error semantics to the shared PM&SE enum or a controlled one-to-one evidence mapping; require timestamp/sequence/age evidence at the ADS-to-OBCC observation point; prove stale/no-data/timeout/fault/init-fail paths do not leave old data marked `VALID`. |
| `ADS-IVV-C-I2C-5MS` | Treat v0.2 as a selected code-analysis/instrumentation or documented-gap path, not an unresolved model gap that requires cluttered v0.2 source D2 changes. Preserve the v1.0 formal `<=5 ms` I2C timeout baseline. |
| `ADS-IVV-C-NOBLOCK` | Require source/build map/symbols or equivalent instrumentation; heartbeat/progress deadline `<=400 ms`; measured instrumentation-overhead allowance; and explicit blocked/limited status if source/instrumentation access is absent. |
| `ADS-IVV-C-POS-5M` | Use strict GPS truth policy: GNSS simulator or surveyed/open-sky reference with uncertainty guard band. Consumer phones are auxiliary/limited unless their uncertainty is independently controlled and guard-banded. Preserve matched valid sample and invalid/no-fix/stale handling. |
| `ADS-IVV-C-GYRO-30DPS` | Use motor plus calibrated tachometer as an approved angular-rate truth path. Require tachometer reliability/calibration, motor stability, `deg/s = RPM × 6`, axis alignment, time correlation, uncertainty guard band, and `n = 59` all-within-limit evidence for strict claims. |
| `ADS-IVV-FC-ATT` | Reference the acceleration and heading candidates for quantitative claims; otherwise current attitude evidence remains plausibility/repeatability only. |
| `ADS-IVV-FC-GPS` | Align v1.0 delivery/rate notes with the selected ADS-to-OBCC `5 Hz` decision and strict GPS truth policy. |
| `ADS-IVV-FC-ANG` | Align angular-rate truth/reference assumptions with the motor/tachometer method and strict-statistics rule. |
| `ADS-IVV-C-PROC-5MS` / `ADS-IVV-C-UART-5MS` | Align instrumentation overhead and `n = 59` zero-violation deadline wording with no-blocking and timing decisions. |

##### Folded selected ADS quantitative criteria

- ADS mission-window duration is **10 min = 600 s**; expected internal ADS update opportunities at **5 Hz** are **3000** per mission window.
- Mission-window timing starts after the declared ADS ready/start marker. Any reset, brownout, stuck loop, unrecovered peripheral failure, unreported logger loss, or unmodeled bypass invalidates a strict mission-window pass.
- Nominal internal ADS update period is **200 ms**. Strict rate/freshness pass requires at least 3000 scheduled slots/events over 600 s, observed mean delivery rate `>=5.0 Hz`, no silent missing slot, no duplicate/catch-up burst compensating for a missed slot, no update gap `>400 ms`, timestamp/sequence/freshness evidence, and stale/error data explicitly marked non-fresh.
- Formal jitter/deadline timing samples use **`n = 59` representative consecutive intervals** with every interval **150 ms to 250 ms** inclusive for the selected claim.
- Linear acceleration units are **`m/s²`**. If firmware/logs use `g`, convert with **`g0 = 9.80665 m/s²`** before comparison. `deg/s²` is not an acceleration oracle.
- Strict static acceleration claim uses a six-face fixture with **`n = 59` all-within-limit samples per face**, correct axis/sign convention, driven-axis error plus expanded uncertainty **`<=1.0 m/s²`**, off-axis leakage plus uncertainty **`<=0.75 m/s²`**, and vector-norm error plus uncertainty **`<=1.0 m/s²`**.
- Quantitative heading claim requires circular heading error plus expanded uncertainty **`<=10°`** at headings near **0°, 90°, 180°, and 270°** with **`n = 59` all-within-limit samples per heading** for strict claims.
- Strict GPS `<5 m` pass requires a GNSS simulator or surveyed/open-sky reference point/reference antenna setup with coordinate uncertainty small relative to 5 m; phone-only truth is limited/characterization unless uncertainty-controlled and guard-banded.
- Motors plus tachometer are approved for angular-rate truth when tachometer calibration/reliability and motor stability are adequate. Convert speed with **`deg/s = RPM × 6`**; strict angular-rate claims use **`n = 59`** matched samples per axis/rate and require every guard-banded absolute error **`<30 deg/s`**.
- Runtime progress heartbeat for `Loop` / `ADS Processing` shall be observable under nominal and fault cases with no progress gap greater than **400 ms**.
- Formal timeout/deadline claims use **`n = 59` zero-violation samples** unless a stricter project rule is later selected.
- Timing hooks/logging overhead shall be measured before verdicts and shall be `<=5%` of the 200 ms period or `<=5 ms`, whichever is stricter for the claim being made; otherwise the timing verdict is limited/blocked or the overhead is subtracted/bounded with documented uncertainty.

##### Folded ADS contradictions resolved

| Contradiction or TBD | Selected resolution |
|---|---|
| ADS README requires v1.0 internal delivery to OBCC at least 5 Hz, while `ADS-IVV-C-RATE-5HZ` treated v1.0 as N/A. | v1.0 internal ADS-to-OBCC 5 Hz is required; LoRa 2 s cadence is separate. |
| ADS README acceleration unit said `deg/s²`, while acceleration is linear. | Use `m/s²` or converted `g`; do not use `deg/s²` as the acceleration oracle. |
| `ADS-IVV-FC-ATT` forbids formal numerical attitude accuracy unless a new constraint exists. | Keep attitude plausibility unless a heading/north constraint candidate is added or explicitly folded in. |
| Mission duration, maximum gap, and jitter tolerance were TBD. | Use 10 min, 3000 expected updates, 200 ms nominal, 150-250 ms formal jitter sample, and 400 ms maximum gap/watchdog threshold. |
| v0.2 I2C timeout was a model gap. | Resolve by code-analysis/instrumentation or controlled gap text; do not force cluttered v0.2 source diagrams. |
| GPS truth equipment and phone use were ambiguous. | Use surveyed/open-sky or simulator truth for strict `<5 m`; phones are auxiliary unless uncertainty-controlled. |
| Angular-rate truth fixture was assumed but not fixed. | Motors plus calibrated tachometer are approved with `n=59` all-within-limit strict evidence if reliable/calibrated. |

##### Folded follow-on ADS D2/model and artifact work

The following work is intentionally not closed by this register update:

1. Update `ADS-IVV-C-RATE-5HZ` D2/model definition views so v1.0 is no longer shown only as N/A for internal ADS-to-OBCC `5 Hz` delivery/freshness; Markdown READMEs and the ADS index already document the `ADS-V10-DATA-FRESHNESS` path.
2. Update `ADS-IVV-FC-MISSION-WINDOW` D2/model views to show the 10 min mission, 3000 expected update slots, strict reset/stuck-loop/freshness rules, and 400 ms maximum gap; Markdown READMEs already contain the criteria.
3. Create any ADS-specific `Pointers`/`Returns` supplement for field/schema, ownership/lifetime, return-code mapping, and watchdog implementation if needed; it shall reference the shared PM&SE freshness/status contract rather than redefining freshness.
4. Model the README-only `ADS-IVV-C-ACCEL-3AXIS` and `ADS-IVV-C-HEADING-NORTH` candidates in D2, or explicitly fold them into existing attitude-related packages, then regenerate matching PNGs.
5. Preserve the `ADS-IVV-C-I2C-5MS` v0.2 code-analysis/instrumentation or controlled-gap path; do not add cluttered v0.2 source-model diagrams solely to satisfy this closure.
6. Complete D2/model follow-up for related `ADS-IVV-C-POS-5M`, `ADS-IVV-C-GYRO-30DPS`, `ADS-IVV-FC-GPS`, `ADS-IVV-FC-ANG`, and `ADS-IVV-FC-ATT` views where the selected truth/reference/statistics decisions are not yet represented.
7. Execute the selected tests and archive reports before claiming pass/fail credit.

##### Folded residual ADS execution-only uncertainties

- Exact ADS/OBCC `Pointers`/`Returns` field schema, header/API names, ownership/lifetime details, watchdog implementation, and OBCC log harness; freshness/status semantics are controlled by the shared PM&SE contract.
- UUT serial numbers, hardware revisions, firmware commits, build maps/symbols, instrumentation hook names, parser/log adapter revision, and raw evidence locations.
- Actual equipment asset IDs, calibration certificates/function checks, tool versions, environmental limits, power/ambient readings, and lab configuration.
- Surveyed GPS coordinates or simulator scenario, tachometer calibration/reliability, motor stability, heading-reference calibration, and acceleration fixture alignment.
- Whether acceleration and heading/north D2 packages remain standalone or are folded into existing attitude-related packages.

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
| DPS-BLK-001 | Closed at definition-decision level — the complete active v1.0 candidate backlog is registered (`T-004`, `T-005`, `T-006`, `C-001`, `C-003`, `C-004`, `C-005`, `C-006`, `C-008`) and optional `C-002`/`C-007` remain covered/optional. | No open undefined DPS decision for candidate inventory; detailed modeled definitions and execution still block credit. | Create detailed Capella/D2 definitions and reports before claiming execution credit. |
| DPS-BLK-002 | Closed — obsolete RH dashboard/payload field removed from the OBCC frame table and DPS dashboard model/test baselines. | Dashboard/CSV/payload closure. | Resolved; no placeholder was added and the OBCC payload was not expanded. |
| DPS-BLK-003 | Closed — dashboard top-left attitude model selected and README/model/tests aligned. | `DPS-V10-T-005` / `DPS-V10-C-008`. | Resolved; selected UI/layout oracle now supports detailed-definition follow-up. |
| DPS-BLK-004 | Closed at definition-decision level — ground-station UART model intent is selected as bidirectional, represented later either by one bidirectional CE or paired telemetry/command UART CEs; current PV2/D2 source update remains pending. | Unconditional `DPS-V10-A-001` CE-03 and `DPS-V10-T-002` command/uplink pass credit remains on hold pending source-model update/waiver and byte-direction evidence. | Update PV2/D2 source model or approve waiver; reports shall include Forwarder→Decoder telemetry and Decoder→Forwarder command evidence. |
| DPS-BLK-005 | Closed at definition-decision level — RF/range/PDR baseline is selected in [`DPS-V10_RF_Range_Concurrency_Parameters.md`](../DPS/MBSE/tests/DPS-V10_RF_Range_Concurrency_Parameters.md): 500 m horizontal LOS, 915 MHz, matching 22 AWG 81.4 mm antennas, legal/EIRP/site control, RSSI/SNR logs, `N=300`, `k>=279`. | `DPS-V10-C-001`, `SYS-RF-RANGE-PDR`, and related radio setup no longer lack selected parameters; detailed definition and execution remain pending. | Bind the selected baseline into detailed D2 definitions, freeze as-tested configuration/site evidence, and execute later. |
| DPS-BLK-006 | Closed at definition-decision level — UI/browser/CSV/latency/layout oracles are selected in [`DPS-V10_UI_CSV_Latency_Oracles.md`](../DPS/MBSE/tests/DPS-V10_UI_CSV_Latency_Oracles.md), including primary Chrome/Chromium strict-credit policy, Tkinter HOLD/limited disposition, CSV no-overwrite/session integrity, and latency threshold rules. | `DPS-V10-T-005`, `C-004`, `C-005`, `C-006`, `C-008`; detailed activity definitions, browser implementation/evidence, and execution remain pending. | Bind selected oracles into detailed D2 definitions and execution procedures before credit. |
| DPS-BLK-007 | Closed at definition-decision level — LoRa airtime and concurrency/load profile are selected in [`DPS-V10_RF_Range_Concurrency_Parameters.md`](../DPS/MBSE/tests/DPS-V10_RF_Range_Concurrency_Parameters.md): 100-byte SF7/BW125/CR4/5 airtime basis, 10 min 2 s flight-cadence run, optional 20 min 5 Hz synthetic/serial stress, bounded queues/memory/backlog and p95 `<1 s`. | `DPS-V10-C-003`; detailed concurrency definition and execution instrumentation remain pending. | Bind selected load profile into detailed D2 definition and execute later with instrumentation. |
| DPS-BLK-008 | Closed/dispositioned as conditional historical-closure work, not an active v1.0 blocker. v0.1/v0.2 rows become candidate promotions only if historical closure is required. | DPS v0.1/v0.2 closure if required by a future project decision. | Defer historical gates unless required; then create version-specific detailed definitions and reports. |
| DPS-BLK-009 | Dispositioned as system/PM&SE traceability follow-up, not a DPS-only definition blocker once system-level tests and controlled traceability policy are introduced. | Controlled traceability and final requirement-to-test closure matrix. | Model system-level tests/source trace nodes or approve provisional-label policy; DPS may retain provisional trace labels until then. |

#### Folded DPS definition-closure plan and record

The former standalone DPS plan and closure record for 2026-07-02 are folded into this register. This folded content is definition-decision scope only: it does not execute tests, create evidence, claim pass/fail credit, edit D2/PNG diagrams, or modify implementation/source code. v1.0 remains the active DPS detailed-definition baseline; v0.1/v0.2 closure is conditional historical work only if the project later requires it.

DPS-BLK-003 closure note: the selected top-left dashboard model renders CanSat attitude from pitch/roll/yaw. Altitude remains a two-dimensional telemetry plot/value in DPS dashboard artifacts.

##### Folded selected DPS baselines

| Area | Selected baseline / decision | Remaining follow-up |
|---|---|---|
| RF/range/PDR (`DPS-BLK-005`) | `DPS-V10-C-001` uses 500 m horizontal line of sight or approved RF-equivalent setup; 915 MHz; matching 22 AWG straight-wire monopoles with 81.4 mm exposed conductor; RSSI/SNR and validity logs; legal/EIRP/site approval; `N=300` frames at 2 s cadence with `k>=279` for a one-sided 95% exact-binomial PDR lower bound `>=0.90`. | Bind into detailed D2 definitions, freeze as-tested configuration/site evidence, and execute later. |
| LoRa airtime and concurrency (`DPS-BLK-007`) | LoRa calculation baseline is SF7, BW 125 kHz, CR 4/5, explicit header, CRC on, preamble 8, low-data-rate optimization off; calculate at least current `LORA_PAYLOAD_SIZE = 100 bytes`; note `OBCC/LoRa_Frame.md` variable table is 34 bytes before envelope/schema overhead. Concurrency baseline is a 10 min 2 s flight-cadence run plus optional 20 min 5 Hz synthetic/serial stress if over-air margin is inadequate. | Instrument queue depth, memory, backlog recovery, crash/deadlock, and p95 pipeline latency `<1 s`; execute after detailed definition. |
| UI/browser/CSV/latency/layout (`DPS-BLK-006`) | Strict browser credit requires a declared primary browser and repeatable URL/start-command evidence; current non-browser/Tkinter implementation is HOLD/limited for browser credit. CSV requires unique no-overwrite session naming, monotonic rows, row count and checksum/content match to accepted source payload log. Latency alert: no alert for `<=1.0 s`; top alert for `>1.0 s`; invalid/non-monotonic timestamps rejected or flagged. Layout keeps top-left pitch/roll/yaw attitude model and selected v1.0 telemetry cells; no obsolete RH field. | Bind selected oracles into detailed D2 definitions and execution procedures; implement/browser-evidence path before browser credit. |
| Ground-station UART (`DPS-BLK-004`) | Model intent is bidirectional UART, represented later either by one bidirectional CE (`LoRa Forwarder ↔ PC Decoder`) or paired telemetry/command UART CEs. | Update PV2/D2 source model or approve waiver before unconditional `DPS-V10-A-001` / `DPS-V10-T-002` pass credit. |
| Traceability (`DPS-BLK-009`) | Provisional DPS trace labels are acceptable until system-level tests, source trace nodes, or a controlled provisional-label policy exist. | Close through system-level MBSE tests and requirement-to-test matrix, not a DPS-only test. |

##### Folded active DPS v1.0 detailed-definition queue

| Candidate ID | Coverage / purpose | Definition work queued | Status |
|---|---|---|---|
| `DPS-V10-T-004` | FC04 CanSat transmit path. | Define near-field/final receiver setup, sequence-number oracle, radio-busy/not-ready handling, and buffer-overrun hardening. | Candidate; detailed definition required before execution. |
| `DPS-V10-T-005` | FC05 dashboard visualization and related UI constraints. | Define payload-to-plot mapping, attitude-rendering oracle, selected telemetry cells, stale/invalid-field behavior, browser evidence, and latency alert evidence using the selected UI/CSV/latency oracle. | Candidate; selected UI/layout oracle exists; detailed definition and execution required. |
| `DPS-V10-T-006` | FC06 forwarder initialization. | Define restart campaign, SPI/radio/UART missing-fault injections, logging requirements, and false-ready prohibition. | Candidate; fault-injection detail required. |
| `DPS-V10-C-001` | C01 500 m separation/range. | Define horizontal LOS or RF-equivalent setup, radio settings, antenna details, PDR sample/statistics, RSSI/SNR logging, and legal/site prerequisites using the selected RF/range/PDR baseline. | Candidate; selected RF/range/PDR baseline exists; detailed definition and execution required. |
| `DPS-V10-C-003` | C03 concurrent Decoder/CSV/Dashboard execution. | Define 10 min flight-cadence run, optional 20 min 5 Hz stress, queue/memory/backlog instrumentation, and p95 latency criterion using the selected concurrency/load baseline. | Candidate; selected load profile exists; detailed definition and execution required. |
| `DPS-V10-C-004` | C04 browser-accessible dashboard. | Apply the selected primary-browser strict-credit policy, define refresh/reconnect and user-operation evidence, and record limited/HOLD handling for non-browser implementation. | Candidate; browser/evidence policy selected; detailed definition, implementation, and execution required. |
| `DPS-V10-C-005` | C05 unique CSV name and archive integrity. | Apply selected session/restart/same-second cases, no-overwrite oracle, filename uniqueness, monotonic rows, and row-count/checksum comparison to source log. | Candidate; selected CSV/session oracle exists; detailed definition and execution required. |
| `DPS-V10-C-006` | C06 top alert when latency is greater than 1 s. | Apply selected monotonic timestamp source policy, threshold-boundary cases around `1.0 s`, alert placement, invalid timestamp handling, and evidence capture. | Candidate; selected latency threshold oracle exists; detailed definition and execution required. |
| `DPS-V10-C-008` | C08 4x4 plot matrix and top-left attitude model. | Apply selected layout/mapping oracle, pitch/roll/yaw attitude rendering evidence, selected telemetry cells, missing-field behavior, and resize/display checks. | Candidate; selected UI layout oracle exists; detailed definition and execution required. |

Optional separate signoffs: `DPS-V10-C-002` remains covered by `DPS-V10-I-001`; `DPS-V10-C-007` remains covered by `DPS-V10-T-002`. Keep separate reports only if a review board requires constraint-specific signoff.

##### Folded conditional historical DPS backlog

- v0.1 rows remain candidates only if historical v0.1 closure is required: `DPS-V01-I-001`, `DPS-V01-A-001`, `DPS-V01-A-002`, `DPS-V01-T-001` through `DPS-V01-T-006`, and `DPS-V01-C-001` through `DPS-V01-C-007`. If promoted, define the same categories of physical/link inspection, CE analysis, allocation review, downlink/storage, command/uplink, datalogger receive/transmit, dashboard visualization, initialization, range, concurrency, browser, CSV, latency, cooldown, and layout evidence.
- No detailed v0.2 test plan exists under `DPS/MBSE/v0.2/tests/`. If historical v0.2 closure is required, create version-specific definitions for physical/link inspection, CE analysis, allocation, IMU downlink decode/storage, command/uplink, datalogger receive/transmit, dashboard visualization/no-jitter, forwarder initialization, IMU-only processing, range, concurrency, browser, CSV, latency, and layout. Otherwise keep v0.2 as view-only historical scope with an explicit defer/N/A rationale.

##### Folded DPS existing-test update list

| Artifact / activity | Required update or controlled status | Reason |
|---|---|---|
| `DPS/MBSE/tests/DPS-V10-A-001/README.md` | CE-03 analysis uses selected bidirectional or paired UART intent; until PV2/D2 is updated or waived, record limitation for unconditional pass. | Align CE analysis with command/uplink behavior. |
| `DPS/MBSE/tests/DPS-V10-T-002/README.md` | Preserve command/cooldown definition, but require Decoder→Forwarder command-byte evidence and RF command capture; bind discrepancy watch to selected model-update follow-up. | Avoid overclaiming command/uplink pass while source PV2 arrow remains stale. |
| `DPS/MBSE/tests/DPS-V10-T-001/README.md` | Align radio/PDR setup with selected 915 MHz baseline, 500 m horizontal LOS or RF-equivalent controls, `N=300`, `k>=279`, CSV uniqueness, p95 `<1 s`, and corrupt-frame rejection. | Keep downlink decode/storage consistent with selected RF, CSV, and latency oracles. |
| `DPS/MBSE/tests/README.md` | Keep selected baselines, active v1.0 candidate backlog, optional `C-002`/`C-007`, and conditional v0.1/v0.2 work visible in the central DPS test plan. | Prevent `DPS-BLK-001` and `DPS-BLK-008` from reappearing as undefined blockers. |
| `PM&SE/MBSE_Test_Plan_Assessment.md` | Continue to distinguish closed definition decisions from pending detailed modeling, D2/source updates, execution, system traceability, and historical closure. | Prevent finished-DPS or finished-CanSat overclaiming. |

##### Folded DPS D2/source-model follow-up

1. Update DPS v1.0 PV2/source model so CE-03 is either a bidirectional UART component exchange labeled `LoRa Forwarder ↔ PC Decoder` or two explicit paired UART exchanges.
2. Regenerate corresponding PNGs only after the D2/source-model update is reviewed.
3. Update `DPS-V10-A-001` and `DPS-V10-T-002` verification-specific diagrams/checklists to match the final UART modeling choice.
4. Create detailed modeled definitions for active v1.0 candidates `DPS-V10-T-004`, `DPS-V10-T-005`, `DPS-V10-T-006`, `DPS-V10-C-001`, `DPS-V10-C-003`, `DPS-V10-C-004`, `DPS-V10-C-005`, `DPS-V10-C-006`, and `DPS-V10-C-008`.
5. Add RF/range/PDR, LoRa airtime, concurrency, UI/browser/CSV/latency/layout assumptions to detailed views and source-model constraints where appropriate.
6. Create v0.1/v0.2 detailed modeled definitions only if the project requires historical closure.
7. Model system-level trace elements, requirement-to-test matrix entries, and final system-level tests so DPS provisional trace labels are replaced or explicitly controlled.

##### Folded DPS execution status

The 2026-07-02 DPS blocker-resolution issues produced the folded closure decisions above plus the two retained controlled DPS parameter/oracle documents (`DPS-V10_RF_Range_Concurrency_Parameters.md` and `DPS-V10_UI_CSV_Latency_Oracles.md`). Temporary DPS issue files were removed. No tests were executed, no pass/fail credit was claimed, and no D2, PNG, source-code, or implementation updates were claimed by that pass.

##### Folded DPS residual execution-only uncertainties

- Final hardware revisions, UUT serial numbers, radio modules, antenna build/installation details, firmware commits, PC software revisions, parser versions, and tool/script versions.
- Final payload schema/version, field units, timestamp source, monotonic clock behavior, clock synchronization if needed, and OBCC-to-DPS field mapping.
- Legal/EIRP approval, range site geometry, RF-equivalent validation if used, weather/interference conditions, antenna orientation, and independence rationale for packet trials.
- Actual `LORA_PAYLOAD_SIZE`, envelope/schema overhead beyond the 34-byte OBCC variable-table basis, and final airtime/duty-cycle margin.
- Browser start command and URL, whether the current UI is browser-accessible or non-browser/HOLD, UI automation method, screenshot/video evidence method, and dashboard field/layout oracle scripts.
- CSV output location, session-naming implementation, restart/same-second collision handling, checksum method, and raw source-payload log retention.
- Queue-depth, memory, backlog, p95 latency, and crash/deadlock instrumentation for concurrency and stress tests.
- CE-03 source-model update or accepted waiver before unconditional component-exchange and command/uplink pass credit.
- Equipment asset IDs, calibration certificates/function checks, RF monitor configuration, timebase accuracy, environmental limits, and lab configuration.
- Decision on whether v0.1/v0.2 historical closure is required.
- System-level mission/capability/use-case/feared-event trace nodes or controlled provisional-label policy, plus the final requirement-to-test matrix.

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
| PDS-BLK-002 | Definition-level decision selected: add an explicit INA219 `[CE] I2C` exchange between ESS Processing/XIAO and Battery monitoring/INA219; the source-model D2 edit remains pending. | Final CE completeness for `PDS-VV-FC-002`, `PDS-VV-CE-003`, and `PDS-VV-CON-007` remains pending. | Apply the pending source-model/D2 edit and baseline refresh, or approve controlled justification/waiver; no execution credit until the model is updated/justified and evidence is recorded. |
| PDS-BLK-003 | Definition-level candidate added: `PDS-VV-CON-010` regulator-efficiency validation for the 3.3 V and 5 V rail `1 A` / `95%` requirements. | PDS efficiency closure remains candidate/detailed-definition pending. | Define the modeled measurement topology, instrumentation, load cases, uncertainty/guard band, thermal limits, and evidence paths before execution; no test has been executed. |
| PDS-BLK-004 | Campaign-defined load/endurance profile accepted: On-mode load/current budget and 6 h endurance profile are execution parameters for `PDS-VV-CON-002` and system power tests. | Not a new model-definition blocker. | Freeze representative load profile, current budget, logging/sample cadence, ambient/thermal envelope, anomaly handling, and end criteria before execution. |
| PDS-BLK-005 | Source-model/interface edit pending: master-switch/accessibility hardware detail must be added or clarified in the PDS physical/source model, or controlled waiver path approved. | Allocation/external-actor safe power-off closure remains pending source/interface update or waiver. | Update the source/interface definition or approve waiver; later execution records safe access, de-energized state, and any deviation evidence. |
| PDS-BLK-006 | Reclassified as an execution prerequisite for final powered charge acceptance: Li-ion safety documents, charger model/certification, and cell safety evidence are required. | No unresolved definition blocker from this item. | Collect cell/pack datasheet/SDS or equivalent, certification evidence when available, charge/discharge/storage limits, certified charger settings, containment, and safety controls before powered acceptance. |
| PDS-BLK-007 | Closed at definition level by referencing `S&A/PCB_General_Rules.md` as the baseline Carvera Air/PCB rule set; deviations/evidence remain execution records. | No unresolved DFM rule-definition blocker for `PDS-VV-CON-009`. | During execution, map applicable rules to board/coupon IDs and record Carvera/PCB pre-checks, workmanship evidence, deviations, and waivers. |
| PDS-BLK-008 | Closed at definition level by selected conservative missed-demand interpretation and quantitative setpoint/trial criteria for `PDS-VV-CON-003`. | Formal protection-probability credit remains execution-evidence pending. | Use missed demanded unsafe protection-action probability `<1%` per mode; strict claim requires 299 independent zero-miss demanded trials per mode, predeclared safe setpoints, safe-outcome rules, independence rationale, and exact-binomial reporting. |
| PDS-BLK-009 | Reclassified as campaign/execution confirmation for rail-test parameters: no-load, nominal-load, and 1 A cases; thermal limits; settling windows; ripple treatment; sample count; and calibration status. | Not a `PDS-VV-CON-004` definition blocker. | Freeze the rail campaign parameters before execution and record actual settings/evidence in the report. |

#### 2.6.1 PDS §2.6 closure detail folded into this register

This subsection folds the 2026-07-02 PDS closure record into the CON-003 register at definition-planning level only. No tests are executed here, no execution report or pass/fail credit is created, and no `.d2` or `.png` source/model edits are performed by this PM&SE update.

##### Folded PDS candidate and update register

| Candidate / update | Type | Status and follow-up |
|---|---|---|
| `PDS-VV-CON-010` | New regulator-efficiency validation candidate | Queued for the README 3.3 V and 5 V rail `1 A` / `95%` efficiency requirements; detailed modeled definition and execution remain pending. |
| INA219 `[CE] I2C` source follow-on | Pending source-model/D2 edit | Add explicit I2C exchange between ESS Processing/XIAO and Battery monitoring/INA219, then refresh derived artifacts as required before final CE completeness credit. |
| Master switch/accessibility | Pending source-model/interface edit or waiver | Clarify hardware/interface detail in the PDS physical/source model or approve a controlled waiver before unqualified allocation/safe-power-off closure. |

##### Folded existing PDS test update list

| Artifact / activity | Definition-planning update retained here |
|---|---|
| `PDS-VV-FC-002` | Align battery-supervision and CE completeness wording with the pending INA219 I2C source edit; execution evidence remains pending. |
| `PDS-VV-CON-002` | Keep the 6 h On-mode load profile/current budget campaign-defined; freeze profile, logging, thermal envelope, anomaly handling, and end criteria before execution. |
| `PDS-VV-CON-003` | Use the selected conservative missed-demand interpretation, 299 zero-miss independent demanded trials per mode for strict `<1%` claim, predeclared setpoints, safe-outcome rules, independence rationale, and exact-binomial reporting. |
| `PDS-VV-CON-004` | Treat nominal-load, no-load/1 A cases, thermal limits, settling windows, ripple treatment, sample counts, and calibration status as campaign execution parameters. |
| `PDS-VV-CON-009` | Reference `S&A/PCB_General_Rules.md` for Carvera Air/PCB rules; board-specific DFM pre-checks, workmanship evidence, deviations, and waivers are execution records. |
| `PDS-VV-ALLOC-001` | Keep master switch/accessibility as a pending source/interface update or waiver before unqualified allocation and external-actor safe-power-off credit. |
| `PDS&ESS/MBSE/tests/README.md` | Keep the efficiency candidate, source follow-ons, existing-test caveats, incremental-gate caveat, and execution-only prerequisites visible in the PDS test index. |

##### Folded residual PDS execution-only prerequisites

- As-tested article IDs, hardware revisions, regulator/protection/INA219 identities, harness/backplane configuration, firmware/software baselines, and deviations.
- Li-ion cell/pack safety documents, charger model/certification/settings, charge/discharge/storage limits, containment, observer, and abort controls.
- Equipment asset IDs/calibration/status for supplies, loads, power analyzer, DMM/DAQ, oscilloscope/logger, logic analyzer, thermal instruments, timebase, and analysis tools.
- 6 h endurance, rail-load, thermal, settling, ripple, and sample-count campaign settings.
- Protection thresholds, current-limited overcurrent/short-equivalent and overvoltage fixtures, trial sequence, cooldown/reset, independence evidence, exact-binomial analysis, and deviation handling.
- DFM board/coupon mapping to `S&A/PCB_General_Rules.md`, Carvera/PCB rule checks, workmanship evidence, high-current trace review, and waiver/deviation records.
- Final reports and archives must state any unexecuted, limited, or screening evidence without claiming final pass/fail credit.

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
