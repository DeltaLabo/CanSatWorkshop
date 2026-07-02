# AMS Blocker Resolution Plan — CON-003 §2.3

Date: 2026-07-02
Repository: CanSat Workshop

## Goal

Resolve `AMS-BLK-001` through `AMS-BLK-005` from `PM&SE/CON-003_Candidates_and_Definition_Blockers.md` at definition-planning level. Outputs are a complete candidate/update list, a shared ADS/AMS sensor-to-OBCC freshness contract, PM&SE register/assessment updates, and explicit follow-on D2/model work. No tests are executed and no pass/fail credit is claimed.

Non-D2 documentation may be updated. Do not edit source D2 diagrams in this pass.

## User decisions to preserve

| Blocker | Decision |
|---|---|
| `AMS-BLK-001` | Real candidate test: add/track a temperature response-time `<=60 s` activity. |
| `AMS-BLK-002` | Resolve consistently in ADS and AMS with one shared sensor-to-OBCC freshness contract. ADS/AMS respond to OBCC at `5 Hz`; at each `2 s` telemetry push required data is fresh with max age `<=400 ms` (two missed 5 Hz samples) or explicitly non-valid. Status enum: `VALID`, `STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, `INIT_FAIL`. Timeout/fault must not leave old data marked valid. |
| `AMS-BLK-003` | Non-issue: AMS `v0.2` was the PCB-ready delivery; no native v0.2 logical/CE/allocation/FC closure is required beyond existing PCB/bring-up caveats. |
| `AMS-BLK-004` | Close by requiring API/non-blocking evidence to report 100% getter/OBCC collection-path inventory, explicit statuses, pointer ownership/lifetime/null policy, static callable-path review, dynamic timing/non-blocking traces, and dependency on `AMS-VV-CON-003` for I2C timeout evidence. |
| `AMS-BLK-005` | Non-issue once system-level tests are introduced; provisional trace IDs are acceptable pending `SYS-*` modeling. |

## Issues

| Issue | Work | Main outputs | Order |
|---|---|---|---|
| `PM&SE/ams_blocker_resolution_issues/ISSUE-AMS-001_closure_record.md` | Create central AMS closure record. | `PM&SE/AMS_Blocker_Closure_Record_2026-07-02.md`. | First. |
| `PM&SE/ams_blocker_resolution_issues/ISSUE-AMS-002_shared_freshness_contract.md` | Create shared ADS/AMS freshness contract and IVV reference. | `PM&SE/contracts/*` or equivalent PM&SE contract file; `PM&SE/IVV.md`. | After 001. |
| `PM&SE/ams_blocker_resolution_issues/ISSUE-AMS-003_ams_test_plan_alignment.md` | Align AMS docs with response/freshness/evidence decisions. | `AMS/MBSE/tests/*.md` updates only. | After 001/002. |
| `PM&SE/ams_blocker_resolution_issues/ISSUE-AMS-004_ads_sys_alignment.md` | Align ADS and system planning to the same freshness rule. | ADS Markdown and/or PM&SE planning updates. | After 001/002; avoid AMS files. |
| `PM&SE/ams_blocker_resolution_issues/ISSUE-AMS-005_pmse_validation_cleanup.md` | Update PM&SE register/assessment, validate, remove temporary AMS issue files. | `CON-003`, assessment, completed plan status. | Last. |

## Coordination rules

- Work from repo root. Do not push.
- Read this plan, the issue file, `PM&SE/IVV.md`, `PM&SE/CON-003_Candidates_and_Definition_Blockers.md`, and `PM&SE/MBSE_Test_Plan_Assessment.md` before editing.
- Do not ask the user questions. If execution details are unknown, record them as execution/model-update follow-up.
- Do not edit D2/PNG files. List D2/model follow-up explicitly.
- Commit focused changes with a clear message (`AMS: ...`, `ADS/AMS: ...`, or `PMSE: ...`).
- Existing `PM&SE/ads_blocker_resolution_issues/` files predate this AMS pass; do not remove them unless explicitly instructed.

## Acceptance criteria

- AMS closure record lists `AMS-BLK-001`..`AMS-BLK-005` with decisions, candidate/new-test impacts, existing-test updates, prerequisites, and follow-up.
- Shared freshness contract defines `5 Hz`, `2 s`, `<=400 ms`, the exact six-status enum, timestamp/age evidence, and no stale-valid behavior after timeout/fault.
- AMS candidate/update list includes `AMS-V10-TEMP-RESPONSE-60S` (or equivalent) and `AMS-V10-DATA-FRESHNESS` or extension through existing AMS API/FC tests.
- ADS alignment includes `ADS-V10-DATA-FRESHNESS` or extension through existing ADS OBCC-delivery/getter/rate tests using the same contract.
- `SYS-END-TO-END-DATA` planning uses the same PM&SE freshness/status/age rule.
- `AMS-BLK-003` and `AMS-BLK-005` are dispositioned non-issues; `AMS-BLK-004` is closed at definition level by required evidence checklists.
- `PM&SE/CON-003_Candidates_and_Definition_Blockers.md` and `PM&SE/MBSE_Test_Plan_Assessment.md` are consistent with the decisions.
- Temporary AMS issue files are removed by the final cleanup issue. This plan remains.

## Execution status

Completed on 2026-07-02. PM&SE register and assessment updates now disposition `AMS-BLK-001` through `AMS-BLK-005` at definition level, align ADS/AMS freshness planning to the shared PM&SE contract, and keep execution/modeling gaps explicit. Validation run included `git status --short`, the required cross-artifact `rg` consistency scan, and `find "PM&SE/ams_blocker_resolution_issues" -type f` before cleanup; the find output showed only the five temporary AMS issue files. The temporary AMS issue directory was removed after validation, while `PM&SE/ads_blocker_resolution_issues/` was intentionally preserved.

Residual follow-up: create/update the AMS D2/model definitions and regenerated PNGs for `AMS-V10-TEMP-RESPONSE-60S` and the `AMS-V10-DATA-FRESHNESS` extensions; complete ADS D2/model follow-up for `ADS-V10-DATA-FRESHNESS` where old v1.0 N/A rate rationale remains; model `SYS-END-TO-END-DATA` and the final requirement-to-test matrix; freeze payload/schema/configuration details; execute tests and archive reports before claiming pass/fail credit.
