# SAA-VV-FC-002 — Backplane mating, rail/testpoint/signal-access scenario

Model-defined verification activity for the S&A `v1.0` flight-readiness baseline. This activity turns the candidate backplane mating and signal-access scenario into Capella-style verification-only views for report-by-reference.

- **IADT method:** Demonstration / Testing
- **IVV source category:** Functional chain / scenario
- **SSIV / development version:** `SAA-v1.0` flight readiness / final acceptance. `v0.1` is copied as incremental context only; the executable scenario is defined for the integrated `v1.0` article.
- **Definition folder:** `S&A/MBSE/tests/SAA-VV-FC-002/`
- **Expected report/evidence folder:** `S&A/MBSE/tests/results/SAA-VV-FC-002/`
- **Primary traceability targets:** `SAA-UC-BackplaneIntegration`, `SAA-FE-BackplaneMisMate`, and the v1.0 Backplane PCB constraints for defined pin interface, `5.0 ±0.1 V`, `3.3 ±0.1 V`, testpoints for critical signals, low-capacitance SPI/I2C/UART, and ERC + DRC clean.
- **References:** IVV (`PM&SE/IVV.md`), SAA-R4 and SAA-R5 as indexed in `S&A/MBSE/tests/references/README.md`.

## Model views

| View | D2 | PNG | Purpose |
|---|---|---|---|
| Baseline copy v0.1 | `baseline/SAA_v0.1_view1_physical.d2` | `baseline/SAA_v0.1_view1_physical.png` | Frozen incremental structural/module/backplane-volume context. |
| Baseline copy v1.0 | `baseline/SAA_v1.0_view1_physical.d2` | `baseline/SAA_v1.0_view1_physical.png` | Frozen source context for the v1.0 backplane/header/testpoint constraints and physical endpoints. |
| v1.0 physical testbench | `SAA-VV-FC-002_v1.0_physical_testbench.d2` | `SAA-VV-FC-002_v1.0_physical_testbench.png` | PV1 testbench with integrated assembly/backplane UUT, mate/demate alignment jig, current-limited bench supply, safe load/no-load adapter, DMM/DAQ, continuity tester, oscilloscope/logic analyzer, testpoint probes, operator/witness, ambient meter, camera and evidence repository. |
| Logical interface exchange | `SAA-VV-FC-002_logical_interface_exchange.d2` | `SAA-VV-FC-002_logical_interface_exchange.png` | Verification-only PV2 exchanges for rail/testpoint/netlist/measurement/evidence data and acceptance-gate disposition. |
| Functional allocation / procedure | `SAA-VV-FC-002_functional_allocation_procedure.d2` | `SAA-VV-FC-002_functional_allocation_procedure.png` | Verification-only PV3 allocation of mate, inspect seating, apply safe power, measure rails, probe testpoints/fast lines, detect anomalies and log evidence. |
| Nominal mating / rail / testpoint chain | `SAA-VV-FC-002_nominal_mating_rail_testpoint_chain.d2` | `SAA-VV-FC-002_nominal_mating_rail_testpoint_chain.png` | Main Demonstration / Testing functional chain for nominal backplane mating and access checks. |
| Fault-hardening hold chain | `SAA-VV-FC-002_fault_hardening_hold_chain.d2` | `SAA-VV-FC-002_fault_hardening_hold_chain.png` | Functional chain for misalignment, bent-pin, short/open/swap, inaccessible-testpoint, rail-drop/overcurrent and fast-line-loading hold behavior. |

The logical components, component exchanges, functions, physical links to test equipment, verification testpoint access pads/probe terminals and functional chains in this folder are **verification-only** and do not modify the S&A baseline architecture.

## Item under verification

The UUT is the integrated `v1.0` S&A backplane mating and access configuration within the CanSat Assembly, including:

- Standard Carrier Module Stack (Type 1) with ADS, AMS, OBCC, PDS and ESS Modules;
- ADS/AMS/OBCC/PDS `44 mm × 44 mm` PCBs;
- Backplane PCB `100 mm × 28 mm`, two-layer, with ADS/AMS/OBCC/PDS `2 mm 2×6` headers, PDM Servo Connector and Backplane Spine;
- verification-required rail and critical signal testpoints associated with the backplane constraint;
- ESS Battery Pack and Parachute / Top Module context only to the extent needed to preserve the integrated `v1.0` mating/access geometry.

## Verification means and allocated functions

| Actor / equipment | Verification-only functions |
|---|---|
| S&A Test Operator | Identify article/baseline; prepare ESD setup; operate the alignment jig; mate/demate the backplane without force; inspect seating, orientation, connector flushness and pins; configure safe load or document no-load; place probes; record anomalies. |
| QA Witness | Witness setup, calibration IDs, current limits, no-force insertion, 100% net/rail/testpoint completion and pass/fail/hold disposition. |
| Mate/Demate Fixture with Alignment Jig | Constrain orientation and seating datum; support repeated mate cycles when used as screening evidence. |
| Current-limited Bench Supply | Set voltage/current limits before enabling power; apply and remove safe `5 V` / `3.3 V` test power. |
| Campaign Safe Load / No-load Adapter | Present the campaign-defined safe load or a controlled no-load marker/rationale. |
| Calibrated DMM / DAQ | Measure `5.0 V` and `3.3 V` at required testpoints; log raw readings, calibration status and timestamps. |
| Continuity / Isolation Tester | Check 100% required endpoint continuity/isolation and detect short, open or swapped endpoint anomalies before power. |
| Oscilloscope / Logic Analyzer | Demonstrate critical SPI/I2C/UART access with low-capacitance probes or record a rise-time/capacitance analysis dependency. |
| Testpoint Probe Set | Contact required rail and signal testpoints without modifying the article or creating adjacent-pin shorts. |
| Ambient Thermo-Hygrometer | Record ambient temperature/humidity before checks. |
| Camera / Evidence Light Box | Capture seating, pin, probe, instrument, reading and anomaly evidence. |
| Evidence Repository | Store the controlled report, raw readings, net/endpoint matrix, photos/video, calibration IDs, ambient record, witness decision and anomaly dispositions under `S&A/MBSE/tests/results/SAA-VV-FC-002/`. |

## Demonstration / testing procedure definition

1. Identify the `v1.0` article, build/configuration record, baseline copy, operator, witness, equipment IDs, calibration status and this model definition revision.
2. Record ambient temperature/humidity and confirm ESD handling, fixture state, probe condition and evidence-capture setup.
3. Confirm bench-supply outputs are off, set current limits and voltage targets for `5 V` and `3.3 V`, and record the campaign safe-load value or controlled no-load rationale.
4. Place the assembly/backplane in the mate/demate fixture and align the perpendicular Backplane PCB to the ADS/AMS/OBCC/PDS `2 mm 2×6` headers and the PDM Servo Connector.
5. Mate the backplane without force. Stop and record an anomaly if orientation, insertion force, alignment, pin state or connector path is questionable.
6. Inspect seating, connector flushness, orientation, visible pins and connector damage. Record photo/video evidence and witness confirmation.
7. Before applying power, perform 100% continuity/isolation checks for the required rail/testpoint/critical endpoint paths from the released netlist/pinout/testpoint evidence. Any short, open, swapped endpoint, unknown endpoint or partial seat inhibits power and triggers the fault-hardening hold chain.
8. Enable current-limited safe power only after pre-power checks pass. Measure `5.0 ±0.1 V` and `3.3 ±0.1 V` at required testpoints under the campaign safe load, or under a documented no-load condition if no safe-load campaign value exists.
9. Demonstrate that required rail and critical signal testpoints are physically reachable with controlled probes without modifying the article, back-driving nets or creating adjacent-pin short risk.
10. Demonstrate critical SPI/I2C/UART access non-invasively with low-capacitance probes when useful for access evidence. Any excessive capacitance/rise-time concern is recorded as an analysis dependency, normally to SAA-VV-CE-001 or SAA-VV-CON-003, and the activity is held unless the flight-readiness authority accepts the dependency.
11. Capture raw readings, endpoint matrix, photos/video, ambient data, calibration IDs, safe-load/no-load state and witness review.
12. Apply the pass/fail constraints below. If any exception occurs, execute the fault-hardening hold chain and re-run affected nominal checks after approved rework or dependency closure before claiming pass.
13. QA witness approves pass/fail/hold and the evidence repository releases the report-by-reference package.

## Pass/fail constraints

Pass only if all of the following are true for the `v1.0` article:

- the perpendicular Backplane PCB seats in the modeled fixture and mates ADS, AMS, OBCC and PDS `2 mm 2×6` headers plus the PDM Servo Connector to the modeled orientation/alignment;
- no forced insertion, bent pin, damaged connector, wrong orientation, partial seat, unapproved shim or connector unseat is observed;
- required testpoints are reachable with controlled probes without article modification, back-driving, probe instability or adjacent-pin short risk;
- 100% required rail/testpoint/critical endpoint continuity/isolation checks show no short, open, swapped endpoint or unknown endpoint anomaly;
- bench-supply current limits are recorded before rail enable;
- `5 V` rail measurements at required testpoints are within `5.0 ±0.1 V` under the campaign safe load or a controlled documented no-load condition;
- `3.3 V` rail measurements at required testpoints are within `3.3 ±0.1 V` under the campaign safe load or a controlled documented no-load condition;
- fast-line SPI/I2C/UART probe access is non-invasive or any capacitance/rise-time issue is explicitly recorded as a controlled analysis dependency with accepted disposition;
- ambient conditions, instrument/probe calibration status, raw readings, endpoint matrix, photos/video, witness review and anomaly dispositions are complete;
- every anomaly, waiver, rework or deviation is closed with approved disposition and affected checks have been re-run.

Fail or hold for any missing modeled mating endpoint, forced insertion, bent pin, wrong orientation, partial seat, connector damage, inaccessible required testpoint, probe-induced short risk, short/open/swapped endpoint, rail outside tolerance, overcurrent, rail drop, unknown safe-load/no-load state, missing evidence, expired/unknown calibration affecting a result, unresolved fast-line-loading dependency, or unapproved anomaly disposition.

## Viewpoints

- **Statistical significance:** This is a 100% check of the modeled v1.0 backplane mating endpoints, required rail/testpoint/critical endpoint paths and required testpoints for the tested article. It makes no sampling or population reliability claim. Repeated mate/demate cycles are only screening evidence unless an approved independent-cycle statistical plan defines sample size, independence and acceptance criteria.
- **Fault hardening:** The model requires de-energized mating/demating, pre-power continuity/isolation, current limiting before rail enable, no-force witness inspection, and hold on wrong orientation, misalignment, bent pins, connector unseat, inaccessible testpoints, shorts, opens, swapped endpoints, overcurrent, rail drop, out-of-tolerance rails and unresolved SPI/I2C/UART loading or rise-time concerns.

## Required report content

The execution report in `S&A/MBSE/tests/results/SAA-VV-FC-002/` should reference this model definition and record only execution-specific information:

- model definition revision and v1.0 baseline copy used;
- inspected article identifier, version and build/configuration record;
- operator, witness, equipment IDs, probe IDs, calibration records, ESD setup and ambient record;
- fixture/alignment observations and photos/video for all ADS/AMS/OBCC/PDS headers and the PDM Servo Connector;
- released netlist/pinout/testpoint evidence revision used for the 100% endpoint/testpoint checklist;
- completed continuity/isolation matrix with short/open/swap status;
- supply settings, current limits, safe-load value or no-load rationale, raw `5 V` and `3.3 V` readings and timestamps;
- testpoint reachability and critical fast-line probe-access observations, including any capacitance/rise-time dependency;
- evidence IDs and file paths for photos/video, raw data and matrices;
- pass/fail/hold rationale;
- deviations, anomalies, waivers, rework and re-run evidence.

## Assumptions and blockers

- The executable scenario is for `SAA-v1.0`; `v0.1` is retained as copied context because it does not include the modeled PCB/backplane/header/servo-connector integration required for this activity.
- The baseline S&A v1.0 source view contains no `[CE]`, `[LC]`, `[F]`, `[FE]` or functional-chain elements; this folder adds verification-only definitions rather than editing the baseline.
- The required netlist/pinout/testpoint list and campaign safe-load value are assumed to be provided at execution time. If absent, the report shall document a controlled no-load condition and/or hold unresolved endpoint/testpoint coverage until evidence is available.
- The fast-line access check demonstrates physical access and records gross loading concerns; quantitative signal-integrity closure remains an analysis/test dependency unless the execution authority extends this activity with an approved SI acceptance method.
- The gate may be placed on hold rather than failed when a discrepancy is correctable by approved rework, model/evidence update, or accepted dependency before flight-readiness closure.
