# SAA-VV-PC-001 — Physical component presence/identity/placement inspection

Model-defined verification activity for the S&A physical architecture baselines. This activity was selected from the S&A verification plan to close the physical-component portion of component/link IVV coverage for the available S&A baselines.

- **IADT method:** Inspection
- **IVV source category:** Component/link — physical component portion
- **SSIV / development versions:** `SAA-v0.1` transition-readiness gate and `SAA-v1.0` flight-readiness gate
- **Definition folder:** `S&A/MBSE/tests/SAA-VV-PC-001/`
- **Expected report/evidence folder:** `S&A/MBSE/tests/results/SAA-VV-PC-001/`
- **Primary traceability targets:** `SAA-UC-IntegratedAssembly`, `SAA-UC-BackplaneIntegration`, `SAA-UC-ParachuteClearance`, `SAA-FE-EnvelopeNonCompliance`, `SAA-FE-BackplaneMisMate`, `SAA-FE-StructuralLoosening`, and the modeled PC containment/placement constraints.
- **References:** IVV (`PM&SE/IVV.md`), SAA-R1, SAA-R2, SAA-R3, SAA-R4, SAA-R5 as indexed in `S&A/MBSE/tests/references/README.md`.

## Model views

| View | D2 | PNG | Purpose |
|---|---|---|---|
| Baseline copy v0.1 | `baseline/SAA_v0.1_view1_physical.d2` | `baseline/SAA_v0.1_view1_physical.png` | Frozen source context for the v0.1 PC census. |
| Baseline copy v1.0 | `baseline/SAA_v1.0_view1_physical.d2` | `baseline/SAA_v1.0_view1_physical.png` | Frozen source context for the v1.0 PC census. |
| v0.1 physical inspection testbench | `SAA-VV-PC-001_v0.1_physical_inspection_testbench.d2` | `SAA-VV-PC-001_v0.1_physical_inspection_testbench.png` | PV1 inspection testbench with equipment physical links and v0.1 pass/fail constraints. |
| v1.0 physical inspection testbench | `SAA-VV-PC-001_v1.0_physical_inspection_testbench.d2` | `SAA-VV-PC-001_v1.0_physical_inspection_testbench.png` | PV1 inspection testbench with equipment physical links and v1.0 pass/fail constraints. |
| Logical evidence exchange | `SAA-VV-PC-001_logical_evidence_exchange.d2` | `SAA-VV-PC-001_logical_evidence_exchange.png` | Verification-only PV2 component exchanges for checklist/evidence/QA control. |
| Functional allocation / procedure | `SAA-VV-PC-001_functional_allocation_procedure.d2` | `SAA-VV-PC-001_functional_allocation_procedure.png` | Verification-only PV3 allocation of inspection functions to operators, equipment, records, and version gates. |

The logical component exchanges, logical components, and functions in this folder are **verification-only** and do not modify the S&A baseline architecture. No functional chain is required because the method is pure Inspection; the inspection procedure is modeled through PV2/PV3 views and pass/fail constraints.

## Required inspection census

### v0.1 transition-readiness census

Inspect and disposition one row for each modeled v0.1 physical component:

1. CanSat Structural Envelope
2. Standard Carrier Module Stack (Type 1)
3. ADS Module
4. AMS Module
5. OBCC Module
6. PDS Module
7. ESS Module
8. Perpendicular Backplane Volume
9. Parachute / Top Module (Type 2)

### v1.0 flight-readiness census

Inspect and disposition one row for each modeled v1.0 physical component:

1. CanSat Assembly
2. Standard Carrier Module Stack (Type 1)
3. ADS Module
4. AMS Module
5. OBCC Module
6. PDS Module
7. ESS Module
8. ADS PCB, 44 mm × 44 mm
9. AMS PCB, 44 mm × 44 mm
10. OBCC PCB, 44 mm × 44 mm
11. PDS PCB, 44 mm × 44 mm
12. ESS Battery Pack
13. Backplane PCB, 100 mm × 28 mm, two-layer
14. 2 mm 2×6 ADS Headers
15. 2 mm 2×6 AMS Headers
16. 2 mm 2×6 OBCC Headers
17. 2 mm 2×6 PDS Headers
18. PDM Servo Connector
19. Backplane Spine
20. Parachute / Top Module (Type 2)
21. Cap
22. Parachute
23. Servo

## Verification means and allocated functions

| Actor / equipment | Verification-only functions |
|---|---|
| Inspection Operator | Identify article version/build record; enumerate modeled PCs from checklist; inspect presence, identity, placement and condition; record evidence references; disposition anomalies. |
| QA Witness | Witness 100% PC census; approve readiness gate or place hold. |
| Calibrated Camera / Microscope | Capture photo and magnified identity evidence for each component or anomaly. |
| Caliper / Scale | Measure identity or placement dimensions when needed to resolve ambiguity; calibration must be current. |
| ESD / Assembly Fixture | Support the article in an ESD-safe inspection state. |
| Evidence Repository | Store controlled report and evidence package under `S&A/MBSE/tests/results/SAA-VV-PC-001/`. |

## Inspection procedure definition

For each inspected article and selected baseline (`v0.1` or `v1.0`):

1. Identify article version, build record, and baseline copy used for the inspection.
2. Place the article on the ESD/assembly fixture; record any ambient or handling deviation that could affect evidence quality.
3. Enumerate the full modeled PC set for that version from this README and the baseline copy.
4. For every modeled PC, inspect and record:
   - presence/absence;
   - unique identity or evidence binding to the intended modeled PC;
   - correct containment/location relative to the modeled hierarchy;
   - visible condition and absence of damage affecting readiness;
   - photo, microscope, build-record, or measurement evidence reference;
   - anomaly disposition if not immediately conforming.
5. Use calibrated camera/microscope evidence for all items where identity or condition could be ambiguous.
6. Use caliper/scale measurements only as supporting evidence where identity or placement cannot be resolved visually or from build records; quantitative envelope, mass, electrical and environmental compliance remain assigned to the SAA-VV-CON-* activities unless explicitly referenced in the execution report.
7. QA witness reviews the completed census and evidence package.
8. Close the version gate as pass, fail, or hold.

## Pass/fail constraints

Pass for the selected version only if **every** modeled PC in that version is:

- present;
- uniquely identifiable;
- correctly contained and located relative to the modeled hierarchy;
- visibly undamaged or dispositioned as acceptable;
- recorded with sufficient evidence for report-by-reference; and
- accepted by the QA witness.

Fail or hold the gate for any missing modeled PC, unapproved substitution, extra unmodeled item affecting the modeled assembly, ambiguous duplicate instance, wrong containment/location, visible damage without approved disposition, missing evidence, or unresolved QA witness objection.

## Required report content

The execution report in `S&A/MBSE/tests/results/SAA-VV-PC-001/` should reference this model definition and record only execution-specific information:

- model definition revision and baseline copy used;
- inspected article identifier, version, and build/configuration record;
- completed PC census table with pass/fail/hold disposition for each row;
- evidence IDs and file paths for photos, microscope images, build records, or measurements;
- actual instrument calibration status and any environmental/handling deviations;
- QA witness identity and approval/hold decision;
- anomalies, waivers, substitutions, deviations, and rationale.

## Viewpoints

- **Statistical significance:** 100% census of modeled physical components for every inspected v0.1 and v1.0 article. This activity makes no sampling or population reliability claim; the report shall state the actual article count and any repeated inspections.
- **Fault hardening:** The inspection intentionally screens for wrong module type, omitted PC, swapped or missing PCB, missing battery/backplane/header/spine/servo connector/cap/parachute/servo, mechanical damage, placement error, ESD/handling nonconformance, ambiguous duplicates, unapproved substitutions, and evidence-control escapes.

## Constraint coverage note

This activity covers the physical-component presence, identity, containment, placement, condition, and evidence-recording portions of the S&A physical constraints. Quantitative envelope/mass, landing-impact, electrical rails, signal integrity, DRC/ERC, screw/print-process, and environmental-retention constraints remain assigned in the top-level plan to `SAA-VV-CON-001` through `SAA-VV-CON-005` and related link/interface activities.

## Assumptions

- The only available S&A baselines are `v0.1` and `v1.0`; both are covered separately.
- If a component has no serial number, acceptable identity evidence may be a drawing/build-record reference, label, distinctive geometry, measured dimension, or photo binding approved by the QA witness.
- The inspection may place a gate on hold rather than fail when a discrepancy is correctable but not yet dispositioned.
