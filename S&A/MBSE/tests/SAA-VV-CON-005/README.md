# SAA-VV-CON-005 — Retention under vibration/drop/landing-style loads

Model-defined constraint/component-link verification activity for the S&A `v1.0` flight-readiness/final-acceptance baseline. This activity defines a structural/environmental retention screen with mandatory pre/post inspections for the battery fixture, PCB standoffs/screws, stack screws, backplane fixture, ADS/AMS/OBCC/PDS headers, PDM Servo Connector and related top-module/backplane interfaces.

- **IADT method:** Testing / Inspection
- **IVV source category:** Constraint / component-link
- **SSIV / development version:** `SAA-v1.0` flight readiness / final acceptance. `v0.1` is copied as incremental structural context only; the executable activity is defined for the integrated `v1.0` article.
- **Definition folder:** `S&A/MBSE/tests/SAA-VV-CON-005/`
- **Expected report/evidence folder:** `S&A/MBSE/tests/results/SAA-VV-CON-005/`
- **Primary traceability targets:** modeled landing-impact, envelope/mass, backplane and assembly/printing constraints; `SAA-UC-IntegratedAssembly`; `SAA-UC-BackplaneIntegration`; `SAA-FE-StructuralLoosening`; `SAA-FE-LandingDamage`; `SAA-FE-BackplaneMisMate`; `SAA-FE-EnvelopeNonCompliance`.
- **References:** IVV (`PM&SE/IVV.md`) and SAA-R1 through SAA-R5 as indexed in `S&A/MBSE/tests/references/README.md`.

## Model views

| View | D2 | PNG | Purpose |
|---|---|---|---|
| Baseline copy v0.1 | `baseline/SAA_v0.1_view1_physical.d2` | `baseline/SAA_v0.1_view1_physical.png` | Frozen incremental structural/module/backplane-volume context. |
| Baseline copy v1.0 | `baseline/SAA_v1.0_view1_physical.d2` | `baseline/SAA_v1.0_view1_physical.png` | Frozen source context for the integrated v1.0 article and target retention physical links. |
| Physical retention testbench | `SAA-VV-CON-005_physical_retention_testbench.d2` | `SAA-VV-CON-005_physical_retention_testbench.png` | PV1 testbench with integrated v1.0 UUT, tailored vibration/drop/proof-load fixture, accelerometer/event logger, scale/envelope gauge, camera, inspection kit, backplane checkout tool, operator/witness, safety boundary and evidence repository. |
| Logical evidence interface | `SAA-VV-CON-005_logical_evidence_interface.d2` | `SAA-VV-CON-005_logical_evidence_interface.png` | Verification-only PV2 evidence CEs for baseline selection, target census, pre/post inspections, screen configuration, execution logs, movement matrix, envelope/mass, backplane checks, statistical basis, anomalies and evidence release. |
| Functional allocation / procedure | `SAA-VV-CON-005_functional_allocation_procedure.d2` | `SAA-VV-CON-005_functional_allocation_procedure.png` | Verification-only PV3 allocation of human, fixture, logger, inspection, scale/envelope, backplane checkout, UUT-retention and evidence functions. |
| Retention environmental screen chain | `SAA-VV-CON-005_retention_environmental_screen_chain.d2` | `SAA-VV-CON-005_retention_environmental_screen_chain.png` | Main Testing / Inspection functional chain covering pre-inspection, fixture configuration, execution, monitoring/logging, post-inspection, envelope/mass and backplane rail/interface checks, and disposition. |
| Anomaly disposition chain | `SAA-VV-CON-005_anomaly_disposition_chain.d2` | `SAA-VV-CON-005_anomaly_disposition_chain.png` | Hold/re-run functional chain for detachment, loosening, movement, backplane/rail/interface failure, uncontrolled level, ambiguous evidence or unapproved rework. |

The logical components, component exchanges, functions, physical links to verification means, records and functional chains in this folder are **verification-only** and do not modify the S&A baseline architecture.

## Item under verification

The UUT is the integrated `v1.0` CanSat Assembly defined by `S&A/MBSE/v1.0/SAA_v1.0_view1_physical.d2`, including:

- Standard Carrier Module Stack (Type 1), ADS/AMS/OBCC/PDS/ESS Modules, stack screws and top-module stack attachment;
- ADS/AMS/OBCC/PDS `44 mm × 44 mm` PCBs and their PCB standoffs/screws;
- ESS Battery Pack and battery fixture;
- Backplane PCB `100 mm × 28 mm`, Backplane Spine, ADS/AMS/OBCC/PDS `2 mm 2×6` headers, perpendicular fixture/header mating and PDM Servo Connector;
- Parachute / Top Module, Cap, Parachute and Servo as top-module/backplane connector-retention and envelope context.

`v0.1` is retained as a copied baseline because the prompt requires all S&A baselines to be preserved in the test folder, but it does not contain the battery, PCBs, backplane PCB, headers or PDM Servo Connector required for this executable retention activity.

## Released movement/witness-mark thresholds (`SAA-BLK-007`)

These thresholds select definition values for later execution/reporting; they do not state that any retention screen has passed. Use measurement uncertainty guard bands wherever measurements are taken. Any crack, rattle, loss of continuity/isolation, rail failure, connector unseat, bent pin, forced reseat, unapproved post-screen tightening, or ambiguous evidence is hold/fail regardless of measured displacement.

| Feature | Released threshold |
|---|---|
| ESS battery pack / battery fixture | No detachment; witness-mark shift or measured movement `<=0.5 mm` in any direction after screen; no new gap, rattle, fixture crack, cell damage, harness strain, or contact with prohibited neighbors. |
| ADS/AMS/OBCC/PDS PCBs and PCB standoffs/screws | Board-edge or standoff displacement `<=0.25 mm`; no new gap, board flex set, cracked/stripped boss, loose standoff, or screw witness-mark rotation beyond `10°`. |
| Backplane PCB / backplane spine / header mating | Displacement or seating-gap increase `<=0.25 mm`; no partial unseat, bent pin, intermittent continuity, new short/open, or rail/testpoint failure. |
| PDM servo connector and other connectors/harnesses | Connector seating-gap increase or relative movement `<=0.25 mm`; latch/friction retention remains engaged; no polarity/orientation shift, bent pin, intermittent continuity, insulation damage, or harness strain-relief failure. |
| Stack screws / top-module / cap / parachute context | No new visible gap over `0.25 mm`; no screw witness-mark rotation beyond `10°`; no new interference with parachute/cap/servo clearance. |

If a feature cannot be measured to the above resolution, use before/after witness marks, macro photos, and continuity/functional checks; ambiguous evidence is hold, not pass.

## Verification means and allocated functions

| Actor / equipment | Verification-only functions |
|---|---|
| S&A Test Operator | Identify v1.0 article, baseline copy, build record and evidence folder; install/verify retention witness marks; configure fixture axis/orientation/restraint/abort limits; execute approved screen; record anomalies and re-run needs. |
| Safety / QA Witness | Establish safety boundary; witness pre/post PC, PL and interface inspections; approve pass/fail/hold, waiver rejection or re-run disposition. |
| Tailored Vibration / Drop / Proof-load Fixture | Provide approved load level, axis, duration, orientation, fixture coupling, remote release and safe stop for vibration, drop, landing-impact or `20 g`-style proof-load screening. |
| Accelerometer / Event Logger | Capture vibration, shock or proof-load event markers/time history and flag under-test, over-test, abort or missing sensor evidence. |
| Retention Inspection Kit | Inspect witness marks, torque marks, gaps, cracks, rattle, bent pins and connector seating; measure or bound battery, PCB, backplane and connector movement. |
| Scale and Envelope Gauge | Check post-screen mass/part census for lost hardware and verify 355 ml envelope free fit / max dimensions. |
| Backplane Checkout Tool | Check post-screen continuity, isolation, header/connector seating and, when safe to power, `5.0 ±0.1 V` and `3.3 ±0.1 V` rails at required testpoints. |
| Ambient Meter and Photo/Video Camera | Record temperature/humidity before repetitions and capture setup, loading, rest state, inspections, anomalies and evidence context. |
| Evidence Repository | Store report-by-reference package under `S&A/MBSE/tests/results/SAA-VV-CON-005/`. |

## Procedure definition

1. Identify the `v1.0` article, build/configuration record, baseline copy, operator, witness, equipment IDs, calibration/status records and evidence repository path.
2. Confirm the full as-flown configuration is installed: battery, ADS/AMS/OBCC/PDS PCBs, backplane, headers, PDM Servo Connector, cap, parachute, servo and all modeled retention hardware.
3. Load the tailored screen definition. Record vibration/drop/landing-impact/proof-load level, axes, orientations, duration, fixture coupling, safety controls, abort criteria and limitations. If levels or limitations are not approved, record a hold/no-pass rather than executing or claiming pass.
4. Record ambient temperature/humidity, safety boundary, fixture setup, accelerometer/event logger setup, camera field of view and instrument calibration/status.
5. Perform mandatory 100% pre-screen PC/PL/interface inspection for battery fixture, stack screws, PCB standoffs/screws, backplane fixture, headers, PDM Servo Connector and top-module context. Capture witness marks, gap/torque marks and reference photos.
6. Configure the fixture for the first approved axis/orientation/event. Couple the UUT without hidden preload, unapproved shim, obstruction, temporary omission or damage.
7. Execute the approved screen and monitor the acceleration/event log, camera view, witness observations, over/under-test condition, aborts and forbidden events.
8. Repeat the configured sequence for every approved axis, orientation, level or event in the screen definition.
9. Safe the fixture and remove the UUT without tightening, reseating or altering the as-found condition unless the anomaly chain has been opened.
10. Perform mandatory 100% post-screen retention inspection for detachment, looseness, witness-mark shift, new gap, rattle, crack, bent pin, connector unseat and hidden damage.
11. Measure or bound battery, PCB/standoff, backplane/header, connector/harness and stack/top-module/cap/parachute movement against the released thresholds above. If a feature cannot be measured to the required resolution, use before/after witness marks, macro photos and continuity/functional checks; ambiguous evidence is hold, not pass.
12. Check post-screen mass/part census and envelope compliance. Verify no retained part was lost and that `D_max + U_D ≤ 66.0 mm` and `H_max + U_H ≤ 122.0 mm` remain true for the modeled envelope.
13. Run post-screen backplane/header/PDM-servo-connector seating checks, continuity/isolation and required rail/testpoint checks. Apply `5.0 ±0.1 V` and `3.3 ±0.1 V` only under recorded safe-load or no-load conditions when power is applied.
14. Apply pass/fail constraints and statistical/fault-hardening viewpoints. If any hold trigger occurs, execute the anomaly disposition chain, preserve as-found evidence, quarantine the article, disposition corrective action and re-run affected checks or full screen as required.
15. QA witness releases pass/fail/hold decision and the evidence repository archives the screen definition, limitations, logs, photos/video, inspection records, measurements, rail/interface records, anomaly dispositions and final decision.

## Pass/fail constraints

Pass only if all of the following are true for the `v1.0` article:

- tailored screen levels, axes, orientations, duration, fixture coupling, limitations, safety controls and abort criteria are approved and recorded before execution;
- no retained mass detaches and no hardware is lost; post-screen mass/part census has no unexplained change outside measurement uncertainty;
- ESS battery pack/battery fixture has no detachment; witness-mark shift or measured movement is `<=0.5 mm` in any direction, with no new gap, rattle, fixture crack, cell damage, harness strain or contact with prohibited neighbors;
- ADS/AMS/OBCC/PDS PCBs and PCB standoffs/screws have board-edge or standoff displacement `<=0.25 mm`, no new gap, no board flex set, no cracked/stripped boss, no loose standoff and no screw witness-mark rotation beyond `10°`;
- Backplane PCB/backplane spine/header mating displacement or seating-gap increase is `<=0.25 mm`, with no partial unseat, bent pin, intermittent continuity, new short/open or rail/testpoint failure;
- PDM Servo Connector and other connectors/harnesses have connector seating-gap increase or relative movement `<=0.25 mm`; latch/friction retention remains engaged with no polarity/orientation shift, bent pin, intermittent continuity, insulation damage or harness strain-relief failure;
- stack screws/top-module/cap/parachute context has no new visible gap over `0.25 mm`, no screw witness-mark rotation beyond `10°` and no new deployment-clearance interference;
- post-screen envelope remains compliant with `D_max + U_D ≤ 66.0 mm` and `H_max + U_H ≤ 122.0 mm`;
- post-screen PC/PL/interface inspection passes for 100% of target retention features;
- backplane seating, header mating, PDM Servo Connector seating, continuity/isolation and required rail/interface checks pass; powered rail checks meet `5.0 ±0.1 V` and `3.3 ±0.1 V` at required testpoints under recorded safe-load or no-load conditions;
- acceleration/event logs, photos/video, ambient records, equipment status, screen definition, limitations, pre/post inspections, measurements, witness review and anomaly/waiver/rework/re-run dispositions are complete.

Fail or hold for any detachment, looseness, movement or seating-gap increase beyond the released thresholds, shifted witness mark beyond threshold, new gap beyond threshold, rattle, crack, bent pin, connector unseat, intermittent continuity, new short/open, rail/testpoint failure, deployment-clearance interference, uncontrolled or unapproved screen level, fixture-induced hidden preload/damage, missing or ambiguous evidence, unapproved rework/tightening/reseating, unresolved anomaly, unapproved waiver or required re-run not completed.

## Viewpoints

- **Statistical significance:** This activity is a v1.0 article environmental screen by default. It verifies the screened article/configuration and makes no population reliability or qualification claim unless an independent article/trial plan is approved before execution. Pre/post inspection is a mandatory 100% census of every target PC, PL and interface on the screened article. Repeated axes/orientations/events on one article are workmanship/integration evidence, not independent reliability trials, unless independence and representativeness are justified. If a reliability claim is later required, use the project IVV binomial policy (for example, `29/29` zero-failure independent representative trials for an R90/C95 planning point).
- **Fault hardening:** The modeled activity explicitly screens and holds for heavy battery detachment, battery slip, stack-screw loosening, PCB/standoff movement, stripped/cracked printed bosses, header/PDM Servo Connector unseat, backplane movement, bent pins, hidden cracks, post-test rail/signal failure, unsafe fixture over-constraint, under/over-test, ambiguous acceleration/video data, after-the-fact tightening or reseating, and evidence-control escape.

## Required report content

The execution report in `S&A/MBSE/tests/results/SAA-VV-CON-005/` should reference this model definition and record only execution-specific information:

- model definition revision and v1.0 baseline copy used;
- article identifier, version, build/configuration record and confirmation that flight-relevant battery/PCBs/backplane/connectors/top-module hardware are installed;
- operator, witness, equipment IDs, calibration/status records, ambient record, safety boundary and camera/logger setup;
- tailored screen definition: type, level, axis, orientation, duration, fixture coupling, abort criteria, impact surface or proof-load adapter, limitations and approval/hold rationale;
- pre/post PC/PL/interface inspection checklist for battery fixture, stack screws, PCB standoffs/screws, backplane fixture, headers, PDM Servo Connector and top-module context;
- witness-mark/gap/movement measurements for each released threshold, measurement uncertainty/guard-band method, macro-photo references, and any use of witness marks when direct measurement resolution is unavailable;
- acceleration/event logs, photos/video and screen validity/over-test/under-test/abort notes;
- post-screen mass/part census and envelope check results;
- post-screen backplane/header/PDM-servo-connector seating, continuity/isolation and rail/interface check results;
- statistical-basis statement distinguishing article screen from any approved independent reliability/qualification claim;
- pass/fail/hold rationale;
- deviations, anomalies, waivers, rework, re-tightening/reseating prohibitions, re-run scope and re-run evidence.

## Assumptions and blockers

- The baseline S&A views contain only physical architecture; this folder adds verification-only PV2, PV3 and functional-chain definitions rather than editing baseline source views.
- The executable activity is for `SAA-v1.0`; `v0.1` is retained as copied context only.
- The closure record approves the environmental-screen decision, but detailed test-definition edits for environmental levels, surfaces, orientations/axes, durations/events, limitations and success criteria are pending and are not inserted here. This definition therefore continues to require an approved controlled screen record and records all limitations before a pass can be claimed; unresolved detailed levels produce hold/no-pass.
- Movement thresholds for battery, PCB/standoff, backplane/header, connector/harness and stack/top-module/cap/parachute context are released in this README from the closure record. Ambiguous movement evidence is hold, not pass.
- The gate may be held rather than failed when a discrepancy is correctable by approved rework, model/evidence update, or accepted limitation before flight-readiness closure; all affected checks or screen events must then be re-run.
