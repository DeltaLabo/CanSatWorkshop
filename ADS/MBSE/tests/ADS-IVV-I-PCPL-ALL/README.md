# ADS-IVV-I-PCPL-ALL — all-version physical component / physical link inspection definition

**IADT method:** Inspection. Continuity, isolation, and current-limited power readings are supporting evidence for physical-link presence/absence and endpoint correctness.

**IVV source category:** component/link.

**Selected SSIV/development scope:** all ADS development versions currently present in the MBSE corpus: `v0.1`, `v0.2`, `v0.3`, and `v1.0`.

**Traceability targets:** `ADS-CAP-PHY`, `ADS-CAP-PCB` where PCB/backplane delivery is applicable, and feared event `ADS-FE-OPEN-SHORT-LINK`.

**References cited in diagrams:** IVV minimum PC/PL inspection rule, NASA-SE, saved workmanship references under `../references/`, and the ADS MBSE IVV plan `../README.md`.

## Source-view copies

All Capella/D2 views for the selected all-version scope were copied under `source_views/`:

- `source_views/v0.1/` — physical, logical, allocation, GPS position chain, Serial logging chain.
- `source_views/v0.2/` — physical, logical, allocation, GPS, angular velocity, attitude estimation, peripheral initialisation, Serial logging chains.
- `source_views/v0.3/` — physical PCB delivery view.
- `source_views/v1.0/` — physical, logical, allocation, GPS, angular velocity, attitude estimation, peripheral initialisation chains.

## Test-definition views

| View | Purpose |
|---|---|
| `definition_views/ADS_IVV_I_PCPL_ALL_view1_physical_test_setup.d2/png` | PV1 test setup: selected version article, non-human test-equipment External Actors, temporary probe/power/fixture Physical Links, and PC/PL pass/fail constraints. |
| `definition_views/ADS_IVV_I_PCPL_ALL_view2_logical_test_interfaces.d2/png` | PV2 human-operator Component Exchanges for checklist/evidence and anomaly disposition. |
| `definition_views/ADS_IVV_I_PCPL_ALL_view3_functional_allocation.d2/png` | PV3 allocation of verification-only functions to human operators, DMM, power supply, header fixture, microscope/camera, ambient monitor, and selected article interface. |
| `definition_views/ADS_IVV_I_PCPL_ALL_view4_inspection_sequence.d2/png` | Inspection sequence functional chain, used as a modeled procedure reference even though the IADT method remains Inspection. |

## Version coverage

| Version | Model element(s) covered | Pass/fail constraints |
|---|---|---|
| `v0.1` | PCs: UBX-G7020-KT GPS, XIAO ESP32; EA endpoint: PC; PLs: UART Cables, 3V3, GND, USB-C Cable. | Pass if every modeled item/link is present, identified, correctly routed, continuous where applicable, free of unintended shorts, and evidenced. Fail on missing/wrong/damaged component, open/short, reversed UART interpretation, weak power/ground, or loose/unfit USB-C. |
| `v0.2` | PCs: UBX-G7020-KT GPS, XIAO ESP32, ICM20948 IMU; EA endpoint: PC; PLs: GPS-XIAO UART/3V3/GND, IMU-XIAO I2C/3V3/GND, XIAO-PC USB-C. | Same as v0.1 plus fail on swapped or misrouted I2C SDA/SCL, weak IMU 3V3/GND, damaged IMU link, or PC enumeration/logging endpoint absence. |
| `v0.3` | PCs: ADS PCB, UBX-G7020-KT GPS, ICM20948 IMU, Backplane Connector; PLs: GPS/ICM20948/connector footprints, UART/I2C/3V3 traces. | Pass if every modeled PCB component, footprint, and trace is present, correct, workmanlike, continuous where applicable, isolated from unintended shorts, and evidenced. Fail on wrong footprint/orientation, open trace, solder bridge, lifted pad, connector mounting defect, or unresolved manufacturing nonconformance. |
| `v1.0` | All v1.0 PCs and PLs in the physical view: CanSat, modules, PCBs, sensors, connectors, headers, spine, XIAO ESP32-S3, screws, fixtures, footprints, UART/I2C/3V3 traces, parallel cables. | Pass if 100% of modeled v1.0 PCs/PLs are present, correct, secure, mated as modeled, continuous where electrical, isolated from shorts, and evidenced. Fail on mis-mated headers, cable reversal, open/short, loose fixture/screw, wrong connector/footprint, solder/cable workmanship defect, or any uninspected item. |

## Viewpoints

- **Statistical significance:** complete enumeration, not sampling. Inspect 100% of the selected version's modeled PC/PL inventory for every article. If future lot sampling is introduced, define a separate sampling plan and do not claim this activity provides population inference by itself.
- **Fault hardening:** open/short links, swapped UART TX/RX, swapped I2C SDA/SCL, weak or missing 3V3/GND, USB-C enumeration failure, mis-mated 2 mm headers, cable/header reversal, loose screws/fixtures, solder bridges, cracked/lifted pads, damaged connectors/cables.
- **Configuration control:** report identifies selected ADS version, source-view copy, hardware revision/BOM, firmware commit if powered, article serial/identifier, equipment IDs/calibration status, operator, witness/reviewer if used, and deviations.
- **Environmental context:** ambient temperature/humidity are read from the modeled ambient thermometer/hygrometer before the article or batch inspection; defer if condensation, unsafe ESD state, or unresolved equipment calibration/function-check exists.

## Expected report locations

Reports should reference this modeled definition and store evidence under:

- `../results/ADS-IVV-I-PCPL-ALL/v0.1/`
- `../results/ADS-IVV-I-PCPL-ALL/v0.2/`
- `../results/ADS-IVV-I-PCPL-ALL/v0.3/`
- `../results/ADS-IVV-I-PCPL-ALL/v1.0/`

Each report shall identify referenced model views/elements, selected SSIV/version, as-inspected/as-tested configuration, raw evidence, actual environmental/equipment conditions, deviations, anomalies, waivers, pass/fail rationale, and retest status.

## Status

Modeled definition ready for review. Execution remains pending.
