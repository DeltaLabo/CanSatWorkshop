# Integration, Verification, and Validation Plan

> For any ARCADIA model defining a System Integration Version or Subsystem Integration Version (SSIV), what are the minimum verification requirements when applying the techniques of Inspection, Analysis, Demonstration, and Testing (IADT)?

## Principles

### 1. Model as source of truth
For model-based verification, the ARCADIA model is the authoritative definition of the verification activity. When a verification activity is represented by a functional chain or scenario, the model should define the test item, test means, interfaces, stimuli, expected behavior, constraints, and relevant operational context.

### 2. Reports by reference
Verification reports should reference the modeled verification definition rather than duplicate it. A report exists to bind evidence to a specific modeled verification activity, baseline, and as-executed configuration.

Information already controlled in the model need not be restated in the report unless it is needed to:
- identify the exact as-tested configuration,
- record actual execution conditions,
- explain the observed results, or
- document deviations from the modeled verification definition.

## Project-wide test-plan conventions

Text files under `*/tests/` are temporary planning references from which the verification scenarios should later be modeled in ARCADIA/Capella. The model remains the source of truth.

Use these conventions for every subsystem test folder:

- The folder entry point is `tests/README.md`.
- Evidence is archived under `tests/results/<test-id>/` from the project-root perspective, i.e. `results/<test-id>/` inside each `tests/` folder, unless a campaign-level results folder is explicitly agreed.
- Scenario tables should use, or be easily mappable to, these columns: `ID`, `Scenario type`, `View/chain`, `Method (I/A/D/T)`, `Test/procedure`, `Sample/stat basis`, `Pass criteria`, `Evidence`.
- Every scenario should trace to a modeled component, exchange, function, functional chain, constraint, feared event, or use case.

## Project-wide statistical policy

Use this policy unless a safety standard, launch provider, component datasheet, or modeled constraint is stricter.

1. **Binary success/failure claims:** use exact one-sided binomial / Clopper-Pearson confidence bounds. Record successes `k`, trials `n`, confidence, and required success probability. Useful zero-failure planning points at 95% confidence:
   - `29/29` demonstrates at least 90% success probability.
   - `59/59` demonstrates about 95% success probability.
   - `299/299` is the order of magnitude needed to support a `<1%` failure-probability claim.
2. **Packet delivery / PDR:** pass only when the one-sided 95% exact lower confidence bound is at least the required PDR. For `PDR ≥ 0.90`, `96/100` valid frames is a useful planning point.
3. **Continuous measurement accuracy:** collect at least `n ≥ 30` stable samples per operating point; retain raw data; report bias, standard deviation, confidence interval, and expanded uncertainty. A limit is met only when the measured value plus/minus expanded uncertainty remains inside the modeled requirement.
4. **Timing and deadline limits:** for a 95/95 non-parametric one-sided tolerance claim, collect at least `n = 59` representative samples and require every sample to meet the limit. Smaller samples are characterization unless the report states the weaker confidence.
5. **Rates and sustained performance:** evaluate mean rate, interval distribution, stale/dropped frames, and worst gaps. High-rate frame samples support performance evidence, but repeated samples on one article are not automatically independent reliability trials.
6. **Fault injection:** classify each trial as pass/fail, include forbidden events as failures, and state whether the evidence is workshop screening or a statistical reliability demonstration.

## CanSat MBSE glossary and cross-subsystem semantics

- **Internal acquisition / control rate:** subsystem sensing and control loops may run at `≥5 Hz`; this is the internal rate used especially by parachute-trigger logic.
- **Telemetry cadence:** the v1.0 LoRa heartbeat/status/measurement downlink cadence is `2 s`. Telemetry frames may contain the latest internally acquired values plus age/stale/error metadata.
- **Shared ADS/AMS sensor-to-OBCC freshness contract:** [`PM&SE/contracts/sensor_obcc_freshness_contract.md`](contracts/sensor_obcc_freshness_contract.md) governs ADS/AMS data offered to OBCC and parachute-control consumers. ADS and AMS shall support OBCC requests at `5 Hz` (`200 ms` period); at every `2 s` telemetry push, required data is fresh only when status is `VALID` and sample age is `<=400 ms` (two failed `5 Hz` samples). The required status enum is exactly `VALID`, `STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, `INIT_FAIL`; timeout, fault, initialization failure, and no-data conditions shall not leave old data marked `VALID`.
- **Startup critical fault:** a failed startup check for a critical component prevents entry into operational mode so flight readiness is not falsely declared.
- **Runtime sensor fault:** a mid-flight sensor/getter failure shall not block or brick the CanSat. The getter returns a bounded error/result code, health telemetry discloses the fault, and OBCC/PDM logic commands emergency deployment when needed by the modeled safety policy.
- **Physical-view context vs ownership:** subsystem physical views may show other modules to express integration links. That does not transfer ownership of those modules; detailed design ownership stays with the corresponding subsystem model.
- **Version semantics:** versions below `v1.0` are incremental delivery baselines. Development-only paths such as Serial0 logging may appear there even when the `v1.0` flight architecture has no required serial-console operator path.

## Minimum Verification Requirements

1. **Physical components and physical links**  
   For every physical component or physical link in the model, perform a presence/absence inspection. Pass if all modeled physical components and physical links are present.
   For every physical component, consider performing a unit test modeled as a functional chain.

2. **Component exchanges**  
   For every component exchange, perform a presence/absence analysis. Pass if all modeled component exchanges are present and implemented consistently with the model intent. For example, if the component exchange is modeled as multi-point communication, analyze whether the implemented protocol is consistent with that intent, such as I2C or SPI rather than UART.

3. **Functional allocation to logical components**  
   For every logical component, analyze correct functional allocation. Pass if all intended functions are allocated and no foreign functions are allocated. In practice, allocation can be evaluated by analyzing whether data and resource flows move through the correct component exchanges when crossing logical component boundaries.

4. **Functional chains and scenarios**  
   For every functional chain or scenario:
   - extend it to cover the verification means, whether human or automated,
   - define pass conditions for that verification activity as constraints,
   - analyze the chain or scenario from all relevant viewpoints, including at least statistical significance and fault hardening where applicable,
   - and link it to the relevant mission, capability, use case, or feared event.

   If the model has not yet been assigned the required functional chains or scenarios, create them.

5. **Constraint coverage**
   - **5a.** For every constraint, assign it as a pass condition to at least one functional chain or scenario. Inspect that every constraint is assigned to all relevant functional chains and scenarios from all relevant viewpoints.
   - **5b.** If 5a is not applicable, design a new verification activity modeled as a functional chain, including verification means, and analyze it from at least the statistical significance and fault hardening viewpoints where applicable. Define pass criteria for the new verification activity from the constraint.
   - **5c.** If neither 5a nor 5b is applicable, design a new presence/absence analysis test and list all relevant viewpoints.

6. **SSIV completeness**  
   Ensure SSIV documents contain, or reference, all verification activities associated with that SSIV.

## Completeness of the Modeled Verification Definition

When a verification activity is modeled as a functional chain or scenario, completeness should be pursued primarily in the model rather than in the report.

Each modeled verification definition should include, as applicable:
- the item under verification,
- the verification means,
- participating components and exchanges,
- stimuli or input conditions,
- expected observable behavior or outputs,
- pass/fail constraints,
- relevant operational or environmental context,
- relevant viewpoints,
- and traceability to missions, capabilities, use cases, feared events, or constraints.

## Reporting

Generate a report, or equivalent controlled record, for each verification activity or verification campaign.

Each report shall:
1. identify the referenced model elements, such as functional chain, scenario, constraint, and SSIV,
2. identify the model baseline or version used for verification,
3. identify the as-tested or as-analyzed configuration where more specific than the model,
4. record actual results and supporting evidence,
5. document pass/fail rationale,
6. document deviations from the modeled verification definition,
7. document anomalies, waivers, assumptions, or limitations affecting interpretation of the result.

A report should not duplicate model content unnecessarily. If the UUT, environment, interfaces, or test means are already adequately defined in the ARCADIA model, the report may reference the model definition and record only execution-specific details.

### Minimum report content by verification category

1. **Physical component and physical link inspections**  
   Include the results of all physical component and physical link presence/absence inspection activities.

2. **Component exchange analyses**  
   Include the results of all component exchange presence/absence analysis activities, with pass/fail rationale.

3. **Functional allocation analyses**  
   Include the results of all functional allocation analysis activities, with relevant viewpoints and pass/fail rationale.

4. **Constraint-derived presence/absence analysis tests**  
   Include the results of all presence/absence analysis tests derived from constraints, with relevant viewpoints and pass/fail rationale.

5. **Functional chain and scenario verification activities**  
   Include a section for every functional chain or scenario derived from capabilities, missions, use cases, feared events, or constraints. Document the associated mission, capability, use case, feared event, or constraint, the relevant viewpoints, the supporting evidence, and the rationale for the pass/fail decision.
