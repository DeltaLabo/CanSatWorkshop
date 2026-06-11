# PDM v1.0 test plan

Planning artifact for the Capella/D2 Physical Architecture views in `PDM/MBSE/v1.0`. The diagrams were read for traceability only and were not modified.

## 1. Model views read

Current test scope is **PDM v1.0**, because it is the canonical current architecture in `PDM/MBSE/README.md`.

- `PDM_v1.0_view1_physical.d2`: CanSat, ADS module, OBCC module, backplane PCB, parachute module, cap, parachute, servo, physical links.
- `PDM_v1.0_view2_logical.d2`: ADS kinematic sensing, ADS processing, OBCC, PDM processing, trigger, parachute holder, descent-speed control; I2C, PWM, torque exchanges.
- `PDM_v1.0_view3_functional_allocation.d2`: user preparation functions, IMU measurement/read/process functions, deployment decision, servo open/close functions, cap separation, parachute fold/unfold, descent-speed limiting; constraints: I2C timeout <= 5 ms, process/calculate < 5 ms, no blocking except I2C, initial servo = 0 deg, max parachute diameter = 30 cm.
- `PDM_v1.0_view4_imu_triggered_deployment_chain.d2`: IMU-triggered deployment chain; no manual/BLE open command.

Historical views were also read as prior scenario context: v0.1 contains a manual fall-test chain with **3 reps** and `11 m/s max`; v0.2 contains a manual/BLE deployment test with **3 reps**. These are treated as development-screening history, not as high-confidence qualification evidence.

## 2. Reference corpus

Saved sources are in `tests/references/sources`; search records are in `tests/references/search`; source index is in `tests/references/README.md`.

Reference IDs used below:

- R1-R4: ESA/Andoya/ESERO CanSat recovery and parachute guidance.
- R5: CanSat Mission Guide 2024a environmental/drop-test examples.
- R6-R7: ECSS verification and testing process standards.
- R8: NXP UM10204 I2C bus specification.
- R9-R10: ICM-20948 datasheet/product information.
- R11: Servo PWM timing reference.
- R12-R13: binomial confidence/reliability demonstration references.
- R14-R16: MIL-STD-810H environmental, vibration, and shock tailoring references.

## 3. Statistical policy

For pass/fail scenario tests with `n` independent trials and zero failures, use the exact binomial one-sided lower confidence bound:

```text
R_L = (1 - C)^(1/n)
n >= ceil(ln(1 - C) / ln(R_target))
```

Examples with zero failures:

| Trials `n` | Demonstrated reliability lower bound at 90% confidence |
| ---: | ---: |
| 3 | 46% |
| 5 | 63% |
| 10 | 79% |
| 22 | 90% |
| 100 | 97.7% |
| 1000 | 99.77% |

Use `3 reps` only as development screening. Use `10 reps` for workshop-level acceptance when hardware is scarce. Use `22 reps` where the scenario is critical and the team wants to demonstrate about 90% reliability at 90% confidence.

For measured quantities such as descent speed, latency, voltage, or PWM pulse width: keep raw per-trial data, compute min/mean/max and confidence intervals, but also classify each trial pass/fail against the stated limit and apply the binomial policy above.

## 4. Scenario-based test list

| ID | Scenario | Type | Main model trace | Method | Acceptance criteria | Statistical plan | Refs |
| --- | --- | --- | --- | --- | --- | --- | --- |
| PDM-T-001 | User folds/reintroduces parachute and places cap before launch. | Expected use case | `User.reintroduce_parachute`, `Fold`, `Place cap`, `Stay shut`; cap/parachute/servo PCs | Inspection + repeated repack/close cycles using flight-like parachute, cap, and servo. Measure deployed parachute diameter. | Parachute can be folded and reintroduced without damage; cap seats repeatably; deployed parachute diameter <= 30 cm; no side protrusion in stowed configuration. | 10 consecutive repack cycles per design build; inspect every flight article. | R1-R4, R6 |
| PDM-T-002 | Parachute/nylon-thread attachment survives opening load. | Feared event: attachment rupture | `Parachute`, `Nylon thread`, `Unfold`, `Limit terminal speed` | Static pull test or instrumented deployment-load test on engineering article; visual inspection after load. | No tear, knot slip, line failure, or anchor failure. If no project load is defined, tailor to mission-estimated peak opening load with margin; compare with ESA parachute-connection strength guidance. | Minimum 5 engineering pull tests; do not destructively overload the flight article unless required. | R1-R5, R16 |
| PDM-T-003 | Power-up sets servo to safe closed state. | Expected use case and feared premature deployment | `Set Servo init state`, `Reach closed position`, `Retain position`, `Stay shut`; constraint `Initial servo position = 0 degrees` | Power-cycle full stack with parachute packed and cap installed; observe servo angle and cap state. | Servo initializes to calibrated closed pulse/angle; cap remains closed; no open pulse before deployment condition. | 22 zero-failure power cycles for current software/hardware release. | R6-R7, R11, R13 |
| PDM-T-004 | ADS IMU data are read over I2C within the timing budget. | Expected use case | `Respond to I2C Requests`, `Read angular velocities`, `Read accelerations`, `Read field intensities`; constraint `I2C read timeout <= 5 ms` | Logic analyzer on SCL/SDA and firmware timestamps during continuous reads. Verify bus speed and ACK/NACK behavior. | Each I2C read completes or times out within <= 5 ms; bus rate within selected standard/fast-mode limits; no blocking operation outside allowed I2C wait. | 1000 read cycles with zero timing failures gives 99.77% lower bound at 90% confidence for per-read success. | R8-R10, R12-R13 |
| PDM-T-005 | IMU health and calibration are adequate before arming deployment. | Expected use case / feared bad sensor | ICM-20948 PC; `Measure angular velocities`, `Measure accelerations`, `Measure magnetic field intensities`, `Calculate pitch, roll, yaw` | Run ICM-20948 self-test where available; static 6-orientation accelerometer check; gyro stillness bias check; magnetometer plausibility check away from strong magnetic disturbances. | Self-test passes datasheet limits; static acceleration norm is plausible; gyro bias remains within project threshold; bad/missing sensor does not arm deployment. | At least 10 power-up health checks per integrated unit; record bias/offset distributions. | R8-R10, R12 |
| PDM-T-006 | ADS processing detects the true deployment condition. | Expected use case | `Process angular velocities`, `Process accelerations`, `Calculate pitch, roll, yaw`, `Collect measurements`, `Evaluate deployment condition` | Replay recorded or simulated IMU profiles through flight software; include nominal descent, non-deploy handling, and threshold-crossing cases. | True deployment profiles trigger exactly once; non-deploy profiles do not trigger; process/calculate functions each take < 5 ms. | 22 positive trigger trials and 22 negative trials for critical threshold set; expand with regression profiles after algorithm changes. | R6-R7, R9-R13 |
| PDM-T-007 | No manual/BLE command can deploy PDM v1.0. | Feared event / regression from v0.2 | Chain note `No manual/BLE open command`; no BLE function in v1.0 chain | Firmware/interface review plus black-box attempts to send historical v0.2 manual/BLE open command or equivalent debug commands. | No manual/BLE command path can produce `Send open signal to Servo` in flight mode; any debug command is disabled or gated by a ground-test-only mode. | Review every release; 22 black-box no-open attempts if interface exists. | R6-R7, v0.2 views |
| PDM-T-008 | PWM command drives servo to open and closed calibrated positions. | Expected use case | `Send open signal to Servo`, `Send close signal to Servo`, `Reach open position`, `Reach closed position`, `Retain position`; CE/FE `PWM` | Oscilloscope/logic analyzer on PWM trace; position gauge or video on servo/cap; test under representative cap load. | PWM period about 20 ms / 50 Hz; high pulse widths match calibrated closed/open values; servo reaches and retains the commanded position; no brownout or excessive jitter. | 22 open/close cycles with zero actuation failures. | R7, R11, R12-R13 |
| PDM-T-009 | Full IMU-triggered deployment chain succeeds on the ground. | Expected use case | v1.0 functional chain from IMU measurement to `Limit terminal speed` | Full stack test with packed parachute: inject real/replayed IMU trigger, observe PWM, servo, cap separation, parachute extraction/unfolding. | Chain completes in order; no manual command involved; parachute clears holder; all logged timing limits met. | 10 development trials minimum; 22 trials if used as release qualification evidence. | R1-R7, R9-R13 |
| PDM-T-010 | Deployed parachute limits terminal descent speed. | Expected use case / mission performance | `Unfold`, `Limit terminal speed`; historical v0.1 `11 m/s max` | Drop tower, drone drop, balloon drop, or safe equivalent with final CanSat mass. Measure speed by video/altimeter over terminal segment after deployment transient. | Terminal descent speed within project requirement. Default from CanSat references: 8-11 m/s; at minimum, satisfy the model's `11 m/s max` historical constraint unless a newer requirement replaces it. | 10 measured drops for acceptance screening; 22 if demonstrating 90% reliability at 90% confidence. All individual drops must pass. | R1-R5, R12-R13 |
| PDM-T-011 | Deployment shock/drop does not damage PDM or disconnect links. | Feared event | Physical links: servo cable, backplane fixtures, connectors, nylon thread; functions before/after shock | CanSat-style drop/shock test in flight configuration, followed by full functional test. The CanSat Mission Guide example uses a 61 cm cord and states the drop generates about 30 g shock. | No component detaches; cap/parachute/servo links intact; connectors remain seated; post-shock PDM-T-003, T-004, and T-008 still pass. | 3 engineering trials minimum; one acceptance shock test per flight article if competition process requires it. Do not claim high reliability from only 3 reps. | R5-R7, R16 |
| PDM-T-012 | Launch/transport vibration does not loosen mounts or break electrical links. | Feared event | ADS/OBCC/backplane/parachute module physical links; I2C and PWM paths | Tailored vibration test: CanSat guide sweep example or MIL-STD-810H Method 514.8 category tailored to expected transport/launch environment. Functional test before, during if safe, and after. | No fastener/connector loosening; no solder/cable failure; I2C/PWM remain functional; full deployment chain still passes after vibration. | Environmental qualification is normally article-limited: test at least one qualification article; inspect and acceptance-test every flight article. | R5-R7, R14-R15 |
| PDM-T-013 | Servo current transient does not brown out OBCC/ADS/IMU. | Feared event | `3V3 power traces`, servo cable `(PWM + 5V)`, `Set Servo init state`, `Send open signal to Servo` | Instrument 5 V servo rail, 3V3 rail, MCU reset line, and I2C bus while commanding servo under cap load. | No MCU reset; 3V3 remains within electronics limits; I2C reads continue or timeout cleanly <= 5 ms; servo reaches required position. | 100 open/close cycles with voltage logging; zero brownouts gives 97.7% lower bound at 90% confidence. | R7-R11, R13 |
| PDM-T-014 | I2C bus or IMU fault fails safe. | Feared event | I2C CE, `Read*` functions, `Evaluate deployment condition`, timeout/no-blocking constraints | Inject NACK, disconnected IMU, stuck SDA, stuck SCL, delayed response/clock stretching if applicable. | Flight software times out <= 5 ms per read, records sensor fault, does not trigger deployment from invalid data, and recovers or enters defined safe state. | 10 trials per fault class; 22 for any fault class considered mission-critical. | R6-R10, R12-R13 |
| PDM-T-015 | Servo/cap jam fails safe and is diagnosable. | Feared event | `Reach open position`, `Retain position`, `Separate from Module`, cap/servo rotating link | Mechanically restrict cap/servo movement and command open/close while measuring current, PWM, and state/log outputs. | No repeated over-current heating; no reset; failure is logged or otherwise observable; if cap cannot open, system remains safe and does not claim successful deployment. | 10 jam trials using engineering article; inspect for damage after each. | R6-R7, R11, R13, R16 |
| PDM-T-016 | Post-deployment recovery and repack supports repeated tests. | Expected use case | `Reintroduce parachute`, `Fold`, `Send close signal`, `Reach closed position`, `Place cap` | After a deployment test, recover, close servo, fold/reintroduce parachute, place cap, and rerun preflight checks. | No wear that prevents repack; cap closes; servo closed state passes; next deployment chain can execute. | 10 full recover/repack cycles on engineering unit. | R1-R4, R6-R7 |

## 5. Execution order

1. **Inspection and bench setup:** PDM-T-001, PDM-T-003, PDM-T-004, PDM-T-005.
2. **Software and signal tests:** PDM-T-006, PDM-T-007, PDM-T-008, PDM-T-014.
3. **Actuation and full-chain ground tests:** PDM-T-009, PDM-T-013, PDM-T-015, PDM-T-016.
4. **Environmental and mechanical qualification:** PDM-T-011, PDM-T-012.
5. **Drop/descent performance:** PDM-T-010.
6. **Flight readiness regression:** rerun PDM-T-003, PDM-T-004, PDM-T-008, and one non-destructive end-to-end deployment check on the final packed configuration, as allowed by operations.

## 6. Data to archive per test

For each test run, save:

- test ID, hardware serial/configuration, firmware commit, date, operator;
- pass/fail outcome and failure mode classification;
- raw timing traces for I2C/PWM/processing tests;
- voltage/current logs for power tests;
- video and speed extraction spreadsheet for descent tests;
- photos before/after shock/vibration/drop tests;
- computed binomial lower confidence bound for scenario pass probability when repeated trials are used.
