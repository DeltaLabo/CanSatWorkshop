# DPS-V10-T-001 — Downlink decode and storage verification definition

- **SSIV / version:** DPS-v1.0 (confirmed by user for current detailed definitions).
- **IADT method:** Testing.
- **IVV source category:** Functional chain/scenario, with constraint coverage for C05.
- **Model elements covered:** FC01 downlink decode/storage; Ground LoRa Transceiver, LoRa Forwarder, Decoder, CSV Writer; UART/Payload component exchanges; C05 unique CSV-name constraint.
- **Traceability target:** inferred use case “receive, decode, timestamp and store OBCC telemetry”; inferred feared event “corrupt or stale RF/UART frame accepted as valid telemetry”. Formal mission/capability/use-case IDs are not present in the source model.
- **References cited in diagrams:** P0 (`PM&SE/IVV.md`), R1-R5 and R8-R15 from `../references/INDEX.md`.
- **Selected parameter/oracle baselines:** [DPS-V10 RF range, LoRa airtime, PDR, and concurrency parameters](../DPS-V10_RF_Range_Concurrency_Parameters.md); [DPS-V10 UI, CSV, latency, and dashboard layout oracles](../DPS-V10_UI_CSV_Latency_Oracles.md).
- **Expected report/evidence folder:** `DPS/MBSE/tests/results/DPS-V10-T-001/`.

## Baseline views copied

The unmodified DPS v1.0 Capella/D2 source views and rendered PNGs are copied under [`baseline/`](./baseline/) for traceability. The verification-specific model views in this folder extend the copied baseline with test means, verification-only functions, pass/fail constraints, and fault-hardening sequences.

## Verification-specific diagrams

| View | Purpose |
|---|---|
| [`DPS-V10-T-001_view1_physical_test_context.d2`](./DPS-V10-T-001_view1_physical_test_context.d2) | Physical context, including LoRa test transmitter and controlled RF path. |
| [`DPS-V10-T-001_view2_logical_test_context.d2`](./DPS-V10-T-001_view2_logical_test_context.d2) | Logical/component-exchange context, including Test Operator EA and verification-only Test Evidence Collector LC. |
| [`DPS-V10-T-001_view3_functional_allocation_test_context.d2`](./DPS-V10-T-001_view3_functional_allocation_test_context.d2) | Allocation of operator, equipment, SUT, and verification-only evidence functions. |
| [`DPS-V10-T-001_view4_valid_downlink_test_chain.d2`](./DPS-V10-T-001_view4_valid_downlink_test_chain.d2) | Functional chain for the valid-frame statistical downlink test sequence. |
| [`DPS-V10-T-001_view5_corrupt_frame_hardening_chain.d2`](./DPS-V10-T-001_view5_corrupt_frame_hardening_chain.d2) | Functional chain for corrupt-frame rejection and recovery hardening. |

Rendered PNGs have been generated beside the D2 sources. Regenerate them with the project Capella-D2 command:

```sh
d2 --layout=elk \
  --elk-padding="[top=20,left=20,bottom=20,right=20]" \
  --elk-nodeNodeBetweenLayers=30 \
  --elk-edgeNodeBetweenLayers=20 \
  <view>.d2 <view>.png
```

## Pass/fail constraints

1. **Environment and setup:** calibrated ambient thermometer read before repetitions; lab ambient 15 °C to 30 °C and stable within ±2 °C; RF path, antenna state, transmitter settings and ground-station configuration recorded. Where RF/range/PDR evidence is claimed, use the selected baseline of 915 MHz, SF7, BW 125 kHz, CR 4/5, explicit header, CRC on, preamble 8, 100-byte airtime basis, and the controlled antenna/range/site evidence from the RF parameter document.
2. **Valid-frame statistics:** `N = 300` scheduled valid frames at `2.0 s ±0.2 s`; one-sided 95% exact Clopper-Pearson lower bound for decoded-and-stored PDR is `≥0.90` (`k ≥ 279` for `N = 300`). The predeclared valid-frame status sequence shall cover every `deployment_status` code `0..9`. A frame is valid for storage credit only when it uses the declared `OBCC-LORA-PAYLOAD-v1.0` schema, payload length/order/encoding, and a recognized `deployment_status` code `0..9` mapped to the controlled enum.
3. **Latency and data integrity:** p95 RX-to-CSV latency `<1 s`; CSV rows equal accepted decoded frames; payload and sequence match transmitter log; CSV/session evidence uses the selected no-overwrite session naming, monotonic row order, row-count/checksum/content match oracle, and preserved deployment-status columns with the exact names `deployment_status_code`, `deployment_status`, and `deployment_status_category`.
4. **Fault hardening:** at least 30 invalid-frame trials across CRC-bad, truncated/short, wrong payload type, stale/duplicate sequence, missing status byte, and invalid/unrecognized `deployment_status` cases; zero invalid frames appended to CSV or queued as timestamped payload; every invalid frame rejected or logged with reject reason; subsequent valid follow-up accepted once. `COMMAND_SENT`, in-progress, fault, and `UNKNOWN` status values are never credited as deployed.

## Evidence expected in report

The report in `tests/results/DPS-V10-T-001/` should reference these modeled diagrams and selected parameter/oracle baselines and record: model baseline, as-tested hardware/software configuration, payload schema/version, field order and `deployment_status` byte offset/encoding, decoder/parser version, transmitter log with expected status sequence, CSV output with raw status code/symbol/category, decoder/error logs and invalid-status reject reasons, ambient reading, RF/radio setup, computed PDR/latency, CSV/session integrity comparison, PDM/actuator confirmation evidence for any `OPEN_CONFIRMED` row, corrupt-frame k/n by class, pass/fail rationale, deviations, anomalies, waivers and limitations.
