# OBCC-V01-GATE-001 — v0.1 breadboard startup-health advancement gate

## Scope and selected version

- **Activity ID:** `OBCC-V01-GATE-001`
- **SSIV / version gate:** OBCC `v0.1 -> v0.2`
- **Chosen pending activity for this session:** Issue 001, breadboard hardware and startup-health advancement gate.
- **IADT method(s):** Inspection + Analysis + Demonstration/Testing.
- **IVV source categories:** component/link, component exchange, allocation, functional chain/scenario, constraint.
- **Traceability targets:** `OBCC-UC-StartupHealth`, `OBCC-FE-SilentCriticalFault`, integration/build readiness, startup/fault subset of `OBCC-VV-CON-004`.
- **Expected evidence/report path:** `OBCC/MBSE/tests/results/OBCC-V01-GATE-001/`.
- **Execution status:** modeled definition complete; execution and report evidence pending.

No `v0.1` Capella/D2 source views exist in this repository. This definition uses the `v1.0` OBCC model only as target-architecture context and documents the source-baseline limitation in the diagrams.

## References

- Project IVV: `PM&SE/IVV.md`
- OBCC requirements and derived startup checks: `OBCC/README.md`
- Startup criticality and payload context: `OBCC/LoRa_Frame.md`
- Getter/result-code convention: `OBCC/Variable_Getter_Template.md`
- Test planning inventory: `OBCC/MBSE/tests/README.md`
- Source context copied from: `OBCC/MBSE/v1.0/`

## Baseline/source-view copies

Copied source context is under `source_views/v1.0/` and includes the v1.0 README plus all eight source D2 views and rendered PNGs. There is no `source_views/v0.1/` because no v0.x Capella/D2 baseline is present.

## Verification-specific diagram catalogue

| View | D2 | Rendered PNG | Purpose |
|---|---|---|---|
| PV1 physical setup | `OBCC-V01-GATE-001_view1_test_physical_setup.d2` | `OBCC-V01-GATE-001_view1_test_physical_setup.png` | Breadboard UUT, critical/non-critical peripherals, verification equipment, and physical links/wiring to inspect. |
| PV2 logical interfaces | `OBCC-V01-GATE-001_view2_test_logical_interfaces.d2` | `OBCC-V01-GATE-001_view2_test_logical_interfaces.png` | Test-specific external actors, verification-only diagnostic interfaces, startup-health exchanges, and criticality policy. |
| PV3 functional allocation | `OBCC-V01-GATE-001_view3_test_functional_allocation.d2` | `OBCC-V01-GATE-001_view3_test_functional_allocation.png` | Operator/test-equipment functions and v0.1 verification-only functions allocated to the breadboard architecture. |
| Functional chain | `OBCC-V01-GATE-001_view4_startup_health_gate_chain.d2` | `OBCC-V01-GATE-001_view4_startup_health_gate_chain.png` | Nominal, critical-fault, and non-critical-fault startup test sequences with pass/fail constraints. |

All four D2 files were rendered with the required `d2 --layout=elk` command and ELK spacing flags.

## Verification coverage table

| Verification activity ID | SSIV / development version | Model element(s) covered | IVV source category | IADT method | Traceability target | Relevant viewpoints: statistical significance and fault hardening | Pass/fail constraint(s) | Diagram/report references | Status |
|---|---|---|---|---|---|---|---|---|---|
| `OBCC-V01-GATE-001-I01` | v0.1 -> v0.2 | Breadboard XIAO ESP32-S3, RFM96W, BME280, servo/deployment actuator context, UBX-G7020 GPS, ICM20948 IMU, INA219, USB/status indication, jumper harnesses and links | Component/link | Inspection | Integration/build readiness; `OBCC-UC-StartupHealth` | Stat: 100% inspection of the integrated article. Fault hardening: part identity, critical wiring, antenna/servo presence, no undispositioned substitutions. | `PF-001` | PV1; expected report `results/OBCC-V01-GATE-001/inspection.md` | Definition ready; execution pending |
| `OBCC-V01-GATE-001-A01` | v0.1 -> v0.2 | SPI/I2C/UART/PWM/USB/LoRa startup exchanges; Health Monitor, Supervisor, telemetry/status, verification-only test harness and serial diagnostic interface | Component exchange; allocation | Analysis | `OBCC-UC-StartupHealth`; `OBCC-FE-SilentCriticalFault` | Stat: 100% interface/allocation review for the v0.1 breadboard configuration. Fault hardening: critical-vs-non-critical classification is observable through status/logs. | `PF-002` through `PF-005` are trace targets; analysis passes if exchanges and allocations support those observations without hidden required operator paths. | PV2, PV3; expected report `results/OBCC-V01-GATE-001/interface_allocation_analysis.md` | Definition ready; execution pending |
| `OBCC-V01-GATE-001-T01` | v0.1 -> v0.2 | Nominal startup health chain with all peripherals connected | Functional chain/scenario; constraint | Demonstration/Testing | `OBCC-UC-StartupHealth` | Stat: at least one advancement-screening nominal boot; use 29/29 nominal boots only if claiming R90/C95. Fault hardening: no false missing-peripheral status. | `PF-002`, `PF-006` | PV3, Functional chain; expected report `results/OBCC-V01-GATE-001/nominal_startup.md` | Definition ready; execution pending |
| `OBCC-V01-GATE-001-T02` | v0.1 -> v0.2 | Missing startup-critical RFM96W, BME280, Servo cases | Functional chain/scenario; constraint | Demonstration/Testing | `OBCC-FE-SilentCriticalFault`; startup/fault subset of `OBCC-VV-CON-004` | Stat: one injected case per critical peripheral for v0.1 screening; more trials must classify forbidden operational-readiness events as failures. Fault hardening: missing criticals must not permit operational mode. | `PF-003`, `PF-006` | PV1, PV2, PV3, Functional chain; expected report `results/OBCC-V01-GATE-001/critical_faults.md` | Definition ready; execution pending |
| `OBCC-V01-GATE-001-T03` | v0.1 -> v0.2 | Missing non-critical UBX-G7020 GPS, ICM20948 IMU, INA219 cases | Functional chain/scenario; constraint | Demonstration/Testing | `OBCC-UC-StartupHealth`; startup/fault subset of `OBCC-VV-CON-004` | Stat: one injected case per non-critical peripheral for v0.1 screening. Fault hardening: degraded operation must remain telemetry/status-visible and non-critical faults must not brick startup. | `PF-004`, `PF-006` | PV1, PV2, PV3, Functional chain; expected report `results/OBCC-V01-GATE-001/noncritical_faults.md` | Definition ready; execution pending |

## Pass/fail constraints

- **PF-001 — component/link inspection:** all required v0.1 breadboard components, jumper harnesses, power/status links, and critical links are present, identified, and dispositioned. Any substitution or absent element is recorded before the gate can pass.
- **PF-002 — nominal startup:** with all peripherals connected, startup checks complete, no startup-critical or non-critical missing-peripheral fault is reported, operational readiness is allowed, and status is visible through serial diagnostics or LoRa health/status telemetry.
- **PF-003 — critical startup fault:** when exactly one of RFM96W, BME280, or Servo is missing at startup, the status/log identifies the named peripheral as startup-critical and OBCC does not enter operational mode.
- **PF-004 — non-critical startup fault:** when exactly one of UBX-G7020 GPS, ICM20948 IMU, or INA219 is missing at startup, OBCC enters degraded operation and reports error-coded, zero, null, or stale-marked values/status for the affected capability.
- **PF-005 — interface/allocation consistency:** the v0.1 implementation provides the modeled startup observations through the diagnostic/status interfaces without requiring a hidden unmodeled operator path.
- **PF-006 — environmental/evidence condition:** before repeated boots, record ambient thermometer model/serial and reading; if conditions are outside a bench range compatible with the modeled BME280 telemetry range (`10..40 °C`) or the thermometer identity is not recorded, the report must log a deviation/evidence gap.

## Statistics and fault-hardening viewpoints

- This gate is an **advancement screening** for `v0.1 -> v0.2`, not a final reliability demonstration.
- Minimum statistical basis: 100% inspection of the integrated breadboard plus at least one nominal boot, one missing case for each critical peripheral, and one missing case for each non-critical peripheral.
- If the team wants a binary reliability claim for nominal startup, use the project IVV binomial policy; `29/29` successful nominal boots supports an R90/C95 screening claim.
- Fault-hardening emphasis: no silent critical fault, no false operational readiness, degraded non-critical startup remains observable, and v0.1 USB/serial diagnostics remain a bench-only aid rather than a v1.0 flight operator path.

## Assumptions and gaps for feedback

- No v0.x Capella/D2 baseline is present; the copied v1.0 model is context only.
- `LoRa_Frame.md`, the v1.0 model, and the current plan use the selected `RFM96W` radio name; execution should record the actual radio module fitted.
- The IMU may be the selected `ICM20948`; execution should record the actual part and apply the corresponding non-critical trial.
- Exact health/status encoding and serial/telemetry log schema are not specified in the repository; the report must attach raw logs and state how pass/fail was decoded.
- The ambient thermometer model is not specified; the diagram marks it as calibrated/model TBD and `PF-006` requires the exact model/serial in evidence.
- Servo/deployment actuator testing must be performed in a safe bench configuration; this gate checks startup presence/criticality, not deployment timing.
