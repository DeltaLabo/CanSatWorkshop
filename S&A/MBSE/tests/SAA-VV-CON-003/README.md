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

## Verification means and allocated functions

| Actor / equipment | Verification-only functions |
|---|---|
| S&A Test Operator | Select v0.1/v1.0 gate; identify article, board revision and baseline copy; handle UUT; stop execution and record hold on anomaly. |
| PCB / Interface Reviewer | Review CAD, stackup, drawing, pinout, netlist, ERC/DRC and low-capacitance/rise-time evidence; disposition warnings and waivers. |
| QA Witness | Witness equipment/calibration/ambient/ESD setup, no-power/continuity gates, measurements and final pass/fail/hold decision. |
| Calipers / Board Gauge | Measure or gauge v0.1 allocation clearance and v1.0 Backplane PCB length/width with uncertainty. |
| 2 mm 2×6 Header / Pitch Gauge | Verify header pitch, pin count, orientation and visible condition for ADS/AMS/OBCC/PDS headers. |
| Continuity / Isolation Tester | Check 100% released endpoint matrix on every released backplane board before power. |
| DMM / DAQ and current-limited supply | Apply safe current-limited power only after pre-power checks; measure `5.0 ±0.1 V` and `3.3 ±0.1 V` at required testpoints under defined safe-load or controlled no-load condition. |
| Testpoint Probe Set | Verify required rail and critical signal testpoints are present, mapped and reachable without modification, back-driving or adjacent-pin short risk. |
| Oscilloscope / Logic Analyzer / Capacitance Meter | Support low-capacitance SPI/I2C/UART analysis and optional characterization of capacitance/rise-time/probe loading. |
| Released PCB CAD / Netlist / ERC/DRC Evidence | Provide controlled design package, pinout, netlist, drawing, stackup and clean/dispositioned ERC/DRC evidence. |
| Ambient Meter / ESD Workstation | Record temperature/humidity and ESD state before checks; hold if uncontrolled. |
| Evidence Repository | Store report, raw readings, endpoint matrices, photos/video, design evidence, calibration records and anomaly dispositions under `S&A/MBSE/tests/results/SAA-VV-CON-003/`. |

## Procedure definition

### Design review / evidence analysis

1. Select `SAA-v0.1`, `SAA-v1.0`, or both gates and identify the frozen baseline copy used.
2. Collect released PCB CAD, drawings, Gerbers, stackup, BOM, pinout, netlist, ERC/DRC reports, testpoint list and fast-line evidence.
3. For v0.1, confirm the model contains a perpendicular backplane volume and slot/clearance rationale for a `100 mm × 28 mm` two-layer perpendicular PCB allocation.
4. For v1.0, confirm the released design package matches the modeled `100 mm × 28 mm` two-layer Backplane PCB with ADS/AMS/OBCC/PDS `2 mm 2×6` headers and PDM Servo Connector endpoints.
5. Review pinout/netlist consistency, rail/testpoint mapping and low-capacitance SPI/I2C/UART rationale.
6. Review ERC/DRC outputs. Pass requires clean reports or approved disposition for every warning/error.
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
3. With supply outputs off, set `5 V` and `3.3 V` voltage/current limits and record the campaign safe-load value or controlled no-load rationale.
4. Before power, perform 100% continuity/isolation against the released endpoint matrix for every released board.
5. Inhibit power and hold execution for any short, open, swapped endpoint, unknown net or probe-risk anomaly.
6. Enable current-limited power only after pre-power checks pass.
7. Measure `5.0 ±0.1 V` and `3.3 ±0.1 V` at all required rail testpoints under the defined load/no-load condition.
8. Verify rail and critical signal testpoint reachability without article modification, back-driving or adjacent-pin short risk.
9. Record raw readings, endpoint matrix, photos/video and witness decision.

### Low-capacitance SPI/I2C/UART analysis

1. Identify every released SPI, I2C and UART fast-line net on the Backplane PCB and all connected headers/testpoints.
2. Identify the selected I2C mode, pull-ups, rail level, bus members and timing requirement.
3. Build the capacitance/loading budget, including PCB traces, headers, module inputs, pull-ups, pads, required testpoints and intended probe loading.
4. Check I2C total capacitance and rise-time against the released selected-mode limit. If no limit is released, hold until a limit is selected from SAA-R4/UM10204 or a stricter design authority.
5. Check SPI/UART topology, loading, edge-rate margin and any DRC/ERC/SI warnings.
6. Use optional capacitance/rise-time measurement only as characterization unless a separate approved statistical plan is issued.
7. Record calculations, plots, warning dispositions, anomalies and acceptance decision.

## Pass/fail constraints

Pass only if all applicable constraints below are satisfied:

- **v0.1 allocation readiness:** the Perpendicular Backplane Volume exists in the modeled Type 1 stack context; the perpendicular slot and top-module clearance are not blocked; the allocation is bounded for a future `100 mm × 28 mm` two-layer Backplane PCB. Missing allocation, blocked slot, unknown clearance or unbounded keepout is hold/fail.
- **v1.0 PCB geometry and stackup:** measured Backplane PCB dimensions match `100 mm × 28 mm` within the released drawing tolerance and measurement uncertainty; released evidence shows a two-layer stackup. Wrong size, wrong layer count, unapproved rework or missing evidence is hold/fail.
- **Headers and pin interface:** ADS/AMS/OBCC/PDS headers are `2 mm 2×6` with correct pitch, pin count, placement, orientation and undamaged condition; PDM Servo Connector endpoints match the released pinout/netlist. Wrong pitch, swapped orientation/pinout, bent pin, damaged connector, unknown endpoint or unowned extra net is hold/fail.
- **ERC/DRC/netlist:** ERC and DRC reports are clean or every warning/error has approved disposition; released pinout/netlist/testpoint matrices are controlled and match the model. Any undispositioned ERC/DRC finding or missing matrix is hold/fail.
- **Continuity/isolation:** 100% continuity/isolation is performed on every released backplane board before power. Any short, open, swapped endpoint, unknown net or probe-risk anomaly is hold/fail until corrected and re-run.
- **Rails:** with current limits set and safe load applied or controlled no-load documented, all required `5 V` testpoint readings satisfy `5.0 ±0.1 V` and all required `3.3 V` readings satisfy `3.3 ±0.1 V`. Overcurrent, rail drop, out-of-tolerance reading, missing load/no-load state or missing raw data is hold/fail.
- **Testpoints:** required rail and critical signal testpoints are present, labeled/mapped, reachable and safely probeable without article modification, back-driving, unstable contact or adjacent-pin short risk. Missing or inaccessible testpoint is hold/fail.
- **Low-capacitance fast lines:** every SPI/I2C/UART fast-line net is included in the capacitance/loading/rise-time rationale; I2C bus capacitance/rise-time is inside the selected released mode limit; SPI/UART loading/topology margins are accepted; testpoints/probes do not invalidate the budget. Excessive capacitance/rise-time, missing mode limit, unowned fast-line net or undispositioned SI warning is hold/fail.
- **Evidence control:** baseline copy, article/board ID, design-evidence revision, calibration state, ambient/ESD record, raw readings, endpoint matrix, measurements, photos/video, witness review and anomaly/waiver/rework dispositions are complete. Missing evidence or open anomaly is hold/fail.

## Viewpoints

- **Statistical significance:** The activity uses a 100% census of the released design evidence: DRC/ERC/netlist/pinout/testpoint review for the relevant gate and 100% continuity/isolation on every released backplane board. Rail readings and dimensional checks are controlled article-level acceptance measurements with uncertainty/calibration records. Optional capacitance/rise-time measurements are characterization unless a separate approved statistical plan exists. This activity makes no population reliability claim.
- **Fault hardening:** The model explicitly prevents false pass from wrong header pitch, swapped pinout, missing or unreachable testpoint, unowned net, PDM servo miswire, rail short/open/drop, overcurrent, excessive I2C capacitance or rise-time, SPI/UART loading escape, undispositioned ERC/DRC warning, uncalibrated tools, uncontrolled ambient/ESD state, ambiguous photos, missing raw data or evidence-control escape.

## Required report content

The execution report in `S&A/MBSE/tests/results/SAA-VV-CON-003/` should reference this model definition and record execution-specific information:

- model definition revision and baseline copy used;
- article identifier, board ID/revision, build/configuration record and gate (`v0.1`, `v1.0` or both);
- operator, reviewer, witness, equipment IDs, calibration records, ambient/ESD record and safe-load/no-load state;
- released CAD/drawing/stackup/pinout/netlist/testpoint/ERC/DRC evidence revision;
- v0.1 allocation-readiness assessment and any slot/clearance measurements or rationale;
- v1.0 board outline measurements, uncertainty values, layer-count evidence and header/pitch/orientation inspection evidence;
- completed continuity/isolation matrix for every released board;
- raw `5 V` and `3.3 V` readings, timestamps, current limits and load/no-load condition;
- testpoint presence/reachability observations and photos/video;
- SPI/I2C/UART fast-line capacitance/rise-time/loading worksheet and optional measurement records;
- pass/fail/hold rationale by gate;
- deviations, anomalies, waivers, rework, re-analysis and re-run evidence.

## Assumptions and blockers

- The baseline S&A views contain only physical architecture; this folder adds verification-only PV2, PV3 and functional-chain definitions rather than editing baseline source views.
- `v0.1` is an incremental allocation/design readiness gate and does not close built-board rail, continuity or signal-integrity acceptance by itself.
- Exact pinout/netlist/testpoint lists, drawing tolerances, board revision, safe-load value and selected I2C mode are assumed to be released before execution. If absent, the report records a hold rather than a pass.
- The low-capacitance criterion is closed by released design rationale against the selected bus-mode limit; optional measurements are characterization unless an approved statistical plan is issued.
- The gate may be held rather than failed when a discrepancy is correctable by approved rework, model/evidence update, or accepted dependency before flight-readiness closure.
