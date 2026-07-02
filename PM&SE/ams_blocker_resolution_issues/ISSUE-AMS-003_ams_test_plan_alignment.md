# ISSUE-AMS-003 — Align AMS test docs with response, freshness, and evidence decisions

## Context

Align AMS documentation with AMS blocker decisions. Do not edit ADS or PM&SE integration tables here.

Read first:

- `PM&SE/AMS_Blocker_Resolution_Plan_2026-07-02.md`
- `PM&SE/AMS_Blocker_Closure_Record_2026-07-02.md`
- `PM&SE/contracts/sensor_obcc_freshness_contract.md` (or exact shared contract path)
- `PM&SE/IVV.md`
- `AMS/MBSE/tests/README.md`
- `AMS/MBSE/tests/AMS-VV-API-001/README.md`
- `AMS/MBSE/tests/AMS-VV-FC-001/README.md`
- `AMS/MBSE/tests/AMS-VV-FC-002/README.md`
- `AMS/MBSE/tests/AMS-VV-CON-003/README.md`
- `AMS/MBSE/tests/AMS-VV-CON-004/README.md`

## Decisions to apply

- `AMS-BLK-001`: temperature response-time `<=60 s` is a candidate test.
- `AMS-BLK-002`: AMS uses the shared contract (`5 Hz`, `2 s`, `<=400 ms`, exact status enum, no stale-valid after timeout/fault).
- `AMS-BLK-003`: v0.2 PCB-ready non-issue.
- `AMS-BLK-004`: API/non-blocking evidence must include 100% getter/OBCC inventory, explicit statuses, pointer ownership/lifetime/null policy, static callable-path review, dynamic traces, and `AMS-VV-CON-003` dependency.
- `AMS-BLK-005`: provisional trace IDs are acceptable pending system-level/source trace modeling.

## Task

Apply focused Markdown-only updates to AMS test docs, likely:

- `AMS/MBSE/tests/README.md`
- `AMS/MBSE/tests/AMS-VV-API-001/README.md`
- `AMS/MBSE/tests/AMS-VV-FC-001/README.md`
- `AMS/MBSE/tests/AMS-VV-FC-002/README.md`
- `AMS/MBSE/tests/AMS-VV-CON-003/README.md`
- `AMS/MBSE/tests/AMS-VV-CON-004/README.md`

Minimum updates:

1. Add candidate/update path for `AMS-V10-TEMP-RESPONSE-60S` or equivalent response-time test.
2. Add `AMS-V10-DATA-FRESHNESS` as either a README-only candidate/alias or explicit extension path through `AMS-VV-API-001` and `AMS-VV-FC-*`.
3. Reference the shared contract and its `5 Hz`, `2 s`, `<=400 ms`, enum, and stale-valid rules.
4. Document v0.2 PCB-ready non-issue and provisional trace-ID non-issue in AMS planning text.
5. Strengthen `AMS-VV-API-001` and `AMS-VV-CON-004` report/pass criteria with the AMS-BLK-004 evidence checklist.
6. Align `AMS-VV-FC-001`, `AMS-VV-FC-002`, and `AMS-VV-CON-003` to the shared statuses, especially `INIT_FAIL`, `TIMEOUT`, `SENSOR_FAULT`, and no old data marked `VALID`.

Do not update PM&SE CON/assessment, ADS files, D2, or PNG files.

## Acceptance criteria

- AMS docs expose response-time and data-freshness candidate/update paths.
- AMS docs reference the shared contract and exact enum.
- AMS-BLK-004 evidence requirements are explicit.
- v0.2 and trace-ID non-issue rationale is documented.
- No D2/PNG files change.
- Commit with message `AMS: align test docs with freshness blockers`.

## Final response

Return files changed, candidate/update paths, evidence requirements added, and D2/model follow-up.
