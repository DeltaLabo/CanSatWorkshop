# OBCC-V04-GATE-001 — v0.4 wireless command/state advancement gate

## Scope and selected version

- **Activity ID:** `OBCC-V04-GATE-001`
- **SSIV / version gate:** OBCC `v0.4 -> v0.5`
- **Chosen pending activity for this session:** Issue 004, wireless command uplink and On/Stand-by state advancement before deployment control is enabled.
- **IADT method(s):** Testing + Inspection + Analysis.
- **IVV source categories:** component/link, component exchange, allocation, functional chain/scenario, constraint.
- **Traceability targets:** `OBCC-UC-WirelessCommand`, `OBCC-FE-InvalidCommand`, and command/state constraint family `OBCC-VV-CON-002`.
- **Existing v1.0 candidate mapping:** `OBCC-VV-FC-003` and `OBCC-VV-CON-002`.
- **Expected evidence/report path:** `OBCC/MBSE/tests/results/OBCC-V04-GATE-001/`.
- **Execution status:** modeled definition complete; execution and report evidence pending.

No `v0.4` Capella/D2 source views exist in this repository. This definition uses the copied `v1.0` command/state, telemetry, logical, allocation, and physical views only as target-behavior context.

## References

- Project IVV: `PM&SE/IVV.md`
- OBCC requirements and state-transition requirement: `OBCC/README.md`
- LoRa frame/peripheral context: `OBCC/LoRa_Frame.md`
- Getter/result-code context, where telemetry/status observability is relevant: `OBCC/Variable_Getter_Template.md`
- Test planning inventory: `OBCC/MBSE/tests/README.md`
- Source context copied from: `OBCC/MBSE/v1.0/`

## Baseline/source-view copies

Copied source context is under `source_views/v1.0/` and includes the v1.0 README plus all eight source D2 views and rendered PNGs. There is no `source_views/v0.4/` because no v0.x Capella/D2 baseline is present.

## Verification-specific diagram catalogue

| View | D2 | Rendered PNG | Purpose |
|---|---|---|---|
| PV1 physical setup | `OBCC-V04-GATE-001_view1_test_physical_setup.d2` | `OBCC-V04-GATE-001_view1_test_physical_setup.png` | UUT, RFM95W radio path, ground command transmitter, RF monitor, telemetry observer, bench USB aid, deployment safe-load/logic probe, and ambient thermometer physical links. |
| PV2 logical interfaces | `OBCC-V04-GATE-001_view2_test_logical_interfaces.d2` | `OBCC-V04-GATE-001_view2_test_logical_interfaces.png` | LoRa command uplink, SPI command receipt, command handler, state manager, telemetry feedback, trace publisher, deployment guard, and no-serial-console analysis target. |
| PV3 functional allocation | `OBCC-V04-GATE-001_view3_test_functional_allocation.d2` | `OBCC-V04-GATE-001_view3_test_functional_allocation.png` | Verification equipment and operator functions, plus UUT command/state/telemetry functions and verification-only trace/deployment-guard functions. |
| Functional chain | `OBCC-V04-GATE-001_view4_command_state_gate_chain.d2` | `OBCC-V04-GATE-001_view4_command_state_gate_chain.png` | Valid On, valid Stand-by, replay/duplicate, and invalid-equivalence-class command sequences with pass/fail constraints. |

All four D2 files were rendered with the required `d2 --layout=elk` command and ELK spacing flags.

## Verification coverage table

| Verification activity ID | SSIV / development version | Model element(s) covered | IVV source category | IADT method | Traceability target | Relevant viewpoints: statistical significance and fault hardening | Pass/fail constraint(s) | Diagram/report references | Status |
|---|---|---|---|---|---|---|---|---|---|
| `OBCC-V04-GATE-001-I01` | v0.4 -> v0.5 | RFM95W/XIAO command-state UUT, antenna/RF path, state/status telemetry path, USB flash/setup port, deployment output safe-load or logic probe, RF monitor, telemetry observer, ambient thermometer | Component/link; constraint | Inspection | `OBCC-UC-WirelessCommand`; `OBCC-FE-InvalidCommand`; no serial-console constraint | Stat: 100% inspection of the integrated test article and test means. Fault hardening: RF path present, safe deployment monitor present, USB path identified as bench-only. | `PF-001`, `PF-002`, `PF-006` | PV1, PV3; expected report `results/OBCC-V04-GATE-001/inspection.md` | Definition ready; execution pending |
| `OBCC-V04-GATE-001-A01` | v0.4 -> v0.5 | LoRa command uplink, RFM95W-to-XIAO SPI RX, Command Handler, OBCC Supervisor/State Manager, Telemetry Encoder, Command-result Trace Publisher, Deployment Output Guard, telemetry observer, no serial-console command path | Component exchange; allocation; constraint | Analysis | `OBCC-UC-WirelessCommand`; `OBCC-FE-InvalidCommand`; `OBCC-VV-CON-002` | Stat: 100% interface/allocation review for command/state path and bench-only USB path. Fault hardening: no hidden command authority, no deployment enable before v0.5, command result observable over LoRa telemetry. | `PF-002`, `PF-007` | PV2, PV3; expected report `results/OBCC-V04-GATE-001/interface_allocation_analysis.md` | Definition ready; execution pending |
| `OBCC-V04-GATE-001-T01` | v0.4 -> v0.5 | Valid wireless On and Stand-by commands, Command Handler validation, State Manager On/Stand-by transition, telemetry state/result publication, RF and deployment side-effect monitors | Functional chain/scenario; constraint | Testing | `OBCC-UC-WirelessCommand` | Stat: for separate R90/C95 screening claims, plan `29/29` successful applications for each valid command class; fewer trials are advancement characterization only. Fault hardening: accepted exactly once, no duplicate transition, telemetry-visible result. | `PF-003`, `PF-006`, `PF-008` | PV2, PV3, Functional chain; expected report `results/OBCC-V04-GATE-001/valid_commands.md` | Definition ready; execution pending |
| `OBCC-V04-GATE-001-T02` | v0.4 -> v0.5 | Invalid/corrupt/malformed/unsupported/out-of-context command rejection, command error logging, state preservation, telemetry rejection evidence | Functional chain/scenario; constraint | Testing | `OBCC-FE-InvalidCommand`; `OBCC-VV-CON-002` | Stat: invalid coverage is exhaustive by equivalence class unless waived; one trial per class is screening, not reliability demonstration. Fault hardening: bad CRC/corrupt payload, malformed header/footer/length, unsupported opcode, out-of-context command, stale context. | `PF-004`, `PF-006`, `PF-008` | PV2, PV3, Functional chain; expected report `results/OBCC-V04-GATE-001/invalid_commands.md` | Definition ready; execution pending |
| `OBCC-V04-GATE-001-T03` | v0.4 -> v0.5 | Replay/duplicate command hardening, transition count or equivalent oracle, deployment side-effect monitor | Functional chain/scenario; constraint | Testing / Analysis | `OBCC-FE-InvalidCommand`; pre-`v0.5` deployment-safety gate context | Stat: replay/duplicate vectors are mandatory invalid equivalence classes; repeated cases classify any second transition or deployment edge as a failure. Fault hardening: replayed valid frame, duplicate packet, stale trial ID, RF retransmission artifact. | `PF-005`, `PF-006`, `PF-008` | PV1, PV2, PV3, Functional chain; expected report `results/OBCC-V04-GATE-001/replay_duplicate.md` | Definition ready; execution pending |

## Pass/fail constraints

- **PF-001 — setup/component/link inspection:** command-state UUT, RFM95W, antenna/RF path, telemetry observer, RF link monitor, command transmitter, deployment safe-load/logic probe, and ambient thermometer are present, identified, connected as modeled, and dispositioned before command trials begin.
- **PF-002 — no serial-console flight operator path:** On/Stand-by command authority and state observability are provided over LoRa command uplink and LoRa telemetry. USB serial may be used only for flashing/setup or bench diagnostics and must be disconnected, disabled, or shown non-authoritative for command trials.
- **PF-003 — valid command behavior:** each valid wireless On or Stand-by command is accepted exactly once, causes the modeled state transition, updates the command/state transition count or equivalent oracle once, is reflected in telemetry, and produces no deployment side effect.
- **PF-004 — invalid command rejection:** each invalid/corrupt/malformed/unsupported/out-of-context/stale-context vector is rejected or ignored, produces telemetry/log evidence of the rejection class when supported, preserves the previous On/Stand-by state, and produces no deployment side effect.
- **PF-005 — replay/duplicate hardening:** replaying or duplicating a previously accepted command frame does not increment the accepted-transition count a second time, does not create an unintended state transition, and does not produce deployment side effects.
- **PF-006 — environmental/evidence condition:** before repetitions, record calibrated ambient thermometer model/serial and reading, radio settings, firmware/configuration IDs, RF monitor and telemetry observer clock synchronization, and as-tested UUT configuration. Missing records are report deviations.
- **PF-007 — exchange/allocation consistency:** implemented command/state component exchanges and allocations match the modeled LoRa/SPI/Command Handler/State Manager/Telemetry path; no hidden serial-console command path or unmodeled deployment bypass is required for flight operation.
- **PF-008 — statistical and coverage interpretation:** valid-command statistics follow the project binomial policy; invalid command coverage is by declared equivalence class, and any forbidden event is counted as a failure.

## Statistics and fault-hardening viewpoints

- This is a `v0.4 -> v0.5` advancement gate, not final v1.0 flight-readiness closure.
- For valid commands, `29/29` zero-failure applications support an R90/C95 screening claim. If On and Stand-by need separate claims, plan `29/29` for each command class; a pooled `29/29` only supports the combined command path.
- Invalid commands are covered by equivalence class rather than by pooled reliability statistics. Required classes are malformed header/footer/length, bad CRC/corrupt payload, unsupported opcode, out-of-context command, replay, duplicate, and stale trial ID/context when the implementation exposes such metadata.
- Fault-hardening emphasis: RF corruption, duplicate/replayed frames, stale or out-of-context commands, hidden serial fallback, and forbidden deployment side effects before deployment control is enabled.
- Timing/rate claims are not primary for this gate. Telemetry is used as the evidence channel and should remain consistent with the v1.0 2 s heartbeat/status context where implemented.

## Assumptions and gaps for feedback

- No v0.4 Capella/D2 source baseline is present; copied v1.0 views are target context only.
- The exact command frame schema, CRC field, sequence/trial ID, replay-protection mechanism, and command-result telemetry fields are not specified in the repository; execution must document the actual oracle used to determine “accepted exactly once.”
- `LoRa_Frame.md` includes legacy/peripheral context and lists `RFM96W`, while the v1.0 model uses `RFM95W`; execution should record the actual fitted radio module and settings.
- v0.4 is before deployment control enablement; the modeled deployment monitor is a safe-load/logic-probe side-effect check, not a servo actuation test.
- USB serial may exist as a bench aid, but any command success requiring serial operator input is a failure for this gate.
- Ambient thermometer model and calibration status are TBD and must be captured in the execution evidence.
- This was a non-interactive subagent run; needed feedback is captured here instead of requested live.
