# Reference corpus for PDS & ESS tests

This folder contains the reproducible search records and retrieved reference sources used to draft `../README.md`.

## Search records

Saved JSON search records are in `searches/`:

- `cansat-power-battery-test-plan.json`
- `nasa-gevs-smallsat-power-env-test.json`
- `liion-safety-standards.json`
- `ina219-i2c-measurement-testing.json`
- `i2c-um10204-timeout-testing.json`
- `ipc-2152-pcb-current-testing.json`
- `un-38-3-lithium-battery-official.json`
- `cansat-competition-requirements-battery-safety.json`
- academic-search records: `semantic-*.json`, `arxiv-cubesat-eps-battery-testing.json`

## Retrieved sources

| ID | File | Use in test plan |
|---|---|---|
| R1 | `sources/nasa-gsfc-std-7000-gevs.md`, `sources/gsfc-std-7000b-gevs.pdf` | Tailorable environmental verification baseline for components/subsystems. |
| R2 | `sources/esa-what-is-cansat.md`, `sources/esa-cansat-guidelines-23-24.pdf` | CanSat constraints: safe materials, battery power, accessible master switch, 4 h baseline operation, 20 g survivability. |
| R3 | `sources/cansat-competition-mission-guide-2024.pdf` | Practical CanSat environmental tests: 30 g drop, 60 °C thermal exposure, 0–233 Hz vibration. |
| R4 | `sources/intertek-iec-62133-li-ion-battery-safety.md` | IEC 62133 safety themes for rechargeable lithium batteries: overcharge, over-discharge, short circuit, thermal runaway, documentation. |
| R5 | `sources/un-manual-38-3-prba-mirror.pdf`, `sources/tuvsud-un-dot-38-3-lithium-battery-testing.pdf` | UN/DOT 38.3 lithium battery transport test classes: altitude, thermal, vibration, shock, short-circuit, overcharge, forced discharge. |
| R6 | `sources/nasa-li-ion-battery-space-guidelines.pdf`, `sources/aerospace-tor-2013-00295-li-ion-power-subsystems.pdf` | Space-use Li-ion guidance and system-level protection/verification rationale. |
| R7 | `sources/review-battery-technology-in-cubesats.pdf`, `sources/smallsat-battery-certification-testbed.pdf` | CubeSat/small-satellite battery literature and testbed rationale. |
| R8 | `sources/ipc-2152-standard-toc.pdf`, `sources/sierra-ipc-2152-pcb-trace-optimization.md` | PCB trace current capacity, temperature rise, and thermal verification. |
| R9 | `sources/ti-ina219-product.md`, `sources/ti-ina219-datasheet.pdf` | INA219 measurement range, I2C/SMBus interface, 0.5% max accuracy for INA219B, conversion time, 28 ms interface timeout. |
| R10 | `sources/nxp-um10204-i2c-spec-pololu-mirror.pdf` | I2C bus speed classes, clock stretching, timing, and bus behavior. |

Some attempted official URLs returned HTTP 403/404; their diagnostics are retained under `sources/*.diagnostics/` for provenance.
