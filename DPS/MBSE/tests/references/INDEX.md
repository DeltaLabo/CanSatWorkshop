# DPS v1.0 test reference corpus

This folder contains the search outputs and fetched source artifacts used to prepare `../README.md` for the Capella/D2 Physical Architecture views in `DPS/MBSE/v1.0/`.

## Search records

Saved JSON search results are in [`searches/`](./searches/):

- `ecss-testing.json` — ECSS space-engineering testing standard.
- `software-testing-29119.json`, `iso-29119-2.json` — ISO/IEC/IEEE software test process and documentation standards.
- `binomial-statistics.json` — NIST/SEMATECH statistical methods for binomial/proportion tests and sample size.
- `etsi-en-300-220.json`, `the-things-network-eu868.json` — short-range-device radio and LoRa regional operating constraints.
- `rfm95w-datasheet.json`, `semtech-an1200-22.json` — RFM95W/SX1276/LoRa radio references.
- `cansat-telemetry-testing.json`, `andoya-cansat-telemetry-system.json` — CanSat telemetry, ground-station, and radio-test references.
- `lora-path-loss-pdr.json`, `semantic-lora-path-loss-exact.json`, `semantic-lora-pdr.json`, `arxiv-lora-path-loss*.json`, `google-scholar-lora-path-loss.json` — LoRa path-loss/PDR literature searches. Some academic API searches returned zero or broad/ambiguous results and are retained for reproducibility.

## Retrieved sources

### Test process and documentation

- **R1** — [`sources/ecss-e-st-10-03c-rev1-testing.md`](./sources/ecss-e-st-10-03c-rev1-testing.md) and [`sources/ecss-e-st-10-03c-rev1-testing.pdf`](./sources/ecss-e-st-10-03c-rev1-testing.pdf): ECSS-E-ST-10-03C Rev.1, Space engineering — Testing.
- **R2** — [`sources/iso-iec-ieee-29119-2-test-processes.md`](./sources/iso-iec-ieee-29119-2-test-processes.md): ISO/IEC/IEEE 29119-2:2021 official abstract for software test processes.
- **R3** — [`sources/iso-iec-ieee-29119-3-test-documentation.md`](./sources/iso-iec-ieee-29119-3-test-documentation.md): ISO/IEC/IEEE 29119-3:2021 official abstract for test documentation templates.

### Statistics

- **R4** — [`sources/nist-prc24-proportion-defectives.md`](./sources/nist-prc24-proportion-defectives.md): NIST/SEMATECH guidance for testing a proportion defective.
- **R5** — [`sources/nist-prc242-sample-sizes.md`](./sources/nist-prc242-sample-sizes.md): NIST/SEMATECH sample-size guidance for proportion tests.

### Radio and regulatory references

- **R6** — [`sources/etsi-en-300-220-2-v3-3-1.pdf`](./sources/etsi-en-300-220-2-v3-3-1.pdf): ETSI EN 300 220-2 V3.3.1 for SRD equipment.
- **R7** — [`sources/the-things-network-eu868.md`](./sources/the-things-network-eu868.md) and [`sources/the-things-network-duty-cycle.md`](./sources/the-things-network-duty-cycle.md): EU863-870 LoRa regional parameters, EIRP, and duty-cycle notes.
- **R8** — [`sources/hoperf-rfm95w-product-page.md`](./sources/hoperf-rfm95w-product-page.md) and [`sources/hoperf-rfm95w-v2-0-datasheet.pdf`](./sources/hoperf-rfm95w-v2-0-datasheet.pdf): HopeRF RFM95W module information and datasheet.
- **R9** — [`sources/semtech-sx1276-product-page.md`](./sources/semtech-sx1276-product-page.md): Semtech SX1276 feature summary.
- **R10** — [`sources/semtech-an1200-22-lora-modulation-basics-mirror.pdf`](./sources/semtech-an1200-22-lora-modulation-basics-mirror.pdf) plus [`sources/semtech-an1200-22-find-documentation.md`](./sources/semtech-an1200-22-find-documentation.md): Semtech AN1200.22 LoRa modulation basics; Semtech's historical direct URL redirects to a documentation search page, so a public mirror PDF is retained.

### CanSat and LoRa telemetry literature

- **R11** — [`sources/andoya-cansat-telemetry-system.md`](./sources/andoya-cansat-telemetry-system.md): Andøya CanSat telemetry, RFM96/RFM9x radio, SPI, ground-station, antenna, and radio-test guidance.
- **R12** — [`sources/andoya-testing-and-using-rfm96-radio.md`](./sources/andoya-testing-and-using-rfm96-radio.md): Andøya RFM96 send/receive test procedure.
- **R13** — [`sources/cansat-mission-guide-2025e.pdf`](./sources/cansat-mission-guide-2025e.pdf): CanSat competition mission guide with telemetry, ground-station, and operational readiness expectations.
- **R14** — [`sources/callebaut-lora-p2p-path-loss-2020.pdf`](./sources/callebaut-lora-p2p-path-loss-2020.pdf) and [`sources/ieee-callebaut-lora-p2p-path-loss-landing.md`](./sources/ieee-callebaut-lora-p2p-path-loss-landing.md): Callebaut & Van der Perre, *Characterization of LoRa Point-to-Point Path Loss*, IEEE Internet of Things Journal, 2020.
- **R15** — [`sources/rademacher-urban-lora-path-loss-2021-arxiv.pdf`](./sources/rademacher-urban-lora-path-loss-2021-arxiv.pdf): Rademacher et al., *Path Loss in Urban LoRa Networks: A Large-Scale Measurement Study*, 2021.

Diagnostics from low-confidence or redirected fetches are preserved beside the corresponding source artifacts.
