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

- Dummy CanSat mass/configuration matches the final/as-representative PDM drop configuration within `+/- 5%` or `+/- 10 g`, whichever is tighter, unless a controlled execution rationale approves a different tolerance. Use a scale with `<= 1 g` resolution or measurement uncertainty that supports that tolerance.
- Parachute is folded/released manually as modeled and is open/stable for the accepted measurement segment; non-open/partial-open parachute, major tangle, misfold, release-bias, or visible damage-related segment effects are failed or excluded only by predeclared anomaly rules.
- Terminal descent speed is calculated from retained video/time-distance evidence or an equivalent calibrated timebase. Strict pass requires known frame rate/timestamped frames (`>= 30 fps` unless another calibrated timebase is used), distance calibration uncertainty `<= 5%`, a side-on accepted segment after parachute open/stable and before ground-effect/landing disturbance, and measured speed plus uncertainty/guard band `<= 11 m/s`.
- Wind/environment satisfies the strict screening condition of measured wind `<= 3 m/s` or justified indoor/still-air equivalent, with ambient conditions recorded.
- No silent cherry-picking: predeclared accepted/rejected rationale is required for each run.
- Evidence includes source model version, UUT configuration, dummy/reference mass records, scale ID/status, ballast/center-of-mass notes where relevant, raw video and calibration records, analysis worksheet/script, ambient/wind records, accepted/rejected segment rationale, repeat-level results, anomalies, and waivers.

## Execution-specific strict-credit prerequisites

Strict-credit interpretation is allowed only if all of the following execution-specific items are predeclared:

- final/as-tested mass (or applicability rationale if still unknown);
- scale/camera/timebase IDs, model/serial/lot, and calibration status;
- distance-calibration method and marker fixture IDs + raw references;
- wind-meter/airstream sensor IDs + location + exposure log;
- release-fixture ID and operation log; and
- predeclared anomaly/exclusion rulebook and run-level accept/reject rationale.

If any item is missing, results are characterization/development-screening only for that run.

## Quantitative interpretation criteria (`PDM-BLK-007`)

These criteria are definition-level interpretation rules for future execution evidence; no executed values or pass/fail credit are claimed by this document update.

### Mass and configuration

- The dummy CanSat mass used for a strict fall-test interpretation shall match the final/as-representative PDM drop configuration mass within `+/- 5%` or `+/- 10 g`, whichever is tighter, unless a controlled execution rationale approves a different tolerance.
- Use a scale with `<= 1 g` resolution or include measurement uncertainty showing the tolerance can be judged.
- Record dummy mass, target/reference mass, scale ID/status, added ballast distribution, center-of-mass notes if visible/relevant, and any post-drop mass/configuration changes.
- If final mass is unknown, label the result development characterization until a final mass applicability analysis is recorded.

### Video/time-distance measurement and uncertainty

- Use retained video with known frame rate or timestamped frames; minimum `>= 30 fps` for strict workshop screening unless another calibrated timebase is used.
- Include a distance scale/drop-height reference in the camera plane; distance calibration uncertainty should be `<= 5%` of the measured distance segment for strict screening.
- Camera should view the accepted descent segment approximately side-on with parallax controlled; accepted segment must be after parachute open/stable and before ground-effect/landing disturbance.
- Compute speed from a predeclared distance/time segment or fitted trajectory; include uncertainty/guard band. Strict pass requires measured speed plus uncertainty not to exceed `11 m/s`.
- Preserve raw video, calibration images/measurements, analysis worksheet/script, accepted/rejected segment rationale, and repeat-level results.

### Wind/environment and anomaly controls

- Record wind speed/direction and ambient conditions. For strict workshop screening, use calm/light wind with measured wind `<= 3 m/s` or justify an indoor/still-air equivalent.
- Record drop height, release method, line tangle/misfold/partial-open anomalies, parachute damage after each drop, and whether the run is accepted or rejected.
- A run with non-open/partial-open parachute, major tangle, off-camera segment, uncalibrated timing/distance, or wind beyond the criterion is failed or excluded only by predeclared anomaly rules; do not silently cherry-pick.
- Existing 3 repetitions remain development screening; reliability/confidence claims require a separate binomial/statistical basis per `PM&SE/IVV.md`.

## Viewpoints

- **Statistical significance:** execute 3 v0.1 repetitions as development screening only. Do not claim reliability/confidence without a separately stated statistical basis and assumptions.
- **Fault hardening:** consider misfold/tangle, partial opening, release-fixture bias, mass mismatch, poor video calibration, wind/gusts, and damage after repeated drops.
- **Measurement/environment:** formalized by calibrated scale (`<= 1 g` resolution or adequate uncertainty), release/drop fixture, drop-height marker, calibrated video/timebase (`>= 30 fps` unless another timebase is used), time/distance reference target with `<= 5%` distance calibration uncertainty, and ambient/wind meter (`<= 3 m/s` wind for strict screening or justified indoor/still-air equivalent).

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

- Exact final mass is unknown at definition time and is treated as a pre-execution configuration input; if still unknown at execution/report time, the result is development characterization until final mass applicability is recorded.
- Verification-only test setup physical links do not replace source architecture PL coverage.
- No source v0.1 component exchanges exist, so CE presence/absence coverage is a documented v0.1 gap/N/A.
