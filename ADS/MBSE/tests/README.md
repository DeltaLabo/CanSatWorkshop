# ADS MBSE-wide verification corpus

This is the umbrella corpus for the ADS subsystem across all D2/Capella-style versions in `ADS/MBSE/`.

It complements the version-specific ADS v0.2 test corpus at `../v0.2/tests/README.md` by adding:

- a cross-version model inventory,
- a version lineage summary,
- a version-applicability matrix for ADS verification scenarios,
- PCB/backplane/manufacturing references needed by v0.3 and v1.0,
- references back to the existing GNSS/IMU/I2C/software/statistics corpus.

Project-wide IVV conventions, statistics, rate terminology, fault semantics, and artifact paths are defined in [`../../../PM&SE/IVV.md`](../../../PM&SE/IVV.md). In this corpus, `5 Hz` means the internal ADS acquisition/collection rate; v1.0 LoRa telemetry cadence is governed by OBCC/DPS and is separately modeled as `2 s` downlink cadence. Serial0 logging in ADS v0.1/v0.2 is an incremental-delivery/development interface, not a required v1.0 flight-operator path.

## Files

- `ADS_MBSE_CORPUS.md` — human-readable corpus and cross-version test scenario catalogue.
- `model_inventory.json` — machine-readable summary of versions, views, components, constraints, and chains.
- `references/README.md` — reference index for the umbrella corpus.
- `references/searches/*.json` — saved web-search records for PCB/workmanship references.
- `references/sources/*` — saved PCB/workmanship source artifacts and extracts.

## D2 source coverage

| Version | Views covered | ADS scope captured by the model |
|---|---:|---|
| v0.1 | 5 | GPS-only ADS on XIAO ESP32 with UART GPS, development Serial0 logging to PC, internal 5 Hz collection, `<5 m` position accuracy. |
| v0.2 | 8 | Adds ICM20948 IMU, I2C sensing, angular-rate and attitude chains, peripheral init, development Serial0 logging. |
| v0.3 | 1 | ADS PCB delivery only: UBX-G7020-KT, ICM20948, backplane connector, PCB footprints/traces, manufacturability note. |
| v1.0 | 7 | Integrated CanSat architecture: ADS Module sensor PCB, Backplane PCB, OBCC Module with XIAO ESP32-S3 running ADS Processing and OBCC collection. |

## Reference strategy

The ADS v0.2 reference pack already contains the GNSS, IMU, I2C, CanSat, NASA SE/GEVS, software-test, and statistical sources needed for most ADS behavioral verification:

- `../v0.2/tests/references/`

This umbrella corpus adds only the extra manufacturing/workmanship references needed for v0.3/v1.0 PCB/backplane verification.
