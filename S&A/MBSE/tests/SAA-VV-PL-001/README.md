# SAA-VV-PL-001 — Physical link presence/retention/alignment inspection

Model-defined verification activity for the S&A physical architecture baselines. This activity closes the physical-link portion of component/link IVV coverage for the available S&A baselines.

- **IADT method:** Inspection
- **IVV source category:** Component/link — physical link portion
- **SSIV / development versions:** `SAA-v0.1` transition-readiness gate and `SAA-v1.0` flight-readiness gate
- **Definition folder:** `S&A/MBSE/tests/SAA-VV-PL-001/`
- **Expected report/evidence folder:** `S&A/MBSE/tests/results/SAA-VV-PL-001/`
- **Primary traceability targets:** `SAA-UC-IntegratedAssembly`, `SAA-UC-BackplaneIntegration`, `SAA-UC-ParachuteClearance`, `SAA-FE-BackplaneMisMate`, `SAA-FE-StructuralLoosening`, `SAA-FE-LandingDamage`, and the modeled S&A physical-link, backplane, assembly, and retention/mating constraints.
- **References:** IVV (`PM&SE/IVV.md`), SAA-R1, SAA-R2, SAA-R3, SAA-R4, SAA-R5 as indexed in `S&A/MBSE/tests/references/README.md`.

## Model views

| View | D2 | PNG | Purpose |
|---|---|---|---|
| Baseline copy v0.1 | `baseline/SAA_v0.1_view1_physical.d2` | `baseline/SAA_v0.1_view1_physical.png` | Frozen source context for the v0.1 PL census. |
| Baseline copy v1.0 | `baseline/SAA_v1.0_view1_physical.d2` | `baseline/SAA_v1.0_view1_physical.png` | Frozen source context for the v1.0 PL census. |
| v0.1 physical link inspection testbench | `SAA-VV-PL-001_v0.1_physical_link_inspection_testbench.d2` | `SAA-VV-PL-001_v0.1_physical_link_inspection_testbench.png` | PV1 inspection testbench with equipment physical links, v0.1 modeled PLs, and v0.1 pass/fail constraints. |
| v1.0 physical link inspection testbench | `SAA-VV-PL-001_v1.0_physical_link_inspection_testbench.d2` | `SAA-VV-PL-001_v1.0_physical_link_inspection_testbench.png` | PV1 inspection testbench with equipment physical links, v1.0 modeled PLs, and v1.0 pass/fail constraints. |
| Logical evidence exchange | `SAA-VV-PL-001_logical_evidence_exchange.d2` | `SAA-VV-PL-001_logical_evidence_exchange.png` | Verification-only PV2 component exchanges for checklist/evidence/tool/QA control. |
| Functional allocation / procedure | `SAA-VV-PL-001_functional_allocation_procedure.d2` | `SAA-VV-PL-001_functional_allocation_procedure.png` | Verification-only PV3 allocation of link-inspection functions to operators, equipment, records, and version gates. |

The logical component exchanges, logical components, and functions in this folder are **verification-only** and do not modify the S&A baseline architecture. No functional chain is required because the method is pure Inspection; the inspection procedure is modeled through PV2/PV3 views and pass/fail constraints.

## Required inspection census

### v0.1 transition-readiness PL census

Inspect and disposition one row for each modeled v0.1 physical link:

| PL ID | Modeled physical link | Modeled endpoints | Required inspection focus |
|---|---|---|---|
| v0.1-PL-01 | Stack screws | ADS Module — AMS Module | Present, correct endpoints, retained, not loose, no stripped boss/damage. |
| v0.1-PL-02 | Stack screws | AMS Module — OBCC Module | Present, correct endpoints, retained, not loose, no stripped boss/damage. |
| v0.1-PL-03 | Stack screws | OBCC Module — PDS Module | Present, correct endpoints, retained, not loose, no stripped boss/damage. |
| v0.1-PL-04 | Stack screws | PDS Module — ESS Module | Present, correct endpoints, retained, not loose, no stripped boss/damage. |
| v0.1-PL-05 | Stack screws | Standard Carrier Module Stack — Parachute / Top Module | Present, correct endpoints, retained, not loose, no stripped boss/damage. |
| v0.1-PL-06 | Perpendicular backplane slot | Standard Carrier Module Stack — Perpendicular Backplane Volume | Slot present, clear, aligned, not blocked or damaged. |
| v0.1-PL-07 | Backplane clearance | Parachute / Top Module — Perpendicular Backplane Volume | Clearance path present, aligned, no interference or damage. |

### v1.0 flight-readiness PL census

Inspect and disposition one row for each modeled v1.0 physical link:

| PL ID | Modeled physical link | Modeled endpoints | Required inspection focus |
|---|---|---|---|
| v1.0-PL-01 | Stack screws | ADS Module — AMS Module | Present, correct endpoints, retained, not loose, no stripped boss/damage. |
| v1.0-PL-02 | Stack screws | AMS Module — OBCC Module | Present, correct endpoints, retained, not loose, no stripped boss/damage. |
| v1.0-PL-03 | Stack screws | OBCC Module — PDS Module | Present, correct endpoints, retained, not loose, no stripped boss/damage. |
| v1.0-PL-04 | Stack screws | PDS Module — ESS Module | Present, correct endpoints, retained, not loose, no stripped boss/damage. |
| v1.0-PL-05 | Stack screws | Standard Carrier Module Stack — Parachute / Top Module | Present, correct endpoints, retained, not loose, no stripped boss/damage. |
| v1.0-PL-06 | Perpendicular fixture + header mating | Standard Carrier Module Stack — Backplane PCB | Backplane seated perpendicularly, headers mated/aligned, no bent pins, no open/short evidence where checked, no bypass. |
| v1.0-PL-07 | Backplane fixture + servo connector | Parachute / Top Module — Backplane PCB | Fixture and servo connector present, seated, retained, clear of parachute/cap/servo interference, no unseat/damage. |
| v1.0-PL-08 | PCB standoffs / screws | ADS PCB — ADS Module | Present, retained, aligned, no loose hardware, no PCB stress/damage. |
| v1.0-PL-09 | PCB standoffs / screws | AMS PCB — AMS Module | Present, retained, aligned, no loose hardware, no PCB stress/damage. |
| v1.0-PL-10 | PCB standoffs / screws | OBCC PCB — OBCC Module | Present, retained, aligned, no loose hardware, no PCB stress/damage. |
| v1.0-PL-11 | PCB standoffs / screws | PDS PCB — PDS Module | Present, retained, aligned, no loose hardware, no PCB stress/damage. |
| v1.0-PL-12 | Battery fixture | ESS Battery Pack — ESS Module | Battery retained, no slip, no fixture damage, no interference with stack/backplane. |

## Verification means and allocated functions

| Actor / equipment | Verification-only functions |
|---|---|
| Inspection Operator | Identify article version/build record/baseline; enumerate modeled PLs; inspect link presence, endpoints, routing, mating, retention, alignment, looseness, interference, and damage; record evidence and anomalies. |
| QA Witness | Witness the 100% PL census, tool suitability/calibration checks, and evidence package; approve the version readiness gate or require hold/fail. |
| Calibrated Camera / Microscope | Capture overview, close-up, and anomaly images for each PL or link group. |
| Torque Tool / Pull Gauge | Support retention checks for stack screws, PCB standoffs/screws, battery fixture, and other retained links where accessible and safe. |
| Continuity / Alignment Aids | Support slot/clearance/header/connector alignment checks and record open/short or bent-pin evidence where applicable. |
| Assembly Fixture / ESD Support | Hold the article in a stable, ESD-safe inspection orientation without creating inspection damage. |
| Evidence Repository | Store the released checklist, photos, tool readings, report, anomalies, waivers, and QA decision under `S&A/MBSE/tests/results/SAA-VV-PL-001/`. |

## Inspection procedure definition

For each inspected article and selected baseline (`v0.1` or `v1.0`):

1. Identify article version, build/configuration record, and the baseline copy used for the inspection.
2. Place the article on the assembly fixture; apply ESD handling where electrical/PCB links are inspected.
3. Confirm camera/microscope, torque or pull gauge, and continuity/alignment aids are identified and in current calibration or approved workshop check status before their readings are used as evidence.
4. Enumerate the full modeled PL set for that version from this README and the baseline copy.
5. For every modeled PL, inspect and record:
   - presence/absence;
   - modeled endpoints and observed endpoints;
   - routing, mating, seating, or clearance state as applicable;
   - retention/alignment condition and visible looseness;
   - absence/presence of interference, damage, stripped bosses, bent pins, open/short evidence where applicable, or unapproved bypass;
   - photo, microscope, tool, alignment, continuity, build-record, or waiver evidence reference;
   - anomaly disposition if not immediately conforming.
6. Use camera/microscope evidence for each PL group and for every anomaly or ambiguous endpoint/mating condition.
7. Use torque/pull or continuity/alignment aids only within safe inspection limits; if applying a tool could damage the article, record a visual/manual retention check and put quantitative proof-load or environmental retention evidence under the relevant constraint activity such as `SAA-VV-CON-005`.
8. QA witness reviews the completed census and evidence package.
9. Close the version gate as pass, fail, or hold.

## Environmental-screen evidence interface

When this PL inspection is used as pre/post evidence for the approved S&A tailored environmental screen, it remains a 100% PC/PL/interface census and evidence-control activity, not environmental pass/fail credit by itself. Before the screen, predeclare article/build IDs, installed state, ballast/surrogate rationale, fixture adapters, safety boundary, equipment calibration/status, ambient, camera/logger setup and evidence path; capture witness-mark/gap photos for every affected link group. After the screen, repeat the 100% PC/PL/interface census and compare against the `SAA-BLK-007` thresholds used by `SAA-VV-CON-005`. Do not tighten, reseat or rework between pre/post checks unless an anomaly is opened and affected screen events/checks are re-run.

## Pass/fail constraints

Pass for the selected version only if **every** modeled PL in that version is:

- present;
- correctly endpointed to the modeled physical components;
- routed, seated, mated, or clear as modeled;
- retained/aligned with no visible looseness;
- free of interference, damage, stripped bosses, bent pins, open/short evidence where applicable, and unapproved bypass;
- recorded with sufficient evidence for report-by-reference; and
- accepted by the QA witness.

Fail or hold the gate for any missing modeled PL, extra unmodeled link affecting the modeled assembly, wrong or ambiguous endpoint, unapproved routing/bypass, loose screw/fixture/connector, stripped boss, battery fixture slip, blocked slot, insufficient clearance, misaligned/mis-mated header, bent pin, open/short evidence where applicable, interference with parachute/cap/servo/backplane, damage without approved disposition, missing evidence, or unresolved QA witness objection.

## Required report content

The execution report in `S&A/MBSE/tests/results/SAA-VV-PL-001/` should reference this model definition and record only execution-specific information:

- model definition revision and baseline copy used;
- inspected article identifier, version, and build/configuration record;
- completed PL census table with pass/fail/hold disposition for each row;
- evidence IDs and file paths for photos, microscope images, tool readings, continuity/alignment notes, build records, anomalies, and waivers;
- actual instrument/tool calibration or workshop-check status and any environmental/handling deviations;
- QA witness identity and approval/hold/fail decision;
- deviations from this model definition, anomalies, waivers, substitutions, and pass/fail rationale.

## Viewpoints

- **Statistical significance:** 100% census of modeled physical links for every inspected `v0.1` and `v1.0` article. This activity makes no sampling, population reliability, qualification, or system environmental-regression claim; the report shall state the actual article count and any repeated inspections. Environmental article/workmanship screens remain separate unless explicitly referenced.
- **Fault hardening:** The inspection intentionally screens for loose or missing stack screws, wrong endpoints, stripped bosses, blocked backplane slot, clearance interference, PCB standoff/screw failures, battery fixture slip, header/backplane misalignment, bent pins, servo connector unseat, open/short indications, parachute/cap/servo/backplane interference, damage, unapproved bypasses, and evidence-control escapes.

## Constraint coverage note

This activity covers physical-link presence, endpoint correctness, routing/mating, retention/alignment, immediate damage/interference condition, and evidence recording. Quantitative envelope/mass, electrical rail tolerance, signal-integrity performance, DRC/ERC, print-process, vibration/drop, and proof-load article/workmanship-screen criteria remain assigned in the top-level plan to `SAA-VV-CON-001` through `SAA-VV-CON-005` and related interface activities unless an execution report explicitly invokes this inspection as supporting evidence.

## Assumptions

- The only available S&A baselines are `v0.1` and `v1.0`; both are covered separately.
- A link may be inspected as a grouped interface only when the checklist still records each modeled PL row and its endpoints.
- This pure PL inspection does not by itself impose torque or proof-load values. When quantitative retention evidence is invoked, use the `SAA-VV-CON-004` screw-torque/coupon criteria plus the approved S&A tailored environmental-screen criteria in `SAA-VV-CON-005` (`20 g` equivalent proof retention with `20 N` ESS / `10 N` PCB-backplane-connector-top-module minimums, `10 s` holds, `60 s` low-level vibration/handling where used, and `SAA-BLK-007` movement thresholds). This activity still requires retention/no-looseness evidence, records any approved project or work-instruction criteria used during execution, and does not claim `SYS-ENVIRONMENTAL-REGRESSION`.
- The gate may be placed on hold rather than failed when a discrepancy is correctable but not yet dispositioned.
