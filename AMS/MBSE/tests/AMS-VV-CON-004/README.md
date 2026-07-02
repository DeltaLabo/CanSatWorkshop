# AMS-VV-CON-004 — Processing timing and non-blocking verification definition

- **SSIV / development version:** AMS v1.0 final acceptance / flight readiness.
- **IADT method:** Testing with supporting Analysis.
- **Scope:** `Calculate altitude`, `Process temperature`, and AMS callable paths outside the I2C/UART wait points allowed by the model.
- **Explicit exclusion:** I2C read timing/recovery is not re-tested here; it is referenced to `AMS-VV-CON-003`.
- **Traceability:** `[C] All Process or Calculate functions must take < 5 ms`; `[C] No blocking operations besides I2C or UART comms`; `AMS-UC-MeasureAtmosphere`; `AMS-FE-SensorBusFault`; `AMS-FE-SchedulerBlock`.
- **References cited in diagrams:** IVV, shared ADS/AMS freshness contract [`../../../../PM&SE/contracts/sensor_obcc_freshness_contract.md`](../../../../PM&SE/contracts/sensor_obcc_freshness_contract.md), AMS-R5 (statistics), PM&SE/IVV timing/fault semantics.
- **Expected report path:** `AMS/MBSE/tests/results/AMS-VV-CON-004/report.md`.

## Covered candidate activities

This model-defined activity covers candidate `AMS-VV-CON-004` (`Process/Calculate functions < 5 ms`) and, if executed completely with the modeled static and dynamic coverage evidence, candidate `AMS-VV-CON-005` (`No blocking operations besides I2C or UART comms`). It is also the non-blocking/status-propagation leg of the `AMS-V10-DATA-FRESHNESS` update path.

## AMS-BLK-004 evidence/report checklist

Non-blocking closure is not a pass unless the report includes all AMS-BLK-004 evidence below:

1. 100% inventory of AMS getters, OBCC collection paths, and AMS callable paths outside the explicitly allowed I2C/UART wait points.
2. Static callable-path review proving no unbounded blocking, hidden waits, unbounded retries, or unmodeled data crossings on those paths.
3. Dynamic timing/non-blocking traces for `Calculate altitude`, `Process temperature`, representative getter/OBCC paths, scheduler liveness/heartbeat, and representative fault/status propagation.
4. Explicit shared-status propagation using `VALID`, `STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, and `INIT_FAIL`; timeout/fault/init/no-data cases shall not be converted to fresh `VALID` outputs.
5. Pointer ownership/lifetime/null-policy evidence by reference to `AMS-VV-API-001`.
6. I2C wait timing, timeout, fault, stale-valid, and recovery evidence by explicit dependency on `AMS-VV-CON-003` rather than by retesting here.

The shared freshness contract remains applicable to any freshness/non-blocking claim: AMS supports `5 Hz` OBCC request/response, `2 s` telemetry can treat data as fresh only when `status == VALID` and `age_ms <= 400 ms`, and non-`VALID` conditions shall preserve the shared status.

## Baseline views copied

Baseline copies of all AMS v1.0 D2/PNG views are in `baseline/` and are refreshed to the selected v1.0 freshness/status/non-blocking definition baseline.

## Test-definition views

| View | Purpose |
|---|---|
| `AMS_VV_CON_004_view1_physical_testbench.d2` | Physical testbench links for host PC profiler/logger, timer harness, bench power, optional fault/stimulus injector, and evidence repository. |
| `AMS_VV_CON_004_view2_logical_testbench.d2` | Logical testbench with VV-only timing/non-blocking instrumentation and evidence record exchanges. |
| `AMS_VV_CON_004_view3_functional_allocation_testbench.d2` | Allocation of UUT functions, VV-only harness functions, human/operator functions, bench equipment functions, and pass/fail constraints. |
| `AMS_VV_CON_004_view4_processing_timing_chain.d2` | Timing functional chain for `Calculate altitude` and `Process temperature` with representative, boundary, and invalid input vectors. |
| `AMS_VV_CON_004_view5_nonblocking_analysis_chain.d2` | Supporting analysis chain mapping AMS callable paths and allowed I2C/UART blocking points. |

Rendered PNGs with matching names are generated beside each D2 file.

## Pass/fail constraints

Pass only if all modeled constraints in the D2 views are satisfied and the execution report supplies the predeclared timing, non-blocking, and status-propagation evidence below:

1. `Calculate altitude` completes with `t_exec + U95 < 5.000 ms` for representative and boundary input sets.
2. `Process temperature` completes with `t_exec + U95 < 5.000 ms` for representative and boundary input sets.
3. A final 95/95 deadline claim uses `59/59` in-limit timings per function/input-set; smaller sets must be labeled screening or characterization only.
4. Invalid/boundary sensor values and non-`VALID` shared-status inputs (`STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, `INIT_FAIL`) do not cause overflow, unhandled infinite values, memory corruption, infinite loops, unbounded retry, scheduler blockage, stale success masking, or conversion to fresh `VALID`; invalid/NaN inputs may produce flagged non-`VALID` outputs only when control returns normally and status/error handling remains explicit.
5. No unbounded blocking exists outside allowed I2C or UART communication waits.
6. Runtime sensor/getter faults return bounded error/result codes mapped to the shared enum (`TIMEOUT`, `SENSOR_FAULT`, `INIT_FAIL`, `STALE`, or `NO_DATA` as applicable) and do not block or brick the scheduler; old data is not returned as fresh `VALID`.
7. I2C read wait timing, timeout/fault status mapping, stale-valid prevention, and recovery are excluded from this activity and must reference `AMS-VV-CON-003` evidence.
8. Non-blocking closure requires the full AMS-BLK-004 checklist above: 100% getter/OBCC/callable-path inventory, static review, dynamic trace evidence, explicit status propagation, pointer-policy reference to `AMS-VV-API-001`, and `AMS-VV-CON-003` dependency; any smaller dynamic set remains screening.

## Statistical and fault-hardening viewpoints

- **Statistical significance:** AMS-R5 / IVV timing policy is applied: `59/59` in-limit samples support a 95/95 non-parametric one-sided deadline claim. The report records timer resolution, instrumentation overhead, raw timings, and `U95`.
- **Fault hardening:** Boundary, `STALE`/`NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, `INIT_FAIL`, invalid, and NaN inputs are modeled. Forbidden outcomes include overflow, unhandled infinite values, memory corruption, infinite loop, scheduler blockage, unbounded retry, stale success masking, or conversion of non-`VALID` conditions into fresh `VALID` outputs.
- **Non-blocking analysis:** Allowed waits are classified as I2C or UART communication waits only. I2C timing proof is by reference to `AMS-VV-CON-003`; this activity covers processing/calculation and other AMS callable paths.

## Assumptions recorded

- No user disambiguation was requested per orchestration instructions; the selected SSIV is AMS v1.0 final acceptance.
- Representative and boundary vectors are to be bound in the execution report to the implemented units/ranges; the model defines the coverage intent and pass/fail constraints.
- The optional fault/stimulus injector may be implemented by host-driven firmware inputs if no separate hardware injector is used; the report must record the as-tested configuration.
- The AMS-BLK-004 checklist and shared-status propagation are represented in this README and the D2 views for this phase; execution evidence, actual vectors, code/build IDs, scheduler hook names, and deviations remain report-time records.
