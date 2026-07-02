# PDM blocker-resolution orchestration plan — CON-003 §2.7

Date: 2026-07-02
Repository: CanSat Workshop

## End goal

Resolve the PDM blockers `PDM-BLK-001` through `PDM-BLK-007` in `PM&SE/CON-003_Candidates_and_Definition_Blockers.md` §2.7 at definition-planning level so the project has:

1. a complete PDM candidate verification-activity list,
2. a controlled list of updates required for existing PDM tests,
3. selected quantitative criteria and ownership decisions for the PDM blockers,
4. updated non-diagram documentation where safe to update now, and
5. remaining D2/model and execution work explicitly listed as follow-up, not hidden blockers.

This pass does **not** execute tests, does **not** claim pass/fail credit, and does **not** edit D2 diagrams. Documentation files that are not D2 diagrams may be updated.

## User-approved decisions and constraints

- `PDM-BLK-001`: the PDM v1.0 candidate activities already listed in `PDM/MBSE/v1.0/tests/README.md` remain candidates and need later modeling. The blocker should be closed as an inventory/definition-decision blocker by making that status explicit; do not model the candidates in this pass.
- `PDM-BLK-002`: the v1.0 terminal descent-speed limit is confirmed as **`<= 11 m/s`**, consistent with ESA CanSat handbook guidance and historical v0.1 fall-test context.
- `PDM-BLK-003`: emergency-deploy/lost-observability policy is owned by OBCC. Mark the PDM blocker closed/dispositioned and point PDM tests to the OBCC-owned policy baseline instead of redefining it.
- `PDM-BLK-004`: define servo/trigger status semantics pragmatically. Only a high-level outline is required from which future test definitions can be created/updated; do not create full tests in this pass.
- `PDM-BLK-005`: use available ADS blocker-resolution criteria where applicable, especially ADS freshness/status, angular-rate truth/statistics, timing/no-blocking, and equipment/evidence conventions. Define missing PDM-specific execution-readiness criteria as needed.
- `PDM-BLK-006`: define quantitative power validity criteria for the v0.2 BLE/manual deployment test. Terminal-speed evidence does not need to be demonstrated inside that test; it may link to `PDM-V02-TEST-TERMINAL-SPEED` and v0.1 fall-test evidence.
- `PDM-BLK-007`: define quantitative mass/measurement/environment criteria for the v0.1 fall test as appropriate.
- No pushes. Subagents may edit only scoped files and should not edit D2 diagrams or generated PNGs in this pass.

## Selected criteria to encode

| Area / blocker | Resolution decision to encode |
|---|---|
| Candidate inventory (`PDM-BLK-001`) | Keep all PDM v1.0 rows from `PDM/MBSE/v1.0/tests/README.md` as the complete candidate backlog except `PDM-VV-FC-001`, which already has a modeled definition. Mark the blocker closed at definition-inventory level while preserving later D2/modeling and execution as follow-up. |
| Descent speed (`PDM-BLK-002`) | Use `<= 11 m/s` as the PDM v1.0 terminal descent-speed limit for `PDM-VV-FC-003` and related system deployment-safety planning. Strict evidence should use calibrated video/time-distance or equivalent measurement, uncertainty/guard band, representative as-tested mass/configuration, and wind/environment records. |
| OBCC-owned emergency policy (`PDM-BLK-003`) | Reference `OBCC/MBSE/tests/OBCC-V10_Deployment_Fault_Policy.md`. PDM deploys when OBCC commands deployment and exposes actuator/status evidence; OBCC owns mode/trigger/emergency/safe-error/no-false-success decisions. |
| Servo status semantics (`PDM-BLK-004`) | Define an OBCC/PDM-facing high-level status vocabulary or oracle mapping: not-commanded, command-sent, opening/in-progress, open-confirmed, no-open-confirmed, timeout, jam/fault, unknown. Success requires independent open confirmation or PDM feedback, not merely PWM command sent. |
| FC-001 readiness (`PDM-BLK-005`) | Predeclare UUT IDs, PDM/ADS/OBCC hardware revisions, firmware commits/builds, IMU stimulus/replay set, ADS data freshness/status inputs, timing instrumentation, equipment IDs/calibration/status, environmental limits, statistical claim type, and evidence archive path before execution. Use `PM&SE/IVV.md` statistics, ADS selected angular-rate truth where relevant, and shared sensor freshness semantics when ADS data feed the trigger. |
| v0.2 power validity (`PDM-BLK-006`) | Define execution thresholds for battery/boost/servo power during BLE deployment: safe starting battery condition, 5 V servo rail tolerance, brownout/no-reset criteria, current logging, boost current/thermal limits, and actuator voltage/current evidence. Terminal-speed may be linked to `PDM-V02-TEST-TERMINAL-SPEED` and v0.1 fall-test evidence rather than demonstrated inside `PDM-V02-FC-BLE-DEPLOY`. |
| v0.1 fall-test criteria (`PDM-BLK-007`) | Define final/dummy mass estimate tolerance, scale resolution/uncertainty, video frame-rate/timebase and distance calibration, accepted measurement segment, wind/environment limits, drop-height/line-of-sight constraints, and anomaly/deviation rules. |

## Delegated issues

| Issue file | Delegated work | Main files / outputs | Dependencies |
|---|---|---|---|
| `PM&SE/pdm_blocker_resolution_issues/ISSUE-PDM-001_v10_candidate_and_existing_test_updates.md` | Update PDM v1.0 test documentation for blockers `PDM-BLK-001` through `PDM-BLK-005`: candidate inventory status, 11 m/s descent-speed limit, OBCC policy ownership, servo status semantics, and `PDM-VV-FC-001` execution-readiness criteria. | `PDM/MBSE/v1.0/tests/README.md`; `PDM/MBSE/v1.0/tests/PDM-VV-FC-001/README.md`; optional PDM references README if only text links are needed. | Can run first. Must avoid PM&SE register edits except reading. |
| `PM&SE/pdm_blocker_resolution_issues/ISSUE-PDM-002_v02_v01_quantitative_criteria.md` | Update historical PDM v0.2/v0.1 test documentation for `PDM-BLK-006` and `PDM-BLK-007`: v0.2 power thresholds and terminal-speed linkage; v0.1 mass/video/wind/environment measurement criteria. | `PDM/MBSE/v0.2/tests/README.md`; `PDM/MBSE/v0.2/tests/PDM-V02-FC-BLE-DEPLOY/README.md`; `PDM/MBSE/v0.1/tests/README.md`; `PDM/MBSE/v0.1/tests/PDM-V01-FC-FALL/README.md`. | Can run in parallel with issue 001. Must avoid PM&SE register edits except reading. |
| `PM&SE/pdm_blocker_resolution_issues/ISSUE-PDM-003_pmse_register_assessment_integration.md` | Integrate PDM decisions into PM&SE docs: mark PDM blockers closed/dispositioned at definition level, add folded candidate/update registers, align assessment PDM findings and cross-cutting deployment/descent-speed text. | `PM&SE/CON-003_Candidates_and_Definition_Blockers.md`; `PM&SE/MBSE_Test_Plan_Assessment.md`; this plan file status if appropriate. | Run after issues 001 and 002 so it can reflect their wording. |
| `PM&SE/pdm_blocker_resolution_issues/ISSUE-PDM-004_validation_cleanup.md` | Validate consistency after edits and clean up transient issue files. | consistency checks; removal of `PM&SE/pdm_blocker_resolution_issues/`; final plan status update if needed. | Run last. |

## Coordination rules for subagents

- Work from repository root `/Users/antho/CanSatWorkshop`.
- Read the assigned issue file, this plan, `PM&SE/CON-003_Candidates_and_Definition_Blockers.md`, `PM&SE/MBSE_Test_Plan_Assessment.md`, `PM&SE/IVV.md`, and every PDM test README you edit.
- Use the `ivv` skill as the controlling verification-completeness guidance.
- Do not edit D2 files, PNGs, source code, or unrelated subsystem files.
- Do not execute tests or claim pass/fail credit. Use wording such as "definition decision selected", "candidate retained", "execution pending", and "D2/model follow-up pending".
- Keep edits focused and do not push.
- Because the repository may contain unrelated local work, subagents should **not commit**. The orchestrator will review and commit selected path changes.
- If conflicts or unexpected scope appear, stop and summarize rather than making broad unrelated changes.

## Final acceptance criteria

- `PM&SE/CON-003_Candidates_and_Definition_Blockers.md` §2.7 no longer presents `PDM-BLK-001` through `PDM-BLK-007` as undefined blockers. It records closed/dispositioned definition decisions plus residual D2/model/execution follow-up.
- The PDM candidate test list is complete and matches `PDM/MBSE/v1.0/tests/README.md`, `PDM/MBSE/v0.2/tests/README.md`, and `PDM/MBSE/v0.1/tests/README.md`.
- The existing-test update list identifies which PDM test docs must be modeled/updated later and which existing definitions have new criteria now.
- PDM v1.0 docs encode the confirmed `<=11 m/s` terminal-speed criterion, OBCC-owned emergency policy boundary, servo status/no-false-success semantics, and `PDM-VV-FC-001` execution-readiness criteria.
- PDM v0.2 docs encode quantitative power validity thresholds and clearly link terminal-speed evidence to `PDM-V02-TEST-TERMINAL-SPEED` and v0.1 fall-test evidence where not demonstrated in-run.
- PDM v0.1 docs encode quantitative mass, video/time-distance, and environment/wind criteria for interpreting the fall test.
- `PM&SE/MBSE_Test_Plan_Assessment.md` is consistent with the selected decisions and does not continue to state the same PDM criteria are TBD.
- No D2 diagrams or PNGs are changed by this pass.
- Temporary issue files under `PM&SE/pdm_blocker_resolution_issues/` are removed by the final cleanup issue. This plan remains as the high-level orchestration record.

## Execution status

Completed at definition-planning level. ISSUE-PDM-004 final validation/cleanup passed after the PDM v1.0/v0.2/v0.1 Markdown updates from ISSUE-PDM-001 and ISSUE-PDM-002 and the PM&SE register/assessment integration from ISSUE-PDM-003. Transient issue files under `PM&SE/pdm_blocker_resolution_issues/` were removed after validation. No execution pass/fail credit is claimed, and no D2/PNG/source edits are claimed by this status note.
