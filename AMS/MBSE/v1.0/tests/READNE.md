# AMS v1.0 Testing Plan

This plan defines reference-based verification tests for the Atmospheric Measurement System (AMS) represented by the Capella Physical Architecture D2 views in `AMS/MBSE/v1.0/`. The plan is intentionally stored as `READNE.md` to match the requested filename.

## 1. Architecture scope read from the D2 views

D2/Capella semantics used: `[PC]` physical components, `[LC]` logical components, `[F]` functions, `[PL]` physical links, `[CE]` component exchanges, `[FE]` functional exchanges, and `[C]` constraints.

Reviewed views:

The AMS repository states that the latest complete split views are in `AMS/MBSE/v1.0/`; these are the baseline for this plan. The older `v0.1` and PCB-only `v0.2` views were checked for context but are not modified by this testing plan.

- `AMS_v1.0_view1_physical.d2` / `.png`: AMS PCB with BME280, backplane connector, I2C + 3V3 traces, CanSat/backplane/OBCC physical integration, and the constraint to block sunlight while allowing airflow.
- `AMS_v1.0_view2_logical.d2` / `.png`: AMS Sensing on BME280; AMS Processing and OBCC on XIAO ESP32-S3; I2C CE; pointer/return CE; constraints for variable getter pattern, I2C timeout ≤ 5 ms, processing/calculation < 5 ms, and no blocking except I2C/UART.
- `AMS_v1.0_view3_functional_allocation.d2` / `.png`: pressure measurement, temperature measurement, I2C response, BME280 init-state retrieval, pressure/temperature reads, altitude calculation, temperature processing, measurement collection, init-state collection, and constraints for pressure accuracy < 1 hPa, temperature accuracy < 0.5 °C in 10–40 °C, and altitude resolution < 10 m.
- `AMS_v1.0_view4_atmospheric_measurement_chain.d2` / `.png`: runtime pressure/temperature polling, processing, altitude/temperature results, and measurement collection.
- `AMS_v1.0_view5_peripheral_initialisation_chain.d2` / `.png`: BME280 init-state polling and collection under implementation timing/non-blocking constraints.

## 2. Reference corpus

Search results and retrieved sources are saved under `tests/references/`:

- Search records: `references/searches/*.json`
- Retrieved standards/datasheets/literature: `references/sources/`
- Source index: `references/README.md`

Key references used in this plan:

- ISO 7726: instruments/methods for thermal-environment measurements; air-temperature accuracy and response-time concepts.
- WMO-No. 8: meteorological measurement practice, traceability, calibration, metadata, temperature exposure/shelter effects, pressure measurement.
- ICAO Doc 7488 / ICAO Standard Atmosphere: pressure-altitude relationship and standardized atmospheric calculations.
- Bosch Sensortec BME280 datasheet: operating ranges, pressure/temperature accuracy, pressure output resolution, noise, IIR/oversampling, I2C interface.
- NXP/Nexperia UM10204 I2C specification: SDA/SCL, START/STOP, ACK/NACK, standard/fast-mode timing behavior.
- JCGM 100:2008 (GUM) and NIST/SEMATECH: uncertainty reporting, confidence, tolerance intervals, and measurement-process statistics.
- CanSat mission/environmental testing literature: telemetry/pressure/temperature expectations and hot, vibration, and drop test methods.

## 3. Common statistical rules

Apply these rules to all quantitative tests unless a row states otherwise.

1. **Raw data retention:** save timestamped raw readings, reference readings, device state/result codes, and environmental metadata for each test run.
2. **Traceability:** use calibrated reference instruments where available. Record certificate, stated uncertainty, calibration date, and placement.
3. **Uncertainty:** report bias, standard deviation, and expanded uncertainty. Use GUM-style combined uncertainty; if no better coverage factor is justified, use `k ≈ 2` for approximately 95% coverage.
4. **Sample size:** use at least `n = 30` stable samples per operating point for accuracy tests. For non-normal or robustness claims, use at least `n = 60` trials; zero failures then bounds failure probability to roughly `< 5%` at 95% confidence by the rule of three.
5. **Tolerance intervals:** when claiming population coverage without assuming normality, use NIST-style non-parametric tolerance intervals; `n ≈ 46` gives about 90% population coverage at 95% confidence using min/max bounds.
6. **Pass/fail with uncertainty:** a measurement limit is met only when the measured statistic plus its expanded uncertainty remains inside the requirement.
7. **Pre/post checks:** environmental and mechanical tests must include a functional check before and after exposure.

## 4. Tests, one per scenario

| ID | Scenario type | Scenario / risk | Test to perform | Statistical basis | Pass criteria |
|---|---|---|---|---|---|
| AMS-T01 | Expected physical integration | AMS PCB, BME280, backplane connector, 3V3, GND, SDA, and SCL are correctly assembled and connected. | PCB/assembly inspection and electrical continuity test: verify part marking, orientation, solder joints, connector pinout, 3V3 at the BME280, I2C pullups, and no SDA/SCL/3V3/GND shorts. | 100% inspection for one flight article; record measured voltages/resistances. | Correct BME280/BMP280-compatible address configured; 3V3 within component limits; no shorts; SDA/SCL continuity through connector/backplane; visual workmanship accepted. |
| AMS-T02 | Expected startup use case | OBCC asks for BME280 init state during peripheral initialization. | Initialization-state test: cold boot and warm reset the AMS/OBCC and request init state via the variable-getter interface. Include one disconnected-sensor run. | `n = 30` successful boots plus 5 induced-fault boots. | All nominal boots return success and valid state; all disconnected-sensor boots return a documented non-success code without blocking. |
| AMS-T03 | Feared event | I2C no-ACK, stuck bus, connector bounce, or missing BME280 blocks the processor. | I2C timeout/recovery fault-injection test: inject NACK, disconnect/reconnect sensor, and force SDA/SCL fault if safe; measure call duration and recovery. | `n ≥ 60` fault trials; zero hangs demonstrates <5% hang probability at 95% confidence. | Every I2C read fails or succeeds within ≤5 ms; system resumes later reads without reset; no unbounded blocking. |
| AMS-T04 | Expected software integration | AMS Processing exposes `(Read X, Process X)` or `(Read X, Calculate Y)` variable getters to OBCC through pointers/returns. | Variable-getter contract test: call each getter with valid pointer, null/invalid pointer if API permits, and boundary values from mocked sensor data. | `n ≥ 1000` timed calls per getter for performance; boundary cases all checked. | Return codes match template; output units/scaling documented; no overflow/underflow misreporting; 99.9th percentile processing/calculation time <5 ms. |
| AMS-T05 | Expected measurement use case | BME280 measures ambient temperature in the 10–40 °C requirement range. | Temperature accuracy calibration test at 10 °C, 25 °C, and 40 °C against a calibrated reference in a stable chamber or controlled enclosure. | `n ≥ 30` paired samples per set point; compute bias, RMSE, 95% CI, and expanded uncertainty. | For each set point, `|mean bias| + U95 ≤ 0.5 °C`; no unexplained outlier exceeds the limit after reference uncertainty is considered. |
| AMS-T06 | Feared event | Temperature response is too slow after entering a different air mass. | Temperature step-response test: move the sensor/module between two stable air temperatures within 10–40 °C and estimate t90. | At least 5 step repetitions; report mean, max, and 95% CI of t90. | Maximum observed t90 ≤ 60 s and `mean t90 + U95 ≤ 60 s`. |
| AMS-T07 | Feared event | Direct sunlight or blocked airflow causes false temperature readings. | Solar/airflow exposure test: compare shaded/ventilated configuration to reference during heat-lamp or sunlight exposure; include an unshaded negative-control run if practical. | `n ≥ 30` paired samples per configuration after stabilization. | In the intended shaded/ventilated configuration, `|mean bias| + U95 ≤ 0.5 °C`; physical inspection confirms no direct solar line-of-sight and unobstructed airflow path. |
| AMS-T08 | Expected measurement use case | BME280 measures atmospheric pressure accurately enough for AMS requirements. | Pressure accuracy test at ambient and at least two offset pressures within mission range using a calibrated barometer or pressure chamber. | `n ≥ 30` paired samples per pressure point; compute bias, RMSE, drift during run, and expanded uncertainty. | For each point, `|mean bias| + U95 ≤ 1 hPa`; pressure noise is low enough for altitude calculation in AMS-T09. |
| AMS-T09 | Expected derived-value use case | AMS calculates altitude/resolution from pressure and detects ≤10 m altitude changes. | Altitude/pressure-delta test using a pressure chamber, a vertical building/stairs reference, or a calibrated pressure simulator. Test a nominal 10 m equivalent pressure step (`≈130 Pa` using 13 Pa/m) and a larger step. | Paired `n ≥ 30` bottom/top or low/high samples; paired CI for pressure delta; monotonicity check. | Detected 10 m-equivalent pressure change has correct sign and 95% CI excludes zero; calculated altitude error plus uncertainty ≤10 m for the tested deltas. |
| AMS-T10 | Expected runtime use case | OBCC collects pressure-derived altitude and temperature measurements at ≥5 Hz. | End-to-end update-rate test from BME280 read through AMS Processing to OBCC collection for at least 10 min. | At 5 Hz, expect ≥3000 samples. Report interval distribution, dropped/stale frames, and Wilson lower confidence bound for delivery success. | Mean update rate ≥5 Hz; no interval >1 s; 99th percentile interval ≤250 ms; 95% lower confidence bound on successful non-stale samples ≥99%. |
| AMS-T11 | Feared event | Pressure and temperature branches are swapped, stale, or unit-converted incorrectly. | Data-integrity chain test with mocked or chamber-driven known inputs: independently vary pressure and temperature and verify only the intended output changes. | At least 10 levels or steps per variable; compare to expected transfer function. | Pressure changes affect pressure/altitude only; temperature changes affect temperature only except known pressure temperature-coefficient effects; units are Pa/hPa/kPa/°C as specified in interface documentation. |
| AMS-T12 | Feared event | Backplane, screws, connector, or traces intermittently fail under handling/launch vibration. | Mechanical/interconnect robustness test: pre-check, vibration/flex/drop exposure based on CanSat environmental test practice, then post-check electrical and functional tests. | `n ≥ 60` connector flex/contact disturbance observations where practical; zero intermittent failures target <5% failure probability at 95% confidence. | No visible damage or moved components; continuity remains valid; AMS-T02, AMS-T05 spot check, AMS-T08 spot check, and AMS-T10 short run still pass after exposure. |
| AMS-T13 | Feared event | Launch-pad heating or mission thermal/pressure profile causes AMS malfunction. | Environmental profile test: hot soak consistent with CanSat environmental practice, plus pressure profile or simulated pressure values covering expected descent range. | Functional measurements during exposure; `n ≥ 30` samples at each plateau. | AMS remains operational; no reset/hang; temperature and pressure outputs remain within requirements after applying reference uncertainty; post-test functional checks pass. |
| AMS-T14 | Feared event | Long-run drift, self-heating, or memory/state accumulation corrupts measurements during a workshop/mission run. | Long-duration stability test: operate AMS continuously for at least 2 h at stable ambient conditions and compare to reference. | Time-series analysis; bias trend slope, Allan/rolling standard deviation, and outlier count. | Drift over 2 h is <0.5 °C temperature and <1 hPa pressure, or is characterized by a correction; no increasing latency trend; no unhandled errors. |

## 5. Minimum test artifacts to collect

For each test, store under a future `tests/results/<test-id>/` folder:

- Test procedure actually used and deviations from this plan.
- Calibration/reference instrument metadata.
- Raw CSV/JSON logs with timestamps and result codes.
- Summary plots for temperature, pressure, altitude, update interval, and fault-recovery timing where applicable.
- Statistical calculation sheet/script.
- Pass/fail decision with uncertainty and confidence stated.
