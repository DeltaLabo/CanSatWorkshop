# DPS-V10-T-003 — CanSat receive-path command verification definition

- **SSIV / version:** DPS-v1.0 (confirmed by user for current detailed definitions).
- **IADT method:** Testing.
- **IVV source category:** functional chain/scenario.
- **Model elements covered:** FC03 CanSat receive path; CanSat LoRa Transceiver `Receive incoming data`; OBCC `Receive LoRa RX Interrupt` and `Read command`; CE-01 CanSat radio-to-OBCC SPI path.
- **Traceability target:** inferred use case “OBCC receives wireless state command”; inferred feared event “spoof, no-frame interrupt or old buffer is accepted as a valid command”. Formal mission/capability/use-case IDs are not present in the source model.
- **References cited in diagrams:** P0 (`PM&SE/IVV.md`), R1-R5 and R8-R13 from `../references/INDEX.md`.
- **Expected report/evidence folder:** `DPS/MBSE/tests/results/DPS-V10-T-003/`.

## Baseline views copied

The unmodified DPS v1.0 Capella/D2 source views and rendered PNGs are copied under [`baseline/`](./baseline/) for traceability. The verification-specific model views in this folder extend the copied baseline with test means, verification-only evidence functions, pass/fail constraints, RF command stimuli and spoof/no-frame/old-buffer hardening sequences.

## Verification-specific diagrams

| View | Purpose |
|---|---|
| [`DPS-V10-T-003_view1_physical_test_context.d2`](./DPS-V10-T-003_view1_physical_test_context.d2) | Physical context with CanSat command-receive UUT, command test transmitter, OBCC debug monitor and controlled RF/debug probe links. |
| [`DPS-V10-T-003_view2_logical_test_context.d2`](./DPS-V10-T-003_view2_logical_test_context.d2) | Logical/component-exchange context with command test transmitter, OBCC debug monitor, Test Operator and verification-only Command Receive Evidence Collector LC. |
| [`DPS-V10-T-003_view3_functional_allocation_test_context.d2`](./DPS-V10-T-003_view3_functional_allocation_test_context.d2) | Allocation of operator, transmitter, debug monitor, clock, CanSat receive functions and evidence-collector functions. |
| [`DPS-V10-T-003_view4_valid_cansat_command_receive_chain.d2`](./DPS-V10-T-003_view4_valid_cansat_command_receive_chain.d2) | Functional chain for valid CanSat command-receive statistical screening. |
| [`DPS-V10-T-003_view5_spoof_no_frame_old_buffer_hardening_chain.d2`](./DPS-V10-T-003_view5_spoof_no_frame_old_buffer_hardening_chain.d2) | Functional chain for spoof/no-frame/old-buffer rejection and recovery hardening. |

Rendered PNGs have been generated beside the D2 sources.

## Pass/fail constraints

1. **Environment and setup:** RF geometry or attenuator, command transmitter settings, CanSat antenna state, OBCC debug-monitor connection, probe ID, timebase, software revisions and evidence directory are recorded before valid and fault trials.
2. **Valid-command statistics:** at least 60 valid command frames are transmitted to the CanSat radio. Each shall be read by OBCC exactly once with the expected state/sequence. Zero missing, wrong-state, duplicate or stale command acceptances are allowed. For 60/60 successes, the one-sided 95% exact-binomial lower bound is about 0.95 for this controlled setup.
3. **Fault-hardening trials:** at least 60 invalid trials are executed across spoof/wrong sender or wrong type, no-frame/spurious interrupt, old-buffer/stale replay, duplicate sequence and malformed/CRC-bad command-frame cases.
4. **Invalid-case rejection:** zero invalid trials are accepted as commands; every invalid case is rejected, ignored or logged; the previous valid command is never re-read.
5. **Recovery:** after the invalid set, a valid follow-up command is accepted exactly once.
6. **Statistics viewpoint:** valid command receive is exact-binomial screening; invalid-case rejection is counted by fault class as screening evidence and is not a high-confidence reliability claim without additional sample-size rationale.
7. **Fault/anomaly handling:** missing RX interrupt, old-buffer reuse, duplicate read, stale previous command, debug-probe-induced reset, accidental power cycle, missing evidence or timing ambiguity is a failure or report anomaly/limitation unless dispositioned.

## Test sequence checklist

| Sequence | Stimulus | Expected behavior | Evidence |
|---|---|---|---|
| Valid CanSat command receive | 60 valid LoRa command frames with known state/sequence and valid framing/CRC. | CanSat LoRa Transceiver receives each frame; OBCC receives RX interrupt and reads exactly one matching command; no missing/wrong/duplicate/stale command acceptance. | Transmitter command log, OBCC interrupt/read log, accepted-command comparison, k/N statistics. |
| Spoof/no-frame/old-buffer hardening | 60 invalid trials spanning spoof/wrong sender/type, no-frame/spurious interrupt, old-buffer/stale replay, duplicate sequence and malformed/CRC-bad command frame. | OBCC rejects, ignores or logs every invalid case; no previous valid command is re-read. | Fault reference log, OBCC rejection/no-command log, stale-buffer assertion, clean-rejection counts by fault class. |
| Follow-up recovery | One valid command after invalid trials. | Valid follow-up command is accepted exactly once, proving the receive path recovers after rejection. | Follow-up TX log, OBCC read log, comparison/verdict. |

## Constraint coverage disposition

- This activity verifies the FC03 CanSat-side command receive path. It does **not** replace `DPS-V10-T-002`, which verifies the ground-station dashboard command/uplink and cooldown behavior.
- C07 cooldown remains covered by `DPS-V10-T-002`; C01 range remains covered by `DPS-V10-C-001`.
- CE-01 SPI presence/intent remains covered by `DPS-V10-A-001`; this activity supplies behavioral receive-path evidence using that boundary.

## Evidence expected in report

The report in `tests/results/DPS-V10-T-003/` should reference these modeled diagrams and record: model baseline, as-tested CanSat/radio/software configuration, command transmitter settings, RF setup, OBCC debug-monitor setup, timebase, valid command log, OBCC interrupt/read log, invalid fault log, accepted/rejected command comparison, valid-command `k/N`, invalid-case `k/N` by class, follow-up recovery result, pass/fail rationale, deviations, anomalies, waivers and limitations.
