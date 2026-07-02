# SAA-VV-CON-001 — 355 ml envelope, mass, and landing-impact constraint verification

Model-defined constraint-derived verification activity for the S&A `v0.1` transition-readiness baseline and `v1.0` flight-readiness/final-acceptance baseline.

- **IADT method:** Inspection / Testing
- **IVV source category:** Constraint
- **SSIV / development versions:** `SAA-v0.1` structural/module/backplane-volume transition readiness and `SAA-v1.0` final as-flown flight readiness.
- **Definition folder:** `S&A/MBSE/tests/SAA-VV-CON-001/`
- **Expected report/evidence folder:** `S&A/MBSE/tests/results/SAA-VV-CON-001/`
- **Primary traceability targets:** modeled `355 ml` envelope / mass / landing-impact constraint, `SAA-FE-EnvelopeNonCompliance`, `SAA-FE-MassNonCompliance`, `SAA-FE-LandingDamage`, `SAA-UC-IntegratedAssembly`, and `SAA-UC-ParachuteClearance`.
- **References:** IVV (`PM&SE/IVV.md`), SAA-R1, SAA-R2, and SAA-R5 as indexed in `S&A/MBSE/tests/references/README.md`.

## Model views

| View | D2 | PNG | Purpose |
|---|---|---|---|
| Baseline copy v0.1 | `baseline/SAA_v0.1_view1_physical.d2` | `baseline/SAA_v0.1_view1_physical.png` | Frozen source context for the v0.1 structural/module/backplane-volume readiness gate. |
| Baseline copy v1.0 | `baseline/SAA_v1.0_view1_physical.d2` | `baseline/SAA_v1.0_view1_physical.png` | Frozen source context for the v1.0 integrated as-flown flight-readiness gate. |
| v0.1 physical constraint testbench | `SAA-VV-CON-001_v0.1_physical_constraint_testbench.d2` | `SAA-VV-CON-001_v0.1_physical_constraint_testbench.png` | PV1 testbench for the v0.1 structural article with envelope gauge, caliper/height gauge, scale, drop/impact fixture, impact surface, shock witness, inspection kit, ambient meter, operator/witness, camera, repository, physical links, and transition-readiness constraints. |
| v1.0 physical constraint testbench | `SAA-VV-CON-001_v1.0_physical_constraint_testbench.d2` | `SAA-VV-CON-001_v1.0_physical_constraint_testbench.png` | PV1 testbench for the v1.0 integrated as-flown article with envelope gauge, caliper/height gauge, scale, drop/impact fixture, impact surface, shock witness, inspection kit, ambient meter, operator/witness, camera, repository, physical links, and final flight-readiness constraints. |
| Logical evidence interface | `SAA-VV-CON-001_logical_evidence_interface.d2` | `SAA-VV-CON-001_logical_evidence_interface.png` | Verification-only PV2 component exchanges for configuration, baseline selection, measurements, impact-screen definition/hold rationale, post-impact inspection, anomalies, acceptance and evidence release. |
| Functional allocation / procedure | `SAA-VV-CON-001_functional_allocation_procedure.d2` | `SAA-VV-CON-001_functional_allocation_procedure.png` | Verification-only PV3 allocation of human, equipment, UUT, impact-screen, acceptance and evidence functions. |
| Envelope and mass measurement chain | `SAA-VV-CON-001_envelope_mass_measurement_chain.d2` | `SAA-VV-CON-001_envelope_mass_measurement_chain.png` | Inspection/testing functional chain for diameter, height, free-fit and mass guard-band acceptance. |
| Landing-impact / drop-screen chain | `SAA-VV-CON-001_landing_impact_drop_screen_chain.d2` | `SAA-VV-CON-001_landing_impact_drop_screen_chain.png` | Testing functional chain for approved tailored drop/impact screen, plus explicit analysis-backed hold path when exact levels are unresolved. |

The logical components, component exchanges, functions, physical links to test equipment, impact-screen records, shock witnesses and functional chains in this folder are **verification-only** and do not modify the S&A baseline architecture.

## Items under verification

### `v0.1` transition-readiness article

The v0.1 UUT is the structural article defined by `S&A/MBSE/v0.1/SAA_v0.1_view1_physical.d2`:

- CanSat Structural Envelope;
- Standard Carrier Module Stack (Type 1), ADS/AMS/OBCC/PDS/ESS Modules;
- Perpendicular Backplane Volume;
- Parachute / Top Module (Type 2);
- stack-screw interfaces, perpendicular backplane slot and backplane clearance.

`v0.1` closure is limited to structural/module/backplane-volume transition readiness. Mass evidence is reference or ballasted structural evidence unless the article includes final flight hardware and ballast. A v0.1 drop screen may use documented representative ballast if the structural screen claims mass realism.

### `v1.0` final as-flown article

The v1.0 UUT is the integrated CanSat Assembly defined by `S&A/MBSE/v1.0/SAA_v1.0_view1_physical.d2`, including Standard Carrier Module Stack, ADS/AMS/OBCC/PDS/ESS Modules, ADS/AMS/OBCC/PDS `44 mm × 44 mm` PCBs, ESS Battery Pack, Backplane PCB `100 mm × 28 mm`, ADS/AMS/OBCC/PDS `2 mm 2×6` headers, PDM Servo Connector, Backplane Spine, Parachute / Top Module, Cap, Parachute and Servo. `v1.0` closure requires the full as-flown configuration with battery, PCBs, backplane, cap, parachute, servo, connectors and any required ballast installed.

## Verification means and allocated functions

| Actor / equipment | Verification-only functions |
|---|---|
| S&A Test Operator | Identify article, baseline copy, build record and readiness gate; confirm v0.1 ballast or v1.0 as-flown configuration; operate measurement equipment; configure drop fixture and orientation; record anomalies. |
| Safety / QA Witness | Witness setup, calibration, ambient record, safety controls, release/impact, post-impact inspection, no-hand-assist/no-forced-fit rules and pass/fail/hold decisions. |
| 355 ml Envelope / Can Gauge | Check free fit within `Ø66.0 mm × H122.0 mm` without force or protrusion exception. |
| Calibrated Caliper / Height Gauge | Measure maximum outside diameter and height and provide expanded uncertainties `U_D` and `U_H`. |
| Calibrated Scale | Measure structural, ballasted or as-flown mass and provide expanded uncertainty `U_M`; target resolution/uncertainty is `≤0.1 g` unless a better calibration record is used. |
| Drop / Landing-Impact Screen Fixture and Impact Surface | Provide approved or held drop/impact level, orientation set, fixture, impact surface and safety boundary; release the article only when the tailored screen is controlled. |
| Shock / Acceleration Logger or Witness Indicator | Record shock marker, peak acceleration or equivalent impact witness when installed. |
| Post-Impact Inspection Kit | Inspect cracks, deformation, looseness, battery movement, backplane/header/PDM-servo connector unseat, cap/parachute/servo jam, hidden damage and post-impact serviceability. |
| Photo / Video Evidence Camera | Capture configuration, measurement, release, impact, rest state, inspection and anomaly evidence. |
| Ambient Thermo-Hygrometer | Record temperature and humidity before measurement and impact repetitions; hold if conditions can affect measurement or safety. |
| Evidence Repository | Store controlled report, raw readings, uncertainty values, screen definition/hold rationale, photos/video, inspection records, witness decision and anomaly dispositions under `S&A/MBSE/tests/results/SAA-VV-CON-001/`. |

## Procedure definition

### Envelope and mass inspection/testing chain

1. Select the readiness gate: `v0.1` transition readiness or `v1.0` final flight readiness.
2. Identify article, build/configuration record, baseline copy, operator, witness, instrument IDs, calibration status and evidence repository path.
3. Confirm configuration: v0.1 structural article and any representative ballast; or v1.0 full as-flown article.
4. Record ambient temperature/humidity and hold if conditions can affect measurement or evidence quality.
5. Demonstrate free fit in the `355 ml` envelope/can gauge without force or protrusion exception.
6. Measure maximum outside diameter and maximum height with calibrated instruments and record `U_D` and `U_H`.
7. Measure mass with calibrated scale and record `U_M`. For v0.1, state whether mass is unballasted structural, ballasted structural, or final-like. For v1.0, all flight items and required ballast must be installed.
8. Apply uncertainty guard-band pass/fail criteria.
9. Capture photos/video and raw readings sufficient to bind the article, configuration and measurements to the report.
10. QA witness approves pass/fail/hold/re-run and the evidence repository releases the report-by-reference package.

### Landing-impact / drop-screen testing chain

1. Select the readiness gate and load the proposed drop/landing-impact screen definition.
2. Verify that drop height/energy, impact surface, orientation set, fixture, article state and safety boundary are approved. If not, classify an **analysis-backed hold**; do not release the article and do not claim impact pass.
3. Confirm v0.1 ballast/configuration or v1.0 full as-flown configuration.
4. Perform pre-screen PC/PL and condition checks, including stack screws, module interfaces, backplane volume or backplane/header/PDM-servo connector, PCB standoffs, battery fixture, cap, parachute and servo as applicable.
5. Record ambient/environment condition, fixture state, camera field of view and witness identity.
6. Mount/hold the article in the approved orientation without preloading or damage.
7. Execute the tailored drop/landing-impact screen and record the complete release, free fall, impact, rebound/rest state and any forbidden event.
8. Perform post-impact inspection for structural fracture, deformation, loose screws/standoffs, battery movement, module shift, backplane/header/PDM-servo connector unseat, electrical short/open evidence, cap/parachute/servo jam and hidden damage.
9. Repeat envelope and mass checks or verify no post-impact change requiring remeasurement closure.
10. Apply impact pass/fail criteria; open anomaly/waiver/rework/re-run/hold/fail disposition as needed.
11. QA witness approves pass/fail/hold/re-run and the evidence repository archives the screen definition, videos/photos, logs, inspections and decisions.

## Pass/fail constraints

Pass only if all applicable constraints below are satisfied:

- `D_max + U_D ≤ 66.0 mm` for the selected article.
- `H_max + U_H ≤ 122.0 mm` using the closure-record S&A height authority. This activity uses `122.0 mm` unless a later project authority selects a stricter competition limit before test.
- For `v1.0`, measured mass plus expanded uncertainty satisfies `measured mass + U_M < 350.0 g`. The closure record controls the modeled `<350 ±0.1 g` wording as actual total mass `<350.0 g` with a measurement guard band; if `U_M = 0.1 g`, the displayed mass must be `<349.9 g`.
- For `v0.1`, mass is recorded as structural/reference or ballasted structural evidence and is not a final flight mass pass unless final-like hardware and ballast state are documented.
- Impact/drop-screen pass requires an approved tailored level, surface, fixture, orientation set, article state and safety boundary. If exact levels remain unresolved, the only valid modeled outcome is analysis-backed hold.
- After impact, no structural/integration failure is allowed: no crack, permanent deformation, stack screw/standoff loosening, battery movement, module shift, backplane/header/PDM-servo connector unseat, electrical short/open evidence, cap/parachute/servo jam, loss of serviceability, or hidden damage left unresolved.
- Post-impact envelope/mass remeasurement or inspection must remain acceptable under the same guard-band rules.
- Instrument calibration status, ambient record, raw readings, uncertainty values, screen definition/hold rationale, photos/video, pre/post inspection records, witness review and anomaly dispositions must be complete.
- Any missing calibration/evidence, forced gauge fit, missing flight item, temporary omission, unapproved ballast/configuration, ambiguous video, unresolved anomaly, unapproved waiver, or required re-run not completed is a hold/fail.

## Viewpoints

- **Statistical significance:** Diameter, height and mass are calibrated continuous measurements; retain raw readings and expanded uncertainties and pass only with guard bands. Impact/drop-screen outcomes are binary pass/fail trials. A one-article screen is a workmanship/integration screen and makes no population reliability claim. If a reliability claim is made, use representative independent trials and one-sided binomial confidence logic; `29/29` zero-failure trials is the planning point for R90/C95.
- **Fault hardening:** The model prevents false pass from missing flight items, under-mass or undocumented ballast, forced gauge fit, ignored protrusions, measuring non-maximum dimensions, unresolved drop level, unsupported impact surface, unrecorded orientation, preloaded fixture, hidden cracks, loose fasteners, battery migration, backplane/header/PDM-servo connector unseat, jammed cap/parachute/servo, skipped post-impact remeasurement, ambiguous video or evidence-control escape.

## Required report content

The execution report in `S&A/MBSE/tests/results/SAA-VV-CON-001/` should reference this model definition and record execution-specific information:

- model definition revision and baseline copy used;
- article identifier, version, build/configuration record and ballast/battery state;
- operator, witness, equipment IDs, calibration records, ambient record and safety boundary;
- raw diameter, height and mass readings, uncertainty values and guard-band calculations;
- drop/impact level, impact surface, orientation set, fixture configuration, shock witness data if used, and hold rationale if levels remain unresolved;
- pre/post impact inspection checklist and post-impact remeasurement results;
- photo/video/log evidence IDs and file paths;
- pass/fail/hold rationale by v0.1 and/or v1.0 gate;
- deviations, anomalies, waivers, rework and re-run evidence.

## Assumptions and blockers

- The baseline S&A views contain only physical architecture; this folder adds verification-only PV2, PV3 and functional-chain definitions rather than editing baseline source views.
- `v0.1` is an incremental structural readiness gate and cannot by itself close final flight mass/impact acceptance without documented representative ballast or final-like configuration.
- The closure record confirms the modeled height limit `122.0 mm` as the S&A authority unless a later project authority selects a stricter competition limit.
- The impact/drop levels are not resolved in the baseline. The model therefore includes both an executable tailored-screen path and an analysis-backed hold path; execution cannot claim pass until the tailored level, impact surface, orientation set and article state are approved.
- The gate may be held rather than failed when a discrepancy is correctable by approved rework, model/evidence update, or accepted dependency before flight-readiness closure.
