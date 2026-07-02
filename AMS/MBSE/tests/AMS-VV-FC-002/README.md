# AMS-VV-FC-002 — Peripheral initialisation and startup-fault test definition

- **SSIV / development version:** AMS v1.0 final acceptance / flight readiness.
- **IADT method:** Testing / Demonstration.
- **Purpose:** Verify the v1.0 peripheral initialisation functional chain covering BME280 init-state request/response, OBCC collection, and startup-fault behavior.
- **Traceability:** `AMS-UC-InitializePeripheral`, `AMS-FE-SensorBusFault`, `AMS-FE-StartupFault`, and constraints for variable-getter semantics, I2C bounded timeout behavior, and no unbounded blocking.
- **References cited in diagram titles/comments:** IVV, shared ADS/AMS freshness contract [`../../../../PM&SE/contracts/sensor_obcc_freshness_contract.md`](../../../../PM&SE/contracts/sensor_obcc_freshness_contract.md), AMS-R1 (BME280), AMS-R2 (I2C), AMS-R5 (statistics).
- **Expected report path:** `AMS/MBSE/tests/results/AMS-VV-FC-002/report.md`.

## Shared freshness/status contract alignment

This activity is the startup/init-state leg of `AMS-V10-DATA-FRESHNESS`. The shared contract requires AMS-to-OBCC responses to support `5 Hz` request/response and requires each `2 s` telemetry push to treat AMS init/status data as fresh only when `status == VALID` and `age_ms <= 400 ms`. The only allowed external status values are `VALID`, `STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, and `INIT_FAIL`.

Startup initialization failure shall map to `INIT_FAIL` or another applicable non-`VALID` status that preserves the safety-relevant cause. A previous boot result, default success value, or old init state shall not remain marked `VALID` after init failure, timeout, fault, reset, or no-data conditions.

## Baseline views copied

Baseline copies of all AMS v1.0 D2/PNG views are in `baseline/` and are refreshed to the selected v1.0 freshness/status definition baseline.

## Test-definition views

| View | Purpose |
|---|---|
| `AMS_VV_FC_002_view1_physical_testbench.d2` | Physical testbench links for host PC/logger, bench power/power-cycle fixture, I2C fault/disconnect fixture, and ambient thermometer. |
| `AMS_VV_FC_002_view2_logical_testbench.d2` | Logical testbench with VV-only init-state instrumentation, test operator, host logger, power-cycle fixture, fault fixture, ambient logger, and evidence repository. |
| `AMS_VV_FC_002_view3_functional_allocation_testbench.d2` | Allocation of UUT, VV-only instrumentation, operator, equipment, and evidence functions with pass/fail constraints. |
| `AMS_VV_FC_002_view4_nominal_boot_init_state_chain.d2` | Nominal boot/init-state sequence and evidence/statistics chain. |
| `AMS_VV_FC_002_view5_startup_fault_init_state_chain.d2` | Startup-fault sequence for absent/NACK BME280 and held-bus cases, including OBCC critical startup-fault collection and evidence logging. |

Rendered PNGs with matching names are generated beside each D2 file.

## Pass/fail constraints

Pass only if all modeled constraints in the D2 views are satisfied and the execution report supplies the predeclared freshness/status evidence below:

1. Nominal boot/init returns a current BME280 init state with shared status `VALID`; if freshness/currentness is claimed, the OBCC observation has timestamp/sample-ID or boot-ID evidence, monotonic correlation, status `VALID`, and `age_ms <= 400 ms`, and OBCC collects the same state before flight-readiness OK.
2. Use `29/29` nominal boot successes for an R90/C95 binary success claim; smaller repetition counts are screening only.
3. Induced startup faults for absent/disconnected or NACKing BME280 and held SDA/SCL return `INIT_FAIL`, `TIMEOUT`, `SENSOR_FAULT`, or another applicable non-`VALID` shared status and do not create unbounded blocking.
4. Faulted states are never reported as nominal OK/`VALID`; no stale init state, previous boot result, default success value, old data, or ambiguous status is accepted.
5. Exact execution evidence is predeclared and recorded: boot IDs, power-cycle count, fault-fixture configuration, stable 3V3/common-ground evidence, sample/boot timestamps or equivalent monotonic correlation, `age_ms` where applicable, shared status values, ambient conditions, UUT/firmware/build IDs, and deviations/anomalies.
6. Detailed environmental read timeout proof and recovery after released runtime I2C faults are dependencies on `AMS-VV-CON-003`; this activity does not claim that coverage.

## Statistical and fault-hardening viewpoints

- **Nominal statistical viewpoint:** `29/29` successful nominal boot/init trials support an R90/C95 binary success claim. Fewer nominal boots shall be labelled workshop screening in the report.
- **Fault statistical viewpoint:** `29/29` pass per induced startup-fault mode is required for an R90/C95 binary fault-response claim. Smaller fault samples are screening.
- **Fault hardening:** explicitly covers absent/disconnected BME280, forced NACK, held SDA low, held SCL low, `INIT_FAIL`/`TIMEOUT`/`SENSOR_FAULT` status propagation, stale/default OK prevention, no old data marked `VALID`, startup responsiveness, and evidence preservation.
- **Non-duplication:** `AMS-VV-CON-003` remains the owner for environmental measurement I2C read `≤ 5 ms` proof and recovery after released runtime I2C faults.

## Conservative assumptions recorded

- Development version is fixed by orchestration as AMS v1.0 final acceptance; no user disambiguation was requested.
- The BME280 init-state result is treated as a current status value compatible with the project variable-getter semantics and the shared ADS/AMS freshness/status contract.
- Shared freshness/status fields and the `INIT_FAIL`/no-stale-valid oracle are represented in this README and the D2 views for this phase; execution evidence, actual harness IDs, code/build IDs, and deviations remain report-time records.
- A startup BME280 failure is treated as a critical startup fault that prevents false flight readiness.
