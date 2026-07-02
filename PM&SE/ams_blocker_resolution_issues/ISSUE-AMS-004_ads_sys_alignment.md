# ISSUE-AMS-004 — Align ADS and system planning with shared ADS/AMS freshness contract

## Context

Align ADS and system-level planning with the shared PM&SE freshness contract required by `AMS-BLK-002`. Do not edit AMS files here.

Read first:

- `PM&SE/AMS_Blocker_Resolution_Plan_2026-07-02.md`
- `PM&SE/AMS_Blocker_Closure_Record_2026-07-02.md`
- `PM&SE/contracts/sensor_obcc_freshness_contract.md` (or exact shared contract path)
- `PM&SE/IVV.md`
- `PM&SE/ADS_Blocker_Closure_Record_2026-07-02.md`
- `ADS/MBSE/tests/README.md`
- `ADS/MBSE/tests/ADS-IVV-FC-OBCC-DELIVERY/README.md`
- `ADS/MBSE/tests/ADS-IVV-C-GETTER/README.md`
- `ADS/MBSE/tests/ADS-IVV-C-RATE-5HZ/README.md`
- `PM&SE/CON-003_Candidates_and_Definition_Blockers.md` §1.1 `SYS-END-TO-END-DATA` row for context.

## Shared rule

ADS and AMS use one contract: `5 Hz` OBCC requests, `2 s` telemetry pushes, max fresh age `<=400 ms`, enum `VALID`, `STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, `INIT_FAIL`, and no old data marked valid after timeout/fault.

## Task

Apply focused Markdown-only updates to ADS and system planning.

Likely files:

- `PM&SE/ADS_Blocker_Closure_Record_2026-07-02.md`
- `ADS/MBSE/tests/README.md`
- `ADS/MBSE/tests/ADS-IVV-FC-OBCC-DELIVERY/README.md`
- `ADS/MBSE/tests/ADS-IVV-C-GETTER/README.md`
- `ADS/MBSE/tests/ADS-IVV-C-RATE-5HZ/README.md`
- Optional minimal `PM&SE/CON-003_Candidates_and_Definition_Blockers.md` edit for `SYS-END-TO-END-DATA`; if risky, leave exact wording for issue 005.

Minimum updates:

1. Reference the shared PM&SE freshness contract from ADS closure/test planning docs.
2. Name `ADS-V10-DATA-FRESHNESS` as a candidate/alias or explicit extension through `ADS-IVV-FC-OBCC-DELIVERY`, `ADS-IVV-C-GETTER`, and `ADS-IVV-C-RATE-5HZ`.
3. State that v1.0 ADS freshness uses the shared `5 Hz`, `2 s`, `<=400 ms`, enum rule; LoRa `2 s` cadence remains separate from internal 5 Hz evidence.
4. Require timeout/fault/no-data/init-fail not to leave old ADS data marked `VALID`.
5. Ensure `SYS-END-TO-END-DATA` is directly updated or clearly queued to use the same PM&SE rule.
6. If D2 views still say v1.0 rate is N/A, list D2/model follow-up; do not edit D2.

Do not edit AMS files, D2, PNG, or pre-existing ADS issue files.

## Acceptance criteria

- ADS docs/closure record reference the shared contract and exact enum.
- ADS v1.0 data-freshness candidate/update path is clear.
- Internal 5 Hz freshness and 2 s LoRa telemetry are not conflated.
- `SYS-END-TO-END-DATA` use of the shared rule is either updated or queued clearly.
- Commit with message `ADS/AMS: align ADS freshness planning`.

## Final response

Return files changed, ADS alignment path, SYS status, and D2/model follow-up.
