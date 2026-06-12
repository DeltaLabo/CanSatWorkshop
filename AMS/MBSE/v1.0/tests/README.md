# AMS v1.0 Testing Plan

This folder contains the reference corpus and verification plan for the Atmospheric Measurement System (AMS) Capella Physical Architecture views stored in `AMS/MBSE/v1.0/`. The older `v0.1` views and the `v0.2` PCB-delivery view were also read for context; the executable baseline for this plan is the latest complete split-view set in `v1.0`.

No Capella/D2 diagrams are modified by this plan.

Project-wide IVV conventions, statistics, rate terminology, fault semantics, and artifact paths are defined in [`../../../../PM&SE/IVV.md`](../../../../PM&SE/IVV.md). In this plan, `≥5 Hz` is the internal AMS/OBCC measurement-collection rate used by control logic; v1.0 LoRa downlink telemetry remains the OBCC/DPS `2 s` cadence. At subsystem level, a BME280 getter/startup check returns a bounded result code; at system level, OBCC blocks operational-mode entry on critical startup failure but does not allow a mid-flight sensor fault to block the scheduler.

## 1. Architecture scope read from the D2 views

D2/Capella semantics used: `[PC]` physical components, `[LC]` logical components, `[F]` functions, `[PL]` physical links, `[CE]` component exchanges, `[FE]` functional exchanges, and `[C]` constraints.

Reviewed baseline views:

- `AMS_v1.0_view1_physical.d2` / `.png`: CanSat physical integration containing AMS Module, AMS PCB, BME280, backplane connector, Backplane PCB, OBCC Module, XIAO ESP32-S3, connector/cable/trace/fixture/screw physical links, and the constraint to block sunlight while allowing airflow.
- `AMS_v1.0_view2_logical.d2` / `.png`: AMS Sensing on BME280; AMS Processing and OBCC on XIAO ESP32-S3; I2C component exchange; pointer/return component exchanges; constraints for variable-getter implementation, I2C timeout ≤ 5 ms, processing/calculation < 5 ms, and no blocking except I2C/UART.
- `AMS_v1.0_view3_functional_allocation.d2` / `.png`: pressure measurement, temperature measurement, I2C response, BME280 init-state retrieval, pressure/temperature reads, altitude calculation, temperature processing, measurement collection, init-state collection, and constraints for pressure accuracy < 1 hPa, temperature accuracy < 0.5 °C in 10–40 °C, and altitude resolution < 10 m.
- `AMS_v1.0_view4_atmospheric_measurement_chain.d2` / `.png`: runtime pressure/temperature polling, processing, altitude/temperature results, and measurement collection.
- `AMS_v1.0_view5_peripheral_initialisation_chain.d2` / `.png`: BME280 init-state polling and collection under timing and non-blocking constraints.

Context views read but not used as the primary baseline:

- `AMS/MBSE/v0.1/`: early subsystem split views, including a serial logging chain that is not present in the v1.0 baseline.
- `AMS/MBSE/v0.2/`: PCB-delivery physical view with manufacturability constraint.

## 2. Reference corpus

Search records and retrieved sources are saved under `tests/references/`:

- Search records: `references/searches/*.json`
- Retrieved standards/datasheets/literature: `references/sources/`
- Source index: `references/README.md`

Key references used in this plan:

- ISO 7726: instruments and methods for thermal-environment measurements; supports temperature accuracy, sensor placement, and response-time planning.
- WMO-No. 8: meteorological measurement practice, calibration, traceability, metadata, uncertainty, exposure/shelter effects, and pressure measurement.
- ICAO Doc 7488 / ICAO Standard Atmosphere: pressure-altitude relationship and standardized atmospheric calculations.
- Bosch Sensortec BME280 datasheet: operating ranges, pressure/temperature accuracy, pressure output resolution, noise, oversampling/filtering, and I2C interface behavior.
- NXP/Nexperia UM10204 I2C specification: SDA/SCL, START/STOP, ACK/NACK, and bus timing/interface behavior.
- JCGM 100:2008 (GUM) and NIST/SEMATECH Engineering Statistics Handbook: uncertainty reporting, confidence, tolerance intervals, and measurement-process statistics.
- CanSat environmental/mission guides and low-cost altitude-sensor literature: practical CanSat pressure/temperature telemetry expectations and environmental stress testing.

## 3. Common statistical rules

Apply the project-wide policy in [`../../../../PM&SE/IVV.md`](../../../../PM&SE/IVV.md) unless a test row states a stricter criterion.

1. **Raw data retention:** save timestamped raw readings, reference readings, device state/result codes, and environmental metadata.
2. **Traceability:** use calibrated reference instruments where available. Record certificate, stated uncertainty, calibration date, and placement.
3. **Uncertainty:** report bias, standard deviation, confidence interval, and expanded uncertainty. Use GUM-style combined uncertainty; if no better coverage factor is justified, use `k ≈ 2` for approximately 95% coverage.
4. **Measurement accuracy:** use at least `n ≥ 30` stable samples per operating point and guard-band pass/fail decisions with uncertainty.
5. **Binary/fault-injection claims:** use exact one-sided binomial / Clopper-Pearson bounds; `29/29` supports R90/C95 and `59/59` supports about R95/C95.
6. **Timing/deadline limits:** use `n = 59` representative in-limit samples for a 95/95 non-parametric tolerance claim.
7. **Pre/post checks:** environmental and mechanical tests must include a functional check before and after exposure.

## 4. Tests, one per scenario

| ID | Scenario type | Scenario / risk | Test to perform | Statistical basis | Pass criteria |
|---|---|---|---|---|---|
| AMS-T01 | Expected physical integration | AMS PCB, BME280, backplane connector, 3V3, GND, SDA, and SCL are correctly assembled and connected. | PCB/assembly inspection and electrical continuity test: verify part marking, orientation, solder joints, connector pinout, 3V3 at the BME280, I2C pullups, and no SDA/SCL/3V3/GND shorts. | 100% inspection for each flight/workshop article; record measured voltages/resistances. | Correct BME280-compatible part/address; 3V3 within component limits; no shorts; SDA/SCL continuity through connector/backplane; workmanship accepted. |
| AMS-T02 | Expected PCB delivery | The AMS PCB can be manufactured and soldered consistently enough for integration. | Manufacturability/workmanship test using the selected process: inspect milled/etched traces, footprints, connector alignment, solder joints, and reflow/manual solder results. | Inspect all boards in the batch; log defect count by defect type. If estimating yield, use exact binomial confidence bounds. | No critical defect on flight/workshop boards; all reworked defects documented; minimum usable-board yield target agreed before production is met. |
| AMS-T03 | Expected startup use case | OBCC asks for BME280 init state during peripheral initialization. | Initialization-state test: cold boot and warm reset the AMS/OBCC and request init state through the variable-getter interface. Include disconnected-sensor runs. | `29/29` successful boots for R90/C95 plus at least 5 induced-fault boots. | All nominal boots return success and valid state; disconnected-sensor boots return documented non-success state without blocking so OBCC can prevent operational-mode entry as a critical startup fault. |
| AMS-T04 | Feared event | I2C no-ACK, stuck bus, connector bounce, or missing BME280 blocks the processor. | I2C timeout/recovery fault-injection test: inject NACK, disconnect/reconnect sensor, and force SDA/SCL fault if safe; measure call duration and recovery. | `n = 59` representative fault trials for a 95/95 timeout claim; classify every trial pass/fail. | Every I2C read fails or succeeds within ≤5 ms; runtime faults return a documented error/result code, later reads can recover without reset, and there is no unbounded blocking. |
| AMS-T05 | Expected software integration | AMS Processing exposes `(Read X, Process X)` or `(Read X, Calculate Y)` variable getters to OBCC through pointers/returns. | Variable-getter contract test: call each getter with valid pointer, null/invalid pointer if API permits, and boundary values from mocked sensor data. | `n ≥ 1000` timed calls per getter for performance; boundary cases all checked. | Return codes match template; output units/scaling documented; no overflow/underflow misreporting; 99.9th percentile processing/calculation time <5 ms. |
| AMS-T06 | Expected measurement use case | BME280 measures ambient temperature in the 10–40 °C requirement range. | Temperature accuracy calibration at 10 °C, 25 °C, and 40 °C against a calibrated reference in a stable chamber or controlled enclosure. | `n ≥ 30` paired samples per set point; compute bias, RMSE, 95% CI, and expanded uncertainty. | For each set point, `|mean bias| + U95 ≤ 0.5 °C`; no unexplained outlier exceeds the limit after reference uncertainty is considered. |
| AMS-T07 | Feared event | Temperature response is too slow after entering a different air mass. | Temperature step-response test: move the sensor/module between two stable air temperatures within 10–40 °C and estimate t90. | At least 5 step repetitions; report mean, max, and 95% CI of t90. | Maximum observed t90 ≤ 60 s and `mean t90 + U95 ≤ 60 s`. |
| AMS-T08 | Feared event | Direct sunlight or blocked airflow causes false temperature readings. | Solar/airflow exposure test: compare shaded/ventilated configuration to reference during heat-lamp or sunlight exposure; include an unshaded negative-control run if practical. | `n ≥ 30` paired samples per configuration after stabilization. | In the intended shaded/ventilated configuration, `|mean bias| + U95 ≤ 0.5 °C`; physical inspection confirms no direct solar line-of-sight and unobstructed airflow path. |
| AMS-T09 | Expected measurement use case | BME280 measures atmospheric pressure accurately enough for AMS requirements. | Pressure accuracy test at ambient and at least two offset pressures within mission range using a calibrated barometer or pressure chamber. | `n ≥ 30` paired samples per pressure point; compute bias, RMSE, drift during run, and expanded uncertainty. | For each point, `|mean bias| + U95 ≤ 1 hPa`; pressure noise is low enough for altitude calculation in AMS-T10. |
| AMS-T10 | Expected derived-value use case | AMS calculates altitude/resolution from pressure and detects ≤10 m altitude changes. | Altitude/pressure-delta test using a pressure chamber, vertical building/stairs reference, or calibrated pressure simulator. Test a nominal 10 m equivalent pressure step (`≈130 Pa` using 13 Pa/m) and a larger step. | Paired `n ≥ 30` bottom/top or low/high samples; paired CI for pressure delta; monotonicity check. | Detected 10 m-equivalent pressure change has correct sign and 95% CI excludes zero; calculated altitude error plus uncertainty ≤10 m for the tested deltas. |
| AMS-T11 | Expected runtime use case | OBCC collects pressure-derived altitude and temperature measurements internally at ≥5 Hz. | End-to-end update-rate test from BME280 read through AMS Processing to OBCC collection for at least 10 min. | At 5 Hz, expect ≥3000 samples. Report interval distribution, dropped/stale frames, and exact one-sided 95% lower confidence bound for non-stale delivery success. | Mean internal update rate ≥5 Hz; no interval >1 s; 99th percentile interval ≤250 ms; 95% lower confidence bound on successful non-stale samples ≥99%. |
| AMS-T12 | Feared event | Pressure and temperature branches are swapped, stale, or unit-converted incorrectly. | Data-integrity chain test with mocked or chamber-driven known inputs: independently vary pressure and temperature and verify only the intended output changes. | At least 10 levels or steps per variable; compare to expected transfer function. | Pressure changes affect pressure/altitude only; temperature changes affect temperature only except known pressure temperature-coefficient effects; units are Pa/hPa/kPa/°C as specified. |
| AMS-T13 | Feared event | Backplane, screws, connector, cable, or traces intermittently fail under handling/launch vibration. | Mechanical/interconnect robustness test: pre-check, vibration/flex/drop exposure based on CanSat environmental test practice, then post-check electrical and functional tests. | `n = 59` connector flex/contact disturbance observations where practical for about R95/C95 zero-failure evidence. | No visible damage or moved components; continuity remains valid; AMS-T03, AMS-T06 spot check, AMS-T09 spot check, and AMS-T11 short run still pass after exposure. |
| AMS-T14 | Feared event | Launch-pad heating or mission thermal/pressure profile causes AMS malfunction. | Environmental profile test: hot/cold soak consistent with CanSat practice, plus pressure profile or simulated pressure values covering expected descent range. | Functional measurements during exposure; `n ≥ 30` samples at each plateau. | AMS remains operational; no reset/hang; temperature and pressure outputs remain within requirements after applying reference uncertainty; post-test functional checks pass. |
| AMS-T15 | Feared event | Long-run drift, self-heating, or memory/state accumulation corrupts measurements during a workshop/mission run. | Long-duration stability test: operate AMS continuously for at least 2 h at stable ambient conditions and compare to reference. | Time-series analysis; bias trend slope, rolling standard deviation, and outlier count. | Drift over 2 h is <0.5 °C temperature and <1 hPa pressure, or is characterized by a correction; no increasing latency trend; no unhandled errors. |

## 5. Coverage by modeled element or constraint

| Modeled item / constraint | Covered by |
|---|---|
| Physical components and links: AMS PCB, BME280, connectors, backplane, OBCC, screws/fixtures/traces/cable | AMS-T01, AMS-T02, AMS-T13 |
| `[CE] I2C` and `[FE]` pressure/temperature/init-state requests and responses | AMS-T03, AMS-T04, AMS-T09, AMS-T11 |
| Pointer/return component exchanges and variable-getter template | AMS-T05 |
| Pressure accuracy `< 1 hPa` | AMS-T09, AMS-T13, AMS-T14, AMS-T15 |
| Temperature accuracy `< 0.5 °C`, 10–40 °C | AMS-T06, AMS-T07, AMS-T08, AMS-T13, AMS-T14, AMS-T15 |
| Altitude resolution `< 10 m` | AMS-T10 |
| I2C timeout `≤ 5 ms` and no blocking except I2C/UART | AMS-T04, AMS-T11 |
| Processing/calculation `< 5 ms` | AMS-T05, AMS-T11 |
| Block sunlight while allowing airflow | AMS-T08 |
| Peripheral initialization functional chain | AMS-T03, AMS-T04 |
| Atmospheric measurement functional chain | AMS-T06 through AMS-T12 |

## 6. Minimum test artifacts to collect

For each test, store evidence under `results/<test-id>/` inside this `tests/` folder:

- Test procedure actually used and deviations from this plan.
- Model baseline and as-tested hardware/software configuration.
- Calibration/reference instrument metadata.
- Raw CSV/JSON logs with timestamps, raw sensor values, processed values, and result codes.
- Summary plots for temperature, pressure, altitude, update interval, and fault-recovery timing where applicable.
- Statistical calculation sheet/script.
- Pass/fail decision with uncertainty and confidence stated.
