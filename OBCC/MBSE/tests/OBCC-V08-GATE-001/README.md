# OBCC-V08-GATE-001 — PCB/backplane/link workmanship advancement gate

## Scope and selected version

- **Activity ID:** `OBCC-V08-GATE-001`
- **SSIV / version gate:** OBCC `v0.8 -> v0.9`
- **Chosen pending activity for this session:** Issue 008, PCB/backplane/link workmanship and integration inspection before final mission rehearsal.
- **IADT method(s):** Inspection + Analysis + Demonstration.
- **IVV source categories:** component/link, component exchange, allocation, functional chain/scenario, constraint.
- **Traceability targets:** integration/build readiness, `OBCC-FE-LostTelemetry`, `OBCC-FE-NonDeployment`, `OBCC-FE-SchedulerBlocked`.
- **Existing v1.0 candidate mapping:** `OBCC-VV-PC-001`, `OBCC-VV-PL-001`, and physical/protocol aspects of `OBCC-VV-CE-001`.
- **Expected evidence/report path:** `OBCC/MBSE/tests/results/OBCC-V08-GATE-001/`.
- **Execution status:** modeled definition complete; execution and evidence report pending.

The absence of a `v0.8` Capella/D2 source baseline is an accepted OBCC lifecycle/modeling decision, not a blocker: versions may jump from `v0.x` to `v1.0`, and the mostly software-dependent subsystem was not complex enough to require incremental source-model deliveries. This definition uses copied `v1.0` physical, logical, functional-allocation, and functional-chain views only as target-behavior context for the `v0.8 -> v0.9` advancement gate; execution reports must identify the actual `v0.8` code/configuration baseline used and acknowledge the target-context-only model reference where applicable. Do not fabricate a `v0.8` source baseline.

## References

- Project IVV: `PM&SE/IVV.md`
- OBCC requirements and PCB-inspection verification context: `OBCC/README.md`
- LoRa/peripheral context: `OBCC/LoRa_Frame.md`
- Getter/result-code and bus bring-up context: `OBCC/Variable_Getter_Template.md`
- Test planning inventory: `OBCC/MBSE/tests/README.md`
- Source context copied from: `OBCC/MBSE/v1.0/`

## Baseline/source-view copies

Copied source context is under `source_views/v1.0/` and includes the v1.0 README plus all eight source D2 views and rendered PNGs. There is no `source_views/v0.8/` per the accepted lifecycle disposition; the `v1.0` copies are target context only.

## Verification-specific diagram catalogue

| View | D2 | Rendered PNG | Purpose |
|---|---|---|---|
| PV1 physical setup | `OBCC-V08-GATE-001_view1_workmanship_physical_setup.d2` | `OBCC-V08-GATE-001_view1_workmanship_physical_setup.png` | UUT, OBCC PCB, XIAO/RFM96W/antenna path, integration-context BME280/ICM20948/UBX-G7020/INA219, backplane headers, servo cable/fixture, ground-station context, microscope, DMM, RF checker, retention fixture, evidence camera, bench power/USB, ambient thermometer, and physical pass/fail constraints. |
| PV2 logical interfaces | `OBCC-V08-GATE-001_view2_workmanship_logical_interfaces.d2` | `OBCC-V08-GATE-001_view2_workmanship_logical_interfaces.png` | Component-exchange and allocation analysis for I2C/UART/SPI/PWM/power/ground/USB/LoRa/header-mating links, including verification-only harness interfaces and analysis constraints. |
| PV3 functional allocation | `OBCC-V08-GATE-001_view3_workmanship_functional_allocation.d2` | `OBCC-V08-GATE-001_view3_workmanship_functional_allocation.png` | Human/operator functions, test-equipment functions, and verification-only UUT functions for inspection, continuity/polarity, RF safety, connector retention, protocol bring-up, evidence indexing, and pass/fail classification. |
| Functional chain — workmanship gate | `OBCC-V08-GATE-001_view4_workmanship_gate_chain.d2` | `OBCC-V08-GATE-001_view4_workmanship_gate_chain.png` | End-to-end inspection/analysis/demonstration sequence from UUT/source-context selection through visual inspection, DMM checks, RF safety, current-limited power, protocol bring-up, evidence capture, oracle comparison, and advancement decision. |

All four verification D2 files were rendered with the required `d2 --layout=elk` command and ELK spacing flags; `d2` reported successful compilation for every PNG.

## Verification coverage table

| Verification activity ID | SSIV / development version | Model element(s) covered | IVV source category | IADT method | Traceability target | Relevant viewpoints: statistical significance and fault hardening | Pass/fail constraint(s) | Diagram/report references | Status |
|---|---|---|---|---|---|---|---|---|---|
| `OBCC-V08-GATE-001-I01` | v0.8 -> v0.9 | OBCC Module/PCB, XIAO ESP32-S3 footprint, RFM96W footprint, LoRa antenna path, OBCC/backplane connectors, ADS/AMS/PDS/ESS/PDM headers, BME280/ICM20948/UBX-G7020/INA219 context devices, servo cable/fixture, USB-C bench link, ground-station physical context, microscope/visual inspector, evidence camera | Component/link; constraint | Inspection | Integration/build readiness; `OBCC-FE-LostTelemetry`; `OBCC-FE-NonDeployment` | Stat: 100% visual/presence/orientation/workmanship inspection of every modeled gate element on the article. Fault hardening: missing component, wrong orientation, solder bridge, contamination, damaged footprint, unsafe substitution, or undispositioned ownership/context item blocks advancement. | `PF-001`, `PF-002`, `PF-006`, `PF-008` | PV1, PV3, gate chain; expected report `results/OBCC-V08-GATE-001/inspection_workmanship.md` | Definition ready; execution pending |
| `OBCC-V08-GATE-001-A01` | v0.8 -> v0.9 | I2C/UART/SPI/PWM/power/ground/USB/LoRa/header-mating component exchanges; XIAO host, RFM96W SPI/RF interface, OBCC header interface, backplane connector matrix, sensor/power endpoints, ground-station evidence context, verification-only harness allocation | Component exchange; allocation; constraint | Analysis | `OBCC-FE-SchedulerBlocked`; `OBCC-FE-LostTelemetry`; `OBCC-FE-NonDeployment`; physical/protocol aspects of `OBCC-VV-CE-001` | Stat: 100% CE-by-CE and allocation review against copied v1.0 intent; no reliability inference. Fault hardening: wrong bus topology, wrong pull-up/address/chip-select, voltage mismatch, missing ground reference, unmodeled bypass, hidden foreign function, or v0.8/v1.0 difference without disposition is a failure/deviation. | `PF-003`, `PF-007`, `PF-008` | PV2, PV3, gate chain; expected report `results/OBCC-V08-GATE-001/interface_allocation_analysis.md` | Definition ready; execution pending |
| `OBCC-V08-GATE-001-D01` | v0.8 -> v0.9 | Power rails, ground references, adjacent pins, SPI/I2C/UART/PWM traces, USB-C bench link, backplane header pins, servo connector/cable, DMM probe points | Component/link; constraint | Demonstration | `OBCC-FE-SchedulerBlocked`; `OBCC-FE-NonDeployment` | Stat: 100% continuity/polarity/no-short demonstration for modeled workmanship-critical links on the gate article. Fault hardening: any unmodeled short, open circuit, reversed polarity, floating ground, loose deployment link, or unrepeatable reading is a gate failure until corrected/dispositioned. | `PF-003`, `PF-005`, `PF-008` | PV1, PV3, gate chain; expected report `results/OBCC-V08-GATE-001/continuity_polarity_demo.md` | Definition ready; execution pending |
| `OBCC-V08-GATE-001-D02` | v0.8 -> v0.9 | RFM96W SPI link, antenna path, RF checker/dummy load, safe low-power LoRa bring-up, ground-station physical context, ground USB/PC evidence, telemetry/link trace | Component exchange; component/link; functional chain/scenario; constraint | Demonstration | `OBCC-FE-LostTelemetry`; integration/build readiness | Stat: one-gate safe bring-up demonstration unless repetitions and independence are justified. Fault hardening: no LoRa TX without antenna/dummy-load safety; open antenna path, absent RF evidence, inconsistent ground-station link, or unsafe RF substitution is a failure/deviation. | `PF-004`, `PF-007`, `PF-008` | PV1, PV2, PV3, gate chain; expected report `results/OBCC-V08-GATE-001/rf_ground_bringup_demo.md` | Definition ready; execution pending |
| `OBCC-V08-GATE-001-D03` | v0.8 -> v0.9 | Backplane header mating, connector retention/keying, PDM servo connector, servo cable/fixture, retained deployment link evidence, retention fixture | Component/link; constraint | Inspection + Demonstration | `OBCC-FE-NonDeployment`; integration/build readiness | Stat: 100% connector/retention/keying checks for modeled mechanical links. Fault hardening: loose header, mis-keyed connector, intermittent servo cable, unretained deployment link, or fixture movement beyond acceptance blocks advancement. | `PF-002`, `PF-005`, `PF-008` | PV1, PV2, PV3, gate chain; expected report `results/OBCC-V08-GATE-001/connector_retention_demo.md` | Definition ready; execution pending |

## Pass/fail constraints

- **PF-001 — source and setup identity:** UUT hardware revision, PCB/backplane revision, firmware/configuration IDs, copied v1.0 source-context references, test equipment identities, accepted v0.8 target-context caveat, and actual code/configuration baseline are recorded before pass/fail classification.
- **PF-002 — component/link presence and workmanship:** 100% of modeled physical components and physical links in the gate are present, correct, oriented, seated, soldered/worked acceptably, and dispositioned as OBCC-owned or integration context. Missing, reversed, substituted, unseated, bridged, damaged, contaminated, or undispositioned elements fail unless formally waived with corrective action.
- **PF-003 — electrical continuity, polarity, and protocol intent:** no unmodeled shorts; power/ground references, SPI, I2C, UART, PWM, USB-C bench link, backplane headers, and servo links pass continuity/polarity checks and align with modeled direction, voltage, addressing/chip-select, and bus topology intent.
- **PF-004 — RF/antenna safety:** RFM96W footprint and antenna path are inspected and checked before any transmit attempt. LoRa TX occurs only with verified antenna or dummy load; open/unsafe antenna path is a failure before bring-up.
- **PF-005 — mechanical connector and deployment-link retention:** backplane headers, OBCC connector, subsystem headers, PDM servo connector, servo cable, and fixture retain, key, and seat correctly; no loose or intermittent deployment/telemetry link is accepted.
- **PF-006 — evidence completeness:** microscope/visual records, photos/video, DMM readings with probe locations, RF checker status, retention-fixture results, power/current records, USB/protocol bring-up logs, and ground-station evidence are indexed to UUT and step IDs.
- **PF-007 — exchange/allocation analysis:** implemented links/exchanges are consistent with copied v1.0 intent for I2C, UART, SPI, PWM, power/ground, LoRa, USB bench evidence, and header mating; no hidden bypass or foreign allocation is needed to pass the gate; v0.8/v1.0 differences are listed as assumptions/deviations.
- **PF-008 — environmental/statistical interpretation:** ambient thermometer model/serial/reading, bench current limit, RF load state, as-tested wiring, and evidence path are recorded. This is 100% inspection and gate-article demonstration, not a reliability claim; repeated measurements are screening unless independence is justified.

## Statistics and fault-hardening viewpoints

- This is a `v0.8 -> v0.9` advancement gate, not final v1.0 flight-readiness closure.
- Statistical significance is by exhaustive gate coverage: every modeled workmanship-critical component, physical link, and physical/protocol component exchange in this definition is inspected/analyzed/demonstrated on the article. No PDR, timing, or reliability claim is made from this gate alone.
- If repeated continuity/bring-up readings are taken, the execution report shall state whether they are independent. Otherwise they are advancement screening evidence only.
- Fault-hardening emphasis: solder bridges, opens, shorts, reversed polarity, missing ground, wrong bus topology, wrong I2C address/pull-up/chip-select, unsafe LoRa antenna path, loose backplane/header mating, loose servo/deployment link, unsafe substitution, USB bench path mistaken as flight operator path, and undispositioned v0.8/v1.0 source differences.
- Forbidden events for this gate include energizing with unresolved shorts, transmitting with unsafe antenna path, advancing with a loose deployment link, accepting a missing/incorrect modeled PC/PL without waiver, or claiming CE/protocol conformance without evidence.

## Candidate mapping and coverage notes

- **`OBCC-VV-PC-001`:** modeled by `OBCC-V08-GATE-001-I01` and supported by `D01/D03`, covering 100% presence/orientation/workmanship evidence for OBCC PCB/backplane/ground-context components and integration-context devices named in the issue.
- **`OBCC-VV-PL-001`:** modeled by `OBCC-V08-GATE-001-I01/D01/D03`, covering electrical continuity/polarity, RF/antenna path safety, USB-C bench link, header mating, servo cable/fixture, and connector retention/keying.
- **Physical/protocol aspects of `OBCC-VV-CE-001`:** modeled by `OBCC-V08-GATE-001-A01/D01/D02`, covering I2C/UART/SPI/PWM/power/ground protocol intent and safe bring-up evidence. This activity does **not** replace the broader software/runtime CE closure for all of `OBCC-VV-CE-001`.
- Related functional-chain coverage is limited to the workmanship gate sequence; it is not the v0.9 mission-window rehearsal or final v1.0 regression.

## Assumptions and gaps for feedback

- Lifecycle disposition: no `v0.8` Capella/D2 source baseline is required or fabricated; copied v1.0 views are target context only, and the report identifies the actual v0.8 code/configuration baseline.
- The exact v0.8 PCB revision, backplane revision, antenna connector/antenna or dummy-load model, connector-retention load/acceptance values, and DMM/RF-checker equipment models are not controlled in the repository artifacts read here.
- The source context and `LoRa_Frame.md` use the selected `RFM96W` radio and `ICM20948` IMU names; execution must still record the actual fitted hardware and configuration baseline.
- USB-C is modeled only as a bench evidence/power path for this v0.8 gate; it is not a required v1.0 flight operator path.
- Detailed solder/workmanship workmanship standard or microscope magnification threshold is not specified in the repository; the execution report must state the applied shop/workshop acceptance convention or waiver basis.
- This was a non-interactive subagent run; needed feedback is captured here instead of requested live.
