# ADS-IVV-C-HEADING-NORTH — heading/north quantitative accuracy candidate

**IADT method:** Testing with supporting Analysis.

**IVV source category:** constraint-derived candidate for `ADS-BLK-003` and supporting attitude-chain evidence.

**Selected SSIV/development scope:** ADS `v0.2` and `v1.0` where magnetometer/attitude data are modeled. `v0.1` has no IMU/attitude behavior and `v0.3` is PCB-only unless a later behavior baseline is added.

**Traceability targets:** ADS north/orientation requirement, `ADS-CAP-ATT`, `ADS-CAP-IMU`, `ADS-FE-CORRUPT-MEASUREMENT`, and `ADS-FE-STUCK-LOOP`.

**Status:** README-only candidate definition ready for review; execution and D2/model update are pending. This file intentionally does not edit D2/PNG source or definition views.

## Requirement interpretation and selected criteria

- The candidate verifies a quantitative heading/north claim, not only attitude plausibility.
- Controlled heading may be referenced to either:
  - **true north**, using a surveyed/known reference line, GNSS baseline, sun-shadow/survey method, or equivalent documented method; or
  - **magnetic north**, using a calibrated magnetic reference with local declination treatment explicitly recorded.
- The reported ADS heading shall state whether it is true or magnetic heading. If the ADS output and the reference use different north conventions, apply the declared declination correction before comparison.
- Strict pass threshold: circular heading error plus expanded uncertainty/guard band **`<= 10°`** at every tested orientation.
- Minimum orientation set for a strict claim: headings near **0°, 90°, 180°, and 270°**.

## Reference setup and controls

Use a non-magnetic fixture/site and heading reference that can hold repeatable yaw orientations. The setup shall include:

- non-magnetic turntable, board, jig, or marked ground reference; no ferrous tools, magnets, high-current wiring, motors, or active radios close enough to disturb the measurement;
- declared true-north or magnetic-north reference method, including declination source/date when needed;
- magnetometer/IMU calibration state before and after the run;
- local magnetic disturbance survey or comparison check against the reference before collecting nominal data;
- level/alignment notes, yaw index marks, fixture photos, ambient/power record, and UUT/logging configuration.

## Procedure

1. Record UUT ID, hardware revision, firmware commit/build, logger/schema version, operator, date/time, heading reference method, equipment IDs, calibration status, declination value if used, and site/fixture identification.
2. Perform the declared IMU/magnetometer calibration and record the calibration state. If calibration fails or is not repeatable, place the activity on HOLD.
3. Establish the reference north line or magnetic reference away from disturbances. Record the disturbance survey result before nominal sampling.
4. Place the UUT at minimum yaw orientations near 0°, 90°, 180°, and 270° relative to the selected reference. Additional intermediate headings may be added but do not replace the cardinal set.
5. At each heading, wait for stable readings and collect **`n = 59`** valid heading samples for a strict tolerance-style claim. Smaller sets or `n >= 30` continuous-accuracy sets are characterization unless the report states the weaker confidence basis.
6. Compute circular error for each sample, e.g. `wrap_to_180(ADS_heading_deg - reference_heading_deg)` after any declination correction.
7. Apply the predeclared expanded uncertainty/guard band covering reference setup, alignment, declination, calibration residuals, magnetic disturbance, sensor noise, timestamp matching, and analysis rounding.
8. Repeat or hold the run if the fixture shifts, the reference is disturbed, calibration state changes, or invalid/fault markers appear during nominal sampling.

## Sample/statistical basis

- Strict workshop acceptance uses **`n = 59` all-within-limit samples per heading orientation**. Every retained nominal sample shall have `|circular_error| + U <= 10°` and valid/fresh status.
- Reports shall also retain continuous-measurement statistics from `PM&SE/IVV.md`: mean circular error, circular standard deviation, confidence/expanded uncertainty, raw samples, and analysis output.
- A campaign with fewer than `n = 59` valid samples per heading, uncontrolled reference uncertainty, missing declination treatment, or missing calibration/disturbance records is **characterization only** and shall not close the strict heading/north requirement.

## HOLD/fail rules

Place the activity on HOLD, or mark the strict claim failed/limited, if any of the following occurs:

- magnetic contamination, moving ferrous objects, motors, high-current wiring, or RF/electrical disturbances are present and not quantified/guard-banded;
- true-vs-magnetic north convention is unknown or declination correction is missing when needed;
- the fixture cannot repeatably hold cardinal yaw orientations;
- magnetometer/IMU calibration is stale, failed, or unrecorded;
- ADS heading is stale, missing, non-finite, saturated, disturbed, I2C-faulted, no-data, timeout, or init-fail but still marked valid;
- circular error plus guard band exceeds `10°` for any retained strict sample.

## Required evidence

- Site/reference method description, declination treatment, disturbance survey, and fixture/reference photos.
- Raw ADS heading/magnetic/attitude samples, timestamps, status/freshness fields, and reference-heading records for each orientation.
- Calibration status before/after, uncertainty/guard-band calculation, and circular-error analysis script/output.
- UUT serial/identifier, hardware revision, firmware commit/build, logger/schema version, equipment IDs/calibration or function-check records, ambient/power records, deviations, anomalies, and retest status.

## Relation to attitude plausibility

`ADS-IVV-FC-ATT` remains a plausibility/repeatability activity unless this candidate, or an equivalent modeled heading constraint, is executed with the controls above. A plausible yaw change alone shall not be credited as quantitative north accuracy closure.

## D2/model follow-up

Add a modeled constraint/activity package and regenerated D2/PNG views for this candidate, then link it from `ADS-IVV-FC-ATT` and the ADS test index. Until that model update is made, this README is the controlled textual candidate definition and execution planning source.
