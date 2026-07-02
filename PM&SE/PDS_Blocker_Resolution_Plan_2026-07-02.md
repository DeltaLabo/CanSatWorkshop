# PDS & ESS Blocker Resolution Plan — CON-003 §2.6

Date: 2026-07-02
Repository: CanSat Workshop

## End goal

Resolve the PDS & ESS definition blockers in `PM&SE/CON-003_Candidates_and_Definition_Blockers.md` §2.6 at definition-decision level so the PDS test suite has:

1. a complete PDS candidate/detailed-definition backlog,
2. a controlled list of updates to existing PDS tests and source-model artifacts,
3. selected quantitative criteria for the protection-probability blocker, and
4. PM&SE/PDS Markdown updates showing which items are definition blockers, pending source edits, candidate tests, or execution-only prerequisites.

This pass does **not** execute tests and does **not** claim pass/fail credit. It should avoid editing `.d2`/`.png` diagrams; D2/source-model changes are recorded as follow-on unless the orchestrator explicitly changes scope. Markdown documentation may be updated.

## User decisions to apply

- `PDS-BLK-002`: the INA219 I2C component exchange is a quick source-model fix. Select the fix as adding an explicit `[CE] I2C` / INA219 bus exchange between ESS Processing/XIAO and Battery monitoring/INA219. In this pass, record the D2/source-model edit as pending unless a later issue is explicitly scoped to modify diagrams.
- `PDS-BLK-003`: add a regulator-efficiency validation candidate to the PDS candidate list. Use `PDS-VV-CON-010` unless a reviewed file already establishes a better ID.
- `PDS-BLK-004`: On-mode load/current budget and 6 h endurance profile may remain campaign-defined; do not create a separate modeled load-profile estimation activity.
- `PDS-BLK-005`: master-switch/accessibility hardware detail needs a source/interface fix; document it as a pending source-model/interface edit.
- `PDS-BLK-006`: Li-ion safety documents, charger model/certification, and cell safety evidence are literal execution prerequisites, not definition blockers.
- `PDS-BLK-007`: Carvera Air DFM rules are documented in `S&A/PCB_General_Rules.md`; reference that file from PDS DFM test definitions and keep deviation records as execution evidence.
- `PDS-BLK-008`: define quantitative protection-probability criteria. Keep the conservative missed-demand interpretation already used by `PDS-VV-CON-003`, and add concrete setpoint/trial validity criteria suitable for bench execution.
- `PDS-BLK-009`: rail-test nominal load, thermal, and settling parameters are literal campaign/execution confirmations, not an issue with test definitions.

## Selected criteria for `PDS-BLK-008`

Subagents may refine wording, but should preserve this intent:

- Formal claim: source `[C] Probability < 1%` means missed demanded unsafe protection-action probability `<1%` per demanded mode: overcurrent/output-short-equivalent and overvoltage.
- Statistics: strict verification requires 299 valid independent demanded trials with zero missed unsafe actions per mode, supporting a one-sided 95% exact-binomial upper bound below 1%. Fewer trials are screening/characterization with the exact upper bound reported.
- Overcurrent/output-short-equivalent demand: use a current-limited source/load or short-equivalent fixture; predeclare nominal trip/current-limit threshold from the protection design or test article datasheet; valid trials must demand at least 110% of the declared trip threshold or the minimum current that reliably enters the protection region while staying inside the testbench safe-energy envelope. Direct uncontrolled battery shorts are out of scope.
- Overvoltage demand: use a current-limited injection source; predeclare the nominal overvoltage threshold from the protection design or datasheet; valid trials must exceed that threshold by at least 5% or by the smallest campaign-approved margin that reliably demands protection without exceeding absolute maximum ratings.
- Per-trial safe outcome: protection detects/acts, removes or limits unsafe output before declared rail/cell/PCB/temperature limits are violated, inhibits restore until the fault is cleared, and controlled restore returns to nominal without uncontrolled restart/reset.
- Independence: trials require cooldown/reset or randomized/procedure-separated demand order, recorded source/load settings, independent instrumentation triggers, stable ambient/thermal preconditions, and anomaly/deviation disposition. If independence is not defensible, classify as screening.

## Work breakdown

| Issue | Delegated work | Main outputs | Dependencies |
|---|---|---|---|
| `ISSUE-PDS-001_closure_record_and_candidate_register.md` | Create central PDS closure record with dispositions, candidate list, existing-test update list, source-model follow-on list, and residual execution prerequisites. | `PM&SE/PDS_Blocker_Closure_Record_2026-07-02.md` | First |
| `ISSUE-PDS-002_pds_test_markdown_updates.md` | Apply PDS Markdown-only updates to the test index and relevant test README files; do not edit D2/PNG. | Updated `PDS&ESS/MBSE/tests/README.md` and focused test READMEs | After issue 001 |
| `ISSUE-PDS-003_pmse_integration.md` | Integrate the closure into PM&SE registers/assessment without overclaiming execution. | Updated `PM&SE/CON-003_Candidates_and_Definition_Blockers.md`, `PM&SE/MBSE_Test_Plan_Assessment.md` | After issues 001–002 |
| `ISSUE-PDS-004_validation_cleanup.md` | Validate consistency, ensure no D2/PNG edits, and remove temporary PDS issue files. | Issue directory removed; plan remains | Last |

## Coordination rules for subagents

- Work from `/Users/antho/CanSatWorkshop`.
- Read this plan, your issue file, `PM&SE/IVV.md`, `PM&SE/MBSE_Test_Plan_Assessment.md`, `PM&SE/CON-003_Candidates_and_Definition_Blockers.md`, and every PDS/S&A file your issue references.
- Do not push. Do not commit; the orchestrator will review and commit path-specific changes.
- Do not edit `.d2`, `.png`, binary, or unrelated subsystem files.
- Do not execute hardware tests or claim execution pass/fail credit.
- Use wording such as “definition decision selected”, “candidate queued”, “source-model edit pending”, “execution prerequisite”, or “execution pending” as appropriate.
- Keep PDS definition decisions separate from D2/model follow-up and execution blockers.
- If scope conflicts appear, stop and summarize instead of making broad unrelated changes.

## Acceptance criteria

- Every `PDS-BLK-002` through `PDS-BLK-009` appears exactly once in the closure record decision table with selected disposition, affected tests/docs, source-model or execution follow-up, and residual status.
- The PDS candidate list includes the regulator-efficiency validation candidate (`PDS-VV-CON-010` unless changed with rationale).
- The existing-test update list covers at least `PDS-VV-FC-002`, `PDS-VV-CON-002`, `PDS-VV-CON-003`, `PDS-VV-CON-004`, `PDS-VV-CON-009`, `PDS-VV-ALLOC-001`, and `PDS&ESS/MBSE/tests/README.md`.
- `PDS-BLK-004`, `PDS-BLK-006`, and `PDS-BLK-009` are no longer described as undefined test-definition blockers; they are campaign/execution prerequisites.
- `PDS-BLK-007` references `S&A/PCB_General_Rules.md` and leaves deviation records/evidence to execution.
- `PDS-BLK-008` has quantitative criteria sufficient to guide later test-definition update/execution.
- PM&SE assessment/register language is consistent and does not claim tests were executed.
- Temporary issue files under `PM&SE/pds_blocker_resolution_issues/` are removed by the final cleanup issue. This plan remains as the high-level orchestration record.

## Execution status

Completed at definition-planning level on 2026-07-02.

- `ISSUE-PDS-001` created `PM&SE/PDS_Blocker_Closure_Record_2026-07-02.md`.
- `ISSUE-PDS-002` aligned PDS Markdown test-planning documents without editing D2/PNG diagrams.
- `ISSUE-PDS-003` folded PDS dispositions into the CON-003 register and MBSE assessment.
- `ISSUE-PDS-004` validation/cleanup completed; temporary PDS issue files were removed.
- No PDS tests were executed, no pass/fail credit is claimed, and source-model/D2 edits remain follow-on where listed.
