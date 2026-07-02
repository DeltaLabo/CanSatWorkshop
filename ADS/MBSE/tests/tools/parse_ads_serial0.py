#!/usr/bin/env python3
"""Validate ADS v0.1/v0.2 Serial0 canonical JSON Lines logs."""

from __future__ import annotations

import argparse
import json
import math
import sys
from collections import Counter
from pathlib import Path
from typing import Any, Dict, List, Optional, Tuple

PARSER_VERSION = "ads.serial0.parser.v1"
SCHEMA_VERSION = "ads.serial0.v1"
SUPPORTED_ADS_VERSIONS = {"v0.1", "v0.2"}
RECORD_TYPES = {"init", "measurement", "fault", "heartbeat"}
VALIDITY_VALUES = {"valid", "degraded", "invalid", "unknown"}
STATUS_VALUES = {"ok", "degraded", "fault", "unavailable"}
SENSOR_STATUS_VALUES = {
    "valid",
    "initializing",
    "no_fix",
    "stale",
    "error",
    "unavailable",
    "unknown",
}
GPS_FIX_VALUES = {"no_fix", "fix_2d", "fix_3d", "dgps", "rtk", "unknown", "unavailable", "error"}
FIELD_MARKERS = {"valid", "missing", "stale", "error", "unavailable", "not_applicable"}
NONVALID_MARKERS = {"missing", "stale", "error", "unavailable"}
NONOK_SENSOR_STATUS = {"initializing", "no_fix", "stale", "error", "unavailable", "unknown"}
BAD_GPS_FIX_STATUS = {"no_fix", "unknown", "unavailable", "error"}

ENVELOPE_FIELDS = [
    "schema_version",
    "ads_version",
    "sample_id",
    "timestamp_ms",
    "record_type",
    "validity",
    "status",
    "stale",
    "field_markers",
]

INIT_FIELDS_COMMON = [
    "firmware_commit",
    "firmware_build",
    "adapter_id",
    "serial0_baud",
    "serial0_framing",
    "gps_init_status",
]

MEASUREMENT_FIELDS_COMMON = [
    "gps_latitude_deg",
    "gps_longitude_deg",
    "gps_fix_status",
    "gps_status",
    "gps_stale",
    "gps_age_ms",
]

MEASUREMENT_FIELDS_V02 = [
    "imu_init_status",
    "imu_status",
    "imu_stale",
    "imu_age_ms",
    "imu_gyro_dps_x",
    "imu_gyro_dps_y",
    "imu_gyro_dps_z",
    "imu_accel_mps2_x",
    "imu_accel_mps2_y",
    "imu_accel_mps2_z",
    "imu_mag_uT_x",
    "imu_mag_uT_y",
    "imu_mag_uT_z",
    "attitude_pitch_deg",
    "attitude_roll_deg",
    "attitude_yaw_deg",
]

NUMERIC_OR_NULL_FIELDS = {
    "gps_latitude_deg",
    "gps_longitude_deg",
    "imu_gyro_dps_x",
    "imu_gyro_dps_y",
    "imu_gyro_dps_z",
    "imu_accel_mps2_x",
    "imu_accel_mps2_y",
    "imu_accel_mps2_z",
    "imu_mag_uT_x",
    "imu_mag_uT_y",
    "imu_mag_uT_z",
    "attitude_pitch_deg",
    "attitude_roll_deg",
    "attitude_yaw_deg",
}
INT_OR_NULL_FIELDS = {"gps_age_ms", "imu_age_ms"}
BOOLEAN_FIELDS = {"stale", "gps_stale", "imu_stale"}
STRING_FIELDS = {"firmware_commit", "firmware_build", "adapter_id", "serial0_port", "serial0_framing", "fault_code", "fault_message", "message"}
SENSOR_STATUS_FIELDS = {"gps_init_status", "imu_init_status", "gps_status", "imu_status"}

CONTROLLED_FIELD_MARKER_NAMES = {
    "gps_init_status",
    "imu_init_status",
    "gps_latitude_deg",
    "gps_longitude_deg",
    "gps_fix_status",
    "gps_status",
    "gps_stale",
    "gps_age_ms",
    "imu_status",
    "imu_stale",
    "imu_age_ms",
    "imu_gyro_dps_x",
    "imu_gyro_dps_y",
    "imu_gyro_dps_z",
    "imu_accel_mps2_x",
    "imu_accel_mps2_y",
    "imu_accel_mps2_z",
    "imu_mag_uT_x",
    "imu_mag_uT_y",
    "imu_mag_uT_z",
    "attitude_pitch_deg",
    "attitude_roll_deg",
    "attitude_yaw_deg",
    "firmware_commit",
    "firmware_build",
    "adapter_id",
    "fault_code",
}

ALLOWED_PROPERTIES = set(ENVELOPE_FIELDS) | CONTROLLED_FIELD_MARKER_NAMES | {
    "serial0_port",
    "serial0_baud",
    "serial0_framing",
    "fault_message",
    "message",
}


def is_int(value: Any) -> bool:
    return isinstance(value, int) and not isinstance(value, bool)


def is_number(value: Any) -> bool:
    return isinstance(value, (int, float)) and not isinstance(value, bool) and math.isfinite(value)


def reject_nonstandard_json_constant(value: str) -> None:
    raise ValueError(f"non-standard JSON constant {value!r}")


class ValidationState:
    def __init__(self) -> None:
        self.total_records = 0
        self.type_counts: Counter[str] = Counter()
        self.marker_counts: Counter[str] = Counter()
        self.status_counts: Counter[str] = Counter()
        self.missing_fields = 0
        self.sample_id_issues = 0
        self.timestamp_issues = 0
        self.issues: List[str] = []
        self.previous_sample_id: Optional[int] = None
        self.previous_timestamp_ms: Optional[int] = None

    def issue(self, line_no: int, message: str) -> None:
        self.issues.append(f"line {line_no}: {message}")

    def missing(self, line_no: int, field: str) -> None:
        self.missing_fields += 1
        self.issue(line_no, f"missing required field {field!r}")


def top_level_flagged(record: Dict[str, Any], marker: str) -> bool:
    validity = record.get("validity")
    status = record.get("status")
    stale = record.get("stale")
    if marker == "stale":
        return stale is True
    if marker in {"missing", "error", "unavailable"}:
        return validity != "valid" or status != "ok" or stale is True
    return True


def validate_value_type(record: Dict[str, Any], field: str, line_no: int, state: ValidationState) -> None:
    value = record.get(field)

    if field in NUMERIC_OR_NULL_FIELDS:
        if value is not None and not is_number(value):
            state.issue(line_no, f"field {field!r} must be a finite number or null")
        return

    if field in INT_OR_NULL_FIELDS:
        if value is not None and (not is_int(value) or value < 0):
            state.issue(line_no, f"field {field!r} must be a non-negative integer or null")
        return

    if field in BOOLEAN_FIELDS:
        if not isinstance(value, bool):
            state.issue(line_no, f"field {field!r} must be boolean")
        return

    if field in STRING_FIELDS:
        if not isinstance(value, str) or not value:
            state.issue(line_no, f"field {field!r} must be a non-empty string")
        return

    if field == "serial0_baud":
        if not is_int(value) or value <= 0:
            state.issue(line_no, "field 'serial0_baud' must be a positive integer")
        return

    if field in SENSOR_STATUS_FIELDS:
        if value not in SENSOR_STATUS_VALUES:
            state.issue(line_no, f"field {field!r} has unsupported sensor status {value!r}")
        return

    if field == "gps_fix_status":
        if value not in GPS_FIX_VALUES:
            state.issue(line_no, f"field 'gps_fix_status' has unsupported value {value!r}")
        return


def validate_required_fields(
    record: Dict[str, Any],
    fields: List[str],
    line_no: int,
    state: ValidationState,
    field_markers: Dict[str, Any],
) -> None:
    for field in fields:
        if field not in record:
            state.missing(line_no, field)
            continue

        validate_value_type(record, field, line_no, state)
        marker = field_markers.get(field, "valid")
        value = record.get(field)

        if value is None and marker not in NONVALID_MARKERS:
            state.issue(line_no, f"field {field!r} is null without missing/stale/error/unavailable marker")

        if marker in NONVALID_MARKERS and not top_level_flagged(record, marker):
            state.issue(line_no, f"field {field!r} has marker {marker!r} but record envelope is not flagged")


def validate_sensor_flags(record: Dict[str, Any], line_no: int, state: ValidationState) -> None:
    validity = record.get("validity")
    status = record.get("status")
    stale = record.get("stale")

    for field in ("gps_status", "imu_status", "gps_init_status", "imu_init_status"):
        value = record.get(field)
        if value in NONOK_SENSOR_STATUS:
            state.status_counts[value] += 1
            if value == "stale" and stale is not True:
                state.issue(line_no, f"{field!r} is stale but top-level 'stale' is false")
            if validity == "valid" and status == "ok" and stale is not True:
                state.issue(line_no, f"{field!r} is {value!r} but record envelope is valid/ok/fresh")

    gps_fix_status = record.get("gps_fix_status")
    if gps_fix_status in BAD_GPS_FIX_STATUS:
        state.status_counts[gps_fix_status] += 1
        if validity == "valid" and status == "ok" and stale is not True:
            state.issue(line_no, f"gps_fix_status is {gps_fix_status!r} but record envelope is valid/ok/fresh")

    for field in ("gps_stale", "imu_stale"):
        if record.get(field) is True and stale is not True:
            state.issue(line_no, f"{field!r} is true but top-level 'stale' is false")

    if stale is True and validity == "valid" and status == "ok":
        state.issue(line_no, "top-level 'stale' is true while validity/status remain valid/ok")


def validate_record(record: Dict[str, Any], line_no: int, state: ValidationState, allow_nonmonotonic_sample_id: bool) -> None:
    state.total_records += 1

    unknown_properties = sorted(set(record) - ALLOWED_PROPERTIES)
    for field in unknown_properties:
        state.issue(line_no, f"unknown field {field!r}; canonical schema has additionalProperties=false")

    for field in ENVELOPE_FIELDS:
        if field not in record:
            state.missing(line_no, field)

    schema_version = record.get("schema_version")
    ads_version = record.get("ads_version")
    record_type = record.get("record_type")
    validity = record.get("validity")
    status = record.get("status")
    stale = record.get("stale")

    if schema_version != SCHEMA_VERSION:
        state.issue(line_no, f"unsupported schema_version {schema_version!r}; expected {SCHEMA_VERSION!r}")
    if ads_version not in SUPPORTED_ADS_VERSIONS:
        state.issue(line_no, f"unsupported ads_version {ads_version!r}")
    if record_type not in RECORD_TYPES:
        state.issue(line_no, f"unsupported record_type {record_type!r}")
    else:
        state.type_counts[record_type] += 1
    if validity not in VALIDITY_VALUES:
        state.issue(line_no, f"unsupported validity {validity!r}")
    if status not in STATUS_VALUES:
        state.issue(line_no, f"unsupported status {status!r}")
    if not isinstance(stale, bool):
        state.issue(line_no, "field 'stale' must be boolean")

    sample_id = record.get("sample_id")
    if not is_int(sample_id) or sample_id < 0:
        state.issue(line_no, "field 'sample_id' must be a non-negative integer")
    elif not allow_nonmonotonic_sample_id:
        if state.previous_sample_id is not None and sample_id <= state.previous_sample_id:
            state.sample_id_issues += 1
            state.issue(
                line_no,
                f"duplicate/non-monotonic sample_id {sample_id}; previous was {state.previous_sample_id}",
            )
        state.previous_sample_id = sample_id

    timestamp_ms = record.get("timestamp_ms")
    if not is_int(timestamp_ms) or timestamp_ms < 0:
        state.issue(line_no, "field 'timestamp_ms' must be a non-negative integer")
    else:
        if state.previous_timestamp_ms is not None and timestamp_ms < state.previous_timestamp_ms:
            state.timestamp_issues += 1
            state.issue(
                line_no,
                f"timestamp reversal {timestamp_ms}; previous was {state.previous_timestamp_ms}",
            )
        state.previous_timestamp_ms = timestamp_ms

    field_markers = record.get("field_markers")
    if not isinstance(field_markers, dict):
        state.issue(line_no, "field 'field_markers' must be an object")
        field_markers = {}

    for field, marker in field_markers.items():
        if field not in CONTROLLED_FIELD_MARKER_NAMES:
            state.issue(line_no, f"field_markers contains unknown field {field!r}")
        if marker not in FIELD_MARKERS:
            state.issue(line_no, f"field_markers[{field!r}] has unsupported marker {marker!r}")
            continue
        if marker in NONVALID_MARKERS:
            state.marker_counts[marker] += 1
            if not top_level_flagged(record, marker):
                state.issue(line_no, f"field_markers[{field!r}]={marker!r} is not flagged by the record envelope")

    if record_type == "init":
        init_fields = INIT_FIELDS_COMMON.copy()
        if ads_version == "v0.2":
            init_fields.append("imu_init_status")
        validate_required_fields(record, init_fields, line_no, state, field_markers)

    if record_type == "measurement":
        measurement_fields = MEASUREMENT_FIELDS_COMMON.copy()
        if ads_version == "v0.2":
            measurement_fields.extend(MEASUREMENT_FIELDS_V02)
        validate_required_fields(record, measurement_fields, line_no, state, field_markers)

    if record_type == "fault":
        validate_required_fields(record, ["fault_code"], line_no, state, field_markers)
        if status == "ok" and validity == "valid":
            state.issue(line_no, "fault record has valid/ok envelope")

    validate_sensor_flags(record, line_no, state)


def parse_log(path: Path, allow_nonmonotonic_sample_id: bool) -> ValidationState:
    state = ValidationState()
    try:
        with path.open("r", encoding="utf-8", newline="") as handle:
            for line_no, raw_line in enumerate(handle, start=1):
                if raw_line.strip() == "":
                    state.issue(line_no, "blank line is not a valid JSON Lines record")
                    continue
                try:
                    record = json.loads(raw_line, parse_constant=reject_nonstandard_json_constant)
                except (json.JSONDecodeError, ValueError) as exc:
                    state.issue(line_no, f"unparseable JSON record: {exc}")
                    continue
                if not isinstance(record, dict):
                    state.issue(line_no, "JSON Lines record must be an object")
                    continue
                validate_record(record, line_no, state, allow_nonmonotonic_sample_id)
    except FileNotFoundError:
        state.issue(0, f"input log not found: {path}")
    except UnicodeDecodeError as exc:
        state.issue(0, f"input log is not strict UTF-8 text: {exc}")
    except OSError as exc:
        state.issue(0, f"could not read input log: {exc}")

    if state.total_records == 0 and not state.issues:
        state.issue(0, "input log contains no records")
    return state


def expected_measurement_count(duration_s: float, nominal_rate_hz: float) -> Tuple[Optional[int], Optional[str]]:
    if duration_s <= 0:
        return None, "duration must be positive"
    if nominal_rate_hz <= 0:
        return None, "nominal rate must be positive"
    expected_float = duration_s * nominal_rate_hz
    expected_int = round(expected_float)
    if not math.isclose(expected_float, expected_int, rel_tol=0.0, abs_tol=1e-9):
        return None, f"duration_s * nominal_rate_hz is not an integer ({expected_float})"
    return expected_int, None


def print_summary(
    path: Path,
    state: ValidationState,
    duration_s: Optional[float],
    nominal_rate_hz: float,
    expected_count: Optional[int],
) -> None:
    measurement_records = state.type_counts["measurement"]
    print(f"ADS Serial0 parser: {PARSER_VERSION}")
    print(f"schema_version: {SCHEMA_VERSION}")
    print(f"input: {path}")
    print(f"total_records: {state.total_records}")
    print(f"measurement_records: {measurement_records}")
    print(f"init_records: {state.type_counts['init']}")
    print(f"fault_records: {state.type_counts['fault']}")
    print(f"heartbeat_records: {state.type_counts['heartbeat']}")
    print(f"missing_fields: {state.missing_fields}")
    print(
        "stale_error_counts: "
        f"missing={state.marker_counts['missing']} "
        f"stale={state.marker_counts['stale']} "
        f"error={state.marker_counts['error']} "
        f"unavailable={state.marker_counts['unavailable']} "
        f"sensor_nonok={sum(state.status_counts.values())}"
    )
    print(f"sample_id_issues: {state.sample_id_issues}")
    print(f"timestamp_issues: {state.timestamp_issues}")
    if duration_s is None:
        print("expected_measurement_records: not checked (provide --duration-s to compute)")
    elif expected_count is None:
        print(f"expected_measurement_records: not computed (duration_s={duration_s}, nominal_rate_hz={nominal_rate_hz})")
    else:
        print(
            f"expected_measurement_records: {expected_count} "
            f"(duration_s={duration_s}, nominal_rate_hz={nominal_rate_hz})"
        )
    print(f"verdict: {'FAIL' if state.issues else 'PASS'}")
    if state.issues:
        print("issues:")
        for issue in state.issues[:50]:
            print(f"- {issue}")
        if len(state.issues) > 50:
            print(f"- ... {len(state.issues) - 50} more issue(s) omitted")


def build_arg_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        description=(
            "Validate ADS v0.1/v0.2 Serial0 canonical JSON Lines logs against "
            "the local ads.serial0.v1 baseline."
        )
    )
    parser.add_argument("log_path", help="Path to the newline-delimited UTF-8 JSON Lines Serial0 log")
    parser.add_argument(
        "--duration-s",
        type=float,
        help="Configured measurement-campaign duration in seconds; use 600 for the 10 min mission window",
    )
    parser.add_argument(
        "--nominal-rate-hz",
        type=float,
        default=5.0,
        help="Nominal measurement rate used with --duration-s (default: 5.0)",
    )
    parser.add_argument(
        "--require-expected-count",
        action="store_true",
        help="Fail unless measurement_records equals duration_s * nominal_rate_hz",
    )
    parser.add_argument(
        "--allow-nonmonotonic-sample-id",
        action="store_true",
        help="Explicitly allow duplicate or decreasing sample_id values for a documented special case",
    )
    parser.add_argument("--version", action="version", version=f"%(prog)s {PARSER_VERSION}")
    return parser


def main(argv: Optional[List[str]] = None) -> int:
    arg_parser = build_arg_parser()
    args = arg_parser.parse_args(argv)

    path = Path(args.log_path)
    state = parse_log(path, args.allow_nonmonotonic_sample_id)

    expected_count = None
    if args.duration_s is not None:
        expected_count, expected_error = expected_measurement_count(args.duration_s, args.nominal_rate_hz)
        if expected_error is not None:
            state.issue(0, f"invalid expected-count configuration: {expected_error}")
        elif args.require_expected_count and state.type_counts["measurement"] != expected_count:
            state.issue(
                0,
                "measurement count mismatch: "
                f"observed {state.type_counts['measurement']}, expected {expected_count}",
            )
    elif args.require_expected_count:
        state.issue(0, "--require-expected-count requires --duration-s")

    print_summary(path, state, args.duration_s, args.nominal_rate_hz, expected_count)
    return 1 if state.issues else 0


if __name__ == "__main__":
    sys.exit(main())
