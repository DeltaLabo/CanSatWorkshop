# Sensor-to-OBCC freshness contract

**Contract version:** `PMSE-SENSOR-OBCC-FRESHNESS-v1.0`

**Owner:** PM&SE

**Applies to:** ADS and AMS v1.0 sensor data delivered to OBCC internal consumers and packaged into LoRa telemetry.

## 1. Purpose and scope

This is the shared ADS/AMS sensor-to-OBCC data freshness contract for v1.0 internal OBCC consumers and telemetry packaging. It defines the common timing, status, age, and stale/error behavior that ADS and AMS verification activities shall use when proving that sensor data is safe to consume by OBCC, parachute-control logic, and 2 s telemetry packaging.

This contract does not define subsystem-specific pointer names, payload field names, or ownership/lifetime implementation details. ADS- or AMS-specific `Pointers`/`Returns` supplements may define those details only by referencing this PM&SE contract.

## 2. Terminology and timing definitions

- **OBCC request/response capability at `5 Hz`:** ADS and AMS shall be able to respond to OBCC data requests at `5 Hz` for parachute-control consumers.
- **Nominal request period:** `5 Hz` corresponds to a nominal request period of **`200 ms`**.
- **Telemetry push cadence:** each **`2 s`** LoRa telemetry push uses the latest ADS/AMS samples, but telemetry shall expose, or be traceable to, the status and age of those samples.
- **Sample age:** `age_ms = consumer/request timestamp - sample_time_ms`, computed at the ADS/AMS-to-OBCC observation point with the same monotonic timebase or with a documented equivalent correlation method.
- **Freshness threshold:** required ADS/AMS data is fresh only when `status == VALID`, all required fields are finite/in range, and **sample age `<=400 ms`**. The `400 ms` threshold is equivalent to **two failed samples at `5 Hz`**.
- **Successful update:** a subsystem update that completed within its bounded timeout, initialized sensor state is available, no active runtime fault applies to the sample, and all required payload fields are finite and in range.

## 3. Required status enum

Every ADS/AMS response envelope governed by this contract shall use exactly this status vocabulary:

- `VALID`
- `STALE`
- `NO_DATA`
- `TIMEOUT`
- `SENSOR_FAULT`
- `INIT_FAIL`

## 4. Status semantics

- `VALID`: data age is `<=400 ms`, the sensor is initialized, no active fault is present, all required fields are finite and in range, and the sample was produced from a successful update.
- `STALE`: a last successful sample exists but age is `> 400 ms`, or freshness cannot be proven.
- `NO_DATA`: no successful sample has ever been produced since boot/reset or after reinitialization.
- `TIMEOUT`: the latest request/read exceeded the subsystem's bounded timeout.
- `SENSOR_FAULT`: a runtime sensor, bus, or value fault was detected.
- `INIT_FAIL`: startup initialization failed or never completed.

When more than one non-`VALID` condition is present, the implementation shall report a non-`VALID` status that preserves the most safety-relevant cause for the consumer and execution evidence. `VALID` is permitted only when every `VALID` condition above is true.

## 5. Forbidden behavior

Timeout, sensor fault, initialization failure, and no-data conditions shall not leave old samples marked `VALID`. Old values may be returned only with a non-`VALID` status and an age value. In particular:

- a timed-out read after a previous good sample shall report `TIMEOUT` or another applicable non-`VALID` status, not `VALID`;
- a runtime sensor/bus/value fault after a previous good sample shall report `SENSOR_FAULT` or another applicable non-`VALID` status, not `VALID`;
- failed or incomplete initialization shall report `INIT_FAIL` or `NO_DATA` as applicable, not `VALID`;
- after reset, reinitialization, buffer clear, or any interval with no successful sample available, an absent value shall report `NO_DATA` or another applicable non-`VALID` status, not a previous value as `VALID`.

## 6. Required response envelope fields

Any ADS/AMS response envelope to OBCC shall include, or be losslessly traceable in the associated log/evidence to, timestamp, sequence, age, and status evidence using these fields:

| Field | Requirement |
|---|---|
| `contract_version` | Identifies this contract version, `PMSE-SENSOR-OBCC-FRESHNESS-v1.0`. |
| `subsystem_id` | `ADS` or `AMS`. |
| `sample_id` | Monotonic or otherwise unique-enough sample/update identifier for stale/drop/duplicate analysis. |
| `sample_time_ms` | Subsystem sample timestamp in milliseconds on the declared timebase. |
| `request_time_ms` or consumer timestamp | OBCC request/consumer timestamp used to compute age. |
| `age_ms` | Computed age of the sample at OBCC consumption/packaging time. |
| `status` | One of `VALID`, `STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, `INIT_FAIL`. |
| Payload validity / field-status indicators | Per-payload validity, finite/range flags, field-status bits, or equivalent indicators when applicable. |

## 7. Telemetry packaging rule

At every `2 s` telemetry push, each required ADS/AMS sensor value is fresh only when `status` is `VALID` and `age_ms` is `<=400 ms` at packaging/consumption time. Every telemetry frame that includes ADS or AMS sensor values shall include, or be traceable through preserved logs to, the `age_ms` and `status` for those values. If `age_ms > 400 ms` or `status` is not `VALID`, telemetry shall not present the value as fresh valid data. It may include the old value only as stale/degraded/faulted data with the non-`VALID` status and age preserved.

## 8. Statistical and test oracle

- Strict freshness evidence should use **`n = 59`** representative request/response observations, with every response meeting age/status criteria, for formal timing/tolerance claims under the project IVV timing policy.
- Mission-window evidence should preserve all request/response and telemetry-packaging logs, including sample IDs, timestamps, ages, statuses, payload-validity indicators, dropped/duplicate/stale observations, fault markers, firmware/build identifiers, UUT identifiers, tool/script revisions, deviations, and waivers.
- Smaller samples or incomplete telemetry-packaging logs may support characterization only unless the verification report explicitly states the weaker claim.

## 9. Relationship to subsystem and system tests

- **ADS alignment path:** use this contract from `ADS-V10-DATA-FRESHNESS` if created, or from explicit extensions of `ADS-IVV-FC-OBCC-DELIVERY`, `ADS-IVV-C-GETTER`, `ADS-IVV-C-RATE-5HZ`, `ADS-IVV-FC-MISSION-WINDOW`, and `ADS-IVV-C-NOBLOCK` where those activities make freshness/status, mission-window, or no-blocking claims.
- **AMS alignment path:** use this contract from `AMS-V10-DATA-FRESHNESS` if created, or from explicit extensions of `AMS-VV-API-001`, `AMS-VV-FC-001`, `AMS-VV-FC-002`, `AMS-VV-CON-003`, and `AMS-VV-CON-004` where those activities make freshness/status, init-fault, timeout, or non-blocking claims.
- **System alignment path:** `SYS-END-TO-END-DATA` uses this contract as the sensor freshness oracle for ADS/AMS payload age/status fields and stale/error behavior.
