# DPS v0.1 test reference corpus

This folder contains the search outputs and fetched source artifacts used to prepare `../README.md`.

## Search records

Saved JSON search results are in [`searches/`](./searches/):

- `ecss-testing.json` — ECSS space engineering testing standard.
- `software-testing-29119.json` — ISO/IEC/IEEE software testing process/documentation standards.
- `binomial-statistics.json` — NIST/SEMATECH statistical methods for proportions and sample size.
- `etsi-en-300-220.json` — ETSI short-range-device radio standard for sub-GHz operation.
- `semtech-lora-link-budget.json`, `semtech-an1200-22.json`, `rfm95w-datasheet.json` — LoRa/SX1276/RFM95W radio references.
- `cansat-telemetry-testing.json`, `semantic-cansat-lora.json` — CanSat telemetry and ground-station references.
- `semantic-lora-pdr.json`, `semantic-lora-path-loss-exact.json`, `lora-path-loss-pdf.json` — LoRa range/PDR/path-loss literature.
- `arxiv-lora-pdr.json` — retained for reproducibility; broad query also returned unrelated LLM LoRA results and was not used as a primary source.

## Retrieved sources

### Test process and documentation

- [`sources/ecss-e-st-10-03c-rev1-testing.md`](./sources/ecss-e-st-10-03c-rev1-testing.md) and [`sources/ecss-e-st-10-03c-rev1-testing.pdf`](./sources/ecss-e-st-10-03c-rev1-testing.pdf) — ECSS-E-ST-10-03C Rev.1, Space engineering — Testing.
- [`sources/iso-iec-ieee-29119-2-test-processes.md`](./sources/iso-iec-ieee-29119-2-test-processes.md) — ISO official abstract for software test processes.
- [`sources/iso-iec-ieee-29119-3-test-documentation.md`](./sources/iso-iec-ieee-29119-3-test-documentation.md) — ISO official abstract for test documentation templates.

### Statistics

- [`sources/nist-prc24-proportion-defectives.md`](./sources/nist-prc24-proportion-defectives.md) — NIST/SEMATECH binomial proportion test guidance.
- [`sources/nist-prc242-sample-sizes.md`](./sources/nist-prc242-sample-sizes.md) — NIST/SEMATECH sample-size guidance for proportion tests.

### Radio and regulatory references

- [`sources/etsi-en-300-220-2-v3-3-1.pdf`](./sources/etsi-en-300-220-2-v3-3-1.pdf) — ETSI EN 300 220-2 V3.3.1 for SRD equipment.
- [`sources/the-things-network-eu868.md`](./sources/the-things-network-eu868.md) — EU863-870 operational notes, EIRP, data rates, duty cycle pointers.
- [`sources/semtech-sx1276-product-page.md`](./sources/semtech-sx1276-product-page.md) — Semtech SX1276 feature summary.
- [`sources/hoperf-rfm95w-product-page.md`](./sources/hoperf-rfm95w-product-page.md) and [`sources/hoperf-rfm95w-v2-0-datasheet.pdf`](./sources/hoperf-rfm95w-v2-0-datasheet.pdf) — HopeRF RFM95W radio module details.
- [`sources/semtech-an1200-22-lora-modulation-basics-mirror.pdf`](./sources/semtech-an1200-22-lora-modulation-basics-mirror.pdf) — Semtech AN1200.22 LoRa modulation basics, retrieved from a public mirror because Semtech's historical direct URL redirected to [`sources/semtech-an1200-22-find-documentation.md`](./sources/semtech-an1200-22-find-documentation.md).

### CanSat and LoRa telemetry literature

- [`sources/andoya-cansat-telemetry-system.md`](./sources/andoya-cansat-telemetry-system.md) — CanSat telemetry, RFM96/RFM9x radio use, ground station and radio testing guidance.
- [`sources/cansat-mission-guide-2025e.pdf`](./sources/cansat-mission-guide-2025e.pdf) — CanSat competition mission guide; ground station demonstration and communications readiness references.
- [`sources/callebaut-lora-p2p-path-loss-2020-scispace.pdf`](./sources/callebaut-lora-p2p-path-loss-2020-scispace.pdf) and [`sources/ieee-callebaut-lora-p2p-path-loss-landing.md`](./sources/ieee-callebaut-lora-p2p-path-loss-landing.md) — Callebaut & Van der Perre, "Characterization of LoRa Point-to-Point Path Loss: Measurement Campaigns and Modeling Considering Censored Data", IEEE Internet of Things Journal, 2020.

Diagnostic folders are preserved where the fetcher produced them for low-confidence or redirected pages.
