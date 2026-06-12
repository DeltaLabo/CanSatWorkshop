# ADS MBSE-wide corpus and verification plan

## 1. Scope

This corpus targets all ADS Capella/D2 views under `ADS/MBSE/`:

- `v0.1/` — GPS-only ADS prototype.
- `v0.2/` — GPS + ICM20948 IMU ADS prototype with Serial0 logging.
- `v0.3/` — ADS PCB delivery model.
- `v1.0/` — integrated CanSat/Backplane/OBCC allocation model.

It is an umbrella corpus: it normalizes what persists across versions, identifies version-specific deltas, and defines verification scenarios that can be applied to any ADS version where the relevant model element exists.

Project-wide IVV conventions, statistics, rate terminology, fault semantics, and artifact paths are defined in [`../../../PM&SE/IVV.md`](../../../PM&SE/IVV.md). Serial0 logging is a development interface for pre-v1.0 baselines; `5 Hz` is an internal ADS acquisition/collection rate, not the v1.0 LoRa downlink telemetry cadence.

## 2. Source views

| Version | D2 views read into the corpus |
|---|---|
| v0.1 | physical, logical, functional allocation, GPS position chain, Serial0 logging chain |
| v0.2 | physical, logical, functional allocation, GPS position chain, angular velocity chain, attitude estimation chain, peripheral initialization chain, Serial0 logging chain |
| v0.3 | physical PCB delivery view |
| v1.0 | physical, logical, functional allocation, GPS position chain, angular velocity chain, attitude estimation chain, peripheral initialization chain |

## 3. Cross-version ADS lineage

| Version | Main architecture | Main behavior represented | Key verification emphasis |
|---|---|---|---|
| v0.1 | UBX-G7020-KT GPS + XIAO ESP32 + PC over USB-C. | GPS latitude/longitude acquisition at 5 Hz, getters, collection, Serial0 logging, UBX init state. | GPS UART, position accuracy `<5 m`, 5 Hz loop, Serial0 output, no-blocking/process/UART timeout constraints. |
| v0.2 | Adds ICM20948 IMU on I2C to the v0.1 physical architecture. | GPS chain plus angular velocity, acceleration, magnetic-field, pitch/roll/yaw, GPS+IMU init states, Serial0 logging. | v0.1 tests plus I2C/IMU integrity, angular-rate accuracy `<30 deg/s`, attitude plausibility. |
| v0.3 | ADS PCB containing GPS, ICM20948, and backplane connector. No runtime behavior views. | Physical delivery of PCB footprints and traces. | PCB manufacturing, solder/reflow/manual assembly, trace continuity, connector and footprint inspection. |
| v1.0 | Full CanSat: ADS Module sensor PCB connects through Backplane PCB to OBCC Module with XIAO ESP32-S3. | ADS Processing on OBCC reads GPS/IMU over backplane, returns/pointers to OBCC collection. | End-to-end backplane integration, ADS/OBCC interface, I2C and UART timeout constraints, GPS/IMU functional chains. |

## 4. Normalized ADS feature model

| Feature | v0.1 | v0.2 | v0.3 | v1.0 |
|---|---:|---:|---:|---:|
| UBX-G7020-KT GPS | yes | yes | yes | yes |
| ICM20948 IMU | no | yes | yes | yes |
| XIAO ESP32/ESP32-S3 processing | XIAO ESP32 in ADS | XIAO ESP32 in ADS | not modelled | XIAO ESP32-S3 in OBCC Module |
| External PC / Serial0 logging | yes | yes | no | not modelled as ADS chain |
| Backplane connector / backplane integration | no | no | ADS PCB connector | ADS, Backplane, OBCC modules |
| GPS UART functional chain | yes | yes | no behavior view | yes |
| IMU I2C chain | no | yes | no behavior view | yes |
| Attitude estimation chain | no | yes | no behavior view | yes |
| Peripheral init-state chain | GPS only | GPS + ICM20948 | no behavior view | GPS + ICM20948 |
| Position accuracy `<5 m` | yes | yes | not in view | yes |
| GPS collection at `5 Hz` | yes | yes | not in view | not explicitly shown |
| Angular-rate accuracy `<30 deg/s` | no | yes | not in view | yes |
| Process/calculate duration `<5 ms` | yes | yes | not in view | yes |
| UART read timeout `<=5 ms` | yes | yes | not in view | yes |
| I2C read timeout `<=5 ms` | not applicable | not explicitly shown | not in view | yes |
| No blocking except I2C/UART | yes | yes | not in view | yes |
| Variable Getter pattern | yes | yes | not in view | yes |

## 5. Model-derived verification targets

| ID | Target | Applies to | Model evidence |
|---|---|---|---|
| ADS-GEN-PHY-01 | GPS physical connection to processing host by UART plus 3V3/GND. | v0.1, v0.2, v0.3, v1.0 | v0.1/v0.2 UART cables; v0.3/v1.0 UART traces/backplane path. |
| ADS-GEN-PHY-02 | ICM20948 physical connection to processing host by I2C plus 3V3/GND. | v0.2, v0.3, v1.0 | v0.2 I2C cables; v0.3/v1.0 I2C traces/backplane path. |
| ADS-GEN-PHY-03 | ADS PCB/backplane/header/connector mechanical and electrical integration. | v0.3, v1.0 | ADS PCB, backplane connector, 2mm 2x6 ADS/OBCC headers, parallel cable, fixtures/screws. |
| ADS-GEN-GPS-01 | GPS longitude/latitude are measured, sent, read/stored, exposed by getters, and collected. | v0.1, v0.2, v1.0 | GPS position chain in each behavior version. |
| ADS-GEN-GPS-02 | Position accuracy target is `<5 m`. | v0.1, v0.2, v1.0 | Accuracy constraint linked to `Get lat`/`Get lon`. |
| ADS-GEN-GPS-03 | Collection rate is `5 Hz` where explicitly modelled. | v0.1, v0.2 | `At 5 Hz` constraint on `Collect measurements`. |
| ADS-GEN-IMU-01 | IMU angular velocities are measured, read over I2C, processed, and collected. | v0.2, v1.0 | Angular velocity chain. |
| ADS-GEN-IMU-02 | Angular-rate accuracy target is `<30 deg/s`. | v0.2, v1.0 | Accuracy constraint on angular-rate measurement. |
| ADS-GEN-ATT-01 | Accelerations and magnetic-field intensities feed pitch/roll/yaw calculation and collection. | v0.2, v1.0 | Attitude estimation chain. |
| ADS-GEN-INIT-01 | Peripheral init states are collected before/with measurement delivery. | v0.1, v0.2, v1.0 | Peripheral init/logging chains and functional allocation. |
| ADS-GEN-SW-01 | Process/calculate functions run in `<5 ms`; UART reads timeout `<=5 ms`; I2C reads timeout `<=5 ms` when explicitly modelled; no unintended blocking; Variable Getter pattern. | v0.1, v0.2, v1.0 | Logical/functional allocation constraints. |
| ADS-GEN-LOG-01 | Measurement/init-state data is delivered to the consuming actor/component. | v0.1, v0.2, v1.0 | Serial0 logging in v0.1/v0.2; Pointers/Returns to OBCC in v1.0. |

## 6. Statistical acceptance rules

Use the project-wide policy in [`../../../PM&SE/IVV.md`](../../../PM&SE/IVV.md) unless a project-specific requirement supersedes it.

1. **Measurement accuracy** (`<5 m`, `<30 deg/s`): collect at least `n ≥ 30` stable samples per test condition, report uncertainty, and guard-band pass/fail decisions.
2. **Timing/deadline limits** (`<5 ms`, `<=5 ms`) and 95/95 tolerance claims: collect `n = 59` representative samples with every sample inside the limit.
3. **Boolean pass/fail checks:** use exact one-sided binomial / Clopper-Pearson bounds; `29/29` supports R90/C95 and `59/59` supports about R95/C95.
4. **Rate checks:** for an internal 5 Hz target, nominal period is 200 ms. Evaluate mean rate, per-sample periods, stale/dropped values, and worst gaps.

## 7. Cross-version scenario catalogue

### ADS-GEN-T01 — Model inventory and version-delta inspection

**Applies to:** v0.1, v0.2, v0.3, v1.0.

**Scenario:** Verify that the implementation/configuration under test matches the intended ADS MBSE version.

**Procedure:**
1. Identify the target ADS version and D2 view set.
2. Inspect hardware BOM, firmware allocation, and electrical interfaces against the version row in `model_inventory.json`.
3. Confirm whether the version is a runtime ADS build (v0.1/v0.2/v1.0) or PCB-only delivery (v0.3).

**Acceptance:** implementation matches the selected version, or all deviations are recorded as test constraints/nonconformances.

### ADS-GEN-T02 — Breadboard/prototype physical electrical integration

**Applies to:** v0.1, v0.2.

**Scenario:** Verify cable-level GPS/IMU/USB-C physical links.

**Acceptance:** all modelled UART/I2C/3V3/GND/USB-C links are present, continuous, correctly oriented, and powered within component limits.

### ADS-GEN-T03 — PCB/backplane physical integration and workmanship

**Applies to:** v0.3, v1.0.

**Scenario:** Verify ADS PCB fabrication/assembly and v1.0 backplane integration.

**Procedure:**
1. Inspect GPS, ICM20948, and connector footprints against design files/BOM.
2. Inspect solder joints, cleanliness, polarity/orientation, and rework evidence.
3. Continuity-test UART, I2C, 3V3, and GND traces from sensor pins to connector/header endpoints.
4. For v1.0, mate ADS/backplane/OBCC connectors and verify no shorts or mis-keying.
5. Apply connector tug/strain-relief checks appropriate to the physical build.

**Acceptance:** no open/short on required nets; no solder or assembly defects that violate the chosen workmanship criteria; ADS and OBCC modules mate through the backplane with correct UART/I2C/power continuity.

### ADS-GEN-T04 — GPS UART protocol and valid lat/lon storage

**Applies to:** v0.1, v0.2, v1.0.

**Scenario:** GPS latitude/longitude are measured, sent over UART, stored by ADS Processing/Loop, and returned by getters.

**Acceptance:** valid GPS frames update stored lat/lon; invalid/no-fix/malformed frames do not silently corrupt stored values; getters return the same stored values consumed by `Collect measurements` or OBCC collection.

### ADS-GEN-T05 — GPS position accuracy and collection rate

**Applies to:** v0.1, v0.2, v1.0 for `<5 m`; v0.1/v0.2 for explicit `5 Hz`.

**Scenario:** At a surveyed or high-confidence reference point, verify horizontal position error and output cadence.

**Acceptance:** one-sided 95/95 upper bound of horizontal position error is `<5 m`; for v0.1/v0.2, nominal measurement collection is 5 Hz with no unexplained long gaps. For v1.0, rate is recorded as characterization unless a separate v1.0 requirement defines it.

### ADS-GEN-T06 — IMU I2C communication integrity

**Applies to:** v0.2, v1.0.

**Scenario:** Processing host reads ICM20948 gyro, accelerometer, and magnetometer data over I2C.

**Acceptance:** nominal reads ACK and return expected byte counts; fault injection produces bounded errors and recovery; for v1.0, each I2C read returns or times out in `<=5 ms`.

### ADS-GEN-T07 — Angular velocity accuracy

**Applies to:** v0.2, v1.0.

**Scenario:** ADS processed angular velocity is compared against a known still/rotating reference.

**Acceptance:** per-axis one-sided 95/95 upper bound of absolute angular-rate error is `<30 deg/s`; values remain finite and within configured ICM20948 full-scale range.

### ADS-GEN-T08 — Attitude estimation plausibility

**Applies to:** v0.2, v1.0.

**Scenario:** Acceleration and magnetic-field samples produce finite pitch/roll/yaw outputs.

**Acceptance:** pitch/roll/yaw are finite, bounded to the documented convention, respond correctly to static orientation changes, and are delivered to collection.

### ADS-GEN-T09 — Peripheral initialization-state collection

**Applies to:** v0.1, v0.2, v1.0.

**Scenario:** ADS reports peripheral availability/degraded states.

**Acceptance:** nominal boot reports expected GPS and, where applicable, ICM20948 init states; disconnected/faulted peripherals are reported without firmware hang or reset.

### ADS-GEN-T10 — Software timing, timeout, and Variable Getter behavior

**Applies to:** v0.1, v0.2, v1.0.

**Scenario:** Verify the implementation constraints carried through the logical/functional views.

**Acceptance:** process/calculate functions are `<5 ms`; UART reads timeout in `<=5 ms`; I2C reads timeout in `<=5 ms` where explicitly required; no non-I2C/non-UART function blocks on external data; repeated getter calls are stable until a successful read updates the backing variable.

### ADS-GEN-T11 — Measurement delivery to consumer

**Applies to:** v0.1, v0.2, v1.0.

**Scenario:** Measurement and init-state data are delivered to the modeled consumer.

**Acceptance:** v0.1/v0.2 Serial0 output is parseable by PC and contains modeled init/measurement fields; v1.0 ADS Processing provides values to OBCC through the modeled Pointers/Returns interface with explicit freshness/validity semantics.

### ADS-GEN-T12 — End-to-end CanSat mission-window run

**Applies to:** v0.1, v0.2, v1.0 runtime configurations.

**Scenario:** Run ADS for a representative CanSat mission/descent window.

**Acceptance:** no firmware reset or unrecovered peripheral failure; expected GPS/IMU/attitude fields are time-correlated where applicable; at least 95% of expected frames/cycles are present during the run; no gap exceeds the project-defined maximum.

### ADS-GEN-T13 — Tailored environmental/workmanship regression

**Applies to:** all hardware versions; especially v0.3 and v1.0.

**Scenario:** Verify ADS remains functional after handling, transport, assembly, and safe educational environmental screening.

**Acceptance:** no loose connectors, cracked solder joints, damaged traces, or damaged cables; pre/post functional baseline tests pass; any environmental levels are documented and kept within component limits.

## 8. Version-specific notes and gaps

- v0.3 is PCB-delivery-only in the current D2 corpus; runtime behavioral requirements should be inherited only when the PCB is integrated with a processor/firmware version.
- v1.0 does not include a Serial0 logging chain inside ADS; it models ADS Processing delivering data to OBCC by `Pointers` and `Returns` component exchanges.
- v1.0 does not explicitly carry the `At 5 Hz` note found in v0.1/v0.2; treat 5 Hz as a v0.1/v0.2 requirement unless another v1.0 requirement source exists.
- ADS MBSE now consistently names the IMU init state as ICM20948 in the D2 diagrams under `ADS/MBSE/`.

## 9. Reporting template

For each executed test, record:

- ADS version and D2 views covered.
- Hardware revision/BOM and firmware commit.
- Test date, operator, location, equipment, and calibration/truth source.
- Procedure deviations and environmental conditions.
- Raw data paths and analysis scripts.
- Pass/fail for each applicable acceptance criterion.
- Anomalies, corrective action, and retest status.
