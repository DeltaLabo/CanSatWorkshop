# Structures and Assembly

Owners: @prigo11, @secoher26, @MariaAC1501

This subsystem provides a lightweight and modular physical structure for the CanSat, designed to protect internal components and ensure impact resistance during landing. It maintains standard dimensions, facilitates easy module replacement, and allows for straightforward handling and maintenance, contributing to the overall reliability and efficiency of the CanSat.

See [Understanding Capella Physical Diagrams](./../PM&SE/Understanding%20Capella%20Physical%20Diagrams/Understanding%20Capella%20Physical%20Diagrams.md) if needed.

## Diagram Sources

- [`MBSE/v0.1/`](./MBSE/v0.1/) — reusable structural module models with S&A constraints.
- [`MBSE/v1.0/`](./MBSE/v1.0/) — same module structure with PCBs and integration hardware mounted.

## Integration, Verification, and Validation (IVV) Plan

- **v0.1** — [physical PNG](./MBSE/v0.1/SAA_v0.1_view1_physical.png) · [D2 source](./MBSE/v0.1/SAA_v0.1_view1_physical.d2)
- **v1.0** — [physical PNG](./MBSE/v1.0/SAA_v1.0_view1_physical.png) · [D2 source](./MBSE/v1.0/SAA_v1.0_view1_physical.d2)

![S&A v0.1 physical view](./MBSE/v0.1/SAA_v0.1_view1_physical.png)
View 1 — v0.1 physical structure model and constraints.

![S&A v1.0 physical view](./MBSE/v1.0/SAA_v1.0_view1_physical.png)
View 1 — v1.0 integrated physical assembly with PCBs mounted.

## Requirements

| Requirement | Verification method |
| --- | --- |
| The CanSat structure must be modular, with a maximum of two types of modules. | 3D model inspection |
| The CanSat dimensions must be the same of a 355ml aluminum can, with a diameter of 6.6cm and height of 12.2cm | Dimensions inspection |
| The total mass of the CanSat must be less than 350±0.1 grams | Weight inspection |
| The CanSat structure must withstand the impact of landing | Drop test |
| The CanSat modules must accommodate a 44mm x 44mm PCB | 3D model inspection |
| The CanSat modules must allow for the allocation of a perpendicular backplane PCB | 3D model inspection |
| The CanSat modules must be assembled using a maximum of two types of self-tapping screws | 3D model inspection |
| The CanSat structure must be printed with a precision of 0.2 mm. | Printer software configuration inspection |
| The CanSat structure must be printed with a fill of 15%. | Printer software configuration inspection |

### Success Criteria

The S&A subsystem has defined a modular structure that meets the dimensional constraints of the CanSat format, enables proper integration of all functional modules, and ensures a robust assembly capable of parachute deployment.

## Backplane

# Backplane

The port that i being used in the whole CanSat is [TMM-106-01-L-D-RA SAMTEC](https://www.tme.com/cl/es/details/tmm-106-01-l-d-ra/conectores-placa-placa/samtec/).

![Pin Assignment](Pin Interface_page-0001.jpg)
This is the pin assignment we will use for the CanSat. If any changes are needed, you can find the [Excel](https://estudianteccr-my.sharepoint.com/:x:/g/personal/kalebgranac13_estudiantec_cr/ETmAzbKWU1ZBgWh_Ee5cvZABLW6a4r9ywtOAFayDHpDFFA?e=c6SHXV) file here.

This is not a standalone subsystem, but the BackPlane helps reduce the rigidity of traditional wiring while providing greater stability for the power and data connections of the entire CanSat.

See [Understanding Capella Physical Diagrams](./../PM&SE/Understanding%20Capella%20Physical%20Diagrams/Understanding%20Capella%20Physical%20Diagrams.md) if needed.

## Requirements

| **Requirement** | **Verification method** |
| --- | --- |
| The Backplane must follow the defined pin interface.  | Visual inspection |
| The backplane shall supply 5.0±0.1V to each subsystem that requieres it, with the least amount of voltage lost across the distribution path. | Power Test |
| The backplane shall supply 3.3±0.1V to each subsystem that requieres it, with the least amount of voltage lost across the distribution path.. | Power Test |
| The backplane should have testpoints in the PCB for critical signal and voltage measurement. | Signal testing |
| The backplane should keep extra low capacitance on the fast communication lines (SPI, I2C & UART). | Signal testing |
| The backplane must follow the Electronic Rules Check (ERC). | Design review by Fusion 360 |
| The backplane must follow the Design Rule Check (DRC). | Design review by Fusion 360 |
| The backplane must use 2 mm 2x6 pin headers for connections to the CanSat subsystems. | Visual Inspection |
| The backplane must have physical dimensions of 100 mm × 28 mm. | Dimensions inspection |
| The backplane shall be composed of a two-layer PCB stackup. | Desing review in Fusion 360 |