# ISSUE-PDS-003 — PM&SE PDS integration updates

Work in `/Users/antho/CanSatWorkshop`.

## Read first

- `PM&SE/PDS_Blocker_Resolution_Plan_2026-07-02.md`
- `PM&SE/PDS_Blocker_Closure_Record_2026-07-02.md`
- `PM&SE/IVV.md`
- `PM&SE/MBSE_Test_Plan_Assessment.md`
- `PM&SE/CON-003_Candidates_and_Definition_Blockers.md`
- `PDS&ESS/README.md`
- `PDS&ESS/MBSE/tests/README.md`
- `S&A/PCB_General_Rules.md`

## Scope

Integrate PDS closure decisions into PM&SE Markdown. Do **not** edit `.d2`, `.png`, binary, or unrelated subsystem files. Do **not** execute tests. Do **not** commit or push.

## Required edits

### 1. `PM&SE/CON-003_Candidates_and_Definition_Blockers.md`

Update the PDS entries only, preserving the overall structure and avoiding broad rewrites outside PDS-related rows.

Required changes:

- In §1.2 “Subsystem candidate backlog”, update the PDS & ESS row so it explicitly lists the new regulator-efficiency candidate `PDS-VV-CON-010` and says it is a candidate/detailed definition pending, not executed. Keep that most v1.0 rows are model-defined.
- In §2.6 PDS & ESS blockers, change `PDS-BLK-002` through `PDS-BLK-009` from open blockers to dispositions consistent with the closure record:
  - `PDS-BLK-002`: definition-level decision selected; add INA219 I2C CE as pending source-model D2 edit; no execution credit until updated/justified.
  - `PDS-BLK-003`: definition-level candidate added (`PDS-VV-CON-010`); modeled definition/execution pending.
  - `PDS-BLK-004`: campaign-defined load/endurance profile accepted; execution parameter for `PDS-VV-CON-002` and system power tests, not a new model-definition blocker.
  - `PDS-BLK-005`: pending source-model/interface edit for master switch/accessibility; document as source edit/waiver path.
  - `PDS-BLK-006`: execution prerequisite for final powered charge acceptance, not a definition blocker.
  - `PDS-BLK-007`: closed at definition level by referencing `S&A/PCB_General_Rules.md`; deviations/evidence remain execution records.
  - `PDS-BLK-008`: closed at definition level by selected conservative missed-demand interpretation and quantitative setpoint/trial criteria; execution evidence pending.
  - `PDS-BLK-009`: campaign/execution confirmation for rail test parameters, not a definition blocker.
- Add a short folded PDS closure detail subsection after the PDS blocker table, similar in style to existing ADS/AMS folded sections but much shorter. It should include:
  - statement that this is definition-planning closure only; no tests executed; no D2/PNG edits performed;
  - candidate/update register including `PDS-VV-CON-010` and source-model follow-ons for INA219 I2C CE and master switch/accessibility;
  - existing-test update list (`PDS-VV-FC-002`, `PDS-VV-CON-002`, `PDS-VV-CON-003`, `PDS-VV-CON-004`, `PDS-VV-CON-009`, `PDS-VV-ALLOC-001`, PDS test index);
  - residual execution-only prerequisites.

### 2. `PM&SE/MBSE_Test_Plan_Assessment.md`

Update PDS-related findings only:

- `SUB-PDS-003`: say regulator efficiency candidate `PDS-VV-CON-010` is queued/added at definition-planning level; detailed modeled definition and execution remain pending.
- `SUB-PDS-004`: say INA219 I2C CE source edit is selected as a pending quick source-model/D2 update; until applied/justified, final CE completeness credit remains pending.
- `SUB-PDS-005`: split/clarify that the On-mode load profile may remain campaign-defined, while master-switch/accessibility is a pending source-model/interface edit.
- `GAP-006` or relevant cross-cutting efficiency row: update to note that a PDS efficiency validation candidate has been added, not executed.
- Avoid claiming final power acceptance or test execution.

## Done

- PM&SE files are consistent with `PM&SE/PDS_Blocker_Closure_Record_2026-07-02.md`.
- No `.d2`/`.png` files are modified.
- No execution pass/fail credit is claimed.
- Run `rg -n "PDS-BLK-00[2-9]|PDS-VV-CON-010|efficiency|Carvera|master switch|campaign-defined" PM&SE/CON-003_Candidates_and_Definition_Blockers.md PM&SE/MBSE_Test_Plan_Assessment.md` and summarize relevant hits in your final response.
