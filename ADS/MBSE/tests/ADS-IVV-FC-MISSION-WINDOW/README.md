# ADS-IVV-FC-MISSION-WINDOW — end-to-end runtime mission-window verification definition

**IADT method:** Demonstration/Testing with supporting Analysis.

**IVV source category:** functional chain / scenario, with linked component-exchange, allocation, and constraint observations.

**Selected SSIV/development scope:** ADS `v0.1`, `v0.2`, `v0.3`, and `v1.0`. Runtime mission-window execution applies to `v0.1`, `v0.2`, and `v1.0`; `v0.3` is an explicit PCB-delivery N/A branch because no runtime LC, CE, allocation, or functional chain is modeled.

**Traceability targets:** `ADS-MSN-CANSAT-DESCENT`; placeholders `ADS-CAP-GPS`, `ADS-CAP-IMU`, `ADS-CAP-ATT`, `ADS-CAP-INIT`, `ADS-CAP-DELIVERY`; feared events `ADS-FE-SILENT-SENSOR-FAIL`, `ADS-FE-STUCK-LOOP`, and `ADS-FE-CORRUPT-MEASUREMENT`. The `v0.3` N/A branch also references `ADS-CAP-PCB` / `ADS-CAP-DELIVERY`.

**References cited in diagrams:** IVV, NASA-SE, GEVS, ESA-CANSAT, SW/statistics references, and the ADS MBSE IVV plan `../README.md`. No external research was performed for this definition.

## Source-view copies

All D2 and PNG source views for the selected ADS versions were copied under `source_views/`:

- `source_views/v0.1/` — physical, logical, allocation, GPS position chain, Serial0 logging chain.
- `source_views/v0.2/` — physical, logical, allocation, GPS, angular velocity, attitude estimation, peripheral initialisation, Serial0 logging chains.
- `source_views/v0.3/` — physical PCB delivery view; used only for the N/A rationale.
- `source_views/v1.0/` — physical, logical, allocation, GPS, angular velocity, attitude estimation, peripheral initialisation chains.

## Definition-view catalogue

| View | Purpose |
|---|---|
| `definition_views/ADS_IVV_FC_MISSION_WINDOW_view1_cross_version_source_inventory.d2/png` | Cross-version runtime source inventory and explicit `v0.3` PCB-only N/A branch. |
| `definition_views/ADS_IVV_FC_MISSION_WINDOW_view2_physical_mission_window_setup.d2/png` | Physical mission-window setup with human conductor, run controller/timer, power source, PC/OBCC logger, GPS/IMU truth/stimulus tools, ambient monitor, analysis station, temporary PLs/CEs, and pass/fail constraints. |
| `definition_views/ADS_IVV_FC_MISSION_WINDOW_view3_verification_functional_allocation.d2/png` | Verification-only functional allocation for UUT observation, human actions, timer control, truth/stimulus, power logging, Serial0/OBCC capture, ambient monitoring, analysis, and IVV review. |
| `definition_views/ADS_IVV_FC_MISSION_WINDOW_view4_runtime_sequence_nominal_fault.d2/png` | Functional-chain style mission-window sequence with nominal runtime flow, v0.3 N/A path, fault-monitor branch, analysis, and verdict closure. |
| `definition_views/ADS_IVV_FC_MISSION_WINDOW_view5_evidence_traceability.d2/png` | Evidence package, traceability targets, analysis outputs, report locations, and blocked-prerequisite handling. |

## Version coverage and pass/fail criteria

| Version | Mission-window model elements covered | Pass/fail criteria |
|---|---|---|
| `v0.1` | GPS position chain and Serial0 logging chain: UBX-G7020-KT GPS, XIAO ESP32, GPS UART, `Read and store lat/lon`, getters, `Collect measurements`, UBX init state, `Log via Serial0`, PC monitor. | Pass if the selected `v0.1` article runs the **10 min / 600 s** mission window with no reset, no stuck loop, and no unrecovered GPS/UART failure; Serial0 records are parseable; expected GPS and UBX-init fields are present and time-correlated; modeled 5 Hz collection evidence accounts for **3000 expected update opportunities** (or exact measured-duration equivalent), every formal `n = 59` timing sample meets the predeclared interval limit, no unflagged stale/drop/duplicate record occurs, and no observed internal gap exceeds **400 ms**. Fail on missing required fields, unbounded UART wait, invalid/stale GPS accepted as valid, reset/stuck loop, unrecovered peripheral failure, gap `>400 ms`, or unapproved deviations. |
| `v0.2` | GPS, angular velocity, attitude estimation, peripheral initialisation, and Serial0 logging chains: GPS UART, IMU I2C, GPS/ICM init states, GPS fields, angular-rate fields, acceleration/magnetic-field/PRY fields, `Collect measurements`, `Log via Serial0`. | Pass if the selected `v0.2` article runs the **10 min / 600 s** mission window with no reset, no stuck loop, and no unrecovered GPS/IMU/UART/I2C failure; Serial0 records are parseable; GPS, IMU angular-rate, attitude, and init fields are present and time-correlated; modeled 5 Hz collection evidence accounts for **3000 expected update opportunities** (or exact measured-duration equivalent), every formal `n = 59` timing sample meets the predeclared interval limit, no unflagged stale/drop/duplicate record occurs, no observed internal gap exceeds **400 ms**, and injected/dispositioned faults are flagged or bounded without accepting corrupt/stale data as valid. |
| `v0.3` | PCB-only physical view: ADS PCB, GPS, ICM20948 IMU, backplane connector, footprints, UART/I2C/3V3 traces, manufacturing note. | Pass/N/A if `source_views/v0.3` is reviewed and confirms no runtime LC, CE, allocation, or functional chain exists. Fail if runtime mission-window behavior is claimed from `v0.3` without a modeled runtime architecture. |
| `v1.0` | Integrated CanSat ADS/backplane/OBCC runtime chains: GPS and IMU sensing on ADS PCB, ADS Processing on OBCC XIAO ESP32-S3, peripheral init, GPS/IMU/attitude functions, UART/I2C CEs, ADS Processing to OBCC `Pointers`/`Returns`, OBCC collection. | Pass if the selected integrated article runs the **10 min / 600 s** mission window with no reset, no stuck loop, no unrecovered GPS/IMU/backplane/OBCC delivery failure, and no invalid pointer/return behavior; OBCC evidence contains expected GPS, IMU, attitude, and init records; records are time-correlated with truth/timebase evidence; ADS-to-OBCC freshness follows `ADS-V10-DATA-FRESHNESS` / the shared PM&SE contract with 5 Hz request/response evidence, `status == VALID` only when `age_ms <= 400 ms`, exact non-`VALID` statuses for stale/no-data/timeout/fault/init-fail, no old data marked `VALID`, and 2 s LoRa telemetry treated only as packaging evidence. |

## Constraint coverage in this activity

- `Accuracy < 5 m` and `Accuracy < 30 deg/s`: mission-window evidence records field propagation and time correlation; formal accuracy closure should reference `ADS-IVV-FC-GPS` / `ADS-IVV-FC-ANG` unless this run also uses qualified truth/reference samples and the required analysis.
- `At 5 Hz`: directly observed for `v0.1` / `v0.2` through cycle/frame presence and gap analysis over the selected **10 min** mission window; for `v1.0`, observed through `ADS-V10-DATA-FRESHNESS` ADS-to-OBCC request/response evidence. The nominal period is 200 ms, the expected 10 min count is 3000 update opportunities, formal timing samples use `n = 59`, and no internal freshness gap may exceed 400 ms.
- `No blocking operations besides I2C or UART comms`, UART timeout `<=5 ms`, and `v1.0` I2C timeout `<=5 ms`: observed through reset/stuck-loop, health, timeout/fault, and gap evidence.
- Variable Getter and process/calculate `<5 ms` constraints: sampled through field freshness, corruption/staleness checks, and timing/fault evidence; formal unit-level closure may remain in linked constraint activities.

## Statistical and fault-hardening viewpoints

- **Statistical significance:** use complete mission-window logs. Repeated frames from one article are sustained-performance screening unless independence is justified. For cadence/frame delivery, report expected count, observed valid count, missing/stale count, worst gap, and whether the 95% expected-cycle/frame rule is satisfied. Use exact binomial/PDR confidence bounds only for population delivery claims. Use `n = 59` all-within-limit planning for 95/95 deadline claims.
- **Fault hardening:** exercise or explicitly disposition silent GPS/IMU, malformed/corrupt measurement, stale data, UART/I2C timeout, I2C NACK/stuck bus where applicable, reset/brownout, stuck loop, unrecovered peripheral failure, and `v1.0` OBCC pointer/return faults. Invalid/stale/corrupt data shall not be accepted as valid nominal mission-window data.

## Required execution conditions

Before execution, record or select:

- ADS version/SSIV, copied source-view package, hardware revision/BOM, UUT identifier, firmware commit/build, logger build/configuration, and operator.
- Mission/descent window duration is selected as **10 min / 600 s**. Expected internal ADS 5 Hz update opportunities are **3000** over the full window, or exact measured-duration equivalent. Maximum allowed internal freshness gap is **400 ms**; formal deadline/timing claims use `n = 59` all-within-limit observations.
- Power source/battery-simulator mode, voltage/current limits, reset/brownout detection method, and power-log path.
- GPS truth/stimulus method and uncertainty; IMU/orientation/rate truth or reference method for `v0.2`/`v1.0`; fault-injection method or explicit disposition.
- Timebase synchronization method for ADS logs, truth/reference logs, run-controller markers, and PC/OBCC logger.
- Ambient monitor model/ID/calibration status and temperature/humidity readings before and after the run; do not execute if required equipment calibration or truth/reference configuration is unknown.

## Expected report locations

Reports should reference this modeled definition and store evidence under:

- `../results/ADS-IVV-FC-MISSION-WINDOW/v0.1/`
- `../results/ADS-IVV-FC-MISSION-WINDOW/v0.2/`
- `../results/ADS-IVV-FC-MISSION-WINDOW/v0.3/`
- `../results/ADS-IVV-FC-MISSION-WINDOW/v1.0/`

Each report shall identify referenced source and definition views, selected SSIV/version, as-tested configuration, actual environmental/equipment conditions, raw evidence, analysis settings, pass/fail/N/A/blocked rationale, deviations, anomalies, waivers, assumptions, limitations, and retest status.

## Status

Modeled definition ready for review with mission duration and maximum-gap criteria selected. Execution remains pending; no pass/fail credit is claimed until reports bind evidence to the selected article and configuration.

## Assumptions and execution records

- Controlled SSIV/version labels are inferred from folder names; no separate SSIV document was found.
- Mission/capability/feared-event IDs are controlled ADS-plan trace labels until modeled explicitly.
- Mission duration and maximum allowed internal freshness gap are selected as 10 min / 600 s and 400 ms respectively; the D2 definition views carry those selected criteria.
- Truth/reference equipment, calibration IDs, exact implementation data-schema revision, hardware revisions, and firmware commits are report-time execution records.
- `v0.2` does not model an explicit I2C `<=5 ms` timeout constraint; handle as a fault-hardening observation/gap unless superseded by implementation evidence.
