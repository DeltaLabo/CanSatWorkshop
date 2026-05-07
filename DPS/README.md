# Data Processing System

Owners: @anthonyarguedas, @abimonge, @ItsMaxXs, @JLPL1503

The data processing system manages the reception, storage, and analysis of data collected by the CanSat’s sensors. It organizes and prioritizes information for transmission, enabling real-time reporting and providing positional and orientation data for mission analysis.

See [Understanding Capella Physical Diagrams](./../PM&SE//Understanding%20Capella%20Physical%20Diagrams/Understanding%20Capella%20Physical%20Diagrams.md) if needed.

See [Variable Getter Template](./../OBCC/Variable%20Getter%20Template.md) if needed.

## Integration, Verification, and Validation (IVV) Plan

The DPS v1.0 MBSE views translated from Capella XML to D2 are available in [`./MBSE/v1.0/`](./MBSE/v1.0/):

### Architecture views
- [View 1 — Physical view (PNG)](./MBSE/v1.0/DPS_v1.0_view1_physical.png) · [D2 source](./MBSE/v1.0/DPS_v1.0_view1_physical.d2)
- [View 2 — Logical view (PNG)](./MBSE/v1.0/DPS_v1.0_view2_logical.png) · [D2 source](./MBSE/v1.0/DPS_v1.0_view2_logical.d2)
- [View 3 — Functional allocation view (PNG)](./MBSE/v1.0/DPS_v1.0_view3_functional_allocation.png) · [D2 source](./MBSE/v1.0/DPS_v1.0_view3_functional_allocation.d2)

### Functional chain views
- [View 4 — Downlink decode and storage chain (PNG)](./MBSE/v1.0/DPS_v1.0_view4_downlink_processing_chain.png) · [D2 source](./MBSE/v1.0/DPS_v1.0_view4_downlink_processing_chain.d2)
- [View 5 — Dashboard command and uplink chain (PNG)](./MBSE/v1.0/DPS_v1.0_view5_command_uplink_chain.png) · [D2 source](./MBSE/v1.0/DPS_v1.0_view5_command_uplink_chain.d2)
- [View 6 — CanSat receive path (PNG)](./MBSE/v1.0/DPS_v1.0_view6_cansat_receive_chain.png) · [D2 source](./MBSE/v1.0/DPS_v1.0_view6_cansat_receive_chain.d2)
- [View 7 — CanSat transmit path (PNG)](./MBSE/v1.0/DPS_v1.0_view7_cansat_transmit_chain.png) · [D2 source](./MBSE/v1.0/DPS_v1.0_view7_cansat_transmit_chain.d2)
- [View 8 — Dashboard visualisation chain (PNG)](./MBSE/v1.0/DPS_v1.0_view8_dashboard_visualisation_chain.png) · [D2 source](./MBSE/v1.0/DPS_v1.0_view8_dashboard_visualisation_chain.d2)
- [View 9 — Forwarder initialisation chain (PNG)](./MBSE/v1.0/DPS_v1.0_view9_forwarder_initialisation_chain.png) · [D2 source](./MBSE/v1.0/DPS_v1.0_view9_forwarder_initialisation_chain.d2)

Recommended reading order: View 1 → View 2 → View 3 → View 4 → View 8 → View 5 → View 6 → View 7 → View 9.

This order goes from structure to allocation, then follows the main DPS operational flows: downlink decoding and storage, dashboard visualisation, command uplink, CanSat-side receive/transmit behavior, and finally forwarder initialisation.

## Requirements

| **Requirement** | **Verification method** |
| --- | --- |
| The data processing system must be capable of receiving, storing, and processing real-time data from the OBCC processing rate of at least 5 Hz. | Communication Test |
| The data processing system must allow access to processed data through a user-friendly interface. | Interface inspection |
| The interface of the system must show  a real-time report of all the atmospheric measurements in the CanSat. | Interface inspection |
| The interface of the system must generate a real-time report with a 3D model that displays the CanSat's altitude. | Interface inspection |
| The Data Processing System must store all information send by OBCC, locally. | File inspection |

### Success Criteria

The DPS demonstrates the capability to acquire, process, store, and display real-time data received from the OBCC, with a functional user interface and complete traceability of the processed information.
