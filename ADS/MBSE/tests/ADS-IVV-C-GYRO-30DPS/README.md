# ADS-IVV-C-GYRO-30DPS — angular-rate accuracy constraint verification definition

**IADT method:** Testing with supporting Analysis.

**IVV source category:** constraint. The activity also exercises linked component exchanges, allocation, and angular velocity functional chains where needed to verify the constraint.

**Selected SSIV/development scope:** all ADS MBSE versions currently present: `v0.1`, `v0.2`, `v0.3`, and `v1.0`. Constraint execution applies to `v0.2` and `v1.0`; `v0.1` and `v0.3` are explicit N/A branches.

**Model elements covered:** angular velocity chain, ICM20948 angular-rate readings, `Accuracy < 30 deg/s` constraint, I2C communication, v0.2 Loop/Serial0 collection evidence where used, and v1.0 ADS Processing / OBCC integrated delivery observation where applicable.

**Traceability targets:** constraint `<30 deg/s`, `ADS-CAP-IMU`, `ADS-FE-CORRUPT-MEASUREMENT`, and `ADS-FE-STUCK-LOOP`. N/A rationale may reference `ADS-CAP-PHY` for `v0.1` and `ADS-CAP-PCB` / `ADS-CAP-DELIVERY` for `v0.3`.

**References cited in diagrams:** IVV, NASA-SE, IMU/I2C, SW/statistics references, and the ADS MBSE IVV plan `../README.md`. No external research was performed for this definition.

## Source-view copies

All available D2/PNG source views for the selected scope were copied under `source_views/` so reports can reference a stable activity package:

- `source_views/v0.1/` — physical, logical, allocation, GPS position chain, and Serial logging chain; used only for N/A rationale.
- `source_views/v0.2/` — physical, logical, allocation, GPS, angular velocity, attitude estimation, peripheral initialisation, and Serial logging chains.
- `source_views/v0.3/` — physical PCB delivery view; used only for N/A rationale.
- `source_views/v1.0/` — physical, logical, allocation, GPS, angular velocity, attitude estimation, and peripheral initialisation chains.

## Definition-view catalogue

| View | Purpose |
|---|---|
| `definition_views/ADS_IVV_C_GYRO_30DPS_view1_source_constraint_inventory.d2/png` | Inventory of the `<30 deg/s` constraint, source angular-rate chain elements, I2C path, observation points, and v0.1/v0.3 N/A rationale. |
| `definition_views/ADS_IVV_C_GYRO_30DPS_view2_physical_reference_setup.d2/png` | Physical/reference setup: selected ADS UUT, angular-rate reference or still/rotation fixture, axis fixture, UUT selector, PC/OBCC logger, ambient monitor, fault injector, power, temporary PLs/CEs, and pass/fail notes. |
| `definition_views/ADS_IVV_C_GYRO_30DPS_view3_verification_functional_allocation.d2/png` | Verification-only functional allocation to the UUT observation interface, human conductor, reference fixture, logger, fault injector, ambient monitor, analysis tool, and quality/configuration authority. |
| `definition_views/ADS_IVV_C_GYRO_30DPS_view4_sample_analysis_fault_sequence.d2/png` | Functional-chain style sample, analysis, delivery-observation, and I2C/stale/saturation fault-hardening test sequence. |
| `definition_views/ADS_IVV_C_GYRO_30DPS_view5_evidence_traceability.d2/png` | Evidence and traceability view tying source views, configuration, calibration, raw logs, analysis outputs, reports, pass/fail rationale, and traceability targets. |

## Version coverage and pass/fail rules

| Version | Coverage | Pass/fail constraints |
|---|---|---|
| `v0.1` | N/A. Source views show GPS-only ADS behavior with no ICM20948 IMU, no I2C angular-rate CE, no angular velocity chain, and no `Accuracy < 30 deg/s` constraint. | Pass/N/A if all copied `v0.1` views are reviewed and no angular-rate constraint behavior is claimed. Fail if angular-rate evidence is credited to `v0.1` without a modeled IMU/angular-rate chain. |
| `v0.2` | Applies. Source model includes ICM20948 IMU, ADS Kinematic Sensing, I2C CE to Loop, angular velocity chain functions `Measure angular velocities`, `Respond to I2C Requests`, `Read angular velocities`, `Process angular velocities`, `Collect measurements`, and the `Accuracy < 30 deg/s` constraint. | Pass if valid angular-rate data propagate through the modeled chain to the v0.2 collection/evidence point and, for each accepted axis/rate condition, strict evidence uses `n = 59` matched ADS/truth samples with every guard-banded absolute angular-rate error `<30 deg/s` (`n >= 30` is characterization only unless a weaker claim is stated). Outputs shall be finite/fresh/in range, and saturated/stale/non-finite/I2C-fault data shall not be accepted as valid. Record the missing explicit v0.2 I2C `<=5 ms` timeout as a model gap while still observing no-blocking behavior. |
| `v0.3` | N/A. Source model is a PCB delivery with ICM20948 hardware and I2C traces but no LC, CE, allocation, functional chain, or `<30 deg/s` behavioral constraint. | Pass/N/A if the single `v0.3` source view is reviewed and physical I2C traces are not credited as constraint verification. Fail if runtime angular-rate behavior is claimed from this PCB-only baseline without an applicable integrated behavior model. |
| `v1.0` | Applies. Source model includes ICM20948 on ADS PCB, I2C CE through the integrated ADS/backplane/OBCC path to ADS Processing, angular velocity chain functions, `Accuracy < 30 deg/s`, I2C timeout `<=5 ms`, and ADS Processing to OBCC `Pointers`/`Returns` delivery interfaces. | Pass if valid angular-rate data propagate through the modeled chain to ADS Processing and the integrated ADS/OBCC observation point where applicable and, for each accepted axis/rate condition, strict evidence uses `n = 59` matched ADS/truth samples with every guard-banded absolute angular-rate error `<30 deg/s` (`n >= 30` is characterization only unless a weaker claim is stated). Every relevant I2C read shall return data or timeout/error in `<=5 ms`; outputs shall remain finite/fresh/in range; saturated/stale/non-finite/I2C-fault data shall not be accepted as valid by ADS Processing or OBCC. |

## Statistical and fault-hardening viewpoints

- **Approved truth method:** motors plus a calibrated/reliable tachometer are an approved workshop truth path. Convert tachometer speed using `deg/s = RPM × 6`, record tachometer asset/calibration or function-check evidence, verify motor setpoint stability before sampling, and document axis alignment, fixture slip/vibration, timestamp correlation, power, and ambient conditions. If tachometer reliability/calibration is inadequate, use a calibrated rate table or mark the motor/tachometer run characterization only.
- **Statistical significance:** strict angular-rate evidence uses `n = 59` matched ADS/truth samples per selected axis/rate condition with every guard-banded absolute error `<30 deg/s`. A smaller `n >= 30` continuous-accuracy set may support characterization if the report states the weaker basis and retains bias, standard deviation, confidence interval, and expanded uncertainty.
- **Accuracy calculation:** compare ADS `gx/gy/gz` against the calibrated tachometer/motor truth, calibrated rate table, or controlled still fixture after timestamp matching and validity filtering. The pass criterion is `<30 deg/s` after uncertainty/guard-band treatment.
- **Fault hardening:** inject or simulate I2C NACK, stuck bus, wrong address, partial read, stale sample, saturation/out-of-range value, non-finite value, and recovery. Invalid/faulted samples may be excluded from accuracy calculations only if ADS marks or handles them as invalid.
- **Delivery viewpoint:** for `v1.0`, evidence must include the integrated ADS/OBCC delivery or collection point unless a deviation is explicitly approved.

## Required execution conditions

Before execution, record ADS version, copied source-model package, hardware revision/BOM, firmware commit/build, UUT serial/identifier, logger configuration, motor/tachometer or alternate reference fixture method, rate setpoints/RPM logs, axis/sign convention, mounting/alignment, warm-up, power mode, timebase, tachometer calibration or function-check status, ambient temperature/humidity, and all deviations.

Required verification means are modeled as: motor plus calibrated tachometer truth fixture or calibrated rate table, controlled still fixture for zero-rate checks, axis alignment fixture, ADS UUT/version selector, PC/OBCC logger, human test conductor, ambient monitor, statistical analysis tool, current-limited supply or battery simulator, and I2C/IMU fault injector.

## Expected report locations

Reports should reference this modeled definition and store evidence under:

- `../results/ADS-IVV-C-GYRO-30DPS/v0.1/`
- `../results/ADS-IVV-C-GYRO-30DPS/v0.2/`
- `../results/ADS-IVV-C-GYRO-30DPS/v0.3/`
- `../results/ADS-IVV-C-GYRO-30DPS/v1.0/`

Each report shall identify referenced model views/elements, selected SSIV/version, as-tested configuration, angular-rate reference method, calibration/equipment IDs, raw ADS/truth/fault/ambient logs, analysis settings, actual environmental conditions, pass/fail or N/A rationale, deviations, anomalies, waivers, limitations, and retest status.

## Status

Modeled definition ready for review. Execution remains pending.

## Assumptions and gaps

- Controlled SSIV/current-development labels are inferred from `v0.1`, `v0.2`, `v0.3`, and `v1.0` folders.
- Mission/capability/feared-event IDs are placeholders from the ADS MBSE-wide IVV plan and need confirmation in a controlled trace model.
- Motor/tachometer is the selected workshop truth method for strict gyro claims when calibrated/reliable; exact motor, tachometer asset/calibration record, ambient monitor model, axis/rate matrix, timing tolerance method, and guard-band calculation must be fixed before execution.
- `v0.2` has no explicit modeled I2C timeout constraint; report this as a modeling gap while observing no-blocking/fault recovery behavior.
- `v1.0` delivery schema, timestamp source, and OBCC evidence capture mechanism must be identified for the as-tested configuration.
