# AMS-VV-FC-002 — Peripheral initialisation and startup-fault test definition

- **SSIV / development version:** AMS v1.0 final acceptance / flight readiness.
- **IADT method:** Testing / Demonstration.
- **Purpose:** Verify the v1.0 peripheral initialisation functional chain covering BME280 init-state request/response, OBCC collection, and startup-fault behavior.
- **Traceability:** `AMS-UC-InitializePeripheral`, `AMS-FE-SensorBusFault`, `AMS-FE-StartupFault`, and constraints for variable-getter semantics, I2C bounded timeout behavior, and no unbounded blocking.
- **References cited in diagram titles/comments:** IVV, AMS-R1 (BME280), AMS-R2 (I2C), AMS-R5 (statistics).
- **Expected report path:** `AMS/MBSE/tests/results/AMS-VV-FC-002/report.md`.

## Baseline views copied

Untouched baseline copies of all AMS v1.0 D2/PNG views are in `baseline/`.

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

Pass only if all modeled constraints in the D2 views are satisfied, including:

1. Nominal boot/init returns a valid, current BME280 init state and OBCC collects the same state before flight-readiness OK.
2. Use `29/29` nominal boot successes for an R90/C95 binary success claim; smaller repetition counts are screening only.
3. Induced startup faults for absent/disconnected or NACKing BME280 and held SDA/SCL return a bounded critical startup fault/status and do not create unbounded blocking.
4. Faulted states are never reported as nominal OK; no stale init state, previous boot result, default success value, or ambiguous status is accepted.
5. Ambient conditions, stable 3V3/common ground, exact power-cycle count, and fault-fixture configuration are recorded with the evidence.
6. Detailed environmental read timeout proof and recovery after released runtime I2C faults are dependencies on `AMS-VV-CON-003`; this activity does not claim that coverage.

## Statistical and fault-hardening viewpoints

- **Nominal statistical viewpoint:** `29/29` successful nominal boot/init trials support an R90/C95 binary success claim. Fewer nominal boots shall be labelled workshop screening in the report.
- **Fault statistical viewpoint:** `29/29` pass per induced startup-fault mode is required for an R90/C95 binary fault-response claim. Smaller fault samples are screening.
- **Fault hardening:** explicitly covers absent/disconnected BME280, forced NACK, held SDA low, held SCL low, stale/default OK prevention, startup responsiveness, and evidence preservation.
- **Non-duplication:** `AMS-VV-CON-003` remains the owner for environmental measurement I2C read `≤ 5 ms` proof and recovery after released runtime I2C faults.

## Conservative assumptions recorded

- Development version is fixed by orchestration as AMS v1.0 final acceptance; no user disambiguation was requested.
- The BME280 init-state result is treated as a current status value compatible with the project variable-getter semantics.
- A startup BME280 failure is treated as a critical startup fault that prevents false flight readiness.
