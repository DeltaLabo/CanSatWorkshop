# AMS-VV-FC-001 — Atmospheric measurement functional-chain acceptance test

- **SSIV / development version:** AMS `v1.0` final acceptance / flight readiness.
- **IADT method:** Testing / Demonstration.
- **Purpose:** Verify the v1.0 atmospheric measurement functional chain covering pressure, temperature, altitude calculation, processing, and OBCC measurement collection.
- **Traceability targets:** `AMS-UC-MeasureAtmosphere`, `[C] Accuracy < 1 hPa`, `[C] Accuracy < 0.5 Celsius, 10-40 °C range`, `[C] Resolution < 10m`, `AMS-FE-BadExposure`, `AMS-FE-StaleMeasurement`.
- **Expected report path:** `AMS/MBSE/tests/results/AMS-VV-FC-001/report.md`.
- **Status:** Model-defined; execution/report pending.

## Scope and assumptions

This activity covers the v1.0 atmospheric measurement functional chain and associated pressure, temperature, altitude, currentness, and evidence-logging pass/fail constraints. It uses `AMS-VV-CON-003` as a dependency for detailed environmental I2C read timeout proof (`≤5 ms`) and does not duplicate that fault-injection/timing activity.

Conservative assumptions recorded for execution:

1. The selected development version is AMS `v1.0` final acceptance only.
2. The test collects `n ≥ 30` paired pressure and temperature samples per operating point; reduced repetitions would be screening only and not final acceptance.
3. Temperature test point(s) are within `10–40 °C` and are established with a reference thermometer / stable thermal source.
4. Altitude resolution is verified by a modeled pressure-step method equivalent to 10 m using the standard-atmosphere rationale and recorded reference uncertainty.
5. OBCC result capture via VV-only logging/instrumentation does not bypass or replace the modeled BME280 → AMS Processing → OBCC chain.

## References cited in the model

- IVV skill / project IVV report-by-reference rules.
- Source model baseline: `AMS/MBSE/v1.0/AMS_v1.0_view1` through `view5`.
- AMS-R1: BME280 datasheet/product references in `AMS/MBSE/tests/references/`.
- AMS-R3/R4: environmental measurement and standard-atmosphere references.
- AMS-R5: GUM/NIST statistical and uncertainty references.
- AMS-R7: low-cost altitude-sensor context, used for altitude-resolution rationale only.

## Baseline views copied

Untouched copies of all AMS v1.0 `.d2` and `.png` views are in `baseline/`:

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

## Pass/fail constraints modeled in D2

Pass only if the modeled constraints in the D2 views are satisfied, including:

1. Collect `n ≥ 30` paired pressure and temperature samples per operating point before final acceptance statistics are computed.
2. Pressure passes iff `abs(bias) + U95 ≤ 1 hPa` for AMS pressure paired with the reference pressure.
3. Temperature passes iff `abs(bias) + U95 ≤ 0.5 °C` at tested point(s) inside the `10–40 °C` range.
4. Altitude passes iff a 10 m-equivalent pressure change is resolved with correct sign and uncertainty; the confidence interval for the measured altitude delta excludes zero.
5. OBCC collects current altitude and temperature results in the modeled order; stale data is not accepted as current.
6. VV-only logging/instrumentation records sample IDs, order/currentness, reference values, uncertainty inputs, raw AMS results, deviations, and anomalies without bypassing the modeled chain.
7. Detailed environmental I2C read timeout proof (`≤5 ms`) is a dependency on `AMS-VV-CON-003`, not duplicated here; any timeout or stale-current anomaly observed during this activity is still a failure or reportable anomaly.

## Environmental and configuration conditions

- Ambient thermometer reading, instrument IDs, calibration status, and uncertainties are recorded before repetitions.
- Pressure reference/calibrator and thermal reference/stable source are co-located with the BME280 measurement environment as applicable.
- Final acceptance exposure configuration blocks direct sunlight while preserving airflow; exposure-specific verification remains a dependency/context for `AMS-VV-CON-001` if separately executed.
- Bench supply provides stable 3V3/common ground and voltage/current evidence before and after sample batches.

## Viewpoints

- **Statistical significance:** `n ≥ 30` paired pressure/temperature samples per operating point; bias and expanded uncertainty (`U95`) are reported for pressure, temperature, and altitude-step results.
- **Fault hardening:** Detects BadExposure, stale measurements, swapped pressure/temperature branches, outliers, OBCC order/currentness errors, evidence gaps, and any observed timeout/stale OK behavior. Detailed I2C fault-timeout hardening is credited to `AMS-VV-CON-003`.
- **Report by reference:** The report should identify the as-tested article, firmware, instruments, raw data paths, statistical calculations, deviations, anomalies, waivers, and pass/fail rationale while referencing these model definitions rather than duplicating them.
