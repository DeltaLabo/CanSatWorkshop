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

## Derived Requirements

| Requirement | Verification method |
| --- | --- |
| The subsystem must perform startup checks for all peripherals | Test setup: Manually disconnect each peripheral and run startup.

Pass/Fail criteria: PASS if there is any terminal output acknowledging the missing peripheral, FAIL otherwise. |
| The subsystem must enter an error state if any critical peripheral is faulty at startup | Test setup: Manually disconnect each critical peripheral and run startup.

Pass/Fail criteria: PASS if all the following hold:

- There is terminal output acknowledging the missing peripheral, which explicitly mentions that it’s critical and that the OBCC can’t start without it
- The OBCC does not enter the program loop

FAIL otherwise. |
| The subsystem must disable the functionalities that depend on any non-critical components that are faulty at startup | Test setup: Manually disconnect all non-critical peripheral and run startup.

Pass/Fail criteria: PASS if all the following hold:
- There is terminal output acknowledging the all missing peripherals, which explicitly mentions that none of them are critical and that the OBCC will start without them
- The OBCC enters the program loop
- Comms work normally with zero or null values for the variables related to the missing peripherals

FAIl otherwise. |
| The subsystem must indicate when no startup checks failed | Test setup: Run startup with all peripherals connected and operational

Pass/Fail criteria: PASS if there is terminal output indicating that all startup checks have been completed successfully, FAIL otherwise. |
| The subsystem must execute a single-threaded program loop at a set time interval, as soon as startup is done | Communication Test, Operational State Transition Test |
| The subsystem must execute all sensor reading and variable calculation functions | Communication Test, Operational State Transition Test |
| The subsystem must send all measured variables in a bytes frame via LoRa | Communication Test |
| The subsystem must open the parachute no more than 5s after the trigger conditions have been met | Drop Test (from PDM) |