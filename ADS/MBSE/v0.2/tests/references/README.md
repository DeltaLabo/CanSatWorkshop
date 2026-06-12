# ADS v0.2 test-reference corpus

This directory contains the saved search results and source documents used to derive the ADS subsystem test plan in `../README.md`. Sources were selected for CanSat mission context, NASA-style verification planning, GNSS performance, I2C/IMU/GPS device behavior, software-test process guidance, and statistical acceptance methods.

## Search records

Saved in `searches/`:

- `cansat-testing-guidelines.json`
- `semantic-scholar-cansat-testing-telemetry.json`
- `semantic-scholar-cansat-gps-imu-testing.json`
- `nasa-gevs-environmental-verification.json`
- `nasa-systems-engineering-verification.json`
- `gps-sps-performance-standard.json`
- `i2c-bus-specification.json`
- `icm-20948-datasheet.json`
- `icm20948-ds000189-pdf.json`
- `ubx-g7020-kt-datasheet.json`
- `software-testing-standard.json`
- `nist-statistical-methods-testing.json`
- `binomial-reliability-demonstration.json`
- `mil-std-810h-environmental-tests.json`

## Source documents and local extracts

Saved in `sources/`:

| Local source | Use in ADS tests |
|---|---|
| `esa_cansat_what_is.md` | CanSat size/flight/recovery context; recommends retrieval system, 120 s max flight time, descent-rate guidance, and testing of critical hardware. |
| `esa_cansat_book_23_24.pdf`, `.txt` | CanSat project/testing context and recovery/descent testing background. |
| `cansat_compendium_mdpi_machines_2023.pdf`, `.txt` | Literature context: CanSats commonly use GPS, IMU/environment sensors, telemetry/logging, and short descent windows. |
| `nasa_systems_engineering_handbook_2016.pdf`, `.txt` | Verification/validation framing: proof by test, analysis, inspection, demonstration; validation under realistic conditions. |
| `nasa_gevs_standard_page.md`; `nasa_gevs_gsfc_std_7000b.pdf`, `.txt` | Tailorable environmental verification/workmanship approach for hardware and associated software. |
| `mil_std_810h_everyspec_page.md` | Environmental-test method discovery/source page; use only as a tailored reference, not as a direct CanSat requirement. |
| `gps_sps_performance_standard_2020.pdf`, `.txt` | GPS SPS performance context, especially 95% horizontal/vertical position accuracy definitions. |
| `ublox_g7020_product_summary.pdf`, `.txt` | UBX-G7020 device capability: navigation update rate up to 10 Hz, position accuracy figures, UART/DDC/SPI/USB interfaces, electrical/temperature data. |
| `ublox_m8_receiver_protocol_spec.pdf`, `.txt` | u-blox receiver protocol background for UART/DDC configuration, valid-fix flags, UBX/NMEA message streams, and rate/port configuration. |
| `tdk_icm_20948_datasheet.pdf`, `.txt`; `tdk_invensense_icm20948_product_page.md` | ICM-20948 ranges, timing, I2C Fast-mode limits, gyro/accelerometer/magnetometer characteristics. |
| `nxp_um10204_i2c_spec.pdf`, `.txt` | I2C bus protocol and timing references: Standard/Fast-mode rates, START/STOP, ACK/NACK, bus-capacitance/timing concepts. |
| `iso_iec_ieee_29119_overview.md` | Software-test process and documentation context. |
| `nist_tolerance_intervals.md`; `nist_normal_tolerance_intervals.md` | Statistical tolerance-interval basis for continuous acceptance limits. |
| `reliability_test_design_binomial_reliasoft.md` | Non-parametric binomial/reliability-demonstration basis for zero-failure sample counts. |

Diagnostics folders under `sources/*.diagnostics/` preserve HTTP extraction details where direct extraction required workarounds.
