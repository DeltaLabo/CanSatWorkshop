# OBCC-V02-GATE-001 — v0.2 bus/protocol and getter timing advancement gate

## Scope and selected version

- **Activity ID:** `OBCC-V02-GATE-001`
- **SSIV / version gate:** OBCC `v0.2 -> v0.3`
- **Chosen pending activity for this session:** Issue 002, bus/protocol bring-up, getter contracts, and bounded timing before a more integrated build.
- **IADT method(s):** Analysis + Testing.
- **IVV source categories:** component exchange, allocation, functional chain/scenario, constraint. Component/link presence is treated as a setup precondition for this gate; full PC/PL closure remains in the dedicated inspection gates and final readiness.
- **Primary v1.0 candidate-row mapping:** `OBCC-VV-CE-001`, `OBCC-VV-CE-003`, and timing/fault portions of `OBCC-VV-CON-004`.
- **Traceability targets:** `OBCC-UC-RuntimeFaultHandling`, `OBCC-FE-SchedulerBlocked`, startup/interface readiness.
- **Expected evidence/report path:** `OBCC/MBSE/tests/results/OBCC-V02-GATE-001/`.
- **Execution status:** modeled definition complete; execution and report evidence pending.

No `v0.2` Capella/D2 source views exist in this repository. This definition uses the copied `v1.0` OBCC model as target-architecture context and documents the source-baseline limitation in the diagrams.

## References

- Project IVV: `PM&SE/IVV.md`
- OBCC requirements and derived fault/getter behavior: `OBCC/README.md`
- Getter/result-code convention: `OBCC/Variable_Getter_Template.md`
- Telemetry and peripheral criticality context: `OBCC/LoRa_Frame.md`
- Test planning inventory: `OBCC/MBSE/tests/README.md`
- Orchestration plan: `OBCC/MBSE/tests/OBCC_test_definition_orchestration_plan.md`
- Source context copied from: `OBCC/MBSE/v1.0/`
- Legacy bring-up context: `OBCC/legacy_tests/BMP280/BMP280.ino`, `GPS/GPS.ino`, `INA219/INA219.ino`, `MPU6050/MPU6050.ino`, `lora/lora.ino`, and `3dmodel v1/` pin/settings snippets.

## Baseline/source-view copies

Copied source context is under `source_views/v1.0/` and includes the v1.0 README copy plus all eight source D2 views and rendered PNGs. There is no `source_views/v0.2/` because no v0.x Capella/D2 baseline is present.

## Verification-specific diagram catalogue

| View | D2 | Rendered PNG | Purpose |
|---|---|---|---|
| PV1 physical setup | `OBCC-V02-GATE-001_view1_test_physical_setup.d2` | `OBCC-V02-GATE-001_view1_test_physical_setup.png` | v0.2 bus-bring-up UUT, instrumented I2C/UART/SPI/PWM harness, logic analyzer, fault injector, serial log capture, timer/trace collector, ambient thermometer, and safety constraints. |
| PV2 logical interfaces | `OBCC-V02-GATE-001_view2_test_logical_interfaces.d2` | `OBCC-V02-GATE-001_view2_test_logical_interfaces.png` | Component-exchange analysis view for I2C, UART, SPI, PWM, getter, queue, state, mode-gate, bus ownership, and test-equipment logical interfaces. |
| PV3 functional allocation | `OBCC-V02-GATE-001_view3_test_functional_allocation.d2` | `OBCC-V02-GATE-001_view3_test_functional_allocation.png` | Allocation of operator, reviewer, test-equipment, verification-only harness, FreeRTOS, driver/getter, telemetry, radio, and servo functions. |
| Functional chain | `OBCC-V02-GATE-001_view4_bus_getter_timing_gate_chain.d2` | `OBCC-V02-GATE-001_view4_bus_getter_timing_gate_chain.png` | End-to-end analysis + testing sequence for nominal protocol evidence, getter timing, fault injection, scheduler liveness, and evidence closure. |

All four D2 files were rendered successfully with the required `d2 --layout=elk` command and ELK spacing flags.

## Verification coverage table

| Verification activity ID | SSIV / development version | Model element(s) covered | IVV source category | IADT method | Traceability target | Relevant viewpoints: statistical significance and fault hardening | Pass/fail constraint(s) | Diagram/report references | Status |
|---|---|---|---|---|---|---|---|---|---|
| `OBCC-V02-GATE-001-A01` | v0.2 -> v0.3 | I2C, UART, SPI, PWM component exchanges; BME280, IMU, GPS, INA219, RFM95W, servo interfaces; verification harness/test-equipment exchanges | Component exchange | Analysis | Startup/interface readiness; `OBCC-UC-RuntimeFaultHandling`; `OBCC-FE-SchedulerBlocked`; `OBCC-VV-CE-001` | Stat: 100% CE-by-CE review, no sampling claim. Fault hardening: protocol mismatch, wrong voltage/direction/address, unowned shared bus, unobservable fault path. | `PF-001`, `PF-007`, `PF-008` | PV1, PV2; expected report `results/OBCC-V02-GATE-001/component_exchange_analysis.md` | Definition ready; execution pending |
| `OBCC-V02-GATE-001-A02` | v0.2 -> v0.3 | Getter interfaces; FreeRTOS shared-bus protection; queue, state, mode-gate paths; ADS/AMS/ESS/PDM processing ownership | Component exchange; allocation | Analysis | `OBCC-UC-RuntimeFaultHandling`; `OBCC-FE-SchedulerBlocked`; `OBCC-VV-CE-003`; timing/fault subset of `OBCC-VV-CON-004` | Stat: 100% getter/API/allocation review. Fault hardening: hidden cross-task ownership, stale getter values, queue/state/mode-gate misuse, unbounded getter calls. | `PF-002`, `PF-006`, `PF-007`, `PF-008` | PV2, PV3; expected report `results/OBCC-V02-GATE-001/getter_allocation_analysis.md` | Definition ready; execution pending |
| `OBCC-V02-GATE-001-T01` | v0.2 -> v0.3 | Nominal I2C getters for BME280/IMU/INA219, GPS UART getter, RFM95W SPI transaction, servo PWM command in safe fixture | Functional chain/scenario; constraint | Testing | Startup/interface readiness; `OBCC-VV-CE-001`; `OBCC-VV-CE-003` | Stat: advancement screening requires at least one nominal pass per interface class; 59 in-limit representative timing samples per class only if claiming 95/95 timing. Fault hardening: verifies baseline observations before fault injection. | `PF-001`, `PF-002`, `PF-003`, `PF-004`, `PF-007` | PV1, PV3, Functional chain; expected report `results/OBCC-V02-GATE-001/nominal_bus_getter_timing.md` | Definition ready; execution pending |
| `OBCC-V02-GATE-001-T02` | v0.2 -> v0.3 | I2C NACK/stuck bus, GPS UART silence/malformed frames, SPI radio busy/fault, PWM/servo unavailable | Functional chain/scenario; constraint | Testing | `OBCC-UC-RuntimeFaultHandling`; `OBCC-FE-SchedulerBlocked`; timing/fault portions of `OBCC-VV-CON-004` | Stat: one injected case per fault class for v0.2 screening; classify forbidden scheduler-blocking or silent-fault events as failures. Use 59 in-limit samples per class for a 95/95 deadline claim. Fault hardening: bounded and observable error paths. | `PF-003`, `PF-004`, `PF-005`, `PF-006`, `PF-007` | PV1, PV2, PV3, Functional chain; expected report `results/OBCC-V02-GATE-001/fault_injection_timing.md` | Definition ready; execution pending |
| `OBCC-V02-GATE-001-T03` | v0.2 -> v0.3 | Scheduler heartbeat/liveness during getter and interface faults; queue/state/mode-gate data paths under repeated calls | Allocation; functional chain/scenario; constraint | Testing | `OBCC-FE-SchedulerBlocked`; `OBCC-UC-RuntimeFaultHandling`; `OBCC-VV-CE-003`; `OBCC-VV-CON-004` | Stat: advancement screening unless repeated independent timing/liveness samples are collected; report mean/worst gap and any missed heartbeat. Fault hardening: no deadlock, no priority inversion symptom, no queue/state/mode-gate ownership violation. | `PF-002`, `PF-006`, `PF-007` | PV2, PV3, Functional chain; expected report `results/OBCC-V02-GATE-001/scheduler_liveness.md` | Definition ready; execution pending |

## Pass/fail constraints

- **PF-001 — component-exchange implementation:** implemented I2C, UART, SPI, PWM, getter, queue, state, and mode-gate exchanges match model intent for protocol, voltage level, direction, addressing, data ownership, and observable endpoint.
- **PF-002 — getter/API contract:** each getter returns a typed value and explicit success/error status compatible with `Variable_Getter_Template.md`; no getter blocks without a bounded exit and no hidden cross-task bus ownership is required.
- **PF-003 — I2C/UART bounded timing:** modeled I2C and UART read attempts either return valid data or timeout within `<=5 ms`, with timestamp/log evidence.
- **PF-004 — SPI/PWM bounded error paths:** SPI radio busy/fault and PWM/servo-unavailable cases exit through a bounded, observable status/log/health path; no indefinite wait is allowed.
- **PF-005 — required fault matrix:** executed fault set includes I2C NACK or stuck bus, GPS UART silence, GPS malformed frame, SPI radio fault/busy, and PWM/servo unavailable.
- **PF-006 — scheduler and data-path liveness:** scheduler heartbeat/timer activity continues during nominal and fault cases; queue, state, and mode-gate ownership remain as modeled and do not create a hidden bypass.
- **PF-007 — evidence/environment:** raw logic-analyzer decodes, serial logs, trace timing tables, review notes, UUT firmware/configuration ID, test-equipment IDs, and ambient thermometer model/serial/reading are archived under the expected results folder.
- **PF-008 — source-gap declaration:** the report and diagrams state that v0.2 Capella/D2 source views are absent and that v1.0 views are used only as intended-target context.

## Statistics and fault-hardening viewpoints

- This gate is a **v0.2 advancement screening**, not final v1.0 reliability evidence.
- Analysis minimum: 100% disposition of the I2C, UART, SPI, PWM, getter, queue, state, mode-gate, and allocation/ownership items in the v0.2 implementation.
- Testing minimum: at least one nominal run per interface class and at least one injected trial per required fault class before advancement.
- Timing claim policy: use the project IVV timing rule (`n = 59` representative in-limit samples for a 95/95 non-parametric one-sided tolerance claim) if the report claims deadline confidence; otherwise label timing evidence as characterization/advancement screening.
- Fault-hardening focus: I2C NACK/stuck bus, GPS UART silence/malformed frames, SPI radio busy/fault, PWM/servo unavailable, stale/missing getter values, queue/state/mode-gate ownership, and scheduler-blocking failure modes.

## Coverage mapping to existing OBCC v1.0 candidate rows

- **`OBCC-VV-CE-001`:** covered by `A01`, `T01`, and `T02` for sensor/bus CEs (`I2C`, `UART`, `SPI`, `PWM`), including protocol/voltage/direction/addressing review and nominal/fault waveform evidence.
- **`OBCC-VV-CE-003`:** covered by `A02`, `T01`, and `T03` for `Getters`, `Queue`, `State`, `Mode gate`, and relevant IMU/altitude data-path ownership checks.
- **`OBCC-VV-CON-004`:** covered only for the v0.2 timing/fault subset: bounded getter return codes, I2C/UART `<=5 ms`, shared-bus protection, and no scheduler blocking. Startup critical/non-critical policy and later runtime-critical safe/error behavior remain in other gates.

## Assumptions and gaps for feedback / execution planning

- No v0.x Capella/D2 baseline is present; v1.0 source views are context only and shall not be edited.
- Exact v0.2 pin map, I2C addresses, UART baud, SPI mode, chip-select handling, PWM pulse-width policy, and timeout implementation are not controlled in the repository artifacts read here.
- Legacy context includes `BMP280`, `MPU6050`, and serial/AT-command LoRa examples, while the v1.0 target model uses `BME280`, `ICM20948`, and `RFM95W`; execution must record the actual parts fitted.
- `LoRa_Frame.md` lists `RFM96W` while the v1.0 model uses `RFM95W`; execution must identify the actual radio module.
- The getter result-code enum beyond the template's success/overflow/underflow example must be confirmed for communication/runtime failures.
- The timer/trace hook, scheduler heartbeat observable, and FreeRTOS task/queue ownership review artifacts are not specified; execution must attach the code/configuration evidence used.
- Fault injection must use a current-limited, safe bench setup; the servo path is tested with a safe load/disconnect fixture, not a live deployment hazard.
