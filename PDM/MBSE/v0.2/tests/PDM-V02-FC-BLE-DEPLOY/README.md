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
- **Constraints:** BLE range/pre-flight connection, airborne command gating, no premature actuation, `PDM-BLK-006` power validity and terminal-speed evidence linkage, statistical viewpoint, and fault-hardening viewpoint are assigned in the definition views.

## Pass/fail rules

Pass only if all applicable constraints below are satisfied or explicitly waived in the report:

1. BLE connection and command/control path are established and verified at `>= 20 m` line-of-sight before airborne/release.
2. No parachute open actuation occurs before the modeled command and airborne condition.
3. During the modeled airborne condition, the human BLE open command results in OBCC PWM open position and the servo/parachute mechanism reaches the open state.
4. Power validity criteria are met:
   - starting source is identified and safe (v0.2 PDS/battery/boost configuration and pre-boost condition).
   - the nominal `5.0 V` servo rail remains within `4.5 V` to `5.5 V` during command and actuation at the servo rail or nearest measurable point.
   - OBCC/XIAO operation shows no reset, brownout marker, boot banner, watchdog reset, telemetry/log discontinuity, or BLE reconnect caused by actuation.
   - current/thermal evidence is captured from pre-command baseline through at least `2 s` after open observation or branch failure, with no current-limit collapse, boost thermal shutdown, connector heating, swelling, smoke, or sustained stall outside the safe envelope.
5. Terminal-speed limiting may be credited by explicit in-run terminal-speed measurement or by linking `PDM-V02-TEST-TERMINAL-SPEED` and/or applicable `PDM-V01-FC-FALL` evidence when as-tested mass/parachute/configuration applicability is justified for the selected `<= 11 m/s` criterion. If neither exists, record a terminal-speed evidence gap/hold.
6. Evidence includes source/model baseline, source and UUT IDs, BLE device/configuration, range/LOS evidence, wind/environment observations, logs/video/PWM/power traces with measurement locations, deviations, and anomalies.

## Quantitative power validity criteria (`PDM-BLK-006`)

These are definition-level execution criteria only; they do not assert that a run has occurred or that any equipment ID/value has been recorded.

- **Starting power condition:** before a credited BLE deployment run, identify the v0.2 PDS/battery/boost configuration and confirm that the battery/pre-boost source is within its declared safe operating range. For a Li-ion cell, record open-circuit voltage and verify it against the approved usable range for the cell/charger policy; if no approved range is available, require a controlled execution input before strict credit.
- **Servo/boost rail:** the servo supply commanded as nominal `5.0 V` shall remain within `5.0 V +/- 10%` (`4.5 V` to `5.5 V`) at the servo or nearest measurable servo rail during command and actuation.
- **Controller brownout:** the OBCC/XIAO logic rail shall remain within the board/regulator valid range and shall show no reset, brownout marker, boot banner, watchdog reset, telemetry/log discontinuity, or BLE reconnect caused by actuation. If the exact board threshold is not controlled, report-time datasheet/configuration evidence is required.
- **Current/thermal:** log battery, boost, and servo current at the logged rail location(s). There shall be no current-limit collapse, boost thermal shutdown, smoke, swelling, connector heating, or sustained stall current beyond the servo/boost safe envelope. Exact current maxima may be execution-configuration inputs, but absence of current/thermal evidence limits credit.
- **Timing/evidence:** capture voltage/current from pre-command baseline through at least `2 s` after the open-state observation or until the branch is declared failed. Correlate the power trace with BLE command timestamp, PWM trace, and video/observer evidence.
- **Pass/fail interpretation:** a deployment that opens only after reset/reconnect, rail collapse, or uncontrolled brownout is not a strict pass even if the parachute eventually opens.

## Terminal-speed evidence linkage

`PDM-V02-FC-BLE-DEPLOY` does not require terminal-speed demonstration inside the BLE/manual deployment run. The run verifies command-to-open, no-premature-open, BLE/range, and power-validity behavior. Terminal-speed limiting may be credited by linked `PDM-V02-TEST-TERMINAL-SPEED` and/or v0.1 `PDM-V01-FC-FALL` evidence if the report justifies applicability of the as-tested mass, parachute, and configuration to v0.2 and uses `<= 11 m/s` as the numeric descent-speed criterion. Without in-run or linked evidence, the report shall state a terminal-speed evidence gap/hold.

## Viewpoints

- **Statistical significance:** three successful repetitions are development screening only. Any reliability/confidence claim must state the needed repetition basis, independence assumptions, and exact confidence method.
- **Fault hardening:** consider BLE loss/out-of-range, late/missed command, low battery/boost sag, servo jam/stall, antenna orientation, wind/gusts, and partial parachute deployment.

## Expected evidence/report locations

- Expected execution report: `PDM/MBSE/v0.2/tests/results/PDM-V02-FC-BLE-DEPLOY/report.md`.
- Expected evidence subfolders may include `ble_logs/`, `pwm_traces/`, `power_traces/`, `video/`, `photos/`, and `environment/` under `PDM/MBSE/v0.2/tests/results/PDM-V02-FC-BLE-DEPLOY/`.

Reports should reference these model views instead of duplicating the full model definition.

## Assumptions and open items

- The issue file disambiguates the development version as PDM v0.2 -> PDM v1.0.
- The selected definition-level power criteria above are the default validity thresholds; execution still records the exact v0.2 PDS / battery / boost configuration, source and UUT IDs, rail measurement location, logger/equipment/calibration IDs, current/thermal envelope, and any controlled execution input that substitutes for unavailable policy limits.
- The safe airborne condition may be represented by a drop/suspension surrogate unless a flight drop is authorized.
- Quantified terminal-speed measurement may be a companion activity; this activity still verifies open-state support and records the `<= 11 m/s` linkage or a hold/gap.
- No execution has been performed by this definition package.
