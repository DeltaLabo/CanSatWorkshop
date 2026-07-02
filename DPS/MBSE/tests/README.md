# DPS v1.0 MBSE IVV verification plan

Derived from `DPS/MBSE/v1.0/` Capella/D2 Physical Architecture views. Source architecture diagrams are preserved in the version folder; detailed verification-definition diagrams are added under activity folders in this `tests/` directory. This plan uses [`../../../../PM&SE/IVV.md`](../../../../PM&SE/IVV.md) and the existing corpus in [`references/`](./references/).

## 1. SSIV and assumptions

- **Version/SSIV:** `DPS-v1.0` subsystem integration version confirmed for the current detailed verification definitions. No formal SSIV document was found.
- **Baseline meaning:** full flight-packaging DPS model; ground station PCB reuses the OBCC PCB with the Backplane Connector not soldered.
- **Cadence assumption:** v1.0 OBCC heartbeat/status/measurement downlink cadence is 2 s. 5 Hz runs are optional lab stress only.
- **Traceability gap:** explicit mission, capability, use-case and feared-event model elements are absent; trace targets below are inferred and need confirmation.

## 2. References

- **P0:** `PM&SE/IVV.md` project MBSE IVV, IADT and statistics policy.
- **R1-R3:** ECSS-E-ST-10-03C and ISO/IEC/IEEE 29119-2/3 test process/documentation artifacts.
- **R4-R5:** NIST/SEMATECH binomial/sample-size artifacts.
- **R6-R10:** ETSI/TTN/RFM96W/SX1276/LoRa radio artifacts.
- **R11-R13:** CanSat/Andøya telemetry and ground-station artifacts.
- **R14-R15:** LoRa PDR/path-loss literature artifacts.

## 3. MBSE planning inventory

### 3.1 Views read

PV1 `DPS_v1.0_view1_physical.d2`; PV2 `DPS_v1.0_view2_logical.d2`; PV3 `DPS_v1.0_view3_functional_allocation.d2`; chains `DPS_v1.0_view4_downlink_processing_chain.d2` through `DPS_v1.0_view9_forwarder_initialisation_chain.d2`.

### 3.2 Physical components and links

- **PCs:** CanSat; OBCC Module; OBCC PCB; CanSat RFM96W LoRa; CanSat XIAO ESP32-S3; Backplane Connector; Ground Station PCB; ground RFM96W LoRa; ground XIAO ESP32; PC; PC USB Port.
- **PLs:** OBCC Module-to-OBCC PCB screws; CanSat RFM footprint; CanSat XIAO footprint; Backplane Connector footprint; CanSat RFM96W-to-XIAO SPI traces; ground RFM footprint; ground XIAO footprint; ground RFM96W-to-XIAO SPI traces; ground RFM96W-to-XIAO 5 V power traces; ground XIAO-to-PC USB-C cable.

### 3.3 Component exchanges

1. CanSat LoRa Transceiver -> OBCC: SPI.
2. LoRa Forwarder -> ground LoRa Transceiver: SPI.
3. LoRa Forwarder -> PC Decoder: UART.
4. PC Decoder -> CSV Writer: Payload.
5. PC Decoder -> Dashboard: Payload.
6. Dashboard -> PC Decoder: Command.

### 3.4 Logical allocation inventory

| LC | Allocated functions or note |
|---|---|
| CanSat LoRa Transceiver | Receive incoming data; Transmit outgoing data. |
| OBCC | Receive LoRa RX Interrupt; Send LoRa packet; Read command. |
| ESS Processing | Context LC in DPS view, no DPS-owned functions allocated. Analyze for no foreign DPS function and no load starvation. |
| ADS Processing | Context LC in DPS view, no DPS-owned functions allocated. Analyze for no foreign DPS function and no load starvation. |
| PDM Processing | Context LC in DPS view, no DPS-owned functions allocated. Analyze for no foreign DPS function and no load starvation. |
| AMS Processing | Context LC in DPS view, no DPS-owned functions allocated. Analyze for no foreign DPS function and no load starvation. |
| Ground LoRa Transceiver | Store incoming data; Transmit outgoing data. |
| LoRa Forwarder | Init Serial0 with interrupts; Init SPI with interrupts; Log error; Receive LoRa RX Interrupt; Read payload; Forward to PC; Store incoming UART data; Receive Serial0 RX Interrupt; Read command; Generate frame; Write to LoRa Radio. |
| Decoder | Check if data is available; Read and decode frame; Push to payload queue; Get RX timestamp; Calculate latency; Forward to transceiver; Consume command queue. |
| CSV Writer | Consume payload queue; Append to CSV. |
| Dashboard | Consume payload queue; Update CanSat attitude model; Push to command queue; Update temperature 2D plot; Update altitude 2D plot; Catch State toggle; Update latency alert; Disable toggle; Enable toggle; Cooldown; Create plots. |
| USB Power | Provide power. |

### 3.5 Functional chains and constraints

- **Chains:** FC01 downlink decode/storage; FC02 dashboard command/uplink; FC03 CanSat receive path; FC04 CanSat transmit path; FC05 dashboard visualisation; FC06 forwarder initialisation.
- **Constraints:** C01 max 500 m CanSat-DPS separation; C02 Ground Station PCB reuses OBCC PCB and Backplane Connector is not soldered; C03 concurrent Decoder/CSV/Dashboard execution; C04 browser-accessible dashboard; C05 unique CSV name from initial timestamp; C06 top alert when latency >1 s; C07 5 s toggle cooldown; C08 4x4 plot matrix with the CanSat attitude model in the top-left cell.
- **Inferred feared events:** missing hardware/interface, wrong protocol, dropped or corrupt accepted frame, overwritten CSV, hidden latency, command spam/stale command, silent init failure, RF false frame, USB/UART interruption, shared CanSat processing starvation.

## 4. Candidate IVV activities

All rows include: ID, SSIV/version, model elements, IVV source category, IADT method, trace target, references, viewpoints including statistics/fault hardening, pass/fail criteria, diagram/report references, and status.

| ID | SSIV/version | Model element(s) covered | IVV source category | IADT | Traceability target | Refs | Viewpoints: statistics and fault hardening | Pass/fail criteria | Diagram/report references | Status |
|---|---|---|---|---|---|---|---|---|---|---|
| DPS-V10-I-001 | DPS-v1.0 | All PCs and PLs in §3.2; C02 ground-station PCB reuse/no backplane | component/link | I | Assembled v1.0 DPS/CanSat interface; ground-station integration safety constraint C02 | P0,R1-R3,R8,R11-R13 | 100% item coverage; article/revision identification; footprint population; screw presence; backplane absence; continuity, polarity and shorts; ESD, illumination and antenna-before-TX fault hardening. | 100% of modeled PCs/PLs inspected; every item present or dispositioned; correct variants/revisions; screws/footprints/traces/5 V/USB-C cable pass visual and continuity checks; UUT unpowered for resistance checks; no 5 V/GND short or reversed polarity; ground-station backplane connector absent/not soldered; illumination ≥500 lx and ESD controls recorded. | Definition diagrams/checklist: `DPS-V10-I-001/` views 1-3, baseline copy in `DPS-V10-I-001/baseline/`; report/evidence: `tests/results/DPS-V10-I-001/` | Defined; diagrams/checklist generated; awaiting user review/execution. |
| DPS-V10-A-001 | DPS-v1.0 | All six CEs in §3.3: CE-01 CanSat LoRa→OBCC SPI; CE-02 Forwarder→ground LoRa SPI; CE-03 Forwarder→Decoder UART; CE-04 Decoder→CSV Payload; CE-05 Decoder→Dashboard Payload; CE-06 Dashboard→Decoder Command | component exchange | A | Telemetry and command paths; feared wrong protocol, corrupt accepted payload, lost UART/SPI, stale bytes, duplicate/stale command, hidden unmodeled exchange | P0,R1-R3,R8-R13 | CE-by-CE protocol/direction/data analysis; SPI/UART/Payload/Command intent; implementation artifact baseline; 100% checklist coverage; fault-hardening review for stale bytes, corrupt payloads, lost UART/SPI and disconnects. | All six modeled CEs have implementation evidence; protocols and direction match model intent; no silent substitute protocol or hidden bypass; Payload/Command data semantics preserved; stale/corrupt/disconnect/duplicate cases are detected, rejected or logged; unresolved CE item is a failed or limited analysis. | Definition diagrams/checklist: `DPS-V10-A-001/` views 1-2, baseline copy in `DPS-V10-A-001/baseline/`; report/evidence: `tests/results/DPS-V10-A-001/` | Defined; diagrams/checklist generated; awaiting user review/execution. |
| DPS-V10-A-002 | DPS-v1.0 | All 12 LC/function allocations in §3.4; allocation-boundary consistency against CEs in §3.3; context ESS/ADS/PDM/AMS no-DPS-function/no-starvation review | allocation | A | Correct responsibility partition and shared-load behavior; feared missing/foreign function, command bypass, unbounded queue growth, stale command path and shared CanSat processing starvation | P0,R1-R5,R8-R13 | Static code/module allocation review; 100% LC/function checklist coverage; cross-LC boundary-flow consistency; runtime trace/scheduling review for ESS/ADS/PDM/AMS shared-load starvation; statistics not primary beyond coverage and cited trace duration. | All intended DPS functions allocated to modeled LCs; no LC owns a foreign DPS function; context LCs contain no DPS-owned functions; cross-LC responsibilities use modeled CEs/local queues/protocols without direct bypass; 2 s OBCC LoRa/command handling is not starved under representative shared-load evidence; unresolved allocation item or missing shared-load evidence is fail/limited. | Definition diagrams/checklist: `DPS-V10-A-002/` views 1-2, baseline copy in `DPS-V10-A-002/baseline/`; report/evidence: `tests/results/DPS-V10-A-002/` | Defined; diagrams/checklist generated; awaiting user review/execution. |
| DPS-V10-T-001 | DPS-v1.0 | FC01 downlink decode/storage; Ground LoRa Transceiver; LoRa Forwarder; Decoder; CSV Writer; UART/Payload CEs; C05 unique CSV name | functional chain/scenario | T | Use case: receive, decode, timestamp and store OBCC telemetry; feared event: corrupt/stale RF-UART frame accepted as telemetry | P0,R1-R5,R8-R15 | Exact binomial decoded+stored PDR; p95 latency; CSV/data integrity; corrupt-frame rejection; USB/UART interruption and stale-byte hardening. | Valid-frame sequence: `N≥300` at `2.0 s ±0.2 s`; one-sided 95% exact PDR lower bound `≥0.90` (`k≥279/300` planning threshold); p95 RX-to-CSV latency `<1 s`; CSV rows equal accepted decoded frames; unique timestamp filename/no overwrite. Fault sequence: ≥30 invalid frames across CRC-bad/short/wrong-type/stale cases; zero invalid CSV rows; every invalid frame rejected/logged; valid follow-up accepted once. | Definition diagrams: `DPS-V10-T-001/` views 1-5, baseline copy in `DPS-V10-T-001/baseline/`; report/evidence: `tests/results/DPS-V10-T-001/` | Defined; diagrams generated; awaiting user review/execution. |
| DPS-V10-T-002 | DPS-v1.0 | FC02 command/uplink; Dashboard, Decoder, LoRa Forwarder, Ground LoRa Transceiver functions; Command/UART/SPI path; C07 5 s cooldown | functional chain/scenario | T | Use case: wireless state command; feared command spam, duplicate/stale command, direct command bypass, UART/SPI/radio-not-ready fault | P0,R1-R5,R8-R13 | Exact-binomial valid-command screening; 100% command sequence comparison; cooldown timing distribution; duplicate/stale-command hardening; RF command capture; CE-03 UART direction discrepancy disposition. | Valid sequence: ≥60 accepted toggles outside cooldown; each produces exactly one RF command frame matching expected state; zero wrong states, zero duplicates and zero missing commands. Cooldown sequence: ≥30 rapid-toggle bursts; only first toggle enqueues/transmits; suppressed toggles generate zero extra queue entries/RF frames; UI re-enables at 5.0 s ±0.5 s; post-cooldown toggle accepted once. | Definition diagrams/checklist: `DPS-V10-T-002/` views 1-5, baseline copy in `DPS-V10-T-002/baseline/`; report/evidence: `tests/results/DPS-V10-T-002/` | Defined; diagrams generated; awaiting user review/execution. |
| DPS-V10-T-003 | DPS-v1.0 | FC03 CanSat receive path; CanSat LoRa Transceiver receive function; OBCC RX interrupt and Read command functions; CE-01 CanSat radio→OBCC SPI path | functional chain/scenario | T | Use case: OBCC receives wireless state command; feared spoof/no-frame interrupt or old buffer accepted as valid command | P0,R1-R5,R8-R13 | Exact-binomial valid-command screening; OBCC interrupt/read log comparison; spoof/wrong sender/type, no-frame/spurious interrupt, old-buffer/stale replay, duplicate sequence and malformed/CRC-bad command hardening. | Valid sequence: ≥60 valid command frames; each is read by OBCC exactly once with expected state/sequence; zero missing, wrong, duplicate or stale acceptances. Fault sequence: ≥60 invalid trials by class; zero invalid commands accepted; previous valid command is never re-read; valid follow-up command accepted once. | Definition diagrams/checklist: `DPS-V10-T-003/` views 1-5, baseline copy in `DPS-V10-T-003/baseline/`; report/evidence: `tests/results/DPS-V10-T-003/` | Defined; diagrams generated; awaiting user review/execution. |
| DPS-V10-T-004 | DPS-v1.0 | FC04 CanSat transmit path | functional chain/scenario | T | Use case: OBCC transmits LoRa frame | P0,R1-R5,R8-R13 | Sequence success count; radio-busy/not-ready and buffer-overrun hardening. | 60 transmissions with zero missing sequence numbers at near-field receiver; no TX while radio not ready; no buffer overrun. | `tests/results/DPS-V10-T-004/` | Candidate, detailed definition required. |
| DPS-V10-T-005 | DPS-v1.0 | FC05 dashboard visualisation, C03,C04,C06,C08 | functional chain/scenario | D/T | Use case: operator sees real-time telemetry | P0,R1-R5,R11-R13 | Payload-to-display success; display latency; stale/invalid field hardening. | `N=300` known v1.0 payloads update the selected dashboard displays; top-left cell renders CanSat attitude from pitch/roll/yaw; browser works; alert only for latency >1 s. | `tests/results/DPS-V10-T-005/` | Candidate, UI oracle required. |
| DPS-V10-T-006 | DPS-v1.0 | FC06 forwarder initialisation | functional chain/scenario | T | Feared event: silent init failure | P0,R1-R5,R8 | Independent restart trials; missing SPI/radio/UART hardening. | 59-60 restarts with zero init failures for selected claim; injected faults log error and never false-ready. | `tests/results/DPS-V10-T-006/` | Candidate, fault-injection detail required. |
| DPS-V10-C-001 | DPS-v1.0 | C01 500 m separation | constraint | A/T | CanSat-to-DPS link constraint | P0,R1-R5,R6-R15 | Exact binomial PDR; RSSI/SNR/path-loss; legal duty cycle, antenna and interference hardening. | Field or RF-equivalent 500 m test; lower 95% PDR bound meets agreed target, default ≥0.90; radio settings legal. | `tests/results/DPS-V10-C-001/` | Candidate, range definition required. |
| DPS-V10-C-002 | DPS-v1.0 | C02 ground PCB reuse/no backplane | constraint | I/A | Ground-station integration safety | P0,R1-R3,R8 | 100% article inspection; unintended backplane load/short hardening. | Ground PCB population matches reuse intent; backplane connector absent/not soldered; no unintended backplane continuity or load. | Covered in `DPS-V10-I-001/`; optional separate report `tests/results/DPS-V10-C-002/` only if constraint-specific sign-off is required. | Covered by DPS-V10-I-001; retire or keep as optional constraint sign-off after review. |
| DPS-V10-C-003 | DPS-v1.0 | C03 concurrent execution | constraint | T | Concurrent process/store/display capability | P0,R1-R5 | Sustained frame count, queue depth, memory growth; backlog/crash/deadlock hardening. | Mission-duration flight-cadence run passes; optional 20 min 5 Hz stress has no crash; backlog returns to zero; p95 latency <1 s; memory bounded. | `tests/results/DPS-V10-C-003/` | Candidate, load definition required. |
| DPS-V10-C-004 | DPS-v1.0 | C04 browser access | constraint | I/D | Operator UI use case | P0,R1-R3,R11-R13 | Browser refresh/reconnect hardening; statistics not primary. | Dashboard opens in agreed browser(s), refresh/reconnect does not corrupt data, no developer console dependence for user functions. | `tests/results/DPS-V10-C-004/` | Candidate, browser set TBD. |
| DPS-V10-C-005 | DPS-v1.0 | C05 unique CSV name | constraint | T | Data archival integrity | P0,R1-R3 | Rapid restart/same-second hardening; statistics not primary. | At least 10 sessions produce zero overwrites; filenames unique; row order monotonic; row count/checksum matches accepted frames. | `tests/results/DPS-V10-C-005/` | Candidate, filesystem oracle needed. |
| DPS-V10-C-006 | DPS-v1.0 | C06 latency alert >1 s | constraint | T | Feared hidden latency | P0,R1-R5 | Threshold samples; boundary timestamp hardening. | 30 payloads below, at and above threshold; no alert for ≤1.0 s; top alert for >1.0 s; invalid timestamps rejected/flagged. | `tests/results/DPS-V10-C-006/` | Candidate, threshold oracle needed. |
| DPS-V10-C-007 | DPS-v1.0 | C07 5 s cooldown | constraint | T | Feared command spam, duplicate/stale command | P0,R1-R5 | Covered as part of `DPS-V10-T-002`: burst trials, timing distribution, monotonic clock-jitter hardening, queue/RF duplicate suppression. | 30 bursts; only first toggle enqueues/transmits; suppressed toggles create zero extra queue entries/RF frames; UI disabled during cooldown and re-enabled at 5.0 s ±0.5 s; post-cooldown toggle accepted once. | Covered by `DPS-V10-T-002/` views 3 and 5; optional separate report `tests/results/DPS-V10-C-007/` only if constraint-specific sign-off is required. | Covered by DPS-V10-T-002; retire or keep as optional constraint sign-off after review. |
| DPS-V10-C-008 | DPS-v1.0 | C08 4x4 plots, attitude model top-left | constraint | I/D | Telemetry visualisation use case | P0,R1-R3,R11-R13 | Layout/mapping inspection; missing fields and resize hardening. | Required plot matrix is present; top-left cell renders CanSat attitude from pitch/roll/yaw; remaining dashboard cells are mapped to selected v1.0 telemetry displays. | `tests/results/DPS-V10-C-008/` | Candidate, UI oracle detail required. |

### 4.1 Detailed definitions created

- `DPS-V10-A-001/` defines the component-exchange analysis using copied v1.0 baseline views, a focused PV2 CE-analysis view, a PV3 functional allocation/evidence-control view, and a six-CE checklist. The expected report remains `tests/results/DPS-V10-A-001/`.
- `DPS-V10-A-002/` defines the functional-allocation analysis using copied v1.0 baseline views, a PV3 full LC/function allocation analysis view, a PV2 allocation-boundary/CE consistency view, and LC/boundary checklists. The expected report remains `tests/results/DPS-V10-A-002/`.
- `DPS-V10-I-001/` defines the physical component/link inspection using copied v1.0 baseline views, PV1/PV2/PV3 inspection-context views, equipment/operator functions, and a complete PC/PL checklist. The expected report remains `tests/results/DPS-V10-I-001/`.
- `DPS-V10-T-001/` defines the downlink decode/storage test using copied v1.0 baseline views, focused PV1/PV2/PV3 test-context views, and two functional-chain test sequences: valid-frame statistical downlink and corrupt-frame hardening/recovery. The expected report remains `tests/results/DPS-V10-T-001/`.
- `DPS-V10-T-002/` defines the dashboard command/uplink and cooldown test using copied v1.0 baseline views, focused PV1/PV2/PV3 test-context views, and two functional-chain test sequences: valid command/uplink screening and C07 cooldown/duplicate hardening. The expected report remains `tests/results/DPS-V10-T-002/`.
- `DPS-V10-T-003/` defines the CanSat receive-path command test using copied v1.0 baseline views, focused PV1/PV2/PV3 test-context views, and two functional-chain test sequences: valid CanSat command receive screening and spoof/no-frame/old-buffer hardening. The expected report remains `tests/results/DPS-V10-T-003/`.

## 5. Gaps before detailed definition

- Formal SSIV, mission, capability, use-case and feared-event IDs are missing.
- Earlier delivery versions (`v0.1`, `v0.2`) are intentionally not detailed here yet; they need version-specific verification definitions later.
- All candidate rows except `DPS-V10-I-001`, `DPS-V10-A-001`, `DPS-V10-A-002`, `DPS-V10-T-001`, `DPS-V10-T-002`, `DPS-V10-T-003`, C02 coverage through `DPS-V10-I-001`, and C07 coverage through `DPS-V10-T-002` still require detailed definition with Capella/D2 verification views before execution.
- DPS v1.0 payload/dashboard field decision is closed: the obsolete RH dashboard field is removed instead of adding placeholders or expanding the OBCC frame.
- The top-left attitude model is the 3D orientation display driven by pitch/roll/yaw.
- Altitude remains a 2D telemetry plot/value in the dashboard mapping.
- DPS v1.0 PV2 models CE-03 UART as LoRa Forwarder→PC Decoder, while FC02 command/uplink uses command bytes from Decoder back to Forwarder; `DPS-V10-T-002` records reverse-use evidence but the model/implementation discrepancy still needs disposition.
- Statistical claims, independence of trials, RF environment and exact PDR thresholds must be fixed in each detailed test definition.
- Corrupt-frame rejection is modeled for `DPS-V10-T-001`; USB/UART interruptions, RF interference, power recovery and shared CanSat processing load still need detailed verification scenarios.
