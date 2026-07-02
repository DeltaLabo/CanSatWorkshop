# ISSUE-PDS-001 — PDS closure record and candidate/update register

Work in `/Users/antho/CanSatWorkshop`.

## Read first

- `PM&SE/PDS_Blocker_Resolution_Plan_2026-07-02.md`
- `PM&SE/IVV.md`
- `PM&SE/MBSE_Test_Plan_Assessment.md`
- `PM&SE/CON-003_Candidates_and_Definition_Blockers.md`
- `PDS&ESS/README.md`
- `PDS&ESS/MBSE/tests/README.md`
- `PDS&ESS/MBSE/tests/PDS-VV-FC-002/README.md`
- `PDS&ESS/MBSE/tests/PDS-VV-CON-001/README.md`
- `PDS&ESS/MBSE/tests/PDS-VV-CON-002/README.md`
- `PDS&ESS/MBSE/tests/PDS-VV-CON-003/README.md`
- `PDS&ESS/MBSE/tests/PDS-VV-CON-004/README.md`
- `PDS&ESS/MBSE/tests/PDS-VV-CON-009/README.md`
- `PDS&ESS/MBSE/tests/PDS-VV-ALLOC-001/README.md`
- `S&A/PCB_General_Rules.md`

## Output

Create only:

- `PM&SE/PDS_Blocker_Closure_Record_2026-07-02.md`

Do not edit any other file. Do not edit `.d2`/`.png`. Do not execute tests. Do not commit or push.

## Required content

The closure record must be self-contained and include:

1. **Scope:** definition decisions only; no execution credit; no D2/PNG edits; no candidate folders created in this issue.
2. **Decision table for `PDS-BLK-002` through `PDS-BLK-009`**, with these columns: selected disposition, affected candidate/new tests, affected existing tests/docs, source-model or execution prerequisites, follow-up status.
3. **Apply these user decisions exactly:**
   - `PDS-BLK-002`: source-model quick fix selected: add explicit INA219 `[CE] I2C` exchange between ESS Processing/XIAO and Battery monitoring/INA219; document as D2/source-model follow-on in this pass.
   - `PDS-BLK-003`: add regulator-efficiency validation candidate to the candidate list; use ID `PDS-VV-CON-010` unless you find a conflicting established ID.
   - `PDS-BLK-004`: leave On-mode load/current budget and 6 h endurance profile campaign-defined; no new modeled load-profile estimation test.
   - `PDS-BLK-005`: master-switch/accessibility hardware detail requires source/interface fix; document as pending source-model/interface edit.
   - `PDS-BLK-006`: Li-ion safety docs/charger model/cell evidence are literal execution prerequisites, not definition blockers.
   - `PDS-BLK-007`: DFM rule set is documented in `S&A/PCB_General_Rules.md`; PDS DFM tests should reference it and keep deviation records as execution evidence.
   - `PDS-BLK-008`: define quantitative criteria using the plan’s selected missed-demand interpretation, statistics, setpoints, safe outcome, and independence rules.
   - `PDS-BLK-009`: rail nominal-load/thermal/settling parameters are literal campaign/execution confirmations, not a test-definition flaw.
4. **Complete candidate backlog:**
   - Existing modeled PDS v1.0 definitions: `PDS-VV-PC-001`, `PDS-VV-PL-001`, `PDS-VV-CE-001`, `PDS-VV-CE-002`, `PDS-VV-CE-003`, `PDS-VV-ALLOC-001`, `PDS-VV-ALLOC-002`, `PDS-VV-ALLOC-003`, `PDS-VV-FC-001`, `PDS-VV-FC-002`, `PDS-VV-CON-001` through `PDS-VV-CON-009`, `PDS-VV-SAFE-001`.
   - New candidate: `PDS-VV-CON-010` regulator efficiency validation for the PDS README 3.3 V and 5 V at 1 A / 95% efficiency requirements. Mark as candidate/detailed definition pending, not executed.
   - Incremental gates already modeled: `PDS-V01-GATE-001`, `PDS-VV-V02-FC-001`, `PDS-V03-GATE-001`; clarify they are not substitutes for v1.0 final acceptance.
5. **Existing-test update list** with what should be updated now/later for at least:
   - `PDS&ESS/MBSE/tests/README.md`
   - `PDS-VV-FC-002` / `PDS-VV-CE-003` for the selected I2C CE source edit
   - `PDS-VV-CON-002` for campaign-defined 6 h load profile
   - `PDS-VV-CON-003` for quantitative protection-probability criteria
   - `PDS-VV-CON-004` for rail campaign parameters being execution confirmations
   - `PDS-VV-CON-009` for `S&A/PCB_General_Rules.md`
   - `PDS-VV-ALLOC-001` / `PDS-VV-ALLOC-003` for master-switch/accessibility source edit
   - PM&SE CON-003 and assessment integration
6. **Follow-on D2/source-model list**, including:
   - Add explicit INA219 I2C CE to `PDS&ESS/MBSE/v1.0/PDS_v1.0_view2_logical.d2` and regenerate PNG.
   - Refresh baseline copies in affected test folders after source-model update, if project policy requires baseline recopy.
   - Add/clarify master switch/accessibility hardware/interface in the relevant PDS physical/source model and regenerate PNG.
   - Later create/model `PDS-VV-CON-010` if/when the efficiency candidate is promoted.
7. **Residual execution-only prerequisites**, including exact article IDs, hardware revisions, charger/cell safety documents, equipment calibration, thermal limits, campaign load settings, rail settling windows, trial setpoints, and deviation/waiver records.

## Done

`PM&SE/PDS_Blocker_Closure_Record_2026-07-02.md` exists, is self-contained, and every `PDS-BLK-002` through `PDS-BLK-009` appears exactly once in the decision table.
