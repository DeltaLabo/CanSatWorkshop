# ADS-IVV-A-ALLOC-ALL — all-version functional allocation analysis definition

**IADT method:** Analysis.

**IVV source category:** allocation.

**Selected SSIV/development scope:** all ADS development versions currently present in the MBSE corpus: `v0.1`, `v0.2`, `v0.3`, and `v1.0`.

**Traceability targets:** `ADS-CAP-GPS`, `ADS-CAP-IMU`, `ADS-CAP-ATT`, `ADS-CAP-INIT`, `ADS-CAP-DELIVERY`, `ADS-CAP-PCB` for v0.3 N/A rationale, and feared events `ADS-FE-SILENT-SENSOR-FAIL`, `ADS-FE-STUCK-LOOP`, `ADS-FE-CORRUPT-MEASUREMENT`. Physical-only v0.3 disposition may also reference `ADS-FE-OPEN-SHORT-LINK`.

**References cited in diagrams:** IVV minimum allocation analysis rule, NASA-SE, GPS/UBX references, ICM20948/I2C references, SW/statistics references, and the ADS MBSE IVV plan `../README.md`.

## Source-view copies

All Capella/D2 views for the selected all-version scope were copied under `source_views/`:

- `source_views/v0.1/` — physical, logical, allocation, GPS position chain, Serial logging chain.
- `source_views/v0.2/` — physical, logical, allocation, GPS, angular velocity, attitude estimation, peripheral initialisation, Serial logging chains.
- `source_views/v0.3/` — physical PCB delivery view.
- `source_views/v1.0/` — physical, logical, allocation, GPS, angular velocity, attitude estimation, peripheral initialisation chains.

## Test-definition views

| View | Purpose |
|---|---|
| `definition_views/ADS_IVV_A_ALLOC_ALL_view1_logical_boundary_inventory.d2/png` | PV2 logical boundary inventory for all allocation baselines; shows LC/PC boundaries and CE support for cross-LC flows, plus v0.3 N/A rationale. |
| `definition_views/ADS_IVV_A_ALLOC_ALL_view2_functional_allocation_inventory.d2/png` | PV3 allocation inventory listing modeled PCs, LCs, and functions for v0.1, v0.2, and v1.0; includes v0.3 zero-allocation rationale and applicable constraints. |
| `definition_views/ADS_IVV_A_ALLOC_ALL_view3_verification_means.d2/png` | PV3 verification means: allocation analyst, firmware/static-analysis tools, runtime evidence tools, reference corpus, quality authority, and verification-only functions. |
| `definition_views/ADS_IVV_A_ALLOC_ALL_view4_analysis_sequence.d2/png` | Functional-chain style analysis sequence used as the modeled allocation-analysis procedure; IADT method remains Analysis. |

## Version allocation coverage

| Version | Model element(s) covered | Pass/fail constraints |
|---|---|---|
| `v0.1` | 3 LCs / 11 LC functions: ADS GPS Sensing on GPS; Setup and Loop on XIAO. PC monitor EA function is supporting evidence, not an LC allocation. | Pass if all v0.1 functions are allocated to the modeled LCs/PCs, no foreign functions are present, GPS→Loop UART boundary is consistent with the modeled CE, and any Setup↔Loop or Loop→PC flow gap is dispositioned. Fail on missing/wrong ownership, v0.2+ foreign functions, unbounded UART/blocking behavior, stale/corrupt GPS data accepted as valid, or undispositioned cross-LC flow. |
| `v0.2` | 4 LCs / 22 LC functions: ADS GPS Sensing on GPS; ADS Kinematic Sensing on IMU; Setup and Loop on XIAO. PC monitor EA function is supporting evidence. | Pass if every intended v0.2 function is allocated to the modeled LC/PC, no foreign functions are allocated, and LC-boundary data/resource flows are supported by UART/I2C CEs or dispositioned gaps. Record gaps for `Init Serial0 and Serial1` chain coverage, Setup/Loop boundary flows, Kinematic/Setup init flow, and missing v0.2 I2C timeout constraint. |
| `v0.3` | No modeled LCs/functions/CEs. Source is a PV1-only PCB delivery model with ADS PCB, GPS, IMU, connector, footprints, UART/I2C/3V3 traces. | Pass/N/A if all v0.3 D2 views are reviewed, LC count = 0, function count = 0, CE count = 0, physical traces are not credited as logical allocation, and PCB-only rationale is recorded. Fail if any LC/function/CE is found but not inventoried or if behavior is claimed without an allocation model. |
| `v1.0` | 4 LCs / 20 functions: ADS GPS Sensing on GPS; ADS Kinematic Sensing on IMU; ADS Processing and OBCC on XIAO ESP32-S3/OBCC PCB. | Pass if 4/4 LCs and 20/20 functions are reviewed, each function is allocated to its intended LC/PC, no foreign function is present, and every cross-LC data/resource flow is justified by UART, I2C, Pointers, or Returns. Fail on missing/unallocated/duplicated functions, wrong LC/PC ownership, bypassed CE boundary, unsafe pointer/return ownership, stale/corrupt data accepted as valid, or no-blocking/timeout violation. |

## Constraint and viewpoint coverage

- **Allocation correctness:** every logical component is checked for intended functions and absence of foreign functions.
- **Boundary-flow rationale:** data/resource flows crossing LC boundaries are checked against modeled CEs or dispositioned as same-PC internal flow/model gap.
- **Constraint interaction:** no blocking except I2C/UART, Variable Getter semantics, Process/Calculate `<5 ms`, UART timeout `<=5 ms`, v1.0 I2C timeout `<=5 ms`, GPS `<5 m`, gyro `<30 deg/s`, and v0.1/v0.2 `5 Hz` collection are reviewed for ownership/allocation consistency where applicable.
- **Statistical significance:** complete enumeration, not sampling. Runtime samples are supporting evidence only for linked chain/constraint tests.
- **Fault hardening:** silent/malformed/no-fix GPS, stale lat/lon cache, I2C NACK/stuck/wrong address, failed reads corrupting storage, blocking Loop, misplaced init/logging responsibility, invalid getters/calculators, unsafe pointer/return ownership, and OBCC consuming invalid ADS data.
- **Configuration control:** report identifies selected ADS version, source-view copy, hardware/software baseline, firmware commit, implementation modules reviewed, static-analysis evidence, runtime evidence if used, deviations, waivers, and retest status.

## Expected report locations

Reports should reference this modeled definition and store evidence under:

- `../results/ADS-IVV-A-ALLOC-ALL/v0.1/`
- `../results/ADS-IVV-A-ALLOC-ALL/v0.2/`
- `../results/ADS-IVV-A-ALLOC-ALL/v0.3/`
- `../results/ADS-IVV-A-ALLOC-ALL/v1.0/`

Each report shall identify referenced model views/elements, selected SSIV/version, as-analyzed implementation/configuration, evidence sources, allocation pass/fail or N/A rationale, unresolved model gaps, anomalies, waivers, limitations, and retest status.

## Status

Modeled definition ready for review. Execution remains pending.
