# Attitude Determination System

Owners: @GaboArayaIA, @diego211002, @KalebG13

The attitude determination system calculates and updates the CanSat’s orientation in flight, based on sensor data such as GPS and IMU. This is crucial for monitoring the CanSat’s relative position in the mission and provides essential orientation information for the mission.

See [Understanding Capella Physical Diagrams](./../PM&SE//Understanding%20Capella%20Physical%20Diagrams/Understanding%20Capella%20Physical%20Diagrams.md) if needed.

See [Variable Getter Template](./../OBCC/Variable%20Getter%20Template.md) if needed.

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
| The Altitute determination system must determine the position of the CanSat with an accuracy of less than 5m under open sky. | Integration Test |
| The ADS must determine the angles of rotation in 3 axes with an accuracy of 30 deg/s. | Communication Test |
| The ADS must determine the acceleration in 3 axes with an accuracy of 30 deg/s^2. | Communication Test |
| The ADS  must determine the orientation  to the north. | Integration Test |
| All ADS data needed by flight logic must be delivered internally to the OBCC with an update rate of at least 5 Hz; this is separate from the v1.0 LoRa telemetry cadence. | Communication Test |

### Success Criteria

The ADS presents a functional design capable of determining the CanSat’s position, orientation, acceleration, and rotation with the required accuracy, ensuring internal data delivery to the OBCC.

## Components

GPS:

https://www.robotshop.com/products/gps-module-ubx-g7020-kt-enclosure?qd=6880226c030e69d617cd8368fe0825b5

IMU: [https://www.amazon.com/-/es/dp/B0DZ2MHSJ6/ref=sr_1_9?__mk_es_US=ÅMÅŽÕÑ&dib=eyJ2IjoiMSJ9.MdKyLwZ4832ylX3VPjX9dQ7kjZyskSQobXiQ5nkS8GmbMrh1YktK-Jf1_B7ptU2bTenENvOtWaBGEF_vbMhFIOanLcprl0x7KkCNnE1Dc9Ool0FPW7fqXgRKQdT7SvnmXUkYgEil2XKrWa85BL00IQ.hF0_eVr7xy7s35L26tJXCYdrJ8iIi_2qJ_y7thbin-g&dib_tag=se&keywords=MPU9250&qid=1741380426&sr=8-9](https://www.amazon.com/-/es/dp/B0DZ2MHSJ6/ref=sr_1_9?__mk_es_US=%C3%85M%C3%85%C5%BD%C3%95%C3%91&dib=eyJ2IjoiMSJ9.MdKyLwZ4832ylX3VPjX9dQ7kjZyskSQobXiQ5nkS8GmbMrh1YktK-Jf1_B7ptU2bTenENvOtWaBGEF_vbMhFIOanLcprl0x7KkCNnE1Dc9Ool0FPW7fqXgRKQdT7SvnmXUkYgEil2XKrWa85BL00IQ.hF0_eVr7xy7s35L26tJXCYdrJ8iIi_2qJ_y7thbin-g&dib_tag=se&keywords=MPU9250&qid=1741380426&sr=8-9)