# ISSUE-ADS-004 — ADS acceleration, heading, and accuracy-method candidate tests

## Context

The orchestrator is resolving ADS blockers from `PM&SE/CON-003_Candidates_and_Definition_Blockers.md` §2.2. Read first:

- `PM&SE/ADS_Blocker_Resolution_Plan_2026-07-02.md`
- `PM&SE/ADS_Blocker_Closure_Record_2026-07-02.md`
- `PM&SE/IVV.md`
- `ADS/README.md`
- `ADS/MBSE/tests/README.md`
- `ADS/MBSE/tests/ADS-IVV-FC-ATT/README.md`
- `ADS/MBSE/tests/ADS-IVV-C-GYRO-30DPS/README.md`
- `ADS/MBSE/tests/ADS-IVV-C-POS-5M/README.md`

Relevant blockers:

- `ADS-BLK-002`: Acceleration accuracy requirement is not separately quantified or assigned.
- `ADS-BLK-003`: North/heading accuracy requirement lacks quantitative acceptance criterion.
- Accuracy-method portion of `ADS-BLK-010`: GPS `<5 m`, gyro `<30 deg/s`, and related accuracy tests need truth/reference/statistics methods.

User/orchestrator decisions to preserve:

- Clarify acceleration units as m/s² or g converted to m/s², not `deg/s²`.
- Consumer mobile phones are auxiliary only for strict GPS truth unless uncertainty is independently controlled. Strict GPS pass should use surveyed/open-sky reference point or equivalent truth with uncertainty guard band.
- Motors + tachometer are approved for gyro truth. Use strict statistics-backed evidence (`n=59` all-within-limit style where making a strict claim) when the tachometer reliability/calibration is adequate.

## Task

Add or update ADS textual candidate definitions for acceleration and heading/north, and update existing accuracy test READMEs with truth/reference/statistics methods.

You may create README-only candidate folders under `ADS/MBSE/tests/` if no existing activity cleanly covers the requirement. Suggested IDs:

- `ADS-IVV-C-ACCEL-3AXIS`
- `ADS-IVV-C-HEADING-NORTH`

If you choose different IDs, explain why and update the test index consistently.

## Required content for acceleration candidate

Define a candidate test with at least:

- Requirement clarified as 3-axis linear acceleration in m/s², with any g conversion explicit.
- Fixture: non-dynamic six-face orientation fixture or equivalent gravity reference.
- Procedure: place each IMU axis at +1g and -1g orientations, record stable samples, check sign, units, axis mapping, vector norm, and off-axis leakage.
- Quantitative criterion: choose a workshop-feasible threshold and state uncertainty guard band. Prefer a clear threshold such as per-axis/vector error within a specified m/s² limit after calibration/bias handling.
- Sample/stat basis aligned with `PM&SE/IVV.md`: use `n=59` all-within-limit for strict tolerance-style claims, or explicitly label smaller samples as characterization.
- Fault handling: stale/non-finite/saturated/I2C-fault values must not be accepted as valid.
- Evidence: raw samples, orientation photos, calibration/bias record, analysis script/output, UUT/firmware/equipment IDs.

## Required content for heading/north candidate

Define a candidate test with at least:

- Quantitative heading error threshold, e.g. a selected maximum degrees from reference north.
- Reference setup: true-north or magnetic-north reference, declination treatment, non-magnetic fixture, calibration state, magnetic disturbance controls.
- Procedure: multiple yaw orientations (minimum cardinal directions), stable samples, circular angle-error calculation.
- Sample/stat basis aligned with `PM&SE/IVV.md`, preferably `n=59` all-within-limit per orientation for strict claims.
- HOLD/fail rules for magnetically contaminated environments or uncontrolled references.
- Evidence: site/reference method, fixture photos, raw samples, calibration status, analysis output, UUT/firmware/equipment IDs.

## Existing README update requirements

Update these as applicable:

- `ADS/README.md`: clarify the acceleration requirement units if the current `30 deg/s^2` wording is wrong/ambiguous. Do not silently change intent; note that the test candidate controls units/criterion.
- `ADS/MBSE/tests/README.md`: add candidate rows or update coverage/status for acceleration and heading/north; add the truth/reference decisions if there is a suitable coverage-gap section.
- `ADS/MBSE/tests/ADS-IVV-C-POS-5M/README.md`: add GPS truth/reference method with surveyed reference as strict path and phones as auxiliary/limited path.
- `ADS/MBSE/tests/ADS-IVV-C-GYRO-30DPS/README.md`: add motor/tachometer truth method and strict sample/stat criteria.
- `ADS/MBSE/tests/ADS-IVV-FC-ATT/README.md`: if heading remains a separate candidate, state that attitude plausibility does not close the heading/north quantitative requirement unless the new heading candidate is executed.

Avoid editing D2 diagrams unless absolutely necessary. If you leave D2 updates for later, list them explicitly in the relevant README/status text.

## Acceptance criteria

- Acceleration and heading/north candidate definitions exist either as new README folders or clear entries in the ADS test index.
- Quantitative criteria and sample/stat basis are selected, not TBD.
- GPS and gyro accuracy READMEs contain usable truth/reference/statistics methods.
- The phone-as-GPS-reference limitation is explicit.
- The tachometer/motor strict-statistics method is explicit.
- Commit your changes with a message like `ADS: define accuracy candidate criteria`.

## Final response

Return a concise summary with files changed, candidate IDs created/updated, selected thresholds, and any D2 follow-up.
