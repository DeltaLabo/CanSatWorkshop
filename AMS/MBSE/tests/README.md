# AMS v1.0 IVV-aligned verification plan

Planning artifact for the Capella/D2 views in `AMS/MBSE/v1.0`. The model remains the source of truth; this file inventories the current model and identifies candidate verification activities to be modeled in a test-definition pass. Baseline Capella/D2 diagrams in `AMS/MBSE/v1.0` are not modified; modeled test-definition copies are added under this `tests/` folder.

Project-wide IVV conventions, evidence paths, statistical policy, fault semantics, and report-by-reference rules are defined in [`../../../PM&SE/IVV.md`](../../../PM&SE/IVV.md). Evidence for any activity below should be stored under `results/<activity-id>/` in this `tests/` folder unless a campaign-level folder is later agreed.

## 1. SSIV / development-version assumptions

- **Confirmed SSIV:** AMS subsystem integration version **v1.0** for **final acceptance**. Earlier AMS versions are treated as protoflight/incremental delivery baselines.
- **Campaign scope:** final acceptance for AMS v1.0.
- **AMS-VV-CON-003 scope confirmation:** I2C timeout verification is scoped to environmental measurement I2C read functions (`Read pressure`, `Read temperature`) only; peripheral-init, chip-ID, and hidden driver setup reads are out of scope unless reachable inside those environmental reads. Recovery without reset after released I2C fault is mandatory.
- **Rate semantics from project IVV:** internal AMS/OBCC measurement collection may use `≥5 Hz`; v1.0 downlink telemetry cadence is the system-level `2 s` LoRa cadence.
- **Fault semantics from project IVV:** a BME280 startup failure is treated as a critical startup fault; runtime getter/sensor failures shall return bounded error/result codes and shall not block the scheduler.

## 2. Views read

- `AMS_v1.0_view1_physical.d2`: physical components, physical links, and airflow/sunlight physical constraint.
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

### 4.1 Physical context and components

Physical context: `[System] Physical System`; `[PC] CanSat`. Physical components: `[PC] AMS Module`; `[PC] AMS PCB`; `[PC] BME280`; AMS-side `[PC] Backplane Connector`; `[PC] Backplane PCB`; `[PC] 2mm 2x6 AMS Headers`; `[PC] Spine`; `[PC] 2mm 2x6 OBCC Headers`; `[PC] OBCC Module`; `[PC] OBCC PCB`; `[PC] XIAO ESP32-S3`; OBCC-side `[PC] Backplane Connector`.

### 4.2 Physical links

AMS PCB screws; OBCC PCB screws; AMS module backplane fixture; OBCC module backplane fixture; BME280 footprint; AMS connector footprint; AMS I2C + 3V3 traces; AMS parallel connector; XIAO footprint; OBCC connector footprint; OBCC I2C + 3V3 traces; OBCC parallel cable; AMS header footprint; OBCC header footprint.

### 4.3 Component exchanges

- `[CE] I2C`: AMS Sensing to AMS Processing.
- `[CE] Pointers`: AMS Processing to OBCC.
- `[CE] Returns`: AMS Processing to OBCC.

### 4.4 Logical components and allocated functions

- `[LC] AMS Sensing`: `Measure pressure`, `Measure temp.`, `Respond to I2C Requests`.
- `[LC] AMS Processing`: `Get BME280 init state`, `Read pressure`, `Read temperature`, `Calculate altitude`, `Process temperature`.
- `[LC] OBCC`: `Collect peripheral init states`, `Collect measurements`.

### 4.5 Functional chains / scenarios

- `AMS v1.0 — Atmospheric measurement chain`: pressure and temperature measurement, I2C response, read/process/calculate, and OBCC measurement collection.
- `AMS v1.0 — Peripheral initialisation chain`: BME280 init-state request/response and OBCC init-state collection.

### 4.6 Constraints

Block sunlight while allowing airflow; variable-getter template for read/process or read/calculate pairs; all I2C read functions timeout `≤ 5 ms`; all process/calculate functions `< 5 ms`; no blocking operations besides I2C or UART comms; pressure accuracy `< 1 hPa`; temperature accuracy `< 0.5 °C` over `10–40 °C`; altitude resolution `< 10 m`.

### 4.7 Traceability targets currently available

The AMS views do not contain explicit mission, capability, use-case, or feared-event nodes. Candidate trace targets used below are therefore provisional: `AMS-UC-MeasureAtmosphere`, `AMS-UC-InitializePeripheral`, `AMS-FE-SensorBusFault`, `AMS-FE-BadExposure`, and the modeled constraints listed above.

## 5. Verification activities

Activities below are planning candidates unless their status states `Model-defined`. Detailed procedures, test means, stimuli, expected behavior, and pass/fail constraints should be modeled under the `capella-pa-tests-definition.md` workflow before execution evidence is treated as final.

| Verification activity ID | SSIV / version | Model element(s) covered | IVV source category | IADT method | Traceability target | Relevant references | Viewpoints: statistical significance and fault hardening | Preliminary pass/fail criteria or constraint candidates | Expected diagram/report location | Status |
|---|---|---|---|---|---|---|---|---|---|---|
| AMS-VV-PC-001 | AMS v1.0 final acceptance | All 13 modeled UUT physical components in §4.1 / `AMS_v1.0_view1_physical.d2`: CanSat; AMS Module; AMS PCB; BME280; AMS-side Backplane Connector; Backplane PCB; 2mm 2x6 AMS Headers; Spine; 2mm 2x6 OBCC Headers; OBCC Module; OBCC PCB; XIAO ESP32-S3; OBCC-side Backplane Connector. Excludes physical-link integrity except as context. | Component/link — PC portion | Inspection | AMS physical integration/build readiness; `AMS-UC-MeasureAtmosphere` | IVV, AMS-R1, AMS-R6 | Stat: 100% census inspection, `13/13` target PCs per final-acceptance article, no sampling/reliability claim. Fault hardening: missing/wrong PC, wrong variant, wrong side/location, duplicate-instance confusion, visible damage, FOD, contamination, unapproved critical substitution. | Pass iff every target PC is present, identifiable, correct for the v1.0 baseline, installed in modeled containment, and recorded with checklist/photo/build-record evidence; any missing, wrong, ambiguous, damaged, contaminated, temporary/loose, or unapproved substituted PC fails unless controlled waiver/model update exists; PL integrity remains under AMS-VV-PL-001. | Model definition: `tests/AMS-VV-PC-001/` (`AMS_VV_PC_001_view1` and `view3` D2/PNG); report/evidence: `tests/results/AMS-VV-PC-001/`; expected report: `tests/results/AMS-VV-PC-001/report.md` | Model-defined; execution/report pending |
| AMS-VV-PL-001 | AMS v1.0 final acceptance | All 14 modeled UUT physical links in §4.2 / `AMS_v1.0_view1_physical.d2`: AMS PCB screws; OBCC PCB screws; AMS module backplane fixture; OBCC module backplane fixture; BME280 footprint; AMS connector footprint; AMS I2C + 3V3 traces; AMS parallel connector; XIAO footprint; OBCC connector footprint; OBCC I2C + 3V3 traces; OBCC parallel cable; AMS header footprint; OBCC header footprint. Excludes PC presence/identity covered by AMS-VV-PC-001 and CE protocol/timing behavior. | Component/link — PL portion | Inspection | AMS physical/electrical integration readiness; `AMS-UC-MeasureAtmosphere`; `AMS-UC-InitializePeripheral`; `AMS-FE-SensorBusFault` / intermittent interconnect | IVV, AMS-R2, AMS-R6 | Stat: 100% census inspection, `14/14` target PLs per final-acceptance article, no sampling/reliability claim. Fault hardening: missing/loose link, wrong endpoint/route/cable, open, short, intermittent contact, connector/cable seating error, solder bridge, lifted pad, bent pin, FOD/contamination, unapproved bypass, probe-induced damage. | Pass iff every target PL is present, connects exactly the modeled endpoints, is installed/routed/seated/soldered as modeled, has visual/retention/continuity/build-record evidence as applicable, and has no unapproved reroute, bypass, temporary jumper, repair, or substitution; missing endpoint PCs are dependencies/anomalies against AMS-VV-PC-001; CE behavior is not credited here. | Model definition: `tests/AMS-VV-PL-001/` (`AMS_VV_PL_001_view1` and `view3` D2/PNG); report/evidence: `tests/results/AMS-VV-PL-001/`; expected report: `tests/results/AMS-VV-PL-001/report.md` | Model-defined; execution/report pending |
| AMS-VV-CE-001 | AMS v1.0 | `[CE] I2C` between AMS Sensing and AMS Processing | Component exchange | Analysis | `AMS-UC-MeasureAtmosphere`; `AMS-UC-InitializePeripheral`; `AMS-FE-SensorBusFault` | IVV, AMS-R1, AMS-R2 | Stat: analysis is 100% design/interface coverage; timing evidence may use 59 in-limit samples for a 95/95 deadline claim. Fault hardening: NACK, missing device, stuck SDA/SCL, clock-stretch/timeout behavior. | Implemented bus topology, address, pullups, voltage levels, transaction direction, and timeout policy are consistent with modeled I2C intent. | Future model definition: `tests/definitions/AMS-VV-CE-001`; report/evidence: `tests/results/AMS-VV-CE-001/` | Candidate; interface evidence pending |
| AMS-VV-CE-002 | AMS v1.0 | `[CE] Pointers` between AMS Processing and OBCC | Component exchange | Analysis | `AMS-UC-MeasureAtmosphere`; `AMS-UC-InitializePeripheral` | IVV | Stat: 100% API-path review. Fault hardening: null/invalid pointer handling if permitted by API; stale-data prevention. | Pointer ownership, lifetime, units, scaling, and error-result semantics are consistent with the variable-getter model. | Future model definition: `tests/definitions/AMS-VV-CE-002`; report/evidence: `tests/results/AMS-VV-CE-002/` | Candidate; API contract pending |
| AMS-VV-CE-003 | AMS v1.0 | `[CE] Returns` between AMS Processing and OBCC | Component exchange | Analysis | `AMS-UC-MeasureAtmosphere`; `AMS-UC-InitializePeripheral`; `AMS-FE-SensorBusFault` | IVV | Stat: 100% return-code and data-field review. Fault hardening: bounded error/result code for startup and runtime faults. | Return values distinguish valid measurement, stale value, startup fault, runtime sensor fault, timeout, and invalid input as applicable. | Future model definition: `tests/definitions/AMS-VV-CE-003`; report/evidence: `tests/results/AMS-VV-CE-003/` | Candidate; API contract pending |
| AMS-VV-ALLOC-001 | AMS v1.0 | `[LC] AMS Sensing` and its functions | Allocation | Analysis | `AMS-UC-MeasureAtmosphere`; `AMS-UC-InitializePeripheral` | IVV, AMS-R1 | Stat: 100% function-to-LC allocation review. Fault hardening: sensor self-state and invalid measurement behavior. | Only BME280 sensing and I2C response functions are allocated to AMS Sensing; no processing/OBCC functions are foreign to this LC. | Future model definition: `tests/definitions/AMS-VV-ALLOC-001`; report/evidence: `tests/results/AMS-VV-ALLOC-001/` | Candidate; allocation review pending |
| AMS-VV-ALLOC-002 | AMS v1.0 | `[LC] AMS Processing` and its functions | Allocation | Analysis | `AMS-UC-MeasureAtmosphere`; `AMS-UC-InitializePeripheral`; constraints on timing/getters | IVV, AMS-R1, AMS-R2 | Stat: 100% function-to-LC and data-flow review. Fault hardening: invalid BME280 response, timeout, stale data, computation overflow/units mismatch. | Init-state, read, process, and altitude-calculation functions are allocated to AMS Processing; all crossings use modeled I2C/pointer/return CEs. | Future model definition: `tests/definitions/AMS-VV-ALLOC-002`; report/evidence: `tests/results/AMS-VV-ALLOC-002/` | Candidate; allocation review pending |
| AMS-VV-ALLOC-003 | AMS v1.0 | `[LC] OBCC`: collect init states and collect measurements | Allocation | Analysis | `AMS-UC-MeasureAtmosphere`; `AMS-UC-InitializePeripheral` | IVV | Stat: 100% function-to-LC review. Fault hardening: OBCC behavior for critical startup fault versus runtime bounded fault. | OBCC only collects status/measurements; it does not own AMS sensing/processing functions; startup-fault blocking and runtime non-blocking semantics match IVV. | Future model definition: `tests/definitions/AMS-VV-ALLOC-003`; report/evidence: `tests/results/AMS-VV-ALLOC-003/` | Candidate; allocation review pending |
| AMS-VV-FC-001 | AMS v1.0 | Atmospheric measurement functional chain | Functional chain/scenario | Testing / Demonstration | `AMS-UC-MeasureAtmosphere`; constraints: pressure, temperature, altitude resolution | IVV, AMS-R1, AMS-R3, AMS-R4, AMS-R5, AMS-R7 | Stat: `n ≥ 30` stable paired samples per operating point; report uncertainty; use rate/distribution evidence for sustained update claims. Fault hardening: swapped branches, stale data, sensor noise/outliers. | Pressure and temperature are read, processed, and collected in the modeled order; pressure accuracy `<1 hPa`, temperature accuracy `<0.5 °C`, altitude resolution `<10 m`, and update-rate/staleness criteria are met with uncertainty included. | Future model definition: `tests/definitions/AMS-VV-FC-001`; report/evidence: `tests/results/AMS-VV-FC-001/` | Candidate; detailed chain test definition pending |
| AMS-VV-FC-002 | AMS v1.0 | Peripheral initialisation functional chain | Functional chain/scenario | Testing / Demonstration | `AMS-UC-InitializePeripheral`; `AMS-FE-SensorBusFault` | IVV, AMS-R1, AMS-R2, AMS-R5 | Stat: 29/29 nominal boots supports R90/C95; add explicit induced-fault trials. Fault hardening: absent BME280, NACK, stuck bus, warm reset. | Init-state request/response and OBCC collection complete; nominal boots return valid init state; critical startup fault is reported without unbounded blocking. | Future model definition: `tests/definitions/AMS-VV-FC-002`; report/evidence: `tests/results/AMS-VV-FC-002/` | Candidate; detailed chain test definition pending |
| AMS-VV-CON-001 | AMS v1.0 | `[C] Block sunlight, allow airflow` | Constraint | Inspection / Demonstration | Constraint; `AMS-FE-BadExposure` | IVV, AMS-R3, AMS-R6 | Stat: 100% configuration inspection plus paired exposure samples if tested. Fault hardening: direct solar/heat-lamp bias, blocked ventilation. | Installed AMS configuration has no direct solar line-of-sight to BME280 and has an unobstructed airflow path; if tested, shaded/ventilated bias plus uncertainty remains within temperature constraint. | Future model definition: `tests/definitions/AMS-VV-CON-001`; report/evidence: `tests/results/AMS-VV-CON-001/` | Candidate; exposure test means pending |
| AMS-VV-CON-002 | AMS v1.0 | `[C] Variable Getter template` | Constraint | Analysis / Testing | Constraint; `AMS-UC-MeasureAtmosphere`; `AMS-UC-InitializePeripheral` | IVV | Stat: 100% getter inventory and API-case coverage. Fault hardening: invalid pointers and error-result propagation. | Each read/process or read/calculate pair is implemented as the agreed variable-getter pattern with documented units, ownership, and bounded status returns. | Future model definition: `tests/definitions/AMS-VV-CON-002`; report/evidence: `tests/results/AMS-VV-CON-002/` | Candidate; software design evidence pending |
| AMS-VV-CON-003 | AMS v1.0 final acceptance | `[C] All I2C read functions must have a timeout ≤ 5 ms` scoped to environmental measurement reads; `[CE] I2C`; `[F] Read pressure`; `[F] Read temperature`; `[F] Respond to I2C Requests`; `[LC] AMS Processing`; `[LC] AMS Sensing`; relevant I2C physical path; atmospheric measurement chain. Peripheral-init, chip-ID, and hidden driver setup reads are out of scope unless reachable inside the environmental read functions. | Constraint; component exchange; functional chain/scenario | Testing / Analysis | Constraint; `AMS-FE-SensorBusFault`; `AMS-UC-MeasureAtmosphere` | IVV, AMS-R2, AMS-R5 | Stat: `59/59` nominal samples per environmental I2C read function for 95/95 timing claim; `29/29` fault trials per fault mode/read function if claiming R90/C95 binary fault response, otherwise report as screening. Fault hardening: NACK/absent sensor, held SDA, held SCL, timeout/no-response, no stale OK data, no reset/deadlock, mandatory recovery without reset after release. | Pass iff every environmental I2C read returns OK or a bounded timeout/error status within `t_read + U95 ≤ 5.000 ms` from read-function entry to returned status; nominal OK values are current; faulted reads return only `TIMEOUT`, `NACK`, `BUS_ERROR`, or `SENSOR_UNAVAILABLE`; after fault release, the next modeled recovery read succeeds without reset; supporting analysis maps 100% of environmental AMS Processing I2C read call paths and finds no extra environmental read path lacking a `≤5 ms` timeout. | Model definition: `tests/AMS-VV-CON-003/` (`AMS_VV_CON_003_view1`–`view6` D2/PNG); report/evidence: `tests/results/AMS-VV-CON-003/`; expected report: `tests/results/AMS-VV-CON-003/report.md` | Model-defined; execution/report pending |
| AMS-VV-CON-004 | AMS v1.0 | `[C] Process/Calculate functions < 5 ms` | Constraint | Testing / Analysis | Constraint; `AMS-UC-MeasureAtmosphere` | IVV, AMS-R5 | Stat: 59 representative in-limit timings for 95/95 deadline claim; larger profiling set may characterize tails. Fault hardening: boundary pressure/temperature values and invalid samples. | `Calculate altitude` and `Process temperature` each complete in `<5 ms` with representative worst-case inputs. | Future model definition: `tests/definitions/AMS-VV-CON-004`; report/evidence: `tests/results/AMS-VV-CON-004/` | Candidate; timing definition pending |
| AMS-VV-CON-005 | AMS v1.0 | `[C] No blocking operations besides I2C or UART comms` | Constraint | Analysis / Testing | Constraint; `AMS-FE-SensorBusFault` | IVV, AMS-R2 | Stat: static/dynamic coverage of all AMS callable paths; fault trials classified pass/fail. Fault hardening: mid-flight sensor fault shall not block scheduler. | Code review and instrumentation show no unbounded blocking outside allowed comm waits; runtime faults return bounded codes and scheduler continues. | Future model definition: `tests/definitions/AMS-VV-CON-005`; report/evidence: `tests/results/AMS-VV-CON-005/` | Candidate; code/path coverage pending |
| AMS-VV-CON-006 | AMS v1.0 | `[C] Pressure accuracy < 1 hPa` | Constraint | Testing | Constraint; `AMS-UC-MeasureAtmosphere` | IVV, AMS-R1, AMS-R3, AMS-R5, AMS-R7 | Stat: `n ≥ 30` paired samples per pressure point; report bias, CI, and expanded uncertainty. Fault hardening: pressure drift/noise, environmental exposure, post-vibration spot check. | For each point, `abs(bias) + U95 ≤ 1 hPa`; raw pressure data retained. | Future model definition: `tests/definitions/AMS-VV-CON-006`; report/evidence: `tests/results/AMS-VV-CON-006/` | Candidate; calibration setup pending |
| AMS-VV-CON-007 | AMS v1.0 | `[C] Temperature accuracy < 0.5 °C, 10–40 °C` | Constraint | Testing | Constraint; `AMS-UC-MeasureAtmosphere`; `AMS-FE-BadExposure` | IVV, AMS-R1, AMS-R3, AMS-R5, AMS-R6 | Stat: `n ≥ 30` paired samples at representative set points within 10–40 °C; uncertainty guard-band. Fault hardening: self-heating, sunlight, airflow obstruction, thermal soak. | At each set point, `abs(bias) + U95 ≤ 0.5 °C`; no unexplained outlier remains after reference uncertainty analysis. | Future model definition: `tests/definitions/AMS-VV-CON-007`; report/evidence: `tests/results/AMS-VV-CON-007/` | Candidate; calibration/exposure setup pending |
| AMS-VV-CON-008 | AMS v1.0 | `[C] Altitude resolution < 10 m` | Constraint | Testing / Analysis | Constraint; `AMS-UC-MeasureAtmosphere` | IVV, AMS-R1, AMS-R4, AMS-R5, AMS-R7 | Stat: paired pressure/altitude samples with `n ≥ 30` per level or pressure step; CI on delta. Fault hardening: pressure-to-altitude unit/conversion error and stale pressure data. | A 10 m-equivalent pressure change is detected with correct sign and confidence interval excluding zero; calculated altitude error plus uncertainty is `<10 m` for tested deltas. | Future model definition: `tests/definitions/AMS-VV-CON-008`; report/evidence: `tests/results/AMS-VV-CON-008/` | Candidate; altitude/pressure stimulus pending |

## 6. Coverage and gaps

- **Physical coverage:** all AMS v1.0 physical components and physical links are covered by AMS-VV-PC-001 and AMS-VV-PL-001.
- **Exchange coverage:** all modeled component exchanges are covered by AMS-VV-CE-001 through AMS-VV-CE-003.
- **Allocation coverage:** all modeled logical components and allocated functions are covered by AMS-VV-ALLOC-001 through AMS-VV-ALLOC-003.
- **Functional-chain coverage:** both modeled AMS chains are covered by AMS-VV-FC-001 and AMS-VV-FC-002.
- **Constraint coverage:** every explicit AMS constraint is assigned to at least one constraint-derived activity.
- **Modeling gaps:** explicit mission/capability/use-case/feared-event nodes are absent; traceability targets in this plan are candidates requiring user/model confirmation.
- **Definition progress:** AMS-VV-PC-001 is now model-defined under `tests/AMS-VV-PC-001/` with baseline copies, physical inspection testbench view, functional-allocation inspection view, and inspection pass/fail constraints.
- **Definition progress:** AMS-VV-PL-001 is now model-defined under `tests/AMS-VV-PL-001/` with baseline copies, physical-link inspection testbench view, functional-allocation inspection view, and inspection pass/fail constraints.
- **Definition progress:** AMS-VV-CON-003 is now model-defined under `tests/AMS-VV-CON-003/` with baseline copies, physical/logical/allocation testbench views, nominal timing, fault-recovery, and supporting analysis chains.
- **Remaining definition gaps:** detailed test means, instrumentation, environmental profiles, reference-instrument IDs, and exact pass/fail constraints remain pending for all activities other than AMS-VV-PC-001, AMS-VV-PL-001, and AMS-VV-CON-003.

## 7. Model-defined activity index

### AMS-VV-PC-001 — Physical component presence/absence inspection

- Test folder: `tests/AMS-VV-PC-001/`.
- Baseline copied views: `tests/AMS-VV-PC-001/baseline/AMS_v1.0_view1` through `view5` (`.d2` and `.png`).
- Inspection testbench views: `AMS_VV_PC_001_view1_physical_inspection_testbench.d2`, `AMS_VV_PC_001_view3_functional_allocation_inspection.d2`.
- Confirmed final-acceptance scope: 100% census of the 13 modeled UUT physical components; PL integrity is excluded and remains under `AMS-VV-PL-001`.
- Rendered PNGs with matching names are generated beside each D2 file.
- Report-by-reference target: `tests/results/AMS-VV-PC-001/report.md`.

### AMS-VV-PL-001 — Physical link presence/absence inspection

- Test folder: `tests/AMS-VV-PL-001/`.
- Baseline copied views: `tests/AMS-VV-PL-001/baseline/AMS_v1.0_view1` through `view5` (`.d2` and `.png`).
- Inspection testbench views: `AMS_VV_PL_001_view1_physical_link_inspection_testbench.d2`, `AMS_VV_PL_001_view3_functional_allocation_inspection.d2`.
- Confirmed final-acceptance scope: 100% census of the 14 modeled UUT physical links; PC identity and CE behavior are excluded.
- Rendered PNGs with matching names are generated beside each D2 file.
- Report-by-reference target: `tests/results/AMS-VV-PL-001/report.md`.

### AMS-VV-CON-003 — I2C read timeout ≤ 5 ms

- Test folder: `tests/AMS-VV-CON-003/`.
- Baseline copied views: `tests/AMS-VV-CON-003/baseline/AMS_v1.0_view1` through `view5` (`.d2` and `.png`).
- Testbench views: `AMS_VV_CON_003_view1_physical_testbench.d2`, `AMS_VV_CON_003_view2_logical_testbench.d2`, `AMS_VV_CON_003_view3_functional_allocation_testbench.d2`.
- Test/analysis chains: `AMS_VV_CON_003_view4_nominal_i2c_read_timing_chain.d2`, `AMS_VV_CON_003_view5_fault_timeout_recovery_chain.d2`, `AMS_VV_CON_003_view6_timeout_implementation_analysis_chain.d2`.
- Confirmed final-acceptance scope: environmental I2C reads only (`Read pressure`, `Read temperature`); recovery without reset after released fault is mandatory.
- Rendered PNGs with matching names are generated beside each D2 file.
- Report-by-reference target: `tests/results/AMS-VV-CON-003/report.md`.
