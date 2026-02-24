# Attitude Determination System

Owners: @KGaboArayaIA, @diego211002, @KalebG13

The attitude determination system calculates and updates the CanSat’s orientation in flight, based on sensor data such as GPS and IMU. This is crucial for monitoring the CanSat’s relative position in the mission and provides essential orientation information for the mission.

See [Understanding Capella Physical Diagrams](./../..//Understanding%20Capella%20Physical%20Diagrams/Understanding%20Capella%20Physical%20Diagrams.md) if needed.

## Subsystem Integration Version (SSIV) 

![v0.1](ADS_v0.1.jpg)
v0.1

![v0.2](ADS_v0.2.jpg)
v0.2

![v1.0](ADS_v1.0.jpg)
v1.0

## Requirements

| **Requirement** | **Verification method** |
| --- | --- |
| The Altitute determination system must determine the position of the CanSat with an accuracy of less than 5m under open sky. | Integration Test |
| The ADS must determine the angles of rotation in 3 axes with an accuracy of 30 deg/s. | Communication Test |
| The ADS must determine the acceleration in 3 axes with an accuracy of 30 deg/s^2. | Communication Test |
| The ADS  must determine the orientation  to the north. | Integration Test |
| All ADS data must be transmitted to the OBCC with a rate of 5 Hz. | Communication Test |

### Success Criteria

The ADS presents a functional design capable of determining the CanSat’s position, orientation, acceleration, and rotation with the required accuracy, ensuring data transmission to the OBCC