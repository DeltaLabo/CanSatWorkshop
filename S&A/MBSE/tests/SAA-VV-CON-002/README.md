# SAA-VV-CON-002 — Modular-structure and 44 mm PCB accommodation constraint verification

Model-defined constraint-derived verification activity for the S&A `v0.1` transition-readiness baseline and `v1.0` flight-readiness/final-acceptance baseline.

- **IADT method:** Inspection / Demonstration
- **IVV source category:** Constraint
- **SSIV / development versions:** `SAA-v0.1` reusable module/structural transition readiness and `SAA-v1.0` integrated module/PCB flight readiness.
- **Definition folder:** `S&A/MBSE/tests/SAA-VV-CON-002/`
- **Expected report/evidence folder:** `S&A/MBSE/tests/results/SAA-VV-CON-002/`
- **Primary traceability targets:** modeled modular-structure constraint, `SAA-UC-IntegratedAssembly`, `SAA-FE-EnvelopeNonCompliance`, `SAA-FE-StructuralLoosening`, and the two-module-type / `44 mm × 44 mm` standard-module accommodation constraint.
- **References:** IVV (`PM&SE/IVV.md`), SAA-R1, SAA-R3, SAA-R4, and SAA-R5 as indexed in `S&A/MBSE/tests/references/README.md`.

## Model views

| View | D2 | PNG | Purpose |
|---|---|---|---|
| Baseline copy v0.1 | `baseline/SAA_v0.1_view1_physical.d2` | `baseline/SAA_v0.1_view1_physical.png` | Frozen source context for the v0.1 reusable structural/module/backplane-volume readiness gate. |
| Baseline copy v1.0 | `baseline/SAA_v1.0_view1_physical.d2` | `baseline/SAA_v1.0_view1_physical.png` | Frozen source context for the v1.0 integrated module/PCB flight-readiness gate. |
| v0.1 physical modular-accommodation testbench | `SAA-VV-CON-002_v0.1_physical_modular_accommodation_testbench.d2` | `SAA-VV-CON-002_v0.1_physical_modular_accommodation_testbench.png` | PV1 testbench for the reusable module stack, Type 1 standard modules, Type 2 top module, 44 mm dummy PCB/fit gauges, calipers/feeler gauges, keepout probes, operator/witness, ambient record and evidence repository. |
| v1.0 physical modular-accommodation testbench | `SAA-VV-CON-002_v1.0_physical_modular_accommodation_testbench.d2` | `SAA-VV-CON-002_v1.0_physical_modular_accommodation_testbench.png` | PV1 testbench for the integrated CanSat Assembly with ADS/AMS/OBCC/PDS flight PCBs, backplane/header/battery/top-module interference checks, fit gauges, calipers/feeler gauges, operator/witness, ambient record and evidence repository. |
| Logical evidence interface | `SAA-VV-CON-002_logical_evidence_interface.d2` | `SAA-VV-CON-002_logical_evidence_interface.png` | Verification-only PV2 component exchanges for baseline selection, module-type census, PCB fit/clearance records, keepout/removal-path records, anomaly disposition and evidence release. |
| Functional allocation / procedure | `SAA-VV-CON-002_functional_allocation_procedure.d2` | `SAA-VV-CON-002_functional_allocation_procedure.png` | Verification-only PV3 allocation of human, equipment, UUT and evidence functions used to inspect/demonstrate the modular-structure constraint. |
| Module-type census chain | `SAA-VV-CON-002_module_type_census_chain.d2` | `SAA-VV-CON-002_module_type_census_chain.png` | Functional chain for counting modeled module instances, classifying Type 1 and Type 2 modules, rejecting extra module families/adapters, and recording pass/fail. |
| 44 mm accommodation / keepout chain | `SAA-VV-CON-002_pcb_accommodation_keepout_chain.d2` | `SAA-VV-CON-002_pcb_accommodation_keepout_chain.png` | Functional chain for inserting/removing `44 mm × 44 mm` gauges or flight PCBs, checking clearance/retention, inspecting keepouts/interference/removal paths, screening cycles, and recording pass/fail. |

The logical components, component exchanges, functions, physical links to test equipment, fit gauges, dummy boards, evidence records and functional chains in this folder are **verification-only** and do not modify the S&A baseline architecture.

## Items under verification

### `v0.1` transition-readiness article

The v0.1 UUT is the reusable structural/module article defined by `S&A/MBSE/v0.1/SAA_v0.1_view1_physical.d2`:

- CanSat Structural Envelope;
- Standard Carrier Module Stack (Type 1), ADS/AMS/OBCC/PDS/ESS Modules;
- Perpendicular Backplane Volume;
- Parachute / Top Module (Type 2);
- stack-screw interfaces, perpendicular backplane slot and backplane clearance.

`v0.1` closure is limited to reusable module readiness: confirm that the stack uses no more than the modeled two module types and that the ADS/AMS/OBCC/PDS standard-module PCB accommodations accept a calibrated `44 mm × 44 mm` dummy PCB or fit gauge without forced fit, with positive measured clearance and an unblocked service/removal path. The ESS module is counted as a Type 1 standard module; if an ESS PCB accommodation is claimed, it must use the same evidence, otherwise the report records the controlled battery-only allocation for ESS.

### `v1.0` flight-readiness article

The v1.0 UUT is the integrated CanSat Assembly defined by `S&A/MBSE/v1.0/SAA_v1.0_view1_physical.d2`, including Standard Carrier Module Stack, ADS/AMS/OBCC/PDS/ESS Modules, ADS/AMS/OBCC/PDS `44 mm × 44 mm` PCBs, ESS Battery Pack, Backplane PCB `100 mm × 28 mm`, ADS/AMS/OBCC/PDS `2 mm 2×6` headers, PDM Servo Connector, Backplane Spine, Parachute / Top Module, Cap, Parachute and Servo. `v1.0` closure requires the integrated as-flown configuration or a documented final-equivalent fit configuration.

## Verification means and allocated functions

| Actor / equipment | Verification-only functions |
|---|---|
| S&A Test Operator | Select v0.1 or v1.0 gate; identify article and baseline copy; count module instances and classify Type 1/Type 2; insert/remove PCB gauges, dummy boards, or flight PCBs using the normal service path; record anomalies. |
| Safety / QA Witness | Witness no-force insertion/removal, type-count classification, calibration/ambient status, clearance measurements, keepout checks, cycle-screen evidence and pass/fail/hold decisions. |
| 44 mm PCB Fit Gauge / Dummy PCB Set | Provide calibrated `44.00 mm × 44.00 mm` gauge boards or dummy PCBs representative of board outline and thickness; identify gauge ID and uncertainty. |
| ADS/AMS/OBCC/PDS Flight PCBs | v1.0 boards used for final integrated fit acceptance where installed and released for handling. |
| Calipers / Feeler Gauges | Measure minimum edge, fastener, component and removal-path clearances and provide expanded uncertainty `U_C`; target resolution is adequate to prove `C_min - U_C > 0`. |
| Keepout / Removal-Path Probe | Check backplane, header, battery, stack screw, top module, cap, parachute and servo interference or blockage around each board path. |
| Insert/Remove Cycle Counter | Record the minimum workshop screen of `N ≥ 3` insert/remove cycles per mandatory accommodation unless a stricter plan is released; cycles are screening only, not reliability trials. |
| Photo / Video Evidence Camera | Capture module type count, board/gauge identity, insertion/removal, clearance/feeler checks, keepout state, anomalies and witness review. |
| Ambient Thermo-Hygrometer | Record temperature and humidity before fit repetitions; hold if outside instrument/material operating range or if ambient drift invalidates clearance interpretation. |
| Evidence Repository | Store controlled report, raw readings, cycle counts, photos/video, gauge/calibration records, pass/fail decisions and anomaly dispositions under `S&A/MBSE/tests/results/SAA-VV-CON-002/`. |

## Procedure definition

### Module-type census inspection chain

1. Select `SAA-v0.1` transition readiness or `SAA-v1.0` flight readiness.
2. Identify article, build/configuration record, baseline copy, operator, witness, evidence repository path and ambient record.
3. Enumerate every module in the stack and top assembly and classify each as either Type 1 standard carrier module or Type 2 parachute/top module.
4. Confirm ADS/AMS/OBCC/PDS/ESS modules are Type 1 standard carrier module instances and the parachute/top module is Type 2.
5. Inspect for extra structural module families, adapters, permanent shims, service-only blockers or undocumented module variants that would increase the module-type count or invalidate the standard accommodation claim.
6. Apply the two-module-type pass/fail constraint and record witness decision and evidence.

### 44 mm PCB accommodation demonstration/inspection chain

1. Select gate and mandatory accommodations: ADS/AMS/OBCC/PDS for v0.1 dummy/gauge readiness and ADS/AMS/OBCC/PDS flight-PCB acceptance for v1.0.
2. Verify fit gauge/dummy PCB or flight PCB identity, outline, thickness/keepout representativeness, instrument calibration, witness identity and ambient conditions.
3. Inspect the module bay, standoffs/screws, backplane/header side, top/battery/stack neighbors and service/removal path before insertion.
4. Insert the `44 mm × 44 mm` gauge/dummy/flight PCB through the intended service path using finger pressure only; no forcing, prying, filing, unapproved shim, temporary removal of unrelated hardware or board flex is allowed.
5. Measure minimum clearances with calipers/feeler gauges and record expanded uncertainty `U_C`. Pass requires `C_min - U_C > 0` for every applicable edge, standoff, keepout, fastener and removal-path location.
6. Verify retention by engaging the intended standoffs/screws or approved retention feature; no rocking, stress, warped print contact, stripped boss or blocked connector/keepout is allowed.
7. Remove the board/gauge through the intended path without snag, blocked removal, scraping, bent pins, contact with the backplane/headers/battery/top module/cap/parachute/servo, or damage.
8. Repeat the insert/remove screen for at least `N ≥ 3` cycles per mandatory accommodation unless a stricter plan is released. Treat repetitions as workmanship screening only.
9. Record pass/fail per accommodation and gate. Any open anomaly, missing evidence, missing calibration, unproven positive clearance, or forced fit is hold/fail until corrected and re-run.

## Pass/fail constraints

Pass only if all applicable constraints below are satisfied:

- The module type count is `≤ 2`: Type 1 Standard Carrier Module and Type 2 Parachute / Top Module only. ADS, AMS, OBCC, PDS and ESS modules count as Type 1 instances; the top/parachute module counts as Type 2. Extra module families, permanent adapters, undocumented shims or structural variants are fail/hold unless the baseline is updated and re-verified.
- For v0.1, ADS/AMS/OBCC/PDS reusable standard-module accommodations accept the calibrated `44 mm × 44 mm` dummy PCB or fit gauge through the intended service path without force, scraping, board flex, filing, unapproved hardware removal or temporary omission.
- For v1.0, ADS/AMS/OBCC/PDS flight PCBs or final-equivalent gauges seat in their standard modules and engage intended retention features without forced fit, stress, warped-print contact, stripped bosses, protrusion, keepout violation or damage.
- For every mandatory accommodation, measured minimum clearance after uncertainty is positive: `C_min - U_C > 0` at edges, standoffs, fasteners, components, backplane/header side, service/removal path and any local keepout defined by the drawing or released fit gauge.
- Retention remains acceptable after the screen: no loose board, rocking beyond intended clearance, missing/stripped fastener, cracked/warped module feature, blocked connector or evidence of stress after insertion/removal.
- No keepout/interference/removal-path blockage is allowed from stack screws, backplane volume/PCB, headers, ESS battery pack, top module, cap, parachute, servo, camera/evidence handling, or temporary fixtures.
- Ambient condition, calibration state, gauge/PCB identity, raw clearance readings, cycle count, photos/video, module-count evidence, witness review and anomaly disposition must be complete.
- Any forced fit, unmeasured or non-positive guard-banded clearance, blocked removal path, wrong module type count, missing calibration/evidence, open anomaly, unapproved substitution, undocumented rework or required re-run not completed is a hold/fail.

## Viewpoints

- **Statistical significance:** Module-type count and PCB accommodation verification are 100% census inspections/demonstrations over every modeled module instance and every mandatory ADS/AMS/OBCC/PDS accommodation in the selected gate. Clearance values are calibrated continuous measurements with uncertainty guard bands. `N ≥ 3` insert/remove repetitions per accommodation are workmanship screens only and do not support a population reliability claim. Any reliability claim requires a separate approved representative-trial/binomial plan per the IVV policy.
- **Fault hardening:** The model explicitly prevents false pass from wrong module type count, hidden third module family, tolerance stack, warped print, undersized or unrepresentative dummy boards, ignored gauge uncertainty, forced board insertion, service-path blockage, backplane/header/battery/top-module interference, stripped or misaligned retention features, blocked removal path, temporary hardware omission, ambiguous photos or evidence-control escape.

## Required report content

The execution report in `S&A/MBSE/tests/results/SAA-VV-CON-002/` should reference this model definition and record execution-specific information:

- model definition revision and baseline copy used;
- article identifier, version, build/configuration record and final-equivalent fit configuration if not fully as-flown;
- operator, witness, equipment IDs, calibration records, fit gauge/dummy/flight PCB IDs and ambient record;
- module-type census table with every module instance and Type 1/Type 2 classification;
- raw clearance measurements, uncertainty values and `C_min - U_C` calculations per accommodation;
- insert/remove cycle counts and any no-force/retention/removal-path observations;
- keepout/interference inspection evidence for backplane/header/battery/stack/top-module/cap/parachute/servo neighbors;
- photo/video evidence IDs and file paths;
- pass/fail/hold rationale by v0.1 and/or v1.0 gate;
- deviations, anomalies, waivers, rework and re-run evidence.

## Assumptions and blockers

- The baseline S&A views contain only physical architecture; this folder adds verification-only PV2, PV3 and functional-chain definitions rather than editing baseline source views.
- `v0.1` is an incremental reusable module readiness gate; it does not by itself close final v1.0 integrated fit unless the report identifies final-equivalent boards and neighboring hardware.
- The mandatory PCB accommodation set is ADS/AMS/OBCC/PDS. ESS is counted as a Type 1 module; if an ESS PCB accommodation is claimed later, this activity must be extended or re-run for that accommodation.
- The default workmanship screen is `N ≥ 3` insert/remove cycles per accommodation. This is a screening assumption, not a reliability-demonstration claim.
- Exact module drawing tolerances, PCB thickness and keepout drawings may be refined before execution. If the released drawings impose stricter limits than `C_min - U_C > 0`, use the stricter limits and update the report/anomaly disposition.
- The gate may be held rather than failed when a discrepancy is correctable by approved rework, model/evidence update, or accepted dependency before flight-readiness closure.
