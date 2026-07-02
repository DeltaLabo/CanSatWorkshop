# DPS-V10 RF range, LoRa airtime, PDR, and concurrency parameters

Date: 2026-07-02

## 1. Scope and status

This document freezes definition parameters only for `DPS-V10-C-001`, `DPS-V10-C-003`, and related future detailed definitions that need the same RF/range/PDR, LoRa airtime, or concurrency assumptions. It is not an execution report and does not grant pass/fail credit.

Execution, detailed activity READMEs, D2/source-model updates, PNG regeneration, and system-level integration updates remain pending.

## 2. RF/range campaign parameters

Strict `DPS-V10-C-001` and `SYS-RF-RANGE-PDR` range/PDR evidence shall use this baseline unless a later controlled system definition supersedes it:

- Endpoint geometry: horizontal line-of-sight range with `500 m` endpoint separation. The measured horizontal separation between antenna endpoints, including measurement uncertainty, shall be at least `500 m` for strict credit.
- Frequency: `915 MHz`.
- Antennas: matching `22 AWG` straight-wire monopoles with `81.4 mm` exposed conductor on the CanSat and ground-station RFM96W articles.
- Orientation/polarization: both monopoles straight and vertical unless the final as-flown installation requires otherwise; both endpoints shall use matching linear polarization. Record any tilt, enclosure shadowing, body orientation, or polarization mismatch.
- Height: record measured antenna feed-point height above local ground for both endpoints. Strict final-article credit should use the final mounted orientation/height; non-final mast heights are characterization unless justified by the detailed definition.
- Endpoint-distance evidence: record the distance tool/method, endpoint coordinates or survey marks, uncertainty, and photos showing line of sight.
- Environment and interference: record weather, temperature, wind/rain, notable obstructions, observed 915 MHz interference/channel occupancy if available, and any nearby transmitters.
- RF evidence: log per-frame sequence, timestamp, RSSI, SNR, validity/reject reason, and receiver article ID.
- Site safety: record site approval, public/traffic separation, spotter/communication plan as needed, trip/vehicle hazards, and safe handling of powered RF articles and antennas.
- Article/configuration IDs: record CanSat radio article, ground-station radio article, antenna build IDs, firmware commits/builds, settings/config files, TX power/EIRP inputs, PC/logger, analysis tool version, and operator.
- Legal/site approval: the selected frequency, TX power, antenna gain, EIRP, duty cycle, and site authorization shall be legal for the test location. If legal/EIRP/duty-cycle/site approval is not controlled and recorded, the run is limited to characterization and shall not be used for strict range/PDR acceptance.

## 3. LoRa parameters and frame-duration calculation

Selected LoRa parameters for definition-level airtime calculations:

| Parameter | Value |
|---|---|
| Frequency | `915 MHz` |
| Spreading factor | `SF7` |
| Bandwidth | `125 kHz` |
| Coding rate | `4/5` (`CR = 1` in the common Semtech formula) |
| Header mode | Explicit header (`IH = 0`) |
| Payload CRC | On (`CRC = 1`) |
| Preamble | `8` symbols |
| Low-data-rate optimization | Off (`DE = 0`) |
| Current worst-case payload length | `LORA_PAYLOAD_SIZE = 100 bytes` |

Standard LoRa time-on-air formula:

```text
T_sym = 2^SF / BW
T_preamble = (N_preamble + 4.25) * T_sym
N_payload = 8 + max(ceil((8*PL - 4*SF + 28 + 16*CRC - 20*IH)
                        / (4*(SF - 2*DE))) * (CR + 4), 0)
T_payload = N_payload * T_sym
T_packet = T_preamble + T_payload
```

Worked calculation for `PL = 100`, `SF = 7`, `BW = 125000 Hz`, `CR = 1`, `IH = 0`, `CRC = 1`, `DE = 0`, `N_preamble = 8`:

```text
T_sym = 2^7 / 125000 = 0.001024 s = 1.024 ms
T_preamble = (8 + 4.25) * 1.024 ms = 12.544 ms
N_payload = 8 + ceil((8*100 - 4*7 + 28 + 16*1 - 20*0) / (4*(7 - 2*0))) * (1 + 4)
          = 8 + ceil(816 / 28) * 5
          = 8 + 30 * 5
          = 158 symbols
T_payload = 158 * 1.024 ms = 161.792 ms
T_packet = 12.544 ms + 161.792 ms = 174.336 ms
```

**Current 100-byte worst-case airtime result:** `174.336 ms` per LoRa frame with the selected parameters.

At a `2 s` flight cadence this is about `8.72%` raw RF time-on-air per transmitting node before turn-around/listen margins. A `5 Hz` over-air stress would consume about `87.17%` raw RF time-on-air for this 100-byte frame, so the optional high-rate stress should use synthetic, serial-injected, or RF-cabled frames whenever legal/duty-cycle margin is inadequate.

`OBCC/LoRa_Frame.md` currently totals `34 bytes` in the variable table before LoRa envelope, IDs, schema/version, delimiters, command/request fields, RSSI/SNR logging fields, or future schema overhead. Any schema or envelope change shall trigger a new airtime calculation before execution.

## 4. PDR/statistical acceptance

For the RF/range PDR claim, use `N = 300` scheduled unique frames at `2 s` cadence over a `10 min` campaign window. Do not use `N = 100` for this gate.

Acceptance rule:

- Require `k >= 279` successful frames out of `N = 300`.
- This gives a one-sided 95% exact-binomial / Clopper-Pearson lower confidence bound of approximately `0.90076`, satisfying the required lower bound `>= 0.90`.
- Formula for reporting: `L = BetaInv(0.05; k, N-k+1)` and pass only if `L >= 0.90`.

Trial classification:

- A success is one scheduled unique frame received at the DPS ground station within its declared timing window, with expected source/destination/configuration ID, valid LoRa/frame integrity, valid sequence/timestamp, valid payload length/schema, and recorded RSSI/SNR. For `DPS-V10-T-001` storage evidence, the same accepted frame shall also appear exactly once in the accepted decoded/stored evidence stream.
- A failure is a missing frame, integrity failure, parse/schema failure, wrong ID, stale replay, out-of-window frame, duplicate replacing a missing sequence, corrupted payload accepted as valid, or loss of required RSSI/SNR/validity evidence for that trial.
- Invalid, stale, duplicate, or stray frames are logged with reject reasons. They do not add successes or trials; if they correspond to a scheduled trial, that scheduled trial is failed. Only the first valid instance of a unique expected sequence can be counted as a success.
- Independence: the `300` trials shall be predeclared unique scheduled opportunities at fixed `2 s` cadence. Do not cherry-pick, remove, or restart trials after observing outcomes.
- Retransmission rule: no deliberate application-level retransmission of a failed sequence is allowed for the strict PDR count. If the protocol uses request/response, one response to one scheduled request is one trial; a repeated request after a timeout means the original trial is failed and any late/retried response is logged separately.
- Abort rule: abort for safety, legal/site approval loss, equipment damage risk, power/configuration mismatch, logger failure that invalidates evidence, or uncontrolled site conditions. An aborted run gives no strict pass; partial data may be retained only as characterization.

## 5. Concurrency/load profile parameters

`DPS-V10-C-003` shall use the following selected load profiles.

### 5.1 Flight-cadence concurrency run

- Duration/cadence: `10 min` at `2 s` cadence, `N = 300` scheduled frames.
- Components active: LoRa forwarder, decoder, payload queue, CSV writer, dashboard, latency calculation, and normal command queue handling if present in the as-tested configuration.
- Payload size basis: current worst-case `LORA_PAYLOAD_SIZE = 100 bytes` unless a future schema recalculation supersedes it.
- Required observations: frame sequence, RX timestamp, decode timestamp, CSV append timestamp, dashboard update timestamp where available, queue depths/backlog, process liveness, memory/heap/RSS trend, dropped/rejected frames, and exception/error logs.
- Thresholds: p95 RX-to-consumer pipeline latency `< 1 s`; no crash, watchdog reset, unhandled exception, deadlock, or persistent UI/process freeze; no accepted-frame loss from queue overflow; queue/backlog remains bounded and returns to zero within `10 s` after the last scheduled frame; memory remains bounded with no monotonic leak that threatens the campaign duration.

### 5.2 Optional high-rate stress

If over-air airtime, duty-cycle, or legal margin is inadequate, perform optional stress by synthetic payload injection, serial-injected frames, or RF-cabled/attenuated frames rather than open-air transmission.

- Duration/cadence: `20 min` at `5 Hz`, `6000` injected frames.
- Purpose: characterize concurrency margin and fault hardening beyond flight cadence; it does not replace the strict 500 m RF/PDR campaign.
- Thresholds for claiming stress pass: p95 pipeline latency `< 1 s`; no crash, deadlock, watchdog reset, or unhandled exception; queue depth remains below configured capacity; no accepted-frame loss from overflow; memory remains bounded; backlog returns to zero within `60 s` after the last injected frame.
- If these thresholds are not fully instrumented, report the run as characterization only.

## 6. Affected-test update map

| Target | Required update/use of this parameter baseline |
|---|---|
| `DPS-V10-C-001` | Use the 500 m horizontal LOS RF/range campaign, matching 81.4 mm 22 AWG antennas, RSSI/SNR logging, legal/site prerequisites, and `N=300`, `k>=279` PDR acceptance. |
| `DPS-V10-C-003` | Use the 10 min flight-cadence concurrency run and optional 20 min/5 Hz synthetic or RF-cabled stress profile with bounded queue/memory/backlog and p95 latency criteria. |
| `DPS-V10-T-001` | Align valid downlink/storage frame count and PDR/statistical handling with `N=300`, `k>=279`, 2 s cadence, 100-byte airtime, and invalid/stale/duplicate rules. |
| `DPS-V10-T-005` | Use the same flight-cadence payload stream when dashboard visualization is exercised; dashboard-specific UI/browser/mapping oracles remain in the separate UI/CSV/latency definition work. |
| `SYS-RF-RANGE-PDR` | Reuse these RF campaign and exact-binomial parameters for final-article system range/PDR unless the system-level MBSE definition approves stricter conditions. |
| Final `CON-003` integration | Reference this file to close `DPS-BLK-005` and `DPS-BLK-007` at definition-decision level while preserving detailed-definition, D2/model, and execution follow-up. |

## 7. Residual prerequisites and follow-up

Before strict execution credit:

1. Create/update detailed modeled definitions for `DPS-V10-C-001`, `DPS-V10-C-003`, affected `DPS-V10-T-001`/`DPS-V10-T-005` material, and `SYS-RF-RANGE-PDR` as applicable.
2. Update D2/source-model views and regenerate PNGs where the project decides to represent these parameters in the model.
3. Freeze as-tested article/configuration IDs, firmware/build commits, exact radio settings including TX power, antenna installations, payload schema/envelope, timestamp source, logging paths, and analysis scripts.
4. Confirm legal RF operation, EIRP/duty-cycle compliance, site approval, weather/interference controls, and safety plan.
5. Execute only after the detailed definitions and evidence paths are approved; archive results under the applicable `tests/results/<test-id>/` paths.
