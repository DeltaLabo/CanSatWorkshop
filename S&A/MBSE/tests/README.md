# S&A MBSE IVV-aligned verification plan

Planning artifact for the Capella/D2 physical views in `S&A/MBSE`. The model remains the source of truth; this file inventories the current model and identifies candidate verification activities to be modeled in a later test-definition pass. No Capella/D2 diagrams are modified by this plan.

Project-wide IVV conventions, evidence paths, statistical policy, fault semantics, and report-by-reference rules are defined in [`../../../PM&SE/IVV.md`](../../../PM&SE/IVV.md). Evidence for any activity below should be stored under `results/<activity-id>/` in this `tests/` folder unless a campaign-level folder is later agreed.

## 1. SSIV / development-version assumptions

- **Assumed baselines:** S&A physical integration views `v0.1` and `v1.0`, inferred from the D2 folder names and file names.
- **Primary planning baseline:** `SAA-v1.0`, because it is the integrated assembly view containing the subsystem PCBs, battery pack, backplane, PDM servo connector, cap, parachute and servo. `v0.1` is retained as historical/early physical-context coverage.
- **System-level campaign ambiguity:** no separate SSIV/campaign identifier was found in the S&A model files. Confirm whether this plan is for workshop acceptance, protoflight, qualification, or final flight acceptance.
- **Modeling scope:** current S&A D2 files are physical views only. They do not model logical components, functions, component exchanges, or functional chains. This plan therefore includes explicit gap-analysis activities for those IVV categories rather than inventing detailed test-definition diagrams in the planning stage.

## 2. Views read

- `v0.1/SAA_v0.1_view1_physical.d2`: early physical structure with structural envelope, standard carrier stack, backplane volume, parachute/top module, constraints on module types, backplane allowance and assembly/printing.
- `v1.0/SAA_v1.0_view1_physical.d2`: integrated assembly with ADS/AMS/OBCC/PDS PCBs, ESS battery pack, backplane PCB, headers, PDM servo connector, cap, parachute and servo.

## 3. Reference set used

No new external research was performed. References are the existing corpus in `tests/references/` plus the project IVV plan.

| Ref ID | Local source |
|---|---|
| IVV | `../../../PM&SE/IVV.md` |
| SAA-R1 | CanSat size/mass/context artifacts: ESA, Andøya, Nordic ESERO, Crown 355 ml can dimensions |
| SAA-R2 | Drop, vibration and environmental artifacts: ASTM D5276, CanSat environmental template, GSFC-STD-7000B, NASA SSRI, INSTAR vibration |
| SAA-R3 | Additive manufacturing/FDM artifacts: ISO/ASTM 52902, Hubs FDM settings, infill-density literature |
| SAA-R4 | PCB/backplane and signal-integrity artifacts: IPC design-rule overviews and UM10204 I2C artifacts |
| SAA-R5 | Reliability demonstration artifacts: ReliaSoft and sample-size planning extracts |

## 4. Planning inventory from the model

### 4.1 Physical components

Modeled S&A physical components include: CanSat Structural Envelope / CanSat Assembly; Standard Carrier Module Stack (Type 1); Parachute / Top Module (Type 2); ADS Module and `44 mm × 44 mm` ADS PCB; AMS Module and `44 mm × 44 mm` AMS PCB; OBCC Module and `44 mm × 44 mm` OBCC PCB; PDS Module and `44 mm × 44 mm` PDS PCB; ESS Module and ESS Battery Pack; Perpendicular Backplane Volume; Backplane PCB `100 mm × 28 mm` two-layer stackup; Backplane Spine; `2 mm 2×6` ADS/AMS/OBCC/PDS headers; PDM Servo Connector; Cap; Parachute; Servo.

### 4.2 Physical links

Modeled S&A physical links include: stack screws; PCB standoffs/screws; perpendicular backplane slot; perpendicular fixture and header mating; backplane clearance; battery fixture; backplane fixture + servo connector.

### 4.3 Component exchanges

No `[CE]` component exchanges are modeled in the S&A views. However, constraints reference 5 V, 3.3 V, testpoints, low-capacitance SPI/I2C/UART and pin-interface behavior. These are treated as a modeling gap requiring later CE/interface definition or explicit cross-reference to subsystem models.

### 4.4 Logical components, allocated functions and chains

No `[LC]`, `[F]`, `[FE]` or functional-chain views are modeled in the S&A folder. Physical fit, structural retention, backplane mating and deployment-clearance scenarios are therefore candidate verification activities that should be modeled later if S&A is to own them as scenarios.

### 4.5 Constraints

- `355 ml` can envelope: diameter `6.6 cm`, height `12.2 cm`, total mass `<350 ±0.1 g`, withstand landing impact.
- Modular structure: maximum two module types; each standard module accommodates a `44 mm × 44 mm` PCB.
- Backplane allowance: perpendicular PCB allocation, `100 mm × 28 mm`, two-layer, `2 mm 2×6` headers and pin interface, `5.0 ±0.1 V`, `3.3 ±0.1 V`, testpoints, low-capacitance fast lines, ERC/DRC clean.
- Backplane PCB: defined pin interface, rails/testpoints/low-capacitance SPI/I2C/UART, ERC/DRC clean.
- Assembly/printing: max two self-tapping screw types, `0.2 mm` print precision, `15%` infill.

### 4.6 Traceability targets currently available

The S&A views do not contain explicit mission, capability, use-case, or feared-event nodes. Candidate trace targets used below are provisional: `SAA-UC-IntegratedAssembly`, `SAA-UC-BackplaneIntegration`, `SAA-UC-ParachuteClearance`, `SAA-FE-EnvelopeNonCompliance`, `SAA-FE-MassNonCompliance`, `SAA-FE-BackplaneMisMate`, `SAA-FE-StructuralLoosening`, `SAA-FE-LandingDamage`, and the modeled constraints listed above.

## 5. Candidate verification activities

Every activity below is a planning candidate. Detailed procedures, test means, stimuli, expected behavior, and pass/fail constraints should be modeled later under the `capella-pa-tests-definition.md` workflow before execution evidence is treated as final.

| Verification activity ID | SSIV / version | Model element(s) covered | IVV source category | IADT method | Traceability target | Relevant references | Viewpoints: statistical significance and fault hardening | Preliminary pass/fail criteria or constraint candidates | Expected diagram/report location | Status |
|---|---|---|---|---|---|---|---|---|---|---|
| SAA-VV-PC-001 | SAA v0.1/v1.0; primary v1.0 | All physical components in §4.1 | Component/link | Inspection | `SAA-UC-IntegratedAssembly`; `SAA-FE-EnvelopeNonCompliance`; `SAA-FE-StructuralLoosening` | IVV, SAA-R1-R4 | Stat: 100% inspection of each integrated article. Fault hardening: wrong module type, wrong PCB size, missing battery restraint, cap/parachute/servo interference, unmodeled extra module type. | Every modeled PC is present, correctly located, correctly identified, and dispositioned; standard modules, top module, PCBs, backplane, battery, cap, parachute and servo match the model. | Future model definition: `tests/definitions/SAA-VV-PC-001`; report/evidence: `tests/results/SAA-VV-PC-001/` | Candidate; checklist definition pending |
| SAA-VV-PL-001 | SAA v0.1/v1.0; primary v1.0 | All physical links in §4.2 | Component/link | Inspection | `SAA-UC-IntegratedAssembly`; `SAA-UC-BackplaneIntegration`; `SAA-FE-BackplaneMisMate`; `SAA-FE-StructuralLoosening` | IVV, SAA-R2-R4 | Stat: 100% link inspection; pre/post environmental checks. Fault hardening: loose screws, stripped bosses, header misalignment, battery fixture slip, backplane clearance interference, servo connector unseat. | Stack screws, PCB standoffs/screws, backplane slot/fixture/header mating, battery fixture, backplane clearance and servo connector are present and retain/alignment-check as modeled. | Future model definition: `tests/definitions/SAA-VV-PL-001`; report/evidence: `tests/results/SAA-VV-PL-001/` | Candidate; retention/torque criteria pending |
| SAA-VV-CE-001 | SAA v1.0 | Missing but implied power/signal interfaces: 5 V, 3.3 V, pin interface, testpoints, SPI/I2C/UART, PDM servo connector | Component exchange | Analysis | `SAA-UC-BackplaneIntegration`; `SAA-FE-BackplaneMisMate` | IVV, SAA-R4 | Stat: 100% net/interface review; automated frame/message runs may support protocol confidence but are not modeled yet. Fault hardening: swapped pinout, excessive capacitance/rise time, missing testpoint, voltage rail short/open. | Before final definition, add S&A-owned CEs or cross-reference subsystem CE definitions. Backplane pinout, rail ownership, signal direction, testpoint access and low-capacitance criteria must be consistent with model constraints. | Future model definition: `tests/definitions/SAA-VV-CE-001`; report/evidence: `tests/results/SAA-VV-CE-001/` | Candidate; **blocked by CE modeling gap** |
| SAA-VV-ALLOC-001 | SAA v1.0 | Missing logical components/functions/allocations for structure, backplane, fit and deployment clearance | Allocation | Analysis | `SAA-UC-IntegratedAssembly`; `SAA-UC-BackplaneIntegration`; `SAA-UC-ParachuteClearance` | IVV, SAA-R1-R4 | Stat: 100% modeling review. Fault hardening: ambiguous ownership of backplane, harness, retention and deployment-clearance functions. | Either add logical/functional allocation views for S&A-owned integration functions or explicitly state that subsystem models own all behavior and S&A owns physical constraints only. | Future model definition: `tests/definitions/SAA-VV-ALLOC-001`; report/evidence: `tests/results/SAA-VV-ALLOC-001/` | Candidate; **allocation modeling gap** |
| SAA-VV-FC-001 | SAA v1.0 | Integrated assembly fit/check scenario candidate | Functional chain/scenario | Demonstration / Inspection | `SAA-UC-IntegratedAssembly`; `SAA-FE-EnvelopeNonCompliance`; `SAA-FE-MassNonCompliance` | IVV, SAA-R1, SAA-R5 | Stat: repeated measurements use calibrated instruments and guard bands; reliability claims need binomial evidence if repeated fit cycles are treated as pass/fail trials. Fault hardening: fit only after full mass/configuration, external exceptions, measurement uncertainty. | As-flown assembly fits the modeled envelope, mass limit, module stack and PCB accommodation constraints with uncertainty guard bands; deviations/external exceptions are dispositioned. | Future model definition: `tests/definitions/SAA-VV-FC-001`; report/evidence: `tests/results/SAA-VV-FC-001/` | Candidate; **scenario not yet modeled as chain** |
| SAA-VV-FC-002 | SAA v1.0 | Backplane mating and signal-access scenario candidate | Functional chain/scenario | Demonstration / Testing | `SAA-UC-BackplaneIntegration`; `SAA-FE-BackplaneMisMate` | IVV, SAA-R4, SAA-R5 | Stat: 100% net continuity; protocol frame/message counts only after CE definitions are modeled. Fault hardening: mate/unmate wear, bent pins, inaccessible testpoints, rail drop. | Backplane seats perpendicularly, mates all modeled headers/connectors, exposes required testpoints, and supports rails/signals within constraints before subsystem functional testing. | Future model definition: `tests/definitions/SAA-VV-FC-002`; report/evidence: `tests/results/SAA-VV-FC-002/` | Candidate; **scenario not yet modeled as chain** |
| SAA-VV-FC-003 | SAA v1.0 | Parachute/top-module clearance and deployment-interference scenario candidate | Functional chain/scenario | Demonstration / Testing | `SAA-UC-ParachuteClearance`; `SAA-FE-StructuralLoosening`; `SAA-FE-LandingDamage` | IVV, SAA-R1-R3, SAA-R5 | Stat: 10 repeated deployments for workshop screen; 29 zero-snag trials for R90/C95 only if representative and independent. Fault hardening: cap rub, servo connector/backplane interference, post-vibration/drop looseness. | Cap/servo motion clears structure/backplane, parachute extracts without snagging, reset is serviceable, and links remain secure before/after vibration/drop screens. | Future model definition: `tests/definitions/SAA-VV-FC-003`; report/evidence: `tests/results/SAA-VV-FC-003/` | Candidate; **scenario not yet modeled as chain** |
| SAA-VV-CON-001 | SAA v0.1/v1.0 | `355 ml` envelope, diameter/height, mass `<350 ±0.1 g`, landing impact | Constraint | Inspection / Testing | Constraint; `SAA-FE-EnvelopeNonCompliance`; `SAA-FE-MassNonCompliance`; `SAA-FE-LandingDamage` | IVV, SAA-R1, SAA-R2, SAA-R5 | Stat: use calibrated measurements with uncertainty; impact tests use pass/fail binomial logic if claiming reliability. Fault hardening: full as-flown configuration, ballast/battery state, post-impact remeasurement. | Diameter plus uncertainty `<=66.0 mm`; height plus uncertainty `<=122.0 mm` unless a stricter competition limit is adopted; mass interpretation `<350 ±0.1 g` is clarified; landing-impact screen causes no structural/integration failure. | Future model definition: `tests/definitions/SAA-VV-CON-001`; report/evidence: `tests/results/SAA-VV-CON-001/` | Candidate; height and mass wording require confirmation |
| SAA-VV-CON-002 | SAA v0.1/v1.0 | Modular-structure constraint: maximum two module types; standard module accommodates `44 mm × 44 mm` PCB | Constraint | Inspection / Demonstration | Constraint; `SAA-UC-IntegratedAssembly` | IVV, SAA-R1, SAA-R3 | Stat: inspect all module instances; repeated insert/remove cycles are screen evidence. Fault hardening: interference, removal path blocked, keep-out violation, wrong module type count. | Only the modeled module types are used; ADS/AMS/OBCC/PDS PCB dummies or flight PCBs seat in standard modules without force and with positive clearance after uncertainty. | Future model definition: `tests/definitions/SAA-VV-CON-002`; report/evidence: `tests/results/SAA-VV-CON-002/` | Candidate; PCB drawing tolerances pending |
| SAA-VV-CON-003 | SAA v0.1/v1.0 | Backplane allowance / Backplane PCB constraints: perpendicular allocation, `100 mm × 28 mm`, two-layer, headers/pin interface, rails, testpoints, low-cap SPI/I2C/UART, ERC/DRC clean | Constraint | Inspection / Analysis / Testing | Constraint; `SAA-UC-BackplaneIntegration`; `SAA-FE-BackplaneMisMate` | IVV, SAA-R4 | Stat: 100% DRC/ERC/netlist review; continuity/isolation on every released board. Fault hardening: wrong header pitch, missing testpoint, excessive I2C capacitance, rail out of tolerance, DRC escape. | Backplane dimensions/stackup/header/pinout match the model; DRC/ERC are clean or dispositioned; rails meet `5.0 ±0.1 V` and `3.3 ±0.1 V`; critical fast lines remain electrically usable. | Future model definition: `tests/definitions/SAA-VV-CON-003`; report/evidence: `tests/results/SAA-VV-CON-003/` | Candidate; pinout/netlist and loads pending |
| SAA-VV-CON-004 | SAA v0.1/v1.0 | Assembly/printing constraint: max two self-tapping screw types, `0.2 mm` print precision, `15%` infill | Constraint | Inspection / Analysis / Testing | Constraint; `SAA-FE-StructuralLoosening` | IVV, SAA-R3, SAA-R5 | Stat: at least 3 coupons/modules per printer/material batch for process screen; 29 screw-hole trials for R90/C95 only if needed. Fault hardening: stripped bosses, warped slots, weak infill, torque damage. | Print settings and measured critical features satisfy the modeled process capability; screw type count `<=2`; representative assembly cycles do not strip/crack or lose alignment. | Future model definition: `tests/definitions/SAA-VV-CON-004`; report/evidence: `tests/results/SAA-VV-CON-004/` | Candidate; print profile and torque criteria pending |
| SAA-VV-CON-005 | SAA v1.0 | Battery fixture, PCB standoffs/screws, stack screws, backplane fixture and servo connector retention under vibration/drop/20 g-style loads | Constraint / component-link | Testing / Inspection | `SAA-FE-StructuralLoosening`; `SAA-FE-LandingDamage` | IVV, SAA-R2, SAA-R5 | Stat: environmental article tests are screens unless independent article/trial plan is agreed; pre/post inspections are mandatory. Fault hardening: heavy battery detachment, connector unseat, backplane movement, post-test rail/signal failure. | After tailored vibration/drop/proof-load screens, no retained mass detaches, no connector/fixture loosens, envelope remains compliant, and post-test PC/PL/backplane checks pass. | Future model definition: `tests/definitions/SAA-VV-CON-005`; report/evidence: `tests/results/SAA-VV-CON-005/` | Candidate; environmental levels pending |

## 6. Coverage and gaps

- **Physical coverage:** all modeled S&A physical components and physical links are covered by SAA-VV-PC-001 and SAA-VV-PL-001, with retention/environmental follow-up in SAA-VV-CON-005.
- **Exchange coverage:** no component exchanges are modeled; SAA-VV-CE-001 records the required gap analysis for rails, pin interface, testpoints and SPI/I2C/UART.
- **Allocation coverage:** no logical components/functions/allocations are modeled; SAA-VV-ALLOC-001 records the required gap analysis.
- **Functional-chain/scenario coverage:** no chains are modeled; SAA-VV-FC-001 through SAA-VV-FC-003 identify fit, backplane and deployment-clearance scenario candidates requiring later definition.
- **Constraint coverage:** every explicit S&A constraint is assigned to at least one constraint-derived activity.
- **Traceability gaps:** explicit mission/capability/use-case/feared-event nodes are absent; provisional IDs in this plan require user/model confirmation.
- **Ambiguities needing confirmation:** SSIV/campaign stage; model height `122 mm` versus some CanSat references with stricter height; meaning of `<350 ±0.1 g`; backplane pinout and loads; I2C mode/capacitance targets; IPC/DFM class; print material/profile; screw torque and environmental levels.
- **Definition-stage handoff:** detailed test means, fixtures, stimuli and pass/fail constraints must be modeled later with `capella-pa-tests-definition.md`; this planning stage intentionally does not create or edit test-definition diagrams.
