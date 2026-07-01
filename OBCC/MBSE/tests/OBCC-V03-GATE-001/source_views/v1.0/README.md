# OBCC v1.0 MBSE D2 views

Capella-style Physical Architecture views for the On-board Computer and Communications subsystem.

Key v1.0 modeling decisions:

- Uses the existing project style: `[System] Physical System` includes the integrated CanSat, ground-station electronics, and PC context; external subsystem modules shown on OBCC views are integration context, not OBCC ownership.
- OBCC runs on the XIAO ESP32-S3 with multiple FreeRTOS tasks, queues, timers, ISRs, and shared-bus protection.
- Correct hardware names are `RFM95W LoRa` and `ICM20948 IMU`.
- `Stand-by` still sends heartbeat/status telemetry and measurement telemetry at the modeled 2 s downlink cadence; it only inhibits parachute deployment.
- Relative humidity is excluded from OBCC v1.0 telemetry.
- v1.0 is flight-ready and wireless; no serial-console test operator is modeled.
- Startup critical-component failures prevent operational mode so flight readiness is not falsely declared.
- Runtime sensor/getter faults are bounded, disclosed as error/result codes in telemetry, and do not block the scheduler; when descent-state observability is lost in On mode, the deployment gate can receive an emergency-deploy request.

| View | Source | Rendered PNG |
| --- | --- | --- |
| PV1 Physical | [D2](OBCC_v1.0_view1_physical.d2) | [PNG](OBCC_v1.0_view1_physical.png) |
| PV2 Logical | [D2](OBCC_v1.0_view2_logical.d2) | [PNG](OBCC_v1.0_view2_logical.png) |
| PV3 Functional allocation | [D2](OBCC_v1.0_view3_functional_allocation.d2) | [PNG](OBCC_v1.0_view3_functional_allocation.png) |
| Startup health chain | [D2](OBCC_v1.0_view4_startup_health_chain.d2) | [PNG](OBCC_v1.0_view4_startup_health_chain.png) |
| Telemetry downlink chain | [D2](OBCC_v1.0_view5_telemetry_downlink_chain.d2) | [PNG](OBCC_v1.0_view5_telemetry_downlink_chain.png) |
| Command and state chain | [D2](OBCC_v1.0_view6_command_state_chain.d2) | [PNG](OBCC_v1.0_view6_command_state_chain.png) |
| Deployment gating chain | [D2](OBCC_v1.0_view7_deployment_gating_chain.d2) | [PNG](OBCC_v1.0_view7_deployment_gating_chain.png) |
| Runtime fault-handling chain | [D2](OBCC_v1.0_view8_runtime_fault_handling_chain.d2) | [PNG](OBCC_v1.0_view8_runtime_fault_handling_chain.png) |

Render with:

```sh
d2 --layout=elk \
  --elk-padding="[top=20,left=20,bottom=20,right=20]" \
  --elk-nodeNodeBetweenLayers=30 \
  --elk-edgeNodeBetweenLayers=20 \
  input.d2 output.png
```
