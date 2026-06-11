# PDM v1.0 test-reference corpus

This folder contains the web search records and saved source artifacts used to define the PDM v1.0 test plan.

## Search records

Reproducible Brave Search JSON files are in `search/`.

## Saved sources

| ID | Local artifact | Source URL | Use in test plan |
| --- | --- | --- | --- |
| R1 | `sources/esa_what_is_a_cansat.md` | https://www.esa.int/Education/CanSat/What_is_a_CanSat | CanSat size/mass, reusable recovery system, parachute connection strength, 8-11 m/s descent guidance. |
| R2 | `sources/andoya_cansat_competition_requirements.md` | https://learn.andoyaspace.no/docs/cansat/cansat_competition_requirements/ | CanSat recovery and descent-rate requirements. |
| R3 | `sources/andoya_parachute_design.md` | https://learn.andoyaspace.no/docs/cansat/recovery_system/parachute/ | Parachute sizing, drag equation, test guidance, 8-11 m/s descent range. |
| R4 | `sources/esero_cansat_parachute_design.pdf` | https://esero.kopernik.org.pl/wp-content/uploads/2019/06/CanSat_Parachute_Design.pdf | ESA/ESERO parachute design and drop-test teaching guide. |
| R5 | `sources/cansat_mission_guide_2024a.pdf` | https://www.cansatcompetition.com/docs/CanSat_Mission_Guide_2024a.pdf | CanSat drop, shock, vibration, thermal/vacuum test examples; 30 g shock drop-test rationale. |
| R6 | `sources/ecss_e_st_10_02c_rev1_verification.pdf` | https://ecss.nl/wp-content/uploads/2017/02/ECSS-E-ST-10-02C-Rev.1-DIR2(2February2017).pdf | Verification planning, methods, qualification/acceptance stages, reports. |
| R7 | `sources/ecss_e_st_10_03c_testing_2012.pdf` | https://ecss.nl/wp-content/uploads/standards/ecss-e/ECSS-E-ST-10-03C1June2012.pdf | Qualification, acceptance, protoflight testing approach; functional tests before/after environmental tests. |
| R8 | `sources/nxp_um10204_i2c_bus_spec_rev03_umich_copy.pdf` | https://web.eecs.umich.edu/~prabal/teaching/resources/eecs373/NXP-I2C-Specification.pdf | NXP UM10204 I2C-bus specification copy; bus rate, open-drain, clock stretching, bus recovery. |
| R9 | `sources/sparkfun_tdk_icm20948_datasheet_v1_3.pdf` | https://cdn.sparkfun.com/assets/7/f/e/c/d/DS-000189-ICM-20948-v1.3.pdf | ICM-20948 datasheet copy; sensor ranges, I2C/SPI rates, voltage ranges, self-test. |
| R10 | `sources/tdk_invensense_icm20948_product_page.md` | https://invensense.tdk.com/products/motion-tracking/9-axis/icm-20948/ | Current TDK product page for ICM-20948. |
| R11 | `sources/realdigital_servo_pwm.md` | https://www.realdigital.org/doc/f3d22b093e544b3821b8bcddeea64abf | Servo PWM timing: 20 ms / 50 Hz, 1-2 ms pulses, 1.5 ms center. |
| R12 | `sources/nist_tn2119_instrument_performance_confidence_intervals.pdf` | https://nvlpubs.nist.gov/nistpubs/TechnicalNotes/NIST.TN.2119.pdf | Binomial confidence intervals and bounds for pass/fail performance. |
| R13 | `sources/reliasoft_cumulative_binomial_rdt.md` | https://help.reliasoft.com/articles/content/hotwire/issue118/relbasics118.htm | Reliability demonstration test design with cumulative binomial and zero-failure tests. |
| R14 | `sources/mil_std_810h.pdf` | https://cvgstrategy.com/wp-content/uploads/2019/03/MIL-STD-810H.pdf | Environmental tailoring reference. |
| R15 | `sources/mil_std_810h_method_514_8_vibration.pdf` | https://cvgstrategy.com/wp-content/uploads/2019/08/MIL-STD-810H-Method-514.8-Vibration.pdf | Vibration test tailoring and functional/endurance concepts. |
| R16 | `sources/mil_std_810h_method_516_8_shock.pdf` | https://cvgstrategy.com/wp-content/uploads/2019/08/MIL-STD-810H-Method-516.8-Shock.pdf | Shock, transit drop, functional shock, bench handling concepts. |

Notes:
- The current NXP direct `UM10204.pdf` URL returned HTTP 404 in this environment, so the saved I2C artifact is a university-hosted copy of the NXP UM10204 document discovered during search.
- The current TDK direct datasheet download was not statically retrievable; the saved corpus includes the current product page and a SparkFun-hosted copy of the TDK/InvenSense ICM-20948 datasheet.
