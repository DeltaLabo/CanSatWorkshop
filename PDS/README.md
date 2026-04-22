# Power Distribution System

Owners: @GaboArayaIA, @JLPL1503, @juanjorojash

The power distribution system is responsible for regulating and supplying the necessary energy to all CanSat components. It maintains a stable and safe power flow, with protections to prevent overcurrent failures and ensure the continuous functionality of the systems in operational conditions.

[Power Budget](https://estudianteccr-my.sharepoint.com/:x:/g/personal/joseluispiedra_estudiantec_cr/EUAGHGN1rZlJvwReav6_xnwB106XWC1TTyXf4Vv0bnZCjA?e=fXEnSf)

See [Understanding Capella Physical Diagrams](./../PM&SE/Understanding%20Capella%20Physical%20Diagrams/Understanding%20Capella%20Physical%20Diagrams.md) if needed.

See [Variable Getter Template](./../OBCC/Variable%20Getter%20Template.md) and [LoRa Frame](./../OBCC/LoRa%Frame.md) if needed.

## Diagram Sources

- [`MBSE/v0.1/`](./MBSE/v0.1/)
- [`MBSE/v0.2/`](./MBSE/v0.2/)
- [`MBSE/v0.3/`](./MBSE/v0.3/)
- [`MBSE/v1.0/`](./MBSE/v1.0/)

## Integration, Verification, and Validation (IVV) Plan

### Diagram sets by version

- **v0.1** — [physical PNG](./MBSE/v0.1/PDS_v0.1_view1_physical.d2.png) · [functional allocation PNG](./MBSE/v0.1/PDS_v0.1_view2_functional_allocation.d2.png) · [power chain PNG](./MBSE/v0.1/PDS_v0.1_view3_power_chain.d2.png)
- **v0.2** — [physical PNG](./MBSE/v0.2/PDS_v0.2_view1_physical.d2.png) · [functional allocation PNG](./MBSE/v0.2/PDS_v0.2_view2_functional_allocation.d2.png) · [power chain PNG](./MBSE/v0.2/PDS_v0.2_view3_power_chain.d2.png) · [measurement chain PNG](./MBSE/v0.2/PDS_v0.2_view4_measurement_chain.d2.png)
- **v0.3** — [physical PNG](./MBSE/v0.3/PDS_v0.3_view1_physical.d2.png) · [functional allocation PNG](./MBSE/v0.3/PDS_v0.3_view2_functional_allocation.d2.png) · [power and protection chain PNG](./MBSE/v0.3/PDS_v0.3_view3_power_and_protection_chain.d2.png) · [battery supervision chain PNG](./MBSE/v0.3/PDS_v0.3_view4_battery_supervision_chain.d2.png)
- **v1.0** — [physical PNG](./MBSE/v1.0/PDS_v1.0_view1_physical.d2.png) · [logical PNG](./MBSE/v1.0/PDS_v1.0_view2_logical.d2.png) · [functional allocation PNG](./MBSE/v1.0/PDS_v1.0_view3_functional_allocation.d2.png) · [power and protection chain PNG](./MBSE/v1.0/PDS_v1.0_view4_power_and_protection_chain.d2.png) · [battery supervision chain PNG](./MBSE/v1.0/PDS_v1.0_view5_battery_supervision_chain.d2.png)

### Latest split views

Latest available split views are grouped under [`./MBSE/v1.0/`](./MBSE/v1.0/).

![view 1 physical](./MBSE/v1.0/PDS_v1.0_view1_physical.d2.png)
View 1 — physical architecture and physical links ([D2 source](./MBSE/v1.0/PDS_v1.0_view1_physical.d2))

![view 2 logical](./MBSE/v1.0/PDS_v1.0_view2_logical.d2.png)
View 2 — logical components and software exchanges ([D2 source](./MBSE/v1.0/PDS_v1.0_view2_logical.d2))

![view 3 functional allocation](./MBSE/v1.0/PDS_v1.0_view3_functional_allocation.d2.png)
View 3 — functional allocation across physical and logical components ([D2 source](./MBSE/v1.0/PDS_v1.0_view3_functional_allocation.d2))

![view 4 power and protection](./MBSE/v1.0/PDS_v1.0_view4_power_and_protection_chain.d2.png)
View 4 — power delivery and protection functional chain ([D2 source](./MBSE/v1.0/PDS_v1.0_view4_power_and_protection_chain.d2))

![view 5 battery supervision](./MBSE/v1.0/PDS_v1.0_view5_battery_supervision_chain.d2.png)
View 5 — battery supervision and software chain ([D2 source](./MBSE/v1.0/PDS_v1.0_view5_battery_supervision_chain.d2))

## Requirements

| **Requirement** | **Verification method** |
| --- | --- |
| The power distribution system must continuously supply 3.3±0.1 V and 1 A, with an efficiency of 95%. | Power Test |
| The power distribution system must con tinuously supply 5±0.1 V and 1 A, with an efficiency of 95%. | Power Test |
| The system must be capable of recover automatically after a fault. | Automatic Recovery Test |

### Success Criteria

The PDS presents a design that ensures stable and efficient power delivery at required voltage and current levels, including automatic recovery capabilities in the event of a fault.