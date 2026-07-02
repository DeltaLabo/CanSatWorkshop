# AMS-VV-CON-003 — I2C read timeout ≤ 5 ms test definition

- **SSIV / development version:** AMS v1.0 final acceptance.
- **IADT method:** Testing with supporting Analysis.
- **Confirmed scope:** environmental measurement I2C reads only: `[F] Read pressure` and `[F] Read temperature`. Peripheral-init, chip-ID, and hidden driver setup reads are out of scope unless they are reachable inside those environmental read functions.
- **Traceability:** constraint `[C] All I2C read functions must have a timeout ≤ 5 ms` as scoped above; `AMS-FE-SensorBusFault`; `AMS-UC-MeasureAtmosphere`.
- **References cited in diagram titles:** IVV, shared ADS/AMS freshness contract [`../../../../PM&SE/contracts/sensor_obcc_freshness_contract.md`](../../../../PM&SE/contracts/sensor_obcc_freshness_contract.md), AMS-R2 (I2C), AMS-R5 (statistics).
- **Expected evidence/report path:** `AMS/MBSE/tests/results/AMS-VV-CON-003/`.

## Shared freshness/status contract alignment

This activity supplies the I2C timeout/fault evidence dependency for `AMS-V10-DATA-FRESHNESS`, `AMS-VV-API-001`, `AMS-VV-FC-001`, `AMS-VV-FC-002`, and `AMS-VV-CON-004`. It retains low-level I2C evidence, but the external AMS-to-OBCC result shall map to the shared enum: `VALID`, `STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, `INIT_FAIL`.

- A bounded read timeout maps to `TIMEOUT` at the AMS-to-OBCC boundary.
- NACK, bus error, held SDA/SCL, absent sensor after initialization, or value/sensor runtime fault maps to `SENSOR_FAULT` or another applicable non-`VALID` shared status while retaining the low-level cause in the evidence.
- Failed or incomplete startup initialization maps to `INIT_FAIL` or `NO_DATA` as applicable; stale last-good values after any timeout/fault/init/no-data condition shall not be reported as `VALID`.
- Where freshness is claimed, evidence shall include sample ID/sequence, timestamps or equivalent monotonic correlation, `age_ms`, status, and the `5 Hz` request/response context; `2 s` telemetry packaging may use the value as fresh only when `status == VALID` and `age_ms <= 400 ms`.

## Baseline views copied

Baseline copies of all AMS v1.0 D2/PNG views are in `baseline/` and are refreshed to the selected v1.0 freshness/status definition baseline.

## Test-definition views

| View | Purpose |
|---|---|
| `AMS_VV_CON_003_view1_physical_testbench.d2` | Physical testbench links for host PC, logic analyzer, fault-injection harness, and bench power. |
| `AMS_VV_CON_003_view2_logical_testbench.d2` | VV-only timeout instrumentation LC and component exchanges for test command/result flow. |
| `AMS_VV_CON_003_view3_functional_allocation_testbench.d2` | Allocation of operator, equipment, environmental, and VV-only instrumentation functions. |
| `AMS_VV_CON_003_view4_nominal_i2c_read_timing_chain.d2` | Nominal timing sequence over environmental pressure and temperature I2C reads. |
| `AMS_VV_CON_003_view5_fault_timeout_recovery_chain.d2` | Fault-injection and mandatory recovery sequence for NACK/absent sensor, held SDA, held SCL, and timeout/no-response cases. |
| `AMS_VV_CON_003_view6_timeout_implementation_analysis_chain.d2` | Supporting analysis sequence mapping environmental I2C read functions to implementation call paths and timeout configuration. |

## Pass/fail constraints

Pass only if all modeled constraints in the D2 views are satisfied and the execution report supplies the predeclared timeout/fault/status evidence below:

1. For each environmental I2C read function (`Read pressure`, `Read temperature`), collect `59/59` nominal samples with `t_read + U95 ≤ 5.000 ms`.
2. Timing boundary is read-function entry to returned success/error status; instrumentation overhead is recorded.
3. Fault modes include NACK/absent sensor, held SDA, held SCL, and timeout/no-response cases for each environmental I2C read function.
4. Faulted reads return only bounded statuses within `5.000 ms` including uncertainty and map externally to the shared enum: `TIMEOUT` for timeout/no-response, `SENSOR_FAULT` for runtime sensor/bus/value faults such as NACK/held SDA/held SCL/absent sensor after initialization, and `INIT_FAIL` or `NO_DATA` for initialization/no-data conditions as applicable.
5. No stale, old, default, or previous data is reported as `VALID`; no watchdog reset, power-cycle requirement, deadlock, or lost test-command responsiveness occurs.
6. **Mandatory:** after fault release, the next modeled recovery read succeeds without reset and with `t_read + U95 ≤ 5.000 ms`.
7. Supporting analysis maps 100% of environmental AMS Processing I2C read functions to implementation call paths and finds no additional environmental read path without a `≤ 5 ms` timeout.
8. Evidence records preserve low-level I2C cause codes, shared status mapping, sample/sequence IDs, timestamps or monotonic correlation, `age_ms` where freshness is claimed, instrumentation overhead, and any recovery/deviation notes.

## Environmental and configuration conditions

- Ambient temperature is recorded before repetitions using the modeled ambient thermometer function; nominal bench acceptance range is `20–30 °C` unless the campaign defines a stricter condition.
- Bench supply provides stable 3V3/common ground and records voltage/current before and after each timing batch.
- Harness pullups, capacitance, and any fault-adapter deviations are recorded in the evidence report because the harness can alter I2C timing.
- Shared freshness/status mapping and the no-stale-valid oracle are represented in this README and the D2 views for this phase; execution evidence, actual harness IDs, code/build IDs, low-level cause-code names, and deviations remain report-time records.
