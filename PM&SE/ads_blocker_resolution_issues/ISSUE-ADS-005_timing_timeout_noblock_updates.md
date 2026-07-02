# ISSUE-ADS-005 — ADS timing, mission-window, I2C-timeout, and no-blocking updates

## Context

The orchestrator is resolving ADS blockers from `PM&SE/CON-003_Candidates_and_Definition_Blockers.md` §2.2. Read first:

- `PM&SE/ADS_Blocker_Resolution_Plan_2026-07-02.md`
- `PM&SE/ADS_Blocker_Closure_Record_2026-07-02.md`
- `PM&SE/IVV.md`
- `ADS/README.md`
- `ADS/MBSE/tests/README.md`
- `ADS/MBSE/tests/ADS-IVV-C-RATE-5HZ/README.md`
- `ADS/MBSE/tests/ADS-IVV-FC-MISSION-WINDOW/README.md`
- `ADS/MBSE/tests/ADS-IVV-C-I2C-5MS/README.md`
- `ADS/MBSE/tests/ADS-IVV-C-NOBLOCK/README.md`
- `ADS/MBSE/tests/ADS-IVV-FC-OBCC-DELIVERY/README.md` if needed for 5 Hz v1.0 semantics

Relevant blockers:

- `ADS-BLK-001`: v1.0 ADS-to-OBCC 5 Hz semantics conflict with current v1.0 N/A rationale.
- `ADS-BLK-004`: mission-window duration and maximum gap not selected.
- `ADS-BLK-005`: 5 Hz jitter/worst-gap tolerance not selected.
- `ADS-BLK-008`: v0.2 I2C timeout not explicitly modeled; user prefers constraint/code-analysis test over convoluted MBSE diagrams.
- `ADS-BLK-009`: firmware/source/build map/instrumentation criteria for no-blocking not confirmed.

User/orchestrator decisions:

- v1.0 ADS must deliver data to OBCC at 5 Hz internally; v1.0 LoRa telemetry remains 2 s and samples latest ADS data.
- Mission duration is 10 min.
- Expected 5 Hz updates over 10 min: 3000.
- Use strict, predeclared timing criteria consistent with `PM&SE/IVV.md`; avoid weak after-the-fact characterization.
- v0.2 I2C timeout should be treated as a constraint-derived code-analysis/instrumentation activity, not a source-diagram modeling exercise.

## Task

Apply textual README/test-definition updates for the timing and software-behavior blockers.

## Required criteria to select and encode

For 5 Hz rate/freshness:

- Nominal period: 200 ms.
- Define mean-rate, interval, worst-gap, stale/drop/duplicate, and timestamp continuity criteria.
- Use `PM&SE/IVV.md` timing policy: `n=59` representative samples with every sample meeting the limit for formal 95/95-style timing claims.
- Select concrete thresholds. Suggested baseline unless you find a stronger project rule:
  - mean valid update rate over the evaluated window `>= 5.0 Hz`,
  - strict timing sample: `n=59` consecutive representative inter-update intervals, each `<= 250 ms`,
  - full 10 min mission window: at least 3000 valid produced/available ADS updates or a predeclared equivalent accounting for exact measured duration, no unflagged stale/duplicate samples, no reset/stuck loop, and no gap `> 400 ms`,
  - OBCC-consumed ADS sample age at telemetry packaging is reported; stale/error flag if above the selected freshness threshold.
- If you choose different thresholds, justify them clearly.

For mission window:

- Duration: 10 min.
- Expected internal ADS updates: 3000 at 5 Hz.
- Pass/fail: no reset, no stuck loop, no unrecovered GPS/IMU/backplane/OBCC-delivery failure, required fields present/time-correlated, invalid/stale/corrupt data not accepted as valid, expected records/update criteria met, max gap criterion met.

For v0.2 I2C timeout:

- Update `ADS-IVV-C-I2C-5MS` so v0.2 is no longer just an undefined model gap. It should be a constraint-derived code-analysis/instrumentation branch or explicitly dispositioned as a controlled gap/waiver if code access is absent.
- Keep the source-diagram rationale: do not force this into MBSE diagrams if it would make them convoluted.
- Criteria should include 5 ms timeout/error behavior, NACK/stuck/wrong-address/partial-read fault cases, and invalid data not accepted as valid.

For no-blocking:

- Define required source/build map or equivalent instrumentation access.
- Define heartbeat/progress deadline. Suggested baseline: observable loop/ADS-processing heartbeat at least every 250 ms during nominal 5 Hz operation, and no mission-window gap above 400 ms under fault cases unless stale/error is reported and safe behavior is maintained.
- Define instrumentation overhead allowance. Suggested baseline: timing hooks/logging overhead must be measured and must be `<=5%` of the 200 ms period or `<=5 ms`, whichever is stricter for the claim being made; otherwise the verdict is limited/blocked.
- Reports must identify firmware commit/build, compiler/toolchain, symbols/map file or instrumentation method, and analysis script revision.

## Files likely to edit

- `ADS/MBSE/tests/ADS-IVV-C-RATE-5HZ/README.md`
- `ADS/MBSE/tests/ADS-IVV-FC-MISSION-WINDOW/README.md`
- `ADS/MBSE/tests/ADS-IVV-C-I2C-5MS/README.md`
- `ADS/MBSE/tests/ADS-IVV-C-NOBLOCK/README.md`
- `ADS/MBSE/tests/README.md` if the summary/status rows must change
- Maybe `ADS/MBSE/tests/ADS-IVV-FC-OBCC-DELIVERY/README.md` only if needed to align v1.0 5 Hz semantics with issue 003 contract files

Avoid editing D2 diagrams unless absolutely necessary. If D2 views still mention old TBD/N/A details after README updates, add a clear "D2 follow-up required" note rather than silently leaving a contradiction.

Do not update PM&SE blocker tables in this issue; final integration will do it.

## Acceptance criteria

- The listed READMEs no longer leave mission duration, maximum gap, jitter/worst-gap tolerance, v0.2 I2C timeout approach, or no-blocking instrumentation criteria as undefined/TBD.
- v1.0 ADS-to-OBCC 5 Hz requirement is recognized as a requirement or candidate update, not dismissed as N/A without follow-up.
- Execution remains pending; no pass credit is claimed.
- D2 follow-up needs are explicitly listed if applicable.
- Commit your changes with a message like `ADS: set timing timeout criteria`.

## Final response

Return a concise summary with files changed, selected timing thresholds, and any D2/model follow-up.
