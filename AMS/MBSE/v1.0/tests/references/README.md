# AMS test reference corpus

Reference material collected for `../READNE.md`. Search result JSON files are in `searches/`; retrieved source artifacts are in `sources/`.

## Source artifacts

| Source | Local artifact | Use in test plan |
|---|---|---|
| ISO 7726:1998 page and sample | `sources/iso_7726_1998_page.md`, `sources/ISO-7726-1998-sample.pdf` | thermal measurement instrumentation, accuracy, response concepts |
| ISO 7726:2025 page | `sources/iso_7726_2025_page.md` | current standard status and scope |
| REHVA overview of ISO 7726 | `sources/rehva_iso7726_overview.md` | accessible discussion of ISO 7726 tolerances and response time |
| WMO-No. 8 official page and Volume I PDF | `sources/wmo_no8_official_page.md`, `sources/WMO_No8_Volume_I_2023.pdf` | meteorological temperature/pressure measurement, exposure, calibration, traceability, uncertainty |
| ICAO Doc 7488 store page and sample | `sources/icao_doc7488_store_page.md`, `sources/ICAO-7488-1993-sample.pdf` | standard atmosphere and pressure-altitude relationship |
| Bosch Sensortec BME280 datasheet/product page | `sources/BST-BME280-DS002_datasheet.pdf`, `sources/bosch_bme280_product_page.md` | sensor ranges, accuracy, resolution, pressure noise, I2C interface |
| NXP/Nexperia UM10204 I2C specification | `sources/Nexperia_NXP_UM10204_I2C_spec.pdf`, `sources/nxp_community_um10204_location.md` | SDA/SCL protocol, START/STOP, ACK/NACK, timing/interface behavior |
| JCGM 100:2008 GUM | `sources/JCGM_100_2008_GUM.pdf` | uncertainty expression and confidence/coverage concepts |
| NIST/SEMATECH Engineering Statistics Handbook | `sources/nist_engineering_statistics_handbook_page.md`, `sources/nist_tolerance_intervals_largest_smallest.md` | measurement statistics and tolerance intervals |
| CanSat environmental/mission guides | `sources/CanSat_Mission_Guide_2025d.pdf`, `sources/Cansat_environmental_tests_r1.3.pdf`, `sources/CanSat_Competition_Guidelines_2025_2026_ESERO.pdf` | CanSat pressure/temperature telemetry and hot/vibration/drop testing practice |
| Ranđelović et al. 2021 low-cost altitude sensor paper | `sources/Randjelovic_2021_low_cost_altitude_sensors.pdf` | literature on low-cost barometric altitude sensors, including BME280 |

## Search records

- `searches/bme280_datasheet_search.json`
- `searches/wmo_no8_search.json`
- `searches/iso7726_search.json`
- `searches/icao_standard_atmosphere_search.json`
- `searches/i2c_um10204_search.json`
- `searches/gum_uncertainty_search.json`
- `searches/nist_statistics_search.json`
- `searches/cansat_sensor_testing_search.json`
- `searches/semantic_low_cost_bme280_weather_validation.json`
- `searches/semantic_pressure_altitude_validation.json`

Some `.diagnostics/` folders in `sources/` document failed or low-confidence HTTP extraction attempts and are retained for reproducibility.
