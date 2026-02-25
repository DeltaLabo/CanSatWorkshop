# Power Distribution System

Owners: @GaboArayaIA, @JLPL1503, @juanjorojash

The power distribution system is responsible for regulating and supplying the necessary energy to all CanSat components. It maintains a stable and safe power flow, with protections to prevent overcurrent failures and ensure the continuous functionality of the systems in operational conditions.

[Power Budget](https://estudianteccr-my.sharepoint.com/:x:/g/personal/joseluispiedra_estudiantec_cr/EUAGHGN1rZlJvwReav6_xnwB106XWC1TTyXf4Vv0bnZCjA?e=fXEnSf)

See [Understanding Capella Physical Diagrams](./../PM&SE/Understanding%20Capella%20Physical%20Diagrams/Understanding%20Capella%20Physical%20Diagrams.md) if needed.

## Integration, Verification, and Validation (IVV) Plan

![v0.1](PDS_v0.1.jpg)
v0.1

![v0.2](PDS_v0.2.jpg)
v0.2

![v0.3](PDS_v0.3.jpg)
v0.3

![v1.0](PDS_v1.0.jpg)
v1.0

## Requirements

| **Requirement** | **Verification method** |
| --- | --- |
| The power distribution system must continuously supply 3.3±0.1 V and 1 A, with an efficiency of 95%. | Power Test |
| The power distribution system must con tinuously supply 5±0.1 V and 1 A, with an efficiency of 95%. | Power Test |
| The system must be capable of recover automatically after a fault. | Automatic Recovery Test |

### Success Criteria

The PDS presents a design that ensures stable and efficient power delivery at required voltage and current levels, including automatic recovery capabilities in the event of a fault.