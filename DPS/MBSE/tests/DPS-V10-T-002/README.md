# DPS-V10-T-002 — Dashboard command/uplink and cooldown verification definition

- **SSIV / version:** DPS-v1.0 (confirmed by user for current detailed definitions).
- **IADT method:** Testing.
- **IVV source category:** functional chain/scenario, with constraint coverage for C07.
- **Model elements covered:** FC02 dashboard command/uplink; Dashboard, Decoder, LoRa Forwarder and Ground LoRa Transceiver functions; Command/UART/SPI component-exchange path; C07 5 s toggle cooldown.
- **Traceability target:** inferred use case “wireless state command”; inferred feared event “command spam, duplicate or stale command is transmitted”. Formal mission/capability/use-case IDs are not present in the source model.
- **References cited in diagrams:** P0 (`PM&SE/IVV.md`), R1-R5 and R8-R13 from `../references/INDEX.md`.
- **Expected report/evidence folder:** `DPS/MBSE/tests/results/DPS-V10-T-002/`.

## Baseline views copied

The unmodified DPS v1.0 Capella/D2 source views and rendered PNGs are copied under [`baseline/`](./baseline/) for traceability. The verification-specific model views in this folder extend the copied baseline with test means, verification-only functions, pass/fail constraints, RF command capture and cooldown-hardening sequences.

## Verification-specific diagrams

| View | Purpose |
|---|---|
| [`DPS-V10-T-002_view1_physical_test_context.d2`](./DPS-V10-T-002_view1_physical_test_context.d2) | Physical context, including the ground-station command-uplink path and external RF command monitor. |
| [`DPS-V10-T-002_view2_logical_test_context.d2`](./DPS-V10-T-002_view2_logical_test_context.d2) | Logical/component-exchange context, including Test Operator, UI Automation Driver, RF Command Monitor and verification-only Command Test Evidence Collector LC. |
| [`DPS-V10-T-002_view3_functional_allocation_test_context.d2`](./DPS-V10-T-002_view3_functional_allocation_test_context.d2) | Allocation of operator, automation, clock, RF-monitor, SUT and verification-only evidence functions. |
| [`DPS-V10-T-002_view4_valid_command_uplink_test_chain.d2`](./DPS-V10-T-002_view4_valid_command_uplink_test_chain.d2) | Functional chain for valid dashboard-toggle command/uplink statistical screening. |
| [`DPS-V10-T-002_view5_cooldown_duplicate_hardening_chain.d2`](./DPS-V10-T-002_view5_cooldown_duplicate_hardening_chain.d2) | Functional chain for C07 cooldown, duplicate/stale-command suppression and recovery after cooldown. |

Rendered PNGs have been generated beside the D2 sources.

## Pass/fail constraints

1. **Environment and setup:** dashboard URL/browser, UI automation method, serial port, ground radio settings, RF monitor settings, antennas/attenuator or fixed geometry, monotonic time source, software revisions and evidence directories are recorded before the run.
2. **Valid-command statistics:** at least 60 valid state toggles are issued outside cooldown. Each accepted toggle shall produce exactly one RF command frame matching the expected state; zero wrong states, zero duplicate RF command frames and zero missing commands are allowed. For 60/60 successes, the one-sided 95% exact-binomial lower bound is about 0.95 for this controlled setup.
3. **Cooldown / C07:** at least 30 rapid-toggle bursts are executed. Each burst starts with one valid toggle followed by at least three rapid repeated/stale toggle attempts during cooldown and one post-cooldown valid toggle for recovery. Only the first toggle in each burst may enqueue/transmit; suppressed toggles shall produce zero extra queue entries and zero extra RF frames. UI re-enable time shall be `5.0 s ±0.5 s` from the first accepted toggle, using the monotonic test timebase.
4. **Recovery:** after cooldown re-enable, the post-cooldown valid toggle is accepted once and produces exactly one RF command frame matching the expected state.
5. **Fault hardening:** stale command replay, duplicate UI event, command queue bypass, direct Dashboard-to-radio path, UART write failure, SPI/radio-not-ready error and missing RF capture are failures unless explicitly dispositioned as limitations/waivers.
6. **Statistics viewpoint:** the valid-command sequence is exact-binomial screening; the cooldown sequence is duplicate-suppression screening. Reports shall record `k/N`, timing min/median/max and anomalies by trial/burst ID.

## Paired UART command/telemetry evidence

The source PV2 now models CE-03 as paired ground-station UART exchanges: **LoRa Forwarder → PC Decoder** telemetry bytes and **Decoder → LoRa Forwarder** command bytes over the same serial/USB path. This activity supplies behavioral evidence for the command side. Reports must include Decoder→Forwarder command-byte evidence, Forwarder→Decoder telemetry-byte evidence where applicable, and RF command capture.

## Test sequence checklist

| Sequence | Stimulus | Expected behavior | Evidence |
|---|---|---|---|
| Valid command/uplink | 60 valid state toggles outside cooldown, alternating expected state. | Dashboard catches toggle and pushes command; Decoder consumes and forwards; Forwarder reads/generates LoRa frame; ground radio transmits; RF monitor captures exactly one matching command frame per accepted toggle. | UI event log, command queue/decoder log, forwarder/serial log, RF capture log, command sequence comparison, k/N statistics. |
| Cooldown suppression | 30 bursts, each with one valid toggle plus ≥3 rapid repeated/stale toggles during cooldown. | First toggle queues/transmits once; Dashboard disables toggle; suppressed attempts create no queue entries/RF frames; UI re-enables at 5.0 s ±0.5 s. | UI timing log, command queue counts, forwarder counts, RF capture count, cooldown timing distribution. |
| Post-cooldown recovery | One valid toggle after each cooldown re-enable. | Post-cooldown toggle is accepted once and transmitted once with expected state. | UI log, RF capture, queue/forwarder logs. |

## Constraint coverage disposition

- **C07** is directly assigned to this activity as a pass/fail condition.
- This activity verifies FC02 command/uplink behavior on the ground-station side. It does not claim the CanSat-side command receive path; that remains assigned to `DPS-V10-T-003`.
- It does not claim C01 range performance; range remains assigned to `DPS-V10-C-001`.
- It does not replace the component-exchange presence/intent analysis in `DPS-V10-A-001`; it supplies behavioral evidence for the CE-03b UART command path.

## Evidence expected in report

The report in `tests/results/DPS-V10-T-002/` should reference these modeled diagrams and record: model baseline, as-tested hardware/software configuration, browser/UI automation details, serial/radio/RF-monitor configuration, monotonic timebase, UI event log, decoder/command queue log, forwarder/serial log, RF capture log, valid-command `k/N`, cooldown burst `k/N`, re-enable timing distribution, pass/fail rationale, CE-03b UART command evidence, deviations, anomalies, waivers and limitations.
