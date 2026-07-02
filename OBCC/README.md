# On-board Computer and Communications

Owners: @anthonyarguedas

This subsystem is the “brain” of the CanSat, coordinating all sensors and actuators to work in sync. Its communication system transmits vital information to the ground station over long distances, ensuring real-time telemetry and status data transmission.

## Requirements

| **Requirement** | **Verification method** |
| --- | --- |
| The On Board Computer & Communication System must manage all sensors and actuators, ensuring proper synchronization of each system. | Integration Test |
| The On Board Computer & Communication System must transmit telemetry data over a minimum radio of 500 m regardless of the topography at intervals of 2 seconds to the DPS. With a transmission success rate of 90%. | Communication Test |
| The On Board Computer & Communication System must verify that all sensor and actuator data is transmitted over a bus due to its ease of use. | PCB inspection |
| The On Board Computer & Communication System shall support the following operational states: “Stand-by” and “On”, when commanded by the *Data Processing System (DPS)* to switch between these operational states. | Operational State Transition Test |

### Success Criteria

The OBCC subsystem has established an architecture that manages sensor and actuator coordination in the Cansat, enables reliable long-range data transmission, and supports multiple operational states commanded by the DPS. For v1.0, operational observability is through LoRa health/state telemetry; USB/serial diagnostics may be used as a bench aid but are not a required flight-operator path.

### Parachute deployment status telemetry

OBCC-to-DPS LoRa telemetry includes `deployment_status` as a one-byte enum in the existing 100-byte payload (current firmware/DPS byte offset `48`; schema traceability through `OBCC-LORA-PAYLOAD-v1.0` final variable-table field at offset `34`). The field is sourced from PDM/actuator confirmation evidence when integrated, or from OBCC-owned deployment/fault policy interpretation. Consumers preserve the enum code, symbol, and category. `COMMAND_SENT` means only that OBCC sent an open command; it is not deployment success. Only `OPEN_CONFIRMED` shall be treated as deployed/success; `COMMAND_SENT`, `OPEN_IN_PROGRESS`, inhibited, no-open, timeout, jam, fault, unknown, missing, or unrecognized states must remain non-success rather than false success.

## Derived Requirements

| Requirement | Verification method |
| --- | --- |
| The subsystem must perform startup checks for all peripherals | Test setup: Manually disconnect each peripheral and run startup.

Pass/Fail criteria: PASS if health/status telemetry or local test-harness diagnostics acknowledge the missing peripheral, FAIL otherwise. |
| The subsystem must enter an error state if any critical peripheral is faulty at startup | Test setup: Manually disconnect each critical peripheral and run startup.

Pass/Fail criteria: PASS if all the following hold:

- Health/status telemetry or local test-harness diagnostics acknowledge the missing peripheral, explicitly mark it as startup-critical, and state that OBCC cannot enter operational mode without it
- The OBCC does not enter operational mode

FAIL otherwise. |
| The subsystem must disable the functionalities that depend on any non-critical components that are faulty at startup | Test setup: Manually disconnect all non-critical peripheral and run startup.

Pass/Fail criteria: PASS if all the following hold:
- Health/status telemetry or local test-harness diagnostics acknowledge the missing peripherals and explicitly mark them as non-critical for startup
- The OBCC enters operational mode in a degraded configuration
- Comms work normally with error-coded, zero, null, or stale-marked values for the variables related to the missing peripherals

FAIL otherwise. |
| The subsystem must indicate when no startup checks failed | Test setup: Run startup with all peripherals connected and operational

Pass/Fail criteria: PASS if health/status telemetry or local test-harness diagnostics indicate that all startup checks have been completed successfully, FAIL otherwise. |
| The subsystem must execute scheduled runtime tasks at their modeled cadence after successful startup | Communication Test, Operational State Transition Test |
| The subsystem must execute all sensor reading and variable calculation functions without unbounded blocking | Communication Test, Operational State Transition Test |
| Runtime sensor/getter faults must be disclosed as bounded error/result codes and must not brick the CanSat; OBCC/PDM shall emergency deploy when the modeled safety policy requires it | Runtime Fault Injection Test |
| The subsystem must send all measured variables and health/status metadata in a bytes frame via LoRa | Communication Test |
| The subsystem must open the parachute no more than 5s after the trigger conditions have been met | Drop Test (from PDM) |