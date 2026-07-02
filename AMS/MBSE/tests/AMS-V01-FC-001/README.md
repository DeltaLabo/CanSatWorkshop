# AMS-V01-FC-001 — v0.1 functional-chain breadboard verification

- **SSIV / development version:** AMS `v0.1`, readiness gate to `v0.2` PCB delivery.
- **IADT method:** Testing / Demonstration.
- **Purpose:** Verify execution behavior of the v0.1 atmospheric measurement chain, BME280 init-state chain, and Serial0 logging chain on the breadboard.
- **Traceability targets:** `AMS-v0.1-to-v0.2-readiness`, `AMS-UC-MeasureAtmosphere`, `AMS-UC-InitializePeripheral`, `AMS-UC-LogSerialTelemetry`, `AMS-FE-SensorBusFault`.
- **Expected report path:** `AMS/MBSE/tests/results/AMS-V01-FC-001/report.md`.
- **Status:** Model-defined; execution/report pending.

## Scope and exclusions

This activity covers functional-chain/scenario behavior and constraint evidence for the v0.1 breadboard. It deliberately does **not** duplicate Issue 001 / `AMS-V01-INTEG-001`, which covers physical-component/link presence, component-exchange presence/intent, and allocation inspection/analysis.

Conservative assumptions recorded for execution:

1. The selected development version is AMS `v0.1` only.
2. The breadboard characterization point is a stable ambient bench point within `10–40 °C`; the BME280 is shaded from direct radiant heating, ventilated, and co-located with the reference instruments.
3. The atmospheric test collects at least `n ≥ 30` stable paired pressure/temperature samples at that point and reports bias, standard deviation, confidence interval, and expanded uncertainty (`U95`).
4. The serial/init smoke chain executes at least `5` nominal power-up/log repetitions as readiness screening only, not as a reliability claim.
5. Altitude readiness uses `13 Pa/m`; a `10 m` equivalent pressure change is `130 Pa`. If a controlled/reference pressure delta sufficient to resolve that step is not available, altitude resolution is recorded as a v0.1-to-v0.2 readiness limitation rather than claimed closed.
6. Temperature-response `≤60 s` is not claimed by this ambient characterization unless the as-run report derives the result from `AMS-V10-TEMP-RESPONSE-60S` or adds a controlled annex defining t0, final/reference condition, and timestamp correlation.
7. Detailed I2C fault-timeout hardening is not closed here unless controlled fault evidence is included; otherwise the derivation path is `AMS-VV-CON-003`, or the report records a readiness limitation.

## References cited in the model

- IVV skill / project IVV report-by-reference rules.
- Source model baseline: `AMS/MBSE/v0.1/AMS_v0.1_view1` through `view6`.
- AMS-R1: BME280 datasheet/product references in `AMS/MBSE/tests/references/`.
- AMS-R2: I2C specification references for timeout/fault context.
- AMS-R3/R4: meteorological/standard-atmosphere references.
- AMS-R5: GUM/NIST statistical and uncertainty references.
- AMS-R6: CanSat bench/environmental context references.

## Baseline views copied

Untouched copies of all AMS v0.1 `.d2` and `.png` views are in `baseline/`:

- `AMS_v0.1_view1_physical.*`
- `AMS_v0.1_view2_logical.*`
- `AMS_v0.1_view3_functional_allocation.*`
- `AMS_v0.1_view4_atmospheric_measurement_chain.*`
- `AMS_v0.1_view5_peripheral_initialisation_chain.*`
- `AMS_v0.1_view6_serial_logging_chain.*`

## Test-definition views

| View | Purpose |
|---|---|
| `AMS_V01_FC_001_view1_physical_testbench.d2/png` | Physical testbench with bench operator, host PC serial logger, reference thermometer, reference pressure instrument, bench power/current monitor, optional logic analyzer/timer, and VV-only breadboard probe points. |
| `AMS_V01_FC_001_view2_logical_testbench.d2/png` | Logical testbench showing I2C target behavior, Serial0 payload logging, VV-only FC instrumentation, evidence repository exchanges, and traceability constraints. |
| `AMS_V01_FC_001_view3_functional_allocation_testbench.d2/png` | Functional allocation of UUT functions plus test-equipment, operator, reference-instrument, and VV-only instrumentation functions. |
| `AMS_V01_FC_001_view4_atmospheric_measurement_test_chain.d2/png` | Atmospheric measurement chain extended through reference measurement, sample pairing, serial capture, comparison, uncertainty calculation, timing check, and evidence archive. |
| `AMS_V01_FC_001_view5_serial_init_smoke_test_chain.d2/png` | Power-up/init-state/Serial0 smoke chain with payload parsing, field-order/units checks, staleness checks, responsiveness monitoring, anomaly capture, and evidence archive. |

## Pass/fail constraints modeled in D2

Pass only if the modeled constraints in the D2 views are satisfied, including:

1. Collect `n ≥ 30` stable paired pressure/temperature samples for the breadboard characterization point before computing atmospheric pass/fail statistics.
2. Pressure passes iff `|P_AMS - P_ref| + U95 ≤ 1 hPa` for the paired sample set.
3. Temperature passes iff `|T_AMS - T_ref| + U95 ≤ 0.5 °C` and the test point is inside `10–40 °C` with shaded/ventilated BME280 exposure.
4. Altitude readiness passes iff the tested pressure delta demonstrates `≤10 m` equivalent resolution using `13 Pa/m = 130 Pa`; otherwise record a readiness limitation.
5. Temperature-response `≤60 s` is not credited unless derived from `AMS-V10-TEMP-RESPONSE-60S` or an execution annex defining t0, final/reference condition, and timestamp correlation.
6. Serial output contains BME280 init state plus measurement fields in expected v0.1 order/units; no stale, old, or default measurement may be logged as current.
7. Nominal read/process/calculate/logging steps complete within modeled constraints (`I2C read timeout ≤5 ms`, process/calculate `<5 ms`) or explicitly reference `AMS-VV-CON-003` for detailed fault-timeout proof.
8. No unbounded blocking occurs during nominal serial logging; only modeled I2C/UART waits are allowed.
9. Reference instrument IDs/calibration, ambient/reference readings, shaded/ventilated exposure state, voltage/current, raw serial logs, timing traces if used, deviations, and anomalies are archived for the report.

## Viewpoints

- **Statistical significance:** Atmospheric characterization uses `n ≥ 30` stable paired samples at the v0.1 breadboard point and reports bias, standard deviation, confidence interval, and expanded uncertainty (`U95`). Smoke repetitions are readiness screening only.
- **Fault hardening:** The activity detects stale/old/default data, swapped/missing serial fields, missing init state, bus non-response/hang symptoms, and unbounded blocking. It does not claim full I2C fault-injection or temperature-response coverage unless the as-run report adds controlled evidence or references the explicit derivation paths above.
- **Report by reference:** The report should identify the as-tested breadboard, firmware, instruments, raw data paths, deviations, anomalies, waivers, and pass/fail rationale while referencing these model definitions rather than duplicating them.
