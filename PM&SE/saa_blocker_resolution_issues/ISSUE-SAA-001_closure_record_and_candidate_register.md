# ISSUE-SAA-001 — S&A closure record and candidate/update register

Work in `/Users/antho/CanSatWorkshop`.

## Read first

- `PM&SE/SAA_Blocker_Resolution_Plan_2026-07-02.md`
- `PM&SE/IVV.md`
- `PM&SE/MBSE_Test_Plan_Assessment.md`
- `PM&SE/CON-003_Candidates_and_Definition_Blockers.md`
- `S&A/README.md`
- `S&A/MBSE/tests/README.md`
- `S&A/MBSE/tests/SAA-VV-CE-001/README.md`
- `S&A/MBSE/tests/SAA-VV-ALLOC-001/README.md`
- `S&A/MBSE/tests/SAA-VV-CON-001/README.md`
- `S&A/MBSE/tests/SAA-VV-CON-003/README.md`
- `S&A/MBSE/tests/SAA-VV-CON-004/README.md`
- `S&A/MBSE/tests/SAA-VV-CON-005/README.md`
- `S&A/PCB_General_Rules.md`

## Output

Create only:

- `PM&SE/SAA_Blocker_Closure_Record_2026-07-02.md`

Do not edit any other file. Do not edit `.d2`/`.png`. Do not execute tests. Do not commit or push.

## Required content

The closure record must be self-contained and include:

1. **Scope:** definition decisions only; no execution credit; no D2/PNG edits; no candidate folders created in this issue.
2. **Decision table for `SAA-BLK-001` through `SAA-BLK-007`**, with these columns: selected disposition, affected candidate/new tests, affected existing tests/docs, model/test-definition follow-up, residual execution prerequisites/status.
3. **Apply these user decisions exactly:**
   - `SAA-BLK-001`: non-issue because the S&A model is physically focused. Do not require baseline S&A component exchanges solely for closure. Keep `SAA-VV-CE-001` as the execution-time cross-reference/ownership analysis.
   - `SAA-BLK-002`: non-issue because the S&A model is physically focused. Do not require baseline S&A logical/function/allocation modeling solely for closure. Keep `SAA-VV-ALLOC-001` as the execution-time ownership/disposition analysis.
   - `SAA-BLK-003`: approved. Record a pending edit to list tailored environmental screen levels/surfaces/orientations/success criteria as approved, but do not edit S&A test-definition files in this issue.
   - `SAA-BLK-004`: confirmed. Use `122 mm` height and conservative mass guard band (`measured mass + U_M < 350.0 g`) unless a later project authority selects a stricter requirement.
   - `SAA-BLK-005`: pinout is frozen by the Fusion 360 design; define the rest of the quantitative backplane criteria using the plan.
   - `SAA-BLK-006`: material is PLA due to availability; preserve existing controlled `0.2 mm` print precision/layer and `15%` fill/infill if present; if absent use `0.2 mm` and `10%`; define the rest of the quantitative print/screw/proof criteria using the plan.
   - `SAA-BLK-007`: release quantitative movement/witness-mark thresholds using the plan.
4. **Complete S&A candidate/detailed-definition backlog:**
   - State that the S&A activity set is already model-defined rather than a planning-candidate backlog: `SAA-VV-PC-001`, `SAA-VV-PL-001`, `SAA-VV-CE-001`, `SAA-VV-ALLOC-001`, `SAA-VV-FC-001`, `SAA-VV-FC-002`, `SAA-VV-FC-003`, and `SAA-VV-CON-001` through `SAA-VV-CON-005`.
   - Clarify that no new S&A candidate folder is required by this pass. Remaining work is Markdown criteria alignment, pending environmental-screen edit, optional future baseline D2/source-model updates, and execution/reporting.
   - Note that S&A has physical-only baseline views; `SAA-VV-CE-001` and `SAA-VV-ALLOC-001` are the correct model-defined analyses for implied interfaces/ownership rather than blockers.
5. **Selected quantitative criteria summary** for at least:
   - backplane pinout source of truth, rail-load/voltage-drop acceptance, I2C mode/capacitance/rise-time, SPI/UART endpoint/loading evidence, and DFM/IPC disposition;
   - PLA material, layer/infill policy, minimum print-profile evidence, print precision, screw torque/cycle criteria, and proof-load/pull values;
   - movement thresholds for battery, PCBs/standoffs, backplane/header mating, PDM servo connector/other connectors, stack screws/top-module/cap/parachute context.
6. **Existing-test update list** with what should be updated now/later for at least:
   - `S&A/MBSE/tests/README.md`
   - `SAA-VV-CE-001` and `SAA-VV-ALLOC-001` for the physical-scope non-issue rationale
   - `SAA-VV-CON-001` / `SAA-VV-FC-001` for confirmed height/mass authority if any text still says it needs confirmation
   - `SAA-VV-CON-003` / `SAA-VV-FC-002` for frozen Fusion 360 pinout and backplane quantitative criteria
   - `SAA-VV-CON-004` for PLA, layer/infill, print-profile, torque/cycle/proof criteria
   - `SAA-VV-CON-005` and affected PL/FC docs for movement thresholds
   - PM&SE CON-003 and assessment integration
   - `SAA-BLK-003` pending test-definition edit, while explicitly saying not to apply it in this pass
7. **Follow-on D2/source-model list**, including optional future source-model updates only if the project wants baseline S&A CEs/allocations, plus any future regenerated PNGs. Make clear these are not required to close `SAA-BLK-001`/`002` at definition-decision level.
8. **Residual execution-only prerequisites**, including exact article IDs, Fusion 360 design revision/exported pinout evidence, board revision, load matrix or default-load approval, equipment calibration, environmental screen evidence, printer/material lot, screw type, torque release/coupon data, proof-load fixture limits, movement measurement method, and deviation/waiver records.

## Done

`PM&SE/SAA_Blocker_Closure_Record_2026-07-02.md` exists, is self-contained, and every `SAA-BLK-001` through `SAA-BLK-007` appears exactly once in the decision table.
