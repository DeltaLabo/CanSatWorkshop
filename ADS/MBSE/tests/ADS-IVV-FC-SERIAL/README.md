# ADS-IVV-FC-SERIAL — Serial0 development logging verification definition

**IADT method:** Demonstration/Testing with supporting Analysis.

**IVV source category:** functional chain / scenario, with linked delivery, freshness/validity, and fault-hardening constraints.

**Selected SSIV/development scope:** all ADS MBSE versions currently present: `v0.1`, `v0.2`, `v0.3`, and `v1.0`. Serial0 logging verification executes for `v0.1` and `v0.2`; `v0.3` is an explicit PCB-only N/A branch; `v1.0` is an explicit N/A branch for ADS Serial0 because ADS delivery is modeled through OBCC `Pointers` / `Returns` instead.

**Traceability targets:** `ADS-CAP-DELIVERY` to the development PC, feared events `ADS-FE-CORRUPT-MEASUREMENT` and `ADS-FE-STUCK-LOOP`, and the related validity/freshness assumptions for logged init-state and measurement records.

**References cited in diagrams:** IVV, NASA-SE, SW/statistics references, ESA-CANSAT references, and the ADS MBSE IVV plan `../README.md`. No external research was performed for this definition.

**Selected activity for this package:** `ADS-IVV-FC-SERIAL`, the pending Serial0 logging functional-chain coverage gap from the ADS-wide test plan.

## Source-view copies

All D2/PNG views for the selected all-version scope were copied under `source_views/` so reports can reference a stable test-definition package:

- `source_views/v0.1/` — physical, logical, allocation, GPS position chain, Serial logging chain.
- `source_views/v0.2/` — physical, logical, allocation, GPS, angular velocity, attitude estimation, peripheral initialisation, Serial logging chains.
- `source_views/v0.3/` — physical PCB delivery view; used only for N/A rationale.
- `source_views/v1.0/` — physical, logical, allocation, GPS, angular velocity, attitude estimation, peripheral initialisation chains; used to confirm no ADS Serial0 chain and redirect delivery verification to OBCC.

## Test-definition views

| View | Purpose |
|---|---|
| `definition_views/ADS_IVV_FC_SERIAL_view1_source_chain_inventory.d2/png` | Serial0 source-chain inventory for `v0.1` and `v0.2`, with explicit `v0.3` and `v1.0` N/A rationale and traceability. |
| `definition_views/ADS_IVV_FC_SERIAL_view2_physical_logical_test_setup.d2/png` | Physical/logical test setup with selected UUT, development PC serial logger/parser, USB-C cable under test, power supply, timebase/ambient monitor, optional sensor/fault harness, analysis script, PLs/CEs, and setup constraints. |
| `definition_views/ADS_IVV_FC_SERIAL_view3_verification_functional_allocation.d2/png` | Verification-only functional allocation to the selected ADS UUT, human test conductor, PC serial logger/parser, power supply, timebase, GPS/IMU stimulus/fault harness, ambient monitor, analysis script, and quality/configuration authority. |
| `definition_views/ADS_IVV_FC_SERIAL_view4_serial_logging_sequence.d2/png` | Functional-chain style verification sequence covering nominal init/measurement logging, parsing, unavailable/stale/malformed/missing-field fault cases, analysis, and N/A branching. |
| `definition_views/ADS_IVV_FC_SERIAL_view5_evidence_traceability.d2/png` | Evidence and traceability interfaces for source views, firmware/configuration, Serial0 schema, raw logs, parser outputs, analysis, reports, deviations, waivers, limitations, and retest status. |

## Controlled local Serial0 baseline

`ADS-BLK-006` is no longer blocked by a missing local schema/parser definition. The controlled v0.1/v0.2 baseline for execution planning is:

- Schema: `../schemas/ads_serial0_v0_1_v0_2.schema.json` (`ads.serial0.v1`).
- Parser: `../tools/parse_ads_serial0.py` (`ads.serial0.parser.v1`).
- Canonical format: UTF-8 JSON Lines over Serial0 USB CDC/UART to the PC logger; default `115200` baud, `8N1` framing where applicable.
- Legacy output: legacy firmware logs must conform directly or be transformed by a documented adapter; actual logs/reports shall identify firmware commit/build and adapter ID/revision (`none` for native canonical output).
- Campaign count: a 10 min mission-window campaign at 5 Hz expects `3000` measurement records. Shorter serial functional checks compute expected records as `configured_duration_s * nominal_rate_hz` and may enforce that count with the parser only when duration/rate are predeclared.

Execution remains pending; this baseline only removes the undefined schema/parser blocker for future Serial0 verdicts.

## Model elements covered

- `v0.1` and `v0.2` Serial logging chains.
- External Actor `PC` and function `Monitor serial port`.
- `XIAO ESP32` to `PC` USB-C physical link.
- `Log via Serial0`, `Collect peripheral init states`, and `Collect measurements`.
- `v0.1` init state: `Get UBX-G7020-KT init state`.
- `v0.2` init states: `Get UBX-G7020-KT init state` and `Get ICM20948 init state`.
- Measurement content produced by modeled GPS, IMU, and attitude chains where present; the controlled Serial0 field schema is `../schemas/ads_serial0_v0_1_v0_2.schema.json`.

## Version coverage and pass/fail rules

| Version | Serial0-chain coverage | Pass/fail constraints |
|---|---|---|
| `v0.1` | Serial logging chain: `Get UBX-G7020-KT init state` → `Collect peripheral init states` → `Log via Serial0`, and `Collect measurements` → `Log via Serial0`; PC `Monitor serial port` and XIAO-PC USB-C are supporting model elements. | Pass if the development PC receives parseable init-state and measurement records matching `../schemas/ads_serial0_v0_1_v0_2.schema.json`, including UBX init state and GPS latitude/longitude/fix/freshness fields or explicit unavailable/stale/error markers. Fail if records are missing/malformed without detection, stale/unavailable/error data are hidden as valid, the loop hangs/unrecovers, or USB-C/Serial0 evidence is absent. Execution remains pending. |
| `v0.2` | Serial logging chain: UBX and ICM20948 init states → `Collect peripheral init states` → `Log via Serial0`, and `Collect measurements` → `Log via Serial0`; PC `Monitor serial port` and XIAO-PC USB-C are supporting model elements. | Same as `v0.1`, plus ICM20948 init state and modeled GPS/IMU/attitude measurement fields in the local schema (angular-rate, acceleration, magnetic-field, and PRY fields) or explicit unavailable/stale/error markers must be parseable. Fault cases shall include unavailable/stale/malformed/missing GPS/IMU/init fields and shall not create false-valid records. Execution remains pending. |
| `v0.3` | N/A. Source package is a PV1-only PCB delivery model with no PC actor, no USB-C link, no logical components, no component exchanges, no allocations, and no Serial0 logging chain. | Pass/N/A if the copied `v0.3` source view is reviewed and the absence of runtime Serial0 behavior is recorded. Fail if Serial0 behavior is claimed from the PCB-only model. |
| `v1.0` | N/A for ADS Serial0. Source package contains ADS/OBCC integrated delivery through `Pointers` and `Returns`, but no ADS Serial0 chain or development PC consumer. | Pass/N/A if the copied `v1.0` source views are reviewed and the no-Serial0 rationale is recorded. Do not use this activity to verify `v1.0` measurement delivery; use or define the OBCC delivery verification activity instead. |

## Pass/fail constraint set

| Constraint ID | Applies to | Criterion |
|---|---|---|
| `ADS-IVV-FC-SERIAL-C-SCHEMA` | `v0.1`/`v0.2` execution prerequisite | Use local schema `../schemas/ads_serial0_v0_1_v0_2.schema.json` and parser `../tools/parse_ads_serial0.py`. The baseline declares Serial0 interface/framing, expected fields, unavailable/stale/error marker vocabulary, parser version, and 10 min / 5 Hz expected count rule. |
| `ADS-IVV-FC-SERIAL-C-PARSE` | `v0.1`/`v0.2` | PC serial logger/parser receives and parses init-state and measurement records; malformed or missing records are detected and recorded. |
| `ADS-IVV-FC-SERIAL-C-FIELDS` | `v0.1`/`v0.2` | Every modeled field covered by the declared schema is present or has an explicit unavailable/stale/error marker; Serial0 output does not silently replace invalid data with valid-looking values. |
| `ADS-IVV-FC-SERIAL-C-FAULTS` | `v0.1`/`v0.2` | Unavailable, stale, malformed, and missing GPS/IMU/init-state cases are visible in the logs/parser results and do not cause unrecovered loop blockage. |
| `ADS-IVV-FC-SERIAL-C-STATS` | `v0.1`/`v0.2` when claimed | Frame/PDR statistics are pass/fail only when expected frame count, campaign size/duration, confidence method, and threshold are declared. The baseline count is 3000 measurement records for a 10 min campaign at 5 Hz; shorter checks use configured duration × nominal rate. Otherwise report frame counts and gaps as characterization. |
| `ADS-IVV-FC-SERIAL-C-NA` | `v0.3`/`v1.0` | N/A rationale is recorded from copied source views; no runtime Serial0 claim is credited. |

## Viewpoints

- **Statistical significance:** no PDR/frame-delivery claim is made by default. If a formal binary/PDR claim is added, use exact one-sided binomial / Clopper-Pearson confidence bounds and record successes, trials, confidence, and required delivery probability. Repeated frames on one article are performance evidence, not independent reliability trials unless justified.
- **Fault hardening:** unavailable sensor/init state, stale value, malformed field, missing field, corrupt value accepted as valid, PC parser mismatch, USB-C disconnect/reconnect, serial-port reset, and firmware loop blockage.
- **Configuration control:** each report identifies ADS version, copied source-view package, hardware revision/BOM, firmware commit/build, UUT serial, PC OS/tool versions, parser/schema version, USB-C cable/port, equipment IDs/calibration status, operator, and deviations.
- **Environmental context:** human test conductor reads/records ambient monitor output before repetitions; reports include temperature/humidity, power/current limit, timebase uncertainty, and any unsafe or out-of-range setup condition.

## Required execution conditions

- Select and record ADS version/SSIV, model baseline, hardware revision, firmware commit/build, UUT identifier, and source-view copy.
- Use the controlled Serial0 schema/parser baseline before pass/fail execution: `../schemas/ads_serial0_v0_1_v0_2.schema.json` and `../tools/parse_ads_serial0.py`.
- Configure development PC serial port, logger, parser, timestamp source, storage path, and tool versions; record firmware commit/build and any legacy-output adapter ID/revision in the log/report.
- Connect the modeled USB-C cable/port and record its identity; apply controlled power using the modeled power supply/battery simulator.
- Read and record ambient temperature/humidity and timebase uncertainty before repetitions.
- Execute nominal boot/init and measurement logging, then execute or disposition unavailable, stale, malformed, and missing-field fault cases using the optional GPS/IMU stimulus/fault harness or equivalent controlled method.
- Preserve raw Serial0 bytes/lines, parsed outputs, parser logs, fault markers, ambient/power/timebase records, and analysis scripts/settings.

## Expected report locations

Reports should reference this modeled definition and store evidence under:

- `../results/ADS-IVV-FC-SERIAL/v0.1/`
- `../results/ADS-IVV-FC-SERIAL/v0.2/`
- `../results/ADS-IVV-FC-SERIAL/v0.3/`
- `../results/ADS-IVV-FC-SERIAL/v1.0/`

Each report shall identify referenced model views/elements, selected SSIV/version, as-tested configuration, Serial0 schema/parser version, raw evidence, analysis settings, actual environmental conditions, pass/fail/Blocked/Limited or N/A rationale, deviations, anomalies, waivers, limitations, and retest status.

## Assumptions and gaps

- Controlled SSIV/current version is inferred from folders; no separate SSIV document was found in the reviewed files.
- Source D2 views model `Log via Serial0` and PC `Monitor serial port`; local files now control the Serial0 schema, default baud, line format, marker vocabulary, parser, expected frame count, and campaign-size rule for v0.1/v0.2 execution planning.
- `Measurements [LoRa Frame]` is treated as the modeled measurement record source for `v0.1`/`v0.2`; canonical field names are defined in `../schemas/ads_serial0_v0_1_v0_2.schema.json`.
- No formal PDR/frame-delivery statistical claim is made until an execution procedure declares duration, threshold, confidence method, and whether the parser count check is verdict-bearing.
- `v0.3` and `v1.0` are intentionally not ignored: both are modeled/documented as N/A for this activity.

## Status

Modeled definition ready for review. Execution remains pending. The local Serial0 schema/parser baseline is declared, so future v0.1/v0.2 Serial0 verdicts are no longer blocked by an undefined schema/parser.
