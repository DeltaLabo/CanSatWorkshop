# ADS-IVV-FC-ANG — angular velocity functional-chain verification definition

**IADT method:** Testing with supporting Analysis.

**IVV source category:** functional chain / scenario and linked constraint.

**Selected SSIV/development scope:** ADS `v0.1`, `v0.2`, `v0.3`, and `v1.0`. Angular velocity functional-chain execution applies to `v0.2` and `v1.0`; `v0.1` is N/A because no IMU/angular-rate chain is modeled; `v0.3` is a PCB-delivery N/A branch because no logical components, component exchanges, allocations, or functional chains are modeled.

**Traceability targets:** `ADS-CAP-IMU`, constraint `Accuracy < 30 deg/s`, and feared events `ADS-FE-STUCK-LOOP`, `ADS-FE-CORRUPT-MEASUREMENT`. The N/A rationale may reference `ADS-CAP-PHY` for `v0.1` and `ADS-CAP-PCB` / `ADS-CAP-DELIVERY` for `v0.3`.

**References cited in diagrams:** IVV, NASA-SE, IMU/I2C, SW/statistics references, and the ADS MBSE IVV plan `../README.md`. No external research was performed for this definition.

## Source-view copies

All D2 views for the selected ADS versions were copied under `source_views/` so reports can reference a stable test-definition package:

- `source_views/v0.1/` — physical, logical, allocation, GPS position chain, Serial logging chain; used for angular-chain N/A rationale.
- `source_views/v0.2/` — physical, logical, allocation, GPS, angular velocity, attitude estimation, peripheral initialisation, Serial logging chains.
- `source_views/v0.3/` — physical PCB delivery view; used for N/A rationale.
- `source_views/v1.0/` — physical, logical, allocation, GPS, angular velocity, attitude estimation, peripheral initialisation chains.

## Test-definition views

| View | Purpose |
|---|---|
| `definition_views/ADS_IVV_FC_ANG_view1_source_chain_inventory.d2/png` | Angular velocity functional-chain inventory for v0.2 and v1.0, plus v0.1/v0.3 N/A rationale and traceability. |
| `definition_views/ADS_IVV_FC_ANG_view2_physical_test_setup.d2/png` | Physical angular-rate test setup, including selected ADS UUT, human test conductor, angular-rate truth/stimulus source, I2C/IMU fault injector, loggers, power supply, temporary PLs/CEs, pass/fail, timing, fault, and environment constraints. |
| `definition_views/ADS_IVV_FC_ANG_view3_verification_functional_allocation.d2/png` | Verification-only functional allocation to the selected ADS version, IVV conductor, angular-rate truth/stimulus source, data logger, statistical analysis tool, and quality/configuration authority. |
| `definition_views/ADS_IVV_FC_ANG_view4_test_chain_sequence.d2/png` | Functional-chain style verification sequence for nominal angular-rate accuracy testing, I2C/no-blocking checks, and I2C/stale/saturation fault cases. |
| `definition_views/ADS_IVV_FC_ANG_view5_results_traceability_interfaces.d2/png` | Results and traceability interfaces for evidence, analysis, model targets, references, deviations, waivers, limitations, and retest status. |

## Version coverage and pass/fail rules

| Version | Angular-chain coverage | Pass/fail constraints |
|---|---|---|
| `v0.1` | No IMU PC/LC/CE or angular velocity functional chain is modeled. | Pass/N/A if all v0.1 source views are reviewed and no angular-rate LC/CE/allocation/functional-chain behavior exists. Fail if angular-rate behavior is claimed from v0.1 without a modeled chain. |
| `v0.2` | Angular velocity chain: Measure angular velocities, Respond to I2C Requests, Read angular velocities, Process angular velocities, Collect measurements. Constraint `Accuracy < 30 deg/s` is attached to the IMU measurement function. | Pass if valid angular-rate data propagate through the modeled chain, at least 30 matched valid ADS/truth samples are analyzed for each accepted axis/rate condition, the accepted per-axis angular-rate error criterion including reference/instrument uncertainty or a 95/95 bound where claimed is `<30 deg/s`, outputs remain finite/recoverable, and invalid/stale/saturated/I2C-fault data are not accepted as valid. Record v0.2 missing I2C timeout as a modeling gap while observing no-blocking behavior. |
| `v0.3` | No angular velocity functional chain is modeled. Source package is a PV1-only PCB delivery model with physical GPS/IMU/backplane elements and UART/I2C/3V3 traces. | Pass/N/A if 1/1 v0.3 source view is reviewed, no angular-rate LC/CE/allocation/functional-chain behavior exists, and physical I2C traces are not credited as functional-chain behavior. Fail if behavior is claimed from v0.3 without a modeled logical/functional chain. |
| `v1.0` | Angular velocity chain: Measure angular velocities, Respond to I2C Requests, Read angular velocities, Process angular velocities, Collect measurements. IMU data flow through ADS Processing and may be delivered to OBCC through related Pointers/Returns interfaces. | Pass if valid angular-rate data propagate through the modeled chain to the ADS/OBCC observation point, at least 30 matched valid ADS/truth samples are analyzed for each accepted axis/rate condition, the accepted per-axis error criterion is `<30 deg/s`, v1.0 I2C reads return data or timeout/error in `<=5 ms`, outputs remain finite/recoverable, and invalid/stale/saturated/I2C-fault data are not accepted as valid by ADS Processing or OBCC. |

## Required execution conditions

- Select and record ADS version, source-model package, hardware revision, firmware commit/build, UUT serial/identifier, and data-logging configuration.
- Select the angular-rate truth method before execution: calibrated rate table/turntable or static zero-rate fixture. Record rate setpoints, axis convention/sign convention, fixture alignment, mounting, vibration/slip, temperature, warm-up, timebase, power mode, calibration status, and uncertainty.
- Collect and preserve raw ADS IMU logs, raw truth/reference logs, timestamps, fault-injection markers, analysis scripts/settings, and any OBCC logs used for v1.0 delivery evidence.
- Minimum nominal accuracy evidence is `>=30` matched valid ADS/truth samples per axis/rate condition. If a formal 95/95 claim is made, record the selected tolerance/confidence method and uncertainty guard band.
- Execute or disposition fault-hardening cases: I2C NACK, stuck bus, wrong address, partial read, stale sample, saturation/out-of-range value, and recovery. Invalid/faulted samples shall be excluded from accuracy calculations only if ADS marks or handles them as invalid; they shall not be accepted as valid angular-rate outputs.
- For `v1.0`, include the modeled I2C `<=5 ms` timeout as a pass/fail condition. For `v0.2`, record the absence of an explicit I2C timeout constraint as a modeling gap and still report observed no-blocking behavior.

## Expected report locations

Reports should reference this modeled definition and store evidence under:

- `../results/ADS-IVV-FC-ANG/v0.1/`
- `../results/ADS-IVV-FC-ANG/v0.2/`
- `../results/ADS-IVV-FC-ANG/v0.3/`
- `../results/ADS-IVV-FC-ANG/v1.0/`

Each report shall identify referenced model views/elements, selected SSIV/version, as-tested configuration, angular-rate truth method, raw evidence, analysis settings, actual environmental conditions, pass/fail or N/A rationale, deviations, anomalies, waivers, limitations, and retest status.

## Status

Modeled definition ready for review. Execution remains pending.
