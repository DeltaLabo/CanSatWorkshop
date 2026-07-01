# PDM-V02-FC-BLE-DEPLOY — BLE/manual parachute deployment verification definition

- **Version gate:** PDM v0.2 -> PDM v1.0.
- **IADT method:** Testing / Demonstration with supporting Inspection and Analysis.
- **Primary IVV source category:** functional chain/scenario, with linked component exchange, physical link, allocation, and constraint coverage.
- **Status:** modeled definition created and rendered; execution evidence is not present.

## Source views copied into this package

Copied under `source_views/v0.2/`:

- `PDM_v0.2_view1_physical.d2/png`
- `PDM_v0.2_view2_logical.d2/png`
- `PDM_v0.2_view3_functional_allocation.d2/png`
- `PDM_v0.2_view4_parachute_deployment_chain.d2/png`

The copied baseline is PDM v0.2 manual BLE deployment only. No IMU/altitude fallback is part of this version.

## New definition views

All new D2 views are under `definition_views/` and were rendered to PNG with the required ELK command.

| View | Purpose | Render status |
| --- | --- | --- |
| `view1_source_inventory_coverage.d2/png` | Binds copied source views to IVV coverage categories and traceability targets. | Rendered OK |
| `view2_physical_ble_deployment_test_setup.d2/png` | Physical UUT/test setup with BLE controller, range marker, power/PWM instrumentation, video, ambient thermometer, and safe airborne surrogate. | Rendered OK |
| `view3_verification_functional_allocation.d2/png` | Allocates human, equipment, UUT, and verification-only functions/components. | Rendered OK |
| `view4_ble_deployment_sequence_fault_chain.d2/png` | Main testing/demonstration sequence with pass/fail, statistical, and fault-hardening constraints. | Rendered OK |
| `view5_evidence_traceability_report_interface.d2/png` | Evidence/report interface and traceability handling for the activity. | Rendered OK |

## Verification definition

The verification activity demonstrates that, in the PDM v0.2 manual BLE baseline, a human BLE open command sent during the modeled airborne condition causes the OBCC to set the PWM open position and the servo/parachute mechanism to reach the open state, while the BLE, power, and evidence constraints are satisfied.

### Test item

- `[PC] CanSat`, including `[PC] OBCC Module`, `[PC] XIAO ESP32-C3`, `[PC] 2.4 GHz Antenna`, `[PC] Parachute Module`, `[PC] Servo`, `[PC] Parachute`, `[PC] Power Module`, `[PC] Battery`, and `[PC] Boost Converter`.

### Verification means

- Human BLE test operator.
- BLE controller / phone.
- 20 m line-of-sight range marker.
- Safe drop/suspension fixture or authorized airborne surrogate.
- PWM logic analyzer and verification-only PWM probe terminal.
- Battery/boost power logger and verification-only power probe terminal.
- Video camera.
- Ambient thermometer.
- Evidence repository/report record.

## Coverage

- **Physical components/links:** covered by the setup view and supporting inspection requirement in `../README.md`.
- **Component exchanges:** BLE command/control and PWM are analyzed/observed through the modeled sequence and instrumentation.
- **Logical allocation:** OBCC, Parachute trigger, Descent speed control, Power storage, and Voltage regulation functions are shown in `view3`.
- **Functional chain/scenario:** main sequence is modeled in `view4`.
- **Constraints:** BLE range/pre-flight connection, airborne command gating, no premature actuation, PDS v0.1 power, terminal-speed evidence linkage, statistical viewpoint, and fault-hardening viewpoint are assigned in the definition views.

## Pass/fail rules

Pass only if all applicable constraints below are satisfied or explicitly waived in the report:

1. BLE connection and command/control path are established and verified at `>= 20 m` line-of-sight before airborne/release.
2. No parachute open actuation occurs before the modeled command and airborne condition.
3. During the modeled airborne condition, the human BLE open command results in OBCC PWM open position and the servo/parachute mechanism reaches open state.
4. PDS v0.1 / battery / boost converter power remains within the needed range during command and servo actuation, using logged evidence.
5. The deployment mechanism reaches the open state and supports terminal-speed limiting. If terminal-speed measurement is not part of the same execution, the report must cite linked companion evidence or record the gap.
6. Evidence includes source model version, UUT configuration, BLE device/configuration, range/LOS conditions, logs/video/PWM/power traces, environmental conditions, deviations, and anomalies.

## Viewpoints

- **Statistical significance:** three successful repetitions are development screening only. Any reliability/confidence claim must state the needed repetition basis, independence assumptions, and exact confidence method.
- **Fault hardening:** consider BLE loss/out-of-range, late/missed command, low battery/boost sag, servo jam/stall, antenna orientation, wind/gusts, and partial parachute deployment.

## Expected evidence/report locations

- Expected execution report: `PDM/MBSE/v0.2/tests/results/PDM-V02-FC-BLE-DEPLOY/report.md`.
- Expected evidence subfolders may include `ble_logs/`, `pwm_traces/`, `power_traces/`, `video/`, `photos/`, and `environment/` under `PDM/MBSE/v0.2/tests/results/PDM-V02-FC-BLE-DEPLOY/`.

Reports should reference these model views instead of duplicating the full model definition.

## Assumptions and open items

- The issue file disambiguates the development version as PDM v0.2 -> PDM v1.0.
- The power pass/fail threshold must be derived from the as-tested PDS v0.1 / battery / boost converter / servo configuration before execution.
- The safe airborne condition may be represented by a drop/suspension surrogate unless a flight drop is authorized.
- Quantified terminal-speed measurement may be a companion activity; this activity still verifies open-state support and records the linkage.
- No execution has been performed by this definition package.
