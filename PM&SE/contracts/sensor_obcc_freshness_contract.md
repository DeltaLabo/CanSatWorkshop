# Sensor-to-OBCC freshness contract

**Contract version:** `PMSE-SENSOR-OBCC-FRESHNESS-v1.0`

**Publication owner:** PM&SE configuration control

**Applies to:** ADS and AMS v1.0 sensor data delivered to OBCC internal consumers and packaged into LoRa telemetry.

## 1. Authority and change control

1. [`PM&SE/MBSE/v1.0/`](../MBSE/v1.0/README.md) owns the cross-subsystem freshness semantics, status vocabulary, and packaging constraints.
2. Subsystem `v1.0` baselines refine subsystem-internal implementation and allocation in `ADS/MBSE/v1.0/`, `AMS/MBSE/v1.0/`, and `OBCC/MBSE/v1.0/`.
3. Modeled verification definitions own the test means, pass/fail oracles, statistics, and fault cases.
4. This Markdown file is a controlled human-readable publication of those modeled semantics. It shall not redefine contradictory values.
5. [`sensor_obcc_freshness_contract.h`](sensor_obcc_freshness_contract.h) is the reference C realization of these modeled constants, enums, and envelope fields.
6. Product semantic changes start in the PM&SE system model, then flow into subsystem baselines and verification packages, and only then into this publication and the header realization.

## 2. Model coverage

| Concern | PM&SE system baseline view(s) | Subsystem refinement view(s) | System verification package(s) |
|---|---|---|---|
| Sensor request/response | [`CANSAT_v1.0_view2_logical.d2`](../MBSE/v1.0/CANSAT_v1.0_view2_logical.d2), [`CANSAT_v1.0_view4_sensor_sample_delivery_chain.d2`](../MBSE/v1.0/CANSAT_v1.0_view4_sensor_sample_delivery_chain.d2) | ADS [`ADS_v1.0_view2_logical.d2`](../../ADS/MBSE/v1.0/ADS_v1.0_view2_logical.d2), [`ADS_v1.0_view5_angular_velocity_chain.d2`](../../ADS/MBSE/v1.0/ADS_v1.0_view5_angular_velocity_chain.d2); AMS [`AMS_v1.0_view3_functional_allocation.d2`](../../AMS/MBSE/v1.0/AMS_v1.0_view3_functional_allocation.d2), [`AMS_v1.0_view4_atmospheric_measurement_chain.d2`](../../AMS/MBSE/v1.0/AMS_v1.0_view4_atmospheric_measurement_chain.d2); OBCC [`OBCC_v1.0_view9_sensor_sample_delivery_chain.d2`](../../OBCC/MBSE/v1.0/OBCC_v1.0_view9_sensor_sample_delivery_chain.d2) | [`SYS-END-TO-END-DATA`](../MBSE/tests/SYS-END-TO-END-DATA/README.md), [`SYS-MISSION-REHEARSAL`](../MBSE/tests/SYS-MISSION-REHEARSAL/README.md) |
| Response envelope | [`CANSAT_v1.0_view4_sensor_sample_delivery_chain.d2`](../MBSE/v1.0/CANSAT_v1.0_view4_sensor_sample_delivery_chain.d2), [`CANSAT_v1.0_view6_telemetry_downlink_chain.d2`](../MBSE/v1.0/CANSAT_v1.0_view6_telemetry_downlink_chain.d2) | ADS [`ADS_v1.0_view2_logical.d2`](../../ADS/MBSE/v1.0/ADS_v1.0_view2_logical.d2), [`ADS_v1.0_view5_angular_velocity_chain.d2`](../../ADS/MBSE/v1.0/ADS_v1.0_view5_angular_velocity_chain.d2); AMS [`AMS_v1.0_view3_functional_allocation.d2`](../../AMS/MBSE/v1.0/AMS_v1.0_view3_functional_allocation.d2), [`AMS_v1.0_view4_atmospheric_measurement_chain.d2`](../../AMS/MBSE/v1.0/AMS_v1.0_view4_atmospheric_measurement_chain.d2); OBCC [`OBCC_v1.0_view9_sensor_sample_delivery_chain.d2`](../../OBCC/MBSE/v1.0/OBCC_v1.0_view9_sensor_sample_delivery_chain.d2), [`OBCC_v1.0_view5_telemetry_downlink_chain.d2`](../../OBCC/MBSE/v1.0/OBCC_v1.0_view5_telemetry_downlink_chain.d2) | [`SYS-END-TO-END-DATA`](../MBSE/tests/SYS-END-TO-END-DATA/README.md), [`SYS-MISSION-REHEARSAL`](../MBSE/tests/SYS-MISSION-REHEARSAL/README.md) |
| Status vocabulary and fresh-valid rule | [`CANSAT_v1.0_view4_sensor_sample_delivery_chain.d2`](../MBSE/v1.0/CANSAT_v1.0_view4_sensor_sample_delivery_chain.d2), [`CANSAT_v1.0_view5_sensor_fault_handling_chain.d2`](../MBSE/v1.0/CANSAT_v1.0_view5_sensor_fault_handling_chain.d2), [`CANSAT_v1.0_view8_deployment_safety_status_chain.d2`](../MBSE/v1.0/CANSAT_v1.0_view8_deployment_safety_status_chain.d2) | ADS [`ADS_v1.0_view2_logical.d2`](../../ADS/MBSE/v1.0/ADS_v1.0_view2_logical.d2), [`ADS_v1.0_view8_degraded_fault_chain.d2`](../../ADS/MBSE/v1.0/ADS_v1.0_view8_degraded_fault_chain.d2); AMS [`AMS_v1.0_view3_functional_allocation.d2`](../../AMS/MBSE/v1.0/AMS_v1.0_view3_functional_allocation.d2), [`AMS_v1.0_view6_sensor_degraded_fault_chain.d2`](../../AMS/MBSE/v1.0/AMS_v1.0_view6_sensor_degraded_fault_chain.d2); OBCC [`OBCC_v1.0_view8_runtime_fault_handling_chain.d2`](../../OBCC/MBSE/v1.0/OBCC_v1.0_view8_runtime_fault_handling_chain.d2), [`OBCC_v1.0_view7_deployment_gating_chain.d2`](../../OBCC/MBSE/v1.0/OBCC_v1.0_view7_deployment_gating_chain.d2) | [`SYS-END-TO-END-DATA`](../MBSE/tests/SYS-END-TO-END-DATA/README.md), [`SYS-DEPLOYMENT-SAFE-LIVE`](../MBSE/tests/SYS-DEPLOYMENT-SAFE-LIVE/README.md), [`SYS-MISSION-REHEARSAL`](../MBSE/tests/SYS-MISSION-REHEARSAL/README.md) |
| Fault and degraded handling | [`CANSAT_v1.0_view5_sensor_fault_handling_chain.d2`](../MBSE/v1.0/CANSAT_v1.0_view5_sensor_fault_handling_chain.d2), [`CANSAT_v1.0_view8_deployment_safety_status_chain.d2`](../MBSE/v1.0/CANSAT_v1.0_view8_deployment_safety_status_chain.d2) | ADS [`ADS_v1.0_view8_degraded_fault_chain.d2`](../../ADS/MBSE/v1.0/ADS_v1.0_view8_degraded_fault_chain.d2); AMS [`AMS_v1.0_view6_sensor_degraded_fault_chain.d2`](../../AMS/MBSE/v1.0/AMS_v1.0_view6_sensor_degraded_fault_chain.d2); OBCC [`OBCC_v1.0_view8_runtime_fault_handling_chain.d2`](../../OBCC/MBSE/v1.0/OBCC_v1.0_view8_runtime_fault_handling_chain.d2); PDM [`PDM_v1.0_view5_degraded_fault_status_chain.d2`](../../PDM/MBSE/v1.0/PDM_v1.0_view5_degraded_fault_status_chain.d2) | [`SYS-DEPLOYMENT-SAFE-LIVE`](../MBSE/tests/SYS-DEPLOYMENT-SAFE-LIVE/README.md), [`SYS-MISSION-REHEARSAL`](../MBSE/tests/SYS-MISSION-REHEARSAL/README.md), [`SYS-END-TO-END-DATA`](../MBSE/tests/SYS-END-TO-END-DATA/README.md) |
| Telemetry packaging | [`CANSAT_v1.0_view6_telemetry_downlink_chain.d2`](../MBSE/v1.0/CANSAT_v1.0_view6_telemetry_downlink_chain.d2) | OBCC [`OBCC_v1.0_view5_telemetry_downlink_chain.d2`](../../OBCC/MBSE/v1.0/OBCC_v1.0_view5_telemetry_downlink_chain.d2); DPS [`DPS_v1.0_view4_downlink_processing_chain.d2`](../../DPS/MBSE/v1.0/DPS_v1.0_view4_downlink_processing_chain.d2) | [`SYS-END-TO-END-DATA`](../MBSE/tests/SYS-END-TO-END-DATA/README.md), [`SYS-MISSION-REHEARSAL`](../MBSE/tests/SYS-MISSION-REHEARSAL/README.md) |

## 3. Semantic scope

This publication defines the shared ADS/AMS-to-OBCC timing, status, age, and stale/error handling used by OBCC consumers and telemetry packaging. It does not define subsystem-specific pointer names, payload field names, memory ownership naming, or other implementation-private API details.

Those implementation details may be published in subsystem supplements only by reference to this contract and the owning model views above.

## 4. Canonical timing and freshness semantics

- **OBCC request/response capability at `5 Hz`:** ADS and AMS shall be able to respond to OBCC data requests at `5 Hz` for parachute-control and other internal consumers.
- **Nominal request period:** `5 Hz` corresponds to **`200 ms`** nominal request spacing.
- **Telemetry packaging cadence:** each **`2 s`** telemetry opportunity packages the latest ADS/AMS snapshots, but telemetry packaging does not replace the internal `5 Hz` freshness evidence path.
- **Sample age:** `age_ms = consumer/request timestamp - sample_time_ms`, computed at the ADS/AMS-to-OBCC observation point with the same monotonic timebase or a documented equivalent correlation method.
- **Freshness threshold:** a required ADS/AMS value is fresh only when `status == VALID`, all required fields are finite and in range, and **`age_ms <= 400 ms`**.
- **Successful update:** a subsystem update completed within its bounded timeout, initialized sensor state is available, no active runtime fault applies to the sample, and all required payload fields are finite and in range.

## 5. Exact status vocabulary and non-contradiction rules

Every ADS/AMS response envelope governed by this contract shall use exactly this status vocabulary:

- `VALID`
- `STALE`
- `NO_DATA`
- `TIMEOUT`
- `SENSOR_FAULT`
- `INIT_FAIL`

### Status semantics

- `VALID`: data age is `<=400 ms`, the sensor is initialized, no active fault is present, all required fields are finite and in range, and the sample was produced from a successful update.
- `STALE`: a last successful sample exists but age is `>400 ms`, or freshness cannot be proven.
- `NO_DATA`: no successful sample has ever been produced since boot/reset or after reinitialization.
- `TIMEOUT`: the latest request/read exceeded the subsystem's bounded timeout.
- `SENSOR_FAULT`: a runtime sensor, bus, or value fault was detected.
- `INIT_FAIL`: startup initialization failed or never completed.

When more than one non-`VALID` condition is present, the implementation shall report the non-`VALID` status that preserves the most safety-relevant cause for the consumer and execution evidence. `VALID` is permitted only when every `VALID` condition above is true.

### Forbidden behavior

Timeout, sensor fault, initialization failure, and no-data conditions shall not leave old samples marked `VALID`. Old values may be returned only with a non-`VALID` status and an age value. In particular:

- a timed-out read after a previous good sample shall report `TIMEOUT` or another applicable non-`VALID` status, not `VALID`;
- a runtime sensor/bus/value fault after a previous good sample shall report `SENSOR_FAULT` or another applicable non-`VALID` status, not `VALID`;
- failed or incomplete initialization shall report `INIT_FAIL` or `NO_DATA` as applicable, not `VALID`;
- after reset, reinitialization, buffer clear, or any interval with no successful sample available, an absent value shall report `NO_DATA` or another applicable non-`VALID` status, not a previous value as `VALID`.

## 6. Derived realization content retained here

The following fields are kept here as human-readable realization detail for integration work. They realize the owning model constraints listed in the coverage table.

| Field | Requirement |
|---|---|
| `contract_version` | `PMSE-SENSOR-OBCC-FRESHNESS-v1.0` |
| `subsystem_id` | `ADS` or `AMS` |
| `sample_id` | Monotonic or otherwise unique-enough sample/update identifier for stale/drop/duplicate analysis |
| `sample_time_ms` | Subsystem sample timestamp in milliseconds on the declared timebase |
| `request_time_ms` or consumer timestamp | OBCC request/consumer timestamp used to compute age |
| `age_ms` | Computed age of the sample at OBCC consumption/packaging time |
| `status` | One of `VALID`, `STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, `INIT_FAIL` |
| Payload validity / field-status indicators | Per-payload validity, finite/range flags, field-status bits, or equivalent indicators when applicable |

### Derived telemetry-packaging rule

At every `2 s` telemetry opportunity, each required ADS/AMS sensor value is fresh only when `status` is `VALID` and `age_ms <= 400 ms` at packaging time. Every telemetry frame that includes ADS or AMS values shall include, or be losslessly traceable through preserved logs to, the `age_ms` and `status` for those values. If `age_ms > 400 ms` or `status` is not `VALID`, telemetry shall not present the value as fresh-valid data.

## 7. Derived execution context owned by IVV and verification packages

The statistics, execution sample sizes, and report oracles below are owned by [`PM&SE/IVV.md`](../IVV.md) and the modeled verification packages; they are repeated here only as a traceability aid:

- Strict freshness timing claims use **`n = 59`** representative request/response observations with every observation satisfying the selected timing/freshness limits.
- Mission-window evidence preserves request/response and telemetry-packaging logs, including sample IDs, timestamps, ages, statuses, payload-validity indicators, dropped/duplicate/stale observations, fault markers, firmware/build identifiers, UUT identifiers, tool/script revisions, deviations, and waivers.
- Smaller samples or incomplete logs support characterization only unless the verification report explicitly states the weaker claim.

Relevant subsystem verification definitions that refine this publication include:

- ADS [`ADS-IVV-FC-OBCC-DELIVERY`](../../ADS/MBSE/tests/ADS-IVV-FC-OBCC-DELIVERY/README.md), [`ADS-IVV-C-GETTER`](../../ADS/MBSE/tests/ADS-IVV-C-GETTER/README.md), [`ADS-IVV-C-RATE-5HZ`](../../ADS/MBSE/tests/ADS-IVV-C-RATE-5HZ/README.md), [`ADS-IVV-FC-MISSION-WINDOW`](../../ADS/MBSE/tests/ADS-IVV-FC-MISSION-WINDOW/README.md), [`ADS-IVV-C-NOBLOCK`](../../ADS/MBSE/tests/ADS-IVV-C-NOBLOCK/README.md)
- AMS [`AMS-V10-DATA-FRESHNESS`](../../AMS/MBSE/tests/AMS-V10-DATA-FRESHNESS/README.md), [`AMS-VV-API-001`](../../AMS/MBSE/tests/AMS-VV-API-001/README.md), [`AMS-VV-CON-003`](../../AMS/MBSE/tests/AMS-VV-CON-003/README.md), [`AMS-VV-CON-004`](../../AMS/MBSE/tests/AMS-VV-CON-004/README.md), [`AMS-VV-FC-002`](../../AMS/MBSE/tests/AMS-VV-FC-002/README.md)
- System [`SYS-END-TO-END-DATA`](../MBSE/tests/SYS-END-TO-END-DATA/README.md), [`SYS-DEPLOYMENT-SAFE-LIVE`](../MBSE/tests/SYS-DEPLOYMENT-SAFE-LIVE/README.md), [`SYS-MISSION-REHEARSAL`](../MBSE/tests/SYS-MISSION-REHEARSAL/README.md)
