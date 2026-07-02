# Attitude Determination System

Owners: @GaboArayaIA, @diego211002, @KalebG13

The attitude determination system calculates and updates the CanSat’s orientation in flight, based on sensor data such as GPS and IMU. This is crucial for monitoring the CanSat’s relative position in the mission and provides essential orientation information for the mission.

See [Understanding Capella Physical Diagrams](./../PM&SE//Understanding%20Capella%20Physical%20Diagrams/Understanding%20Capella%20Physical%20Diagrams.md) if needed.

See [Variable Getter Template](./../OBCC/Variable_Getter_Template.md) if needed.

## Baseline scope notes

- **v0.2** is an incremental development baseline: `UBX-G7020-KT GPS` UART and `ICM20948` IMU I2C feed the `XIAO ESP32` Loop, with source-modeled `5 Hz` collection and Serial0 PC logging only. It does **not** claim v1.0 OBCC `Pointers`/`Returns` or LoRa delivery.
- **v1.0** models ADS/OBCC/backplane physical boundaries: ADS PCB sensors connect through the backplane to OBCC-side `XIAO ESP32-S3` ADS Processing, then internally to OBCC via modeled `Pointers` and `Returns`.
- v1.0 internal ADS-to-OBCC freshness is `5 Hz` (`200 ms` nominal): fresh data requires `status == VALID` and `age_ms <= 400 ms`; allowed status values are exactly `VALID`, `STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, `INIT_FAIL`. Stale/default/fault data must not be marked valid. The `2 s` LoRa telemetry cadence is a separate packaging/downlink concern.
- Article IDs, firmware commits, calibration IDs, and tool/script revisions are report-time configuration records, not open source-level acceptance gates.

## Diagram Sources

- [`MBSE/v0.1/`](./MBSE/v0.1/)
- [`MBSE/v0.2/`](./MBSE/v0.2/)
- [`MBSE/v0.3/`](./MBSE/v0.3/)
- [`MBSE/v1.0/`](./MBSE/v1.0/)

## Integration, Verification, and Validation (IVV) Plan

### Diagram sets by version

- **v0.1** — [physical PNG](./MBSE/v0.1/ADS_v0.1_view1_physical.png) · [logical PNG](./MBSE/v0.1/ADS_v0.1_view2_logical.png) · [functional allocation PNG](./MBSE/v0.1/ADS_v0.1_view3_functional_allocation.png) · [GPS position chain PNG](./MBSE/v0.1/ADS_v0.1_view4_gps_position_chain.png) · [serial logging chain PNG](./MBSE/v0.1/ADS_v0.1_view5_serial_logging_chain.png)
- **v0.2** — [physical PNG](./MBSE/v0.2/ADS_v0.2_view1_physical.png) · [logical PNG](./MBSE/v0.2/ADS_v0.2_view2_logical.png) · [functional allocation PNG](./MBSE/v0.2/ADS_v0.2_view3_functional_allocation.png) · [GPS position chain PNG](./MBSE/v0.2/ADS_v0.2_view4_gps_position_chain.png) · [angular velocity chain PNG](./MBSE/v0.2/ADS_v0.2_view5_angular_velocity_chain.png) · [attitude estimation chain PNG](./MBSE/v0.2/ADS_v0.2_view6_attitude_estimation_chain.png) · [peripheral initialisation chain PNG](./MBSE/v0.2/ADS_v0.2_view7_peripheral_initialisation_chain.png) · [serial logging chain PNG](./MBSE/v0.2/ADS_v0.2_view8_serial_logging_chain.png)
- **v0.3** — [PCB delivery physical PNG](./MBSE/v0.3/ADS_v0.3_view1_physical.png) · [D2 source](./MBSE/v0.3/ADS_v0.3_view1_physical.d2)
- **v1.0** — [physical PNG](./MBSE/v1.0/ADS_v1.0_view1_physical.png) · [logical PNG](./MBSE/v1.0/ADS_v1.0_view2_logical.png) · [functional allocation PNG](./MBSE/v1.0/ADS_v1.0_view3_functional_allocation.png) · [GPS position chain PNG](./MBSE/v1.0/ADS_v1.0_view4_gps_position_chain.png) · [angular velocity chain PNG](./MBSE/v1.0/ADS_v1.0_view5_angular_velocity_chain.png) · [attitude estimation chain PNG](./MBSE/v1.0/ADS_v1.0_view6_attitude_estimation_chain.png) · [peripheral initialisation chain PNG](./MBSE/v1.0/ADS_v1.0_view7_peripheral_initialisation_chain.png)

### Latest split views

Latest complete split views are grouped under [`./MBSE/v1.0/`](./MBSE/v1.0/). The PCB-only delivery view is under [`./MBSE/v0.3/`](./MBSE/v0.3/).

![view 1 physical](./MBSE/v1.0/ADS_v1.0_view1_physical.png)
View 1 — physical architecture and physical links ([D2 source](./MBSE/v1.0/ADS_v1.0_view1_physical.d2))

![view 2 logical](./MBSE/v1.0/ADS_v1.0_view2_logical.png)
View 2 — logical components and component exchanges ([D2 source](./MBSE/v1.0/ADS_v1.0_view2_logical.d2))

![view 3 functional allocation](./MBSE/v1.0/ADS_v1.0_view3_functional_allocation.png)
View 3 — functional allocation across physical and logical components ([D2 source](./MBSE/v1.0/ADS_v1.0_view3_functional_allocation.d2))

![view 4 GPS position](./MBSE/v1.0/ADS_v1.0_view4_gps_position_chain.png)
View 4 — GPS position polling and cached-value functional chain ([D2 source](./MBSE/v1.0/ADS_v1.0_view4_gps_position_chain.d2))

![view 5 angular velocity](./MBSE/v1.0/ADS_v1.0_view5_angular_velocity_chain.png)
View 5 — angular velocity sensing and processing functional chain ([D2 source](./MBSE/v1.0/ADS_v1.0_view5_angular_velocity_chain.d2))

![view 6 attitude estimation](./MBSE/v1.0/ADS_v1.0_view6_attitude_estimation_chain.png)
View 6 — attitude estimation functional chain ([D2 source](./MBSE/v1.0/ADS_v1.0_view6_attitude_estimation_chain.d2))

![view 7 peripheral initialisation](./MBSE/v1.0/ADS_v1.0_view7_peripheral_initialisation_chain.png)
View 7 — peripheral initialisation reporting chain ([D2 source](./MBSE/v1.0/ADS_v1.0_view7_peripheral_initialisation_chain.d2))

![v0.3 PCB delivery](./MBSE/v0.3/ADS_v0.3_view1_physical.png)
ADS v0.3 — PCB-only delivery physical view ([D2 source](./MBSE/v0.3/ADS_v0.3_view1_physical.d2))

## Requirements

| **Requirement** | **Verification method** |
| --- | --- |
| The ADS must determine GPS position with strict error `<5 m`; strict truth is a GNSS simulator or surveyed/open-sky reference. | Integration Test |
| The ADS must determine 3-axis angular rate with strict error `<30 deg/s` against a calibrated rate reference. | Communication Test |
| The ADS must determine linear acceleration in 3 axes in `m/s²` (or `g` converted to `m/s²`); the verification threshold is controlled by `ADS-IVV-C-ACCEL-3AXIS`. The legacy `30 deg/s^2` wording is not used as the acceleration oracle. | Communication Test |
| The ADS must determine orientation to north with quantitative heading criteria controlled by `ADS-IVV-C-HEADING-NORTH`. | Integration Test |
| v1.0 ADS data needed by flight logic must be delivered internally to OBCC at `5 Hz` (`200 ms` nominal) through modeled `Pointers`/`Returns`; fresh data requires `status == VALID` and `age_ms <= 400 ms`, with no stale/default/fault data marked valid. | Communication Test |
| v1.0 runtime must maintain progress for `10 min` / `600 s` (`3000` expected 5 Hz slots), with max freshness/progress gap `400 ms`, no reset/brownout/stuck loop/unrecovered peripheral failure, process/calculate `<5 ms`, UART/I2C reads `<=5 ms`, and no blocking beyond bounded UART/I2C. | Integration Test |

### Success Criteria

The ADS presents a functional design capable of determining the CanSat’s position, orientation, acceleration, and rotation with the required accuracy, ensuring internal data delivery to the OBCC.

## Components

GPS: **UBX-G7020-KT GPS**

https://www.robotshop.com/products/gps-module-ubx-g7020-kt-enclosure?qd=6880226c030e69d617cd8368fe0825b5

IMU: **ICM20948**

Controllers as modeled: **XIAO ESP32** for v0.2 development logging, **XIAO ESP32-S3** for v1.0 OBCC-side ADS Processing.
