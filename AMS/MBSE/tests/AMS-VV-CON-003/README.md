# AMS-VV-CON-003 — I2C read timeout ≤ 5 ms test definition

- **SSIV / development version:** AMS v1.0 final acceptance.
- **IADT method:** Testing with supporting Analysis.
- **Confirmed scope:** environmental measurement I2C reads only: `[F] Read pressure` and `[F] Read temperature`. Peripheral-init, chip-ID, and hidden driver setup reads are out of scope unless they are reachable inside those environmental read functions.
- **Traceability:** constraint `[C] All I2C read functions must have a timeout ≤ 5 ms` as scoped above; `AMS-FE-SensorBusFault`; `AMS-UC-MeasureAtmosphere`.
- **References cited in diagram titles:** IVV, AMS-R2 (I2C), AMS-R5 (statistics).
- **Expected evidence/report path:** `AMS/MBSE/tests/results/AMS-VV-CON-003/`.

## Baseline views copied

Untouched baseline copies of all AMS v1.0 D2/PNG views are in `baseline/`.

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

Pass only if all modeled constraints in the D2 views are satisfied, including:

1. For each environmental I2C read function (`Read pressure`, `Read temperature`), collect `59/59` nominal samples with `t_read + U95 ≤ 5.000 ms`.
2. Timing boundary is read-function entry to returned success/error status; instrumentation overhead is recorded.
3. Fault modes include NACK/absent sensor, held SDA, held SCL, and timeout/no-response cases for each environmental I2C read function.
4. Faulted reads return only bounded statuses (`TIMEOUT`, `NACK`, `BUS_ERROR`, or `SENSOR_UNAVAILABLE`) within `5.000 ms` including uncertainty.
5. No stale data is reported as valid `OK`; no watchdog reset, power-cycle requirement, deadlock, or lost test-command responsiveness occurs.
6. **Mandatory:** after fault release, the next modeled recovery read succeeds without reset and with `t_read + U95 ≤ 5.000 ms`.
7. Supporting analysis maps 100% of environmental AMS Processing I2C read functions to implementation call paths and finds no additional environmental read path without a `≤ 5 ms` timeout.

## Environmental and configuration conditions

- Ambient temperature is recorded before repetitions using the modeled ambient thermometer function; nominal bench acceptance range is `20–30 °C` unless the campaign defines a stricter condition.
- Bench supply provides stable 3V3/common ground and records voltage/current before and after each timing batch.
- Harness pullups, capacitance, and any fault-adapter deviations are recorded in the evidence report because the harness can alter I2C timing.
