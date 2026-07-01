# ADS-IVV-FC-INIT — peripheral initialization-state verification definition

**IADT method:** Testing / Demonstration with supporting Analysis.

**IVV source category:** functional chain / scenario and linked constraints.

**Selected SSIV/development scope:** ADS `v0.1`, `v0.2`, `v0.3`, and `v1.0`. Runtime execution applies to `v0.1`, `v0.2`, and `v1.0`; `v0.3` is a PCB-delivery N/A branch because no runtime logical components, component exchanges, functional allocations, firmware boot behavior, or functional chains are modeled.

**Traceability targets:** `ADS-CAP-INIT`, feared events `ADS-FE-SILENT-SENSOR-FAIL` and `ADS-FE-STUCK-LOOP`, and linked constraints for no-blocking behavior, UART timeout `<=5 ms`, I2C timeout `<=5 ms` where modeled, and process/calculate timing where relevant. The `v0.3` N/A rationale may also reference `ADS-CAP-PCB` / `ADS-CAP-DELIVERY`.

**References cited in diagrams:** IVV, NASA-SE, GPS/UBX, IMU/I2C, SW/statistics references, and the ADS MBSE IVV plan `../README.md`. No external research was performed for this definition.

## Source-view copies

All D2/PNG views for the selected ADS versions were copied under `source_views/` so reports can reference a stable test-definition package:

- `source_views/v0.1/` — physical, logical, allocation, GPS position chain, Serial logging chain. Used for UBX/GPS init state and Serial0/Serial1 setup context.
- `source_views/v0.2/` — physical, logical, allocation, GPS, angular velocity, attitude estimation, peripheral initialisation, Serial logging chains. Used for UBX/GPS and ICM20948 init-state coverage.
- `source_views/v0.3/` — physical PCB delivery view. Used only for N/A rationale.
- `source_views/v1.0/` — physical, logical, allocation, GPS, angular velocity, attitude estimation, peripheral initialisation chains. Used for integrated ADS Processing / OBCC init-state coverage.

## Test-definition views

| View | Purpose |
|---|---|
| `definition_views/ADS_IVV_FC_INIT_view1_source_chain_inventory.d2/png` | Source-chain inventory for v0.1, v0.2, and v1.0 initialization-state behavior, plus explicit v0.3 PCB-only N/A rationale and traceability. |
| `definition_views/ADS_IVV_FC_INIT_view2_physical_test_setup.d2/png` | Physical boot/fault setup with selected ADS UUT, current-limited power supply, boot/reset control, PC/OBCC data loggers, GPS/IMU fault-injection harnesses, ambient monitor, analysis station, temporary PLs, and environmental/pass constraints. |
| `definition_views/ADS_IVV_FC_INIT_view3_verification_functional_allocation.d2/png` | Verification-only allocation to the selected ADS version, human test conductor, power/reset means, data logger, fault harnesses, ambient monitor, and analysis/review station. |
| `definition_views/ADS_IVV_FC_INIT_view4_boot_fault_sequence.d2/png` | Functional-chain style boot and peripheral-fault sequence for nominal boot, GPS fault cases, IMU fault cases, timeout/no-hang analysis, evidence preservation, and v0.3 N/A stop rule. |
| `definition_views/ADS_IVV_FC_INIT_view5_evidence_traceability_interfaces.d2/png` | Evidence and traceability interfaces for source views, configuration, equipment records, boot/fault evidence, supporting analysis, pass/fail/N/A disposition, and expected report archive. |

## Version coverage and pass/fail rules

| Version | Initialization-chain coverage | Pass/fail constraints |
|---|---|---|
| `v0.1` | UBX/GPS initialization and Serial0/Serial1 setup context from allocation and Serial logging views: `Get UBX-G7020-KT init state`, `Collect peripheral init states`, `Init Serial0 and Serial1`, and Serial0 evidence logging. No IMU is modeled. | Pass if nominal boot preserves evidence and reports the expected UBX/GPS init state plus Serial0/Serial1 setup evidence without unexpected reset/hang. GPS disconnected, silent, or no-fix cases shall produce degraded/error/unavailable state evidence without firmware reset/hang and without accepting the state as nominal/ready. UART read timeout `<=5 ms`, no-blocking, and process/calculate timing viewpoints are checked where instrumented. |
| `v0.2` | Peripheral initialisation chain and Serial0 evidence path: UBX/GPS state, ICM20948 state, `Collect peripheral init states`, `Init Serial0 and Serial1`, and Serial0 logging. | Pass if nominal boot reports expected UBX/GPS and ICM20948 init states and Serial setup evidence. GPS disconnected/silent/no-fix and IMU disconnected/NACKing cases shall produce degraded/error/unavailable states without reset/hang. UART timeout `<=5 ms`, no-blocking, Variable Getter, and process/calculate `<5 ms` viewpoints are checked where instrumented. Explicit I2C timeout is not modeled in v0.2; report observed no-hang behavior as a modeling gap rather than claiming the v1.0 timeout requirement. |
| `v0.3` | No runtime initialization chain is modeled. Source package is a PV1-only PCB delivery model with GPS/IMU/connector physical components, footprints, UART/I2C/3V3 traces, and manufacturing note. | Pass/N/A if 1/1 v0.3 source view is reviewed and no LC, CE, functional allocation, functional chain, boot firmware behavior, or initialization-state scenario exists. Fail if runtime initialization behavior is credited to v0.3 without a modeled runtime baseline. |
| `v1.0` | Peripheral initialisation chain in integrated ADS Processing / OBCC context: GPS and ICM20948 init states are collected by OBCC from ADS Processing; no ADS Serial0 chain is modeled. | Pass if nominal boot reports GPS and ICM20948 init states at the ADS/OBCC observation point and preserves boot evidence. GPS disconnected/silent/no-fix and IMU disconnected/NACKing cases shall produce degraded/error/unavailable states without firmware reset/hang and without OBCC treating invalid states as nominal/ready. UART timeout `<=5 ms`, I2C timeout `<=5 ms`, no-blocking, Variable Getter, and process/calculate `<5 ms` viewpoints are pass/fail constraints where applicable/instrumented. |

## Cross-version pass/fail criteria

- Nominal boot reports the expected modeled peripheral initialization states for the selected runtime baseline.
- Boot/reset evidence is preserved with timestamps, firmware commit/build, hardware revision, UUT ID, fault-harness state, supply/current record, and actual ambient conditions.
- Disconnected, silent, no-fix, or NACKing peripherals produce degraded/error/unavailable state evidence rather than nominal/ready state evidence.
- No unexpected firmware reset, watchdog reset, unrecovered hang, or uncontrolled blocking is observed during nominal or injected-fault boot trials.
- UART read functions return data or timeout/error in `<=5 ms` for all runtime baselines where instrumented.
- v1.0 I2C read functions return data or timeout/error in `<=5 ms`; v0.2 I2C timeout remains a visible modeling gap.
- Process/calculate timing `<5 ms` is checked where relevant and instrumented; if instrumentation is unavailable, report the limitation rather than passing silently.

## Viewpoints

- **Statistical significance:** a single successful boot/fault pass is functional evidence only. If a reliability claim is made, use exact zero-failure logic such as `29/29` to support R90/C95 or `59/59` to support about R95/C95; do not infer reliability from unsupported repeated samples. For timing 95/95 claims, use `n = 59` representative samples with every sample inside the modeled limit.
- **Fault hardening:** GPS disconnected, GPS silent/UART timeout, GPS no-fix, IMU disconnected, IMU NACK/wrong-address behavior where applicable, reset/hang detection, current-limit/brownout observation, boot evidence preservation, and recovery after restoring nominal harness state.
- **Configuration control:** every execution report names selected ADS version/SSIV, source-view copy, hardware revision/BOM, firmware commit/build, UUT serial/identifier, power/reset/logger/fault-harness configuration, operator, reviewer, and deviations.
- **Environmental context:** the modeled ambient thermometer/hygrometer is read before repetition groups. Record actual temperature/humidity, equipment ID, and calibration/status. No fixed ambient-temperature requirement is assumed unless a later controlled requirement adds one.

## Required execution conditions

- Select one ADS version per execution and record whether the verdict is runtime pass/fail (`v0.1`, `v0.2`, `v1.0`) or v0.3 N/A.
- Configure current-limited power and boot/reset control before connecting the UUT; record current limit, supply voltage, and abnormal current/reset behavior.
- Configure and verify the PC Serial0 logger for `v0.1`/`v0.2` or OBCC/debug data capture for `v1.0`; preserve raw logs before analysis.
- Mark every fault-harness state in the log before reset/boot capture: nominal, GPS disconnected/silent/no-fix, and IMU disconnected/NACKing where applicable.
- Preserve raw boot logs, fault markers, power/current records, ambient records, analysis scripts/settings, pass/fail rationale, deviations, anomalies, waivers, limitations, and retest status.

## Expected report locations

Reports should reference this modeled definition and store evidence under:

- `../results/ADS-IVV-FC-INIT/v0.1/`
- `../results/ADS-IVV-FC-INIT/v0.2/`
- `../results/ADS-IVV-FC-INIT/v0.3/`
- `../results/ADS-IVV-FC-INIT/v1.0/`

Each report shall identify referenced model views/elements, selected SSIV/version, as-tested configuration, initialization-state observation point, raw boot/fault evidence, supporting analysis settings, actual environmental/equipment conditions, pass/fail or N/A rationale, deviations, anomalies, waivers, limitations, and retest status.

## Status

Modeled definition ready for review. Execution remains pending.

## Assumptions and gaps

- Controlled SSIV documents and mission/capability/feared-event model elements remain inferred from the ADS MBSE plan; IDs used here are placeholders from that plan.
- v0.2 lacks an explicit modeled I2C timeout constraint; only observed no-hang behavior can be reported for v0.2 IMU fault cases unless the model is updated.
- Exact boot record schema, readiness/degraded/error enum names, logger timebase tolerance, and firmware instrumentation hooks must be fixed before execution.
- v1.0 does not model ADS Serial0 logging; use OBCC/debug capture as the evidence path unless a later model update adds a Serial0 test interface.
