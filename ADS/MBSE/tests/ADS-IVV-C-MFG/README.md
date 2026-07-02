# ADS-IVV-C-MFG — manufacturing/workmanship verification

**IADT method:** Inspection with supporting Analysis and continuity/power Testing.

**IVV source category:** constraint plus component/link support.

**Selected SSIV/development scope:** ADS `v0.1`, `v0.2`, `v0.3`, and `v1.0`. The primary formal scope is `v0.3` PCB delivery and `v1.0` integrated PCB/backplane/OBCC assembly. `v0.1`/`v0.2` are noted as prototype support contexts but are not forced into PCB/backplane workmanship criteria unless their as-built configuration uses those criteria.

**Traceability targets:** `ADS-IVV-C-MFG` traces to the v0.3 manufacturing/workmanship note, `ADS-CAP-PCB`, `ADS-CAP-PHY`, `ADS-CAP-DELIVERY`, and `ADS-FE-OPEN-SHORT-LINK`. Explicit mission/capability/use-case/feared-event elements are not modeled as separate source nodes, so controlled ADS plan trace labels remain in use.

**References cited in diagrams:** IVV, the ADS MBSE IVV plan `../README.md`, `ADS_MBSE_CORPUS.md`, `model_inventory.json`, and saved reference material under `../references/` or `../v0.2/tests/references/` as applicable. No external research was performed for this definition.

## Source-view copies

All D2/PNG views for the selected ADS-wide scope were copied under `source_views/` so reports can reference a stable test-definition package:

- `source_views/v0.1/` — v0.1 physical, logical, allocation, GPS, and Serial0 source views.
- `source_views/v0.2/` — v0.2 physical, logical, allocation, GPS, angular velocity, attitude, peripheral initialization, and Serial0 source views.
- `source_views/v0.3/` — v0.3 physical PCB delivery view.
- `source_views/v1.0/` — v1.0 physical, logical, allocation, GPS, angular velocity, attitude, and peripheral initialization source views.

## Test-definition views

| View | Purpose |
|---|---|
| `definition_views/ADS_IVV_C_MFG_view1_source_physical_manufacturing_inventory.d2/png` | Inventory v0.3/v1.0 PCB, footprints, traces, connectors, headers, fixtures, screws, and workmanship constraints. |
| `definition_views/ADS_IVV_C_MFG_view2_physical_inspection_test_setup.d2/png` | Model microscope/camera, DMM, current-limited supply, ESD/ambient controls, mating fixture, and inspection authority. |
| `definition_views/ADS_IVV_C_MFG_view3_verification_functional_allocation.d2/png` | Allocate inspection, measurement, evidence capture, anomaly disposition, and configuration-control functions. |
| `definition_views/ADS_IVV_C_MFG_view4_inspection_continuity_sequence.d2/png` | Functional-chain style sequence for visual inspection, net continuity/isolation, power sanity, connector mating, and anomaly closure. |
| `definition_views/ADS_IVV_C_MFG_view5_evidence_traceability.d2/png` | Model photo evidence, checklists, net measurements, workmanship records, deviations, waivers, and retest closure. |

## Version coverage and pass/fail rules

| Version | Model element(s) covered | Pass/fail constraints |
|---|---|---|
| `v0.1` | Breadboard/prototype hardware support context. | Use PC/PL inspection definitions for formal v0.1 pass/fail; apply this workmanship definition only if an as-built prototype has soldered/cabled workmanship criteria to record. |
| `v0.2` | Breadboard/prototype GPS+IMU support context. | Same as v0.1; do not replace existing PC/PL inspection but record relevant cable/solder workmanship if applicable. |
| `v0.3` | ADS PCB delivery with GPS, ICM20948, backplane connector, footprints, UART/I2C/3V3 traces, and manufacturing note. | Pass if all modeled PCB items/footprints/traces are present, correct, workmanlike, continuous/isolated where applicable, and compatible with the selected manufacturing/soldering route. |
| `v1.0` | Integrated ADS Module, Backplane PCB, OBCC Module, headers/connectors/cables/fixtures/screws/traces. | Pass if the integrated assembly is present/correct/secure/mated as modeled, no opens/shorts or workmanship defects remain, and ADS/backplane/OBCC UART/I2C/3V3/GND paths pass continuity/isolation/power sanity checks. |

## Viewpoints

- **Statistical significance:** apply the sample-count rule stated for this activity before making a formal statistical or deadline claim; otherwise classify evidence as characterization/screening only.
- **Fault hardening:** execute the activity-specific fault cases modeled in the definition views and do not accept invalid, stale, corrupt, or missing data as valid evidence.
- **Configuration control:** every report identifies ADS version/SSIV, source-view copy, hardware revision/BOM, firmware commit/build, instrumentation build, equipment IDs/calibration status, operator, and deviations.
- **Environmental context:** record ambient temperature/humidity, power conditions, and any test-specific environmental or ESD constraints before execution.

## Required execution conditions

- Select workmanship class/criteria before execution and record whether Carvera Air CNC, reflow, manual soldering, rework, or mixed processes were used.
- Record article serial, PCB revision, BOM/configuration, inspector, equipment IDs/calibration, ambient/ESD state, photo set, and deviations.
- Inspect 100% of modeled items for the selected article; do not claim production-lot statistics unless a separate sampling plan is approved.
- Use current-limited power and ESD-safe handling; defer if condensation, unsafe ESD state, or missing equipment function checks are present.

## Expected report locations

Reports should reference this modeled definition and store evidence under:

- `../results/ADS-IVV-C-MFG/v0.1/`
- `../results/ADS-IVV-C-MFG/v0.2/`
- `../results/ADS-IVV-C-MFG/v0.3/`
- `../results/ADS-IVV-C-MFG/v1.0/`

Each report shall identify referenced model views/elements, selected SSIV/version, as-tested/as-inspected configuration, raw evidence, analysis settings, actual environmental and equipment conditions, pass/fail or N/A rationale, deviations, anomalies, waivers, limitations, and retest status.

## Assumptions and execution records

- Workmanship acceptance basis is controlled for execution: NASA-STD-8739.3 solder/workmanship checks and NASA-STD-8739.4A harness/crimp checks where applicable, with IPC-A-610 Class 2 visual acceptability as the default PCB assembly screening level unless a project authority predeclares a stricter class. Any deviation or alternate class is a waiver/deviation record, not an open oracle.
- Manufacturing route and as-built PCB/assembly revision are report-time configuration records.

## Status

Modeled definition ready for review. Execution remains pending.
