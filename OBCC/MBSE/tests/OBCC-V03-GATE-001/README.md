# OBCC-V03-GATE-001 — v0.3 LoRa telemetry advancement gate

## Scope and selected version

- **Activity ID:** `OBCC-V03-GATE-001`
- **SSIV / version gate:** OBCC `v0.3 -> v0.4`
- **Chosen pending activity for this session:** Issue 003, LoRa telemetry frame/cadence/range advancement gate.
- **IADT method(s):** Testing + Analysis, with component/link Inspection for the RF/range test setup.
- **IVV source categories:** component/link, component exchange, allocation, functional chain/scenario, constraint.
- **Traceability targets:** `OBCC-UC-TelemetryDownlink`, `OBCC-FE-LostTelemetry`, and the telemetry constraint family in `OBCC-VV-CON-001`.
- **Existing v1.0 verification rows mapped:** `OBCC-VV-CE-002`, `OBCC-VV-FC-002`, `OBCC-VV-CON-001`.
- **Expected evidence/report path:** `OBCC/MBSE/tests/results/OBCC-V03-GATE-001/`.
- **Execution status:** modeled definition complete; execution and report evidence pending.

The absence of a `v0.3` Capella/D2 source baseline is an accepted OBCC lifecycle/modeling decision, not a blocker: versions may jump from `v0.x` to `v1.0`, and the mostly software-dependent subsystem was not complex enough to require incremental source-model deliveries. This gate uses the copied `v1.0` OBCC telemetry/downlink model as target-architecture context; execution reports must identify the actual `v0.3` code/configuration baseline used and acknowledge the target-context-only model reference where applicable. Do not fabricate a `v0.3` source baseline.

## References

- Project IVV: `PM&SE/IVV.md`
- OBCC requirements: `OBCC/README.md`
- Payload/frame context: `OBCC/LoRa_Frame.md`
- OBCC/DPS telemetry contract: `PM&SE/contracts/obcc_dps_lora_telemetry_contract.md`
- Getter/result-code convention: `OBCC/Variable_Getter_Template.md`
- Legacy LoRa context: `OBCC/legacy_tests/comms/LoRa_Sender_Test/LoRa_Sender_Test.ino`, `OBCC/legacy_tests/comms/LoRa_Receiver_Test/LoRa_Receiver_Test.ino`, `OBCC/legacy_tests/lora/`
- Test planning inventory: `OBCC/MBSE/tests/README.md`
- Source context copied from: `OBCC/MBSE/v1.0/`

## Baseline/source-view copies

Copied source context is under `source_views/v1.0/` and includes the v1.0 README plus all eight source D2 views and rendered PNGs. There is no `source_views/v0.3/` per the accepted lifecycle disposition; the `v1.0` copies are target context only.

## Verification-specific diagram catalogue

| View | D2 | Rendered PNG | Purpose |
|---|---|---|---|
| PV1 RF/range physical setup | `OBCC-V03-GATE-001_view1_rf_physical_setup.d2` | `OBCC-V03-GATE-001_view1_rf_physical_setup.png` | UUT, ground station, antennas, range/weather/time equipment, RF path, logging path, and target-context caveat. |
| PV2 logical CE analysis | `OBCC-V03-GATE-001_view2_logical_ce_analysis.d2` | `OBCC-V03-GATE-001_view2_logical_ce_analysis.png` | LoRa/Payload/UART exchanges, source stubs, decoder/store/display path, schema oracle, malformed-frame injection, and PDR analysis exchanges. |
| PV3 functional allocation | `OBCC-V03-GATE-001_view3_functional_allocation.d2` | `OBCC-V03-GATE-001_view3_functional_allocation.png` | Verification-only functions and SUT/ground functions allocated to actors, equipment, LCs, and PCs. |
| Functional chain | `OBCC-V03-GATE-001_view4_telemetry_gate_chain.d2` | `OBCC-V03-GATE-001_view4_telemetry_gate_chain.png` | Lab + range telemetry sequence, schema/cadence checks, malformed-frame hardening, PDR statistics, and gate classification. |

All four D2 files were rendered with the required `d2 --layout=elk` command and ELK spacing flags.

## Verification coverage table

| Verification activity ID | SSIV / development version | Model element(s) covered | IVV source category | IADT method | Traceability target | Relevant viewpoints: statistical significance and fault hardening | Pass/fail constraint(s) | Diagram/report references | Status |
|---|---|---|---|---|---|---|---|---|---|
| `OBCC-V03-GATE-001-I01` | v0.3 -> v0.4 | UUT OBCC XIAO/RFM96W/antenna, ground station RFM96W/XIAO/antenna, PC logger, RF path, stimulus harness, range/weather/time/orientation equipment | Component/link | Inspection | `OBCC-UC-TelemetryDownlink`; `OBCC-FE-LostTelemetry` | Stat: 100% inspection of the test article, receiver, antennas, and logging path. Fault hardening: missing antenna/feedline, wrong radio module, unsurveyed path, missing raw evidence path. | `PF-004`, `PF-005` | PV1; expected report `results/OBCC-V03-GATE-001/setup_inspection.md` | Definition ready; execution pending |
| `OBCC-V03-GATE-001-A01` | v0.3 -> v0.4 | LoRa downlink CE, Payload CE, ground UART/raw-frame path, decoder/dashboard/CSV writer, packet analyzer, telemetry collector/encoder allocation | Component exchange; allocation | Analysis | `OBCC-UC-TelemetryDownlink`; `OBCC-FE-LostTelemetry`; `OBCC-VV-CE-002` | Stat: 100% CE/allocation review for modeled telemetry path. Fault hardening: corrupt frame handling, sequence/timestamp preservation, no hidden decode/store path. | `PF-001`, `PF-003`, `PF-006` | PV2, PV3; expected report `results/OBCC-V03-GATE-001/ce_allocation_analysis.md` | Definition ready; execution pending |
| `OBCC-V03-GATE-001-T01` | v0.3 -> v0.4 | Telemetry collector, telemetry encoder, 35-byte target variable table excluding relative humidity and including `deployment_status`, health/status metadata, sequence/timestamp metadata | Functional chain/scenario; constraint | Testing + Analysis | `OBCC-UC-TelemetryDownlink`; `OBCC-VV-FC-002`; `OBCC-VV-CON-001` | Stat: field-by-field deterministic schema comparison over the planned frame set. Fault hardening: missing/stale values, invalid deployment status, and RH absence are explicit, not silently misinterpreted. | `PF-001`, `PF-006` | PV2, PV3, Functional chain; expected report `results/OBCC-V03-GATE-001/frame_schema.md` | Definition ready; execution pending |
| `OBCC-V03-GATE-001-T02` | v0.3 -> v0.4 | 2 s telemetry release, received frame interval stream, sequence gaps/duplicates/stale frames | Functional chain/scenario; constraint | Testing | `OBCC-UC-TelemetryDownlink`; `OBCC-VV-FC-002`; `OBCC-VV-CON-001` | Stat: use at least 59 representative intervals for a 95/95 timing claim; smaller runs are advancement characterization. Fault hardening: stale/gapped/duplicate frames are classified as failures for the cadence evidence. | `PF-002`, `PF-006` | Functional chain; expected report `results/OBCC-V03-GATE-001/cadence.md` | Definition ready; execution pending |
| `OBCC-V03-GATE-001-T03` | v0.3 -> v0.4 | PC decoder, dashboard, CSV writer, raw frame logger, malformed-frame injector, sequence/timestamp/status preservation | Functional chain/scenario; component exchange | Testing | `OBCC-FE-LostTelemetry`; `OBCC-VV-CE-002` | Stat: deterministic malformed-frame class coverage. Fault hardening: bad CRC, truncated, wrong-length, corrupt, extra-RH, missing-status, and unrecognized-status frames are rejected and logged invalid. | `PF-003`, `PF-006` | PV2, PV3, Functional chain; expected report `results/OBCC-V03-GATE-001/decode_hardening.md` | Definition ready; execution pending |
| `OBCC-V03-GATE-001-T04` | v0.3 -> v0.4 | RFM96W LoRa downlink, ground station receiver/forwarder, RF path geometry, RSSI/SNR logging, packet counts and PDR evidence | Functional chain/scenario; constraint; component/link | Testing + Analysis | `OBCC-UC-TelemetryDownlink`; `OBCC-FE-LostTelemetry`; `OBCC-VV-CON-001` | Stat: PDR pass only for `N=300` scheduled unique frames at `2 s` cadence with `k>=279` successes, giving a one-sided 95% exact binomial lower bound `>=0.90`, at `>=500 m` horizontal LOS or justified RF equivalent. Fault hardening: RF loss, bad antenna orientation, legal radio settings, weather/path effects, raw evidence retention. | `PF-004`, `PF-005`, `PF-006` | PV1, PV2, Functional chain; expected report `results/OBCC-V03-GATE-001/range_pdr.md` | Definition ready; execution pending; lab-only execution leaves range gate open |

## Pass/fail constraints

- **PF-001 — frame schema and payload content:** valid telemetry frames carry the target `OBCC-LORA-PAYLOAD-v1.0` 35-byte variable table before LoRa envelope/frame/status metadata: pitch, roll, yaw; three angular speeds; three accelerations; altitude; temperature; latitude; longitude; battery voltage; battery current; and one-byte `deployment_status` / `Parachute Deployment Status` at variable-table offset `34` (current payload byte offset `48`). The status byte shall map to the controlled enum `0..9` with code/symbol/category preserved; only `OPEN_CONFIRMED` is deployed/success. Relative humidity is absent or explicitly error-coded and is never silently decoded as another field.
- **PF-002 — cadence:** generated telemetry uses the modeled `2 s` cadence. For a 95/95 timing claim, collect at least `59` representative intervals and require every interval to meet the selected tolerance. The modeled default for this v0.3 gate is `2.0 s +/- 0.2 s` pending project confirmation.
- **PF-003 — decode/display/store hardening:** the ground path preserves sequence, timestamps, raw `deployment_status` code/symbol/category, and reject reasons through raw logs, decoder, dashboard, and CSV. Corrupt, truncated, wrong-length, bad-CRC, extra-relative-humidity, missing-status, or unrecognized-status frames are rejected and logged as invalid, not stored as valid telemetry and never displayed as deployed.
- **PF-004 — range/PDR:** at `>=500 m` horizontal LOS separation or a documented RF-equivalent setup, packet delivery passes only if `k>=279` successful frames out of `N=300` scheduled unique frames at the `2 s` cadence, giving a one-sided 95% exact binomial lower confidence bound `>=0.90`. If only lab/bench evidence is available, schema/cadence/decode items may be characterized but the range/PDR gate remains open.
- **PF-005 — RF/path/environment evidence completeness:** record endpoint positions or RF-equivalent rationale, path geometry, antenna orientation, radio settings, weather/ambient conditions, time-sync method, raw bytes, RSSI/SNR, decoded records, and analysis tool/script version.
- **PF-006 — CE/allocation consistency:** LoRa, Payload, ground UART/raw-frame, decoder/dashboard/CSV, and verification-only analysis exchanges are present, directional, and implemented consistently with the modeled v1.0 telemetry intent; telemetry functions are allocated to the modeled LCs with no hidden required path.

## Statistics and fault-hardening viewpoints

- This is a `v0.3 -> v0.4` advancement gate. It can be executed as a staged lab + range campaign, but final gate closure requires the range/PDR evidence or an explicitly justified RF-equivalent setup.
- PDR evidence uses the project IVV exact one-sided binomial policy and the OBCC/DPS telemetry contract. Reports shall predeclare `N=300` scheduled unique frames at `2 s` cadence and pass only with `k>=279` successful frames, with confidence method and lower bound recorded.
- Cadence evidence follows the project timing/deadline policy: `59/59` in-limit intervals supports a 95/95 non-parametric one-sided timing claim. Smaller sample sizes are characterization unless the report states the weaker confidence.
- Fault hardening emphasized by this gate: corrupt/malformed frame rejection, missing/stale field handling, no relative-humidity misinterpretation, RF loss visibility, RSSI/SNR/path logging, sequence gap/duplicate detection, and ground decode/store failure visibility.

## Assumptions and gaps for feedback

- Lifecycle disposition: no `v0.3` Capella/D2 source baseline is required or fabricated; copied v1.0 views are target-context only, and the report identifies the actual v0.3 code/configuration baseline.
- The exact v0.3 firmware, ground-station software, radio settings, CRC/checksum format, and frame metadata layout are not fully specified in the repository; execution must record the as-tested versions/configuration.
- `LoRa_Frame.md` and the v1.0 model both exclude relative humidity and use the selected `RFM96W` radio name; this gate requires any actual module substitution to be dispositioned.
- The `2.0 s +/- 0.2 s` cadence tolerance is a modeled planning assumption for this test definition and should be confirmed or replaced before formal execution.
- The range campaign may be staged after a lab schema/cadence/decode run. Lab-only execution cannot close `PF-004`.
- Range survey kit, weather/time reference, antenna-orientation tool, stimulus fixture, parser/decoder version, and analysis tool exact model/version identifiers are execution records that must be captured in evidence before strict credit.
