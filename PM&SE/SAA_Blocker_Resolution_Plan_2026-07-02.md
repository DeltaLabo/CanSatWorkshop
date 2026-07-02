# S&A Blocker Resolution Plan — CON-003 §2.8

Date: 2026-07-02
Repository: CanSat Workshop

## End goal

Resolve the S&A definition blockers in `PM&SE/CON-003_Candidates_and_Definition_Blockers.md` §2.8 at definition-decision level so the S&A test suite has:

1. a complete S&A candidate/detailed-definition backlog,
2. a controlled list of updates to existing S&A tests,
3. selected quantitative criteria for backplane, printing/material, retention and movement blockers, and
4. PM&SE/S&A Markdown updates showing which items are non-issues, approved decisions, pending edits, or execution-only prerequisites.

This pass does **not** execute tests and does **not** claim pass/fail credit. It must not edit `.d2` or `.png` diagrams. Markdown documentation may be updated where useful, except that `SAA-BLK-003` environmental screen test definitions are not to be edited in this pass; only record the approved decision and the pending edit list.

## User decisions to apply

- `SAA-BLK-001`: non-issue. The S&A model is intentionally physically focused. Do not force baseline S&A component-exchange modeling solely to satisfy this blocker; `SAA-VV-CE-001` remains the execution-time ownership/cross-reference analysis for implied backplane/interface CEs.
- `SAA-BLK-002`: non-issue. The S&A model is intentionally physically focused. Do not force baseline S&A logical/function/allocation modeling solely to satisfy this blocker; `SAA-VV-ALLOC-001` remains the execution-time ownership/disposition analysis.
- `SAA-BLK-003`: approved. Record a pending edit to list the tailored drop/vibration/landing environmental screen plan as approved, but do **not** edit the S&A test-definition files for this blocker in this pass.
- `SAA-BLK-004`: confirmed. Use the modeled `122 mm` height acceptance and conservative total mass policy (`measured mass + U_M < 350.0 g`) as the S&A envelope/mass authority unless a later project authority selects a stricter competition limit.
- `SAA-BLK-005`: the backplane pinout is frozen by the Fusion 360 design. Define and document the remaining quantitative criteria.
- `SAA-BLK-006`: print material is PLA due to availability. Existing controlled layer/precision and fill/infill values should be preserved; if absent, use `0.2 mm` layer height and `10%` infill defaults. Define the other quantitative criteria.
- `SAA-BLK-007`: define movement/witness-mark thresholds for battery, PCB, backplane and connector retention screens.

## Selected criteria to encode unless a subagent finds a stronger existing controlled criterion

### `SAA-BLK-005` backplane / pinout / electrical-design criteria

- **Pinout source of truth:** the released Fusion 360 backplane design package and exported pin-interface evidence are frozen. Strict execution credit requires 100% match between the released design, installed headers/connectors, netlist, `S&A/Pin Interface_page-0001.jpg` or successor controlled pin-interface evidence, and the inspected article. No pin swaps, undocumented alternates, or unowned extra nets are allowed.
- **Connector/header geometry:** use the existing S&A requirement for `2 mm 2×6` headers and the TMM-106-01-L-D-RA SAMTEC family unless the released Fusion 360 package supersedes it. Each ADS/AMS/OBCC/PDS header and the PDM servo connector must have endpoint, orientation, pin-1, and polarity evidence.
- **Rail-load acceptance:** preserve `5.0 ±0.1 V` and `3.3 ±0.1 V` at required backplane testpoints and subsystem connector endpoints. Execute no-load continuity/isolation before power. Strict loaded credit uses the released PDS/system load matrix; if no matrix is released at execution time, use a documented S&A backplane screen of `1.0 A` aggregate per rail distributed across the populated endpoints or applied at the worst-case/farthest endpoint, with current limiting, thermal monitoring, and all measured endpoints still within tolerance. Lower loads are characterization/limited unless approved by the review board.
- **Voltage drop / thermal guard:** voltage drop through the backplane distribution must not cause any required endpoint to leave the rail tolerance. Record source voltage, endpoint voltage, current, duration, ambient, and board temperature; any visible heating damage, odor, discoloration, or temperature rise beyond the campaign thermal limit is hold/fail.
- **I2C baseline:** default strict S&A backplane I2C mode is Standard-mode `100 kHz` at `3.3 V` unless the system interface authority releases Fast-mode. Total bus capacitance, including PCB trace, headers, module inputs, pullups, pads, and required testpoints, shall be `<=400 pF`; 30%-70% rise time shall be `<=1000 ns` for Standard-mode. If Fast-mode `400 kHz` is selected later, use the stricter `<=300 ns` rise-time target while keeping `<=400 pF` bus capacitance unless the selected standard says otherwise.
- **SPI/UART fast-line evidence:** all SPI and UART nets require 100% endpoint/direction/voltage review, no swapped TX/RX/MOSI/MISO/clock/chip-select lines, no unowned stubs or probe points, and accepted loading/topology rationale. Optional scope/logic-analyzer evidence is characterization unless promoted by a later detailed test.
- **DFM / IPC disposition:** use the project local fabrication rule set in `S&A/PCB_General_Rules.md` as the binding workshop/Carvera-Air DFM rule set. If an IPC class must be stated for external comparison, treat the workshop CanSat as IPC Class 2 intent unless a later authority selects otherwise. All DRC/ERC/DFM warnings or deviations require explicit disposition before strict credit.

### `SAA-BLK-006` printing / material / screw / proof criteria

- **Material:** PLA is the selected structural print material. Record filament supplier/type/color if relevant, material lot if available, printer ID, nozzle, slicer/profile version, build date, orientation, and reprint history.
- **Layer and infill:** preserve existing controlled values. Current S&A documents already contain `0.2 mm` print precision and `15%` fill/infill; use these unless a controlled source says otherwise. The user-approved fallback only if no controlled value exists is `0.2 mm` layer height and `10%` infill.
- **Minimum print-profile evidence:** accepted parts need slicer/G-code/build evidence for material, layer height, infill/fill, wall/perimeter count, top/bottom layers, support/interface settings where relevant, and part IDs. If wall/perimeter/top-bottom settings are not controlled by a released profile, require at least `2` perimeters/walls and at least `3` top/bottom layers for accepted structural parts or record a controlled deviation.
- **Dimensional precision:** keep the existing `|measured - nominal| + U <= 0.2 mm` rule for critical printed features unless a drawing has a stricter tolerance.
- **Screw torque:** exact torque shall be released by screw type or coupon characterization before execution. Pending that release, strict pass should use a torque-limited hand tool, record torque for each screw family, and prohibit installation torque above `0.20 N·m` for self-tapping screws into PLA without coupon evidence. A conservative default target range is `0.05–0.10 N·m` for small M2-class screws and `0.10–0.20 N·m` for M2.5-class screws; revise if the controlled screw type differs.
- **Screw/fit cycles:** retain the existing workmanship screen of at least `3` representative coupons/modules per printer/material batch and no stripped boss, boss pull-out, crack, delamination, weak-infill crushing, torque damage, warped slot, loose standoff, or alignment loss. Use `29/29` independent zero-failure trials only if a R90/C95 screw-hole reliability claim is made.
- **Retention proof-loads:** for non-destructive retention proof checks, use `20 g` equivalent inertial load in each relevant axis/orientation for the retained item mass, with minimum applied proof loads of `20 N` for the ESS battery pack/battery fixture and `10 N` for individual PCBs, backplane/connector retention points, or top-module/servo-connector features unless a released fixture/test definition gives a stronger value. Do not overload electronics, Li-ion cells, or connectors beyond safe fixture limits; use surrogate masses/fixtures if needed and record limitations.

### `SAA-BLK-007` movement / witness-mark thresholds

Use measurement uncertainty guard bands where measurements are taken. Any crack, rattle, loss of continuity/isolation, rail failure, connector unseat, bent pin, forced reseat, or unapproved post-screen tightening is hold/fail regardless of measured displacement.

- ESS battery pack / battery fixture: no detachment; witness-mark shift or measured movement `<=0.5 mm` in any direction after screen; no new gap, rattle, fixture crack, cell damage, harness strain, or contact with prohibited neighbors.
- ADS/AMS/OBCC/PDS PCBs and PCB standoffs/screws: board-edge or standoff displacement `<=0.25 mm`; no new gap, board flex set, cracked/stripped boss, loose standoff, or witness-mark rotation beyond `10°`.
- Backplane PCB / backplane spine / header mating: displacement or seating-gap increase `<=0.25 mm`; no partial unseat, bent pin, intermittent continuity, new short/open, or rail/testpoint failure.
- PDM servo connector and other connectors/harnesses: connector seating-gap increase or relative movement `<=0.25 mm`; latch/friction retention remains engaged; no polarity/orientation shift, bent pin, intermittent continuity, insulation damage, or harness strain relief failure.
- Stack screws/top-module/cap/parachute context: no new visible gap over `0.25 mm`, no screw witness-mark rotation beyond `10°`, and no new interference with parachute/cap/servo clearance.
- If a feature cannot be measured to the above resolution, use before/after witness marks, macro photos, and continuity/functional checks; ambiguous evidence is hold, not pass.

## Work breakdown

| Issue | Delegated work | Main outputs | Dependencies |
|---|---|---|---|
| `ISSUE-SAA-001_closure_record_and_candidate_register.md` | Create central S&A closure record with dispositions, candidate/detailed-definition backlog, existing-test update list, selected quantitative criteria, pending D2/source-model follow-on list, and residual execution prerequisites. | `PM&SE/SAA_Blocker_Closure_Record_2026-07-02.md` | First |
| `ISSUE-SAA-002_saa_test_markdown_updates.md` | Apply S&A Markdown-only updates to the central test plan and relevant test READMEs for non-issue CE/allocation disposition, confirmed envelope/mass authority, backplane criteria, PLA/print criteria, and movement thresholds. Do **not** edit test definitions for `SAA-BLK-003`; only preserve pending-edit wording if needed outside definition files. | Updated `S&A/MBSE/tests/README.md` and focused S&A test READMEs; no `.d2`/`.png` | After issue 001 |
| `ISSUE-SAA-003_pmse_integration.md` | Integrate S&A closure into PM&SE registers/assessment without overclaiming execution, including `SAA-BLK-003` approved/pending-edit status and no forced S&A logical/CE modeling. | Updated `PM&SE/CON-003_Candidates_and_Definition_Blockers.md`, `PM&SE/MBSE_Test_Plan_Assessment.md` | After issues 001–002 |
| `ISSUE-SAA-004_validation_cleanup.md` | Validate consistency, ensure no D2/PNG edits and no execution-credit claims, summarize status, and remove temporary SAA issue files. | Issue directory removed; plan remains | Last |

## Coordination rules for subagents

- Work from `/Users/antho/CanSatWorkshop`.
- Read this plan, your issue file, `PM&SE/IVV.md`, `PM&SE/MBSE_Test_Plan_Assessment.md`, `PM&SE/CON-003_Candidates_and_Definition_Blockers.md`, and every S&A file your issue references.
- Do not push. Do not commit; the orchestrator will review and commit path-specific changes.
- Do not edit `.d2`, `.png`, binary image/PDF files, source code, or unrelated subsystem files.
- Do not execute hardware tests or claim execution pass/fail credit.
- Use wording such as “definition decision selected”, “non-issue by physical-scope rationale”, “approved pending edit”, “candidate/detailed definition already model-defined”, “execution pending”, or “D2/model follow-up pending” as appropriate.
- Keep definition decisions separate from D2/model follow-up and execution prerequisites.
- For `SAA-BLK-003`, do not modify the S&A test-definition READMEs to insert approved environmental levels in this pass. Record only that an approved/pending edit exists.
- If scope conflicts appear, stop and summarize instead of making broad unrelated changes.

## Acceptance criteria

- Every `SAA-BLK-001` through `SAA-BLK-007` appears exactly once in the closure record decision table with selected disposition, affected tests/docs, model/test-definition follow-up, and residual status.
- `SAA-BLK-001` and `SAA-BLK-002` are no longer described as unresolved definition blockers; they are documented as non-issues for a physically focused S&A model with execution-time CE/allocation cross-reference analyses.
- `SAA-BLK-003` is recorded as approved with a pending edit list, and S&A environmental test-definition files are not edited for that blocker in this pass.
- `SAA-BLK-004` uses confirmed `122 mm` height and conservative mass guard-band policy.
- `SAA-BLK-005`, `SAA-BLK-006`, and `SAA-BLK-007` have quantitative criteria sufficient to guide later execution and any future D2/source-model updates.
- S&A Markdown updates, if applied, are consistent with the selected criteria and do not claim tests were executed.
- PM&SE assessment/register language distinguishes closed definition decisions from pending detailed edits, execution evidence, D2/source-model updates, and final CanSat readiness.
- Temporary issue files under `PM&SE/saa_blocker_resolution_issues/` are removed by the final cleanup issue. This plan remains as the high-level orchestration record.

## Execution status

Planning created; issue delegation pending.
