# OBCC MBSE test references

This directory contains the search records and locally saved source artifacts used to build `../README.md`.

## Search records

| File | Purpose |
|---|---|
| `searches/cansat_test_requirements.json` | CanSat test, telemetry, ground-station and environmental-test requirements. |
| `searches/ecss_testing_standard.json` | ECSS-E-ST-10-03C testing standard discovery. |
| `searches/nasa_gevs.json` | NASA GSFC-STD-7000B GEVS environmental verification discovery. |
| `searches/nasa_software_assurance.json` | NASA-STD-8739.8 software assurance/safety discovery. |
| `searches/i2c_um10204.json` | NXP UM10204 I2C specification discovery. |
| `searches/rfm95w_lora_datasheet.json` | RFM95W/SX127x LoRa transceiver data-sheet discovery. |
| `searches/freertos_queues_timers_mutexes_isr.json` | FreeRTOS queue/mutex/timer/ISR documentation discovery. |
| `searches/lora_pdr_outdoor_measurement.json` | Web search for LoRa outdoor packet-delivery evidence. |
| `searches/semantic_lora_pdr.json` | Initial Semantic Scholar search for LoRa packet-delivery ratio literature. |
| `searches/semantic_lora_pdr_rain_refined.json` | Refined LoRa PDR/rain search. |
| `searches/semantic_lora_pdr_rain_exact.json` | Exact-title search for the selected LoRa PDR/rain paper. |
| `searches/binomial_reliability_statistics.json` | Sources for binomial reliability/confidence planning. |
| `searches/nonparametric_tolerance_95_95.json` | Sources for nonparametric tolerance interval planning. |

## Source artifacts

| File | Source / relevance |
|---|---|
| `sources/ecss-e-st-10-03-rev1-testing.pdf` | ECSS-E-ST-10-03C Rev.1, *Testing*; basis for test tailoring, qualification/acceptance/protoflight language, and test documentation expectations. |
| `sources/gsfc-std-7000b-gevs.pdf` | NASA GSFC-STD-7000B GEVS; basis for environmental verification tailoring, verification matrices, workmanship/vibration/thermal context. |
| `sources/nasa-std-8739-8b-software-assurance.pdf` | NASA-STD-8739.8B; basis for software assurance, traceability and IV&V-oriented evidence. |
| `sources/cansat-mission-guide-2025e.pdf` | CanSat mission guide; basis for educational CanSat telemetry, ground-station, drop, thermal, vibration and vacuum-style tests. |
| `sources/andoya-cansat-telemetry-system.md` | Andøya CanSat telemetry tutorial; practical telemetry/ground-station/radio-logging reference. |
| `sources/rfm95w-v2.0.pdf` | HopeRF RFM95W LoRa transceiver data sheet; basis for LoRa packet/CRC, SPI interface and radio evidence. |
| `sources/nxp-um10204-i2c-bus-specification.pdf` | NXP UM10204 I2C-bus specification; basis for I2C SDA/SCL/START/STOP/ACK behavior checks. |
| `sources/freertos-intertask-coordination.md` | FreeRTOS inter-task coordination documentation; basis for queues, semaphores/mutexes, direct notifications and ISR/task coordination checks. |
| `sources/esp-idf-freertos-api.md` | ESP-IDF FreeRTOS API documentation; basis for ESP32 task/queue/timer API checks. |
| `sources/reliability-test-design-reliasoft.md` | Reliability test design overview; used with exact binomial calculations for repeated event tests. |
| `sources/minitab-nonparametric-tolerance-intervals.md` | Nonparametric tolerance interval formulas; basis for 95/95 deadline/continuous-limit sample planning. |
| `sources/enhancement-packet-delivery-ratio-lora-mesh.pdf` | Hossinuzzaman & Dahnil, LoRa PDR during rain attenuation; supports measuring packet-delivery ratio in real outdoor conditions. |
| `sources/nature-lora-signal-propagation-pdr.md` | UAV/ground LoRaWAN propagation dataset article metadata; supports logging RSSI/SNR/timestamps for radio characterization. |

## Reference notes carried into the test plan

- The OBCC model, not a generic competition rule, sets the v1.0 telemetry cadence at **2 seconds** and excludes relative humidity from the payload.
- The model requires **wireless On/Standby commands** and explicitly removes a serial-console operator path for flight operations.
- LoRa downlink performance is environment-sensitive, so the plan requires packet-delivery testing in the final antenna geometry at the modeled **>=500 m** range rather than relying on data-sheet range claims.
- Repeated pass/fail events are evaluated with exact one-sided binomial confidence; timing/deadline limits use distribution-free one-sided tolerance logic when a 95/95 claim is needed.
