# OBCC MBSE v1.0 scenario-based test plan

This folder is a test/reference corpus for the Capella-style D2 Physical Architecture model in `OBCC/MBSE/v1.0`. It was prepared from the diagrams only; the D2/PNG views are not modified.

## Model views read

| View | File | Test-relevant content |
|---|---|---|
| PV physical architecture | `OBCC_v1.0_view1_physical.d2` | XIAO ESP32-S3 OBCC, RFM95W LoRa, BME280, ICM20948, micro-servo, GPS, INA219, battery/PDS, ground station/dashboard, GPIO/I2C/UART/SPI/PWM/LoRa/power links. |
| Logical architecture | `OBCC_v1.0_view2_logical.d2` | FreeRTOS tasks, queues, timers/ISRs, telemetry encoder, LoRa driver, state manager, deployment controller, sensor getters, ground decoder/dashboard/logger. |
| Functional allocation | `OBCC_v1.0_view3_functional_allocation.d2` | Startup health, sensor acquisition, 34-byte telemetry payload, LoRa downlink/uplink, On/Standby modes, deployment gating, runtime fault management. |
| Startup chain | `OBCC_v1.0_view4_startup_health_chain.d2` | Critical vs non-critical peripheral startup checks and degraded-mode entry. |
| Telemetry chain | `OBCC_v1.0_view5_telemetry_downlink_chain.d2` | Sensor sampling, payload encoding, 2 s LoRa heartbeat/status/measurement downlink, ground decode/display/store. |
| Command/state chain | `OBCC_v1.0_view6_command_state_chain.d2` | Wireless On/Standby command path; no serial-console operator for v1.0. |
| Deployment gate chain | `OBCC_v1.0_view7_deployment_gating_chain.d2` | Deployment inhibited in Standby; in On, trigger must actuate servo within 5 s; telemetry continues. |
| Runtime fault chain | `OBCC_v1.0_view8_runtime_fault_handling_chain.d2` | Getter timeouts, bus protection, error flags, safe/degraded behavior, telemetry of health/status. |

## Reference basis

Saved searches and source artifacts are under `tests/references`.

Primary sources used to shape the plan:

- ECSS-E-ST-10-03C Rev.1: qualification/acceptance/protoflight testing, functional/performance tests, test procedures and reports.
- NASA GSFC-STD-7000B GEVS: tailored environmental verification, verification matrices, vibration/thermal/workmanship context.
- NASA-STD-8739.8B: software assurance, software safety, IV&V, traceability.
- CanSat Mission Guide 2025: telemetry/ground-station expectations, drop/thermal/vibration/vacuum tests, pre/post communications and mechanism demonstrations.
- HopeRF RFM95W data sheet: LoRa long-range modem, packet engine/CRC, RSSI/SNR-related evidence, SPI interface.
- NXP UM10204 I2C-bus specification: SDA/SCL, START/STOP, ACK/NACK, bus behavior.
- FreeRTOS documentation: queues, mutexes/semaphores, direct-to-task notifications, ISR/task synchronization, ESP32 task APIs.
- Reliability/tolerance interval references: exact binomial confidence and distribution-free tolerance interval methods.
- LoRa outdoor PDR literature: packet-delivery ratio depends on range, environment, antenna orientation/weather; PDR must be measured in the final test geometry.

## Test philosophy and statistics

1. **Trace every scenario to a model chain.** Each test below cites the view(s) it verifies and produces evidence that can close a verification matrix row.
2. **Use ECSS-style tailoring.** For this educational CanSat, the environmental levels are tailored from CanSat/GEVS practice; they are not a substitute for launcher-required qualification unless a launch provider accepts the tailoring.
3. **Binary success criteria use exact one-sided binomial confidence.** Record successes `k` out of trials `n`; for a required success probability `p_req`, pass only when the one-sided 95% Clopper-Pearson lower bound is at least `p_req`. Useful examples for `p_req = 0.90`:
   - 29/29 successes,
   - 58/59 successes,
   - 96/100 successes,
   - 114/120 successes,
   - 142/150 successes,
   - 188/200 successes,
   - 279/300 successes.
4. **Deadline/continuous limits use nonparametric one-sided tolerance bounds.** To claim at least 95% population coverage with 95% confidence for a limit such as "deployment command to servo actuation <= 5 s", collect at least 59 representative samples with all samples inside the limit. Fewer samples can still be used for engineering characterization but should not be reported as a 95/95 verification.
5. **Forbidden events are counted as failures.** Examples: a deployment in Standby, a state transition on an invalid command, an unreported critical fault, or a telemetry frame with a valid packet count but corrupt payload.
6. **Always log enough observables.** Minimum logs: test build/configuration, UTC/local time, OBCC state, packet counter, command counter, frame CRC/validity, decoded fields, health flags, RSSI/SNR if available, queue high-water marks, reset reason, deployment trigger time, servo command/position/current evidence.

## Test setup baseline

Use the same baseline for all scenario tests unless a test explicitly overrides it.

- Flight-like OBCC hardware: XIAO ESP32-S3, RFM95W, BME280, ICM20948, micro-servo/deployment load or calibrated non-flight load, GPS/INA219 when available, representative battery/PDS harness.
- Ground station: LoRa receiver, UART/USB bridge, PC decoder, dashboard, CSV logger.
- Instrumentation: logic analyzer for SPI/I2C/UART/PWM when needed, current/voltage logger, stopwatch or timestamped telemetry, optional FreeRTOS trace/diagnostic build, RSSI/SNR capture, servo position/current monitor.
- Safety: use a mechanical safe/arming plug or servo-load simulator for repeated deployment tests; never run destructive/armed tests when Standby-inhibit or invalid-command tests are being repeated.

## Scenario test corpus

Method codes: **I** inspection, **A** analysis, **D** demonstration, **T** test.

### Architecture and interface scenarios

| ID | Scenario | Views | Method | Evidence and pass criteria |
|---|---|---:|---|---|
| OBCC-T01 | Flight-like integrated OBCC matches the physical architecture. | PV physical | I/T | Inspect and photograph every modeled physical component and link. Continuity/polarity checks for power, I2C, UART, SPI, PWM, GPIO and LoRa antenna path. Pass: every required PC/PL is present or dispositioned; no shorts/reversed connectors; pre-functional telemetry received before scenario testing. |
| OBCC-T02 | Modeled communication exchanges are implemented with the intended protocols. | Physical, logical, functional allocation | A/T | For each CE/PL, capture a nominal transaction: I2C BME/IMU/INA, UART GPS, SPI LoRa, PWM servo, LoRa frame, ground UART, FreeRTOS queue/timer/ISR event. Pass: protocol, addressing, packet direction, units and timing match the model; no unmodeled serial-console control path is needed for v1.0 operations. |
| OBCC-T03 | Software task topology and shared-bus protection match the logical architecture. | Logical, runtime fault | A/T | Static review plus trace under load. Pass: modeled tasks/queues/timers/ISRs exist; shared buses are protected by mutex/critical sections as appropriate; no queue overflow, deadlock, watchdog reset or priority-inversion symptom during a mission-window run. |

### Startup health scenarios

| ID | Scenario | Views | Method | Evidence and pass criteria |
|---|---|---:|---|---|
| OBCC-T04 | Nominal power-up reaches an operational state and starts heartbeat/status telemetry. | Startup, telemetry | T | Power-cycle with all critical peripherals healthy. Pass for reliability claim: 29/29 clean boots for >=90% success at 95% confidence, or 59/59 if treating boot time/telemetry-start timing as a 95/95 tolerance claim. Each boot reports healthy criticals and emits telemetry without operator serial interaction. |
| OBCC-T05 | A critical startup peripheral fault prevents unsafe operation. | Startup, runtime fault | T | Inject missing/bad RFM95W, BME280, and servo feedback/command-path faults one at a time. Pass: fault is detected; health/status identifies it when the reporting path is available, otherwise local diagnostics/test-harness logs identify it; deployment cannot occur if the servo path is not verified; and the system enters the modeled error/safe state. Use 29/29 per critical fault class for a >=90%/95% claim. |
| OBCC-T06 | A non-critical startup peripheral fault enters degraded operation. | Startup, telemetry, runtime fault | T | Inject GPS, ICM20948 or INA219 faults one at a time. Pass: OBCC continues critical functions; disabled getter or invalid-value coding is visible in telemetry/status; heartbeat remains periodic. Use 29/29 per non-critical fault class for a >=90%/95% claim. |

### Telemetry and ground-station scenarios

| ID | Scenario | Views | Method | Evidence and pass criteria |
|---|---|---:|---|---|
| OBCC-T07 | Telemetry payload schema matches the v1.0 model. | Functional allocation, telemetry | A/T | Golden-frame and boundary-value tests for attitude, angular-rate, acceleration, altitude, temperature, battery voltage/current, state and health/status metadata. Pass: payload length and field order match the model, relative humidity is not present, invalid/missing data are encoded deterministically, CRC/status handling is documented. |
| OBCC-T08 | Telemetry is transmitted every 2 s in both On and Standby. | Telemetry, command/state | T | Measure inter-frame intervals in On and Standby at the ground station and, if possible, at the radio transmit call. Pass for 95/95 timing claim: >=59 consecutive intervals per mode inside the project tolerance. If no tighter tolerance is defined, use 2.0 s +/-10%; any missing scheduled transmit increment is a cadence failure, while RF losses are handled by the PDR test. |
| OBCC-T09 | LoRa downlink works at the modeled >=500 m range. | Physical, telemetry | T | Outdoor end-to-end test at >=500 m with final antenna mounting/orientation; log transmitted and received packet counts, RSSI/SNR, weather and geometry. Pass: exact binomial one-sided 95% lower bound for packet success is >=0.90; practical sample: at least 96/100 valid frames. Repeat after antenna/harness changes. |
| OBCC-T10 | Ground station receives, decodes, displays and stores telemetry. | Physical, telemetry, command/state | D/T | Feed at least 100 known-good and mixed-validity frames through the actual radio/UART path. Pass: packet counter continuity is preserved; valid frames are displayed/plotted and saved to CSV; invalid frames are rejected or flagged; decoded units are SI-compatible; no manual serial-console intervention is used. |
| OBCC-T11 | Telemetry continues in Standby; only deployment is inhibited. | Command/state, deployment gate, telemetry | T | Command Standby, then run a sensor/trigger profile that would otherwise request deployment. Pass: heartbeat/status and measurement telemetry continue at the 2 s cadence, state metadata says Standby, no deployment command is issued. Combine with OBCC-T16 for Standby false-deployment statistics. |

### Command/state scenarios

| ID | Scenario | Views | Method | Evidence and pass criteria |
|---|---|---:|---|---|
| OBCC-T12 | Valid wireless commands change On/Standby state and are reflected in telemetry. | Command/state, telemetry | T | From the dashboard, alternate On and Standby commands through the LoRa uplink. Pass: every valid command is received once, debounced/validated, applied to the state manager, and reported in following status telemetry. Use 29/29 valid command applications for a >=90%/95% claim. |
| OBCC-T13 | Invalid, corrupted, duplicate or out-of-context commands are rejected safely. | Command/state, runtime fault | T | Send malformed command frames, bad CRC, unsupported opcodes, duplicates/replays and commands during startup/error states. Pass: no unintended state transition or deployment; rejection is counted/logged in health/status. Recommended stress sample: 100 invalid frames with zero unsafe transitions. |
| OBCC-T14 | v1.0 has no required serial-console operator path. | Command/state, README/model constraints | I/D | Operate the system with only power, radio and ground station connected. Pass: all mission-required commands and observability are available over LoRa/telemetry; disconnecting USB serial after flashing does not remove a required operational function. |

### Deployment-gating scenarios

| ID | Scenario | Views | Method | Evidence and pass criteria |
|---|---|---:|---|---|
| OBCC-T15 | Startup and non-triggered runtime keep the parachute actuator closed. | Deployment gate, startup | T | Power-cycle and run normal telemetry/sensor profiles without trigger. Pass: servo is commanded/held closed, telemetry indicates no deploy event, no motion beyond allowed mechanical slack. For a 95/95 forbidden-event claim, collect 59 representative no-trigger intervals/trials with zero openings. |
| OBCC-T16 | Standby always inhibits parachute deployment. | Deployment gate, command/state | T | In Standby, inject trigger-equivalent sensor data or simulated trigger events using a safe servo load. Pass: zero deployment commands or servo openings; telemetry continues and reports inhibited/deployment-not-allowed status. Use 59 trials with zero openings for a 95/95 forbidden-event claim, or 29/29 for >=90%/95%. |
| OBCC-T17 | In On mode, a valid trigger deploys within 5 s. | Deployment gate, telemetry, runtime fault | T | In On, inject representative trigger conditions with timestamped trigger and servo actuation evidence. Pass for 95/95 timing claim: at least 59 representative trigger trials and every actuation <=5 s; telemetry reports the deployment event/status. If hardware wear limits repeated full-stroke tests, use an instrumented servo simulator for the statistical run and at least one flight-servo demonstration. |
| OBCC-T18 | Servo/actuator fault is handled as a critical deployment-path fault. | Startup, deployment gate, runtime fault | T | Disconnect/stall/load servo or inject PWM/position-command failure in a safe setup. Pass: fault is detected or bounded, no misleading "deployed" status is reported without actuation evidence, and the system enters the modeled safe/error state while telemetry preserves diagnosability. |

### Runtime fault-handling scenarios

| ID | Scenario | Views | Method | Evidence and pass criteria |
|---|---|---:|---|---|
| OBCC-T19 | Sensor getter timeout/error does not block the scheduler. | Runtime fault, telemetry, logical | T | Force I2C/UART/SPI NACK, timeout, stuck-bus, malformed sensor data and radio-busy conditions. Pass: getter returns within its configured timeout, error counters/health flags update, queues do not overflow, watchdog does not reset, and the next healthy sample clears or ages the fault as specified. For timeout limits, use 59 in-limit samples for 95/95. |
| OBCC-T20 | Runtime critical fault transitions to safe/error behavior. | Runtime fault, startup, telemetry | T | Induce runtime RFM95W, BME280 or servo critical faults after nominal startup. Pass: critical-fault state/status is emitted if the radio path remains available; unsafe deployment is prevented; recovery or latch behavior matches the model. Use 29/29 per critical fault class for >=90%/95% event success. |
| OBCC-T21 | Runtime non-critical faults produce degraded telemetry without losing core functions. | Runtime fault, telemetry | T | Induce GPS/ICM/INA transient and persistent failures. Pass: invalid fields/health flags are visible; heartbeat and command handling continue; no reset loop. Use 29/29 per fault class for >=90%/95% event success. |
| OBCC-T22 | End-to-end mission-window operation is stable. | All chains | T | Run a flight-like sequence: boot, health, Standby telemetry, command On, acquisition, >=500 m or RF-emulated downlink, trigger/no-trigger cases, command Standby, fault injection if safe. Duration: expected mission duration plus 20%; if unknown, use at least 30 min. Pass: no unexplained reset/deadlock, telemetry PDR meets OBCC-T09 criterion for the run, command/deployment timing criteria are met. |

### Environmental and readiness scenarios

| ID | Scenario | Views | Method | Evidence and pass criteria |
|---|---|---:|---|---|
| OBCC-T23 | Drop/shock handling does not break OBCC telemetry or actuator safety. | Physical, telemetry, deployment gate | T | Tailored CanSat drop/shock test in flight configuration, with battery and electronics secured. Pre/post: inspect mounts/connectors/antenna, verify telemetry and safe servo state. Pass: no loose/broken mounts, no unexpected deployment, and post-test functional tests pass. |
| OBCC-T24 | Hot-environment operation preserves telemetry and mechanism function. | Physical, telemetry, deployment gate | T | Tailored CanSat thermal test, e.g. hot chamber around 55-60 °C for the agreed duration when materials allow. Run or immediately repeat telemetry and mechanism checks while hot. Pass: no material deformation affecting fit/function; telemetry, command state, and servo demonstration pass after exposure. |
| OBCC-T25 | Vibration/workmanship exposure preserves connectors, radio and sensor operation. | Physical, logical, telemetry | T | Tailored vibration/workmanship test with the final harness and antenna. Pre/post and, if safe, during-test telemetry logging. Pass: no connector loosening, solder/harness damage, reset loop or lost sensor/radio function; post-test OBCC-T04/T08 spot checks pass. |
| OBCC-T26 | Vacuum/altitude-style deployment simulation is understood and safe. | Deployment gate, telemetry | T | Use a safe pressure/altitude simulator or vacuum chamber only if compatible with the complete CanSat design. Pass: telemetry remains interpretable, altitude/trigger logic behaves as expected, Standby inhibition remains active, and On-mode deployment criterion is met in the simulated profile. |
| OBCC-T27 | Flight readiness rehearsal closes the verification matrix. | All views | D/I | Rehearse the final field sequence with crew roles, checklist, ground station, antenna setup, battery verification, command path, data storage, and post-run artifact export. Pass: every scenario has pass/fail evidence or a signed waiver; residual risks are listed; latest diagram/model version is identified; no open safety-critical item remains. |

## Minimum artifacts per executed test

For each scenario, save:

1. Test procedure or checklist version.
2. Hardware/software configuration and model view revision.
3. Raw logs: telemetry CSV, command log, RF stats, diagnostic/trace logs, sensor/logic analyzer captures if used.
4. Photos/video for physical, deployment and environmental tests.
5. Pass/fail sheet with exact trial counts and binomial/tolerance calculation when applicable.
6. Anomaly reports with retest evidence and regression impact.

## Suggested verification matrix columns

If this corpus is expanded into a formal matrix, use these columns:

`Requirement / modeled behavior`, `View(s)`, `Scenario ID`, `Method`, `Procedure`, `Sample size`, `Acceptance criterion`, `Result`, `Evidence file(s)`, `Anomaly/waiver`, `Closed by`, `Date`.
