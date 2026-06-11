# ADS v0.2 test plan and reference corpus

> File name intentionally follows the requested `READNE.md` spelling. No D2/Capella diagrams were edited while preparing this plan.

## 1. Scope

This test plan covers the ADS subsystem modelled in `ADS/MBSE/v0.2/`:

- `ADS_v0.2_view1_physical.d2`: UBX-G7020-KT GPS, XIAO ESP32, ICM20948 IMU, external PC, UART/I2C/power/USB-C links.
- `ADS_v0.2_view2_logical.d2`: ADS GPS Sensing, ADS Kinematic Sensing, Setup, Loop, UART/I2C CEs, implementation constraints.
- `ADS_v0.2_view3_functional_allocation.d2`: allocated functions and constraints.
- `ADS_v0.2_view4_gps_position_chain.d2`: longitude/latitude, UART payload, getters, `Collect measurements`, `<5 m`, `5 Hz`.
- `ADS_v0.2_view5_angular_velocity_chain.d2`: angular velocity acquisition and processing, `<30 deg/s`.
- `ADS_v0.2_view6_attitude_estimation_chain.d2`: acceleration and magnetic-field acquisition to pitch/roll/yaw.
- `ADS_v0.2_view7_peripheral_initialisation_chain.d2`: UBX/IMU init-state collection and software constraints.
- `ADS_v0.2_view8_serial_logging_chain.d2`: init states and measurements logged via Serial0.

Primary verification method is **test**, supported by **inspection** and **analysis** where noted.

## 2. Reference corpus

The reference corpus is saved under `tests/references/`:

- Search records: `tests/references/searches/*.json`.
- Saved sources and PDF text extracts: `tests/references/sources/`.
- Corpus index: `tests/references/README.md`.

Most relevant sources used here:

| Source | Test use |
|---|---|
| NASA Systems Engineering Handbook | Verification vs validation; methods include test, analysis, inspection, demonstration. |
| NASA GEVS GSFC-STD-7000B | Tailored environmental/workmanship verification; monitor powered hardware during tests where practicable. |
| ESA CanSat page/book and MDPI CanSat compendium | CanSat operational context, recovery/GPS relevance, short flight window; 120 s recommended max flight time. |
| GPS SPS Performance Standard 2020 | GNSS 95% accuracy/statistical framing; SPS horizontal accuracy context. |
| u-blox G7020 product summary and u-blox receiver protocol spec | Update-rate capability, UART/DDC interfaces, valid-fix/message handling. |
| TDK ICM-20948 datasheet | IMU ranges, gyro characteristics, I2C Fast-mode timing. |
| NXP UM10204 I2C-bus specification | I2C START/STOP/ACK/NACK and 100/400 kbit/s mode references. |
| ISO/IEC/IEEE 29119 overview | Test-process and documentation framing. |
| NIST tolerance interval pages; ReliaSoft binomial RDT page | Continuous and pass/fail acceptance statistics. |

## 3. Model-derived verification targets

| ID | Model target | Source view(s) | Verified by |
|---|---|---|---|
| ADS-PHY-01 | GPS-XIAO UART/3V3/GND, IMU-XIAO I2C/3V3/GND, XIAO-PC USB-C physical links exist and are correctly connected. | View 1 | ADS-T01 |
| ADS-INIT-01 | Setup collects UBX-G7020-KT and ICM20948 IMU init states. | Views 3, 7, 8 | ADS-T02, ADS-T09 |
| ADS-GPS-01 | GPS chain returns stored latitude/longitude to `Collect measurements`. | Views 3, 4 | ADS-T03, ADS-T04, ADS-T11 |
| ADS-GPS-02 | Position accuracy `< 5 m` and collection at `5 Hz`. | Views 3, 4 | ADS-T04, ADS-T08, ADS-T11 |
| ADS-IMU-01 | Angular velocities are read over I2C, processed, and collected. | Views 3, 5 | ADS-T05, ADS-T06, ADS-T11 |
| ADS-IMU-02 | Angular-rate accuracy `< 30 deg/s`. | Views 3, 5 | ADS-T06 |
| ADS-ATT-01 | Accelerations and magnetic-field intensities feed pitch/roll/yaw calculation and collection. | Views 3, 6 | ADS-T07, ADS-T11 |
| ADS-SW-01 | No blocking operations except I2C/UART; process/calculate functions `< 5 ms`; UART reads timeout `<= 5 ms`. | Views 2, 3, 7 | ADS-T08 |
| ADS-SW-02 | Read/process or read/calculate pairs follow the Variable Getter pattern. | Views 2, 3, 7 | ADS-T10 |
| ADS-LOG-01 | Init states and measurement frames are logged through Serial0 to PC. | Views 1, 3, 8 | ADS-T09, ADS-T11 |

## 4. Common test instrumentation

Recommended data to log for every runtime test:

- Monotonic timestamp in microseconds or milliseconds.
- Loop sequence counter.
- Function start/end durations for read, process, calculate, collect, and log functions.
- UART read duration, timeout flag, bytes read, parsed message type, GPS valid-fix flag.
- I2C transaction status, bytes read, ACK/NACK/error status.
- Raw and processed GPS/IMU values.
- Serial0 line emitted to the PC, including any init-state fields.
- Reset/brownout markers if available.

## 5. Statistical acceptance rules

Use these rules unless a scenario gives a stricter criterion.

1. **Continuous upper-bound requirements** (`<5 m`, `<30 deg/s`, `<5 ms`, `<=5 ms`): collect at least `n=59` independent samples per condition. Passing all 59 samples below the limit is a non-parametric one-sided 95/95 tolerance demonstration: at 95% confidence, at least 95% of the population is below the observed maximum.
2. **Boolean success/failure requirements**: `n=59` successes with zero failures demonstrates at least 95% reliability at 95% confidence for that scenario using the non-parametric binomial zero-failure rule.
3. **Rate requirements**: evaluate both average rate and worst inter-sample gaps. The ADS target is `5 Hz`, so nominal period is `200 ms`.
4. **If fewer than 59 samples are feasible**, record the achieved confidence and mark the result as characterization unless an exact binomial/tolerance-interval calculation is supplied with the report.

## 6. Scenario tests

### ADS-T01 — Physical integration and electrical continuity

**Scenario:** Assemble the ADS hardware exactly as modelled: UBX-G7020-KT GPS to XIAO ESP32 over UART/3V3/GND, ICM20948 IMU to XIAO over I2C/3V3/GND, and XIAO to PC over USB-C.

**Procedure:**
1. Inspect wiring, connector orientation, pin labels, and strain relief.
2. Verify continuity for UART TX/RX, I2C SDA/SCL, 3V3, GND, and USB-C connection.
3. Power the XIAO from the intended source and measure 3V3 at GPS and IMU under idle and active polling.
4. Confirm no unintended shorts between 3V3/GND or signal lines.

**Acceptance:** all physical links match View 1; supply remains within component limits; no shorts/open circuits; PC enumerates the XIAO serial device.

**References:** TDK ICM-20948 datasheet; u-blox G7020 product summary; NASA SE verification by inspection/test.

### ADS-T02 — Peripheral initialization-state collection

**Scenario:** On boot, Setup initializes Serial0/Serial1 and collects both UBX-G7020-KT and IMU init states.

**Procedure:**
1. Boot the ADS with GPS and IMU connected.
2. Capture Serial0 output and internal test logs from reset through first measurement cycle.
3. Repeat for fault injections: GPS UART disconnected, IMU I2C disconnected, GPS no-fix/open-sky unavailable.
4. Run at least 59 nominal boots if using the zero-failure confidence rule.

**Acceptance:** nominal boot reports both init states as valid/available before measurement logging starts; each injected fault is reported as the correct degraded init state without firmware hang or reset.

**References:** Views 3, 7, 8; u-blox protocol valid/status guidance; I2C ACK/NACK behavior; ReliaSoft binomial RDT.

### ADS-T03 — GPS UART protocol, valid fix, and stored lat/lon getters

**Scenario:** The XIAO requests/receives GPS payloads over UART, stores latitude/longitude, and `Get lat`/`Get lon` return the latest valid stored values.

**Procedure:**
1. Run outdoors with open-sky GNSS reception or use a GNSS simulator/replay fixture.
2. Record UART bytes, parsed GPS message type, valid-fix flag, stored lat/lon, and getter outputs.
3. Inject malformed/truncated UART frames and periods with no UART data.
4. Confirm read timeout behavior is also checked in ADS-T08.

**Acceptance:** valid GPS frames update stored lat/lon once per accepted fix; invalid/no-fix/malformed frames do not overwrite the last valid value unless the implementation explicitly marks the value stale; getters return the same stored value used by `Collect measurements`.

**References:** View 4; u-blox receiver protocol spec; GPS SPS valid position context.

### ADS-T04 — GPS 5 Hz collection and `<5 m` static position accuracy

**Scenario:** At a surveyed open-sky reference point, ADS collects latitude/longitude at 5 Hz and meets the modelled `<5 m` position accuracy target.

**Procedure:**
1. Place ADS antenna at a known surveyed point or a reference point measured with a higher-grade receiver.
2. Wait for stable valid fix.
3. Log at least 59 valid position samples at the ADS output, preferably 5 minutes or more.
4. Convert each lat/lon sample to horizontal error in metres from the reference point.
5. Compute sample count, mean rate, inter-sample periods, maximum horizontal error, and 95th percentile.

**Acceptance:** output rate is `5 Hz` with mean period `200 ms ± 20 ms`; no inter-sample gap exceeds `400 ms` during the test window; the one-sided 95/95 upper bound for horizontal error is `<5 m` (with `n=59`, all samples below 5 m satisfies this non-parametrically).

**References:** Views 3, 4; u-blox G7020 update-rate/accuracy summary; GPS SPS Performance Standard 2020; NIST tolerance intervals.

### ADS-T05 — IMU I2C communication and ICM20948 data integrity

**Scenario:** The XIAO reads angular velocity, acceleration, and magnetic-field data from the ICM20948 over I2C without bus errors.

**Procedure:**
1. Configure I2C in a mode compatible with the ICM20948, preferably Fast-mode `<=400 kHz`.
2. Capture I2C address, register reads, ACK/NACK, error codes, and transaction duration.
3. Collect at least 59 read cycles for each sensor group: gyro, accelerometer, magnetometer.
4. Fault-inject by temporarily disconnecting SDA/SCL or using an invalid address in a bench build.

**Acceptance:** nominal reads complete with ACK and expected byte counts; no stuck bus; fault injection produces bounded error handling and recovery on the next valid cycle.

**References:** View 6; NXP UM10204 I2C spec; TDK ICM-20948 I2C timing (`400 kHz` Fast-mode, bus capacitance/timing constraints).

### ADS-T06 — Angular velocity processing and `<30 deg/s` accuracy

**Scenario:** ADS reads and processes IMU angular velocities and meets the modelled `<30 deg/s` accuracy target.

**Procedure:**
1. Calibrate gyro bias with the ADS held stationary.
2. Test per axis at known rates: stationary `0 deg/s` and at least one controlled rotation rate within the selected gyro range.
3. Use a rate table, calibrated reference IMU, or repeatable turn fixture.
4. Record raw gyro, processed angular velocity, reference angular velocity, and error.
5. Collect at least 59 samples per axis per rate condition.

**Acceptance:** for each axis and rate condition, the one-sided 95/95 upper bound of absolute angular-rate error is `<30 deg/s`; processed values remain finite and within the configured ICM20948 full-scale range.

**References:** Views 3, 5; TDK ICM-20948 gyro range/sensitivity/noise data; NIST tolerance intervals.

### ADS-T07 — Attitude estimation chain plausibility

**Scenario:** Acceleration and magnetic-field readings feed `Calculate pitch, roll, yaw`, then `Collect measurements` receives finite PRY outputs.

**Procedure:**
1. Place ADS in six static orientations: +X, -X, +Y, -Y, +Z, -Z up.
2. For each orientation, log accelerations, field intensities, pitch/roll/yaw, calculation duration, and collected measurement frame.
3. Rotate yaw slowly through at least 180 degrees in a low-magnetic-disturbance area.
4. Repeat after a power cycle to check repeatability.

**Acceptance:** pitch/roll/yaw values are finite, bounded to the implementation's documented angle convention, and update from fresh acceleration/magnetic-field samples; static pitch/roll signs match the known orientation; yaw changes monotonically in the expected direction during the controlled yaw rotation. Calculation duration is checked against ADS-T08.

**References:** View 6; TDK ICM-20948 accelerometer/magnetometer ranges; NASA SE validation under realistic/simulated conditions.

### ADS-T08 — Loop timing, no unintended blocking, and UART timeout

**Scenario:** Runtime functions obey the implementation constraints: no blocking except I2C/UART, all process/calculate functions `<5 ms`, and all UART reads timeout `<=5 ms`.

**Procedure:**
1. Instrument every read, process, calculate, collect, and log function with monotonic timestamps.
2. Run nominal end-to-end operation for at least 120 s.
3. Repeat with GPS UART silent, malformed UART stream, and IMU I2C delayed/unavailable.
4. Record maximum duration and distribution for each function.

**Acceptance:** every process/calculate invocation is `<5 ms`; every UART read returns or times out in `<=5 ms`; no non-I2C/non-UART function blocks waiting for external data; `Collect measurements` remains at 5 Hz under nominal conditions.

**References:** Views 2, 3, 7; ISO/IEC/IEEE 29119 test-process context; NIST tolerance intervals.

### ADS-T09 — Serial0 logging contract to PC

**Scenario:** The XIAO logs peripheral init states and measurement frames through Serial0 over USB-C to the external PC.

**Procedure:**
1. Connect the PC to the XIAO USB-C serial port and capture raw Serial0 output.
2. Boot ADS and record initialization lines.
3. Run nominal 5 Hz measurement logging for at least 120 s.
4. Parse every line/frame for timestamp/sequence, init-state fields, lat/lon, angular velocities, accelerations, pitch/roll/yaw, and any declared LoRa-frame payload.

**Acceptance:** PC receives parseable init-state output and measurement frames; nominal logging rate is 5 Hz; no malformed frame in 59 consecutive frames; fields required by the modelled chains are present or explicitly marked unavailable/stale.

**References:** Views 1, 8; ESA CanSat 120 s flight-time context; CanSat compendium telemetry context.

### ADS-T10 — Variable Getter freshness and single-writer behavior

**Scenario:** Each modelled read/process or read/calculate pair behaves as a Variable Getter pattern: reads update stored variables, getters/calculators consume stored values without hidden blocking side effects.

**Procedure:**
1. Use a software test build or hardware-in-loop fixture with deterministic GPS and IMU input sequences.
2. Step inputs one sample at a time and call getters/calculators multiple times between reads.
3. Verify repeated getter calls return the same value until a new read succeeds.
4. Verify failed reads do not silently corrupt stored values.

**Acceptance:** each variable has one update path; getter/calculator calls are side-effect-light and non-blocking; stale/invalid data is detectable by timestamp, sequence, validity flag, or documented equivalent.

**References:** Views 2, 3, 7; ISO/IEC/IEEE 29119 static/dynamic test-process framing.

### ADS-T11 — End-to-end CanSat mission-duration run

**Scenario:** ADS operates as a complete subsystem through a representative CanSat descent/mission window and produces usable logged data.

**Procedure:**
1. Assemble ADS in its flight-like mechanical/electrical configuration.
2. Start serial capture on the PC.
3. Run a 120 s mission script: boot, wait for valid GPS, nominal 5 Hz collection, manual rotations/tilts, and continued logging.
4. Optionally perform the same run during a tethered outdoor walk/drop-safe test where GPS movement is observable.
5. Check all scenario-specific metrics after the run.

**Acceptance:** no firmware reset or unrecovered peripheral failure; GPS, IMU, attitude, init-state, and logging chains all produce time-correlated data; at least 95% of expected 5 Hz frames are present over 120 s; no gap exceeds 2 s; ADS-T04/T06/T08/T09 metrics remain within limits for the portions of the run where their preconditions are met.

**References:** All D2 views; ESA CanSat operational context; NASA SE validation under realistic conditions.

### ADS-T12 — Tailored environmental/workmanship regression

**Scenario:** ADS remains functional after realistic CanSat handling, transport, and launch/descent workmanship stresses.

**Procedure:**
1. Define environment levels from the actual launcher/competition rules. If unavailable, use safe educational screening levels and document them.
2. Run ADS-T02, ADS-T05, ADS-T08, and ADS-T09 as a pre-test baseline.
3. Subject the assembled ADS to tailored vibration/shake, connector tug, thermal hot/cold soak within component limits, and landing/handling shock screening.
4. Monitor powered hardware during exposures where safe and practicable.
5. Repeat the baseline tests after exposure.

**Acceptance:** no loose connectors, cracked solder joints, or damaged cables; post-exposure baseline tests pass; GPS UART, IMU I2C, and Serial0 logging remain functional.

**References:** NASA GEVS tailoring/workmanship approach; MIL-STD-810H source page for environmental-method discovery; ESA CanSat hardware-testing context; component datasheets for absolute limits.

## 7. Reporting template

For each executed scenario, record:

- Test ID and version of ADS hardware/software.
- Diagram/view requirements covered.
- Date, operator, location, and equipment calibration/source.
- Procedure deviations.
- Raw data path and analysis script path.
- Pass/fail result against each acceptance criterion.
- Anomalies, suspected cause, corrective action, and retest status.

## 8. Open items before execution

- Identify the exact XIAO ESP32 firmware repository and add automated test hooks/scripts there.
- Define the Serial0 frame schema if not already fixed in code.
- Select GPS truth source: surveyed point, high-grade receiver, or GNSS simulator.
- Select angular-rate truth source: rate table, calibrated reference IMU, or approved fixture.
- Define tailored environmental levels from the actual CanSat launch/competition provider.
