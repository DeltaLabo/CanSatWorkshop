# PDM-V01-FC-FALL — Fall-test terminal-speed verification definition

Version gate: **PDM v0.1 -> PDM v0.2**. IADT method: **Testing**, with supporting **Demonstration** and **Inspection**. Status: **modeled definition ready; execution/report pending**.

## Source views

Copied read-only source context is in `source_views/v0.1/`:

- `PDM_v0.1_view1_physical.d2/png`
- `PDM_v0.1_view2_logical.d2/png`
- `PDM_v0.1_view3_functional_allocation.d2/png`
- `PDM_v0.1_view4_fall_test_chain.d2/png`

Source v0.1 has no modeled physical links or component exchanges; this is recorded as gap/N/A coverage rather than inventing source-model PL/CEs.

## Definition views

Rendered views are in `definition_views/`:

1. `PDM-V01-FC-FALL_view1_inventory_coverage.d2/png` — source inventory and IVV coverage/gap context.
2. `PDM-V01-FC-FALL_view2_physical_setup.d2/png` — verification-only physical fall-test setup and equipment links.
3. `PDM-V01-FC-FALL_view3_verification_allocation.d2/png` — verification functions allocated to human/test-equipment actors and the UUT allocation target.
4. `PDM-V01-FC-FALL_view4_test_sequence_chain.d2/png` — fall-test terminal-speed functional chain.
5. `PDM-V01-FC-FALL_view5_evidence_traceability_chain.d2/png` — evidence/report and traceability chain.

## Coverage

This activity covers the v0.1 fall-test functional chain and all source constraints:

- `[C] Same weight as final estimate`
- `[C] Foldable, but deployed manually`
- `[C] With parachute open`
- `[C] 11 m/s max.`

It also provides linked coverage for `[PC] Dummy CanSat`, `[PC] Top module`, `[PC] Parachute`, `[LC] Descent speed control`, and `[F] Limit terminal speed`. Standalone physical-component inspection and allocation-analysis rows remain candidates in `../README.md`.

## Pass/fail rules

Pass only if the as-executed evidence supports all applicable modeled constraints:

- Dummy CanSat mass/configuration matches the final estimate or a documented pre-execution tolerance input.
- Parachute is folded/released manually as modeled and is open for the accepted measurement segment.
- Terminal descent speed calculated from retained video/time-distance evidence is `<= 11 m/s` over the accepted segment.
- Evidence includes source model version, UUT configuration, video/log files, measurement method, environmental conditions, deviations, and anomalies.

## Viewpoints

- **Statistical significance:** execute 3 v0.1 repetitions as development screening only. Do not claim reliability/confidence without a separately stated statistical basis and assumptions.
- **Fault hardening:** consider misfold/tangle, partial opening, release-fixture bias, mass mismatch, poor video calibration, wind/gusts, and damage after repeated drops.
- **Measurement/environment:** formalized by calibrated scale, release/drop fixture, drop-height marker, calibrated video camera, time/distance reference target, and ambient/wind meter.

## Traceability

Traceability targets used because the source model lacks explicit mission/capability nodes:

- `PDM-UC-V01-FallTestTerminalSpeed`
- `PDM-UC-V01-PrepareManualParachute`
- `PDM-FE-V01-ExcessDescentSpeed`
- source constraints listed above

## Evidence and report location

Expected execution evidence/report root: `../results/PDM-V01-FC-FALL/` from this test package, equivalent to `PDM/MBSE/v0.1/tests/results/PDM-V01-FC-FALL/` from the repository root.

The report should reference this modeled definition and record model baseline, as-tested configuration, actual results, supporting evidence, pass/fail rationale, deviations, anomalies, assumptions, waivers, and limitations.

## Assumptions and blockers

- Exact final mass is unknown at definition time and is treated as a pre-execution configuration input.
- Verification-only test setup physical links do not replace source architecture PL coverage.
- No source v0.1 component exchanges exist, so CE presence/absence coverage is a documented v0.1 gap/N/A.
