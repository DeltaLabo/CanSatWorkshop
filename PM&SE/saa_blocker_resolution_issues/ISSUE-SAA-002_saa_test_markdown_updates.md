# ISSUE-SAA-002 — S&A test Markdown updates

Work in `/Users/antho/CanSatWorkshop`.

## Read first

- `PM&SE/SAA_Blocker_Resolution_Plan_2026-07-02.md`
- `PM&SE/SAA_Blocker_Closure_Record_2026-07-02.md`
- `PM&SE/IVV.md`
- `S&A/README.md`
- `S&A/MBSE/tests/README.md`
- `S&A/MBSE/tests/SAA-VV-CE-001/README.md`
- `S&A/MBSE/tests/SAA-VV-ALLOC-001/README.md`
- `S&A/MBSE/tests/SAA-VV-FC-001/README.md`
- `S&A/MBSE/tests/SAA-VV-FC-002/README.md`
- `S&A/MBSE/tests/SAA-VV-CON-001/README.md`
- `S&A/MBSE/tests/SAA-VV-CON-003/README.md`
- `S&A/MBSE/tests/SAA-VV-CON-004/README.md`
- `S&A/MBSE/tests/SAA-VV-CON-005/README.md`
- `S&A/PCB_General_Rules.md`

## Output

Update only Markdown documentation under `S&A/` that is directly needed for S&A blocker alignment. Do not edit `PM&SE/` files in this issue except for reading the closure record. Do not edit `.d2`, `.png`, binary images/PDFs, source code, or other subsystem files. Do not execute tests. Do not commit or push.

## Required updates

Apply focused Markdown updates that align the S&A test documentation with the closure record. Keep wording clear that tests remain execution/report pending and that no pass/fail evidence has been produced.

### 1. Central test plan: `S&A/MBSE/tests/README.md`

Update the coverage/gaps or ambiguity sections so they state:

- The physical-only baseline S&A scope is an accepted modeling decision, not an unresolved blocker. `SAA-VV-CE-001` and `SAA-VV-ALLOC-001` remain required execution-time analyses for implied backplane/interface CE ownership and integration-function ownership, but no forced baseline CE/LC/F modeling is required for definition-decision closure.
- The S&A activity backlog is complete/model-defined: `SAA-VV-PC-001`, `SAA-VV-PL-001`, `SAA-VV-CE-001`, `SAA-VV-ALLOC-001`, `SAA-VV-FC-001`, `SAA-VV-FC-002`, `SAA-VV-FC-003`, and `SAA-VV-CON-001` through `SAA-VV-CON-005`. Execution/reporting remains pending.
- Confirm envelope/mass authority: use `122 mm` height and conservative `measured mass + U_M < 350.0 g` unless a later project authority selects a stricter competition limit.
- Add/reference selected quantitative backplane, printing, retention, and movement criteria from the closure record.
- For `SAA-BLK-003`, do **not** update environmental-screen test-definition criteria. Instead, if the central plan mentions ambiguity, change it only to say the environmental screen decision is approved in the closure record and detailed test-definition edits are pending/not applied in this pass.

### 2. Physical-scope non-issue docs

Update `SAA-VV-CE-001/README.md` and `SAA-VV-ALLOC-001/README.md` only as needed to avoid wording that presents the physical-only model as an unresolved definition blocker. Preserve their execution-time pass/hold/fail requirements and cross-reference logic. Good wording examples:

- “Baseline S&A remains intentionally physical-only; strict execution credit for this analysis comes from the ownership/cross-reference matrix, not from adding baseline S&A CEs in this pass.”
- “Baseline S&A remains intentionally physical-only; ownership analysis may pass with controlled physical-constraint-only S&A responsibilities plus subsystem model references.”

### 3. Confirmed envelope/mass authority

Check `SAA-VV-CON-001/README.md` and `SAA-VV-FC-001/README.md`. If they already use `122.0 mm` and conservative mass guard band, make only minimal wording changes to remove “needs authority confirmation” language. Do not weaken guard-band wording. Keep execution pending.

### 4. Backplane criteria (`SAA-BLK-005`)

Update `SAA-VV-CON-003/README.md` and, if relevant, `SAA-VV-FC-002/README.md` to include:

- released Fusion 360 design package / exported pin-interface evidence as frozen pinout source of truth;
- strict 100% pinout/netlist/header/connector match and no undocumented alternate pins or unowned extra nets;
- rail-load strict-credit rule: use released PDS/system load matrix; if absent, default S&A backplane screen is `1.0 A` aggregate per rail distributed across populated endpoints or applied at worst-case/farthest endpoint, current limited, thermally monitored, with all endpoints still in `5.0 ±0.1 V` / `3.3 ±0.1 V` tolerance;
- default I2C Standard-mode `100 kHz`, `3.3 V`, total bus capacitance `<=400 pF`, 30%-70% rise time `<=1000 ns`; if later Fast-mode `400 kHz` is selected, rise time `<=300 ns` and capacitance remains `<=400 pF` unless superseded;
- SPI/UART endpoint/direction/voltage/loading review;
- `S&A/PCB_General_Rules.md` as binding local workshop/Carvera-Air DFM rule set; IPC Class 2 intent only if external IPC comparison is required.

### 5. Printing/material/screw/proof criteria (`SAA-BLK-006`)

Update `SAA-VV-CON-004/README.md` to include:

- PLA selected material due to availability;
- preserve existing `0.2 mm` print precision/layer and `15%` infill/fill if present; only if no controlled value exists use the fallback `0.2 mm` and `10%`;
- accepted parts need print-profile/build evidence for material, layer height, infill/fill, wall/perimeter count, top/bottom layers, support/interface settings where relevant, and part IDs;
- if wall/perimeter/top-bottom settings are not controlled by released profile, require at least `2` perimeters/walls and `3` top/bottom layers or controlled deviation;
- torque criteria: exact torque by screw type or coupon characterization before execution; without that, do not exceed `0.20 N·m` self-tapping into PLA without coupon evidence; default target `0.05–0.10 N·m` for M2-class and `0.10–0.20 N·m` for M2.5-class screws, revised if screw type differs;
- proof-load criteria: non-destructive retention proof checks use `20 g` equivalent inertial load, with minimum `20 N` for ESS battery pack/battery fixture and `10 N` for PCBs, backplane/connector retention points, or top-module/servo-connector features unless stronger released values exist.

### 6. Movement thresholds (`SAA-BLK-007`)

Update `SAA-VV-CON-005/README.md` and, if directly useful, `SAA-VV-PL-001/README.md` or `SAA-VV-FC-003/README.md`, with the release thresholds from the closure record:

- battery movement `<=0.5 mm` and no rattle/new gap/crack/contact hazard;
- PCB/standoff displacement `<=0.25 mm`, no new gap/flex set/crack/stripped boss, screw witness-mark rotation `<=10°`;
- backplane/header seating-gap increase or displacement `<=0.25 mm`, no partial unseat/bent pin/intermittent continuity/short/open/rail failure;
- PDM servo connector and other connector movement/seating-gap increase `<=0.25 mm`, latch/friction retention engaged, no polarity shift/bent pin/intermittent continuity/harness strain;
- stack/top-module/cap/parachute gap `<=0.25 mm`, screw witness rotation `<=10°`, no new deployment-clearance interference;
- ambiguous evidence is hold, not pass.

### 7. Do not apply `SAA-BLK-003` definition edits

Do not edit `SAA-VV-CON-001/README.md` or `SAA-VV-CON-005/README.md` to replace the environmental hold path with approved environmental levels/surfaces/orientations. Only retain or add a note outside the detailed procedure if necessary that approved environmental-screen edits are pending per the closure record.

## Done

- Only directly relevant S&A Markdown files changed.
- No `.d2`, `.png`, binary, source-code, or unrelated subsystem files changed.
- The changed Markdown differentiates selected definition criteria from execution evidence and does not claim test pass/fail credit.
- The `SAA-BLK-003` approved environmental-screen definition edits remain pending and are not applied to the detailed test definitions in this issue.
