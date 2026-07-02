# ISSUE-PDS-004 — PDS validation and issue cleanup

Work in `/Users/antho/CanSatWorkshop`.

## Read first

- `PM&SE/PDS_Blocker_Resolution_Plan_2026-07-02.md`
- `PM&SE/PDS_Blocker_Closure_Record_2026-07-02.md`
- `PM&SE/CON-003_Candidates_and_Definition_Blockers.md`
- `PM&SE/MBSE_Test_Plan_Assessment.md`
- `PDS&ESS/MBSE/tests/README.md`
- Relevant changed PDS test READMEs from issue 002

## Scope

Final consistency validation and temporary issue cleanup only. Do **not** edit `.d2`, `.png`, binary, or unrelated subsystem files. Do **not** execute tests. Do **not** commit or push.

## Required checks

1. Verify every `PDS-BLK-002` through `PDS-BLK-009` appears in the PM&SE PDS blocker table and in the closure record with consistent disposition.
2. Verify `PDS-VV-CON-010` appears in:
   - `PM&SE/PDS_Blocker_Closure_Record_2026-07-02.md`,
   - `PM&SE/CON-003_Candidates_and_Definition_Blockers.md`,
   - `PDS&ESS/MBSE/tests/README.md`,
   and is described as candidate/detailed definition pending, not executed.
3. Verify D2/source-model follow-ons are explicit for INA219 I2C CE and master switch/accessibility.
4. Verify `S&A/PCB_General_Rules.md` is referenced from PDS DFM documentation / PM&SE closure.
5. Verify `PDS-BLK-004`, `PDS-BLK-006`, and `PDS-BLK-009` are framed as campaign/execution prerequisites, not undefined test-definition blockers.
6. Verify no `.d2` or `.png` files are modified.
7. Run at least:
   - `git status --short`
   - `git diff --name-only`
   - `rg -n "PDS-BLK-00[2-9]|PDS-VV-CON-010|S&A/PCB_General_Rules|campaign-defined|execution prerequisite|source-model" PM&SE PDS\&ESS/MBSE/tests`

## Cleanup

If the checks pass, remove the temporary issue directory:

- `PM&SE/pds_blocker_resolution_issues/`

Do not remove `PM&SE/PDS_Blocker_Resolution_Plan_2026-07-02.md` or `PM&SE/PDS_Blocker_Closure_Record_2026-07-02.md`.

## Done

- Validation summary is provided in your final response.
- `PM&SE/pds_blocker_resolution_issues/` is removed.
- No `.d2`/`.png` files are modified.
- No execution pass/fail credit is claimed.
