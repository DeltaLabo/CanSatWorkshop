# AMS multi-version IVV-aligned verification plan

Planning artifact for the Capella/D2 views in `AMS/MBSE/`. The model remains the source of truth; modeled test definitions and execution records are organized under this `tests/` folder.

Project-wide IVV conventions, evidence paths, statistical policy, fault semantics, and report-by-reference rules are defined in [`../../../PM&SE/IVV.md`](../../../PM&SE/IVV.md). Evidence for any activity below should be stored under `results/<activity-id>/` in this `tests/` folder unless a campaign-level folder is later agreed.

## 1. SSIV / development-version assumptions

- **AMS v0.1:** breadboard/subsystem baseline. Tests support advancement to the v0.2 PCB-delivery baseline.
- **AMS v0.2:** PCB-delivery baseline. Tests support advancement to the v1.0 integrated flight-readiness baseline.
- **AMS v1.0:** final acceptance / flight readiness baseline.
- The only version directories present under `AMS/MBSE/` are `v0.1`, `v0.2`, and `v1.0`; this plan treats them as the controlled AMS development baselines.
- Current AMS v1.0 source D2 includes use-case/feared-event notes; v0.1/v0.2 traceability labels may remain provisional project-level labels derived from model intent and IVV fault semantics. Those provisional labels are controlled by this plan and the current system requirement-to-test matrix; no execution credit is claimed by this Markdown update.
- Shared ADS/AMS freshness contract: [`../../../PM&SE/contracts/sensor_obcc_freshness_contract.md`](../../../PM&SE/contracts/sensor_obcc_freshness_contract.md) governs AMS-to-OBCC delivery planning. AMS shall support OBCC request/response at `5 Hz` (`200 ms` period); each `2 s` LoRa telemetry push treats AMS data as fresh only when `status == VALID` and `age_ms <= 400 ms`; the exact status enum is `VALID`, `STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, `INIT_FAIL`; timeout, runtime fault, initialization failure, and no-data conditions shall not leave old data marked `VALID`.
- Fault semantics from project IVV: a BME280 startup failure is treated as a critical startup fault; runtime getter/sensor failures shall return bounded error/result codes and shall not block the scheduler.
- AMS `v0.2` PCB-ready non-issue: per `AMS-BLK-003`, `v0.2` was the PCB delivery baseline only. `AMS-V02-PCB-001` and `AMS-V02-BRINGUP-001` may demonstrate PCB/build and powered reachability over the modeled physical path, but no native `v0.2` logical, CE, allocation, or functional-chain closure is required unless a future controlled decision adds those source views.

## 2. Views read

### v0.1

- `AMS_v0.1_view1_physical.d2`: BME280, XIAO ESP32, host PC, I2C/3V3/GND/USB links.
- `AMS_v0.1_view2_logical.d2`: AMS Sensing, AMS Processing, and I2C CE.
- `AMS_v0.1_view3_functional_allocation.d2`: sensing, processing, collection, Serial0 logging functions, and timing/accuracy/getter constraints.
- `AMS_v0.1_view4_atmospheric_measurement_chain.d2`: pressure/temperature measurement, processing, and collection chain.
- `AMS_v0.1_view5_peripheral_initialisation_chain.d2`: BME280 init-state collection chain.
- `AMS_v0.1_view6_serial_logging_chain.d2`: collected init-state and measurement payload logging over Serial0.

### v0.2

- `AMS_v0.2_view1_physical.d2`: AMS PCB, BME280, backplane connector, footprints, I2C + 3V3 traces, and manufacturing/soldering constraint.

### v1.0

- `AMS_v1.0_view1_physical.d2`: physical components, physical links, and sunlight/airflow physical constraint.
- `AMS_v1.0_view2_logical.d2`: logical components, I2C and pointer/return component exchanges, and software implementation constraints.
- `AMS_v1.0_view3_functional_allocation.d2`: functions allocated to AMS Sensing, AMS Processing, and OBCC with measurement constraints.
- `AMS_v1.0_view4_atmospheric_measurement_chain.d2`: atmospheric measurement functional chain.
- `AMS_v1.0_view5_peripheral_initialisation_chain.d2`: BME280 initialisation-state functional chain.

## 3. Reference set used

No new external research was performed. References are the existing corpus in `tests/references/` plus the project IVV plan.

| Ref ID | Local source |
|---|---|
| IVV | `../../../PM&SE/IVV.md` |
| AMS-R1 | Bosch Sensortec BME280 datasheet/product artifacts in `references/sources/` |
| AMS-R2 | NXP/Nexperia UM10204 I2C specification artifacts in `references/sources/` |
| AMS-R3 | ISO 7726 and WMO-No. 8 thermal/meteorological measurement artifacts |
| AMS-R4 | ICAO Doc 7488 / standard-atmosphere artifacts |
| AMS-R5 | JCGM 100 GUM and NIST/SEMATECH statistics artifacts |
| AMS-R6 | CanSat mission/environmental guide artifacts |
| AMS-R7 | Ranđelović et al. low-cost altitude-sensor artifact |

## 4. Planning inventory from the model

### 4.1 AMS v0.1 inventory

- **Physical context:** `[System] AMS v0.1 Subsystem`; `[PC] BME280`; `[PC] XIAO ESP32`; external `[EA] PC`.
- **Physical links:** I2C Cables, 3V3, GND, USB-C Cable.
- **Component exchanges:** `[CE] I2C` between AMS Sensing and AMS Processing.
- **Logical components/functions:** AMS Sensing (`Measure pressure`, `Measure temperature`, `Respond to I2C Requests`); AMS Processing (`Get BME280 init state`, `Read pressure`, `Read temperature`, `Calculate altitude`, `Process temperature`, `Collect peripheral init states`, `Collect measurements`, `Init Serial0 and Serial1 with interrupts`, `Log via Serial0`).
- **Functional chains/scenarios:** atmospheric measurement, peripheral initialisation, serial logging.
- **Constraints:** pressure accuracy `±1 hPa`; temperature accuracy `±0.5 °C` over `10–40 °C`; temperature response `≤60 s` (closed only by a definition with t0/final/reference/correlation); altitude resolution `≤10 m` using `13 Pa/m = 130 Pa`; variable-getter template; I2C timeout `≤5 ms`; process/calculate `<5 ms`; no blocking besides I2C/UART.

### 4.2 AMS v0.2 inventory

- **Physical context:** `[System] AMS v0.2 PCB Delivery`.
- **Physical components:** `[PC] AMS PCB`; `[PC] BME280`; `[PC] Backplane Connector`.
- **Physical links:** BME280 footprint; connector footprint; I2C + 3V3 traces.
- **Constraints:** manufacturable in a Carvera Air CNC and soldered by reflux or manually.
- **Model gap:** no v0.2 logical, CE, allocation, or functional-chain views are currently modeled; powered bring-up activities therefore add VV-only test actors/functions around the physical baseline.

### 4.3 AMS v1.0 inventory

- **Physical components:** CanSat; AMS Module; AMS PCB; BME280; AMS-side Backplane Connector; Backplane PCB; 2mm 2x6 AMS Headers; Spine; 2mm 2x6 OBCC Headers; OBCC Module; OBCC PCB; XIAO ESP32-S3; OBCC-side Backplane Connector.
- **Physical links:** AMS PCB screws; OBCC PCB screws; AMS module backplane fixture; OBCC module backplane fixture; BME280 footprint; AMS connector footprint; AMS I2C + 3V3 traces; AMS parallel connector; XIAO footprint; OBCC connector footprint; OBCC I2C + 3V3 traces; OBCC parallel cable; AMS header footprint; OBCC header footprint.
- **Component exchanges:** `[CE] I2C`, `[CE] Pointers`, `[CE] Returns`.
- **Logical components/functions:** AMS Sensing (`Measure pressure`, `Measure temp.`, `Respond to I2C Requests`); AMS Processing (`Get BME280 init state`, `Read pressure`, `Read temperature`, `Calculate altitude`, `Process temperature`); OBCC (`Collect peripheral init states`, `Collect measurements`).
- **Functional chains/scenarios:** atmospheric measurement; peripheral initialisation.
- **Constraints:** block sunlight while allowing airflow; variable-getter template; all I2C read functions timeout `≤5 ms`; all process/calculate functions `<5 ms`; no blocking operations besides I2C or UART comms; pressure accuracy `±1 hPa`; temperature accuracy `±0.5 °C` over `10–40 °C`; temperature response `≤60 s`; altitude resolution `≤10 m` using `13 Pa/m = 130 Pa`.

## 5. Verification activities

### 5.1 AMS blocker alignment definitions/update paths

These rows align the AMS test package with the AMS blocker closure record. Existing freshness/status/API definition extensions are now represented in the affected READMEs and D2 test-definition views; no execution credit is claimed until reports bind evidence to those modeled definitions.

| Definition / update ID | Selected path | Complete oracle and predeclared evidence expectations | Current status |
|---|---|---|---|
| `AMS-V10-TEMP-RESPONSE-60S` | Standalone model-defined activity in `tests/AMS-V10-TEMP-RESPONSE-60S/`; may also be referenced from `AMS-VV-FC-001` response-time discussion. | Apply a declared temperature step; define final/reference condition and response-time calculation; verify reported temperature reaches the defined condition within `<=60 s`; predeclare and retain raw AMS timestamps/data, synchronized or monotonically correlated reference thermometer data, stable thermal source/chamber or fixture description, UUT/firmware/configuration IDs, sunlight/airflow exposure state, uncertainty/deviation notes, and calculation script/version. | Model-defined; execution/report pending. |
| `AMS-V10-DATA-FRESHNESS` | Model-defined activity in `tests/AMS-V10-DATA-FRESHNESS/` plus explicit coverage through `AMS-VV-API-001`, `AMS-VV-FC-001`, `AMS-VV-FC-002`, `AMS-VV-CON-003`, and `AMS-VV-CON-004`. | Use the shared contract: `5 Hz` OBCC request/response (`200 ms` nominal), separate `2 s` LoRa telemetry packaging, fresh only when `status == VALID` and `age_ms <= 400 ms`, exact enum `VALID`/`STALE`/`NO_DATA`/`TIMEOUT`/`SENSOR_FAULT`/`INIT_FAIL`, timestamp/sequence/sample-ID/age evidence at the AMS-to-OBCC observation point, and no timeout/fault/init/no-data/stale condition leaving old/default/previous samples marked `VALID`. | Model-defined; execution/reporting remains pending. |

The two `AMS-V10-*` folders above already exist in this working tree as current model-defined blocker-alignment definitions. They are not unstarted phase-planned rows from the original orchestration table, and this legacy/gate update only indexes them; it does not edit their folder contents.

Both AMS blocker-alignment activities above are now model-defined. Execution/report evidence remains pending; no AMS activity remains planning-level work.

### 5.2 Modeled activity table

Activities below are model-defined unless their status says otherwise. Detailed execution reports should reference the model definition rather than duplicate it.

| Verification activity ID | SSIV / version | Model element(s) covered | IVV source category | IADT method | Traceability target | Relevant references | Viewpoints: statistical significance and fault hardening | Preliminary pass/fail criteria or constraint sources | Expected diagram/report location | Status |
|---|---|---|---|---|---|---|---|---|---|---|
| AMS-V01-INTEG-001 | AMS v0.1 advancement gate to v0.2 PCB delivery | v0.1 BME280, XIAO ESP32, host PC, I2C/3V3/GND/USB links, AMS Sensing/Processing, `[CE] I2C`, allocated sensing/processing/collection/serial functions, and v0.1 constraints as readiness evidence. | Component/link; component exchange; allocation; constraint readiness | Inspection with supporting Analysis | `AMS-v0.1-to-v0.2-readiness`; `AMS-UC-MeasureAtmosphere`; `AMS-UC-InitializePeripheral`; `AMS-FE-SensorBusFault` | IVV, AMS-R1, AMS-R2, AMS-R6 | Stat: 100% census of v0.1 readiness items, no reliability claim. Fault hardening: wrong/missing item, wrong pin, open/short/reversal, loose jumper, wrong I2C role/protocol/address, unmodeled bypass, missing bounded-timeout/non-blocking policy evidence. | Pass iff all target PCs/actors and PLs are present/correct, 3V3/GND/I2C/USB links have correct endpoints/polarity and no open/short/reversal/bypass, I2C CE endpoint/protocol/direction analysis is consistent, no foreign function allocation exists, and evidence is sufficient to convert links into v0.2 PCB traces/connectors. | Model definition: `tests/AMS-V01-INTEG-001/`; report/evidence: `tests/results/AMS-V01-INTEG-001/`; expected report: `tests/results/AMS-V01-INTEG-001/report.md` | Model-defined; execution/report pending |
| AMS-V01-FC-001 | AMS v0.1 readiness gate to v0.2 PCB delivery | v0.1 atmospheric measurement, peripheral initialisation, and serial logging chains; pressure/temp/altitude/timing/no-blocking/variable-getter constraints. | Functional chain/scenario; constraint | Testing / Demonstration | `AMS-v0.1-to-v0.2-readiness`; `AMS-UC-MeasureAtmosphere`; `AMS-UC-InitializePeripheral`; `AMS-UC-LogSerialTelemetry`; `AMS-FE-SensorBusFault` | IVV, AMS-R1, AMS-R2, AMS-R3, AMS-R4, AMS-R5, AMS-R6 | Stat: `n ≥ 30` stable paired pressure/temperature samples at the breadboard characterization point with bias/std/CI/U; serial/init smoke `≥5` nominal repetitions as screening. Fault hardening: stale/old/default data, swapped/missing fields, missing init state, sensor-bus non-response symptoms, unbounded blocking. | Pass iff paired pressure and temperature errors plus uncertainty meet `±1 hPa` and `±0.5 °C over 10–40 °C`, altitude resolution is demonstrated as `≤10 m` using `13 Pa/m = 130 Pa` or recorded as a readiness limitation, temperature-response `≤60 s` is not claimed unless derived from `AMS-V10-TEMP-RESPONSE-60S` or an execution annex with t0/final/reference/correlation, Serial0 includes init state and measurement fields in expected order/units with no stale/old/default current sample, modeled timing constraints are met or explicitly derived from `AMS-VV-CON-003`, and no unbounded blocking occurs during nominal logging. | Model definition: `tests/AMS-V01-FC-001/`; report/evidence: `tests/results/AMS-V01-FC-001/`; expected report: `tests/results/AMS-V01-FC-001/report.md` | Model-defined; execution/report pending |
| AMS-V02-PCB-001 | AMS v0.2 PCB-delivery advancement gate to v1.0 integrated build | v0.2 AMS PCB, BME280, Backplane Connector, BME280 footprint, connector footprint, I2C + 3V3 traces, and manufacturability/soldering constraint. | Component/link; constraint-derived manufacturability/readiness | Inspection with supporting Analysis | `AMS-v0.2-to-v1.0-readiness`; `AMS-UC-MeasureAtmosphere`; `AMS-FE-BadManufacturing`; `AMS-FE-SensorBusFault` | IVV, AMS-R1, AMS-R2, fabrication/rework traveler | Stat: 100% census of one delivered PCB article covering 3 PCs, 3 PLs, and 1 manufacturing constraint. Fault hardening: wrong variant/orientation, pitch mismatch, damage, FOD, solder bridge, lifted pad, open/shorted route, hidden jumper/bypass, traveler mismatch, uncontrolled rework. | Pass iff PCB is the v0.2 baseline with fabrication/rework traceability, components/footprints are present/correct/oriented/undamaged, I2C + 3V3 traces/pads have no visual opens/shorts/unapproved jumpers, and board/soldering evidence is compatible with the modeled manufacturing constraint. | Model definition: `tests/AMS-V02-PCB-001/`; report/evidence: `tests/results/AMS-V02-PCB-001/`; expected report: `tests/results/AMS-V02-PCB-001/report.md` | Model-defined; execution/report pending |
| AMS-V02-BRINGUP-001 | AMS v0.2 advancement gate to v1.0 integrated build | v0.2 AMS PCB, BME280, Backplane Connector, I2C + 3V3 traces, BME280/connector footprints, VV-only connector test access, powered bring-up chain. | Component/link; component exchange; functional chain/scenario; constraint | Demonstration / Testing | `AMS-v0.2-to-v1.0-readiness`; `AMS-UC-MeasureAtmosphere`; `AMS-UC-InitializePeripheral`; `AMS-FE-SensorBusFault` | IVV, AMS-R1, AMS-R2, AMS-R5 | Stat: `3/3` complete power-cycle/read attempts as a bring-up demonstration, not a reliability claim. Fault hardening: overcurrent, reversed power, wrong/no I2C address, NACK-only behavior, stuck SDA/SCL, unmodeled bypass, uncontrolled fixture configuration. | Pass iff the current limit is predeclared from fixture SOP/schematic/build evidence, current-limited 3V3/GND has no short/overcurrent and measures `3.3 V ±5%`, fixture enters through modeled connector/trace path with no bypass, I2C scan finds BME280 at `0x76`/`0x77` per build record, chip ID/status/readback evidence is logged (`0x60` chip ID), logic analyzer shows valid 3V3 I2C ACK/no stuck lines, and `3/3` cycles pass. | Model definition: `tests/AMS-V02-BRINGUP-001/`; report/evidence: `tests/results/AMS-V02-BRINGUP-001/`; expected report: `tests/results/AMS-V02-BRINGUP-001/report.md` | Model-defined; execution/report pending |
| AMS-VV-PC-001 | AMS v1.0 final acceptance | All 13 modeled UUT physical components in v1.0. | Component/link — PC portion | Inspection | AMS physical integration/build readiness; `AMS-UC-MeasureAtmosphere` | IVV, AMS-R1, AMS-R6 | Stat: 100% census inspection, `13/13` target PCs. Fault hardening: missing/wrong PC, wrong variant/location, duplicate-instance confusion, visible damage, FOD, contamination, unapproved substitution. | Pass iff every target PC is present, identifiable, correct for v1.0, installed in modeled containment, and recorded with checklist/photo/build evidence; physical-link integrity remains under `AMS-VV-PL-001`. | Model definition: `tests/AMS-VV-PC-001/`; report/evidence: `tests/results/AMS-VV-PC-001/`; expected report: `tests/results/AMS-VV-PC-001/report.md` | Model-defined; execution/report pending |
| AMS-VV-PL-001 | AMS v1.0 final acceptance | All 14 modeled UUT physical links in v1.0. | Component/link — PL portion | Inspection | AMS physical/electrical integration readiness; `AMS-UC-MeasureAtmosphere`; `AMS-UC-InitializePeripheral`; `AMS-FE-SensorBusFault` | IVV, AMS-R2, AMS-R6 | Stat: 100% census inspection, `14/14` target PLs. Fault hardening: missing/loose link, wrong endpoint/route/cable, open, short, intermittent, connector/cable seating error, solder bridge, lifted pad, bent pin, FOD/contamination, unapproved bypass. | Pass iff every target PL is present, connects modeled endpoints, is installed/routed/seated/soldered as modeled, has applicable visual/retention/continuity/build evidence, and has no unapproved reroute/bypass/temporary jumper/repair/substitution. | Model definition: `tests/AMS-VV-PL-001/`; report/evidence: `tests/results/AMS-VV-PL-001/`; expected report: `tests/results/AMS-VV-PL-001/report.md` | Model-defined; execution/report pending |
| AMS-VV-CE-001 | AMS v1.0 final acceptance | `[CE] I2C` between AMS Sensing and AMS Processing, including pressure/temp/init-state request-response crossings. | Component exchange | Analysis | `AMS-UC-MeasureAtmosphere`; `AMS-UC-InitializePeripheral`; `AMS-FE-SensorBusFault` | IVV, AMS-R1, AMS-R2 | Stat: 100% design/interface analysis of the target CE. Fault hardening: wrong protocol/endpoint/direction/role, address conflict, bus mismatch, pullup/voltage mismatch, unmodeled bypass, NACK, absent BME280, stuck SDA/SCL, clock-stretch/no-response, missing bounded status policy. | Pass iff implementation uses modeled I2C exchange with correct endpoints, requester/responder roles, bus/address, 3V3/pullup/topology intent, bounded fault-policy evidence, and no unmodeled bypass or wrong-protocol substitute; detailed `≤5 ms` proof remains `AMS-VV-CON-003`. | Model definition: `tests/AMS-VV-CE-001/`; report/evidence: `tests/results/AMS-VV-CE-001/`; expected report: `tests/results/AMS-VV-CE-001/report.md` | Model-defined; execution/report pending |
| AMS-VV-API-001 | AMS v1.0 final acceptance / flight readiness | `[CE] Pointers`, `[CE] Returns`, variable-getter template, allocations for AMS Sensing/Processing/OBCC, and modeled getter/collection paths. | Component exchange; allocation; constraint; functional-chain context | Analysis with supporting Inspection | `AMS-UC-MeasureAtmosphere`; `AMS-UC-InitializePeripheral`; `AMS-FE-SensorBusFault`; `AMS-FE-StaleMeasurement`; variable-getter constraint | IVV, model/API-contract analysis, AMS-R1/R2 context | Stat: 100% model/API checklist review; no reliability claim. Fault hardening: null/invalid pointer, ownership/lifetime error, aliasing/concurrency hazard, unit/scaling mismatch, invalid input, stale/no-data, startup/runtime fault, timeout/bus error, unmodeled data crossing, bounded non-blocking propagation. | Pass iff pointer semantics and return statuses are explicit and consistent with variable-getter intent, implementation codes map to the shared enum (`VALID`, `STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, `INIT_FAIL`), stale-valid behavior is forbidden, allocations contain no foreign functions, all LC crossings use modeled `I2C`, `Pointers`, and `Returns`, and 100% of modeled getters/OBCC collection paths plus pointer/null/lifetime/static-review evidence are checked. | Model definition: `tests/AMS-VV-API-001/`; report/evidence: `tests/results/AMS-VV-API-001/`; expected report: `tests/results/AMS-VV-API-001/report.md` | Model-defined; covers CE-002/003, ALLOC-001/002/003, and CON-002 if checklist evidence is complete |
| AMS-VV-FC-001 | AMS v1.0 final acceptance / flight readiness | Atmospheric measurement functional chain, VV acceptance instrumentation/logger access, pressure/temperature/altitude constraints, OBCC currentness/order check. | Functional chain/scenario; constraint | Testing / Demonstration | `AMS-UC-MeasureAtmosphere`; pressure/temperature/altitude constraints; `AMS-FE-BadExposure`; `AMS-FE-StaleMeasurement` | IVV, AMS-R1, AMS-R3, AMS-R4, AMS-R5, AMS-R7 | Stat: `n ≥ 30` paired pressure/temperature samples per operating point; altitude step uses `n ≥ 30` paired samples at P0/P1. Fault hardening: bad exposure, stale/currentness errors, swapped branches, outliers, OBCC order errors, timeout/stale-OK anomalies. | Pass iff pressure `abs(bias)+U95 ≤ 1 hPa`, temperature `abs(bias)+U95 ≤ 0.5 °C` inside `10–40 °C`, 10 m-equivalent pressure change is resolved with correct sign/uncertainty, OBCC collects altitude/temperature in modeled order, any value claimed fresh satisfies the shared contract (`status == VALID`, `age_ms <= 400 ms`), non-valid values carry the shared status, and logging does not bypass the modeled path. | Model definition: `tests/AMS-VV-FC-001/`; report/evidence: `tests/results/AMS-VV-FC-001/`; expected report: `tests/results/AMS-VV-FC-001/report.md` | Model-defined; execution/report pending |
| AMS-VV-FC-002 | AMS v1.0 final acceptance / flight readiness | Peripheral initialisation functional chain, OBCC critical startup-fault/status collection, nominal boot and induced startup-fault chains. | Functional chain/scenario; constraint; component-exchange context | Testing / Demonstration | `AMS-UC-InitializePeripheral`; `AMS-FE-SensorBusFault`; `AMS-FE-StartupFault`; variable-getter/I2C-timeout/no-blocking constraints | IVV, AMS-R1, AMS-R2, AMS-R5 | Stat: `29/29` nominal boot successes for R90/C95 claim; `29/29` per induced startup-fault mode if making that claim. Fault hardening: absent/disconnected BME280, forced NACK, held SDA/SCL, stale/default OK prevention, bounded startup-fault status, startup responsiveness. | Pass iff nominal boot returns a current `VALID` BME280 init state and OBCC collects it before readiness OK; induced startup faults report `INIT_FAIL` or another applicable non-`VALID` shared status with no unbounded blocking; previous/default OK values are never retained as `VALID`; detailed environmental-read timeout proof remains `AMS-VV-CON-003`. | Model definition: `tests/AMS-VV-FC-002/`; report/evidence: `tests/results/AMS-VV-FC-002/`; expected report: `tests/results/AMS-VV-FC-002/report.md` | Model-defined; execution/report pending |
| AMS-VV-CON-001 | AMS v1.0 final acceptance / flight readiness | `[C] Block sunlight, allow airflow` on AMS Module/BME280 installed configuration, exposure geometry, airflow path, optional exposure instrumentation. | Constraint; component/link context; functional chain/scenario | Inspection / Demonstration | Constraint `[C] Block sunlight, allow airflow`; `AMS-FE-BadExposure`; `AMS-UC-MeasureAtmosphere`; temperature-accuracy context | IVV, AMS-R3, AMS-R6, AMS-R5 if paired bias screening is used | Stat: 100% inspection/demonstration of final integrated configuration; optional `n ≥ 30` paired temperature-bias samples only if claiming statistical exposure-bias result. Fault hardening: direct sunlight/bright-lamp line of sight, blocked ventilation, fixture/wire/equipment obstruction, heat soak, unmodeled temporary shielding. | Pass iff no direct solar/bright-lamp line of sight to BME280 exists, airflow path is unobstructed, ambient/reference conditions and photo/video/flow evidence are recorded, and optional paired bias screening satisfies `|bias|+U95 ≤ 0.5 °C`; bad exposure conditions fail unless waived/model-updated. | Model definition: `tests/AMS-VV-CON-001/`; report/evidence: `tests/results/AMS-VV-CON-001/`; expected report: `tests/results/AMS-VV-CON-001/report.md` | Model-defined; execution/report pending |
| AMS-VV-CON-003 | AMS v1.0 final acceptance | Environmental I2C read timeout `≤5 ms` for `Read pressure` and `Read temperature`; `[CE] I2C`; related physical/logical/allocation paths and atmospheric chain context. | Constraint; component exchange; functional chain/scenario | Testing / Analysis | Constraint; `AMS-FE-SensorBusFault`; `AMS-UC-MeasureAtmosphere` | IVV, AMS-R2, AMS-R5 | Stat: `59/59` nominal samples per read function for 95/95 timing claim; `29/29` fault trials per mode/read function if claiming R90/C95 binary response. Fault hardening: NACK/absent sensor, held SDA, held SCL, timeout/no-response, no stale OK data, no reset/deadlock, recovery without reset. | Pass iff every environmental I2C read returns OK/`VALID` or a bounded non-`VALID` shared status within `t_read+U95 ≤ 5.000 ms`; timeout maps to `TIMEOUT`, runtime bus/sensor faults map to `SENSOR_FAULT` or another applicable non-`VALID` shared status while preserving low-level evidence, no old sample is accepted as `VALID`, next recovery read succeeds without reset after fault release, and 100% environmental read call paths have no extra read lacking timeout. | Model definition: `tests/AMS-VV-CON-003/`; report/evidence: `tests/results/AMS-VV-CON-003/`; expected report: `tests/results/AMS-VV-CON-003/report.md` | Model-defined; execution/report pending |
| AMS-VV-CON-004 | AMS v1.0 final acceptance / flight readiness | Process/calculate `<5 ms` constraint; no-blocking constraint; `Calculate altitude`, `Process temperature`, AMS Processing, and AMS callable paths outside excluded I2C/UART waits. | Constraint; allocation/call-path analysis; functional chain/scenario | Testing with supporting Analysis | Constraints; `AMS-UC-MeasureAtmosphere`; `AMS-FE-SensorBusFault`; `AMS-FE-SchedulerBlock` | IVV, AMS-R5, PM&SE/IVV; `AMS-VV-CON-003` by reference | Stat: `59/59` in-limit timings per function/input set for 95/95 deadline claim. Fault hardening: representative/boundary/stale/error-coded/invalid/NaN inputs, bounded runtime fault return, no overflow/Inf acceptance, infinite loop, unbounded retry, or scheduler blockage. | Pass iff `Calculate altitude` and `Process temperature` each satisfy `t_exec+U95 < 5.000 ms`, invalid/NaN and shared-status cases return/control safely, the report includes a 100% getter/OBCC and AMS callable-path inventory with static review, dynamic traces confirm scheduler-alive bounded behavior, no unbounded blocking exists outside allowed I2C/UART waits, status propagation does not mask `TIMEOUT`/`SENSOR_FAULT`/`INIT_FAIL` as `VALID`, and I2C timing/recovery evidence is referenced from `AMS-VV-CON-003`. | Model definition: `tests/AMS-VV-CON-004/`; report/evidence: `tests/results/AMS-VV-CON-004/`; expected report: `tests/results/AMS-VV-CON-004/report.md` | Model-defined; covers CON-005 if non-blocking evidence is complete |

### Covered rows / residual execution notes

| Covered row | Current disposition |
|---|---|
| AMS-VV-CE-002 | Covered by `AMS-VV-API-001` for `[CE] Pointers` ownership/lifetime/null-policy/units/concurrency/aliasing analysis, provided the checklist/static-analysis evidence is executed. |
| AMS-VV-CE-003 | Covered by `AMS-VV-API-001` for `[CE] Returns` status/data semantics mapped to `VALID`, `STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, and `INIT_FAIL`, including invalid-input cases and the stale-valid prohibition. |
| AMS-VV-ALLOC-001/002/003 | Covered by `AMS-VV-API-001` allocation purity and modeled crossing analysis for AMS Sensing, AMS Processing, and OBCC. |
| AMS-VV-CON-002 | Covered by `AMS-VV-API-001` only if the variable-getter checklist, shared-status mapping, pointer ownership/lifetime/null policy, 100% getter/OBCC inventory, and implementation evidence are complete; otherwise retain as residual implementation evidence gap. |
| AMS-VV-CON-005 | Covered by `AMS-VV-CON-004` only if the non-blocking static callable-path inventory, dynamic traces, bounded status propagation, and `AMS-VV-CON-003` dependency evidence are complete; otherwise retain as residual scheduler/blocking evidence gap. |
| AMS-VV-CON-006 | Pressure accuracy constraint is assigned to `AMS-VV-FC-001`; no separate model definition is needed unless execution requires a dedicated calibration campaign. |
| AMS-VV-CON-007 | Temperature accuracy constraint is assigned to `AMS-VV-FC-001`; exposure hardening is addressed by `AMS-VV-CON-001`. |
| AMS-VV-CON-008 | Altitude resolution constraint is assigned to `AMS-VV-FC-001` pressure-step chain. |

## 6. Coverage and gaps

### v0.1 coverage

- **Physical/link coverage:** all v0.1 PCs/actors and physical links are covered by `AMS-V01-INTEG-001`.
- **Component-exchange coverage:** the single v0.1 `[CE] I2C` is covered by `AMS-V01-INTEG-001`.
- **Allocation coverage:** all v0.1 logical components and allocated functions are covered by `AMS-V01-INTEG-001`.
- **Functional-chain coverage:** atmospheric measurement, peripheral initialisation, and Serial0 logging chains are covered by `AMS-V01-FC-001`.
- **Constraint coverage:** v0.1 pressure/temperature accuracy, altitude resolution, timing/getter/no-blocking constraints are assigned as pass conditions or explicit readiness limitations in `AMS-V01-FC-001` and reviewed in `AMS-V01-INTEG-001`; the `≤60 s` temperature-response constraint is not closed by the ambient v0.1 characterization unless derived from `AMS-V10-TEMP-RESPONSE-60S` or an execution annex defining t0/final/reference/correlation.

### v0.2 coverage

- **Physical/link coverage:** all modeled v0.2 PCs and PLs are covered by `AMS-V02-PCB-001`; powered reachability over the same path is covered by `AMS-V02-BRINGUP-001`.
- **Component-exchange / functional-chain coverage:** v0.2 has no modeled logical/CE/FC views, so `AMS-V02-BRINGUP-001` adds VV-only test actors/functions to demonstrate BME280 I2C reachability without claiming native v0.2 allocation coverage. This is the accepted `AMS-BLK-003` PCB-ready non-issue disposition; do not create synthetic native v0.2 LC/CE/allocation/FC closure unless a future controlled decision changes the source model.
- **Constraint coverage:** manufacturability/soldering constraint is covered by `AMS-V02-PCB-001`; safe powered bring-up/readiness is covered by `AMS-V02-BRINGUP-001`.

### v1.0 coverage

- **Physical coverage:** all v1.0 physical components and physical links are covered by `AMS-VV-PC-001` and `AMS-VV-PL-001`.
- **Exchange coverage:** `[CE] I2C` is covered by `AMS-VV-CE-001`; `[CE] Pointers` and `[CE] Returns` are covered by `AMS-VV-API-001`.
- **Allocation coverage:** all modeled logical components and allocated functions are covered by `AMS-VV-API-001`.
- **Functional-chain coverage:** atmospheric measurement is covered by `AMS-VV-FC-001`; peripheral initialisation is covered by `AMS-VV-FC-002`.
- **Constraint coverage:** sunlight/airflow (`AMS-VV-CON-001`), variable getter/API semantics (`AMS-VV-API-001`), I2C timeout (`AMS-VV-CON-003`), process/calculate timing and no-blocking (`AMS-VV-CON-004`), and pressure/temperature/altitude constraints (`AMS-VV-FC-001`) are all assigned to model-defined activities.
- **Traceability note:** v1.0 source views now include use-case/feared-event notes; v0.1/v0.2 trace labels remain controlled provisional labels mapped through the current system requirement-to-test matrix. Execution/report evidence remains pending per activity status.

## 7. Model-defined activity index

### AMS-V10-TEMP-RESPONSE-60S — temperature-response blocker-alignment definition

- Test folder: `tests/AMS-V10-TEMP-RESPONSE-60S/` (existing model-defined activity; execution/report pending).
- Definition view: `definition_views/AMS-V10-TEMP-RESPONSE-60S_view1_verification_chain.d2/png`.
- Report-by-reference target: `tests/results/AMS-V10-TEMP-RESPONSE-60S/report.md`.

### AMS-V10-DATA-FRESHNESS — AMS-to-OBCC freshness/status blocker-alignment definition

- Test folder: `tests/AMS-V10-DATA-FRESHNESS/` (existing model-defined activity; execution/report pending).
- Definition view: `definition_views/AMS-V10-DATA-FRESHNESS_view1_verification_chain.d2/png`.
- Report-by-reference target: `tests/results/AMS-V10-DATA-FRESHNESS/report.md`.

### AMS-V01-INTEG-001 — v0.1 breadboard to v0.2 PCB readiness inspection

- Test folder: `tests/AMS-V01-INTEG-001/`.
- Baseline copied views: v0.1 `view1` through `view6` (`.d2` and `.png`).
- Test-definition views: `AMS_V01_INTEG_001_view1_physical_inspection_testbench.d2`, `AMS_V01_INTEG_001_view2_logical_ce_analysis.d2`, `AMS_V01_INTEG_001_view3_functional_allocation_readiness_analysis.d2` with matching PNGs.
- Report-by-reference target: `tests/results/AMS-V01-INTEG-001/report.md`.

### AMS-V01-FC-001 — v0.1 atmospheric/init/serial functional-chain readiness test

- Test folder: `tests/AMS-V01-FC-001/`.
- Baseline copied views: v0.1 `view1` through `view6` (`.d2` and `.png`).
- Test-definition views: physical, logical, functional-allocation, atmospheric measurement test chain, and serial/init smoke chain views with matching PNGs.
- Report-by-reference target: `tests/results/AMS-V01-FC-001/report.md`.

### AMS-V02-PCB-001 — v0.2 PCB delivery/manufacturability inspection

- Test folder: `tests/AMS-V02-PCB-001/`.
- Baseline copied view: `AMS_v0.2_view1_physical.d2/.png`.
- Test-definition views: PCB physical inspection, inspection/allocation-analysis, and manufacturability/physical-link analysis chain with matching PNGs.
- Report-by-reference target: `tests/results/AMS-V02-PCB-001/report.md`.

### AMS-V02-BRINGUP-001 — v0.2 powered bring-up and I2C reachability demonstration

- Test folder: `tests/AMS-V02-BRINGUP-001/`.
- Baseline copied view: `AMS_v0.2_view1_physical.d2/.png`.
- Testbench views: physical powered bring-up, logical I2C bring-up, functional-allocation bring-up, and power/I2C bring-up chain with matching PNGs.
- Report-by-reference target: `tests/results/AMS-V02-BRINGUP-001/report.md`.

### AMS-VV-PC-001 — Physical component presence/absence inspection

- Test folder: `tests/AMS-VV-PC-001/`.
- Baseline copied views: v1.0 `view1` through `view5` (`.d2` and `.png`).
- Inspection testbench views: `AMS_VV_PC_001_view1_physical_inspection_testbench.d2`, `AMS_VV_PC_001_view3_functional_allocation_inspection.d2` with matching PNGs.
- Report-by-reference target: `tests/results/AMS-VV-PC-001/report.md`.

### AMS-VV-PL-001 — Physical link presence/absence inspection

- Test folder: `tests/AMS-VV-PL-001/`.
- Baseline copied views: v1.0 `view1` through `view5` (`.d2` and `.png`).
- Inspection testbench views: `AMS_VV_PL_001_view1_physical_link_inspection_testbench.d2`, `AMS_VV_PL_001_view3_functional_allocation_inspection.d2` with matching PNGs.
- Report-by-reference target: `tests/results/AMS-VV-PL-001/report.md`.

### AMS-VV-CE-001 — I2C component-exchange presence/absence analysis

- Test folder: `tests/AMS-VV-CE-001/`.
- Baseline copied views: v1.0 `view1` through `view5` (`.d2` and `.png`).
- Analysis testbench views: `AMS_VV_CE_001_view2_logical_ce_analysis_testbench.d2`, `AMS_VV_CE_001_view3_functional_allocation_ce_analysis.d2`, and `AMS_VV_CE_001_view4_i2c_ce_presence_absence_analysis_chain.d2` with matching PNGs.
- Report-by-reference target: `tests/results/AMS-VV-CE-001/report.md`.

### AMS-VV-API-001 — Pointer/return API and allocation consistency analysis

- Test folder: `tests/AMS-VV-API-001/`.
- Baseline copied views: v1.0 `view1` through `view5` (`.d2` and `.png`).
- Analysis testbench views: logical API/CE analysis, functional-allocation API analysis, and variable-getter contract analysis chain with matching PNGs.
- Report-by-reference target: `tests/results/AMS-VV-API-001/report.md`.

### AMS-VV-FC-001 — Atmospheric measurement accuracy and altitude functional-chain test

- Test folder: `tests/AMS-VV-FC-001/`.
- Baseline copied views: v1.0 `view1` through `view5` (`.d2` and `.png`).
- Test-definition views: physical, logical, functional-allocation, atmospheric measurement acceptance chain, and altitude-resolution pressure-step chain with matching PNGs.
- Report-by-reference target: `tests/results/AMS-VV-FC-001/report.md`.

### AMS-VV-FC-002 — Peripheral initialisation and startup-fault functional-chain test

- Test folder: `tests/AMS-VV-FC-002/`.
- Baseline copied views: v1.0 `view1` through `view5` (`.d2` and `.png`).
- Test-definition views: physical, logical, functional-allocation, nominal boot init-state chain, and startup-fault init-state chain with matching PNGs.
- Report-by-reference target: `tests/results/AMS-VV-FC-002/report.md`.

### AMS-VV-CON-001 — Sunlight-blocking and airflow exposure inspection/demonstration

- Test folder: `tests/AMS-VV-CON-001/`.
- Baseline copied views: v1.0 `view1` through `view5` (`.d2` and `.png`).
- Test-definition views: physical exposure testbench, logical exposure testbench, functional-allocation exposure, and sunlight/airflow demonstration chain with matching PNGs.
- Report-by-reference target: `tests/results/AMS-VV-CON-001/report.md`.

### AMS-VV-CON-003 — I2C read timeout ≤ 5 ms

- Test folder: `tests/AMS-VV-CON-003/`.
- Baseline copied views: v1.0 `view1` through `view5` (`.d2` and `.png`).
- Testbench views: physical/logical/allocation timeout testbench views plus nominal timing, fault-recovery, and supporting timeout implementation analysis chains with matching PNGs.
- Report-by-reference target: `tests/results/AMS-VV-CON-003/report.md`.

### AMS-VV-CON-004 — Processing timing and non-blocking callable-path verification

- Test folder: `tests/AMS-VV-CON-004/`.
- Baseline copied views: v1.0 `view1` through `view5` (`.d2` and `.png`).
- Test-definition views: physical, logical, functional-allocation, processing timing chain, and nonblocking analysis chain with matching PNGs.
- Report-by-reference target: `tests/results/AMS-VV-CON-004/report.md`.
