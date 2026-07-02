"""Pure OBCC-DPS LoRa telemetry parsing helpers.

These helpers intentionally avoid GUI, serial-port, and file I/O side effects so
parser and CSV-facing semantics can be validated without hardware.
"""

LORA_HEADER = b"CSWS"
LORA_FOOTER = b"DTLB"
LORA_PAYLOAD_SIZE = 100
DEPLOYMENT_STATUS_OFFSET = 48

DEPLOYMENT_STATUS_NAMES = {
    0: "NOT_COMMANDED",
    1: "INHIBITED_STANDBY",
    2: "COMMAND_SENT",
    3: "OPEN_IN_PROGRESS",
    4: "OPEN_CONFIRMED",
    5: "NO_OPEN_CONFIRMED",
    6: "TIMEOUT",
    7: "JAM_DETECTED",
    8: "PDM_FAULT",
    9: "UNKNOWN",
}

DEPLOYMENT_STATUS_CATEGORIES = {
    0: "not-deployed",
    1: "not-deployed",
    2: "in-progress",
    3: "in-progress",
    4: "deployed",
    5: "not-deployed",
    6: "fault",
    7: "fault",
    8: "fault",
    9: "unknown",
}

# The current dashboard has no live CSV writer. These constants/helpers define
# the required CSV-facing schema so any future writer or test preserves the raw
# enum code, enum symbol, and high-level category without boolean collapse.
DEPLOYMENT_STATUS_CSV_COLUMNS = (
    "deployment_status_code",
    "deployment_status",
    "deployment_status_category",
)

DEFAULT_DEPLOYMENT_STATUS = {
    "code": 9,
    "symbol": "UNKNOWN",
    "name": "UNKNOWN",
    "category": "unknown",
    "is_deployed": False,
    "valid": True,
}


def _status(code, symbol, category, valid):
    return {
        "code": code,
        "symbol": symbol,
        "name": symbol,
        "category": category,
        "is_deployed": code == 4 and symbol == "OPEN_CONFIRMED" and category == "deployed",
        "valid": valid,
    }


def decode_deployment_status(packet):
    """Decode payload byte 48 into code, enum symbol, and category.

    Missing/short packets and unrecognized codes are non-success. Only code 4
    (`OPEN_CONFIRMED`) returns category `deployed` and `is_deployed == True`.
    """
    if packet is None or len(packet) <= DEPLOYMENT_STATUS_OFFSET:
        return _status(None, "MISSING", "unknown", False)

    raw_code = packet[DEPLOYMENT_STATUS_OFFSET]
    if isinstance(raw_code, str):
        raw_code = ord(raw_code)
    code = int(raw_code)

    symbol = DEPLOYMENT_STATUS_NAMES.get(code)
    if symbol is None:
        return _status(code, f"UNRECOGNIZED_{code}", "unknown", False)

    return _status(code, symbol, DEPLOYMENT_STATUS_CATEGORIES[code], True)


def format_deployment_status(status):
    code = status.get("code")
    display_code = "missing" if code is None else code
    return (
        "Parachute: "
        f"{status['category']} — {status['symbol']} (code {display_code})"
    )


def is_deployment_success(status):
    """Return True only for OPEN_CONFIRMED/deployed."""
    return (
        status.get("code") == 4
        and status.get("symbol", status.get("name")) == "OPEN_CONFIRMED"
        and status.get("category") == "deployed"
    )


def deployment_status_csv_columns(prefix_columns=()):
    """Return CSV columns with deployment-status preservation columns appended."""
    return tuple(prefix_columns) + DEPLOYMENT_STATUS_CSV_COLUMNS


def deployment_status_csv_row(status_or_packet):
    """Return deployment-status CSV fields for a decoded status or packet."""
    if isinstance(status_or_packet, dict):
        status = status_or_packet
    else:
        status = decode_deployment_status(status_or_packet)

    code = status.get("code")
    return {
        "deployment_status_code": "" if code is None else code,
        "deployment_status": status.get("symbol", status.get("name", "UNKNOWN")),
        "deployment_status_category": status.get("category", "unknown"),
    }


def is_valid_lora_payload(packet):
    return (
        packet is not None
        and len(packet) == LORA_PAYLOAD_SIZE
        and packet[:4] == LORA_HEADER
        and packet[96:100] == LORA_FOOTER
    )


def _partial_header_suffix_length(buffer):
    max_size = min(len(buffer), len(LORA_HEADER) - 1)
    for size in range(max_size, 0, -1):
        if buffer[-size:] == LORA_HEADER[:size]:
            return size
    return 0


def extract_lora_payload_frames(buffer):
    """Extract complete valid 100-byte payload frames from a serial byte buffer.

    Returns `(frames, remainder)`. Partial frames are retained in `remainder`;
    overlong buffers are split into individual 100-byte frames; bytes before the
    next header and candidates with invalid footers are not accepted as frames.
    """
    data = bytes(buffer or b"")
    frames = []

    while data:
        header_index = data.find(LORA_HEADER)
        if header_index < 0:
            keep = _partial_header_suffix_length(data)
            return frames, data[-keep:] if keep else b""

        if header_index > 0:
            data = data[header_index:]

        if len(data) < LORA_PAYLOAD_SIZE:
            return frames, data

        candidate = data[:LORA_PAYLOAD_SIZE]
        if is_valid_lora_payload(candidate):
            frames.append(candidate)
            data = data[LORA_PAYLOAD_SIZE:]
            continue

        # Header matched but footer/length validation failed; drop one byte and
        # resynchronize instead of accepting a shifted or overlong frame.
        data = data[1:]

    return frames, b""
