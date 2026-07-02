# DPS v0.2 MBSE Views

DPS v0.2 extends the v0.1 circuitboard-based hardware with IMU-only data downlink to the ground station. This version number replaces the former PCB-only v0.2 scope, which was retired because v1.0 reuses the OBCC PCB for the ground station.

Key scope decisions:

- No GPS is included in this version.
- No PCBs are represented; all deployment hardware is on circuitboards.
- The datalogger-side XIAO has exactly two logical components:
  - `[LC] Dummy Datalogger`
  - `[LC] AMS Processing IMU Only`
- IMU-only processing is based on the IMU flows from `ADS/MBSE/v0.2/`.
- `[F] Update CanSat orientation 3D model` has the constraint `[C] No perceptible orientation jitter`.

## Views

### Architecture views
- [View 1 — Physical view (PNG)](./DPS_v0.2_view1_physical.png) · [D2 source](./DPS_v0.2_view1_physical.d2)
- [View 2 — Logical view (PNG)](./DPS_v0.2_view2_logical.png) · [D2 source](./DPS_v0.2_view2_logical.d2)
- [View 3 — Functional allocation view (PNG)](./DPS_v0.2_view3_functional_allocation.png) · [D2 source](./DPS_v0.2_view3_functional_allocation.d2)

### Functional chain views
- [View 4 — IMU downlink decode and storage chain (PNG)](./DPS_v0.2_view4_imu_downlink_processing_chain.png) · [D2 source](./DPS_v0.2_view4_imu_downlink_processing_chain.d2)
- [View 5 — Dashboard command and uplink chain (PNG)](./DPS_v0.2_view5_command_uplink_chain.png) · [D2 source](./DPS_v0.2_view5_command_uplink_chain.d2)
- [View 6 — Datalogger receive path (PNG)](./DPS_v0.2_view6_datalogger_receive_chain.png) · [D2 source](./DPS_v0.2_view6_datalogger_receive_chain.d2)
- [View 7 — Datalogger transmit path (PNG)](./DPS_v0.2_view7_datalogger_transmit_chain.png) · [D2 source](./DPS_v0.2_view7_datalogger_transmit_chain.d2)
- [View 8 — Dashboard visualisation chain (PNG)](./DPS_v0.2_view8_dashboard_visualisation_chain.png) · [D2 source](./DPS_v0.2_view8_dashboard_visualisation_chain.d2)
- [View 9 — Forwarder initialisation chain (PNG)](./DPS_v0.2_view9_forwarder_initialisation_chain.png) · [D2 source](./DPS_v0.2_view9_forwarder_initialisation_chain.d2)
- [View 10 — IMU-only processing chain (PNG)](./DPS_v0.2_view10_imu_processing_chain.png) · [D2 source](./DPS_v0.2_view10_imu_processing_chain.d2)

Recommended reading order: View 1 → View 2 → View 3 → View 10 → View 4 → View 8 → View 5 → View 6 → View 7 → View 9.
