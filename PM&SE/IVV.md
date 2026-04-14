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

## Minimum Verification Requirements

1. **Physical components and physical links**  
   For every physical component or physical link in the model, perform a presence/absence inspection. Pass if all modeled physical components and physical links are present.

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
