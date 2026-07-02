# ISSUE-ADSAMS-009 — Stale ADS/AMS issue-file cleanup after AMS freshness closure

## Context

The current AMS blocker-resolution pass has completed and removed `PM&SE/ams_blocker_resolution_issues/`. However `PM&SE/ads_blocker_resolution_issues/` still contains temporary issue files from the earlier ADS blocker plan and the shared ADS/AMS freshness expansion. The user instruction for orchestrated work is that issue files should be cleaned up after the delegated work is done.

Read first:

- `PM&SE/AMS_Blocker_Resolution_Plan_2026-07-02.md`
- `PM&SE/ADS_Blocker_Resolution_Plan_2026-07-02.md`
- `PM&SE/AMS_Blocker_Closure_Record_2026-07-02.md`
- `PM&SE/ADS_Blocker_Closure_Record_2026-07-02.md`
- `PM&SE/CON-003_Candidates_and_Definition_Blockers.md`

## Task

Perform cleanup only:

1. Remove the temporary issue directory `PM&SE/ads_blocker_resolution_issues/` and all files under it, including this issue file.
2. Update only the **Execution status** section of `PM&SE/ADS_Blocker_Resolution_Plan_2026-07-02.md` to state:
   - the shared ADS/AMS freshness portions were completed by the later AMS freshness closure commits,
   - the temporary ADS/AMS issue files were removed as cleanup,
   - the broader ADS blocker plan is **not** being claimed fully complete by this cleanup; remaining ADS D2/model/execution follow-up is captured in the ADS closure record, CON-003, and commit history.
3. Do not edit ADS/AMS test READMEs, CON-003, the assessment, D2, or PNG files in this cleanup.
4. Do not push.

## Acceptance criteria

- `PM&SE/ads_blocker_resolution_issues/` no longer exists.
- `PM&SE/ADS_Blocker_Resolution_Plan_2026-07-02.md` no longer says temporary ADS issue files remain pending without qualification.
- The ADS plan does not claim all ADS blockers are fully executed or fully modeled.
- No D2/PNG files are changed.
- Commit with message `PMSE: clean stale issue files`.

## Final response

Return files changed, cleanup performed, and residual ADS follow-up.
