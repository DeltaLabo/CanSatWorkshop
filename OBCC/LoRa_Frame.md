# LoRa Frame

Controlled verification baseline: this table is the active `OBCC-LORA-PAYLOAD-v1.0` variable baseline referenced by [`../PM&SE/contracts/obcc_dps_lora_telemetry_contract.md`](../PM&SE/contracts/obcc_dps_lora_telemetry_contract.md). It defines the active measurement/status payload fields; envelope IDs, command/request fields, schema/version, sequence/timestamp, health/status metadata outside the listed fields, RSSI/SNR evidence, and parser/decoder mappings are controlled by the contract or by execution-specific configuration records. Relative humidity is not part of this active v1.0 payload.

- int16 range: [-32768, 32767]

## Peripherals

| Name | Criticality |
| --- | --- |
| RFM96W | Critical |
| BME280 | Critical |
| Servo | Critical |
| UBX G7020 | Non-critical |
| INA219 | Non-critical |
| ICM20948 | Non-critical |

## Variables

| Name | Unit | Raw type | Range | Decimals | Final type | Final bytes | Variable-table byte offset |
| --- | --- | --- | --- | --- | --- | --- | --- |
| Pitch | rad | float | ]-6.29, 6.29[ | 2 | int16 | 2 | 0 |
| Roll | rad | float | ]-6.29, 6.29[ | 2 | int16 | 2 | 2 |
| Yaw | rad | float | ]-6.29, 6.29[ | 2 | int16 | 2 | 4 |
| Angular Speed X | rad/s | float | ]-327.68, 327.68[ | 2 | int16 | 2 | 6 |
| Angular Speed Y | rad/s | float | ]-327.68, 327.68[ | 2 | int16 | 2 | 8 |
| Angular Speed Z | rad/s | float | ]-327.68, 327.68[ | 2 | int16 | 2 | 10 |
| Acceleration X | m/s2 | float | ]-327.68, 327.68[ | 2 | int16 | 2 | 12 |
| Acceleration Y | m/s2 | float | ]-327.68, 327.68[ | 2 | int16 | 2 | 14 |
| Acceleration Z | m/s2 | float | ]-327.68, 327.68[ | 2 | int16 | 2 | 16 |
| Altitude | m | float | [0, 500] | 0 | int16 | 2 | 18 |
| Temperature | Celsius | int | [10.0, 40.0] | 1 | int16 | 2 | 20 |
| Latitude |  | float | NA | 5 | float | 4 | 22 |
| Longitude |  | float | NA | 5 | float | 4 | 26 |
| Battery Voltage | V | float | [0.0, 3.7] | 2 | int16 | 2 | 30 |
| Battery Current | mA | int | [0, 1500] | 0 | int16 | 2 | 32 |
| Parachute Deployment Status (`deployment_status`) | code | uint8 enum | [0, 9] | 0 | uint8 | 1 | 34 |

Current variable-table size: **35 bytes** before LoRa envelope, IDs, command/request fields, schema/version, sequence/timestamp, health/status metadata outside the listed fields, RSSI/SNR logging fields, delimiters, or other envelope overhead. `deployment_status` is the final variable-table byte at zero-based offset **34**. This remains within the existing 100-byte OBCC-to-DPS LoRa telemetry frame basis; the current firmware/DPS packet mapping carries the same one-byte status at payload byte offset **48**, with bytes 49..95 reserved before the footer.

## Parachute deployment status enum

`deployment_status` is a one-byte unsigned enum sourced from PDM/actuator confirmation evidence exposed to OBCC or from OBCC-owned deployment/fault-policy interpretation. It is not a command-success shortcut: `COMMAND_SENT` only means OBCC sent an open command. DPS, CSV, dashboard, and report consumers shall preserve code, symbol, and category and shall treat only `OPEN_CONFIRMED` as deployed/success; all other values, missing status bytes, and unrecognized codes are never success.

| Code | Symbol | Category | Meaning |
| --- | --- | --- | --- |
| 0 | `NOT_COMMANDED` | `not-deployed` | No accepted deployment command/current trigger context. |
| 1 | `INHIBITED_STANDBY` | `not-deployed` | Request suppressed because OBCC is in Stand-by. |
| 2 | `COMMAND_SENT` | `in-progress` | OBCC sent open command; not success by itself. |
| 3 | `OPEN_IN_PROGRESS` | `in-progress` | Actuator/PDM response underway, not confirmed. |
| 4 | `OPEN_CONFIRMED` | `deployed` | PDM feedback or independent safe-fixture/current/position observer confirms open; only success/deployed state. |
| 5 | `NO_OPEN_CONFIRMED` | `not-deployed` | Observer/feedback confirms no open. |
| 6 | `TIMEOUT` | `fault` | No open confirmation within declared timing window. |
| 7 | `JAM_DETECTED` | `fault` | Current/position/feedback indicates jam/blocked travel. |
| 8 | `PDM_FAULT` | `fault` | PDM reports fault or command path unavailable. |
| 9 | `UNKNOWN` | `unknown` | Cannot prove status; never success. |

```mermaid
graph LR
  Start((Start)) --> Checks[Check non-criticals]
  subgraph Startup
  Checks -->|Faulty non-criticals| NC[Disable non-criticals]
  NC --> CC[Check criticals] -->|Faulty criticals| Fail((Startup fail))
  Checks --> CC
  CC --> PL((Loop))
  end
  subgraph "Program Loop"
  PL --> Read[Read sensors] --> Vars[Calculate variables]
  Vars -->|Parachute trigger| Parachute[Open parachute]
  Vars --> LoRa[LoRa comms]
  LoRa --> PL
  end
```