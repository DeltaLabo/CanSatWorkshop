# DPS v0.1 MBSE IVV verification plan

Derived from `DPS/MBSE/v0.1/` Capella/D2 Physical Architecture views. Diagrams were not edited and no detailed test-definition diagrams are created here. This plan uses only [`../../../../PM&SE/IVV.md`](../../../../PM&SE/IVV.md) and the existing corpus in [`references/`](./references/).

## 1. SSIV and assumptions

- **Version/SSIV assumption:** `DPS-v0.1` development subsystem integration version. No formal SSIV document was found.
- **Baseline meaning:** hardware-downgraded datalogger and ground-station circuitboards while preserving the v1.0 functional chains.
- **Rate assumption:** 5 Hz activity is development stress evidence only; v1.0 OBCC flight telemetry remains 2 s.
- **Traceability gap:** explicit mission, capability, use-case and feared-event model elements are absent; trace targets below are inferred and need confirmation.

## 2. References

- **P0:** `PM&SE/IVV.md` project MBSE IVV, IADT and statistics policy.
- **R1:** ECSS-E-ST-10-03C test planning/reporting artifacts.
- **R2:** ISO/IEC/IEEE 29119-2/3 software test process/documentation artifacts.
- **R3:** NIST/SEMATECH binomial/sample-size artifacts.
- **R4:** ETSI EN 300 220 and TTN EU868 radio constraints.
- **R5:** RFM95W/SX1276/LoRa references.
- **R6:** CanSat/Andøya telemetry and ground-station references.
- **R7:** LoRa PDR/path-loss literature artifacts.

## 3. MBSE planning inventory

### 3.1 Views read

PV1 `DPS_v0.1_view1_physical.d2`; PV2 `DPS_v0.1_view2_logical.d2`; PV3 `DPS_v0.1_view3_functional_allocation.d2`; chains `DPS_v0.1_view4_downlink_processing_chain.d2` through `DPS_v0.1_view9_forwarder_initialisation_chain.d2`.

### 3.2 Physical components and links

- **PCs:** Datalogger Circuitboard; datalogger RFM95W LoRa; datalogger XIAO ESP32-S3; Ground Station Circuitboard; ground RFM95W LoRa; ground XIAO ESP32; PC; PC USB Port.
- **PLs:** datalogger RFM95W-to-XIAO SPI wires; ground RFM95W-to-XIAO SPI + 5 V power wires; ground XIAO-to-PC USB-C cable.

### 3.3 Component exchanges

1. Datalogger LoRa Transceiver -> Dummy Datalogger: SPI.
2. LoRa Forwarder -> ground LoRa Transceiver: SPI.
3. LoRa Forwarder -> PC Decoder: UART.
4. PC Decoder -> CSV Writer: Payload.
5. PC Decoder -> Dashboard: Payload.
6. Dashboard -> PC Decoder: Command.

### 3.4 Logical allocation inventory

| LC | Allocated functions |
|---|---|
| Datalogger LoRa Transceiver | Receive incoming data; Transmit outgoing data. |
| Dummy Datalogger | Receive LoRa RX Interrupt; Send LoRa packet; Read command. |
| Ground LoRa Transceiver | Store incoming data; Transmit outgoing data. |
| LoRa Forwarder | Init Serial0 with interrupts; Init SPI with interrupts; Log error; Receive LoRa RX Interrupt; Read payload; Forward to PC; Store incoming UART data; Receive Serial0 RX Interrupt; Read command; Generate frame; Write to LoRa Radio. |
| Decoder | Check if data is available; Read and decode frame; Push to payload queue; Get RX timestamp; Calculate latency; Forward to transceiver; Consume command queue. |
| CSV Writer | Consume payload queue; Append to CSV. |
| Dashboard | Consume payload queue; Update orientation 3D plot; Update relative-humidity 2D plot; Push to command queue; Update temperature 2D plot; Update altitude 2D plot; Catch State toggle; Update latency alert; Disable toggle; Enable toggle; Cooldown; Create plots. |
| USB Power | Provide power. |

### 3.5 Functional chains and constraints

- **Chains:** FC01 downlink decode/storage; FC02 dashboard command/uplink; FC03 CanSat receive path; FC04 CanSat transmit path; FC05 dashboard visualisation; FC06 forwarder initialisation.
- **Constraints:** C01 max 500 m datalogger-ground separation; C02 concurrent Decoder/CSV/Dashboard execution; C03 browser-accessible dashboard; C04 unique CSV name from initial timestamp; C05 top alert when latency >1 s; C06 5 s toggle cooldown; C07 4x4 plot matrix with 3D plot top left.
- **Inferred feared events:** missing hardware/interface, wrong protocol, dropped or corrupt accepted frame, overwritten CSV, hidden latency, command spam/stale command, silent init failure, RF false frame, USB/UART interruption.

## 4. Candidate IVV activities

All rows include: ID, SSIV/version, model elements, IVV source category, IADT method, trace target, references, viewpoints including statistics/fault hardening, preliminary criteria, expected report location, and status.

| ID | SSIV/version | Model element(s) covered | IVV source category | IADT | Traceability target | Refs | Viewpoints: statistics and fault hardening | Preliminary pass/fail criteria | Expected location | Status |
|---|---|---|---|---|---|---|---|---|---|---|
| DPS-V01-I-001 | DPS-v0.1 | All PCs and PLs in §3.2 | component/link | I | Assembled v0.1 telemetry bench capability | P0,R1,R5,R6 | 100% item coverage; wiring polarity, shorts, antenna-before-TX, USB power safety. | Every PC/PL present or dispositioned; SPI/5 V/USB continuity and polarity pass; no unsafe power-up. | `tests/results/DPS-V01-I-001/` | Candidate, define checklist later. |
| DPS-V01-A-001 | DPS-v0.1 | All six CEs in §3.3 | component exchange | A | Telemetry and command paths | P0,R1,R2,R5,R6 | CE-by-CE protocol/direction/data analysis; handle stale bytes, corrupt payloads, lost UART/SPI. | SPI, UART, Payload and Command exchanges exist, match direction/intent, and faulted exchanges are detected or logged. | `tests/results/DPS-V01-A-001/` | Candidate, CE evidence template needed. |
| DPS-V01-A-002 | DPS-v0.1 | All LC/function allocations in §3.4 | allocation | A | Correct software/hardware partition | P0,R1,R2 | Static review and runtime traces; no foreign functions, no missing queue/ISR path. | All intended functions allocated to listed LC/host; no conflicting foreign functions; cross-LC flows use modeled CEs. | `tests/results/DPS-V01-A-002/` | Candidate, update after code baseline. |
| DPS-V01-T-001 | DPS-v0.1 | FC01 downlink decode/storage, C04 | functional chain/scenario | T | Use case: receive, decode, timestamp and store telemetry | P0,R1,R2,R3,R5,R6,R7 | Exact binomial frame success; latency distribution; corrupt-frame rejection. | Development run, nominally 5 Hz for 60 s, `N=300`; decoded+stored lower 95% bound meets agreed PDR target; p95 latency <1 s; CSV rows equal accepted frames; corrupt frames rejected/logged. | `tests/results/DPS-V01-T-001/` | Candidate, detailed definition required. |
| DPS-V01-T-002 | DPS-v0.1 | FC02 command/uplink, C06 | functional chain/scenario | T | Use case: state command, feared command spam | P0,R1,R2,R3,R5,R6 | Binomial command success; cooldown timing; duplicate/stale-command hardening. | At least 60 valid toggles transmit with zero wrong state/duplicates; rapid toggles during cooldown enqueue no extra command; re-enable at 5.0 s ±0.5 s. | `tests/results/DPS-V01-T-002/` | Candidate, detailed definition required. |
| DPS-V01-T-003 | DPS-v0.1 | FC03 CanSat receive path | functional chain/scenario | T | Use case: datalogger receives command | P0,R1,R3,R5,R6 | Valid/rejected-command counts; spoof/no-frame interrupt and old-buffer hardening. | 60 valid commands accepted; 60 spoof/no-frame/old-buffer cases rejected; no stale command is re-read. | `tests/results/DPS-V01-T-003/` | Candidate, detailed definition required. |
| DPS-V01-T-004 | DPS-v0.1 | FC04 CanSat transmit path | functional chain/scenario | T | Use case: datalogger transmits LoRa frame | P0,R1,R3,R5,R6 | Sequence success count; radio-busy/not-ready and buffer-overrun hardening. | 60 transmissions with zero missing sequence numbers at near-field receiver; no TX while radio not ready; no buffer overrun. | `tests/results/DPS-V01-T-004/` | Candidate, detailed definition required. |
| DPS-V01-T-005 | DPS-v0.1 | FC05 dashboard visualisation, C02,C03,C05,C07 | functional chain/scenario | D/T | Use case: operator sees real-time telemetry | P0,R1,R2,R3,R6 | Payload-to-plot success; display latency; stale/invalid field hardening. | `N=300` known payloads update correct plots; 4x4 matrix exists; 3D plot top-left; browser works; alert only for latency >1 s. | `tests/results/DPS-V01-T-005/` | Candidate, UI oracle required. |
| DPS-V01-T-006 | DPS-v0.1 | FC06 forwarder initialisation | functional chain/scenario | T | Feared event: silent init failure | P0,R1,R2,R3,R5 | Independent restart trials; missing SPI/radio/UART hardening. | 59-60 restarts with zero init failures for selected claim; injected faults log error and never false-ready. | `tests/results/DPS-V01-T-006/` | Candidate, fault-injection detail required. |
| DPS-V01-C-001 | DPS-v0.1 | C01 500 m separation | constraint | A/T | Datalogger-to-ground link constraint | P0,R1,R3,R4,R5,R6,R7 | Exact binomial PDR; RSSI/SNR/path-loss; legal duty cycle, antenna and interference hardening. | Field or RF-equivalent 500 m test; lower 95% PDR bound meets agreed target, default ≥0.90 unless stricter; radio settings legal. | `tests/results/DPS-V01-C-001/` | Candidate, range definition required. |
| DPS-V01-C-002 | DPS-v0.1 | C02 concurrent execution | constraint | T | Concurrent process/store/display capability | P0,R1,R2,R3 | Sustained frame count, queue depth, memory growth; backlog/crash/deadlock hardening. | 20 min stress, e.g. 5 Hz, no crash; backlog returns to zero; p95 pipeline latency <1 s; memory bounded. | `tests/results/DPS-V01-C-002/` | Candidate, load definition required. |
| DPS-V01-C-003 | DPS-v0.1 | C03 browser access | constraint | I/D | Operator UI use case | P0,R1,R2,R6 | Browser refresh/reconnect hardening; statistics not primary. | Dashboard opens in agreed browser(s), refresh/reconnect does not corrupt data, no developer console dependence for user functions. | `tests/results/DPS-V01-C-003/` | Candidate, browser set TBD. |
| DPS-V01-C-004 | DPS-v0.1 | C04 unique CSV name | constraint | T | Data archival integrity | P0,R1,R2 | Rapid restart/same-second hardening; statistics not primary. | At least 10 sessions produce zero overwrites; filenames unique; row order monotonic; row count/checksum matches accepted frames. | `tests/results/DPS-V01-C-004/` | Candidate, filesystem oracle needed. |
| DPS-V01-C-005 | DPS-v0.1 | C05 latency alert >1 s | constraint | T | Feared hidden latency | P0,R1,R2,R3 | Threshold samples; boundary timestamp hardening. | 30 payloads below, at and above threshold; no alert for ≤1.0 s; top alert for >1.0 s; invalid timestamps rejected/flagged. | `tests/results/DPS-V01-C-005/` | Candidate, threshold oracle needed. |
| DPS-V01-C-006 | DPS-v0.1 | C06 5 s cooldown | constraint | T | Feared command spam | P0,R1,R2,R3 | Burst trials and timing distribution; clock-jitter hardening. | 30 bursts; only first toggle enqueues; UI disabled during cooldown and re-enabled at 5.0 s ±0.5 s. | `tests/results/DPS-V01-C-006/` | Candidate, UI timing definition needed. |
| DPS-V01-C-007 | DPS-v0.1 | C07 4x4 plots, 3D top-left | constraint | I/D | Telemetry visualisation use case | P0,R1,R2,R6 | Layout/mapping inspection; missing fields and resize hardening. | Required plot matrix present and mapped. **Gap:** DPS README says 3D altitude model while PA model says 3D orientation plot. | `tests/results/DPS-V01-C-007/` | Candidate, open requirement/model discrepancy. |

## 5. Gaps before detailed definition

- Formal SSIV, mission, capability, use-case and feared-event IDs are missing.
- All candidate rows require later detailed definition with `capella-pa-tests-definition.md` before execution.
- DPS v0.1 dashboard includes relative humidity; OBCC v1.0 telemetry excludes it, so any v1.0 reuse must disposition this mismatch.
- Statistical claims, independence of trials, RF environment and exact PDR thresholds must be fixed in each detailed test definition.
- Corrupt frames, USB/UART interruptions, RF interference and power recovery are identified but not yet modeled as detailed verification scenarios.
