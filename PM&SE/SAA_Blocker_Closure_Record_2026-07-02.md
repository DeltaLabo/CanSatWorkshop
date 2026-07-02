# S&A Blocker Closure Record and Candidate/Update Register — 2026-07-02

Repository: `CanSatWorkshop`  
Scope owner: PM&SE / S&A IVV coordination  
Status: definition decisions selected; execution/reporting pending

## 1. Scope and status

This record is self-contained and covers S&A definition decisions only. It does **not** execute hardware tests, does **not** create execution reports, and does **not** claim pass/fail credit for any S&A activity.

This issue created only this Markdown record. It did **not** edit `.d2` or `.png` files, did **not** edit source code or binary artifacts, and did **not** create new S&A candidate folders. The remaining work is controlled Markdown criteria alignment, the pending environmental-screen test-definition edit, optional future source-model/D2 updates if the project elects to add baseline S&A CE/allocation views, and later execution/reporting with evidence.

## 2. Definition-decision table

| Blocker | Selected disposition | Affected candidate/new tests | Affected existing tests/docs | Model/test-definition follow-up | Residual execution prerequisites/status |
|---|---|---|---|---|---|
| `SAA-BLK-001` | Non-issue by physical-scope rationale. The baseline S&A model is intentionally physically focused; do not require baseline S&A component exchanges solely for closure. Keep the CE activity as the execution-time cross-reference/ownership analysis for implied backplane rails, pin interfaces, testpoints, SPI/I2C/UART, and servo-connector paths. | No new candidate or folder. Use existing model-defined `SAA-VV-CE-001`. | `S&A/MBSE/tests/README.md`, `S&A/MBSE/tests/SAA-VV-CE-001/README.md`, PM&SE CON-003 register, PM&SE assessment. | Update wording from unresolved definition blocker to physical-scope non-issue plus execution-time CE ownership/cross-reference analysis. Optional baseline CE source-model/D2 updates only if the project later wants explicit S&A CEs. | Execution pending only: released pinout/netlist, Fusion 360/export evidence, board revision, subsystem CE references or owner responses, completed ownership matrix, calibrated evidence, deviations/waivers. No execution credit here. |
| `SAA-BLK-002` | Non-issue by physical-scope rationale. The baseline S&A model is intentionally physically focused; do not require baseline S&A logical/function/allocation modeling solely for closure. Keep the allocation activity as the execution-time ownership/disposition analysis. | No new candidate or folder. Use existing model-defined `SAA-VV-ALLOC-001`. | `S&A/MBSE/tests/README.md`, `S&A/MBSE/tests/SAA-VV-ALLOC-001/README.md`, PM&SE CON-003 register, PM&SE assessment. | Update wording from unresolved allocation blocker to physical-scope non-issue plus execution-time ownership/disposition analysis. Optional baseline LC/F/allocation source-model/D2 updates only if the project later wants explicit S&A logical ownership views. | Execution pending only: owner/disposition matrix for physical integration functions, subsystem model references, waivers/model-change requests, article/configuration IDs, evidence archive. No execution credit here. |
| `SAA-BLK-003` | Approved pending edit. Tailored environmental screen levels, surfaces, orientations/axes, durations/events, limitations, and success criteria are approved as the closure decision, but the S&A test-definition files are not edited in this issue. | No new S&A candidate or folder. Use existing `SAA-VV-CON-001`, `SAA-VV-CON-005`, and later system environmental regression planning. | `S&A/MBSE/tests/README.md`; `S&A/MBSE/tests/SAA-VV-CON-001/README.md`; `S&A/MBSE/tests/SAA-VV-CON-005/README.md`; PM&SE assessment/register. | Later Markdown edit shall insert the approved tailored drop/vibration/landing screen plan and post-screen checks into the affected test definitions. Do not apply that edit in this pass. D2/PNG refresh, if desired, is later. | Execution pending only: controlled screen definition, impact/vibration surfaces, axes/orientations, fixture coupling, event/logger evidence, safety boundary, equipment calibration, article IDs, pre/post inspection and deviation/waiver records. |
| `SAA-BLK-004` | Confirmed. Use modeled `122 mm` height and conservative mass guard band `measured mass + U_M < 350.0 g` unless a later project authority selects a stricter requirement. | No new candidate or folder. Existing `SAA-VV-CON-001` and `SAA-VV-FC-001` remain the definition/report references. | `S&A/README.md`; `S&A/MBSE/tests/README.md`; `S&A/MBSE/tests/SAA-VV-CON-001/README.md`; `SAA-VV-FC-001` definition; PM&SE assessment/register. | Update any “needs confirmation” wording to the confirmed authority above; preserve note that later stricter competition authority may supersede it. | Execution pending only: exact as-flown article ID, full configuration, calibrated envelope gauge/calipers/height gauge/scale, uncertainty method, ambient record, raw readings, deviations/waivers. |
| `SAA-BLK-005` | Definition decision selected. Backplane pinout is frozen by the Fusion 360 design; remaining quantitative backplane criteria are released by this record for rail load, voltage drop, I2C, SPI/UART, endpoint evidence, and DFM/IPC disposition. | No new candidate or folder. Existing `SAA-VV-CON-003`, `SAA-VV-FC-002`, and `SAA-VV-CE-001` remain the definition/report references. | `S&A/README.md` backplane section; `S&A/MBSE/tests/README.md`; `S&A/MBSE/tests/SAA-VV-CON-003/README.md`; `SAA-VV-FC-002` definition; `SAA-VV-CE-001`; `S&A/PCB_General_Rules.md` as DFM rule source; PM&SE assessment/register. | Update Markdown criteria to name the released Fusion 360 package/exported pin-interface evidence as source of truth and to add the quantitative electrical/DFM criteria below. Optional D2/source constraints and regenerated PNGs later. | Execution pending only: Fusion 360 revision/export, controlled pin-interface evidence, board revision, netlist, DRC/ERC/DFM dispositions, load matrix or approved default-load path, calibrated power/continuity/SI equipment, raw readings, deviations/waivers. |
| `SAA-BLK-006` | Definition decision selected. Structural print material is PLA due to availability. Existing controlled `0.2 mm` print precision/layer and `15%` fill/infill are present and preserved; the fallback `0.2 mm` and `10%` rule is not used unless a future source lacks controlled values. Remaining print, screw, cycle, and proof criteria are released by this record. | No new candidate or folder. Existing `SAA-VV-CON-004` remains the primary definition/report reference, with retention interactions in `SAA-VV-CON-005` and relevant PL/FC definitions. | `S&A/README.md`; `S&A/MBSE/tests/README.md`; `S&A/MBSE/tests/SAA-VV-CON-004/README.md`; `SAA-VV-PL-001`; retention/deployment-clearance definitions as applicable; PM&SE assessment/register. | Update Markdown criteria to select PLA, preserve `0.2 mm` and `15%`, add minimum print-profile evidence, torque-release/coupon policy, screw-cycle basis, and proof-load values. Optional D2/PNG refresh later. | Execution pending only: printer ID, slicer/profile/G-code, PLA supplier/type/color/lot, material batch, part IDs/reprints, exact screw types, torque release or coupon data, torque tool calibration, proof-load fixture limits, deviations/waivers. |
| `SAA-BLK-007` | Definition decision selected. Quantitative movement and witness-mark thresholds are released for battery, PCBs/standoffs, backplane/header mating, PDM servo connector/other connectors, stack screws, top-module, cap, and parachute context. | No new candidate or folder. Existing `SAA-VV-CON-005` remains primary; affected context includes `SAA-VV-PL-001`, `SAA-VV-FC-002`, `SAA-VV-FC-003`, and post-impact portions of `SAA-VV-CON-001`. | `S&A/MBSE/tests/README.md`; `S&A/MBSE/tests/SAA-VV-CON-005/README.md`; affected PL/FC/CON definitions; PM&SE assessment/register. | Update Markdown criteria to replace “visible movement with no threshold” hold language with the released thresholds below, while retaining hold/fail for cracks, rattle, unseat, loss of continuity/isolation, or ambiguous evidence. Optional D2/PNG refresh later. | Execution pending only: approved environmental/proof screen, before/after witness marks, measurement method/resolution/uncertainty, macro photos, continuity/isolation and rail checks, article IDs, no-reseat/no-tightening control, deviations/waivers. |

## 3. S&A candidate and detailed-definition backlog

The S&A activity set is already model-defined rather than a planning-candidate backlog. The controlled activity set is:

- `SAA-VV-PC-001`
- `SAA-VV-PL-001`
- `SAA-VV-CE-001`
- `SAA-VV-ALLOC-001`
- `SAA-VV-FC-001`
- `SAA-VV-FC-002`
- `SAA-VV-FC-003`
- `SAA-VV-CON-001` through `SAA-VV-CON-005`

No new S&A candidate folder is required by this pass. Remaining work is Markdown criteria alignment, the pending environmental-screen edit, optional future baseline D2/source-model updates, any later regenerated PNGs, and execution/reporting.

S&A has physical-only baseline views. That is an accepted modeling-scope decision for this closure pass. `SAA-VV-CE-001` and `SAA-VV-ALLOC-001` are the correct model-defined analyses for implied interfaces and integration-function ownership/disposition; they are not definition blockers requiring baseline S&A CE or allocation diagrams before definition-decision closure.

## 4. Selected quantitative criteria summary

### 4.1 Backplane, pinout, rail, signal, and DFM criteria

- **Pinout source of truth:** the released Fusion 360 backplane design package and exported pin-interface evidence are frozen. Strict execution credit requires a 100% match between the released design, installed headers/connectors, netlist, `S&A/Pin Interface_page-0001.jpg` or successor controlled pin-interface evidence, and the inspected article. No pin swaps, undocumented alternates, or unowned extra nets are allowed.
- **Connector/header geometry:** preserve the existing `2 mm 2×6` header requirement and TMM-106-01-L-D-RA SAMTEC family unless the released Fusion 360 package supersedes it. Each ADS/AMS/OBCC/PDS header and the PDM servo connector need endpoint, orientation, pin-1, and polarity evidence.
- **Rail-load acceptance:** perform no-load continuity/isolation before power. Preserve `5.0 ±0.1 V` and `3.3 ±0.1 V` at required backplane testpoints and subsystem connector endpoints. Strict loaded credit uses the released PDS/system load matrix. If no matrix is released at execution time, use an approved S&A backplane screen of `1.0 A` aggregate per rail, distributed across populated endpoints or applied at the worst-case/farthest endpoint, with current limiting, thermal monitoring, and all endpoints still in tolerance. Lower loads are characterization/limited unless approved by the review board.
- **Voltage-drop and thermal guard:** backplane distribution drop shall not cause any required endpoint to leave rail tolerance. Record source voltage, endpoint voltage, current, duration, ambient, and board temperature. Visible heating damage, odor, discoloration, or temperature rise beyond the campaign thermal limit is hold/fail.
- **I2C baseline:** default strict S&A backplane I2C mode is Standard-mode `100 kHz` at `3.3 V` unless the system interface authority releases Fast-mode. Total bus capacitance, including traces, headers, module inputs, pullups, pads, and required testpoints, shall be `<=400 pF`; 30%-70% rise time shall be `<=1000 ns` for Standard-mode. If Fast-mode `400 kHz` is later selected, use `<=300 ns` rise time while keeping `<=400 pF` bus capacitance unless the selected standard says otherwise.
- **SPI/UART fast-line evidence:** all SPI and UART nets require 100% endpoint, direction, voltage-level, loading, and topology review. No swapped TX/RX/MOSI/MISO/clock/chip-select lines, unowned stubs, or unowned probe points are allowed. Scope/logic-analyzer evidence is characterization unless promoted by a later detailed test.
- **DFM / IPC disposition:** `S&A/PCB_General_Rules.md` is the binding workshop/Carvera-Air DFM rule set. If an IPC class is needed for external comparison, treat the workshop CanSat as IPC Class 2 intent unless a later authority selects otherwise. All DRC/ERC/DFM warnings or deviations require explicit disposition before strict credit.

### 4.2 Printing, material, screw, cycle, and proof criteria

- **Material:** PLA is the selected structural print material. Execution records must capture filament supplier/type/color if relevant, material lot if available, printer ID, nozzle, slicer/profile version, build date, orientation, and reprint history.
- **Layer / precision / infill policy:** existing controlled values are preserved: `0.2 mm` print precision/layer policy and `15%` fill/infill. The fallback `0.2 mm` layer height and `10%` infill applies only if a future accepted source has no controlled value.
- **Minimum print-profile evidence:** accepted parts need slicer/G-code/build evidence for material, layer height, infill/fill, wall/perimeter count, top/bottom layers, support/interface settings where relevant, and part IDs. If wall/perimeter/top-bottom settings are not controlled by a released profile, require at least `2` walls/perimeters and at least `3` top/bottom layers for accepted structural parts or record a controlled deviation.
- **Dimensional precision:** critical printed features must satisfy `|measured - nominal| + U <= 0.2 mm` unless a released drawing has a stricter tolerance.
- **Screw torque:** exact torque shall be released by screw type or coupon characterization before execution. Pending that release, strict pass uses a torque-limited hand tool, records torque for each screw family, and prohibits installation torque above `0.20 N·m` for self-tapping screws into PLA without coupon evidence. Conservative default target ranges are `0.05–0.10 N·m` for small M2-class screws and `0.10–0.20 N·m` for M2.5-class screws; revise if the controlled screw type differs.
- **Screw/fit cycles:** retain the workmanship screen of at least `3` representative coupons/modules per printer/material batch and no stripped boss, boss pull-out, crack, delamination, weak-infill crushing, torque damage, warped slot, loose standoff, or alignment loss. Use `29/29` independent zero-failure trials only if an R90/C95 screw-hole reliability claim is made.
- **Retention proof-loads:** for non-destructive retention proof checks, use `20 g` equivalent inertial load in each relevant axis/orientation for the retained item mass, with minimum applied proof loads of `20 N` for the ESS battery pack/battery fixture and `10 N` for individual PCBs, backplane/connector retention points, or top-module/servo-connector features unless a released fixture/test definition gives a stronger value. Do not overload electronics, Li-ion cells, or connectors beyond safe fixture limits; use surrogate masses/fixtures if needed and record limitations.

### 4.3 Movement and witness-mark thresholds

Use measurement uncertainty guard bands wherever measurements are taken. Any crack, rattle, loss of continuity/isolation, rail failure, connector unseat, bent pin, forced reseat, or unapproved post-screen tightening is hold/fail regardless of measured displacement.

| Feature | Released threshold |
|---|---|
| ESS battery pack / battery fixture | No detachment; witness-mark shift or measured movement `<=0.5 mm` in any direction after screen; no new gap, rattle, fixture crack, cell damage, harness strain, or contact with prohibited neighbors. |
| ADS/AMS/OBCC/PDS PCBs and PCB standoffs/screws | Board-edge or standoff displacement `<=0.25 mm`; no new gap, board flex set, cracked/stripped boss, loose standoff, or witness-mark rotation beyond `10°`. |
| Backplane PCB / backplane spine / header mating | Displacement or seating-gap increase `<=0.25 mm`; no partial unseat, bent pin, intermittent continuity, new short/open, or rail/testpoint failure. |
| PDM servo connector and other connectors/harnesses | Connector seating-gap increase or relative movement `<=0.25 mm`; latch/friction retention remains engaged; no polarity/orientation shift, bent pin, intermittent continuity, insulation damage, or harness strain-relief failure. |
| Stack screws / top-module / cap / parachute context | No new visible gap over `0.25 mm`; no screw witness-mark rotation beyond `10°`; no new interference with parachute/cap/servo clearance. |

If a feature cannot be measured to the above resolution, use before/after witness marks, macro photos, and continuity/functional checks; ambiguous evidence is hold, not pass.

## 5. Existing-test and documentation update list

The updates below are queued for later Markdown/test-definition passes. They were **not** applied by this issue.

| Artifact / activity | Update to apply now in the next Markdown pass | Later / execution notes |
|---|---|---|
| `S&A/MBSE/tests/README.md` | Reclassify S&A as physical-only baseline with no planning-candidate backlog; list the selected dispositions, quantitative criteria, and execution-only prerequisites. | Keep execution/report status pending; do not claim tests passed. |
| `S&A/README.md` | Align high-level S&A requirements with confirmed `122 mm`, conservative mass guard band, PLA material, preserved `0.2 mm` / `15%`, and Fusion 360 pinout authority where useful. | Preserve source requirements and supersession notes if a later authority selects stricter criteria. |
| `SAA-VV-CE-001` | Add the physical-scope non-issue rationale: baseline S&A CEs are not required solely for closure; the activity remains the execution-time ownership/cross-reference analysis. | Execute only with complete pin/net/owner matrix and controlled evidence. |
| `SAA-VV-ALLOC-001` | Add the physical-scope non-issue rationale: baseline S&A logical/functions/allocations are not required solely for closure; the activity remains the execution-time ownership/disposition analysis. | Execute only with complete integration-function owner/disposition matrix. |
| `SAA-VV-CON-001` / `SAA-VV-FC-001` | Replace any “height/mass needs confirmation” wording with confirmed `122 mm` and `measured mass + U_M < 350.0 g` unless later authority selects stricter limits. | Execution still needs final article, calibration, uncertainty, raw readings, and configuration evidence. |
| `SAA-VV-CON-003` / `SAA-VV-FC-002` | Add frozen Fusion 360 pinout source of truth and the selected rail-load, voltage-drop, I2C, SPI/UART, endpoint/loading, and DFM/IPC criteria. | Execution still needs board revision, design export, netlist, DRC/ERC, load matrix/default-load approval, calibrated equipment, and raw evidence. |
| `SAA-VV-CON-004` | Add PLA selection, preserved `0.2 mm` / `15%` policy, minimum print-profile evidence, torque/cycle criteria, and proof-load criteria. | Execution still needs material lot, print profile, exact screw type, torque release/coupon data, proof fixture limits, and deviations/waivers. |
| `SAA-VV-CON-005` and affected PL/FC docs | Add the movement/witness-mark thresholds for battery, PCBs/standoffs, backplane/header mating, connectors, stack screws/top-module/cap/parachute context. Affected context includes `SAA-VV-PL-001`, `SAA-VV-FC-002`, `SAA-VV-FC-003`, and post-impact checks in `SAA-VV-CON-001`. | Retain hold/fail for cracks, rattles, unseats, rail/interface failures, ambiguous evidence, or unapproved tightening/reseating. |
| PM&SE CON-003 register and PM&SE assessment integration | Fold this closure record into the blocker register and assessment language: closed definition decisions versus pending Markdown edits, optional D2/source follow-up, and execution evidence. | Do not overclaim finished CanSat or executed subsystem status. |
| `SAA-BLK-003` pending test-definition edit | Later edit `SAA-VV-CON-001`, `SAA-VV-CON-005`, and affected system-environmental planning to list the approved tailored environmental screen levels, surfaces, orientations/axes, durations/events, limitations, and success criteria. | Explicitly not applied in this pass. Execution remains pending until the approved screen is controlled and evidenced. |

## 6. Follow-on D2/source-model and regenerated-PNG list

No `.d2` or `.png` work is required or performed by this issue.

Optional future source-model updates are limited to project preference and are **not** required to close `SAA-BLK-001`/`002` at definition-decision level:

1. If the project wants explicit baseline S&A component exchanges, add source-model CEs for the `5 V` rail, `3.3 V` rail, ADS/AMS/OBCC/PDS header pin interfaces, testpoints, SPI/I2C/UART fast lines, PDM servo connector path, and any extra implemented backplane nets. Regenerate PNGs only after reviewed D2/source edits.
2. If the project wants explicit baseline S&A logical/functions/allocations, add LC/F/allocation views for envelope/mass control, module retention, `44 mm × 44 mm` PCB accommodation, backplane location/mating, testpoint access, physical fast-line routing constraints, ESS battery retention, PDM servo connector/harness retention, top-module/cap/parachute clearance, and environmental screening. Regenerate PNGs only after reviewed D2/source edits.
3. Update verification D2/test-definition views later, if desired, to reflect confirmed height/mass, frozen Fusion 360 pinout, selected backplane quantitative criteria, PLA/print/screw/proof criteria, environmental-screen approval, and movement thresholds.
4. Regenerate any future PNGs only from reviewed D2/source changes; do not edit generated PNGs manually.
5. System-level D2/source work for `SYS-ENVIRONMENTAL-REGRESSION` and final readiness closure remains separate PM&SE/system work.

## 7. Residual execution-only prerequisites

The following are prerequisites for later execution/reporting and are not evidence of execution in this record.

| Area | Required before execution credit |
|---|---|
| Article/configuration identity | Exact article IDs, version/gate, build/configuration record, as-flown hardware installed, board IDs, printed part IDs, battery/PCBs/backplane/connectors/top-module/cap/parachute/servo state, and any ballast or surrogate rationale. |
| Fusion 360 / backplane design control | Released Fusion 360 design revision, exported pinout/interface evidence, controlled `S&A/Pin Interface_page-0001.jpg` or successor, netlist, board revision, stackup/drawing, PDM servo endpoint evidence, DRC/ERC/DFM reports and dispositions. |
| Electrical load and signal prerequisites | Released PDS/system load matrix or explicit approval of the default S&A backplane screen; current limits; safe-load/no-load state; I2C mode/pullups/capacitance/rise-time budget; SPI/UART endpoint/loading review; rail voltage-drop/thermal limits. |
| Equipment and calibration | Calibration/status for calipers, height gauge, can/envelope gauge, scale, DMM/DAQ, continuity/isolation tester, current-limited supply, oscilloscope/logic analyzer/capacitance meter, torque tool, proof-load/load-cell fixture, accelerometer/event logger, camera, ambient meter, timebase, and analysis scripts. |
| Environmental screen evidence | Controlled tailored screen levels, surfaces, axes/orientations, durations/events, fixture coupling, limitations, abort criteria, safety boundary, event logs, photos/video, pre/post inspections, post-screen backplane/rail/interface checks, and approval/hold rationale. |
| Print and material control | PLA supplier/type/color, material lot if available, printer ID, nozzle, slicer/profile version, G-code/build records, layer height/precision, `15%` fill/infill evidence, walls/perimeters/top-bottom/support settings, build date, orientation, part IDs, and reprint history. |
| Screws, torque, cycles, and proof loads | Exact screw type(s), installed-location map, torque release by screw type or coupon data, torque-tool calibration, cycle/coupon population, proof-load values/adapters, fixture limits, surrogate-mass rationale, and safe limits for electronics, Li-ion cells, and connectors. |
| Movement measurement method | Before/after witness marks, macro-photo method, calipers/feeler/gap gauges or equivalent resolution, uncertainty/guard-band method, board/connector/gap reference points, no-tightening/no-reseating control, continuity/isolation and rail checks after screen. |
| Records and deviations | Deviation/waiver/anomaly records, owner approvals, corrective action and re-run scope, limitations, evidence paths, report IDs, and explicit distinction between strict pass, limited/characterization evidence, hold, fail, or not-run status. |

## 8. Assumptions and limitations

- User-provided definition decisions are treated as the governing authority for this closure record.
- The environmental-screen decision is recorded as approved with a pending edit, but this record does not insert detailed screen values into S&A test-definition files.
- All pass/fail determinations remain future execution/report work; this record only selects definition criteria and follow-up actions.
- No candidate folders, D2 diagrams, PNGs, binaries, source code, or unrelated subsystem files were changed by this issue.
