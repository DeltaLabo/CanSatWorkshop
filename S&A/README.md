# Structures and Assembly

This subsystem provides a lightweight and modular physical structure for the CanSat, designed to protect internal components and ensure impact resistance during landing. It maintains standard dimensions, facilitates easy module replacement, and allows for straightforward handling and maintenance, contributing to the overall reliability and efficiency of the CanSat.

See [Understanding Capella Physical Diagrams](./../PM&SE/Understanding%20Capella%20Physical%20Diagrams/Understanding%20Capella%20Physical%20Diagrams.md) if needed.

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