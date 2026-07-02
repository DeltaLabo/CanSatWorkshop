# ISSUE-AMS-001 — AMS closure record and candidate/update register

## Context

Resolve `AMS-BLK-001` through `AMS-BLK-005` from `PM&SE/CON-003_Candidates_and_Definition_Blockers.md` §2.3 at definition level.

Read first:

- `PM&SE/AMS_Blocker_Resolution_Plan_2026-07-02.md`
- `PM&SE/CON-003_Candidates_and_Definition_Blockers.md`
- `PM&SE/MBSE_Test_Plan_Assessment.md`
- `PM&SE/IVV.md`
- `AMS/README.md`
- `AMS/MBSE/tests/README.md`
- `AMS/MBSE/tests/AMS-VV-API-001/README.md`
- `AMS/MBSE/tests/AMS-VV-FC-001/README.md`
- `AMS/MBSE/tests/AMS-VV-FC-002/README.md`
- `AMS/MBSE/tests/AMS-VV-CON-003/README.md`
- `AMS/MBSE/tests/AMS-VV-CON-004/README.md`
- `PM&SE/ADS_Blocker_Closure_Record_2026-07-02.md`

## User decisions

- `AMS-BLK-001`: real candidate test for temperature response time `<=60 s`.
- `AMS-BLK-002`: one shared ADS/AMS sensor-to-OBCC freshness contract: `5 Hz` OBCC requests, `2 s` telemetry pushes, max fresh age `<=400 ms`, enum `VALID`, `STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, `INIT_FAIL`, and no old data marked valid after timeout/fault.
- `AMS-BLK-003`: non-issue; AMS `v0.2` was PCB-ready only.
- `AMS-BLK-004`: close by required evidence checklist: 100% getter/OBCC collection-path inventory, statuses, pointer ownership/lifetime/null policy, static callable-path review, dynamic timing/non-blocking traces, and `AMS-VV-CON-003` dependency.
- `AMS-BLK-005`: non-issue if system-level tests are introduced; provisional IDs acceptable pending system/source trace modeling.

## Task

Create `PM&SE/AMS_Blocker_Closure_Record_2026-07-02.md`.

It must include:

1. Scope: definition decisions only; no execution/pass credit.
2. Decision table with `AMS-BLK-001`..`AMS-BLK-005` exactly once, including decision, candidate/new tests, existing-test updates, prerequisites, and closure/follow-up status.
3. Complete candidate/update list including:
   - `AMS-V10-TEMP-RESPONSE-60S` or equivalent,
   - `AMS-V10-DATA-FRESHNESS` or extension through `AMS-VV-API-001` / `AMS-VV-FC-*`,
   - `ADS-V10-DATA-FRESHNESS` or extension through ADS OBCC-delivery/getter/rate tests,
   - `SYS-END-TO-END-DATA` update using the same freshness/status rule.
4. Existing-test update list for AMS API/FC/CON tests, ADS freshness-alignment tests, and PM&SE system candidate text.
5. Follow-on D2/model update list and residual execution-only uncertainties.

Do not update CON-003, the assessment, IVV, ADS files, AMS test READMEs, or D2 files in this issue.

## Acceptance criteria

- Closure record exists and is self-contained.
- All five AMS blockers appear exactly once in the decision table.
- The shared freshness rule and enum are explicit.
- `AMS-BLK-003` and `AMS-BLK-005` are recorded as non-issues.
- Commit with message `AMS: record blocker closure decisions`.

## Final response

Return files changed, decisions captured, candidate/update list, and follow-up uncertainties.
