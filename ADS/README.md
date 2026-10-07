# Attitude Determination System

Owners: @GaboArayaIA, @diego211002, @KalebG13

The attitude determination system calculates and updates the CanSat’s orientation in flight, based on sensor data such as GPS and IMU. This is crucial for monitoring the CanSat’s relative position in the mission and provides essential orientation information for the mission.

See [Understanding Capella Physical Diagrams](./../PM&SE//Understanding%20Capella%20Physical%20Diagrams/Understanding%20Capella%20Physical%20Diagrams.md) if needed.

See [Variable Getter Template](./../OBCC/Variable_Getter_Template.md) if needed.

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
