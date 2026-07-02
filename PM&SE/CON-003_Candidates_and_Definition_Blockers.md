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
| `SYS-END-TO-END-DATA` | Truth/reference stimulus to DPS CSV/dashboard evidence. | Define canonical payload, units, timestamps, freshness/stale/error flags, cross-subsystem observability points. |
| `SYS-POWER-ENDURANCE-TRANSIENT` | Full-system power under mission load. | Define mission load profile, servo/RF/sensor transient cases, rail/current/thermal/brownout oracle. |
| `SYS-DEPLOYMENT-SAFE-LIVE` | ADS/OBCC/PDM/PDS/S&A deployment interaction. | Define safe fixture/live sequence policy, Stand-by inhibit, On trigger timing, false-success checks. |
| `SYS-ENVIRONMENTAL-REGRESSION` | Critical functions after mechanical/environmental screens. | Define approved screen levels and post-screen functional regression set. |
| `SYS-WORKSHOP-READINESS` | Educational/reproducibility closure. | Define independent-user rebuild, guide/documentation, BOM/materials-list, and workshop learning-readiness checks. |

### 1.2 Subsystem candidate backlog

| Area | Candidate activity IDs / candidate definitions | Current status | Immediate definition action |
|---|---|---|---|
| ADS | New candidate: v1.0 ADS-to-OBCC internal rate/freshness test. | Existing `ADS-IVV-C-RATE-5HZ` treats v1.0 as N/A, while assessment flags a possible README-level 5 Hz delivery requirement. | Decide if v1.0 ADS-to-OBCC 5 Hz is a requirement; if yes, add a modeled delivery-rate/freshness test or update the requirement. |
| ADS | New candidate: ADS acceleration accuracy / units-correctness test. | Assessment flags root/subsystem requirement for 3-axis acceleration accuracy not separately closed. | Define acceleration quantity, units, accepted error/tolerance, stimulus fixture, and pass/fail oracle; or retire/clarify requirement. |
| ADS | New candidate: ADS north/heading accuracy test. | Attitude tests intentionally avoid a formal numerical attitude/north claim. | Define heading/north accuracy criterion, magnetic/reference setup, environment limits, and pass/fail oracle. |
| AMS | New candidate: temperature step-response `<=60 s` test. | AMS plans cover accuracy/exposure/I2C/timing, but assessment flags response time as not clearly closed. | Add step-response activity or trace response-time requirement to an existing modeled activity with explicit pass/fail criteria. |
| AMS | New candidate: AMS-to-OBCC internal rate/freshness `>=5 Hz`. | AMS v1.0 downlink uses system 2 s LoRa cadence; internal AMS/OBCC delivery rate is not explicitly closed. | Decide rate semantics and add modeled rate/freshness activity if requirement remains. |
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
| OBCC | Original v1.0 candidates are mapped to gate definitions. | No remaining candidate-definition gap; execution/source/configuration caveats remain. | Keep source-gap declarations and close final readiness prerequisites. |
| S&A | All listed S&A activities are model-defined. | No remaining planning-candidate backlog; CE/allocation ownership gaps remain by design. | Execute `SAA-VV-CE-001`/`SAA-VV-ALLOC-001` ownership analyses and resolve holds. |

## 2. Open definition blockers

### 2.1 Cross-cutting and system-level blockers

| Blocker ID | Blocker | Blocks | Closure action |
|---|---|---|---|
| SYS-BLK-001 | Required system-level tests in §1.1 are not yet modeled. | Finished-CanSat claim and SSIV closure. | Create system-level MBSE test package and definitions. |
| SYS-BLK-002 | No requirement-to-test closure matrix exists across root README and subsystem READMEs. | CON-004 closure and final readiness review. | Build and maintain project requirement-to-test matrix. |
| SYS-BLK-003 | Closed — selected as-built hardware names for the affected configuration are frozen as `RFM96W` radio, `ICM20948` IMU, and `BME280` environmental sensor. | Validity of evidence and cross-subsystem traceability for the affected hardware. | Resolved; active BOM, docs, MBSE views, and source sketches use the selected names. Battery architecture remains tracked separately under `PDS-BLK-001`. |
| SYS-BLK-004 | Canonical payload schema, timestamps, units, freshness/error markers, and schema versioning are not frozen across ADS/AMS/OBCC/DPS. | End-to-end data, DPS dashboard/CSV, OBCC telemetry, ADS/AMS delivery. | Publish controlled payload/interface schema and update affected tests. |
| SYS-BLK-005 | Mission-window duration, expected cadence/frame rule, maximum allowed gap, and timing tolerances are not consistently selected. | ADS mission window, OBCC mission rehearsal, DPS concurrency/data-path tests. | Define project-level timing/tolerance policy before execution. |
| SYS-BLK-006 | Lab equipment availability, model IDs, calibration status, and analysis-tool versions are not unified. | Statistical/timing/accuracy/range evidence interpretation. | Build lab equipment/calibration matrix from assessment §7. |
| SYS-BLK-007 | Educational/documentation/workshop-readiness acceptance tests are not modeled. | Root README closure. | Create `SYS-WORKSHOP-READINESS` and documentation/BOM/rebuild checks. |

### 2.2 ADS blockers

| Blocker ID | Blocker | Blocks | Closure action |
|---|---|---|---|
| ADS-BLK-001 | v1.0 ADS-to-OBCC 5 Hz requirement semantics conflict with `ADS-IVV-C-RATE-5HZ` v1.0 N/A rationale. | ADS v1.0 delivery-rate credit. | Define v1.0 ADS-to-OBCC rate/freshness test or update requirement/model. |
| ADS-BLK-002 | Acceleration accuracy requirement is not separately quantified or assigned. | ADS acceleration closure. | Define acceleration accuracy/units/test or retire/clarify requirement. |
| ADS-BLK-003 | North/heading accuracy requirement lacks quantitative acceptance criterion. | ADS north/orientation closure. | Define heading accuracy, reference setup, magnetic environment controls, pass/fail. |
| ADS-BLK-004 | Mission-window duration and maximum gap are not selected. | `ADS-IVV-FC-MISSION-WINDOW` final pass/fail. | Select mission duration, expected frame/cycle definition, max gap. |
| ADS-BLK-005 | 5 Hz jitter/worst-gap tolerance is not selected. | `ADS-IVV-C-RATE-5HZ` and GPS-chain rate verdict. | Predeclare allowed jitter, worst gap, stale/drop criteria, and sample method. |
| ADS-BLK-006 | Controlled Serial0 schema/parser/campaign-size baseline is missing. | `ADS-IVV-FC-SERIAL` pass/fail for v0.1/v0.2. | Declare schema, port/baud/framing, field list, marker vocabulary, parser version, expected count. |
| ADS-BLK-007 | v1.0 Pointers/Returns data schema and delivery watchdog/timeout threshold are not fixed. | `ADS-IVV-FC-OBCC-DELIVERY`. | Freeze Pointers/Returns contract, delivery watchdog, timing overhead treatment, formal claim type. |
| ADS-BLK-008 | v0.2 I2C timeout is not explicitly modeled. | Formal v0.2 I2C timeout/no-blocking credit. | Update v0.2 model/requirements or retain as characterization/gap with waiver. |
| ADS-BLK-009 | Firmware source/build map/symbols or equivalent instrumentation access is not confirmed. | `ADS-IVV-C-NOBLOCK` pass verdict and deadline claims. | Confirm instrumentation/source access, heartbeat deadline, and overhead allowance. |
| ADS-BLK-010 | Accuracy truth/reference methods and statistics methods remain execution assumptions. | GPS `<5 m`, gyro `<30 deg/s`, and related accuracy tests. | Predeclare truth equipment, surveyed/simulator scenario, rate fixture, guard-band/95/95 method, calibration IDs. |

### 2.3 AMS blockers

| Blocker ID | Blocker | Blocks | Closure action |
|---|---|---|---|
| AMS-BLK-001 | Temperature response-time `<=60 s` requirement is not clearly closed. | AMS README response-time closure. | Add step-response test or trace to existing activity with explicit pass/fail. |
| AMS-BLK-002 | AMS-to-OBCC `>=5 Hz` internal delivery/freshness is not explicitly closed. | Internal measurement-rate closure. | Define rate semantics and model a rate/freshness activity if requirement remains. |
| AMS-BLK-003 | v0.2 has no native logical/CE/allocation/functional-chain views. | Native v0.2 allocation/CE/FC closure. | Keep VV-only bring-up caveat or add source views if native closure is required. |
| AMS-BLK-004 | Candidate coverage for `AMS-VV-CON-002` and `AMS-VV-CON-005` depends on complete API/non-blocking evidence. | Variable-getter and scheduler/no-blocking closure. | Ensure `AMS-VV-API-001` and `AMS-VV-CON-004` execution evidence includes full checklists/static-dynamic coverage. |
| AMS-BLK-005 | Mission/capability/use-case/feared-event nodes are absent; trace IDs are provisional. | Controlled traceability. | Confirm provisional IDs or add trace model elements. |

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
| OBCC-BLK-001 | OBCC v0.1 through v0.9 Capella/D2 source baselines are absent; gates use v1.0 target context only. | Historical gate source-backed equivalence. | Preserve source-gap declaration and identify actual code/configuration baselines in reports. |
| OBCC-BLK-002 | Final readiness pass requires mission rehearsal closure. | `OBCC-V10-FLIGHT-001` final PASS. | Execute/disposition `OBCC-V09-GATE-001` before final readiness board. |
| OBCC-BLK-003 | Payload schema, command schema, radio settings, firmware/configuration IDs, and any as-tested configuration identifiers beyond the selected `RFM96W`/`ICM20948`/`BME280` names are not frozen. | Telemetry/command/RF evidence validity. | Freeze as-tested configuration before execution. |
| OBCC-BLK-004 | Emergency-deploy policy, descent-state observability criteria, safe/error-state behavior, and actuator status semantics need confirmation. | Runtime fault handling, mission rehearsal, deployment safety. | Define cross-subsystem policy with PDM/ADS/PM&SE and update affected tests. |
| OBCC-BLK-005 | Telemetry cadence tolerance, range/PDR evidence, payload-schema traceability, and RF settings/evidence details require disposition; RF module naming is selected as `RFM96W`. | OBCC telemetry/range gate and DPS alignment. | Confirm cadence tolerance, final frame schema, radio settings/configuration, and range/PDR plan. |
| OBCC-BLK-006 | Runtime fault telemetry-gap bound (`<=4 s`) and trace/stress load profile/tool IDs require confirmation. | `OBCC-V06-GATE-001` timing/fault-hardening claims. | Confirm or tailor degradation allowance and record trace/stress tools/load profiles. |

### 2.6 PDS & ESS blockers

| Blocker ID | Blocker | Blocks | Closure action |
|---|---|---|---|
| PDS-BLK-001 | Battery architecture conflict: README `2S1P` vs MBSE/tests `1S1P Li-Ion`. | PDS/ESS and system power acceptance. | Resolve model/README/BOM and freeze final battery configuration. |
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
