# ISSUE-002 — Resolve SYS-BLK-003 hardware naming/configuration drift

## Context

The project selected the following canonical as-built hardware names for the affected configuration freeze:

- Radio: `RFM96W`
- IMU: `ICM20948`
- Atmospheric/environmental sensor: `BME280`

This issue resolves `SYS-BLK-003` by making active project docs, MBSE views, test definitions, BOM entries, and source sketches use only those canonical names for these functions.

Do not change unrelated hardware. Do not claim unrelated blockers are closed.

## Scope and important distinction

Update controlled project artifacts. External captured reference/search/source artifacts may remain unchanged if they are quotes/downloads from outside sources, but active docs/models/source should not keep legacy names as project choices.

Legacy/drift terms to remove from controlled project artifacts:

- `RFM95W` / `rfm95w` → `RFM96W` / `rfm96w`
- `MPU6050` / `mpu6050` → `ICM20948` / suitable `icm20948` identifier
- `BMP280` / `bmp280` → `BME280` / suitable `bme280` identifier
- `ICM-20948` should become `ICM20948` in project-controlled naming (library constants like `ICM20948_*` are already fine).

## Likely files/directories to inspect and update

- `PM&SE/BOM/BOM.csv`
- `OBCC/LoRa_Frame.md`
- `PM&SE/CON-003_Candidates_and_Definition_Blockers.md`
- `PM&SE/MBSE_Test_Plan_Assessment.md`
- `OBCC/MBSE/v1.0/` and `OBCC/MBSE/tests/` README/D2/source-view copies
- `DPS/MBSE/v0.2/`, `DPS/MBSE/v1.0/`, and `DPS/MBSE/tests/` README/D2/baseline copies
- Active sketches that still reference old sensors, especially:
  - `OBCC/main/main.ino`
  - `DPS/3dmodel/3dmodel.ino`
  - `DPS/3dmodel/3dmodel.html`
  - `AMS/COD_V0.1_AMS.ino`
  - `ADS/Obtenerdatos_v2.1/Obtenerdatos_v2.1.ino`
  - OBCC legacy test sketches if they are still tracked as project examples rather than immutable external references.
- Capella XML/AIRD files under `PM&SE/capella/` only if straightforward text replacement is safe; do not corrupt XML.

## Required changes

1. Update the BOM row for radio from `RFM95W` to `RFM96W`; update `ICM-20948` to `ICM20948`.
2. Update OBCC/DPS MBSE/readme/test text and D2 labels from `RFM95W` to `RFM96W`.
3. Update OBCC/DPS/AMS/ADS active code and docs from `MPU6050`/`BMP280` to `ICM20948`/`BME280` where they describe the active hardware.
   - For BME280 code, `Adafruit_BME280` has the same `readTemperature`, `readPressure`, and `readAltitude` methods used by BMP280 code.
   - For ICM20948 code, prefer existing project usage of `ICM20948_WE` from ADS sketches as a local pattern; if a full firmware port is too large, at minimum remove project-facing legacy naming and leave a clear TODO-free canonical placeholder rather than claiming MPU6050 active hardware.
4. Update PM&SE closure records:
   - `SYS-BLK-003` should be marked closed/resolved with selected as-built configuration `RFM96W`, `ICM20948`, `BME280`.
   - Hardware naming gap language in `MBSE_Test_Plan_Assessment.md` should no longer say the configuration is not frozen; it may say the selected configuration is now frozen.
5. Do not create new blockers from the rename. If there are files you intentionally exclude as external references, list them in your final response.

## D2 rendering

For every `.d2` you change that has a sibling `.png`, regenerate the PNG with:

```bash
d2 --layout=elk \
  --elk-padding="[top=20,left=20,bottom=20,right=20]" \
  --elk-nodeNodeBetweenLayers=30 \
  --elk-edgeNodeBetweenLayers=20 \
  path/to/file.d2 path/to/file.png
```

## Acceptance checks

Run and report results. The first command should return no hits in controlled active artifacts except external references you explicitly justify.

```bash
rg -n "RFM95W|MPU6050|BMP280|ICM-20948|rfm95w|mpu6050|bmp280" \
  README.md ADS AMS DPS OBCC PDM 'PDS&ESS' 'PM&SE' 'S&A' Workshop \
  --glob '!*.pdf' --glob '!*.png' --glob '!*.jpg' --glob '!*.xlsx' --glob '!*.pptx' --glob '!*.synctex.gz' \
  --glob '!**/references/**'

rg -n "RFM96W|ICM20948|BME280" PM\&SE/BOM/BOM.csv OBCC/LoRa_Frame.md OBCC/MBSE/v1.0/README.md DPS/MBSE/tests/README.md AMS/README.md ADS/MBSE/tests/README.md
```

## Commit instructions

- Do not push.
- Stage only files relevant to this issue.
- Commit with a message like: `Freeze hardware naming configuration`.
- Final response: summarize changed files, validation commands, commit hash, and any excluded external-reference artifacts.
