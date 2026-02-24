# Atmospheric Measurement System

Owners: @Cubillo29, @nicolepradom

This subsystem collects atmospheric data, such as temperature, pressure, and humidity, which are fundamental for the scientific and research objectives of the mission. Data is sent in real-time to the DPS for analysis, helping to monitor the CanSat’s environmental conditions in flight.

See [Understanding Capella Physical Diagrams](./../..//Understanding%20Capella%20Physical%20Diagrams/Understanding%20Capella%20Physical%20Diagrams.md) if needed.

## Integration, Verification, and Validation (IVV) Plan

![v0.1. Mostly a reminder that initial tests don’t need PCB assembly.](AMS_v0.1.jpg)
v0.1. Mostly a reminder that initial tests don’t need PCB assembly.

![v1.0.](AMS_v1.0.jpg)
v1.0.

## Requirements

## System Requirements

Requirements based on the following norms:

- For temperature and humidity readings: [ISO-7726:1998  — "Ergonomics of the thermal environment — Instruments for measuring physical quantities.](https://cdn.standards.iteh.ai/samples/14562/0f8ba16a6e4d454f95d38708649e538a/ISO-7726-1998.pdf)
- For atmospheric pressure readings: [WMO-No. 8 (2018) – Guide to Meteorological Instruments and Methods of Observation](https://library.wmo.int/viewer/68695/?offset=3#page=147&viewer=picture&o=bookmark&n=0&q=)
- For pressure-altitude relationship: [ICAO Standard Atmosphere](https://aiac.ma/wp-content/uploads/2018/01/Manuel-de-l%E2%80%99atmosph%C3%A8re-Type-OACI-Doc7488-1.pdf)

| Requirement | Verification method |
| --- | --- |
| The Atmospheric Measurement System must be capable of collecting temperature data in the immediate environment of the CanSat with an accuracy of ±0.5 °C within the range of 10 °C to 40 °C. | Temperature Test |
| The Atmospheric Measurement System must measure the relative humidity around the CanSat with an accuracy of ±5 %RH within the range of 20 % to 80 %. | Humidity Test |
| The Atmospheric Measurement System must have a response time of no more than 60 seconds for both temperature and humidity measurements. | Response Time Test |
| The Atmospheric Measurement System must be capable of measuring atmospheric pressure with a precision of at least ±1 hPa and a resolution sufficient to detect altitude changes of 10 meters or less, based on the standard pressure-altitude relationship of 13 Pa per meter. | Flight Test |
| The Atmospheric Measurement System must transmit data in real-time to the On-Board Computer and Communication System (OBCC) with an update rate of at least 5 Hz. | Communication Test |
| The Atmospheric Measurement System must be shaded from direct sunlight and properly ventilated to prevent overheating and to ensure accurate temperature and humidity readings. | Visual Inspection Test |

### Pressure Accuracy Estimation

“…for altitudes at which mankind lives, the rate of decrease (lapse rate) for a standard atmosphere may be taken as a reduction of 0.13 mbar per meter of height above sea level…” [source](https://www.sciencedirect.com/science/article/pii/B9780081011232000017)

$$
\frac{\Delta P}{\Delta h}= \frac{0.13 \ \textrm{mbar}}{\textrm{m}} \cdot \frac{100 \ \textrm{Pa}}{1\ \textrm{mbar}} = 13 \ \textrm{Pa}/\textrm{m}
$$

$$
\Delta h_{min}= 5 \ \textrm{m} \Rightarrow \Delta P_{min} = 65 \ \textrm{Pa}
$$

### Success Criteria

The AMS has established a preliminary design capable of accurately measuring temperature, humidity, and atmospheric pressure, and transmitting this data in real time to the OBCC.

### Old Requirements before PDR

| **Requirement** | **Verification method** |
| --- | --- |
| The Atmosferic Measurement System must be capable of collecting temperature data in the immediate environment of the CanSat with an accuracy of ±10°C. | Temperature Test |
| The Atmosferic Measurement System must measure relative humidity around the CanSat with an accuracy of ±10%. | Humidity Test |
| The Atmosferic Measurement System must be capable of collecting the atmospheric pressure at an accuracy sufficient to detect changes equivalent to a minimum altitude variation of 10 meters, corresponding to a pressure change of 130 Pa, based on a lapse rate of 13 Pa per meter. | Flight Test |
| The Atmospheric Measurement System data must be transmitted in real-time to the On Board Computer & Communication System (OBCC) with an update rate of at least 5 Hz. | Communication Test |