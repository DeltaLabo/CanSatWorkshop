# Data Processing System

Owners: @anthonyarguedas, @ItsMaxXs, @JLPL1503

The data processing system manages the reception, storage, and analysis of data collected by the CanSat’s sensors. It organizes and prioritizes information for transmission, enabling real-time reporting and providing positional and orientation data for mission analysis.

See [Understanding Capella Physical Diagrams](./../PM&SE//Understanding%20Capella%20Physical%20Diagrams/Understanding%20Capella%20Physical%20Diagrams.md) if needed.

See [Variable Getter Template](./../OBCC/Variable%20Getter%20Template.md) if needed.

## Requirements

| **Requirement** | **Verification method** |
| --- | --- |
| The data processing system must be capable of receiving, storing, and processing OBCC LoRa telemetry at the v1.0 flight cadence of one frame every 2 seconds; optional lab stress tests may exercise higher rates such as 5 Hz. | Communication Test |
| The data processing system must allow access to processed data through a user-friendly interface. | Interface inspection |
| The interface of the system must show  a real-time report of all the atmospheric measurements in the CanSat. | Interface inspection |
| The interface of the system must generate a real-time report with a 3D model that displays the CanSat's orientation (pitch, roll and yaw attitude). | Interface inspection |
| The Data Processing System must store all information send by OBCC, locally. | File inspection |

### Success Criteria

The DPS demonstrates the capability to acquire, process, store, and display real-time data received from the OBCC, with a functional user interface and complete traceability of the processed information.
