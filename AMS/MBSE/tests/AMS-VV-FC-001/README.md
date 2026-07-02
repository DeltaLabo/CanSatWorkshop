# AMS-VV-FC-001 — Atmospheric measurement functional-chain acceptance test

- **SSIV / development version:** AMS `v1.0` final acceptance / flight readiness.
- **IADT method:** Testing / Demonstration.
- **Purpose:** Verify the v1.0 atmospheric measurement functional chain covering pressure, temperature, altitude calculation, processing, and OBCC measurement collection.
- **Traceability targets:** `AMS-UC-MeasureAtmosphere`, `[C] Accuracy < 1 hPa`, `[C] Accuracy < 0.5 Celsius, 10-40 °C range`, `[C] Resolution < 10m`, `AMS-FE-BadExposure`, `AMS-FE-StaleMeasurement`.
- **Expected report path:** `AMS/MBSE/tests/results/AMS-VV-FC-001/report.md`.
- **Status:** Model-defined; execution/report pending.

## Scope and assumptions

This activity covers the v1.0 atmospheric measurement functional chain and associated pressure, temperature, altitude, currentness/freshness, and evidence-logging pass/fail constraints. It uses `AMS-VV-CON-003` as a dependency for detailed environmental I2C read timeout proof (`≤5 ms`) and does not duplicate that fault-injection/timing activity. It is the atmospheric-chain extension point for `AMS-V10-DATA-FRESHNESS`. `AMS-V10-TEMP-RESPONSE-60S` is not created or closed in this folder during this phase; response-time `<=60 s` requires a separate modeled phase-2 chain/folder or an explicitly modeled FC-001 extension with the response oracle below.

Conservative assumptions recorded for execution:

1. The selected development version is AMS `v1.0` final acceptance only.
2. The test collects `n ≥ 30` paired pressure and temperature samples per operating point; reduced repetitions would be screening only and not final acceptance.
3. Temperature test point(s) are within `10–40 °C` and are established with a reference thermometer / stable thermal source.
4. Altitude resolution is verified by a modeled pressure-step method equivalent to 10 m using the standard-atmosphere rationale and recorded reference uncertainty.
5. OBCC result capture via VV-only logging/instrumentation does not bypass or replace the modeled BME280 → AMS Processing → OBCC chain.
6. The shared ADS/AMS freshness contract applies whenever this activity claims OBCC currentness/freshness: AMS supports `5 Hz` request/response; every `2 s` telemetry push treats data as fresh only when `status == VALID` and `age_ms <= 400 ms`; non-valid data uses one of `STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, or `INIT_FAIL`.

## References cited in the model

- IVV skill / project IVV report-by-reference rules.
- Shared ADS/AMS freshness contract: [`../../../../PM&SE/contracts/sensor_obcc_freshness_contract.md`](../../../../PM&SE/contracts/sensor_obcc_freshness_contract.md).
- Source model baseline: `AMS/MBSE/v1.0/AMS_v1.0_view1` through `view5`.
- AMS-R1: BME280 datasheet/product references in `AMS/MBSE/tests/references/`.
- AMS-R3/R4: environmental measurement and standard-atmosphere references.
- AMS-R5: GUM/NIST statistical and uncertainty references.
- AMS-R7: low-cost altitude-sensor context, used for altitude-resolution rationale only.

## Baseline views copied

Refreshed copies of all AMS v1.0 `.d2` and `.png` views are in `baseline/` and match the selected v1.0 freshness/status definition baseline:

- `AMS_v1.0_view1_physical.*`
- `AMS_v1.0_view2_logical.*`
- `AMS_v1.0_view3_functional_allocation.*`
- `AMS_v1.0_view4_atmospheric_measurement_chain.*`
- `AMS_v1.0_view5_peripheral_initialisation_chain.*`

## Test-definition views

| View | Purpose |
|---|---|
| `AMS_VV_FC_001_view1_physical_testbench.d2/png` | Physical testbench with test operator, host PC/logger, pressure reference/calibrator, reference thermometer/stable thermal source, ambient thermometer, bench supply, evidence repository, and VV-only logger access port. |
| `AMS_VV_FC_001_view2_logical_testbench.d2/png` | Logical testbench showing UUT logical components, VV-only acceptance instrumentation, measurement evidence interface, component exchanges, references, and report/evidence flow. |
| `AMS_VV_FC_001_view3_functional_allocation_testbench.d2/png` | Functional allocation of UUT functions plus test-operator, reference-instrument, host-logger, bench-supply, evidence-repository, and VV-only instrumentation functions. |
| `AMS_VV_FC_001_view4_atmospheric_measurement_acceptance_chain.d2/png` | Atmospheric measurement chain extended through reference measurement, AMS processing, OBCC collection, comparison, staleness/order checks, and evidence archive. |
| `AMS_VV_FC_001_view5_altitude_resolution_pressure_step_chain.d2/png` | Dedicated altitude-resolution pressure-step sequence for the `Resolution < 10m` constraint. |

## Temperature response-time candidate/update path

`AMS-V10-TEMP-RESPONSE-60S` is not closed by the current accuracy/altitude chain alone. The conservative path is to model a standalone response-time activity unless adding the following oracle to this folder remains clearer:

- apply a declared temperature step using a stable thermal source/chamber or documented fixture;
- capture reference thermometer data and raw AMS temperature samples with synchronized or correlated timestamps;
- verify the reported temperature reaches the defined final/reference condition within `<=60 s`;
- record UUT ID, firmware/configuration ID, exposure/airflow state, uncertainty, deviations, and the response-time calculation.

Until that separate phase-2 modeled definition or explicit FC-001 extension and execution evidence exist, `AMS-VV-FC-001` closes accuracy/currentness only, not response time. No `AMS-V10-TEMP-RESPONSE-60S` folder is created here.

## Pass/fail constraints

Pass only if the modeled constraints in the D2 views are satisfied and the following oracle/evidence requirements are met:

1. Collect `n ≥ 30` paired pressure and temperature samples per operating point before final acceptance statistics are computed.
2. Pressure passes iff `abs(bias) + U95 ≤ 1 hPa` for AMS pressure paired with the reference pressure.
3. Temperature passes iff `abs(bias) + U95 ≤ 0.5 °C` at tested point(s) inside the `10–40 °C` range.
4. Altitude passes iff a 10 m-equivalent pressure change is resolved with correct sign and uncertainty; the confidence interval for the measured altitude delta excludes zero.
5. OBCC collects altitude and temperature results in the modeled order; the fresh/current value oracle is exactly `status == VALID` and `age_ms <= 400 ms` at the AMS-to-OBCC observation point.
6. Non-valid values shall carry one of the shared statuses (`STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, `INIT_FAIL`) and shall not be treated as current or fresh; old/default/previous values after timeout/fault/init/no-data/stale conditions shall not remain marked `VALID`.
7. VV-only logging/instrumentation records timestamp/sample-ID/sequence/order evidence, sample/request timestamps or equivalent monotonic correlation, `age_ms`, status, reference pressure/temperature values, uncertainty inputs, raw AMS pressure/temperature/altitude values, deviations, and anomalies without bypassing the modeled chain.
8. Detailed environmental I2C read timeout proof (`≤5 ms`) is a dependency on `AMS-VV-CON-003`, not duplicated here; any `TIMEOUT`, `SENSOR_FAULT`, stale-valid, or currentness anomaly observed during this activity is still a failure or reportable anomaly.

## Environmental and configuration conditions

- Ambient thermometer reading, instrument IDs, calibration status, and uncertainties are recorded before repetitions.
- Pressure reference/calibrator and thermal reference/stable source are co-located with the BME280 measurement environment as applicable.
- Final acceptance exposure configuration blocks direct sunlight while preserving airflow; exposure-specific verification remains a dependency/context for `AMS-VV-CON-001` if separately executed.
- Bench supply provides stable 3V3/common ground and voltage/current evidence before and after sample batches.

## Viewpoints

- **Statistical significance:** `n ≥ 30` paired pressure/temperature samples per operating point; bias and expanded uncertainty (`U95`) are reported for pressure, temperature, and altitude-step results.
- **Fault hardening:** Detects BadExposure, `STALE`/`NO_DATA` measurements, `TIMEOUT`/`SENSOR_FAULT` propagation gaps, swapped pressure/temperature branches, outliers, OBCC order/currentness errors, evidence gaps, and any old-data-as-`VALID` behavior. Detailed I2C fault-timeout hardening is credited to `AMS-VV-CON-003`.
- **Report by reference:** The report should identify the as-tested article, firmware, instruments, raw data paths, statistical calculations, deviations, anomalies, waivers, and pass/fail rationale while referencing these model definitions rather than duplicating them.
