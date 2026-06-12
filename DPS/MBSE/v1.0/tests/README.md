# DPS v1.0 Physical Architecture test plan

Planning artifact for the Capella/D2 Physical Architecture views in `DPS/MBSE/v1.0/`. The diagrams were read for traceability only and were not modified.

Project-wide IVV conventions, statistics, rate terminology, fault semantics, and artifact paths are defined in [`../../../../PM&SE/IVV.md`](../../../../PM&SE/IVV.md). For v1.0 flight operations, `2 s` is the OBCC LoRa heartbeat/status/measurement telemetry cadence; 5 Hz DPS tests are lab/performance stress cases unless a modeled chain explicitly requires a 5 Hz payload path.

## 1. Model views read

Current test scope is **DPS v1.0**, because `DPS/README.md` identifies it as the full Capella XML-to-D2 architecture. The older v0.1 and v0.2 folders are hardware-downgraded/development variants; v0.1 already has its own test plan.

- `DPS_v1.0_view1_physical.d2`: CanSat with OBCC module/PCB, RFM95W LoRa, XIAO ESP32-S3, backplane connector; ground-station PCB with RFM95W and XIAO ESP32; PC USB port; SPI traces, 5 V traces, USB-C cable; 500 m maximum separation; ground-station PCB reuses the OBCC PCB with backplane connector not soldered.
- `DPS_v1.0_view2_logical.d2`: CanSat LoRa transceiver and OBCC plus ESS/ADS/PDM/AMS processing on the CanSat XIAO; ground LoRa forwarder; PC decoder, CSV writer, dashboard, USB power; SPI, UART, payload, and command exchanges; concurrent PC execution; browser-accessible dashboard.
- `DPS_v1.0_view3_functional_allocation.d2`: LoRa RX/TX, forwarder init/read/write/error functions, PC decode/timestamp/latency/queue functions, CSV append, dashboard plots/commands/cooldown/alert, USB power; constraints for unique CSV name, latency alert > 1 s, 5 s cooldown, 4x4 plot matrix with 3D plot top-left, concurrent execution, browser accessibility, and 500 m separation.
- `DPS_v1.0_view4_downlink_processing_chain.d2`: downlink storage, RX interrupt, read payload, forward to PC, UART availability, decode, timestamp, latency, payload queue, CSV consume/append, and read-error logging.
- `DPS_v1.0_view5_command_uplink_chain.d2`: dashboard state toggle, command queue, decoder/forwarder UART path, frame generation, LoRa radio write/transmit, and 5 s UI cooldown.
- `DPS_v1.0_view6_cansat_receive_chain.d2`: CanSat LoRa receive interrupt and OBCC command read.
- `DPS_v1.0_view7_cansat_transmit_chain.d2`: OBCC send LoRa packet and CanSat LoRa transmit.
- `DPS_v1.0_view8_dashboard_visualisation_chain.d2`: payload queue to dashboard, plot creation/update, latency alert, concurrent execution, browser access.
- `DPS_v1.0_view9_forwarder_initialisation_chain.d2`: Serial0 init, SPI init, and init-error logging.

## 2. Reference corpus

Saved source artifacts are in `tests/references/sources`; search records are in `tests/references/searches`; source index is `tests/references/INDEX.md`.

Reference IDs used below:

- **R1-R3:** ECSS-E-ST-10-03C Rev.1 and ISO/IEC/IEEE 29119-2/3 for test planning, functional/performance tests, and documentation.
- **R4-R5:** NIST/SEMATECH binomial proportion and sample-size guidance.
- **R6-R10:** ETSI/TTN regional radio constraints and RFM95W/SX1276/LoRa technical references.
- **R11-R13:** CanSat telemetry, ground-station, and radio-test guidance.
- **R14-R15:** LoRa path-loss/PDR measurement literature.

## 3. Statistical policy

Apply the project-wide policy in [`../../../../PM&SE/IVV.md`](../../../../PM&SE/IVV.md) unless a scenario states a stricter criterion.

For binary scenario outcomes such as received frames, decoded frames, accepted commands, rejected corrupt frames, and successful restarts:

- Record `N`, successes, failures, and the one-sided 95% exact binomial / Clopper-Pearson lower confidence bound for success probability.
- Useful zero-failure planning points at 95% confidence: `29/29` supports R90/C95, `59/59` supports about R95/C95, `300/300` supports about R99/C95.
- For PDR claims, pass only when the exact lower bound meets the required PDR.

For continuous outcomes such as latency, inter-arrival time, RSSI, SNR, CPU load, memory use, queue depth, and voltage: retain raw logs and report min/mean/median/p95/max. Use 59 representative in-limit samples for 95/95 deadline claims. Do not assume all high-rate frame samples are statistically independent; use them for performance evidence and use independent restarts/fault injections for reliability claims.

## 4. Scenario-based test list

| ID | Scenario | Type | Main model trace | Method | Acceptance criteria and statistical plan | Refs |
| --- | --- | --- | --- | --- | --- | --- |
| DPS-T-001 | Assembled DPS v1.0 powers up safely and all local electrical interfaces are present. | Expected use case | Views 1-3: USB-C, USB power, SPI traces, RFM95W modules, XIAO boards, PC USB port | Inspect antennas, USB-C cable, PCB footprints, SPI wiring/traces, 5 V traces, and USB enumeration. Power-cycle PC/ground/CanSat chain. Verify both RFM95W devices respond over SPI. | 10 power cycles with zero unsafe behavior; no radio transmit without antenna; all local interfaces detected every cycle. | R1, R8-R13 |
| DPS-T-002 | Ground-station PCB reuse is correct and the backplane connector is not populated. | Feared event / integration | View 1-3 constraint: ground-station PCB reuses OBCC PCB; backplane connector not soldered | Visual inspection and continuity checks on each ground-station PCB; verify only ground-station XIAO/RFM/USB paths are active. | Inspect every ground-station article; zero unintended backplane population, shorts, or external loads. | R1, R8 |
| DPS-T-003 | Ground forwarder initializes Serial0 and SPI successfully. | Expected use case | View 9: `Init Serial0 with interrupts` -> `Init SPI with interrupts` | Restart ground station and verify Serial0 IRQ, SPI IRQ, and LoRa register access. | 60 independent restarts with zero init failures demonstrates about 95% init success lower bound at 95% confidence. | R1-R5, R8 |
| DPS-T-004 | Ground forwarder reports initialization faults instead of silently operating. | Feared event | View 9: `Init SPI with interrupts` -> `Log error` | Inject missing/miswired radio, SPI fault, and UART unavailable cases. | 20 trials per fault class; 100% produce an error log and no false ready state. | R1-R3, R8 |
| DPS-T-005 | CanSat transmit path emits valid LoRa frames when OBCC provides a packet. | Expected use case | View 7: `Send LoRa packet` -> `Transmit outgoing data` | Unit/integration test with timestamped payloads and near-field receiver; include radio-ready checks. | 60 transmissions, zero missing sequence numbers at receiver; no buffer overrun; no TX while radio not ready. | R8-R12 |
| DPS-T-006 | DPS receives, decodes, stores, and timestamps OBCC telemetry at the v1.0 flight cadence. | Expected use case / performance | Views 4 and 7; `Forward to PC`, `Read and decode frame`, `Append to CSV`; OBCC telemetry cadence = 2 s | Send timestamped payload frames at 2 s cadence from CanSat to ground station to PC for at least 10 min; optionally repeat at 5 Hz as a lab stress/performance margin test. | Flight-cadence run: `N≥300`; decoded+stored success lower 95% bound >= 0.95; CSV row count equals accepted decoded frames; p95 end-to-end latency < 1 s. Optional 5 Hz stress is reported separately. | R1-R5, R8-R15 |
| DPS-T-007 | 500 m CanSat-to-DPS separation is achievable under legal radio settings. | Expected use case / boundary | Views 1-3 constraint: max separation 500 m | Field test at 500 m line-of-sight or controlled RF equivalent path loss; log RSSI/SNR, packet sequence, antennas, frequency, bandwidth, SF, coding rate, TX power. | `N=300`; PDR lower 95% bound >= 0.95; no sustained outage > 1 s in nominal conditions; radio settings comply with local regulations. | R6-R15 |
| DPS-T-008 | Corrupt or unreadable downlink frames are rejected and logged. | Feared event | View 4: `Read payload` -> `Log error`; `Read and decode frame` | Inject bad CRC, truncated payload, invalid field count, bad timestamp, non-numeric/out-of-range values, and wrong sync/frequency frames. | 60 corrupt frames per class; zero corrupt frames enter payload queue, CSV, or dashboard; every rejection logged with reason. | R1-R5, R8-R11 |
| DPS-T-009 | CSV files are uniquely named and preserve all accepted payloads. | Expected use case | Views 3-4: `Append to CSV`; constraint unique name based on initial timestamp | Start 10 logging sessions, including rapid back-to-back starts; feed known payload sequences. | Zero overwritten files; filenames unique; row order monotonic by receive timestamp; row count/checksum matches accepted payloads. | R1-R3 |
| DPS-T-010 | Dashboard is browser-accessible and displays required real-time plots. | Expected use case | Views 3 and 8: `Create plots`, temperature/humidity/altitude/orientation plots, browser constraint, 4x4 matrix note | Feed known payloads covering temperature, relative humidity, altitude, pitch/roll/yaw, and latency; open dashboard in a standard browser. | `N=300`; 100% accepted payloads appear in correct plot; 4x4 plot matrix exists; 3D plot is top-left; p95 display update latency < 1 s. If a requirement still expects a 3D altitude model while the PA says 3D orientation, raise a requirement/model discrepancy. | R1-R3, R11-R13 |
| DPS-T-011 | Latency alert activates only when latency is greater than 1 s. | Feared event / threshold | Views 3 and 8: `Update latency alert`; constraint `Latency > 1s` | Inject payloads with computed latencies below, equal to, and above 1 s. | 30 payloads per threshold class; no alert for `<= 1.0 s`; visible top alert for `> 1.0 s`; no false negatives above threshold. | R1-R5 |
| DPS-T-012 | Dashboard state toggle creates a valid uplink command that reaches the CanSat. | Expected use case | Views 5-6: toggle -> command queue -> UART -> LoRa TX -> CanSat RX/read command | Trigger 60 state toggles separated by more than cooldown; observe command frame and interpreted state at CanSat. | 60 commands, zero wrong state, zero duplicates; command success lower bound about 95% at 95% confidence; p95 command latency < 1 s where radio settings allow. | R1-R5, R8-R12 |
| DPS-T-013 | Toggle cooldown prevents command spam. | Feared event | View 5: `Disable toggle` -> `Cooldown` -> `Enable toggle`; constraint 5 s | Rapid-click/toggle during cooldown; repeat after exactly 5 s. | 30 bursts; only first toggle in each burst enqueues a command; UI disabled during cooldown; re-enabled at `5.0 s ± 0.5 s`. | R1-R3 |
| DPS-T-014 | CanSat receive path extracts command frames only after valid LoRa RX indication. | Expected use case / feared stale command | View 6: `Receive incoming data` -> `Receive LoRa RX Interrupt` -> `Read command` | Send valid command frames; separately spoof/no-frame interrupts and old-buffer conditions. | 60 valid commands accepted; 60 spoof/no-frame cases rejected; no stale command is re-read. | R1-R5, R8-R12 |
| DPS-T-015 | Decoder, CSV writer, and dashboard remain stable under concurrent sustained load. | Expected use case / stress | Views 2-4 and 8: concurrent decoder/CSV/dashboard execution | Replay or generate a 5 Hz payload stream for 20 min while dashboard is open and CSV is writing. | `N=6000` frames; no process crash; queue backlog returns to zero; p95 pipeline latency < 1 s; memory growth bounded and explained. | R1-R5 |
| DPS-T-016 | USB/UART interruption is handled without corrupting state. | Feared event | Views 1-5: USB-C cable, UART CE, `Check if data is available`, `Forward to PC` | Disconnect USB/UART for 10 s during a 2 s flight-cadence telemetry stream; optionally repeat during 5 Hz lab stress, reconnect, and continue. | 10 interruptions; decoder does not crash; CSV remains parseable; dashboard indicates stale/no data; stream resumes without duplicate timestamps. | R1-R3, R11-R13 |
| DPS-T-017 | Co-channel and near-channel RF traffic does not create accepted false payloads or commands. | Feared event | LoRa transceiver functions and 500 m/radio constraints | Operate a second LoRa transmitter with wrong sync word and at frequencies separated by at least 100 kHz; then test deliberate same-channel interference. | 300 foreign frames; zero false accepted payloads/commands. Same-channel interference may reduce PDR but must be measured and reported, not silently misdecoded. | R6-R15 |
| DPS-T-018 | Radio configuration is legal and compatible with flight cadence and any lab stress rate. | Feared event / compliance | Views 1-7 LoRa links; 2 s OBCC telemetry cadence; regional radio references | Compute time-on-air, payload size, frequency/channel, EIRP/ERP, antenna gain, bandwidth/SF/coding rate, and duty cycle for the selected local band. | Configuration complies with applicable regional regulation before over-the-air tests at the 2 s flight cadence. If 5 Hz stress airtime exceeds legal duty cycle, run 5 Hz performance tests only in cabled/attenuated/shielded lab setup. | R6-R10 |
| DPS-T-019 | Shared CanSat XIAO processing does not starve DPS LoRa handling. | Feared event / integration | View 2: OBCC plus ESS/ADS/PDM/AMS processing allocated to XIAO ESP32-S3; Views 4/7 LoRa chains | Run 2 s flight-cadence telemetry while representative ESS/ADS/PDM/AMS internal tasks execute at expected rates; log CPU time, ISR latency, queue depth, and dropped frames. Optionally repeat with 5 Hz lab stress. | Flight-cadence run: `N≥300`; no missed LoRa IRQ due to processing load; p95 transmit/receive service latency within budget for <1 s end-to-end pipeline. Optional 5 Hz stress is reported separately. | R1-R5, R8-R13 |
| DPS-T-020 | Power loss and recovery leaves the system in a defined safe state. | Feared event | View 3: USB power, PC/ground/CanSat functions; all chains | Remove/reapply PC USB power and CanSat power during idle, downlink, and command-uplink operations. | 10 trials per operating state; no partial command falsely executed; CSV remains parseable; software restarts to a known state and resumes after reinitialization. | R1-R3, R11-R13 |

## 5. Recommended execution order

1. **Inspection and bench bring-up:** DPS-T-001, DPS-T-002, DPS-T-003, DPS-T-004.
2. **Radio/packet path unit tests:** DPS-T-005, DPS-T-008, DPS-T-014.
3. **End-to-end nominal flows:** DPS-T-006, DPS-T-009, DPS-T-010, DPS-T-012.
4. **Thresholds, concurrency, and shared-load tests:** DPS-T-011, DPS-T-013, DPS-T-015, DPS-T-019.
5. **Fault and recovery tests:** DPS-T-016, DPS-T-020.
6. **RF environment and compliance:** DPS-T-017, DPS-T-018, then DPS-T-007 at 500 m or equivalent path loss.

## 6. Evidence to archive per test

For each test run, save evidence under `results/<test-id>/` inside this `tests/` folder:

- test ID, diagram version (`DPS v1.0`), hardware serial/configuration, software/firmware commit or hashes, date, operator;
- radio settings: frequency, bandwidth, spreading factor, coding rate, sync word, TX power, antenna type/gain, cable/attenuator losses;
- raw frame log with sequence number, TX timestamp, RX timestamp, RSSI/SNR if available;
- decoded payload log, CSV output, dashboard screenshots/video where relevant;
- command/uplink log for command tests;
- fault-injection description for feared-event tests;
- pass/fail outcome, failure mode classification, raw continuous measurements, and binomial confidence calculation where repeated trials are used.
