# SAA-VV-FC-001 — Integrated assembly fit, mass, envelope, and module accommodation scenario

Model-defined verification activity for the S&A `v1.0` flight-readiness baseline. This activity turns the candidate integrated fit/check scenario into Capella-style verification-only views for report-by-reference.

- **IADT method:** Demonstration / Inspection
- **IVV source category:** Functional chain / scenario
- **SSIV / development version:** `SAA-v1.0` flight readiness. `v0.1` is copied as incremental context only; the executable scenario is defined for the full `v1.0` as-flown article.
- **Definition folder:** `S&A/MBSE/tests/SAA-VV-FC-001/`
- **Expected report/evidence folder:** `S&A/MBSE/tests/results/SAA-VV-FC-001/`
- **Primary traceability targets:** `SAA-UC-IntegratedAssembly`, `SAA-UC-BackplaneIntegration`, `SAA-UC-ParachuteClearance`, `SAA-FE-EnvelopeNonCompliance`, `SAA-FE-MassNonCompliance`, `SAA-FE-BackplaneMisMate`, and the modeled envelope, mass, module, backplane, and assembly constraints.
- **References:** IVV (`PM&SE/IVV.md`), SAA-R1, SAA-R3, SAA-R4, and SAA-R5 as indexed in `S&A/MBSE/tests/references/README.md`.

## Model views

| View | D2 | PNG | Purpose |
|---|---|---|---|
| Baseline copy v0.1 | `baseline/SAA_v0.1_view1_physical.d2` | `baseline/SAA_v0.1_view1_physical.png` | Frozen incremental structural/module/backplane-volume context. |
| Baseline copy v1.0 | `baseline/SAA_v1.0_view1_physical.d2` | `baseline/SAA_v1.0_view1_physical.png` | Frozen source context for the v1.0 flight-readiness activity. |
| v1.0 physical testbench | `SAA-VV-FC-001_v1.0_physical_testbench.d2` | `SAA-VV-FC-001_v1.0_physical_testbench.png` | PV1 testbench with UUT, can/envelope gauge, caliper/height gauge, scale, PCB fit gauges, camera, ambient meter, operator/witness, evidence repository, physical links, and constraints. |
| Logical measurement/evidence exchange | `SAA-VV-FC-001_logical_measurement_evidence_exchange.d2` | `SAA-VV-FC-001_logical_measurement_evidence_exchange.png` | Verification-only PV2 component exchanges for measurements, configuration records, fit status, anomaly status, QA decision, and evidence release. |
| Functional allocation / procedure | `SAA-VV-FC-001_functional_allocation_procedure.d2` | `SAA-VV-FC-001_functional_allocation_procedure.png` | Verification-only PV3 allocation of operator, witness, equipment, UUT, acceptance-gate, and repository functions. |
| Integrated fit/mass/envelope chain | `SAA-VV-FC-001_fit_mass_envelope_chain.d2` | `SAA-VV-FC-001_fit_mass_envelope_chain.png` | Main Demonstration / Inspection functional chain. |
| Anomaly disposition chain | `SAA-VV-FC-001_anomaly_disposition_chain.d2` | `SAA-VV-FC-001_anomaly_disposition_chain.png` | Functional chain for exceptions, rework/waiver/hold/fail disposition, and required re-run. |

The logical components, component exchanges, functions, physical links to test equipment, and functional chains in this folder are **verification-only** and do not modify the S&A baseline architecture.

## Item under verification

The UUT is the full `v1.0` CanSat Assembly in as-flown configuration, including:

- Standard Carrier Module Stack (Type 1) with ADS, AMS, OBCC, PDS and ESS Modules;
- ADS/AMS/OBCC/PDS `44 mm × 44 mm` PCBs;
- ESS Battery Pack;
- Backplane PCB `100 mm × 28 mm`, two-layer, with ADS/AMS/OBCC/PDS `2 mm 2×6` headers, PDM Servo Connector and Backplane Spine;
- Parachute / Top Module (Type 2), Cap, Parachute and Servo.

## Verification means and allocated functions

| Actor / equipment | Verification-only functions |
|---|---|
| S&A Test Operator | Identify article, build record and baseline copy; confirm full as-flown configuration; operate can gauge, caliper/height gauge, scale and PCB fit gauges; inspect backplane/cap/parachute/servo/battery coexistence; record anomalies. |
| QA Witness | Witness setup, calibration status, full-configuration state, measurements and fit/no-force observations; approve pass/fail/hold. |
| 355 ml Envelope / Can Gauge | Demonstrate free fit within the modeled `Ø66.0 mm × H122.0 mm` envelope without force. |
| Calibrated Caliper / Height Gauge | Measure maximum diameter and maximum height and report expanded uncertainty `U_D` and `U_H`. |
| Calibrated Scale | Measure total as-flown mass and report expanded uncertainty `U_M`; target instrument resolution/uncertainty is `≤0.1 g` unless a better calibration record is used. |
| PCB Fit Gauges / Dummy PCBs | Verify `44 mm × 44 mm` PCB accommodation for all Type 1 standard modules without forced fit, bending, blocked standoffs, or visible stress. Installed flight PCBs may serve as the fit article when access and evidence are adequate; an ESS battery-module accommodation check may use controlled pre-closure fit-gauge/build-record evidence if the final battery installation blocks direct gauge insertion. |
| Calibrated Camera / Evidence Light Box | Capture configuration, gauge, measurement and anomaly evidence. |
| Ambient Thermo-Hygrometer | Record workshop temperature and humidity before checks; flag conditions that could affect measurement or evidence quality. |
| Evidence Repository | Store controlled report, raw readings, uncertainty values, photos/video, calibration IDs, ambient record, witness decision and anomaly dispositions under `S&A/MBSE/tests/results/SAA-VV-FC-001/`. |

## Demonstration / inspection procedure definition

1. Identify the `v1.0` article, build/configuration record, baseline copy, operator, witness, instrument IDs and calibration status.
2. Confirm the UUT is in full as-flown configuration: battery, parachute, cap, servo, backplane, headers, PCBs, fixtures and stack hardware installed. No temporary omissions are allowed for a pass.
3. Record ambient temperature/humidity and any handling condition that could affect measurement or evidence quality.
4. Verify `44 mm × 44 mm` PCB accommodation for all Type 1 standard modules using installed flight PCBs, controlled dummy gauges, and/or controlled pre-closure fit-gauge/build-record evidence for any ESS battery-module cavity that is blocked in the final configuration. Record any forced fit, bending, blocked standoff, stress, or access limitation as an anomaly.
5. Inspect the integrated backplane, headers, PDM servo connector, cap, parachute, servo, battery and stack for coexistence and no integrated interference.
6. Demonstrate free fit in the `355 ml` can/envelope gauge without force or external exception.
7. Measure maximum diameter and height with calibrated instruments; record raw values and expanded uncertainties `U_D` and `U_H`.
8. Measure total as-flown mass with the calibrated scale; record raw value and expanded uncertainty `U_M`.
9. Capture photos/video sufficient to bind the article configuration, measurement setup, gauge use, instrument readings and any anomalies to the report.
10. Apply the pass/fail constraints below. If any exception occurs, execute the anomaly disposition chain and re-run affected checks after approved rework before claiming pass.
11. QA witness approves pass/fail/hold and the evidence repository releases the report-by-reference package.

## Pass/fail constraints

Pass only if all of the following are true for the final `v1.0` as-flown article:

- maximum outside diameter plus expanded uncertainty satisfies `D_max + U_D ≤ 66.0 mm`;
- maximum height plus expanded uncertainty satisfies `H_max + U_H ≤ 122.0 mm` using the closure-record S&A height authority; any later project authority-selected stricter competition limit supersedes this value;
- mass satisfies `measured mass + U_M < 350.0 g`;
- all Type 1 standard modules have verified `44 mm × 44 mm` PCB accommodation, with installed ADS/AMS/OBCC/PDS flight PCBs or controlled fit gauges seated without forced fit, PCB bending, blocked standoffs, visible stress, or unapproved access limitation, and any ESS battery-module accommodation evidence bound to controlled pre-closure fit-gauge/build records;
- backplane PCB remains within its `100 mm × 28 mm` allocation, is seated/mated to headers/connectors, and does not create protrusion/interference;
- cap, parachute, servo, battery, standard stack, backplane and harness/connector geometry coexist with no integrated interference;
- instrument calibration status, ambient record, raw readings, uncertainty values, photos/video, and witness review are complete;
- every anomaly, waiver, rework or deviation is closed with approved disposition and any affected check has been re-run in full as-flown configuration.

Fail or hold for any guard-band exceedance, forced fit, missing/removed flight item, temporary omission, external protrusion exception, missing evidence, expired/unknown calibration affecting a result, unresolved interference, unresolved measurement/configuration ambiguity, or unapproved anomaly disposition.

## Viewpoints

- **Statistical significance:** This is a 100% measurement/demonstration of the final `v1.0` article. Diameter, height and mass are continuous measurements; the report shall retain raw readings and expanded uncertainty values. The activity makes no sampling, population reliability, or repeated fit-cycle reliability claim.
- **Fault hardening:** The modeled chains intentionally prevent false pass caused by removing the battery, parachute, cap, servo, backplane, headers, PCBs, screws or protruding items; using alternate envelopes or gauge exceptions; ignoring uncertainty guard bands; accepting forced PCB/module fit; overlooking backplane/cap/parachute/servo interference; or losing measurement/evidence traceability.

## Required report content

The execution report in `S&A/MBSE/tests/results/SAA-VV-FC-001/` should reference this model definition and record only execution-specific information:

- model definition revision and baseline copy used;
- inspected article identifier, version and build/configuration record;
- operator, witness, instrument IDs, calibration records and ambient record;
- raw diameter, height and mass readings, uncertainty values and guard-band calculations;
- module/PCB fit observations by module and any dummy-gauge identifiers;
- final configuration/coexistence observations for backplane, cap, parachute, servo, battery and stack;
- evidence IDs and file paths for photos/video and measurement records;
- pass/fail/hold rationale;
- deviations, anomalies, waivers, rework and re-run evidence.

## Assumptions and execution notes

- The executable scenario is for `SAA-v1.0`; `v0.1` is retained as copied context because it lacks the flight PCBs/backplane/battery/parachute hardware needed for this integrated final-article demonstration.
- The closure record confirms the modeled height limit `122.0 mm` as the S&A authority unless a later project authority adopts a stricter competition requirement before test.
- The closure record controls the mass policy as actual total mass `<350.0 g` with a measurement uncertainty guard band: `measured mass + U_M < 350.0 g`. If `U_M = 0.1 g`, the indicated mass must be `<349.9 g`; otherwise use the reported expanded uncertainty.
- The gate may be placed on hold rather than failed when a discrepancy is correctable but not yet dispositioned.
