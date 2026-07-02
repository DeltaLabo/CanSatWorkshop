# SAA-VV-CON-003 — Backplane allowance / PCB interface constraint verification

Model-defined constraint-derived verification activity for the S&A `v0.1` transition-readiness baseline and `v1.0` flight-readiness/final-acceptance baseline.

- **IADT method:** Inspection / Analysis / Testing
- **IVV source category:** Constraint
- **SSIV / development versions:** `SAA-v0.1` backplane allocation/design readiness and `SAA-v1.0` built Backplane PCB flight readiness.
- **Definition folder:** `S&A/MBSE/tests/SAA-VV-CON-003/`
- **Expected report/evidence folder:** `S&A/MBSE/tests/results/SAA-VV-CON-003/`
- **Primary traceability targets:** modeled Backplane allowance / Backplane PCB constraints, `SAA-UC-BackplaneIntegration`, and `SAA-FE-BackplaneMisMate`.
- **References:** IVV (`PM&SE/IVV.md`), SAA-R4 and SAA-R5 as indexed in `S&A/MBSE/tests/references/README.md`.

## Model views

| View | D2 | PNG | Purpose |
|---|---|---|---|
| Baseline copy v0.1 | `baseline/SAA_v0.1_view1_physical.d2` | `baseline/SAA_v0.1_view1_physical.png` | Frozen source context for the v0.1 structural/module/backplane-volume readiness gate. |
| Baseline copy v1.0 | `baseline/SAA_v1.0_view1_physical.d2` | `baseline/SAA_v1.0_view1_physical.png` | Frozen source context for the v1.0 built Backplane PCB, headers, PDM servo connector, rail/testpoint/fast-line constraints. |
| Physical backplane constraint testbench | `SAA-VV-CON-003_physical_backplane_constraint_testbench.d2` | `SAA-VV-CON-003_physical_backplane_constraint_testbench.png` | PV1 testbench with v0.1 Backplane Volume and v1.0 Backplane PCB UUTs, calipers/board gauge, header/pitch gauge, DMM/DAQ, continuity/isolation tester, DRC/ERC/netlist evidence, testpoint probes, operator, reviewer, witness, ambient/ESD controls and evidence repository. |
| Logical pinout/netlist/rail/signal evidence | `SAA-VV-CON-003_logical_pinout_netlist_rail_signal_evidence.d2` | `SAA-VV-CON-003_logical_pinout_netlist_rail_signal_evidence.png` | Verification-only PV2 CEs for version selection, allocation/geometry/stackup evidence, header/pinout matrices, ERC/DRC disposition, continuity/isolation, rails, testpoints, low-capacitance SPI/I2C/UART evidence and acceptance gate. |
| Functional allocation / procedure | `SAA-VV-CON-003_functional_allocation_procedure.d2` | `SAA-VV-CON-003_functional_allocation_procedure.png` | Verification-only PV3 allocation of operator, reviewer, witness, equipment, UUT and repository functions used to inspect, analyze and test the backplane constraints. |
| Design review / evidence analysis chain | `SAA-VV-CON-003_design_review_chain.d2` | `SAA-VV-CON-003_design_review_chain.png` | Functional chain for v0.1 allocation readiness and v1.0 released design-package review, including pinout/netlist and ERC/DRC evidence. |
| Physical / dimensional inspection chain | `SAA-VV-CON-003_physical_dimensional_inspection_chain.d2` | `SAA-VV-CON-003_physical_dimensional_inspection_chain.png` | Functional chain for v0.1 backplane-volume allowance and v1.0 board dimensions, stackup, header pitch/orientation and testpoint presence/reachability inspection. |
| Safe rail / testpoint check chain | `SAA-VV-CON-003_safe_rail_testpoint_check_chain.d2` | `SAA-VV-CON-003_safe_rail_testpoint_check_chain.png` | Functional chain for pre-power continuity/isolation, current-limited rail application, 5 V / 3.3 V measurements and testpoint reachability checks on every released board. |
| Low-capacitance SPI/I2C/UART analysis chain | `SAA-VV-CON-003_low_capacitance_fast_line_analysis_chain.d2` | `SAA-VV-CON-003_low_capacitance_fast_line_analysis_chain.png` | Functional chain for 100% fast-line census, capacitance/rise-time budget, DRC/ERC/SI warning disposition and optional characterization measurement. |

The logical components, component exchanges, functions, physical links to test equipment, verification records and functional chains in this folder are **verification-only** and do not modify the S&A baseline architecture.

## Items under verification

### `v0.1` transition-readiness article

The v0.1 UUT is the structural/module readiness model defined by `S&A/MBSE/v0.1/SAA_v0.1_view1_physical.d2`, specifically the Standard Carrier Module Stack, Perpendicular Backplane Volume, perpendicular backplane slot, top-module clearance and the Backplane allowance constraint. Closure at v0.1 is limited to design/allocation readiness: the backplane volume must be present, bounded, and compatible with a future `100 mm × 28 mm` two-layer perpendicular Backplane PCB allocation.

### `v1.0` flight-readiness article

The v1.0 UUT is the integrated Backplane PCB acceptance configuration from `S&A/MBSE/v1.0/SAA_v1.0_view1_physical.d2`, including the Backplane PCB `100 mm × 28 mm` two-layer stackup, ADS/AMS/OBCC/PDS `2 mm 2×6` headers, PDM Servo Connector, rail and signal testpoints, SPI/I2C/UART fast-line routes, Backplane Spine and the mating context with ADS/AMS/OBCC/PDS PCBs, Standard Carrier Module Stack and Parachute / Top Module.

## Closure-record backplane criteria (`SAA-BLK-005`)

These criteria select definition values for later execution/reporting; they do not state that any board has passed.

- **Pinout source of truth:** the released Fusion 360 backplane design package and exported pin-interface evidence are the frozen pinout source of truth. Strict execution credit requires a 100% match between the released design, installed headers/connectors, netlist, `S&A/Pin Interface_page-0001.jpg` or successor controlled pin-interface evidence, and the inspected article. No pin swaps, undocumented alternate pins, or unowned extra nets are allowed.
- **Connector/header geometry:** preserve the existing `2 mm 2×6` header requirement and TMM-106-01-L-D-RA SAMTEC family unless the released Fusion 360 package supersedes it. Each ADS/AMS/OBCC/PDS header and the PDM Servo Connector require endpoint, orientation, pin-1, and polarity evidence.
- **Rail-load acceptance:** perform no-load continuity/isolation before power. Strict loaded credit uses the released PDS/system load matrix. If no matrix is released at execution time, use the default S&A backplane screen of `1.0 A` aggregate per rail, distributed across populated endpoints or applied at the worst-case/farthest endpoint, with current limiting, thermal monitoring, and all measured endpoints still in `5.0 ±0.1 V` / `3.3 ±0.1 V` tolerance. Lower loads or no-load rail checks are characterization/limited unless approved by the review board.
- **Voltage-drop and thermal guard:** backplane distribution drop shall not cause any required endpoint to leave rail tolerance. Record source voltage, endpoint voltage, current, duration, ambient, and board temperature; visible heating damage, odor, discoloration, or temperature rise beyond the campaign thermal limit is hold/fail.
- **I2C baseline:** default strict S&A backplane I2C mode is Standard-mode `100 kHz` at `3.3 V`. Total bus capacitance, including PCB trace, headers, module inputs, pullups, pads, and required testpoints, shall be `<=400 pF`; 30%-70% rise time shall be `<=1000 ns`. If a later interface authority selects Fast-mode `400 kHz`, use `<=300 ns` rise time while keeping `<=400 pF` bus capacitance unless superseded.
- **SPI/UART fast-line evidence:** all SPI and UART nets require 100% endpoint, direction, voltage-level, loading, and topology review. No swapped TX/RX/MOSI/MISO/clock/chip-select lines, unowned stubs, or unowned probe points are allowed.
- **DFM / IPC disposition:** `S&A/PCB_General_Rules.md` is the binding local workshop/Carvera-Air DFM rule set. If an IPC class is needed for external comparison, treat the workshop CanSat as IPC Class 2 intent unless a later authority selects otherwise. All DRC/ERC/DFM warnings or deviations require explicit disposition before strict credit.

## Verification means and allocated functions

| Actor / equipment | Verification-only functions |
|---|---|
| S&A Test Operator | Select v0.1/v1.0 gate; identify article, board revision and baseline copy; handle UUT; stop execution and record hold on anomaly. |
| PCB / Interface Reviewer | Review CAD, stackup, drawing, pinout, netlist, ERC/DRC and low-capacitance/rise-time evidence; disposition warnings and waivers. |
| QA Witness | Witness equipment/calibration/ambient/ESD setup, no-power/continuity gates, measurements and final pass/fail/hold decision. |
| Calipers / Board Gauge | Measure or gauge v0.1 allocation clearance and v1.0 Backplane PCB length/width with uncertainty. |
| 2 mm 2×6 Header / Pitch Gauge | Verify header pitch, pin count, orientation and visible condition for ADS/AMS/OBCC/PDS headers. |
| Continuity / Isolation Tester | Check 100% released endpoint matrix on every released backplane board before power. |
| DMM / DAQ and current-limited supply | Apply safe current-limited power only after pre-power checks; measure `5.0 ±0.1 V` and `3.3 ±0.1 V` at required endpoints/testpoints under the released PDS/system load matrix or default `1.0 A` aggregate-per-rail S&A screen for strict loaded credit. |
| Testpoint Probe Set | Verify required rail and critical signal testpoints are present, mapped and reachable without modification, back-driving or adjacent-pin short risk. |
| Oscilloscope / Logic Analyzer / Capacitance Meter | Support low-capacitance SPI/I2C/UART analysis and optional characterization of capacitance/rise-time/probe loading. |
| Released Fusion 360 PCB CAD / Netlist / ERC/DRC Evidence | Provide the controlled Fusion 360 design package, exported pin-interface evidence, pinout, netlist, drawing, stackup and clean/dispositioned ERC/DRC/DFM evidence. |
| Ambient Meter / ESD Workstation | Record temperature/humidity and ESD state before checks; hold if uncontrolled. |
| Evidence Repository | Store report, raw readings, endpoint matrices, photos/video, design evidence, calibration records and anomaly dispositions under `S&A/MBSE/tests/results/SAA-VV-CON-003/`. |

## Procedure definition

### Design review / evidence analysis

1. Select `SAA-v0.1`, `SAA-v1.0`, or both gates and identify the frozen baseline copy used.
2. Collect the released Fusion 360 backplane design package, exported pin-interface evidence, drawings, Gerbers, stackup, BOM, pinout, netlist, ERC/DRC/DFM reports, testpoint list and fast-line evidence.
3. For v0.1, confirm the model contains a perpendicular backplane volume and slot/clearance rationale for a `100 mm × 28 mm` two-layer perpendicular PCB allocation.
4. For v1.0, confirm the released Fusion 360 design package and exported pin-interface evidence match the modeled `100 mm × 28 mm` two-layer Backplane PCB with ADS/AMS/OBCC/PDS `2 mm 2×6` headers and PDM Servo Connector endpoints.
5. Review the strict 100% pinout/netlist/header/connector/testpoint match between released design, installed headers/connectors, netlist, controlled pin-interface evidence, and inspected article; any undocumented alternate pin or unowned extra net is hold/fail until dispositioned.
6. Review ERC/DRC/DFM outputs against `S&A/PCB_General_Rules.md` as the binding workshop/Carvera-Air rule set. Pass requires clean reports or approved disposition for every warning/error/deviation; IPC Class 2 is only an external-comparison intent unless later authority selects otherwise.
7. Record anomalies, waivers, rework, model-update needs and required re-review before applying the design gate.

### Physical / dimensional inspection

1. Identify the inspected article, board revision and baseline copy; record ambient, ESD and calibration status.
2. Inspect v0.1 Backplane Volume, perpendicular slot and top-module clearance; gauge or measure that a `100 mm × 28 mm` allocation is bounded and not blocked.
3. Measure v1.0 Backplane PCB length/width with uncertainty; compare to the released drawing and modeled `100 mm × 28 mm` constraint.
4. Inspect evidence that the board is two-layer.
5. Verify ADS/AMS/OBCC/PDS headers are `2 mm 2×6`, correctly oriented, correctly placed and undamaged; verify PDM Servo Connector placement and endpoint marking.
6. Verify required rail and critical signal testpoints are present, labeled/mapped and reachable without article modification or adjacent-pin short risk.
7. Capture photos/video and raw measurements, then apply the physical/dimensional gate.

### Safe rail / testpoint check

1. Identify the v1.0 Backplane PCB board ID/revision, endpoint matrix, rail/testpoint checklist and equipment calibration.
2. Record ambient temperature/humidity, ESD state, probe condition and supply/DMM/continuity-tester status.
3. With supply outputs off, set `5 V` and `3.3 V` voltage/current limits and record the released PDS/system load matrix. If no matrix is released, configure the default S&A backplane screen of `1.0 A` aggregate per rail distributed across populated endpoints or applied at the worst-case/farthest endpoint, with current limiting and thermal monitoring. Record any lower-load or no-load condition as characterization/limited unless approved for strict credit.
4. Before power, perform 100% continuity/isolation against the released endpoint matrix for every released board.
5. Inhibit power and hold execution for any short, open, swapped endpoint, unknown net, undocumented alternate pin, unowned extra net or probe-risk anomaly.
6. Enable current-limited power only after pre-power checks pass.
7. Measure source voltage, endpoint voltage, current, duration, ambient, and board temperature; all required endpoints/testpoints must remain within `5.0 ±0.1 V` / `3.3 ±0.1 V` rail tolerance under the released matrix or default-load screen for strict credit.
8. Verify rail and critical signal testpoint reachability without article modification, back-driving or adjacent-pin short risk.
9. Record raw readings, endpoint matrix, photos/video and witness decision.

### Low-capacitance SPI/I2C/UART analysis

1. Identify every released SPI, I2C and UART fast-line net on the Backplane PCB and all connected headers/testpoints.
2. Identify the selected I2C mode, pull-ups, rail level, bus members and timing requirement. Default strict credit is Standard-mode `100 kHz` at `3.3 V` unless a later interface authority selects Fast-mode `400 kHz` or another controlled standard.
3. Build the capacitance/loading budget, including PCB traces, headers, module inputs, pull-ups, pads, required testpoints and intended probe loading.
4. Check I2C total capacitance `<=400 pF` and 30%-70% rise time `<=1000 ns` for Standard-mode. If Fast-mode `400 kHz` is later selected, use `<=300 ns` rise time while keeping `<=400 pF` capacitance unless superseded.
5. Check SPI/UART endpoint, direction, voltage-level, loading, topology, edge-rate margin and any DRC/ERC/SI warnings; swapped TX/RX/MOSI/MISO/clock/chip-select lines, unowned stubs or unowned probe points are hold/fail until dispositioned.
6. Use optional capacitance/rise-time measurement only as characterization unless a separate approved statistical plan is issued.
7. Record calculations, plots, warning dispositions, anomalies and acceptance decision.

## Pass/fail constraints

Pass only if all applicable constraints below are satisfied:

- **v0.1 allocation readiness:** the Perpendicular Backplane Volume exists in the modeled Type 1 stack context; the perpendicular slot and top-module clearance are not blocked; the allocation is bounded for a future `100 mm × 28 mm` two-layer Backplane PCB. Missing allocation, blocked slot, unknown clearance or unbounded keepout is hold/fail.
- **v1.0 PCB geometry and stackup:** measured Backplane PCB dimensions match `100 mm × 28 mm` within the released drawing tolerance and measurement uncertainty; released evidence shows a two-layer stackup. Wrong size, wrong layer count, unapproved rework or missing evidence is hold/fail.
- **Headers and pin interface:** ADS/AMS/OBCC/PDS headers are `2 mm 2×6` with correct pitch, pin count, placement, orientation and undamaged condition; PDM Servo Connector endpoints match the released pinout/netlist. Strict credit requires a 100% match between the released Fusion 360 design package, installed headers/connectors, netlist, controlled pin-interface evidence and inspected article. Wrong pitch, swapped orientation/pinout, undocumented alternate pin, bent pin, damaged connector, unknown endpoint or unowned extra net is hold/fail.
- **ERC/DRC/netlist/DFM:** ERC, DRC and DFM reports are clean or every warning/error/deviation has approved disposition; released pinout/netlist/testpoint matrices are controlled and match the model. `S&A/PCB_General_Rules.md` is the binding local workshop/Carvera-Air DFM rule set; IPC Class 2 is only external-comparison intent unless later authority selects otherwise. Any undispositioned ERC/DRC/DFM finding or missing matrix is hold/fail.
- **Continuity/isolation:** 100% continuity/isolation is performed on every released backplane board before power. Any short, open, swapped endpoint, unknown net, undocumented alternate pin, unowned extra net or probe-risk anomaly is hold/fail until corrected and re-run.
- **Rails:** with current limits set, strict loaded rail credit uses the released PDS/system load matrix. If no matrix is released, use the default S&A backplane screen of `1.0 A` aggregate per rail distributed across populated endpoints or applied at the worst-case/farthest endpoint, with current limiting, thermal monitoring, and all required endpoints/testpoints satisfying `5.0 ±0.1 V` / `3.3 ±0.1 V`. Lower loads or no-load rail checks are characterization/limited unless approved by the review board. Overcurrent, rail drop, out-of-tolerance endpoint, missing load state, visible heating damage, odor, discoloration, temperature rise beyond the campaign thermal limit or missing raw data is hold/fail.
- **Testpoints:** required rail and critical signal testpoints are present, labeled/mapped, reachable and safely probeable without article modification, back-driving, unstable contact or adjacent-pin short risk. Missing or inaccessible testpoint is hold/fail.
- **Low-capacitance fast lines:** every SPI/I2C/UART fast-line net is included in the capacitance/loading/rise-time rationale. Default strict I2C is Standard-mode `100 kHz` at `3.3 V`, total bus capacitance `<=400 pF`, and 30%-70% rise time `<=1000 ns`; if later Fast-mode `400 kHz` is selected, rise time is `<=300 ns` and capacitance remains `<=400 pF` unless superseded. SPI/UART endpoint, direction, voltage-level, loading and topology margins are accepted; testpoints/probes do not invalidate the budget. Excessive capacitance/rise-time, swapped fast-line direction, missing mode limit, unowned fast-line net or undispositioned SI warning is hold/fail.
- **Evidence control:** baseline copy, article/board ID, design-evidence revision, calibration state, ambient/ESD record, raw readings, endpoint matrix, measurements, photos/video, witness review and anomaly/waiver/rework dispositions are complete. Missing evidence or open anomaly is hold/fail.

## Viewpoints

- **Statistical significance:** The activity uses a 100% census of the released design evidence: DRC/ERC/netlist/pinout/testpoint review for the relevant gate and 100% continuity/isolation on every released backplane board. Rail readings and dimensional checks are controlled article-level acceptance measurements with uncertainty/calibration records. Optional capacitance/rise-time measurements are characterization unless a separate approved statistical plan exists. This activity makes no population reliability claim.
- **Fault hardening:** The model explicitly prevents false pass from wrong header pitch, swapped pinout, missing or unreachable testpoint, unowned net, PDM servo miswire, rail short/open/drop, overcurrent, excessive I2C capacitance or rise-time, SPI/UART loading escape, undispositioned ERC/DRC warning, uncalibrated tools, uncontrolled ambient/ESD state, ambiguous photos, missing raw data or evidence-control escape.

## Required report content

The execution report in `S&A/MBSE/tests/results/SAA-VV-CON-003/` should reference this model definition and record execution-specific information:

- model definition revision and baseline copy used;
- article identifier, board ID/revision, build/configuration record and gate (`v0.1`, `v1.0` or both);
- operator, reviewer, witness, equipment IDs, calibration records, ambient/ESD record and load-state basis (released load matrix, default `1.0 A` screen, or limited/characterization no-load);
- released Fusion 360 design package/exported pin-interface evidence revision, CAD/drawing/stackup/pinout/netlist/testpoint/ERC/DRC/DFM evidence revision;
- v0.1 allocation-readiness assessment and any slot/clearance measurements or rationale;
- v1.0 board outline measurements, uncertainty values, layer-count evidence and header/pitch/orientation inspection evidence;
- completed continuity/isolation matrix for every released board;
- raw `5 V` and `3.3 V` source/endpoint readings, timestamps, current limits, load matrix or default `1.0 A` aggregate-per-rail screen configuration, thermal-monitoring records, and any limited/characterization no-load condition;
- testpoint presence/reachability observations and photos/video;
- SPI/I2C/UART endpoint/direction/voltage/loading worksheet, I2C capacitance/rise-time worksheet against the selected mode, and optional measurement records;
- pass/fail/hold rationale by gate;
- deviations, anomalies, waivers, rework, re-analysis and re-run evidence.

## Assumptions and blockers

- The baseline S&A views contain only physical architecture; this folder adds verification-only PV2, PV3 and functional-chain definitions rather than editing baseline source views.
- `v0.1` is an incremental allocation/design readiness gate and does not close built-board rail, continuity or signal-integrity acceptance by itself.
- Released Fusion 360 design/exported pin-interface evidence, exact pinout/netlist/testpoint lists, drawing tolerances and board revision are required before strict execution credit; if absent, the report records a hold rather than a pass. If the PDS/system load matrix is absent, use the default `1.0 A` aggregate-per-rail S&A screen above for strict loaded credit. If no later I2C mode is selected, use the Standard-mode `100 kHz` / `3.3 V` / `<=400 pF` / `<=1000 ns` defaults above.
- The low-capacitance criterion is closed by released design rationale against the selected bus-mode limit; optional measurements are characterization unless an approved statistical plan is issued.
- The gate may be held rather than failed when a discrepancy is correctable by approved rework, model/evidence update, or accepted dependency before flight-readiness closure.
