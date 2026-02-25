# On-board Computer and Communications

This subsystem is the “brain” of the CanSat, coordinating all sensors and actuators to work in sync. Its communication system transmits vital information to the ground station over long distances, ensuring real-time telemetry and status data transmission.

## Requirements

| **Requirement** | **Verification method** |
| --- | --- |
| The On Board Computer & Communication System must manage all sensors and actuators, ensuring proper synchronization of each system. | Integration Test |
| The On Board Computer & Communication System must transmit telemetry data over a minimum radio of 500 m regardless of the topography at intervals of 2 seconds to the DPS. With a transmission success rate of 90%. | Communication Test |
| The On Board Computer & Communication System must verify that all sensor and actuator data is transmitted over a bus due to its ease of use. | PCB inspection |
| The On Board Computer & Communication System shall support the following operational states: “Stand-by” and “On”, when commanded by the *Data Processing System (DPS)* to switch between these operational states. | Operational State Transition Test |

### Success Criteria

The OBCC subsystem has established an architecture that manages sensor and actuator coordination in the Cansat, enables reliable long-range data transmission, and supports multiple operational states commanded by the DPS.