# MBSE Test Plan Assessment — CanSat Workshop

Assessment date: 2026-07-01

## 0. Scope and interpretation

| ID | Point |
|---|---|
| SCOPE-001 | This assessment reviews whether the MBSE test definitions, if executed successfully, are sufficient to claim a finished CanSat according to `README.md`. |
| SCOPE-002 | Execution-pending status is not treated as a failure; the question assessed here is definition and coverage sufficiency. |
| SCOPE-003 | Sources reviewed include root `README.md`, `PM&SE/IVV.md`, subsystem READMEs, `*/MBSE/tests/README.md`, individual activity READMEs under `*/MBSE/tests/*/README.md`, and PDM version-local test plans under `PDM/MBSE/v*/tests/README.md`. |
| SCOPE-004 | The assessment uses the project IVV principle that subsystem verification does not replace system-level SSIV closure when cross-subsystem behavior is required. |

## 1. Executive conclusions

| ID | Conclusion | Disposition |
|---|---|---|
| CON-001 | The current MBSE test plans are a strong subsystem-level IVV base, but they are not yet sufficient to claim a finished CanSat. | Add final system-level acceptance and close listed gaps. |
| CON-002 | The split-by-subsystem tests do not fully verify emergent cross-subsystem behavior. | Introduce system-level tests listed in §4. |
| CON-003 | Execution-pending status is acceptable, but some tests are still only planning candidates or have open definition blockers. | Complete detailed definitions before execution credit. |
| CON-004 | Several requirements from subsystem READMEs and the root `README.md` are not yet assigned to executable verification activities. | Add requirement-to-test closure matrix. |
| CON-005 | The affected hardware names are now frozen as `RFM96W`, `ICM20948`, and `BME280`; the OBCC v0.x source-baseline absence is a dispositioned non-issue, while broader execution configuration IDs still require report control. | Use the selected names in active artifacts and identify exact as-tested baselines in reports. |
| CON-006 | The project needs one CanSat-level final readiness review that references subsystem evidence rather than duplicating it. | Model and execute `SYS-FLIGHT-READINESS-CLOSURE`. |

## 2. Finish-readiness against root `README.md`

| ID | README-driven criterion | Assessment | Required action |
|---|---|---|---|
| FR-001 | The CanSat must teach system integration engineering principles. | Subsystem tests are technical, but there is no test proving the workshop teaches integration concepts to target users. | Add workshop/system-integration learning-readiness test. |
| FR-002 | The CanSat must be fully documented for future reproduction by a different team. | Tests generally require evidence records, but there is no independent rebuild / reproduce-from-docs test. | Add independent-user reproduction test. |
| FR-003 | The project shall have an instructible document with subsystem descriptions and proposed educational activities. | Not verified by current MBSE subsystem tests. | Add documentation acceptance test for instructional guide. |
| FR-004 | Each subsystem must create a detailed guide document for assembly, integration, and testing. | Not systematically verified as part of IVV closure. | Add subsystem documentation completeness checklist. |
| FR-005 | Each subsystem should create a materials list in Notion. | Not verified in MBSE test set. | Add BOM/materials-list cross-check. |
| FR-006 | GitHub documentation must be organized by subsystem. | Repository is organized, but no formal verification test closes this administrative requirement. | Add repository organization inspection. |
| FR-007 | Subsystems must be compatible in size, connection, and operation. | Size/mechanical/backplane aspects are partly covered by S&A; operational compatibility is not closed without system-level tests. | Add integrated fit/electrical/protocol/mission rehearsal tests. |
| FR-008 | Each subsystem must complete testing and validation under mission conditions. | Many definitions exist but execution evidence is mostly pending; DPS/PDM have definition gaps. | Complete definitions and execution reports. |
| FR-009 | Overall finished-CanSat claim. | Not currently supportable from subsystem definitions alone. | Execute system-level final readiness closure after subsystem evidence exists. |

## 3. Subsystem assessment and gaps

| ID | Subsystem | Assessment point | Gap or risk | Required action |
|---|---|---|---|---|
| SUB-ADS-001 | ADS | ADS has strong coverage for PC/PL inspection, CE analysis, allocation, GPS, angular rate, attitude, init, Serial0, OBCC delivery, mission-window, timing, no-blocking, getter, and manufacturing constraints. | Overall ADS test definition maturity is high. | Execute and report evidence. |
| SUB-ADS-002 | ADS | ADS v1.0 internal delivery/freshness closure path is selected. | The shared PM&SE sensor-to-OBCC contract resolves the 5 Hz vs 2 s cadence semantics through `ADS-V10-DATA-FRESHNESS`; existing ADS D2/model updates and execution remain pending. | Extend `ADS-IVV-FC-OBCC-DELIVERY`, `ADS-IVV-C-GETTER`, and `ADS-IVV-C-RATE-5HZ` or an equivalent modeled path with the shared freshness/status/age rule. |
| SUB-ADS-003 | ADS | ADS acceleration definition path is selected. | `ADS-IVV-C-ACCEL-3AXIS` now defines linear acceleration units (`m/s²` / `g` conversion), six-face gravity fixture, `n=59` strict samples, and guard-banded thresholds; D2/modeling and execution remain pending. | Model and execute the candidate before claiming acceleration closure. |
| SUB-ADS-004 | ADS | North/heading quantitative criterion is selected. | `ADS-IVV-C-HEADING-NORTH` now defines reference setup, magnetic controls, `n=59` strict samples, and `<=10°` guard-banded circular-error threshold; D2/modeling and execution remain pending. | Model and execute the candidate before claiming heading/north closure. |
| SUB-ADS-005 | ADS | Mission-window runtime criteria are selected. | ADS mission duration is 10 min / 600 s; expected 5 Hz update opportunities are 3000; maximum internal freshness gap is 400 ms; reset/stuck-loop/stale-valid failure rules are selected. | Update D2/model views if needed and execute `ADS-IVV-FC-MISSION-WINDOW`; no pass credit until evidence exists. |
| SUB-AMS-001 | AMS | AMS has good multi-version coverage for breadboard, PCB delivery, bring-up, PC/PL, I2C CE, API/allocation, atmospheric measurement, init faults, I2C timeout, processing/no-blocking, and sunlight/airflow. | Overall AMS definition maturity is good. | Execute and report evidence. |
| SUB-AMS-002 | AMS | Temperature response-time closure path is selected but remains unmodeled/unexecuted. | README requires temperature response time ≤60 s; current accuracy, exposure, I2C timing, and processing timing plans do not by themselves close it. | Add `AMS-V10-TEMP-RESPONSE-60S` or an explicitly equivalent modeled step-response activity, either standalone or as a clear `AMS-VV-FC-001` extension. |
| SUB-AMS-003 | AMS | AMS ≥5 Hz delivery/freshness semantics are selected by the shared PM&SE contract. | `AMS-V10-DATA-FRESHNESS` or extensions of `AMS-VV-API-001`, `AMS-VV-FC-001`, `AMS-VV-FC-002`, `AMS-VV-CON-003`, and `AMS-VV-CON-004` must still be modeled/executed. | Update AMS definitions to use the shared `5 Hz` OBCC request, `2 s` telemetry packaging, `<=400 ms` fresh age, six-status enum, timestamp/age evidence, and no-stale-valid rule. |
| SUB-DPS-001 | DPS | DPS v1.0 has detailed definitions for physical inspection, CE analysis, allocation, downlink decode/storage, command/uplink, and CanSat receive path. | Good start but incomplete. | Continue detailed definition pass. |
| SUB-DPS-002 | DPS | DPS v1.0 definition decisions are selected, but multiple activities remain candidates. | RF/range/PDR, LoRa/concurrency, UI/browser/CSV/latency/layout, and bidirectional UART model-intent decisions are no longer undefined; pending detailed definitions still include CanSat transmit path, dashboard visualization, forwarder initialization, 500 m separation/range, concurrency, browser access, CSV uniqueness, latency alert, and plot layout. | Convert candidate rows to modeled D2 definitions using the selected DPS parameter/oracle docs; execute later before credit. |
| SUB-DPS-003 | DPS | DPS v0.1/v0.2 historical closure is dispositioned as conditional work. | Earlier delivery versions are acknowledged but not fully defined under `DPS/MBSE/tests/`; they are not active v1.0 blockers unless historical closure is required. | Add version-specific DPS gates only if v0.1/v0.2 must be closed. |
| SUB-DPS-004 | DPS | DPS/OBCC payload field blocker closed. | The obsolete RH dashboard/frame field was removed from the controlled OBCC table and DPS dashboard artifacts. | Keep broader payload-schema/versioning control under `SYS-BLK-004`. |
| SUB-DPS-005 | DPS | Dashboard requirement/model blocker closed. | The selected top-left dashboard model renders CanSat attitude from pitch/roll/yaw, and the UI/CSV/latency/layout oracle baseline is selected. | Altitude remains a two-dimensional telemetry plot/value; detailed D2 definitions, browser implementation/evidence, and execution remain pending. |
| SUB-OBCC-001 | OBCC | OBCC has broad gate coverage from v0.1 through v1.0 final closure. | Coverage includes startup health, buses/getters, telemetry, command/state, deployment gate, runtime faults, RTOS allocation, workmanship, mission rehearsal, and final review. | Execute and link evidence to final closure. |
| SUB-OBCC-002 | OBCC | OBCC v0.x source-baseline absence is dispositioned as a lifecycle/modeling non-issue. | Versions may jump from v0.x to v1.0; OBCC's mostly software-dependent scope did not require incremental source-model deliveries, so v0.x gates use v1.0 model copies as target context only. | Do not fabricate v0.x source baselines; reports must identify actual code/configuration baselines and target-context-only model references where applicable. |
| SUB-OBCC-003 | OBCC | OBCC final pass mission-rehearsal dependency is dispositioned as a literal readiness gate. | `OBCC-V10-FLIGHT-001` still forbids final PASS if `OBCC-V09-GATE-001` is unresolved, but this is not a test-definition gap. | Execute mission rehearsal or record approved defer/hold before final readiness board. |
| SUB-OBCC-004 | OBCC | Payload/radio/emergency/fault definition decisions are selected at planning level. | The OBCC/DPS LoRa telemetry contract freezes horizontal 500 m LOS, `915 MHz`, 22 AWG 81.4 mm antennas, RF/PDR/cadence criteria, and payload/command traceability; the OBCC-owned deployment/fault policy freezes descent observability, emergency-deploy, safe/error, and actuator-status semantics. Actual as-tested IDs remain execution records. | Update affected OBCC READMEs/D2 later to cite the selected baselines and record as-tested configuration before execution credit. |
| SUB-PDS-001 | PDS & ESS | PDS/ESS has strong coverage across v0.1, v0.2, v0.3, and v1.0. | Coverage includes power path, charge, endurance, protection probability, rails, supervision, physical inspection, and PCB DFM. | Execute with strict safety controls. |
| SUB-PDS-002 | PDS & ESS | Battery architecture conflict is closed. | PDS/ESS README, BOM, and MBSE/tests now align on `1S1P Li-Ion`; this does not close remaining PDS power/safety blockers. | Maintain the selected architecture in execution reports and close the remaining non-battery PDS blockers before final power acceptance. |
| SUB-PDS-003 | PDS & ESS | Regulator efficiency closure path is selected at planning level. | `PDS-VV-CON-010` is queued as the regulator-efficiency validation candidate for the 3.3 V and 5 V rails at 1 A with 95% efficiency; detailed modeled definition and execution remain pending. | Define/model the candidate measurement topology, instrumentation, load cases, uncertainty/guard band, thermal limits, and evidence paths before execution; no efficiency pass credit yet. |
| SUB-PDS-004 | PDS & ESS | INA219 I2C CE source update path is selected. | Add explicit INA219 `[CE] I2C` between ESS Processing/XIAO and Battery monitoring/INA219 as a pending quick source-model/D2 update. | Until the source edit is applied or controlled justification/waiver is approved, final CE completeness credit remains pending. |
| SUB-PDS-005 | PDS & ESS | On-mode load profile and master switch/accessibility are dispositioned separately. | The 6 h On-mode load/current profile may remain campaign-defined, while master-switch/accessibility hardware/interface detail is a pending source-model/interface edit or waiver. | Freeze campaign load/endurance inputs before execution, and update/waive the master-switch/accessibility source/interface detail before unqualified allocation/safe-power-off credit. |
| SUB-PDM-001 | PDM | PDM v0.1 fall-test and v0.2 BLE/manual deployment definitions exist, v1.0 IMU-triggered deployment has one detailed definition, and the complete v1.0 candidate backlog is registered. | PDM still has many v1.0 candidate rows pending detailed modeling/D2 updates and execution; `PDM-VV-FC-001` is modeled but execution readiness/evidence remain pending. | Define/model remaining v1.0 PC/PL, CE, allocation, FC, and constraint activities before credit. |
| SUB-PDM-002 | PDM | v1.0 terminal descent-speed requirement is selected. | The selected limit is `<= 11 m/s` for `PDM-VV-FC-003` and linked system deployment-safety planning; detailed definition/model updates and execution evidence remain pending. | Apply/model the selected criterion in PDM and system tests; execute/report with calibrated mass, video/time-distance or equivalent measurement, uncertainty, and wind/environment evidence. |
| SUB-PDM-003 | PDM | Emergency-deploy policy is selected as OBCC-owned. | PDM consumes OBCC deployment commands and exposes actuator/status evidence; OBCC owns mode, normal/emergency trigger decisions, descent observability, safe/error behavior, and no-false-success interpretation. System modeling/execution remains pending. | Apply the OBCC deployment/fault policy in PDM, OBCC, and `SYS-DEPLOYMENT-SAFE-LIVE` definitions without redefining ownership. |
| SUB-PDM-004 | PDM | Servo status semantics are selected at outline level. | Future `PDM-VV-CE-004`, `PDM-VV-FC-001`, OBCC, and system tests must map implementation evidence to `NOT_COMMANDED`, `COMMAND_SENT`, `OPEN_IN_PROGRESS`, `OPEN_CONFIRMED`, `NO_OPEN_CONFIRMED`, `TIMEOUT`, `JAM_DETECTED`/`PDM_FAULT`, or `UNKNOWN`; detailed status-field/model updates and execution remain pending. | Define detailed feedback/status mapping and no-false-success evidence; only `OPEN_CONFIRMED` receives strict deployment-success credit. |
| SUB-SAA-001 | S&A | S&A has strong physical/mechanical definitions for v0.1 and v1.0. | Covers PC/PL, integrated fit, envelope/mass, modules, backplane, printing, retention, and deployment clearance; execution/reporting remain pending on the final as-flown article. | Execute and report on the final as-flown article before claiming pass credit. |
| SUB-SAA-002 | S&A | Physical-only S&A model scope is accepted at definition-decision level. | Absence of baseline S&A CE/LC/F/allocation source views is a non-issue for this closure; `SAA-VV-CE-001` and `SAA-VV-ALLOC-001` remain execution-time ownership/cross-reference/disposition analyses for implied interfaces and integration functions. | Execute/report those analyses with subsystem cross-references, owner responses, waivers, and evidence; do not force baseline logical/CE/allocation source modeling unless later desired. |
| SUB-SAA-003 | S&A | Environmental screen decisions are approved at definition-decision level. | Tailored drop/vibration/landing screen levels, surfaces, orientations/axes, durations/events, limitations, and success criteria are approved by the folded S&A §2.8.1 record in `PM&SE/CON-003_Candidates_and_Definition_Blockers.md`; detailed S&A test-definition edit and execution remain pending. | Apply the pending `SAA-BLK-003` test-definition edit to affected S&A/system environmental planning, then execute/report before credit. |
| SUB-SAA-004 | S&A | Height and mass interpretation is confirmed at definition-decision level. | Use `122 mm` height and conservative mass guard band `measured mass + U_M < 350.0 g` unless a later authority selects stricter criteria; execution measurement remains pending. | Measure the final as-flown article with calibrated equipment, uncertainty guard bands, configuration evidence, and deviations/waivers before credit. |

## 4. Required system-level tests

| ID | Proposed system-level test | Purpose | Key pass/fail focus |
|---|---|---|---|
| SYS-001 | `SYS-FLIGHT-READINESS-CLOSURE` | One CanSat-level closure matrix across ADS, AMS, OBCC, PDS/ESS, PDM, S&A, and DPS. | Every subsystem required activity has executed evidence, approved N/A/defer rationale, or waiver; no critical blocker remains. |
| SYS-002 | `SYS-MISSION-REHEARSAL` | Full assembled CanSat plus ground station mission sequence. | Boot, Stand-by, On command, sensing, 2 s LoRa telemetry, dashboard display/store, deployment inhibit/trigger branches. |
| SYS-003 | `SYS-RF-RANGE-PDR` | End-to-end final-article RF performance. | ≥500 m and ≥90% PDR with exact binomial confidence; legal radio settings; final antenna/enclosure orientation. |
| SYS-004 | `SYS-END-TO-END-DATA` | Verify complete data path from truth/reference stimulus to ground evidence. | Sensor truth → subsystem processing → OBCC payload → LoRa → DPS CSV/dashboard; units, timestamps, and the shared PM&SE ADS/AMS freshness/status/age rule (`VALID`/non-`VALID`, age, and no stale-valid behavior). |
| SYS-005 | `SYS-POWER-ENDURANCE-TRANSIENT` | Verify full-system power under realistic mission load. | Battery, regulators, sensors, LoRa TX, servo event, brownout/reset behavior, rail tolerances, thermal behavior. |
| SYS-006 | `SYS-DEPLOYMENT-SAFE-LIVE` | Verify cross-subsystem deployment function using safe fixture and approved live sequence as applicable. | ADS/OBCC/PDM/PDS/S&A interaction; Stand-by inhibit; On-mode trigger ≤5 s; no false success. |
| SYS-007 | `SYS-ENVIRONMENTAL-REGRESSION` | Re-run critical functions after mechanical/environmental screens. | Post-vibration/drop/landing power, comms, sensing, deployment, structure, and backplane checks. |
| SYS-008 | `SYS-WORKSHOP-READINESS` | Verify root README educational/reproducibility requirements. | Independent team can assemble, integrate, test, and understand the CanSat using project documentation. |

## 5. Cross-cutting inconsistencies and blind spots

| ID | Area | Finding | Required action |
|---|---|---|---|
| GAP-001 | Cadence semantics | ADS/AMS 5 Hz subsystem-to-OBCC freshness semantics are selected by the shared PM&SE contract; the v1.0 LoRa 2 s telemetry cadence remains separate. | Implement/model `ADS-V10-DATA-FRESHNESS` and `AMS-V10-DATA-FRESHNESS` (or the documented existing-test extensions) and execute them before claiming closure. |
| GAP-002 | Hardware naming | Closed for the affected hardware: active artifacts now use the selected `RFM96W` radio, `ICM20948` IMU, and `BME280` environmental sensor names. | Maintain these names in controlled artifacts and record exact as-tested hardware/configuration in execution reports. |
| GAP-003 | Battery architecture | Closed: PDS/ESS README, BOM, and MBSE/tests select `1S1P Li-Ion`. | Maintain this selection in reports; final PDS/ESS and system power tests still require the non-battery PDS blockers to close. |
| GAP-004 | Payload schema | The DPS/OBCC RH field mismatch is closed, DPS UI/CSV/latency/layout oracles are selected, ADS/AMS sensor freshness/status semantics are controlled by the shared PM&SE contract, and the OBCC/DPS LoRa telemetry contract selects the active OBCC payload/command/RF traceability baseline; broader system end-to-end schema/versioning remains to be modeled. | Use the selected OBCC/DPS and ADS/AMS contracts while freezing the remaining system canonical payload/schema items for `SYS-END-TO-END-DATA`. |
| GAP-005 | Deployment policy | OBCC-owned deployment/fault criteria are selected at definition level, and PDM status/no-false-success semantics are selected at outline level: ADS/AMS provide data/status, PDM deploys when commanded and exposes status, and OBCC owns mode/trigger/emergency/safe-error/no-false-success behavior. Proper MBSE/system modeling remains pending. | Apply the OBCC policy and PDM status mapping in affected OBCC/PDM/system tests and later model it in `SYS-DEPLOYMENT-SAFE-LIVE`; execute safe-fixture/live sequence later before credit. |
| GAP-006 | Power efficiency | PDS efficiency validation candidate `PDS-VV-CON-010` has been added at definition-planning level for the README 95% regulator-efficiency requirement, but it has not been executed. | Complete detailed modeling and execution of `PDS-VV-CON-010`, or change/retire the requirement through controlled review; no efficiency pass credit yet. |
| GAP-007 | Full-system transients | Servo actuation, RF TX current, brownout and reset behavior need system-level verification beyond subsystem bench tests. | Add `SYS-POWER-ENDURANCE-TRANSIENT`. |
| GAP-008 | Software configuration | Build reproducibility, firmware commits, payload schema versioning, and toolchain control are required in reports but not unified across subsystems. | Create project-level configuration-control checklist. |
| GAP-009 | Mechanical environment | S&A tailored drop/vibration/landing screen decisions are approved at definition-decision level; detailed S&A test-definition edit, system environmental-regression alignment, and execution remain pending. | Apply the pending S&A environmental-screen definition edit, align `SYS-ENVIRONMENTAL-REGRESSION` as needed, then execute/report; no pass credit yet. |
| GAP-010 | Documentation/workshop | Root README administrative and educational deliverables are not tested. | Add documentation and workshop readiness tests. |
| GAP-011 | Statistical claims | Several tests correctly label screening evidence, but final reliability/PDR/deadline claims require defined samples and independence. | Enforce `PM&SE/IVV.md` statistical policy in final closure. |
| GAP-012 | Source baselines | OBCC v0.x source-view absence is dispositioned as a non-blocking lifecycle/modeling decision; S&A physical-only baseline scope is accepted by the folded CON-003 closure record; PDM has several candidate-only v1.0 tests. | Preserve target-context/reporting caveats for OBCC, execute S&A CE/allocation ownership analyses without forcing baseline S&A source modeling, and separately address PDM model maturity. |

## 6. Testing-strategy consistency assessment

| ID | Point | Assessment | Required action |
|---|---|---|---|
| STRAT-001 | IADT coverage | ADS, AMS, PDS/ESS, S&A, and OBCC generally implement Inspection/Analysis/Demonstration/Testing well. | Continue using `PM&SE/IVV.md` as common policy. |
| STRAT-002 | Definition maturity | DPS parameter/oracle decisions and PDM definition decisions are selected, but DPS and PDM still lag in detailed modeled definition completeness. | Prioritize detailed D2 definition completion for DPS candidate rows and PDM v1.0 candidate rows using the selected criteria. |
| STRAT-003 | Version handling | Some subsystems have actual v0.x MBSE views; OBCC v0.x gates are target-context-only by accepted lifecycle decision rather than by an open blocker. | Do not compare OBCC v0.x gates as source-backed gates; execution reports must identify the actual code/configuration baselines used. |
| STRAT-004 | Fault hardening | OBCC, ADS, and PDS/ESS have strong explicit fault-hardening. DPS now has selected RF/UI/load hardening oracles but still needs detailed activity definitions; PDM has selected OBCC policy/status baselines but still needs detailed fault definitions/model updates; S&A environmental-screen decisions are approved at definition-decision level but pending detailed test-definition edit and execution. | Add/complete detailed fault matrices/model updates using the selected PDM baselines, DPS activity definitions, and the pending S&A environmental-screen definition edit/execution. |
| STRAT-005 | Statistics | Many tests use correct screening-vs-reliability wording; final closure must prevent overclaiming. | Require statistical claim review in system final readiness. |
| STRAT-006 | Equipment/calibration | Most definitions call for equipment IDs/calibration, but exact equipment models are still TBD. | Build lab equipment availability matrix from §7. |
| STRAT-007 | SSIV closure | No single CanSat-level SSIV acceptance definition exists. | Create `SYS-FLIGHT-READINESS-CLOSURE`. |

## 7. External equipment needed for testing

### 7.1 General lab and evidence equipment

| ID | Equipment | Needed for |
|---|---|---|
| EQ-GEN-001 | ESD mat and wrist strap | PCB, electronics, and subsystem inspection/bring-up. |
| EQ-GEN-002 | Microscope or high-magnification inspection camera | Solder/workmanship, PCB footprints, connector inspection. |
| EQ-GEN-003 | Evidence camera / video camera | Photo/video evidence for all inspection and mechanical tests. |
| EQ-GEN-004 | Good bench lighting or illumination meter | PCB and physical inspection evidence quality. |
| EQ-GEN-005 | Digital multimeters | Continuity, polarity, voltage, current, resistance checks. |
| EQ-GEN-006 | Cable tester / continuity tester | USB-C, backplane, harness and connector verification. |
| EQ-GEN-007 | Oscilloscope | PWM, SPI/I2C/UART waveform checks, rail transients. |
| EQ-GEN-008 | Logic analyzer | I2C/UART/SPI timing, bus faults, payload/debug traces. |
| EQ-GEN-009 | Current-limited bench power supplies | Safe bring-up, power tests, subsystem fault injection. |
| EQ-GEN-010 | USB power meter | USB-powered bench and ground-station current checks. |
| EQ-GEN-011 | DAQ or multi-channel logger | Rails, timing, current, thermal, long-duration tests. |
| EQ-GEN-012 | Calibrated timebase or synchronized timestamp method | Cadence, timeout, PDR, deployment timing, data correlation. |
| EQ-GEN-013 | Thermo-hygrometer / ambient monitor | Required environmental evidence for most tests. |
| EQ-GEN-014 | Evidence workstation / lab PC | Serial logs, scripts, reports, analysis and archive. |
| EQ-GEN-015 | Version-controlled analysis scripts | PDR, timing, uncertainty, CSV/dashboard validation. |

### 7.2 ADS equipment

| ID | Equipment | Needed for |
|---|---|---|
| EQ-ADS-001 | GNSS simulator or surveyed open-sky reference receiver | GPS `<5 m` position accuracy. |
| EQ-ADS-002 | Surveyed reference point / reference antenna setup | Open-sky GPS truth control. |
| EQ-ADS-003 | GPS/UART fault injector | Silent, malformed, stale, no-fix GPS cases. |
| EQ-ADS-004 | Rate table / turntable | Angular-rate accuracy testing. |
| EQ-ADS-005 | Static zero-rate fixture | IMU zero-rate characterization. |
| EQ-ADS-006 | Non-magnetic 6-face orientation fixture | Attitude/orientation plausibility tests. |
| EQ-ADS-007 | Compass, magnetic reference, or controlled field source | North/yaw/heading reference. |
| EQ-ADS-008 | I2C fault injector | IMU NACK, stuck bus, wrong-address, partial-read cases. |
| EQ-ADS-009 | ADS/OBCC log harness | v1.0 ADS-to-OBCC delivery evidence. |
| EQ-ADS-010 | Power supply or battery simulator | Controlled power and reset/brownout evidence. |

### 7.3 AMS equipment

| ID | Equipment | Needed for |
|---|---|---|
| EQ-AMS-001 | Reference thermometer | Temperature accuracy and exposure checks. |
| EQ-AMS-002 | Stable thermal source or temperature chamber | Temperature accuracy and response-time testing. |
| EQ-AMS-003 | Reference pressure instrument | Pressure accuracy and altitude-resolution tests. |
| EQ-AMS-004 | Pressure calibrator or pressure-step fixture | Altitude resolution / pressure delta evidence. |
| EQ-AMS-005 | Airflow indicator or anemometer | Ventilation/airflow verification. |
| EQ-AMS-006 | Sun simulator or bright lamp | Sunlight-blocking exposure demonstration. |
| EQ-AMS-007 | Shade/ventilation fixture | Exposure configuration test. |
| EQ-AMS-008 | BME280/I2C test harness | v0.2 bring-up and v1.0 I2C tests. |
| EQ-AMS-009 | Logic analyzer | I2C timing and fault evidence. |
| EQ-AMS-010 | Host PC serial/logger | Breadboard/v1.0 logging and evidence capture. |

### 7.4 OBCC, DPS, and RF equipment

| ID | Equipment | Needed for |
|---|---|---|
| EQ-RF-001 | Final CanSat OBCC radio article | RF, telemetry, command, and mission tests. |
| EQ-RF-002 | Ground station radio article | DPS/OBCC downlink/uplink tests. |
| EQ-RF-003 | Ground-station PC | Dashboard, CSV, command, evidence capture. |
| EQ-RF-004 | Antennas matching final configuration | Range/PDR and mission rehearsal. |
| EQ-RF-005 | RF dummy load | Safe radio bring-up. |
| EQ-RF-006 | RF monitor / packet sniffer | Raw frame, RSSI/SNR, command/downlink evidence. |
| EQ-RF-007 | 500 m range site or approved RF-equivalent setup | Range/PDR requirement. |
| EQ-RF-008 | Range survey / distance measurement tool | Endpoint geometry and distance evidence. |
| EQ-RF-009 | Weather instrument or weather recorder | Range/PDR environmental evidence. |
| EQ-RF-010 | Command transmitter / dashboard command tool | On/Stand-by and command-uplink tests. |
| EQ-RF-011 | Malformed-frame generator | Decode hardening and invalid command tests. |
| EQ-RF-012 | RTOS trace/debug hook | OBCC scheduler/liveness analysis. |
| EQ-RF-013 | Fault-injection harness for I2C/UART/SPI/PWM/RF | OBCC runtime fault gates. |
| EQ-RF-014 | Safe deployment logic probe or actuator surrogate | Deployment-gating tests without live release hazard. |
| EQ-RF-015 | CSV/dashboard oracle scripts | DPS storage/display correctness. |

### 7.5 PDS & ESS equipment

| ID | Equipment | Needed for |
|---|---|---|
| EQ-PWR-001 | Certified current-limited Li-ion charger or CCCV supply | Normal charge constraint. |
| EQ-PWR-002 | Battery emulator | Safe power/protection testing without Li-ion abuse. |
| EQ-PWR-003 | Electronic loads for 3.3 V and 5 V rails up to 1 A | Rail regulation and endurance tests. |
| EQ-PWR-004 | Programmable load profile emulator | 6 h On-mode endurance. |
| EQ-PWR-005 | Precision current shunts | Rail, battery, and servo current measurement. |
| EQ-PWR-006 | Power analyzer | Efficiency, voltage/current/power logging. |
| EQ-PWR-007 | Thermal camera or thermocouples | Regulator, PCB trace, battery thermal checks. |
| EQ-PWR-008 | Li-ion fire-safe containment | Battery charge/discharge safety. |
| EQ-PWR-009 | Overcurrent / short-equivalent injection hardware | Protection probability tests. |
| EQ-PWR-010 | Overvoltage injection hardware | Protection probability tests. |
| EQ-PWR-011 | INA219/I2C analyzer and fault fixture | Battery supervision and timeout tests. |
| EQ-PWR-012 | Li-ion safety documentation package | Cell/pack safety prerequisite. |

### 7.6 PDM and mechanical/S&A equipment

| ID | Equipment | Needed for |
|---|---|---|
| EQ-MECH-001 | Safe deployment fixture | OBCC/PDM deployment tests. |
| EQ-MECH-002 | Servo actuator surrogate or instrumented servo fixture | Deployment timing and no-open tests. |
| EQ-MECH-003 | High-speed or clear video camera | Deployment, parachute release, drop evidence. |
| EQ-MECH-004 | Drop fixture or drop tower | PDM descent and S&A landing-impact tests. |
| EQ-MECH-005 | Approved impact surface | Drop/landing tests. |
| EQ-MECH-006 | Shock witness or accelerometer/event logger | Landing/drop/vibration screen evidence. |
| EQ-MECH-007 | Vibration/proof-load fixture or shaker | Retention/environmental screens. |
| EQ-MECH-008 | 355 ml envelope/can gauge | CanSat diameter/height envelope check. |
| EQ-MECH-009 | Calipers and height gauge | Dimensional measurements. |
| EQ-MECH-010 | Precision scale | Mass checks. |
| EQ-MECH-011 | PCB fit gauges / dummy PCBs | Module accommodation checks. |
| EQ-MECH-012 | Clearance gauges / feeler gauges | Backplane, parachute, cap, and module interference checks. |
| EQ-MECH-013 | Torque/cycle tool | Screw/boss/assembly process tests. |
| EQ-MECH-014 | Parachute pack/reset fixture | Repeatable deployment-clearance tests. |
| EQ-MECH-015 | Wind meter | Drop/descent tests where wind affects interpretation. |
| EQ-MECH-016 | Backplane checkout tool | Rail/testpoint/signal access and continuity. |
| EQ-MECH-017 | Header/pitch gauge | Backplane/header physical inspection. |

## 8. Recommended next actions

| ID | Action | Owner suggestion |
|---|---|---|
| ACT-001 | Create a system-level MBSE tests folder and define `SYS-FLIGHT-READINESS-CLOSURE`. | PM&SE / system IVV owner. |
| ACT-002 | Add `SYS-MISSION-REHEARSAL`, `SYS-RF-RANGE-PDR`, `SYS-END-TO-END-DATA`, and `SYS-POWER-ENDURANCE-TRANSIENT`. | PM&SE with all subsystem owners. |
| ACT-003 | Resolve remaining requirement/model conflicts and model-update follow-up: DPS detailed definitions using selected RF/UI/load oracles plus bidirectional UART PV2 update/waiver, implementation of selected ADS/AMS freshness updates, OBCC README/D2 updates using the selected telemetry/RF and deployment/fault baselines, application/modeling of selected PDM criteria (`<= 11 m/s` descent speed, OBCC policy boundary, servo-status/no-false-success semantics, and v0.2/v0.1 quantitative criteria), and execution configuration details; preserve closed selections for `1S1P Li-Ion`, `RFM96W`, `ICM20948`, and `BME280`. | PM&SE configuration control. |
| ACT-004 | Complete detailed definitions for DPS candidate rows and PDM v1.0 candidate rows. | DPS and PDM owners. |
| ACT-005 | Preserve selected ADS mission-window/freshness criteria (10 min, 5 Hz, 400 ms) and apply the selected OBCC/DPS 2 s telemetry, RF/PDR, and payload/command contract; define only the remaining system-level schema/timing items not covered by those baselines. | OBCC/DPS/PM&SE. |
| ACT-006 | Add/model the selected `AMS-V10-TEMP-RESPONSE-60S`, `AMS-V10-DATA-FRESHNESS`, and `ADS-V10-DATA-FRESHNESS` paths, plus ADS acceleration, ADS north heading, and PDS efficiency tests. | Respective subsystem owners. |
| ACT-007 | Build a lab equipment availability matrix from §7 with asset IDs and calibration status. | Lab / PM&SE. |
| ACT-008 | Add documentation/workshop readiness tests to close root `README.md` administrative and educational requirements. | Workshop / PM&SE. |
| ACT-009 | Execute subsystem tests and store reports under the modeled `results/<activity-id>/` paths. | Subsystem owners. |
| ACT-010 | Execute final system readiness review only after subsystem reports, deviations, waivers, and residual risks are indexed. | Final review board. |
