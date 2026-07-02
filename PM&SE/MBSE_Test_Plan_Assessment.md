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
| SUB-ADS-003 | ADS | ADS acceleration requirement is not separately closed. | README requires acceleration in 3 axes with accuracy of 30 deg/s², but detailed constraint coverage emphasizes angular rate `<30 deg/s`. | Add explicit acceleration accuracy / units-correctness test or retire/clarify requirement. |
| SUB-ADS-004 | ADS | North orientation requirement lacks quantitative acceptance. | README says ADS must determine orientation to north, but current attitude test states no formal numerical attitude accuracy claim unless a new constraint is added. | Define heading/north accuracy criterion and test. |
| SUB-ADS-005 | ADS | Mission-window runtime test is blocked. | Mission-window duration and maximum allowed gap are TBD. | Select mission-window duration and gap tolerance before execution. |
| SUB-AMS-001 | AMS | AMS has good multi-version coverage for breadboard, PCB delivery, bring-up, PC/PL, I2C CE, API/allocation, atmospheric measurement, init faults, I2C timeout, processing/no-blocking, and sunlight/airflow. | Overall AMS definition maturity is good. | Execute and report evidence. |
| SUB-AMS-002 | AMS | Temperature response-time closure path is selected but remains unmodeled/unexecuted. | README requires temperature response time ≤60 s; current accuracy, exposure, I2C timing, and processing timing plans do not by themselves close it. | Add `AMS-V10-TEMP-RESPONSE-60S` or an explicitly equivalent modeled step-response activity, either standalone or as a clear `AMS-VV-FC-001` extension. |
| SUB-AMS-003 | AMS | AMS ≥5 Hz delivery/freshness semantics are selected by the shared PM&SE contract. | `AMS-V10-DATA-FRESHNESS` or extensions of `AMS-VV-API-001`, `AMS-VV-FC-001`, `AMS-VV-FC-002`, `AMS-VV-CON-003`, and `AMS-VV-CON-004` must still be modeled/executed. | Update AMS definitions to use the shared `5 Hz` OBCC request, `2 s` telemetry packaging, `<=400 ms` fresh age, six-status enum, timestamp/age evidence, and no-stale-valid rule. |
| SUB-DPS-001 | DPS | DPS v1.0 has detailed definitions for physical inspection, CE analysis, allocation, downlink decode/storage, command/uplink, and CanSat receive path. | Good start but incomplete. | Continue detailed definition pass. |
| SUB-DPS-002 | DPS | Multiple DPS v1.0 activities remain candidates. | Pending detailed definitions include CanSat transmit path, dashboard visualization, forwarder initialization, 500 m separation/range, concurrency, browser access, CSV uniqueness, latency alert, and plot layout. | Convert candidate rows to modeled definitions. |
| SUB-DPS-003 | DPS | DPS v0.1/v0.2 are not detailed to the same level as v1.0. | Earlier delivery versions are acknowledged but not fully defined under `DPS/MBSE/tests/`. | Add version-specific DPS gates if v0.1/v0.2 must be closed. |
| SUB-DPS-004 | DPS | DPS/OBCC payload field blocker closed. | The obsolete RH dashboard/frame field was removed from the controlled OBCC table and DPS dashboard artifacts. | Keep broader payload-schema/versioning control under `SYS-BLK-004`. |
| SUB-DPS-005 | DPS | Dashboard requirement/model blocker closed. | The selected top-left dashboard model renders CanSat attitude from pitch/roll/yaw. | Altitude remains a two-dimensional telemetry plot/value; detailed UI oracle definition remains part of DPS candidate-definition work. |
| SUB-OBCC-001 | OBCC | OBCC has broad gate coverage from v0.1 through v1.0 final closure. | Coverage includes startup health, buses/getters, telemetry, command/state, deployment gate, runtime faults, RTOS allocation, workmanship, mission rehearsal, and final review. | Execute and link evidence to final closure. |
| SUB-OBCC-002 | OBCC | OBCC v0.x source-baseline absence is dispositioned as a lifecycle/modeling non-issue. | Versions may jump from v0.x to v1.0; OBCC's mostly software-dependent scope did not require incremental source-model deliveries, so v0.x gates use v1.0 model copies as target context only. | Do not fabricate v0.x source baselines; reports must identify actual code/configuration baselines and target-context-only model references where applicable. |
| SUB-OBCC-003 | OBCC | OBCC final pass depends on mission rehearsal evidence. | `OBCC-V10-FLIGHT-001` forbids final PASS if `OBCC-V09-GATE-001` is unresolved. | Execute mission rehearsal or record approved defer/hold. |
| SUB-OBCC-004 | OBCC | Payload/radio/emergency/fault details remain open. | Exact payload schema, radio settings, emergency-deploy policy, safe fault matrix, firmware IDs, and execution configuration identifiers beyond the selected `RFM96W`/`ICM20948`/`BME280` names need confirmation. | Freeze as-tested configuration before execution. |
| SUB-PDS-001 | PDS & ESS | PDS/ESS has strong coverage across v0.1, v0.2, v0.3, and v1.0. | Coverage includes power path, charge, endurance, protection probability, rails, supervision, physical inspection, and PCB DFM. | Execute with strict safety controls. |
| SUB-PDS-002 | PDS & ESS | Battery architecture conflict is closed. | PDS/ESS README, BOM, and MBSE/tests now align on `1S1P Li-Ion`; this does not close remaining PDS power/safety blockers. | Maintain the selected architecture in execution reports and close the remaining non-battery PDS blockers before final power acceptance. |
| SUB-PDS-003 | PDS & ESS | Regulator efficiency is not clearly tested. | README requires 3.3 V and 5 V rails at 1 A with 95% efficiency; MBSE rail tests focus voltage/current, not efficiency. | Add efficiency measurement or update requirement. |
| SUB-PDS-004 | PDS & ESS | INA219 I2C CE is missing from source logical view. | Tests document this as a blocker/gap for final CE completeness. | Update source model or justify with controlled waiver. |
| SUB-PDS-005 | PDS & ESS | Master switch and On-mode load profile are unresolved. | Final endurance and safety acceptance depend on campaign-defined load/current budget and switch/accessibility semantics. | Freeze load profile and switch/interface details. |
| SUB-PDM-001 | PDM | PDM v0.1 fall-test and v0.2 BLE/manual deployment definitions exist, and v1.0 IMU-triggered deployment has one detailed definition. | PDM still has many v1.0 candidate rows pending. | Define remaining v1.0 PC/PL, CE, allocation, and constraint activities. |
| SUB-PDM-002 | PDM | v1.0 terminal descent-speed requirement is not explicit. | Historical v0.1 uses `11 m/s max`, but v1.0 plan says descent-speed requirement confirmation is blocked. | Define v1.0 descent-speed limit and test. |
| SUB-PDM-003 | PDM | Emergency-deploy policy is not explicit. | Lost observability behavior and interaction with OBCC/PDM are open. | Define emergency policy with OBCC/ADS/PDM ownership. |
| SUB-PDM-004 | PDM | Servo status semantics are unclear. | Trigger → PDM Processing status semantics need confirmation. | Define feedback/status oracle for deployment success/failure. |
| SUB-SAA-001 | S&A | S&A has strong physical/mechanical definitions for v0.1 and v1.0. | Covers PC/PL, integrated fit, envelope/mass, modules, backplane, printing, retention, and deployment clearance. | Execute on final as-flown article. |
| SUB-SAA-002 | S&A | Baseline logical/CE/allocation model is absent. | CE/allocation activities are necessarily gap analyses or require cross-reference to subsystem models. | Add S&A interface/ownership model or formal cross-references. |
| SUB-SAA-003 | S&A | Drop/vibration/landing levels are unresolved. | Several S&A tests include hold paths if tailored levels are not approved. | Approve environmental screen levels, surfaces, orientations, and success criteria. |
| SUB-SAA-004 | S&A | Height and mass interpretation needs authority confirmation. | Model uses 122 mm height; references may be stricter. Mass `<350 ±0.1 g` is interpreted conservatively but needs approval. | Confirm final envelope and mass acceptance policy. |

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
| GAP-004 | Payload schema | The DPS/OBCC RH field mismatch is closed; broader schema versioning, timestamps, units and freshness/error markers still need project-level control. | Freeze payload schema and dashboard behavior. |
| GAP-005 | Deployment policy | OBCC/PDM emergency deployment and descent observability policies are not fully specified. | Define cross-subsystem safety policy. |
| GAP-006 | Power efficiency | README 95% regulator efficiency is not clearly verified. | Add efficiency test or change requirement. |
| GAP-007 | Full-system transients | Servo actuation, RF TX current, brownout and reset behavior need system-level verification beyond subsystem bench tests. | Add `SYS-POWER-ENDURANCE-TRANSIENT`. |
| GAP-008 | Software configuration | Build reproducibility, firmware commits, payload schema versioning, and toolchain control are required in reports but not unified across subsystems. | Create project-level configuration-control checklist. |
| GAP-009 | Mechanical environment | Final drop/vibration/landing levels and post-environment regression are not controlled. | Approve environmental screen plan. |
| GAP-010 | Documentation/workshop | Root README administrative and educational deliverables are not tested. | Add documentation and workshop readiness tests. |
| GAP-011 | Statistical claims | Several tests correctly label screening evidence, but final reliability/PDR/deadline claims require defined samples and independence. | Enforce `PM&SE/IVV.md` statistical policy in final closure. |
| GAP-012 | Source baselines | OBCC v0.x source-view absence is dispositioned as a non-blocking lifecycle/modeling decision; S&A has only physical views; PDM has several candidate-only v1.0 tests. | Preserve target-context/reporting caveats for OBCC, avoid over-crediting, and separately address S&A/PDM model maturity. |

## 6. Testing-strategy consistency assessment

| ID | Point | Assessment | Required action |
|---|---|---|---|
| STRAT-001 | IADT coverage | ADS, AMS, PDS/ESS, S&A, and OBCC generally implement Inspection/Analysis/Demonstration/Testing well. | Continue using `PM&SE/IVV.md` as common policy. |
| STRAT-002 | Definition maturity | DPS and PDM lag behind the other subsystems in detailed definition completeness. | Prioritize detailed definition completion for DPS and PDM. |
| STRAT-003 | Version handling | Some subsystems have actual v0.x MBSE views; OBCC v0.x gates are target-context-only by accepted lifecycle decision rather than by an open blocker. | Do not compare OBCC v0.x gates as source-backed gates; execution reports must identify the actual code/configuration baselines used. |
| STRAT-004 | Fault hardening | OBCC, ADS, and PDS/ESS have strong explicit fault-hardening. DPS and PDM need more detailed fault definitions; S&A needs approved environment levels. | Add/complete fault matrices and environmental levels. |
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
| ACT-003 | Resolve remaining requirement/model conflicts: DPS detailed UI oracles, implementation of the selected ADS/AMS freshness updates, PDM descent speed, and any unresolved execution configuration details; preserve closed selections for `1S1P Li-Ion`, `RFM96W`, `ICM20948`, and `BME280`. | PM&SE configuration control. |
| ACT-004 | Complete detailed definitions for DPS candidate rows and PDM v1.0 candidate rows. | DPS and PDM owners. |
| ACT-005 | Define final mission-window duration, allowable gaps, timing tolerances, and payload schema. | OBCC/DPS/PM&SE. |
| ACT-006 | Add/model the selected `AMS-V10-TEMP-RESPONSE-60S`, `AMS-V10-DATA-FRESHNESS`, and `ADS-V10-DATA-FRESHNESS` paths, plus ADS acceleration, ADS north heading, and PDS efficiency tests. | Respective subsystem owners. |
| ACT-007 | Build a lab equipment availability matrix from §7 with asset IDs and calibration status. | Lab / PM&SE. |
| ACT-008 | Add documentation/workshop readiness tests to close root `README.md` administrative and educational requirements. | Workshop / PM&SE. |
| ACT-009 | Execute subsystem tests and store reports under the modeled `results/<activity-id>/` paths. | Subsystem owners. |
| ACT-010 | Execute final system readiness review only after subsystem reports, deviations, waivers, and residual risks are indexed. | Final review board. |
