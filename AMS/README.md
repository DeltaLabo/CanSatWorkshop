# Atmospheric Measurement System

Owners: @darielmj, @anthonyarguedas

This subsystem collects atmospheric data, such as temperature and pressure, which are fundamental for the scientific and research objectives of the mission. AMS data needed by flight logic is delivered internally to the OBCC at `>=5 Hz` (`200 ms` nominal request period). The OBCC then packages the latest values into the v1.0 LoRa telemetry stream to the DPS at the separate `2 s` telemetry cadence, preserving each sample's status and age.

See [Understanding Capella Physical Diagrams](./../PM&SE//Understanding%20Capella%20Physical%20Diagrams/Understanding%20Capella%20Physical%20Diagrams.md) if needed.

See [Variable Getter Template](./../OBCC/Variable%20Getter%20Template.md) if needed.

## Requirements

## System Requirements

Requirements based on the following norms:

- For temperature readings: [ISO-7726:1998  — "Ergonomics of the thermal environment — Instruments for measuring physical quantities.](https://cdn.standards.iteh.ai/samples/14562/0f8ba16a6e4d454f95d38708649e538a/ISO-7726-1998.pdf)
- For atmospheric pressure readings: [WMO-No. 8 (2018) – Guide to Meteorological Instruments and Methods of Observation](https://library.wmo.int/viewer/68695/?offset=3#page=147&viewer=picture&o=bookmark&n=0&q=)
- For pressure-altitude relationship: [ICAO Standard Atmosphere](https://aiac.ma/wp-content/uploads/2018/01/Manuel-de-l%E2%80%99atmosph%C3%A8re-Type-OACI-Doc7488-1.pdf)

| Requirement | Verification method |
| --- | --- |
| The Atmospheric Measurement System must be capable of collecting temperature data in the immediate environment of the CanSat with an accuracy of ±0.5 °C within the range of 10 °C to 40 °C. | Temperature Test |
| The Atmospheric Measurement System must have a response time of no more than 60 seconds for temperature measurements. | Response Time Test |
| The Atmospheric Measurement System must be capable of measuring atmospheric pressure with an accuracy of ±1 hPa and a resolution sufficient to detect altitude changes of 10 meters or less, based on the standard pressure-altitude relationship of 13 Pa per meter. | Flight Test |
| The Atmospheric Measurement System data needed by flight logic must be delivered internally to the On-Board Computer and Communication System (OBCC) with an update rate of at least 5 Hz; this is separate from the v1.0 LoRa telemetry cadence of 2 s. | Communication Test |
| The Atmospheric Measurement System must be shaded from direct sunlight and properly ventilated to prevent overheating and to ensure accurate temperature readings. | Visual Inspection Test |

### Pressure Accuracy Estimation

“…for altitudes at which mankind lives, the rate of decrease (lapse rate) for a standard atmosphere may be taken as a reduction of 0.13 mbar per meter of height above sea level…” [source](https://www.sciencedirect.com/science/article/pii/B9780081011232000017)

$$
\frac{\Delta P}{\Delta h}= \frac{0.13 \ \textrm{mbar}}{\textrm{m}} \cdot \frac{100 \ \textrm{Pa}}{1\ \textrm{mbar}} = 13 \ \textrm{Pa}/\textrm{m}
$$

$$
\Delta h_{min}= 10 \ \textrm{m} \Rightarrow \Delta P_{min} = 130 \ \textrm{Pa}
$$

### Success Criteria

The AMS has established a preliminary design capable of accurately measuring temperature and atmospheric pressure, delivering fresh internal responses to the OBCC at `>=5 Hz`, and supporting `2 s` telemetry packaging with preserved `status` and `age_ms`.

### Old Requirements before PDR

| **Requirement** | **Verification method** |
| --- | --- |
| The Atmosferic Measurement System must be capable of collecting temperature data in the immediate environment of the CanSat with an accuracy of ±10°C. | Temperature Test |
| The Atmosferic Measurement System must be capable of collecting the atmospheric pressure at an accuracy sufficient to detect changes equivalent to a minimum altitude variation of 10 meters, corresponding to a pressure change of 130 Pa, based on a lapse rate of 13 Pa per meter. | Flight Test |
| The Atmospheric Measurement System data needed by flight logic must be delivered internally to the On Board Computer & Communication System (OBCC) with an update rate of at least 5 Hz; this is separate from the v1.0 LoRa telemetry cadence. | Communication Test |

## Components

Temperature and Pressure sensor: **BME280**

[**BME280 Datasheet**](https://www.bosch-sensortec.com/media/boschsensortec/downloads/datasheets/bst-bme280-ds002.pdf)

**Accuracy Stats:**

**Temperature:** ±0.5 °C for temperatures within 0-65 °C

**Pressure:** ±1.0 hPa for temperatures within 0-65 °C.

**Pressure Resolution:** 0.18 Pa

**Pressure Range:** 300-1100 hPa