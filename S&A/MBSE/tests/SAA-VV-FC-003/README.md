# SAA-VV-FC-003 — Parachute/top-module clearance and deployment-interference scenario

Model-defined verification activity for the S&A `v1.0` flight-readiness baseline. This activity turns the candidate parachute/top-module clearance scenario into Capella-style verification-only views for report-by-reference.

- **IADT method:** Demonstration / Testing
- **IVV source category:** Functional chain / scenario
- **SSIV / development version:** `SAA-v1.0` flight readiness / final acceptance. `v0.1` is copied as incremental structural context only; the executable scenario is defined for the integrated `v1.0` article.
- **Definition folder:** `S&A/MBSE/tests/SAA-VV-FC-003/`
- **Expected report/evidence folder:** `S&A/MBSE/tests/results/SAA-VV-FC-003/`
- **Primary traceability targets:** `SAA-UC-ParachuteClearance`, `SAA-FE-StructuralLoosening`, `SAA-FE-LandingDamage`, v1.0 top-module/backplane physical links, and modeled landing-impact / assembly constraints.
- **References:** IVV (`PM&SE/IVV.md`) and SAA-R1 through SAA-R5 as indexed in `S&A/MBSE/tests/references/README.md`.

## Model views

| View | D2 | PNG | Purpose |
|---|---|---|---|
| Baseline copy v0.1 | `baseline/SAA_v0.1_view1_physical.d2` | `baseline/SAA_v0.1_view1_physical.png` | Frozen incremental structural/module/backplane-volume context. |
| Baseline copy v1.0 | `baseline/SAA_v1.0_view1_physical.d2` | `baseline/SAA_v1.0_view1_physical.png` | Frozen source context for the v1.0 parachute/top-module, cap, parachute, servo, backplane and PDM servo connector endpoints. |
| v1.0 physical testbench | `SAA-VV-FC-003_v1.0_physical_testbench.d2` | `SAA-VV-FC-003_v1.0_physical_testbench.png` | PV1 testbench with integrated top-module UUT, parachute pack/reset fixture, servo command/manual actuation interface, high-speed/video camera, clearance gauges, pre/post PC-PL inspection kit, operator/witness, environmental-screen record, ambient meter and evidence repository. |
| Logical interface exchange | `SAA-VV-FC-003_logical_interface_exchange.d2` | `SAA-VV-FC-003_logical_interface_exchange.png` | Verification-only PV2 exchanges for command, pack/reset state, motion observation, clearance, extraction, retention, trial count, anomaly and evidence records. |
| Functional allocation / procedure | `SAA-VV-FC-003_functional_allocation_procedure.d2` | `SAA-VV-FC-003_functional_allocation_procedure.png` | Verification-only PV3 allocation of pack, command/open cap/servo, observe extraction, inspect clearance/retention, reset, count trials and log evidence. |
| Nominal deployment / clearance chain | `SAA-VV-FC-003_nominal_deployment_clearance_chain.d2` | `SAA-VV-FC-003_nominal_deployment_clearance_chain.png` | Main Demonstration / Testing functional chain for nominal deployment, clearance, zero-snag extraction, reset and repeated-trial acceptance. |
| Snag / interference fault-hardening chain | `SAA-VV-FC-003_fault_hardening_snag_interference_chain.d2` | `SAA-VV-FC-003_fault_hardening_snag_interference_chain.png` | Functional chain for cap rub, packed-parachute variability, backplane/PDM-servo-connector interference and post-vibration/drop looseness holds. |

The logical components, component exchanges, functions, physical links to test equipment, rub/snag witness markers, keep-out markers and functional chains in this folder are **verification-only** and do not modify the S&A baseline architecture.

## Item under verification

The UUT is the integrated `v1.0` S&A top-module deployment-clearance configuration within the CanSat Assembly, including:

- Parachute / Top Module (Type 2), Cap, Parachute and Servo;
- Backplane PCB `100 mm × 28 mm`, Backplane Spine and PDM Servo Connector as potential interference/retention endpoints;
- Standard Carrier Module Stack (Type 1), ADS/AMS/OBCC/PDS/ESS Modules, PCBs/standoffs, ESS Battery Pack, stack screws and top-module attachment as pre/post movement checks;
- v1.0 physical links for stack screws, perpendicular fixture/header mating, backplane fixture + servo connector, PCB standoffs/screws and battery fixture.

## Verification means and allocated functions

| Actor / equipment | Verification-only functions |
|---|---|
| S&A Test Operator | Identify article/baseline; establish safety zone; pack parachute with fixture; command deployment or manual actuation; reset/service cap, servo and parachute; record anomalies. |
| Safety / QA Witness | Witness setup, no-hand-assist deployment, pre/post screen status, trial count and pass/fail/hold decision. |
| Parachute Pack / Reset Fixture | Constrain repeatable fold, parachute orientation, cap closed state and reset/serviceability. |
| Servo Command Interface / Manual Actuation Tool | Send open command or apply controlled manual actuation; record actuation mode, timestamp and servo return state. |
| High-speed / Video Camera | Capture cap motion, servo horn/linkage, parachute extraction, snags, rubs and evidence-lighting context. |
| Clearance Gauge / Snag Witness Markers | Check cap/servo path against top-module structure, backplane spine and PDM servo connector keep-outs; reveal rub or snag contact. |
| Pre/Post PC-PL Inspection Kit | Inspect stack screws, top-module attachment, backplane fixture, PDM servo connector, PCB standoffs and battery fixture before/after repetitions or environmental screens. |
| Vibration / Drop Screen Record | Provide condition context when the deployment test is executed after environmental screens. |
| Ambient Thermo-Hygrometer | Record ambient temperature/humidity before repetitions. |
| Evidence Repository | Store controlled report, trial log, video/photos, PC-PL inspection records, ambient data, witness decision and anomaly dispositions under `S&A/MBSE/tests/results/SAA-VV-FC-003/`. |

## Demonstration / testing procedure definition

1. Identify the `v1.0` article, build/configuration record, baseline copy, operator, witness, equipment IDs, calibration/status records and this model definition revision.
2. Establish the safety boundary, no-hand-assist rule, camera/lighting/FOV/frame-rate setup, clearance/rub witness markers, pack/reset fixture setting and evidence repository path.
3. Record ambient temperature/humidity and any referenced pre/post vibration/drop screen condition.
4. Perform pre-test PC/PL checks for stack screws, top-module attachment, backplane fixture, PDM Servo Connector, PCB standoffs/screws, battery fixture and visible module/backplane alignment.
5. Pack the parachute using the defined pack/reset fixture and place the cap/servo in the serviceable closed state.
6. Command the servo/open-cap motion through the servo command interface, or use the controlled manual actuation means if the flight command path is unavailable; keep hands clear and record the method.
7. Capture cap, servo and parachute motion with video; observe whether cap/servo motion clears the structure, backplane spine and PDM servo connector.
8. Confirm the parachute extracts without snagging, hang-up, hand assistance, dragging the UUT or pulling on the backplane/connector/module stack.
9. Perform post-trial PC/PL checks for connector/backplane/module/screw/standoff/battery-fixture movement or looseness.
10. Reset the cap, servo and parachute to the serviceable closed state without unapproved rework; record reset status.
11. Log the trial result, pack condition, command method, video/evidence IDs and any anomaly.
12. Repeat for `10` zero-snag deployments for the workshop screen. Use `29` representative independent zero-snag trials only if the report claims R90/C95 reliability.
13. Execute the fault-hardening chain when cap rub, pack variability, backplane/PDM-servo-connector interference, post-vibration/drop looseness, ambiguous video, forced reset or any movement is suspected.
14. Apply the pass/fail constraints below. If any exception occurs, disposition the anomaly and re-run affected nominal checks before claiming pass.
15. QA witness approves pass/fail/hold and the evidence repository releases the report-by-reference package.

## Pass/fail constraints

Pass only if all of the following are true for the `v1.0` article:

- cap and servo motion clear the top-module structure, standard stack, backplane spine and PDM Servo Connector in every accepted trial;
- parachute extracts without snagging, hang-up, hand assistance, dragging the UUT, or ambiguous video evidence;
- reset/serviceability is preserved after every trial without unapproved rework, permanent deformation or forced closure;
- no connector, backplane, module, top-module attachment, stack screw, PCB standoff, PCB, battery fixture or other modeled physical link/component movement is introduced;
- pre/post PC-PL inspection records are acceptable before and after repeated deployments and after any referenced vibration/drop screen;
- the workshop screen has `10/10` zero-snag deployments, or a reliability claim explicitly has `29/29` representative independent zero-snag trials for R90/C95;
- ambient conditions, camera settings, fixture settings, actuation method, trial log, video/photos, inspection records, witness review and anomaly dispositions are complete;
- every anomaly, waiver, rework or deviation is closed with approved disposition and affected checks have been re-run.

Fail or hold for any cap rub/contact mark judged as interference, insufficient servo travel, no-release, parachute snag/hang-up, hand-assisted extraction, forced reset, backplane or PDM-servo-connector contact, connector/backplane/module/screw/standoff/battery-fixture movement, post-screen looseness, missing/ambiguous evidence, expired/unknown equipment status affecting the result, unresolved anomaly disposition, or unapproved waiver.

## Viewpoints

- **Statistical significance:** This is a repeated deployment screen of the v1.0 article. The workshop acceptance screen is `10` repeated deployments with zero snags and zero disallowed movement. It makes no population reliability claim. Claim R90/C95 only with `29` representative independent zero-snag trials and documented independence/representativeness.
- **Fault hardening:** The model requires explicit screening for cap rub, servo travel margin, packed-parachute variability, backplane spine/PDM Servo Connector interference, post-vibration/drop looseness, false pass from ambiguous video, and evidence-control escape. Any trigger causes hold/disposition/re-run rather than a pass.

## Required report content

The execution report in `S&A/MBSE/tests/results/SAA-VV-FC-003/` should reference this model definition and record only execution-specific information:

- model definition revision and v1.0 baseline copy used;
- inspected article identifier, version and build/configuration record;
- operator, witness, equipment IDs, camera settings, fixture settings, gauge IDs, calibration/status records, safety boundary and ambient record;
- pre/post PC-PL inspection checklist for stack screws, top-module attachment, backplane fixture, PDM Servo Connector, PCB standoffs/screws, battery fixture and module/backplane alignment;
- trial-by-trial pack condition, command/manual actuation method, cap/servo motion result, parachute extraction result, reset/serviceability result and evidence IDs;
- video/photo file paths and any rub/snag witness-marker observations;
- statistical basis used (`10/10` workshop screen or `29/29` R90/C95 claim);
- pass/fail/hold rationale;
- deviations, anomalies, waivers, rework and re-run evidence.

## Assumptions and blockers

- The executable scenario is for `SAA-v1.0`; `v0.1` is retained as copied context because it does not include the cap/parachute/servo/backplane/PDM-servo-connector integration required for this activity.
- The baseline S&A v1.0 source view contains no `[CE]`, `[LC]`, `[F]`, `[FE]` or functional-chain elements; this folder adds verification-only definitions rather than editing the baseline.
- Servo actuation may be by the flight command path or a controlled manual/test interface; the report must state which method was used and whether it is representative for the acceptance claim.
- Environmental screen levels are not defined in this activity; when executed after vibration/drop screens, this activity references the as-executed screen record and performs mandatory pre/post PC-PL checks.
- The gate may be placed on hold rather than failed when a discrepancy is correctable by approved rework, model/evidence update, or accepted dependency before flight-readiness closure.
