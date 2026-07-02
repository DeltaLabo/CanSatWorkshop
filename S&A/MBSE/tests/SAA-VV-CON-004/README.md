# SAA-VV-CON-004 — Assembly/printing screw-type, precision, and infill process constraint verification

Model-defined constraint-derived verification activity for the S&A `v0.1` transition-readiness baseline and `v1.0` flight-readiness/final-acceptance baseline.

- **IADT method:** Inspection / Analysis / Testing
- **IVV source category:** Constraint
- **SSIV / development versions:** `SAA-v0.1` printed-process readiness and `SAA-v1.0` final printed/module hardware acceptance.
- **Definition folder:** `S&A/MBSE/tests/SAA-VV-CON-004/`
- **Expected report/evidence folder:** `S&A/MBSE/tests/results/SAA-VV-CON-004/`
- **Primary traceability targets:** modeled Assembly / printing constraint, `SAA-UC-IntegratedAssembly`, `SAA-FE-StructuralLoosening`, `SAA-FE-EnvelopeNonCompliance`, and `SAA-FE-LandingDamage`.
- **References:** IVV (`PM&SE/IVV.md`), SAA-R3 and SAA-R5 as indexed in `S&A/MBSE/tests/references/README.md`.

## Model views

| View | D2 | PNG | Purpose |
|---|---|---|---|
| Baseline copy v0.1 | `baseline/SAA_v0.1_view1_physical.d2` | `baseline/SAA_v0.1_view1_physical.png` | Frozen source context for the v0.1 structural/module/backplane-volume readiness gate and assembly/printing constraint. |
| Baseline copy v1.0 | `baseline/SAA_v1.0_view1_physical.d2` | `baseline/SAA_v1.0_view1_physical.png` | Frozen source context for the v1.0 final assembly with printed modules, stack screws, PCB standoffs/screws, backplane slot/fixture and top-module hardware. |
| Physical/process testbench | `SAA-VV-CON-004_physical_process_testbench.d2` | `SAA-VV-CON-004_physical_process_testbench.png` | PV1 testbench with v0.1 printed modules/coupons, v1.0 final printed/module hardware, screw inventory, printer/build records, calipers/micrometer, torque/cycle tool, ambient meter, operator/reviewer/witness and evidence repository. |
| Logical evidence interface | `SAA-VV-CON-004_logical_evidence_interface.d2` | `SAA-VV-CON-004_logical_evidence_interface.png` | Verification-only PV2 CEs for baseline selection, printer/material batch selection, screw-type census, 15% infill evidence, controlled deviations, dimensional measurements, cycle records, statistical basis, fault-hardening/anomaly records and evidence release. |
| Functional allocation / procedure | `SAA-VV-CON-004_functional_allocation_procedure.d2` | `SAA-VV-CON-004_functional_allocation_procedure.png` | Verification-only PV3 allocation of human, equipment, UUT and evidence functions used to inspect, analyze and test the assembly/printing constraints. |
| Screw-type inventory chain | `SAA-VV-CON-004_screw_type_inventory_chain.d2` | `SAA-VV-CON-004_screw_type_inventory_chain.png` | Functional chain for the max-two self-tapping screw-type census and installed/issued screw traceability. |
| Printer profile / infill chain | `SAA-VV-CON-004_print_profile_and_infill_chain.d2` | `SAA-VV-CON-004_print_profile_and_infill_chain.png` | Functional chain for verifying printer profile, slicer/build logs, 15% infill and controlled-deviation evidence. |
| Critical feature measurement chain | `SAA-VV-CON-004_critical_feature_measurement_chain.d2` | `SAA-VV-CON-004_critical_feature_measurement_chain.png` | Functional chain for measuring critical printed features against the `0.2 mm` precision constraint with uncertainty guard band. |
| Screw/fit cycle fault-hardening chain | `SAA-VV-CON-004_screw_fit_cycle_fault_hardening_chain.d2` | `SAA-VV-CON-004_screw_fit_cycle_fault_hardening_chain.png` | Functional chain for representative screw/fit cycles, torque/cycle records, post-cycle damage/alignment checks and R90/C95 trial scoping if claimed. |

The logical components, component exchanges, functions, physical links to verification means, records and functional chains in this folder are **verification-only** and do not modify the S&A baseline architecture.

## Items under verification

### `v0.1` transition-readiness article

The v0.1 UUT is the printed-process readiness configuration from `S&A/MBSE/v0.1/SAA_v0.1_view1_physical.d2`: Standard Carrier Module Stack (Type 1), ADS/AMS/OBCC/PDS/ESS Modules, Perpendicular Backplane Volume/slot, Parachute / Top Module (Type 2), stack screws and representative printed coupons/screw-boss features from the same printer/material batch. Closure at v0.1 is a process readiness gate: verify screw-type control, 15% infill/build records, `0.2 mm` feature precision and representative screw/boss cycle screening before relying on the printed module process for final assembly.

### `v1.0` flight-readiness article

The v1.0 UUT is the final printed/module hardware used in the integrated CanSat Assembly from `S&A/MBSE/v1.0/SAA_v1.0_view1_physical.d2`: Standard Carrier Module Stack, ADS/AMS/OBCC/PDS/ESS Modules, ADS/AMS/OBCC/PDS PCBs, ESS Battery Pack, Backplane PCB and slot/fixture context, stack screws, PCB standoffs/screws, battery fixture, top module, cap, parachute and servo. Closure at v1.0 requires final part/build traceability, dimensional acceptance and representative assembly-cycle fault hardening on the final or final-equivalent hardware.

## Closure-record print/material/screw/proof criteria (`SAA-BLK-006`)

These criteria select definition values for later execution/reporting; they do not state that any printed article has passed.

- **Material:** PLA is the selected structural print material due to availability. Execution records shall capture filament supplier/type/color if relevant, material lot if available, printer ID, nozzle, slicer/profile version, build date, orientation, and reprint history.
- **Layer / precision / infill policy:** preserve the existing controlled `0.2 mm` print precision/layer policy and `15%` fill/infill. The fallback `0.2 mm` layer height and `10%` infill applies only if a future accepted source has no controlled value.
- **Minimum print-profile evidence:** accepted parts need slicer/G-code/build evidence for material, layer height, infill/fill, wall/perimeter count, top/bottom layers, support/interface settings where relevant, and part IDs. If wall/perimeter/top-bottom settings are not controlled by a released profile, require at least `2` walls/perimeters and at least `3` top/bottom layers for accepted structural parts or record a controlled deviation.
- **Dimensional precision:** critical printed features shall satisfy `|measured - nominal| + U <= 0.2 mm` unless a released drawing has a stricter tolerance.
- **Screw torque:** exact torque shall be released by screw type or coupon characterization before execution. Pending that release, use a torque-limited hand tool, record torque for each screw family, and do not exceed `0.20 N·m` for self-tapping screws into PLA without coupon evidence. Conservative default target ranges are `0.05–0.10 N·m` for small M2-class screws and `0.10–0.20 N·m` for M2.5-class screws; revise if the controlled screw type differs.
- **Screw/fit cycles:** retain the existing workmanship screen of at least `3` representative coupons/modules per printer/material batch and no stripped boss, boss pull-out, crack, delamination, weak-infill crushing, torque damage, warped slot, loose standoff, or alignment loss. Use `29/29` independent zero-failure trials only if an R90/C95 screw-hole reliability claim is made.
- **Retention proof-loads:** for non-destructive retention proof checks, use `20 g` equivalent inertial load in each relevant axis/orientation for the retained item mass, with minimum applied proof loads of `20 N` for the ESS battery pack/battery fixture and `10 N` for individual PCBs, backplane/connector retention points, or top-module/servo-connector features unless a released fixture/test definition gives a stronger value. Do not overload electronics, Li-ion cells, or connectors beyond safe fixture limits; use surrogate masses/fixtures if needed and record limitations.

## Verification means and allocated functions

| Actor / equipment | Verification-only functions |
|---|---|
| S&A Test Operator | Select v0.1/v1.0 gate; identify article, printed batch, baseline copy and evidence folder; inspect screw tray/BOM and installed screw locations; execute representative screw/fit cycles; record anomalies and re-run needs. |
| Manufacturing / Process Reviewer | Review slicer profile, printer setup, PLA/material lot and build logs; verify `0.2 mm` layer/precision, `15%` infill/fill, walls/perimeters, top/bottom layers or approved deviations; review batch drift, reprints and process evidence. |
| QA Witness | Witness setup, calibration, ambient records, screw/fit cycles, no-strip/no-crack/alignment checks and final pass/fail/hold decisions. |
| Controlled Screw Inventory / BOM Tray | Provide controlled self-tapping screw records and support the type count by diameter, pitch/thread form, length, head/drive, material/coating and supplier. |
| Printer Profile / Build Record Set | Provide slicer profile, G-code summary and build evidence for PLA material, layer height, `15%` fill/infill, wall/perimeter count, top/bottom layers, support/interface settings where relevant, material lot, printer ID, nozzle/profile version, build date/time, orientation, reprint history and affected part IDs. |
| Calipers / Micrometer / Feature Gauges | Measure screw bosses/holes, PCB standoffs, PCB bays, backplane slots, stack alignment and top-module interfaces; calculate `|error| + U` against `0.2 mm`. |
| Torque Driver / Insert-Cycle Tool and Cycle Counter | Apply controlled screw insertion/removal or representative assembly/fit cycles using released screw-type torque or coupon-derived limits; pending release, use the default target ranges and `0.20 N·m` self-tapping-into-PLA ceiling above. Record torque setting, tool ID, hole ID, screw type and cycle/trial count. |
| Proof-load Fixture / Load Cell / Surrogate Masses | Support non-destructive retention proof checks at `20 g` equivalent inertial load with minimum `20 N` for the ESS battery pack/fixture and `10 N` for PCBs, backplane/connector retention points, or top-module/servo-connector features, within safe electronics/cell/connector limits. |
| Ambient Thermo-Hygrometer | Record temperature and humidity before measurement, proof checks or cycle repetitions; hold if ambient/material/tool state invalidates measurement or process interpretation. |
| Photo / Video Evidence Camera | Capture screw inventory, profile/build evidence, measurement setup, cycle execution, damage/alignment checks, anomalies and witness review. |
| Evidence Repository | Store controlled report, raw readings, calculations, profiles/build logs, screw census, photos/video, torque/cycle/proof-load records, statistical-basis statement and anomaly dispositions under `S&A/MBSE/tests/results/SAA-VV-CON-004/`. |

## Procedure definition

### Screw-type inventory inspection

1. Select `SAA-v0.1`, `SAA-v1.0` or both gates and identify the frozen baseline copy used.
2. Collect controlled screw BOM, supplier data, tray labels and installed screw-location list for stack screws, PCB standoffs/screws and top-module locations.
3. Classify self-tapping screw types by controlled diameter, pitch/thread form, length, head/drive, material/coating and supplier record.
4. Count unique self-tapping screw types issued or installed for the selected gate.
5. Inspect installed or final-equivalent screws against the controlled inventory and location map.
6. Pass requires the self-tapping screw type count to be `≤ 2` and every screw to map to those types. Any third type, unapproved substitution, mixed bin, missing label or ambiguous evidence is hold/fail until corrected and re-inspected.

### Printer profile / infill evidence analysis

1. Identify printer, PLA supplier/type/color, material lot if available, nozzle/profile version, part IDs, orientation, build date, reprint history and batch boundaries.
2. Select at least `3` coupons/modules per printer/material batch for process-screen traceability; v1.0 final parts must trace to controlled build records or an accepted final-equivalent surrogate rationale.
3. Collect slicer profile, G-code summary, printer log, material/build plate records and support/interface settings where relevant.
4. Verify every accepted printed module, top-module part, screw-boss coupon or accepted surrogate has controlled evidence showing `0.2 mm` layer/precision policy and `15%` print fill/infill. Use the fallback `0.2 mm` layer height and `10%` infill only for a future accepted source with no controlled value.
5. Verify profile/build evidence includes wall/perimeter count and top/bottom layers. If these settings are not controlled by a released profile, require at least `2` walls/perimeters and at least `3` top/bottom layers for accepted structural parts or record a controlled deviation.
6. Treat non-`15%` infill or non-PLA material as acceptable only when an approved controlled deviation exists before acceptance, tied to affected part IDs and re-verification scope.
7. Record missing logs, unapproved infill/profile/material deviation, part mix-up, material substitution, weak-infill concern, batch drift and any required hold/re-run.

### Critical feature measurement / precision testing

1. Identify critical features from the model and released drawings: screw bosses/holes, PCB standoff features, `44 mm` PCB bay interfaces, backplane slot/fixture features, stack alignment and top-module interfaces.
2. Verify calipers/micrometer/gauge identity, calibration status, nominal values and expanded uncertainty `U` method.
3. Record ambient temperature/humidity before measurement repetitions.
4. Measure v0.1 process coupons/modules and v1.0 final/final-equivalent printed features. Include at least `3` coupons/modules per printer/material batch for process-screen coverage.
5. Calculate `|measured - nominal| + U` for every critical feature.
6. Pass requires `|measured - nominal| + U ≤ 0.2 mm` unless a released drawing imposes a stricter tolerance. Missing nominal, unguarded uncertainty, uncalibrated tool, warped feature, blocked fit or open anomaly is hold/fail until corrected and re-measured.

### Representative screw/fit-cycle testing

1. Select representative screw bosses, holes, modules, coupons and v1.0 final hardware locations for the selected gate.
2. Verify allowed screw type, torque driver identity/calibration and controlled torque/tool setting. Exact torque shall be released by screw type or coupon characterization before execution; pending that release, use a torque-limited hand tool, do not exceed `0.20 N·m` for self-tapping screws into PLA without coupon evidence, and use default targets `0.05–0.10 N·m` for M2-class or `0.10–0.20 N·m` for M2.5-class screws unless the controlled screw type differs.
3. Record ambient conditions before repetitions.
4. Pre-inspect boss condition, infill exposure, slot straightness and stack/backplane/PCB/top-module alignment baseline.
5. Perform controlled screw insertion/removal or representative assembly/fit cycles without forcing, prying, filing, unapproved shim or temporary hardware omission.
6. Record torque setting, screw type, hole ID, cycle/trial count and observations.
7. Inspect for stripped bosses, boss pull-out, cracks, delamination, weak-infill crushing, torque damage, warped slot, loose standoff and loss of alignment.
8. For a process screen, use at least `3` representative coupons/modules per printer/material batch. Use `29` independent representative zero-failure screw-hole trials only if the report claims R90/C95 reliability.
9. Pass requires no strip/crack/damage/alignment loss and complete evidence. Stop and hold on any damage, torque above the released/coupon/default limit, missing torque record or open anomaly.

### Non-destructive retention proof-load definition

1. Identify retained item, mass or surrogate mass, load path, fixture adapter, safe electronics/cell/connector limits, axis/orientation set, proof-load equipment ID/calibration and witness.
2. Use `20 g` equivalent inertial load in each relevant axis/orientation for the retained item mass, with minimum applied proof loads of `20 N` for the ESS battery pack/battery fixture and `10 N` for individual PCBs, backplane/connector retention points, or top-module/servo-connector features unless a released fixture/test definition gives a stronger value.
3. If direct loading could damage electronics, Li-ion cells or connectors beyond safe limits, use surrogate masses/fixtures and record the limitation and representativeness rationale.
4. Record load value, duration/hold method if defined by the fixture procedure, pre/post condition, witness marks, movement/gap observations, and any anomaly. Ambiguous or unsafe proof-load evidence is hold, not pass.

## Pass/fail constraints

Pass only if all applicable constraints below are satisfied:

- **Screw-type limit:** self-tapping screw type count is `≤ 2`; every issued or installed self-tapping screw maps to one of those controlled types. Third type, unapproved substitute, mixed untraceable bin or missing location map is hold/fail.
- **Material / layer / infill / print-fill:** accepted structural printed parts use PLA unless a controlled deviation is approved. Printer/profile/build records show the preserved `0.2 mm` layer/precision policy and `15%` infill/fill for every accepted printed module, top-module part, screw-boss coupon or accepted surrogate. The fallback `0.2 mm` / `10%` applies only to a future accepted source with no controlled value. Non-PLA material or non-`15%` infill requires controlled pre-acceptance deviation, part-ID scope and re-verification rationale.
- **Profile completeness:** accepted part evidence includes material, layer height, infill/fill, wall/perimeter count, top/bottom layers, support/interface settings where relevant, and part IDs. If wall/perimeter/top-bottom settings are not controlled by a released profile, accepted structural parts require at least `2` walls/perimeters and at least `3` top/bottom layers or a controlled deviation.
- **Print precision:** every critical printed feature satisfies `|measured - nominal| + U ≤ 0.2 mm` unless stricter drawing tolerance applies. Critical features include screw bosses/holes, PCB standoff features, 44 mm PCB bay interfaces, backplane slot/fixture features, stack alignment and top-module interfaces.
- **Representative screw/fit cycles:** controlled torque/tool cycles use released screw-type torque or coupon-derived limits. Pending that release, self-tapping screws into PLA shall not exceed `0.20 N·m` without coupon evidence, with default targets `0.05–0.10 N·m` for M2-class and `0.10–0.20 N·m` for M2.5-class screws unless the controlled screw type differs. Cycles produce no stripped boss, crack, delamination, weak-infill crushing, boss pull-out, torque damage, warped/blocked slot, loose standoff, blocked backplane/PCB fit or loss of stack/top-module alignment.
- **Retention proof-loads:** non-destructive retention proof checks use `20 g` equivalent inertial load in each relevant axis/orientation, with minimum `20 N` for the ESS battery pack/battery fixture and `10 N` for individual PCBs, backplane/connector retention points, or top-module/servo-connector features unless stronger released values exist. Proof checks shall not overload electronics, Li-ion cells or connectors beyond safe fixture limits; use surrogate masses/fixtures when needed and record limitations.
- **Evidence control:** baseline copy, article IDs, part/build IDs, PLA material and printer/material batch IDs, screw inventory, equipment calibration, ambient record, raw measurements, uncertainty calculations, cycle/torque/proof-load records, photos/video, witness review and anomaly/waiver/rework dispositions are complete.
- **Hold/fail triggers:** missing build logs, unapproved material/profile/infill deviation, missing wall/top-bottom evidence without default/deviation, torque above released/coupon/default limits, uncalibrated instruments, missing nominal values, unguarded measurements, forced fit, unsafe or ambiguous proof-load evidence, open anomaly, required re-run not completed, material/printer batch drift with no disposition, or evidence-control escape.

## Viewpoints

- **Statistical significance:** Screw-type verification is a 100% inventory/type census for the selected gate. Print-process screening includes at least `3` coupons/modules per printer/material batch. Critical-feature checks are continuous measurements with expanded uncertainty guard bands. Routine screw/fit-cycle repetitions are workmanship screens only. Claiming R90/C95 screw-hole reliability requires `29` independent representative zero-failure screw-hole trials with an approved independence rationale.
- **Fault hardening:** The modeled activity explicitly prevents false pass from hidden third screw types, stripped bosses, boss pull-out, cracked/delaminated prints, weak infill, warped slots, torque damage, wrong screw type, unapproved build-profile deviation, material/printer/batch drift, post-cycle misalignment, uncalibrated tools, ignored measurement uncertainty, ambiguous photos and evidence-control escape.

## Required report content

The execution report in `S&A/MBSE/tests/results/SAA-VV-CON-004/` should reference this model definition and record execution-specific information:

- model definition revision and baseline copy used;
- selected gate (`v0.1`, `v1.0` or both), article identifiers, final-equivalent rationale if applicable and configuration/build records;
- operator, process reviewer, witness, equipment IDs, calibration records and ambient temperature/humidity;
- screw BOM/inventory, type classification, installed location map, photos and `≤2` type-count result;
- printer/slicer/profile/G-code/build-log evidence, PLA supplier/type/color, material lot if available, printer ID, nozzle/profile version, build date, orientation, reprint history, batch IDs, `0.2 mm` layer/precision, `15%` infill/fill, wall/perimeter count, top/bottom layers, support/interface settings where relevant and any controlled deviations;
- critical-feature list, nominal source, raw measurements, expanded uncertainty values and `|error| + U` calculations;
- screw/fit-cycle plan, released or coupon-derived torque settings/default target range, cycle/trial counts, hole IDs, pre/post damage and alignment observations;
- proof-load plan and records, including retained item mass or surrogate rationale, `20 g` equivalent load calculation, minimum `20 N` or `10 N` threshold used, fixture/load-cell limits, axes/orientations and pre/post condition;
- statistical-basis statement, including whether evidence is process screen only or includes a `29/29` R90/C95 screw-hole claim;
- pass/fail/hold rationale by gate;
- deviations, anomalies, waivers, rework, reprints, re-measurements and re-run evidence.

## Assumptions and blockers

- The baseline S&A views contain only physical architecture; this folder adds verification-only PV2, PV3 and functional-chain definitions rather than editing baseline source views.
- `v0.1` is an incremental structural/module/backplane-volume readiness gate; it screens the printed process and representative coupons/modules but does not alone close final v1.0 flight acceptance.
- PLA is the selected material for accepted structural printed parts unless a controlled deviation is approved.
- Exact screw torque limits shall be released by screw type or coupon characterization before execution. Pending that release, the default target ranges and `0.20 N·m` self-tapping-into-PLA ceiling above control affected checks; missing torque records or torque above the controlled limit are hold/fail.
- Screw-hole geometry tolerances, material/printer profile details and drawing nominals are assumed to be released before execution. If absent and no fallback/deviation is defined above, the report records a hold rather than a pass for affected checks.
- `15%` infill is interpreted as the controlled slicer/build setting for accepted printed parts; a controlled deviation may pass only when approved and re-verified over the affected scope.
- The default process-screen population is at least `3` coupons/modules per printer/material batch. `29` independent screw-hole trials are required only if a R90/C95 screw-hole reliability claim is made.
- The gate may be held rather than failed when a discrepancy is correctable by approved rework, reprint, model/evidence update or accepted deviation before flight-readiness closure.
