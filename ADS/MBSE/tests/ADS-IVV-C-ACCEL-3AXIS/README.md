# ADS-IVV-C-ACCEL-3AXIS — 3-axis linear acceleration units and accuracy candidate

**IADT method:** Testing with supporting Analysis.

**IVV source category:** constraint-derived candidate for `ADS-BLK-002` and supporting attitude-chain evidence.

**Selected SSIV/development scope:** ADS `v0.2` and `v1.0` where an ICM20948 acceleration/attitude chain is modeled. `v0.1` has no IMU acceleration behavior and `v0.3` is PCB-only unless a later behavior baseline is added.

**Traceability targets:** ADS acceleration requirement, `ADS-CAP-IMU`, `ADS-CAP-ATT`, `ADS-FE-CORRUPT-MEASUREMENT`, and `ADS-FE-STUCK-LOOP`.

**Status:** README-only candidate definition ready for review; execution and D2/model update are pending. This file intentionally does not edit D2/PNG source or definition views.

## Requirement interpretation and selected criteria

- The measured quantity is **3-axis linear acceleration**.
- Controlled verification units are **`m/s²`**. If firmware/logs expose acceleration in `g`, convert with **`g0 = 9.80665 m/s²`** before comparison.
- The legacy `deg/s²` wording is not a valid linear-acceleration unit and shall not be used as the oracle for this candidate.
- Strict pass threshold after declared calibration/bias handling:
  - driven axis at `+1g` or `-1g`: `|measured - expected| + U <= 1.0 m/s²`;
  - off-axis channels expected near `0`: `|measured| + U <= 0.75 m/s²`;
  - vector norm in each static face: `||a||` error from `g0` plus expanded uncertainty `U <= 1.0 m/s²`.
- `U` is the predeclared expanded uncertainty/guard band covering fixture alignment, sensor noise, calibration/bias residuals, timestamp matching, and analysis rounding.

## Verification fixture

Use a non-dynamic six-face orientation fixture or equivalent static gravity reference that can place each IMU sensing axis in `+1g` and `-1g` orientations. The fixture shall:

- hold the ADS UUT without slip or vibration during stable sampling;
- identify the ADS body-frame axis/sign convention and the expected sensor-frame mapping;
- provide orientation photos for all six faces;
- keep power, cabling, and logging from biasing or moving the UUT;
- record ambient temperature and any warm-up/calibration state.

## Procedure

1. Record UUT ID, hardware revision, firmware commit/build, logger/schema version, operator, date/time, equipment IDs, and fixture identification.
2. Record the accelerometer calibration/bias procedure before collecting pass/fail samples. Bias removal is allowed only if the method is predeclared and reproducible.
3. Place the UUT in six static orientations: `+X`, `-X`, `+Y`, `-Y`, `+Z`, `-Z` relative to gravity.
4. For each face, wait for stable data and collect **`n = 59`** valid acceleration samples for a strict tolerance-style claim. Smaller sets or `n >= 30` continuous-accuracy sets are characterization unless the report states the weaker confidence basis.
5. Convert any raw `g` fields to `m/s²` using `g0 = 9.80665 m/s²`.
6. For each sample and orientation, check finite values, freshness/status markers, axis mapping, sign, driven-axis error, off-axis leakage, vector norm, and saturation flags.
7. Run the analysis script on the raw log. The script shall compute per-axis bias, standard deviation, guard-banded sample errors, vector-norm errors, and all pass/fail flags.
8. Repeat or hold the run if the fixture moved, the calibration state changed, the logger lost time correlation, or fault markers appeared during nominal sampling.

## Sample/statistical basis

- Strict workshop acceptance uses **`n = 59` all-within-limit samples per face**. Every retained nominal sample shall satisfy the driven-axis, off-axis, vector-norm, finite/fresh, sign, and axis-mapping checks after applying the uncertainty guard band.
- Reports shall also retain continuous-measurement statistics from `PM&SE/IVV.md`: mean, bias, standard deviation, confidence interval/expanded uncertainty, raw samples, and analysis output.
- A campaign with fewer than `n = 59` valid samples per face, uncontrolled fixture uncertainty, or unrecorded calibration/bias handling is **characterization only** and shall not close the strict acceleration requirement.

## Fault handling

Stale, missing, non-finite, saturated/out-of-range, impossible-unit, wrong-axis, wrong-sign, I2C-fault, timeout, no-data, or initialization-failed values shall not be accepted as valid acceleration samples. Old data may be carried only with a non-`VALID` status. A nominal pass fails if any such condition is hidden as valid data at the observation point.

## Required evidence

- Raw acceleration samples and timestamps/status fields for all six faces.
- Orientation/fixture photos and axis/sign convention notes.
- Calibration/bias record and uncertainty/guard-band calculation.
- Analysis script revision, command/settings, output tables, and plots.
- UUT serial/identifier, hardware revision, firmware commit/build, logger/schema version, equipment IDs/calibration or function-check records, ambient/power records, deviations, anomalies, and retest status.

## D2/model follow-up

Add a modeled constraint/activity package and regenerated D2/PNG views for this candidate, then link it from `ADS-IVV-FC-ATT` and the ADS test index. Until that model update is made, this README is the controlled textual candidate definition and execution planning source.
