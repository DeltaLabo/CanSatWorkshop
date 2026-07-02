# ISSUE-ADS-001 — ADS criteria, candidate list, and update register

## Context

The orchestrator is resolving `ADS-BLK-001` through `ADS-BLK-010` from `PM&SE/CON-003_Candidates_and_Definition_Blockers.md` §2.2. Read the high-level plan first:

- `PM&SE/ADS_Blocker_Resolution_Plan_2026-07-02.md`

Also read:

- `PM&SE/CON-003_Candidates_and_Definition_Blockers.md`
- `PM&SE/MBSE_Test_Plan_Assessment.md`
- `PM&SE/IVV.md`
- `ADS/README.md`
- `ADS/MBSE/tests/README.md`
- the ADS activity READMEs mentioned by the blockers

User-approved decisions to encode:

- v1.0 ADS must provide data internally to OBCC at 5 Hz; OBCC LoRa telemetry remains 2 s and samples the latest ADS data.
- ADS mission duration is 10 min.
- v0.2 I2C timeout should be represented as a constraint/code-analysis/instrumentation test rather than cluttering MBSE diagrams.
- External lab equipment in the assessment is available, but execution reports still need equipment IDs/calibration.
- Motors + tachometer are approved for angular-rate truth and should use statistics-backed methods if the tachometer reliability/calibration is adequate.
- Consumer phones are auxiliary for GPS; strict GPS `<5 m` pass requires controlled surveyed/open-sky truth or equivalent uncertainty control.

## Task

Create a central closure record:

- `PM&SE/ADS_Blocker_Closure_Record_2026-07-02.md`

The record must be self-contained and include:

1. A short statement of scope: definition-blocker resolution only, no test execution credit.
2. A table for `ADS-BLK-001` through `ADS-BLK-010` with:
   - blocker ID,
   - selected closure decision,
   - affected candidate/new tests,
   - affected existing tests,
   - execution prerequisites,
   - whether this issue closes the definition blocker or leaves a D2/execution follow-up.
3. A complete ADS candidate test list. At minimum include:
   - v1.0 ADS-to-OBCC 5 Hz delivery/freshness candidate or explicit update to `ADS-IVV-C-RATE-5HZ` / `ADS-IVV-FC-OBCC-DELIVERY`,
   - acceleration accuracy/units candidate,
   - heading/north accuracy candidate.
4. A list of updates to existing tests. At minimum include updates for:
   - `ADS-IVV-C-RATE-5HZ`,
   - `ADS-IVV-FC-MISSION-WINDOW`,
   - `ADS-IVV-FC-SERIAL`,
   - `ADS-IVV-FC-OBCC-DELIVERY`,
   - `ADS-IVV-C-I2C-5MS`,
   - `ADS-IVV-C-NOBLOCK`,
   - `ADS-IVV-C-POS-5M`,
   - `ADS-IVV-C-GYRO-30DPS`,
   - `ADS-IVV-FC-ATT` or a new heading candidate if heading is not folded into attitude.
5. Selected quantitative criteria, using the plan as baseline:
   - 10 min mission window; 3000 expected updates at 5 Hz.
   - 5 Hz nominal period 200 ms; select a reasonable jitter/worst-gap rule aligned with `PM&SE/IVV.md`. Prefer strict predeclared criteria over weak characterization.
   - Acceleration units in m/s² or g converted to m/s², not `deg/s²`.
   - Heading/north criterion with magnetic/reference controls.
   - GPS strict truth method; phones only auxiliary/limited unless uncertainty is controlled.
   - Gyro truth via motor + tachometer with `n=59` all-within-limit style evidence when making a strict claim.
6. A clear "follow-on D2/model update list" for anything not edited in this pass.

Do **not** update `CON-003` or the assessment in this issue; final integration will do that.

## Constraints

- Keep this as a PM&SE closure/decision record. Do not create schemas/parser/contract files in this issue; later issues handle those.
- Do not claim execution pass/fail.
- If you find contradictory existing criteria, record them in the closure record and choose the plan/user-approved decision unless there is a compelling project source reason not to.

## Acceptance criteria

- `PM&SE/ADS_Blocker_Closure_Record_2026-07-02.md` exists and is internally consistent.
- Every `ADS-BLK-001` through `ADS-BLK-010` appears exactly once in the blocker decision table.
- Candidate test list and existing-test update list are complete enough for later issues to use without rereading the whole project.
- The GPS phone limitation and tachometer strict-statistics decision are explicit.
- Commit your changes with a message like `ADS: record blocker criteria decisions`.

## Final response

Return a concise summary with:

- files changed,
- blocker decisions captured,
- any uncertainties or follow-up D2 updates.
