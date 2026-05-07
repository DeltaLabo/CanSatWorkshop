# Attitude Determination System

Owners: @GaboArayaIA, @diego211002, @KalebG13

The attitude determination system calculates and updates the CanSat’s orientation in flight, based on sensor data such as GPS and IMU. This is crucial for monitoring the CanSat’s relative position in the mission and provides essential orientation information for the mission.

See [Understanding Capella Physical Diagrams](./../PM&SE//Understanding%20Capella%20Physical%20Diagrams/Understanding%20Capella%20Physical%20Diagrams.md) if needed.

See [Variable Getter Template](./../OBCC/Variable%20Getter%20Template.md) if needed.

## Subsystem Integration Version (SSIV) 

![v0.1](ADS_v0.1.jpg)
v0.1

![v0.2](ADS_v0.2.jpg)
v0.2

![v1.0](ADS_v1.0.jpg)
v1.0

## Integration, Verification, and Validation (IVV) Plan

The ADS v1.0 MBSE views translated from Capella XML to D2 are available in [`./MBSE/v1.0/`](./MBSE/v1.0/):

### Architecture views
- [View 1 — Physical view (PNG)](./MBSE/v1.0/ADS_v1.0_view1_physical.png) · [D2 source](./MBSE/v1.0/ADS_v1.0_view1_physical.d2)
- [View 2 — Logical view (PNG)](./MBSE/v1.0/ADS_v1.0_view2_logical.png) · [D2 source](./MBSE/v1.0/ADS_v1.0_view2_logical.d2)
- [View 3 — Functional allocation view (PNG)](./MBSE/v1.0/ADS_v1.0_view3_functional_allocation.png) · [D2 source](./MBSE/v1.0/ADS_v1.0_view3_functional_allocation.d2)

### Functional chain views
- [View 4 — GPS position chain (PNG)](./MBSE/v1.0/ADS_v1.0_view4_gps_position_chain.png) · [D2 source](./MBSE/v1.0/ADS_v1.0_view4_gps_position_chain.d2)
- [View 5 — Angular velocity chain (PNG)](./MBSE/v1.0/ADS_v1.0_view5_angular_velocity_chain.png) · [D2 source](./MBSE/v1.0/ADS_v1.0_view5_angular_velocity_chain.d2)
- [View 6 — Attitude estimation chain (PNG)](./MBSE/v1.0/ADS_v1.0_view6_attitude_estimation_chain.png) · [D2 source](./MBSE/v1.0/ADS_v1.0_view6_attitude_estimation_chain.d2)
- [View 7 — Peripheral initialisation chain (PNG)](./MBSE/v1.0/ADS_v1.0_view7_peripheral_initialisation_chain.png) · [D2 source](./MBSE/v1.0/ADS_v1.0_view7_peripheral_initialisation_chain.d2)

Recommended reading order: View 1 → View 2 → View 3 → View 4 → View 5 → View 6 → View 7.

This order goes from physical structure to logical allocation, then follows the main ADS flows: GPS position acquisition, angular-rate sensing, attitude estimation, and peripheral initialisation reporting.

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