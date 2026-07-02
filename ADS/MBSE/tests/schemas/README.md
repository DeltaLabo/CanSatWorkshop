# ADS Serial0 schema baselines

This folder contains local controlled evidence schemas for ADS MBSE test execution.

## `ads_serial0_v0_1_v0_2.schema.json`

Controlled baseline for `ADS-IVV-FC-SERIAL` v0.1/v0.2 Serial0 development logging.

- **Schema version:** `ads.serial0.v1`
- **Parser baseline:** `ADS/MBSE/tests/tools/parse_ads_serial0.py` (`ads.serial0.parser.v1`)
- **Interface:** Serial0 over USB CDC/UART from ADS XIAO ESP32 to the PC logger.
- **Default serial settings:** `115200` baud, `8N1` framing where applicable.
- **Encoding/framing:** UTF-8 JSON Lines; one complete JSON object per newline.
- **Legacy output rule:** legacy firmware logs must either already conform to this JSON Lines format or be transformed by a documented adapter. The adapter ID/revision is recorded in the canonical `init` record as `adapter_id` (`none` for native output).

## Canonical record envelope

Every line is a JSON object with these required envelope fields:

| Field | Meaning |
|---|---|
| `schema_version` | Must be `ads.serial0.v1`. |
| `ads_version` | `v0.1` or `v0.2`. |
| `sample_id` | Non-negative, strictly increasing record sequence unless a procedure explicitly allows otherwise. |
| `timestamp_ms` | Non-negative monotonic milliseconds from the declared run epoch. |
| `record_type` | `init`, `measurement`, `fault`, or `heartbeat`. |
| `validity` | `valid`, `degraded`, `invalid`, or `unknown`. |
| `status` | `ok`, `degraded`, `fault`, or `unavailable`. |
| `stale` | Boolean top-level freshness indicator. |
| `field_markers` | Object mapping controlled field names to marker vocabulary values. Use `{}` when all present fields are valid/fresh. |

`init` records also carry firmware/configuration identity: `firmware_commit`, `firmware_build`, `adapter_id`, `serial0_baud`, `serial0_framing`, and `gps_init_status`; v0.2 also requires `imu_init_status`.

## Measurement field list

v0.1 measurement records require:

- `gps_latitude_deg`
- `gps_longitude_deg`
- `gps_fix_status`
- `gps_status`
- `gps_stale`
- `gps_age_ms`

v0.2 measurement records require all v0.1 fields plus:

- `imu_init_status`, `imu_status`, `imu_stale`, `imu_age_ms`
- `imu_gyro_dps_x`, `imu_gyro_dps_y`, `imu_gyro_dps_z`
- `imu_accel_mps2_x`, `imu_accel_mps2_y`, `imu_accel_mps2_z`
- `imu_mag_uT_x`, `imu_mag_uT_y`, `imu_mag_uT_z`
- `attitude_pitch_deg`, `attitude_roll_deg`, `attitude_yaw_deg`

If a required numeric value is unavailable, the JSON field remains present with `null` and a matching `field_markers` entry.

## Marker vocabulary

Allowed `field_markers` values are:

- `valid` — current valid data.
- `missing` — required field had no source value; the JSON field is still present with `null` or an unavailable value.
- `stale` — old value; not fresh.
- `error` — source error or corrupt value.
- `unavailable` — sensor/field unavailable for the current record.
- `not_applicable` — outside the selected record/version scope; not used for required measurement fields.

Stale/error/unavailable/missing markers must be reflected in the record envelope (`validity`, `status`, and/or `stale`) so invalid data are not hidden as valid.

## Campaign-size baseline

- Mission-window campaign: `10 min = 600 s` at `5 Hz` means `3000` expected measurement records for applicable v0.1/v0.2 Serial0 campaigns.
- Shorter functional checks compute `expected_measurement_records = configured_duration_s * nominal_rate_hz`; strict count checks require a predeclared duration/rate and an integer expected count.
- The parser can summarize counts without enforcing them, or enforce them with `--duration-s <seconds> --nominal-rate-hz 5 --require-expected-count`.
