# Attitude Determination System

Owners: @GaboArayaIA, @diego211002, @KalebG13

The attitude determination system calculates and updates the CanSat’s orientation in flight, based on sensor data such as GPS and IMU. This is crucial for monitoring the CanSat’s relative position in the mission and provides essential orientation information for the mission.

See [Understanding Capella Physical Diagrams](./../PM&SE//Understanding%20Capella%20Physical%20Diagrams/Understanding%20Capella%20Physical%20Diagrams.md) if needed.

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

## Components

GPS:

https://www.robotshop.com/products/gps-module-ubx-g7020-kt-enclosure?qd=6880226c030e69d617cd8368fe0825b5

IMU: [https://www.amazon.com/-/es/dp/B0DZ2MHSJ6/ref=sr_1_9?__mk_es_US=ÅMÅŽÕÑ&dib=eyJ2IjoiMSJ9.MdKyLwZ4832ylX3VPjX9dQ7kjZyskSQobXiQ5nkS8GmbMrh1YktK-Jf1_B7ptU2bTenENvOtWaBGEF_vbMhFIOanLcprl0x7KkCNnE1Dc9Ool0FPW7fqXgRKQdT7SvnmXUkYgEil2XKrWa85BL00IQ.hF0_eVr7xy7s35L26tJXCYdrJ8iIi_2qJ_y7thbin-g&dib_tag=se&keywords=MPU9250&qid=1741380426&sr=8-9](https://www.amazon.com/-/es/dp/B0DZ2MHSJ6/ref=sr_1_9?__mk_es_US=%C3%85M%C3%85%C5%BD%C3%95%C3%91&dib=eyJ2IjoiMSJ9.MdKyLwZ4832ylX3VPjX9dQ7kjZyskSQobXiQ5nkS8GmbMrh1YktK-Jf1_B7ptU2bTenENvOtWaBGEF_vbMhFIOanLcprl0x7KkCNnE1Dc9Ool0FPW7fqXgRKQdT7SvnmXUkYgEil2XKrWa85BL00IQ.hF0_eVr7xy7s35L26tJXCYdrJ8iIi_2qJ_y7thbin-g&dib_tag=se&keywords=MPU9250&qid=1741380426&sr=8-9)