# AMS-VV-CON-001 — Block sunlight, allow airflow verification definition

- **SSIV / development version:** AMS v1.0 final acceptance / flight readiness.
- **IADT method:** Inspection / Demonstration.
- **Purpose:** verify the integrated AMS physical configuration satisfies `[C] Block sunlight, allow airflow` without creating `AMS-FE-BadExposure` conditions.
- **Traceability:** `[C] Block sunlight, allow airflow`; `AMS-FE-BadExposure`; `AMS-UC-MeasureAtmosphere`; temperature-accuracy constraint context.
- **References cited in diagram titles/comments:** IVV, AMS-R3, AMS-R6, and AMS-R5 for optional paired-sample screening.
- **Expected report path:** `AMS/MBSE/tests/results/AMS-VV-CON-001/report.md`.

## Baseline views copied

Baseline copies of all AMS v1.0 D2/PNG views are in `baseline/` and are refreshed to the selected v1.0 definition baseline.

## Test-definition views

| View | Purpose |
|---|---|
| `AMS_VV_CON_001_view1_physical_exposure_testbench.d2` | Physical exposure inspection/demonstration testbench with inspector/operator, sun-simulator or bright lamp, airflow indicator/anemometer, ambient/reference thermometer, camera, evidence repository, and shade/ventilation fixture. |
| `AMS_VV_CON_001_view2_logical_exposure_testbench.d2` | VV-only logical instrumentation and component exchanges for procedure/status, exposure readings, optional BME280 temperature sample records, and evidence archiving. |
| `AMS_VV_CON_001_view3_functional_allocation_exposure.d2` | Allocation of operator, equipment, evidence, fixture, and VV-only instrumentation functions; includes pass/fail constraints. |
| `AMS_VV_CON_001_view4_sunlight_airflow_demonstration_chain.d2` | Inspection/demonstration sequence for configuring the integrated article, checking line-of-sight sunlight blocking, confirming airflow path, recording conditions, optional paired bias screening, and archiving evidence. |

Rendered PNGs with matching names are generated beside each D2 file.

## Pass/fail constraints

Pass only if all modeled constraints in the D2 views are satisfied:

1. The inspected/demonstrated article is the AMS v1.0 integrated CanSat/AMS configuration.
2. No direct solar or bright-lamp line of sight reaches the BME280 in the modeled installed configuration.
3. The airflow path to the BME280 / AMS module is not obstructed by the shade/vent fixture, wiring, evidence equipment, or CanSat structure.
4. Ambient/reference conditions are recorded before demonstration repetitions, including instrument identity, location, timestamp, and uncertainty/tolerance.
5. Optional paired temperature-bias screening, if used, records `n ≥ 30` paired samples and passes only when `|bias| + U95 ≤ 0.5 °C`; this hardens the exposure assessment but does **not** replace `AMS-VV-FC-001` measurement-accuracy verification and does not close temperature response time.
6. Any blocked airflow, direct radiation path, heat-soak bias without mitigation, or unmodeled temporary shielding fails unless controlled by waiver and/or model update.

## Environmental conditions and equipment formalization

The model includes explicit external actors/equipment for the inspector/operator, inspection light or sun-simulator, airflow indicator/anemometer or smoke/flow indicator, ambient/reference thermometer, camera/video recorder, evidence repository, and shade/ventilation fixture. The exact execution evidence shall be predeclared before the run: instrument IDs and calibration status or function checks, ambient/reference readings, timestamps, photos/video or flow evidence, fixture configuration, and optional `n >= 30` paired temperature-bias data if used. The ambient/reference thermometer is read before demonstration evidence is credited.

## Statistical and fault-hardening viewpoints

- **Statistical basis:** 100% inspection/demonstration of the final integrated configuration. If paired temperature-bias screening is used, apply AMS-R5/GUM/NIST-style uncertainty handling with `n ≥ 30` paired samples; otherwise no statistical accuracy claim is made.
- **Fault hardening:** direct solar/bright-lamp heating, blocked ventilation, fixture/wiring/equipment obstruction, heat-soak bias, and unmodeled temporary shielding are explicit fail modes.

## Scope boundary

This activity verifies physical/environmental exposure suitability for the AMS installation. It provides context for `AMS-VV-FC-001` accuracy evidence and for later phase-2 temperature response-time interpretation, but it does not duplicate the full atmospheric measurement accuracy verification and it does not claim response-time closure. Response-time `<=60 s` requires the future response-time activity/extension with declared temperature step, reference data, synchronized/correlated timestamps, exposure state, and response calculation.

## Assumptions

- The lamp model, airflow indicator model, ambient thermometer model, fixture design, instrument IDs/calibration or function checks, timestamps, photo/video/flow evidence method, and optional paired-sample plan are predeclared before execution and recorded in the report.
- A sun-simulator or bright inspection lamp is an acceptable conservative proxy for checking direct line-of-sight exposure when real sunlight is not safely repeatable.
