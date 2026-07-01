# ADS-IVV-FC-ATT — attitude estimation functional-chain verification definition

**IADT method:** Demonstration with supporting Testing and Analysis.

**IVV source category:** functional chain / scenario.

**Selected SSIV/development scope:** ADS `v0.1`, `v0.2`, `v0.3`, and `v1.0`. Attitude estimation functional-chain execution applies to `v0.2` and `v1.0`; `v0.1` is N/A because no IMU/attitude chain is modeled; `v0.3` is a PCB-delivery N/A branch because no logical components, component exchanges, allocations, or functional chains are modeled.

**Traceability targets:** `ADS-CAP-ATT`, `ADS-CAP-IMU`, and feared events `ADS-FE-STUCK-LOOP`, `ADS-FE-CORRUPT-MEASUREMENT`. The N/A rationale may reference `ADS-CAP-PHY` for `v0.1` and `ADS-CAP-PCB` / `ADS-CAP-DELIVERY` for `v0.3`.

**References cited in diagrams:** IVV, NASA-SE, IMU/I2C, ESA-CANSAT, SW/statistics references, and the ADS MBSE IVV plan `../README.md`. No external research was performed for this definition.

## Source-view copies

All D2 views for the selected ADS versions were copied under `source_views/` so reports can reference a stable test-definition package:

- `source_views/v0.1/` — physical, logical, allocation, GPS position chain, Serial logging chain; used for attitude-chain N/A rationale.
- `source_views/v0.2/` — physical, logical, allocation, GPS, angular velocity, attitude estimation, peripheral initialisation, Serial logging chains.
- `source_views/v0.3/` — physical PCB delivery view; used for N/A rationale.
- `source_views/v1.0/` — physical, logical, allocation, GPS, angular velocity, attitude estimation, peripheral initialisation chains.

## Test-definition views

| View | Purpose |
|---|---|
| `definition_views/ADS_IVV_FC_ATT_view1_source_chain_inventory.d2/png` | Attitude estimation functional-chain inventory for v0.2 and v1.0, plus v0.1/v0.3 N/A rationale and traceability. |
| `definition_views/ADS_IVV_FC_ATT_view2_physical_test_setup.d2/png` | Physical attitude demonstration setup, including selected ADS UUT, human conductor, orientation fixture, magnetic reference/context, I2C/magnetic disturbance injector, loggers, power supply, temporary PLs/CEs, pass/fail, timing, fault, and environment constraints. |
| `definition_views/ADS_IVV_FC_ATT_view3_verification_functional_allocation.d2/png` | Verification-only functional allocation to the selected ADS version, IVV conductor, orientation/magnetic reference means, data logger, demonstration analysis tool, and quality/configuration authority. |
| `definition_views/ADS_IVV_FC_ATT_view4_demonstration_sequence.d2/png` | Functional-chain style verification sequence for static orientation/yaw-change demonstration, repeatability characterization, timing checks, and I2C/invalid-IMU/magnetic-disturbance fault cases. |
| `definition_views/ADS_IVV_FC_ATT_view5_results_traceability_interfaces.d2/png` | Results and traceability interfaces for evidence, analysis, model targets, references, deviations, waivers, limitations, and retest status. |

## Version coverage and pass/fail rules

| Version | Attitude-chain coverage | Pass/fail constraints |
|---|---|---|
| `v0.1` | No IMU PC/LC/CE or attitude functional chain is modeled. | Pass/N/A if all v0.1 source views are reviewed and no attitude LC/CE/allocation/functional-chain behavior exists. Fail if attitude behavior is claimed from v0.1 without a modeled chain. |
| `v0.2` | Attitude estimation chain: Measure accelerations, Measure magnetic field intensities, Respond to I2C Requests, Read accelerations, Read field intensities, Process accelerations, Calculate pitch/roll/yaw, Collect measurements. | Pass if acceleration/magnetic-field data and PRY outputs propagate through the modeled chain, PRY is finite, bounded to the selected convention/range, plausible for known static orientations and yaw changes, repeatability is recorded for the stated demonstration objective, and invalid/stale/disturbed/I2C-fault data are not accepted as valid. Record v0.2 missing I2C timeout as a modeling gap while observing no-blocking behavior. No formal numerical attitude accuracy claim is permitted unless a new constraint is added. |
| `v0.3` | No attitude functional chain is modeled. Source package is a PV1-only PCB delivery model with physical GPS/IMU/backplane elements and UART/I2C/3V3 traces. | Pass/N/A if 1/1 v0.3 source view is reviewed, no attitude LC/CE/allocation/functional-chain behavior exists, and physical I2C traces are not credited as functional-chain behavior. Fail if behavior is claimed from v0.3 without a modeled logical/functional chain. |
| `v1.0` | Attitude estimation chain: Measure accelerations, Measure magnetic field intensities, Respond to I2C Requests, Read accelerations, Read field intensities, Process accelerations, Calculate pitch/roll/yaw, Collect measurements. IMU/attitude data flow through ADS Processing and may be delivered to OBCC through related Pointers/Returns interfaces. | Pass if acceleration/magnetic-field data and PRY outputs propagate through the modeled chain to the ADS/OBCC observation point, PRY is finite, bounded to the selected convention/range, plausible for known static orientations and yaw changes, repeatability is recorded, v1.0 I2C reads return data or timeout/error in `<=5 ms`, Process/Calculate operations remain `<5 ms` where instrumented, and invalid/stale/disturbed/I2C-fault data are not accepted as valid by ADS Processing or OBCC. No formal numerical attitude accuracy claim is permitted unless a new constraint is added. |

## Required execution conditions

- Select and record ADS version, source-model package, hardware revision, firmware commit/build, UUT serial/identifier, and data-logging configuration.
- Select the orientation/magnetic reference method before execution: non-magnetic 6-face fixture, known static orientations, yaw/heading reference or relative yaw-change procedure, and magnetic context or controlled field source. Record axis/sign convention, level/alignment, local magnetic field survey, nearby ferrous/electrical disturbance sources, vibration/slip, temperature, warm-up, timebase, power mode, calibration status, and uncertainty.
- Collect and preserve raw ADS acceleration/magnetic/PRY logs, raw reference orientation/magnetic logs, timestamps, fault-injection markers, analysis scripts/settings, and any OBCC logs used for v1.0 delivery evidence.
- This activity is a demonstration and repeatability characterization. Record sample counts, repeatability, plausibility checks, and any execution-approved plausibility tolerance. Do not claim formal attitude accuracy unless a new modeled constraint and statistical criterion are added.
- Execute or disposition fault-hardening cases: I2C NACK, stuck bus, wrong address, partial read, invalid acceleration, magnetic disturbance, stale data, non-finite PRY behavior, and recovery. Invalid/faulted samples shall be excluded from plausibility/repeatability only if ADS marks or handles them as invalid; they shall not be accepted as valid attitude outputs.
- For `v1.0`, include modeled I2C `<=5 ms` timeout and Process/Calculate `<5 ms` as pass/fail timing viewpoints where instrumented. For `v0.2`, record the absence of an explicit I2C timeout constraint as a modeling gap and still report observed no-blocking behavior.

## Expected report locations

Reports should reference this modeled definition and store evidence under:

- `../results/ADS-IVV-FC-ATT/v0.1/`
- `../results/ADS-IVV-FC-ATT/v0.2/`
- `../results/ADS-IVV-FC-ATT/v0.3/`
- `../results/ADS-IVV-FC-ATT/v1.0/`

Each report shall identify referenced model views/elements, selected SSIV/version, as-tested configuration, orientation/magnetic reference method, raw evidence, analysis settings, actual environmental conditions, pass/fail or N/A rationale, deviations, anomalies, waivers, limitations, and retest status.

## Status

Modeled definition ready for review. Execution remains pending.
