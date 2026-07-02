# ISSUE-AMS-005 — PM&SE integration, validation, and AMS issue cleanup

## Context

This is the final integration issue for resolving `AMS-BLK-001` through `AMS-BLK-005` from `PM&SE/CON-003_Candidates_and_Definition_Blockers.md` §2.3.

Read first:

- `PM&SE/AMS_Blocker_Resolution_Plan_2026-07-02.md`
- `PM&SE/AMS_Blocker_Closure_Record_2026-07-02.md`
- `PM&SE/Sensor_to_OBCC_Freshness_Contract.md` (or the exact shared contract file created by issue 002)
- `PM&SE/IVV.md`
- `PM&SE/CON-003_Candidates_and_Definition_Blockers.md`
- `PM&SE/MBSE_Test_Plan_Assessment.md`
- `AMS/MBSE/tests/README.md`
- `ADS/MBSE/tests/README.md`
- `PM&SE/ADS_Blocker_Closure_Record_2026-07-02.md`

Expected outputs from previous issues:

- A central AMS closure record exists.
- A shared ADS/AMS sensor-to-OBCC freshness contract exists and is referenced by IVV.
- AMS test docs identify the response-time and data-freshness candidates/update paths and the `AMS-BLK-004` evidence requirements.
- ADS planning docs or closure record are aligned to the same freshness contract.

## Task

Update PM&SE assessment/register documents, validate consistency, and remove temporary AMS issue files.

### 1. Update `PM&SE/CON-003_Candidates_and_Definition_Blockers.md`

Make minimal but complete updates so §2.3 AMS blockers are no longer presented as unresolved definition blockers:

- `AMS-BLK-001`: mark as a selected candidate test/update, not an undefined blocker. State that `AMS-V10-TEMP-RESPONSE-60S` or modeled equivalent is required and execution/modeling remains pending.
- `AMS-BLK-002`: mark definition decision resolved by the shared PM&SE freshness contract. State the candidate/update paths for `AMS-V10-DATA-FRESHNESS` and `ADS-V10-DATA-FRESHNESS` or extensions of existing tests, plus `SYS-END-TO-END-DATA` use of the same rule.
- `AMS-BLK-003`: mark closed/dispositioned non-issue with rationale that `v0.2` was PCB-ready only.
- `AMS-BLK-004`: mark definition decision resolved by required API/non-blocking evidence checklist and `AMS-VV-CON-003` dependency.
- `AMS-BLK-005`: mark closed/dispositioned non-issue with rationale that provisional trace IDs are acceptable pending system-level tests.

Also update candidate tables earlier in the file if needed:

- AMS candidate list should include the temperature response-time candidate and data-freshness candidate/update path.
- ADS candidate list should be consistent with the shared freshness contract for `ADS-V10-DATA-FRESHNESS` or existing-test extension.
- System-level `SYS-END-TO-END-DATA` candidate row should mention the shared PM&SE freshness/status/age rule.

Do not claim tests are executed or D2 definitions are complete if they are not.

### 2. Update `PM&SE/MBSE_Test_Plan_Assessment.md`

Make minimal consistency updates so the assessment no longer says the selected AMS blockers are undefined:

- `SUB-AMS-002`: response-time remains a candidate to add, with selected candidate ID/path.
- `SUB-AMS-003` and `GAP-001`: note that ADS/AMS 5 Hz/freshness semantics are selected by the shared PM&SE contract; modeled test updates/execution remain pending.
- `SYS-004` / `SYS-END-TO-END-DATA`: mention the shared freshness/status/age rule.
- `ACT-006` or action list: align with the selected candidate/update list.

Keep residual execution/modeling gaps honest.

### 3. Validate

Run lightweight validation commands, at minimum:

- `git status --short`
- `rg -n "AMS-BLK-00[1-5]|AMS-V10-DATA-FRESHNESS|AMS-V10-TEMP|Sensor_to_OBCC|SYS-END-TO-END-DATA|VALID|STALE|NO_DATA|TIMEOUT|SENSOR_FAULT|INIT_FAIL" "PM&SE" AMS/MBSE/tests ADS/MBSE/tests -g '*.md'`
- `find "PM&SE/ams_blocker_resolution_issues" -type f` before cleanup to confirm only temporary AMS issue files are present.

Do not require D2/PNG regeneration because this pass should not edit D2.

### 4. Cleanup

Remove temporary issue files under:

- `PM&SE/ams_blocker_resolution_issues/`

Remove the directory if empty. Do **not** remove pre-existing `PM&SE/ads_blocker_resolution_issues/` unless the orchestrator separately instructs it; it predates this AMS pass.

Update the execution status section of `PM&SE/AMS_Blocker_Resolution_Plan_2026-07-02.md` from pending to completed, summarizing the validation and residual follow-up.

## Constraints

- Do not edit D2 diagrams or PNGs.
- Do not execute tests or claim pass/fail evidence.
- Keep PM&SE changes focused on AMS §2.3, ADS/AMS freshness alignment, and `SYS-END-TO-END-DATA` consistency.
- If a previous issue did not finish an expected output, make a small corrective edit if safe; otherwise record the residual issue clearly in the plan status.

## Acceptance criteria

- `PM&SE/CON-003_Candidates_and_Definition_Blockers.md` §2.3 reflects the selected dispositions and no longer lists the AMS items as undefined blockers.
- `PM&SE/MBSE_Test_Plan_Assessment.md` is consistent with the selected AMS/ADS freshness contract and candidate/update list.
- `SYS-END-TO-END-DATA` planning text references the shared PM&SE freshness/status/age rule.
- Temporary AMS issue files are removed.
- Plan execution status is completed with residual follow-up documented.
- No D2/PNG files are changed.
- Commit your changes with a message like `PMSE: close AMS blocker register updates`.

## Final response

Return a concise summary with:

- files changed,
- PM&SE blocker/assessment updates,
- validation commands and notable results,
- cleanup performed,
- residual follow-up.
