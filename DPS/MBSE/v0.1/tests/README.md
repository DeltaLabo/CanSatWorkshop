# DPS v0.1 Physical Architecture test plan

This plan is derived from the Capella/D2 Physical Architecture views in `DPS/MBSE/v0.1/`. The diagrams themselves were not modified.

Project-wide IVV conventions, statistics, rate terminology, fault semantics, and artifact paths are defined in [`../../../../PM&SE/IVV.md`](../../../../PM&SE/IVV.md). DPS v0.1 is an incremental-delivery baseline; its 5 Hz radio/PC stream tests are development performance checks and do not change the v1.0 OBCC `2 s` flight telemetry cadence.

## Scope read from the MBSE views

- **Physical links:** datalogger circuitboard (`XIAO ESP32-S3` + `RFM95W LoRa`), ground-station circuitboard (`XIAO ESP32` + `RFM95W LoRa`), and PC connected through USB-C; maximum datalogger-to-ground-station separation is **500 m**.
- **Logical chain:** LoRa transceivers exchange payload/command frames; the ground forwarder bridges LoRa/SPI to PC/UART; the PC decoder feeds CSV writer and dashboard concurrently.
- **Functional chains:**
  - downlink decode/storage,
  - dashboard command uplink,
  - datalogger receive path,
  - datalogger transmit path,
  - dashboard visualisation,
  - forwarder initialisation.
- **Architectural constraints:** 5 s command-toggle cooldown; text alert when latency is `> 1 s`; unique CSV name based on initial timestamp; browser-accessible dashboard; concurrent decoder/CSV/dashboard execution.

## Reference basis

The retrieved reference corpus is in [`references/`](./references/):

- ECSS-E-ST-10-03C Rev.1: testing programme, functional/performance test discipline, test specification/report documentation.
- ISO/IEC/IEEE 29119-2 and 29119-3: software test processes and test documentation templates.
- NIST/SEMATECH e-Handbook: binomial proportion tests and sample-size rationale.
- ETSI EN 300 220 and TTN EU868 notes: short-range device spectrum/duty-cycle/EIRP constraints where EU863-870 operation applies.
- Semtech SX1276 / HopeRF RFM95W / LoRa AN1200.22: LoRa radio capability, SPI interface, link budget, sensitivity, and payload limits.
- CanSat/Andøya references: CanSat telemetry, ground-station, radio test, and operational readiness practices.
- Callebaut & Van der Perre 2020: empirical LoRa point-to-point path-loss/PDR evidence.

## Statistical treatment

Apply the project-wide policy in [`../../../../PM&SE/IVV.md`](../../../../PM&SE/IVV.md) unless a scenario states a stricter criterion.

For binary outcomes such as received frames, decoded frames, accepted commands, and rejected corrupt frames:

- Record `N`, successes, failures, and the one-sided 95% exact binomial / Clopper-Pearson lower confidence bound for success probability.
- Useful zero-failure planning points at 95% confidence: `29/29` supports R90/C95, `59/59` supports about R95/C95, and `300/300` supports about R99/C95.
- For PDR claims, pass only when the exact lower bound meets the required PDR.

For continuous outcomes such as latency, inter-arrival time, RSSI/SNR, CPU/memory, and queue depth, retain raw logs and report min/mean/median/p95/max; use 59 representative in-limit samples for 95/95 deadline claims.

## Planned tests, one per scenario

| ID | Scenario | Type | Diagram trace | Test to perform | Statistical/pass criteria |
|---|---|---|---|---|---|
| DPS-T-001 | Assembled v0.1 physical system powers up and all local interfaces are present. | Expected use case | Views 1-3: USB-C, SPI, PC, LoRa modules, USB power. | Inspect wiring, antennas, USB-C cable, SPI wiring; power-cycle the PC/ground/datalogger chain; verify ground XIAO enumerates and both RFM95W devices respond over SPI. | 10 power cycles, zero unsafe behavior; all interfaces detected every cycle; no radio TX without antenna. |
| DPS-T-002 | Ground forwarder initialises Serial0 and SPI successfully. | Expected use case | View 9: `Init Serial0 with interrupts` → `Init SPI with interrupts`. | Restart the ground station and verify Serial0 IRQ, SPI IRQ, and LoRa radio register access. | 60 restarts, zero init failures to demonstrate at least 95% init success at 95% confidence. |
| DPS-T-003 | Forwarder reports initialisation failure instead of silently operating. | Feared event | View 9: `Init SPI with interrupts` → `Log error`. | Disconnect or misconfigure SPI/radio, then start the forwarder. Repeat with UART unavailable. | 20 trials per injected fault; 100% of trials produce an error log and no false “ready” state. |
| DPS-T-004 | Datalogger telemetry reaches PC decoder and CSV storage at the required processing rate. | Expected use case | View 4 and View 7: `Send LoRa packet`, `Store incoming data`, `Read payload`, `Forward to PC`, `Read and decode frame`, `Append to CSV`. | Send timestamped payload frames at **5 Hz** for 60 s from datalogger to ground station to PC. | `N = 300`; decoded+stored PDR lower 95% bound ≥ 0.95; p95 end-to-end latency < 1 s; CSV row count equals accepted decoded frames. |
| DPS-T-005 | The 500 m datalogger-to-ground-station separation is achievable. | Expected use case / boundary | View 1-3 constraint: max separation 500 m. | Field-test or controlled RF-link test at 500 m equivalent path loss; record RSSI/SNR, PDR, radio settings, antenna setup, and legal TX duty cycle. | `N = 300`; PDR lower 95% bound ≥ 0.95; no sustained outage > 1 s under nominal line-of-sight conditions; RF settings comply with local band rules. |
| DPS-T-006 | Corrupt or unreadable downlink frames are rejected and logged. | Feared event | View 4: `Read payload` → `Log error`; `Read and decode frame`. | Inject frames with bad CRC, truncated payload, invalid field count, bad timestamp, and out-of-range numeric values. | 60 corrupt frames per class; zero corrupt frames enter payload queue/CSV/dashboard; every rejection is logged with reason. |
| DPS-T-007 | Dashboard displays real-time payload data in the required plots. | Expected use case | View 8: payload queue → dashboard plots; View 3 UI functions. | Feed known payloads covering temperature, humidity, altitude, pitch/roll/yaw, and latency; open dashboard in a browser. | `N = 300`; 100% accepted payloads appear in the correct plot; 4x4 plot matrix exists; 3D orientation plot is top-left; p95 display update latency < 1 s. |
| DPS-T-008 | Dashboard latency alert activates only when latency exceeds 1 s. | Feared event / threshold | View 8 and View 3: `Update latency alert`, constraint `Latency > 1s`. | Inject payloads with computed latencies below, equal to, and above 1 s. | 30 payloads per threshold class; no alert for `<= 1.0 s`; alert shown at top for `> 1.0 s`; no false negative above threshold. |
| DPS-T-009 | CSV files are uniquely named and preserve all accepted payloads. | Expected use case | View 3/4 constraint: unique CSV name based on initial timestamp; `Append to CSV`. | Start 10 independent logging sessions, including two starts within the same second if possible; feed known payload sequence. | Zero overwritten files; filenames unique; row order monotonic by RX timestamp; checksum/row count matches accepted payloads. |
| DPS-T-010 | Dashboard state toggle creates a valid uplink command that reaches the datalogger. | Expected use case | View 5 and View 6: toggle → command queue → UART → forwarder → LoRa TX → datalogger receive/read command. | Trigger 60 user state toggles separated by more than the cooldown period; observe command frame at datalogger. | 60 commands, zero wrong state and zero duplicates; command success lower bound ≥ 0.95; p95 command latency < 1 s where radio settings allow. |
| DPS-T-011 | Toggle cooldown prevents command spam. | Feared event | View 5: `Disable toggle` → `Cooldown` → `Enable toggle`, constraint `5 seconds`. | Rapidly click/toggle during cooldown; repeat after exactly 5 s. | 30 bursts; only first toggle in each burst enqueues a command; UI disabled during cooldown; re-enabled at `5.0 s ± 0.5 s`. |
| DPS-T-012 | Datalogger receive path extracts command frames only after LoRa RX indication. | Expected use case | View 6: `Receive incoming data` → `Receive LoRa RX Interrupt` → `Read command`. | Send valid command frames and separately assert/spoof interrupts without valid frames. | 60 valid commands accepted; 60 spoof/no-frame interrupts rejected; no stale command is re-read. |
| DPS-T-013 | Datalogger transmit path sends LoRa frames when a packet is provided. | Expected use case | View 7: `Send LoRa packet` → `Transmit outgoing data`. | Unit/integration test datalogger transmit function with timestamped payloads and radio TX-ready checks. | 60 transmissions; zero missing sequence numbers at a near-field receiver; no buffer overrun; no transmit attempt while radio not ready. |
| DPS-T-014 | PC decoder, CSV writer, and dashboard remain stable under concurrent sustained load. | Expected use case / stress | View 2/3 constraints: concurrent decoder, CSV writer, dashboard. | Replay or generate a 5 Hz payload stream for 20 min while dashboard is open and CSV is writing. | `N = 6000`; no process crash; queue backlog returns to zero; p95 pipeline latency < 1 s; memory growth bounded and explainable. |
| DPS-T-015 | USB/UART interruption is handled without corrupting state. | Feared event | Views 1-5: USB-C, UART CE, `Check if data is available`, `Forward to PC`. | Disconnect USB/UART for 10 s during a 5 Hz stream, then reconnect. | 10 interruptions; decoder does not crash; CSV remains parseable; dashboard indicates stale/no data; stream resumes without duplicate timestamps. |
| DPS-T-016 | Co-channel/near-channel RF traffic does not produce accepted false payloads. | Feared event | LoRa transceiver functions; separation/radio constraints. | Operate a second LoRa transmitter on wrong sync word and on frequencies separated by at least 100 kHz; then test deliberate same-channel interference. | 300 foreign frames; zero false accepted payloads/commands. Same-channel interference may reduce PDR, but degradation is measured and reported rather than silently misdecoded. |
| DPS-T-017 | Radio configuration is legal and compatible with payload rate. | Feared event / compliance | Views 1-7 LoRa links; source standards. | Compute time-on-air, payload size, channel, EIRP/ERP, duty cycle, and antenna gain for chosen local band. | Configuration complies with the applicable regional regulation before over-the-air tests. If 5 Hz LoRa airtime exceeds legal duty cycle, perform 5 Hz performance tests in cabled/attenuated lab setup and field tests at legal airtime. |

## Evidence to archive per test

For each test run, save evidence under `results/<test-id>/` inside this `tests/` folder:

- diagram version (`DPS v0.1`) and test ID,
- firmware/software commit or file hashes,
- radio settings: frequency, bandwidth, spreading factor, coding rate, TX power, antenna type,
- raw frame log with sequence number, TX timestamp, RX timestamp, RSSI/SNR if available,
- decoded payload log, CSV output, dashboard screenshots where relevant,
- command log for uplink tests,
- pass/fail calculation including confidence interval and any excluded samples.
