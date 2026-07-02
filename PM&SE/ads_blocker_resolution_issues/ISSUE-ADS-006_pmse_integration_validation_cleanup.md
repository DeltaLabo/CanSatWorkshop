# ISSUE-ADS-006 — PM&SE integration, validation, and issue cleanup

## Context

This is the final integration issue for resolving `ADS-BLK-001` through `ADS-BLK-010` from `PM&SE/CON-003_Candidates_and_Definition_Blockers.md` §2.2 and for the added shared ADS/AMS sensor-to-OBCC freshness scope.

Read first:

- `PM&SE/ADS_Blocker_Resolution_Plan_2026-07-02.md`
- `PM&SE/ADS_Blocker_Closure_Record_2026-07-02.md`
- `PM&SE/contracts/sensor_obcc_freshness_contract.md`
- `PM&SE/CON-003_Candidates_and_Definition_Blockers.md`
- `PM&SE/MBSE_Test_Plan_Assessment.md`
- `PM&SE/IVV.md`
- ADS files changed by prior issues
- AMS files changed by `ISSUE-AMS-007`

Do not start this issue until all remaining ADS/AMS issues have committed their work.

## Task

Integrate the ADS blocker-resolution work and shared ADS/AMS freshness work into PM&SE controlled records, validate consistency, and remove temporary issue files.

## Required PM&SE updates

1. Update `PM&SE/CON-003_Candidates_and_Definition_Blockers.md` §2.2 ADS blockers so each `ADS-BLK-001` through `ADS-BLK-010` is no longer an open undefined blocker. Use wording like:
   - `Closed — definition decision selected ...`,
   - `Resolved — candidate definition created ...`, or
   - `Dispositioned — handled as constraint/code-analysis path ...`.

   Preserve residual execution prerequisites and D2/model follow-ups, but do not leave the blocker text saying the definition is missing.

2. Update the AMS freshness row (`AMS-BLK-002` and/or the AMS candidate backlog row) so it points to the shared sensor-to-OBCC freshness contract and `AMS-V10-DATA-FRESHNESS` or the selected AMS API/FC extension. Do not claim execution.

3. Update cross-cutting/system freshness text where relevant:
   - `SYS-BLK-004` should mention the shared ADS/AMS freshness contract as a partial/defined rule for sensor-to-OBCC freshness while broader payload/schema work may remain.
   - `SYS-END-TO-END-DATA` candidate row should use the shared contract as the ADS/AMS sensor freshness oracle.

4. Update `PM&SE/MBSE_Test_Plan_Assessment.md` ADS/AMS findings and recommended actions where they currently say the same ADS/AMS freshness criteria are TBD or unassigned. Do not overclaim; tests remain execution pending.

5. Update `PM&SE/ADS_Blocker_Closure_Record_2026-07-02.md` with final status:
   - list committed artifacts,
   - note shared PM&SE freshness contract path,
   - note ADS/AMS test alignment,
   - note any D2/source-model follow-up,
   - note that issue files were removed after validation.

6. Update `PM&SE/ADS_Blocker_Resolution_Plan_2026-07-02.md` execution status from in progress to completed if validation passes.

## Validation commands / checks

Run relevant checks and record results in your final response. At minimum:

- `git status --short` before final cleanup awareness.
- `python3 ADS/MBSE/tests/tools/parse_ads_serial0.py --help` if that parser exists.
- `python3 -m json.tool ADS/MBSE/tests/schemas/ads_serial0_v0_1_v0_2.schema.json >/tmp/ads_serial0_schema_check.json` if the schema exists.
- Inspect shared contract/header for required enum and constants, e.g. `rg -n "VALID|STALE|NO_DATA|TIMEOUT|SENSOR_FAULT|INIT_FAIL|400|200" PM\&SE/contracts`.
- `rg -n "ADS-BLK-00[1-9]|ADS-BLK-010|AMS-BLK-002|SYS-END-TO-END-DATA|TBD|blocked until|schema/parser baseline is missing|v1.0.*N/A.*5 Hz|mission-window duration and maximum|freshness.*TBD|status enum" PM\&SE ADS/MBSE/tests AMS/MBSE/tests ADS/README.md AMS/README.md` and inspect the hits. It is acceptable for historical text to mention old blocker IDs if it clearly says closed/resolved; it is not acceptable for active controlled text to still call the same definition missing.
- If D2 files changed, confirm corresponding PNGs changed or render them. If no D2 files changed, state that no D2 render was required.

## Cleanup

After PM&SE integration and validation, delete all temporary issue files under:

- `PM&SE/ads_blocker_resolution_issues/`

It is okay to delete the directory. The high-level plan and closure record must remain.

## Acceptance criteria

- PM&SE blocker register and assessment are aligned with ADS blocker decisions and shared ADS/AMS freshness decisions.
- Shared contract is referenced by ADS, AMS, and `SYS-END-TO-END-DATA` planning text.
- Closure record and plan have final status.
- Validation commands pass or any remaining hits are explained as historical/resolved/follow-up, not open undefined blockers.
- Temporary issue files are deleted.
- Commit your changes with a message like `PMSE: integrate ADS AMS freshness closure`.

## Final response

Return a concise summary with:

- PM&SE files updated,
- validation commands/results,
- remaining follow-up items,
- confirmation that temporary issue files were removed,
- commit hash.
