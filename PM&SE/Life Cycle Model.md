# An End-to-End Practical Guide to Engineering Project Management based on MBSE

## Lifecycle Stages and Gates

Based on the NASA Systems Engineering Handbook.

### Pre-Phase A: Concept Studies                            

Conduct customer research to generate a comprehensive corpus of stakeholder requirements.
Even though stakeholders may be contacted in later phases, this initial exploration must be thorough.
The principle of focusing on what stakeholders need to accomplish, and not how they will do so, applies during the entire phase.

The means of contacting stakeholders are the expected channels: interviews, focus groups, and contextual observation (field visits).

During all stakeholder contact, the following techniques can be applied to systematically surface requirement from unstructured communications:

- The ORID method to conduct interviews
- Feedback Grids, Empathy Maps, Journey Maps to categorize customer feedback
- Paper Prototyping to gather early feedback from stakeholders

During this phase, there should be viewpoints responsible for documenting the systems already in place (if any) and the available means and resources.
Existing systems specifically don't need to be formally modelled, since the OA focuses on needs prior to a solution in the form of a system.
If existing needs represent a constraint (i.e. because of backwards compatibility) then they should be modelled in the SA onwards.
These viewpoints produce the following artifacts, which are stored as informal requirements and their inclusion into the model is tracked:

- Blueprints, diagrams, 3D models, digital twins of existing infrastructure
- Photographs, video evidence of topography, components, interfaces

Once a large amount of informal needs and desires have been compiled, they must be formalized via ARCADIA's Operational Needs Analyis (OA).
A criticality level (must-have, nice-to-have, etc.) may be assigned to each need and desire, either formal or informal, to guide future design.
Even if all informal requirements are formalized, original transcripts and artifacts (i.e. feedback grids) from stakeholder communications should be preserved.
If not all informal requirements can be formalized during the OA, it is necessary to do so in later ARCADIA stages and keep track of the progress.
Once the Physical Architecture is finalized, all informal requirements should have been formalized.

If the OA is to be skipped, an exhaustive list of textual stakeholder requirements with criticality levels may be used instead.

This phase ends with a Mission Concept Review (MCR),
a meeting where all team viewpoints (not the stakeholders themselves) present the results of their customer research.

They discuss potential contradictory statements from stakeholders and resolve them, and attempt to surface latent needs.

The meeting ensures everyone who will work on the project knows who the stakeholders are and what they need.

The expected cost and complexity of the project is discussed to make sure that the team is capable of assuming responsibility of it.
Potential solutions can be brainstormed to gauge project feasibility but the focus is on understanding stakeholder needs and desires.

The phase ends when the formal Operational Need Analysis has been approved at the MCR.
Textual requirements that couldn't be formalized during the OA also need to be approved and the formalization progress need to tracked.
For projects that skip the OA, the phase ends when an exhaustive list of textual stakeholder requirements with criticality levels has been approved at the MCR.

### Phase A: Concept and Technology Development

Given the exhaustive Operational Need Analysis model (or the stakeholder requirements), this phase follows the ARCADIA System Needs Analysis method to generate a System Architecture.
This phase thus defines what the system must accomplish for the users.

At this point the system is seen as a black box, focusing not on its internal organization but on its boundary and interactions with external entities, either human or other systems.

At this phase it is necessary to avoid introducing new textual requirements to the proposed solution, leaving stakeholders as the only ones capable of establishing actual, unquestionable requirements.
What the system architects must generate is a model reflecting their design choices and how they meet user needs and desires.
Unlike proper requirements, the System Architecture can be iterated on, discussed with stakeholders and modified until a satisfactory result has been reached. The system model, owing to its user/system boundary definition, is thus a sort of customer contract, and as such must be agreed to by all involved parties.

All lifecycle phases including Operations, Sustainment (Maintenance) and Closeout (Retirement) should be viewpoints from this phase onwards.
The Integration, Verification and Validation (IVV) Plan must be started during this phase.
While defining the IVV it useful to follow the V-Model, not formally with all its required documents, but as a mnemonic to create a testing strategy that covers every element of the model, from unit tests to use case tests at the system level. More on IVV in Phase C.

The first gate during this phase is the System Requirements Review (SRR).
This is a meeting where all team members (not the stakeholders) approve the viewpoints that will define the System Architecture.

The focus for the SRR is not on the system architecture itself, but on identifying requirements that were overlooked.
For example, a cybersecurity expert might identify that cyberattack scenarios haven't been modeled as feared events. They don't propose the exact system functions that will handle these cases, they just point out that the cybersecuriy viewpoint needs to be introduced.
Some life-cycle phases (E and F) require the introduction of specialized maintenance and retirement viewpoints. Again, at this point merely listing the viewpoints is sufficient, yet in future stages they will be required to influence architecture and functional content to make the system maintainable/sustainable and to ensure a safe retirement.

After the SRR the System Needs Analysis may be sent to stakeholders for feedback, and then refined.
The feedback will be in the form of stakeholder requirements that were previously overlooked, at might require updates to both the OA and SA.

After the SRR, the Mission Definition Review (MDR) is carried out so all viewpoints confirm that they understand
the mission to be feasible.
As a simplification, this can be a simple yes/no vote.

Finally, the third gate is the System Definition Review.
Its objective is to approve the full System Needs Analysis, both by the viewpoints and the stakeholders.
A full System Needs Analysis includes behavior, system missions, and system capabilities, but a structure model alone may be found sufficient to pass this gate if it fully contains the former elements.
The SRR, MDR and SDR may be carried out all in a single meeting if the viewpoints agree on the system requirements early on.

### Phase B: Preliminary Design and Technology Completion    
                                    
This phase generates the Logical Architecture (LA) of the system, following the ARCADIA method. The LA defines how the system must be organized internally and how it must behave to meet expectations, but not the technology it will use.

Ideally, the LA will remain true years later, when technologies have evolved.

The LA is approved at the Preliminary Design Review (PDR), which doesn't necessarily involve stakeholders.

IVV definition continues during this stage.
                                    
### Phase C: Final Design and Fabrication
                                    
This Phase generates the Physical Architecture of the system, following the ARCADIA method.
The PA defines which phyisical components (actual hardware and software) will implement the desired behavior of the system.

At this point, it is advisable to perform a scoping review of the available literature, either from academic publications or case studies. The Logical Architecture already gives a breakdown of problems solved by the system, as well as formally defined system missions and capabilities, which can be straightforwardly turned into PICOC concepts and then research questions. Individual functional chains or functions of high expected complexity can also be turned into research questions.

During this phase, it is critical that systems engineering doesn't overspecificy subsystems beyond their knowledge.
Instead, a co-engineering approach is preferred, through which systems engineering and the specialty engineering disciplines (mechanical, elecronics, software, electrical, etc.) define the PA together.
Specialty engineering assures that the design is technically sound and sufficiently defined so that it can be evaluated and built, and systems engineering assures that it can be integrated with the rest of the system and that it meets requirements at higher levels of abstraction.
Reaching a high level of detail in the MBSE model is highly advisable, since doing otherwise will lead to late discovery of errors or requirement non-compliance.

Co-engineering is iterative, and it can take a significant amount of time until all viewpoints are satisfied with the result, following concerns like reuse of existing systems and components, design language, internal best practices compliance, maintainability, and retirement.
Viewpoints don't only offer open-ended comments, they actively shape the MBSE model.

The Physical Architecture is approved at the Critical Design Review, by vote from all viewpoints.
It must be noted that the PA is not merely a structural representation, but also a behavioral representation.
Thus, at this stage, the complete behavior of the system, its states and modes, its expected use cases and feared events, should be defined in the appropiate MBSE language.
Behavior modeling based on use cases and feared events is particularly useful because it can be straightforwardly converted to tests later on, and because it can robustly implement risk mitigation by explicitly mapping risks to mitigation structures and behavior in the system.

Also, the PA must be contrasted against the informal needs and desires collected in Pre-Phase A, covering all mediums of need definition (text, multimedia, diagrams, engineering models). It must fully incorporate all informal needs and desires, at least as a constraint.

With the PA approved, the project moves on the Production Readiness Review (PRR).
The focus of this meeting is to determine if the project has enough human talent and physical resources to begin development.
If the available resources are insufficient, a specialized logistics viewpoint can derive a Bill of Materials (aka a Product Breakdown Structure in ARCADIA) from the PA and IVV and arrange the acquisition of components.
Time is also an important resource to consider during this review. Each viewpoint should qualitatively assess feasibility from the PA and the overall project deadline, even though the IVV plan might not be ready yet.

Subsequently, systems engineering is responsible for breaking down all system and subsystem functionality into incremental versions, which are called functional versions.
This happens recursively at the system and subsystem level.
Project management is responsible for assigning deadlines for each functional versioning.
IVV is responsible for linking the existing tests with each functional version, and to introduce any necessary tests to make sure that each version is properly validated before progressing to the next.

Functional versioning and IVV planning are tightly coupled activities.
Both have to agree on the timeline and verification strategy for system integration.
It could be useful for each functional version to be defined as a set of tests after which a meaningful system or subsystem function can be delivered.
Conversely, functional versions could be derived from logistics, time budget, or criticality viewpoints which IVV can then analyze and propose tests to ensure their incremental delivery.
Agile methodologies can inspire functional versioning, for example by constraining each version to be deliverable within one sprint (two work weeks).

To ensure completeness of the verification plan, ensure that each use case or feared event is linked to at least one test.
Test times include inspection (of the MBSE model itself, of code, of CAD, of operational logs, of physical components and their connections, etc.), analysis (of code to comply with style guides, of power consumption against power budgets, of architecture to verify redundancy, etc.), and testing, which covers any formally defined ordered list of steps performed in a constrained environment and with explicit pass/fail gates with documented criteria. 

Also, apply the V-Model as mnemonic. Ensure that, for the physical level of abstraction, functional versions incrementally compose back the complete, integrated system model defined before IVV plan. Is it suggested to apply a unit test per physical component, an integration test per use case or feared event, and one system test per usage environment. Acceptance testing, that is, requirement verification at a level of abstraction at a level higher than the physical, is performed using the following ARCADIA principle:

> The function can be considered verified, when all the scenarios and functional chains [that can be traced back to it] are verified.

See [IVV](IVV.md) for more detail on systematic test definition from MBSE models.

To verify requirements above the physical level of abstraction, remember that under the ARCADIA method 

Regardless of the approach, the IVV plan should be designed while taking subsystem interdependencies into account.
Dependency Structure Matrix (DSM) algorithms can be used to manage dependency between subsystems, or subsystem dependencies on available materials or time budgets.

Finally, at the System Integration Review (SIR) the complete IVV plan is approved.

The CDR, PRR and SIR may be carried out in a single meeting.

### Phase D: System Assembly, Integration and Test, Launch

During this phase, specialty engineering will assemble and integrate the system (hardware, software, humans), perform verification and validation testing, and launch the system.

This phase carries out work already fully defined by the PA and the IVV plan. If functional versions incorporate an Agile viewpoint then they will be directly divisible into sprints. If not, work planning responsibilities fall to specialty engineering, derived from the deadlines set by systems engineering.
If the IVV plan was built using the approach from [IVV](IVV.md) then it can be said to be V-Model-compliant.

The Test Readiness Review is the IVV equivalent to the Production Readiness Review.
The focus of this meeting is to determine if the project has enough human talent and physical resources to begin verification.
Since MBSE-based tests explicitly define required equipment, environmental context, and pass/fail criteria, no external information is needed for this review.

After every test, any fail result must be evaluated to determine whether the MBSE model or the IVV plan (which is also part of the MBSE model) need to be updated. If so, prefer to perform updates at the lowest level of abstraction possible. Follow exchanges to update all model elements affected, and re-approve the resulting MBSE model iteratively.
After test-driven updates, regenerate functional versions and tests if needed.
Tracking such updates should be straightforward if all docs, including MBSE models, are persisted in plain text (e.g. D2 for MBSE models) and managed via version control software (e.g. Github).

After all tests have passed, conduct an Operational Readiness Review (ORR).
Discuss the changes made to the model based on failed tests in terms of economic and time budget impact.
Note that any test-driven updates to the model should not compromise requirement compliance if done with a complete understanding of the extent of the impact, which should be attained by following MBSE traceability links.
However, if requirement compliance is put into question, navigate up the levels of abstraction to find the non-compliance.
Iterate on the MBSE and IVV updates, production, testing, and ORR cycle as many times as needed.

Finally, the Flight Readiness Review (FRR) determines if the project has enough human talent and physical resources to launch.
Launch, like any other operational scenario, should have already been formally modeled as a use case, with its own functions and tests.
Thus, this meeting is strictly about resource availability, and should be started with the system fully built and tested.
                                    
### Phase E: Operations and Sustainment                          

It is customary to perform a Critical Event Readiness Review (CERR) seven weeks prior to launch.
This is the last gate to identify use cases and feared events missing from the system, or insufficent talent and resources.
Errors discovered at this point require changes from the MBSE model to the final built system, hence the need for diligent modelling and testing in earlier phases.
Ideally, a negative result from a CERR only delays the launch until the missing talent and resources have been procured, without changes to the system.

After a positive result from a CERR, the system is clear for lauch.
All feared events and use cases were already modeled, so the system has functions to handle them. If necessary, extensive evaluation and operations analysis can be performed based on the MBSE model to ensure a complete coverage **before** launch.

Human-system interaction (e.g. dashboards, logs, telemetry) was already defined in the PA, and now it is put in use for monitoring and operation.

Maintenance should have been a viewpoint from as early as the System Needs Analysis, so the necessary sustainment functions and structure are expected to have been built and tested prior to launch.

The physical architecture provides a detailed Bill of Materials, so specialized spare parts logistics can be performed at this stage.
For systems with long-running operations, an analysis of discontinued parts replacement can be conducted by following traceability links to determine and update all impacted elements.

If an anomalous event is encountered or feared during operations, the MBSE model provides a detailed description of the system boundary and behavior that can be used to predict the system response.
Pre-defined system observability functions can be leveraged to compare actual states and modes with the expected and modelled ones, for example to make decisions regarding mission extension.

A Post-Launch Assessment Review (PLAR) can be conducted to compare real system behavior with the expected behavior (ideally captured in full by the MBSE model). The insights generated can be used as proof of delivery to stakeholders, or lessons learned for future designs. 

A Disposal Readiness Review (DRR) is performed to verify the availability of talent and resources for decommisssioning.
No changes are made to the MBSE model or the system, since the dedicated retirement viewpoint should have introduced the necessary structure and behavior in earlier phases.

### Phase F: Closeout                

Once the system has been decommissioned and retrieved, returned data, samples (if applicable), and system degradation can be analyzed in full. Hardware can be de-integrated and returned to owners.
Note that these are not ad-hoc procedures. If they are of importance to stakeholders, specialized viewpoints should have been introduced early on to provide the system with the appropiate structure and behavior to support them.
Whenever applicable, decommissioning, sample retrieval, degradation analysis, de-integration, etc. have to be modelled as expected use cases as late as the physical architecture definition stage.

## GitHub as a practical platform for engineering project management

The idealized MBSE-first repository structure can be adapted when a project starts from, or only maintains, the Physical Architecture (PA). This CanSat workshop repository is intentionally subsystem-first: each subsystem owns its PA model, functional-version folders, implementation files, and verification definitions, while PM&SE owns cross-subsystem policy, contracts, and system-level tests.

In this project, “physical-architecture-first” does not mean “structure-only.” A PA version may still include physical views, logical views, functional allocation views, and functional-chain views because the PA is where the actual hardware/software components, interfaces, behavior, and verification definitions are tied together.

A repository following the structure that this project evolved toward looks like this:

```
└── repo-root/
    ├── README.md                         # Project entry point and subsystem navigation
    ├── PM&SE/
    │   ├── README.md                     # Systems-engineering hub
    │   ├── Life Cycle Model.md           # Lifecycle and repository-management guidance
    │   ├── IVV.md                        # Project-wide verification policy and statistics
    │   ├── MBSE/
    │   │   └── tests/
    │   │       ├── README.md             # System-level test index
    │   │       ├── requirements_to_test_matrix.md
    │   │       └── SYS-.../              # System-level modeled verification activities
    │   ├── contracts/                    # Controlled subsystem interface contracts
    │   ├── BOM/                          # Bill of materials and datasheets
    │   └── Understanding Capella Physical Diagrams/
    ├── ADS/                              # Attitude Determination System
    │   ├── README.md                     # Subsystem overview, latest views, requirements, IVV links
    │   ├── MBSE/
    │   │   ├── v0.1/                     # Functional/development baseline model views
    │   │   ├── v0.2/
    │   │   ├── v0.3/
    │   │   ├── v1.0/
    │   │   └── tests/                    # Subsystem-wide modeled verification activities
    │   └── ...                           # Prototypes, firmware, scripts, local evidence
    ├── AMS/
    │   ├── README.md
    │   ├── MBSE/
    │   │   ├── v0.1/
    │   │   ├── v0.2/
    │   │   ├── v1.0/
    │   │   └── tests/
    │   └── ...
    ├── DPS/
    │   ├── README.md
    │   ├── MBSE/
    │   │   ├── v0.1/
    │   │   ├── v0.2/
    │   │   ├── v1.0/
    │   │   └── tests/
    │   └── ...
    ├── OBCC/
    │   ├── README.md
    │   ├── MBSE/
    │   │   ├── v1.0/
    │   │   └── tests/                    # Includes multi-version gate definitions using v1.0 as target context
    │   └── main/
    ├── PDM/
    │   ├── README.md
    │   ├── MBSE/
    │   │   ├── README.md                 # MBSE conversion/context index
    │   │   ├── v0.1/
    │   │   │   └── tests/                # Version-local tests where historically used
    │   │   ├── v0.2/
    │   │   │   └── tests/
    │   │   └── v1.0/
    │   │       └── tests/
    │   └── PDM-Servo/
    ├── PDS&ESS/
    │   ├── README.md
    │   ├── MBSE/
    │   │   ├── v0.1/
    │   │   ├── v0.2/
    │   │   ├── v0.3/
    │   │   ├── v1.0/
    │   │   └── tests/
    │   └── ...
    ├── S&A/
    │   ├── README.md
    │   ├── MBSE/
    │   │   ├── README.md
    │   │   ├── v0.1/                     # Physical-only S&A baseline
    │   │   ├── v1.0/
    │   │   └── tests/
    │   └── ...
    └── Workshop/
        └── README.md                     # Pedagogy/workshop delivery artifacts
```

The minimum MBSE folder contract for this physical-architecture-first structure is:

- `*/MBSE/vX.Y/` stores the model source for one functional version or subsystem integration version. Use `.d2` sources and rendered `.png` files side by side. Prefer stable names such as `*_view1_physical`, `*_view2_logical`, `*_view3_functional_allocation`, and `*_viewN_<functional_chain>_chain` when those views exist.
- `*/MBSE/tests/README.md` is the subsystem verification-plan index. It lists activity IDs, covered model elements, IADT method, pass/fail criteria, status, and expected evidence path.
- `*/MBSE/tests/<activity-id>/README.md` is the entry point for one modeled verification activity. It may copy baseline views, add verification-only views, and define report-by-reference pass/fail criteria.
- `*/MBSE/tests/results/<activity-id>/` is the default evidence/report location. If a subsystem uses version-local tests such as `*/MBSE/vX.Y/tests/`, the nearest MBSE README must index them so they are not hidden.
- `PM&SE/MBSE/tests/` contains system-level tests that integrate more than one subsystem.
- `PM&SE/contracts/` contains interface contracts that multiple subsystem models and tests must reference.
- Implementation files, sketches, firmware, scripts, CAD, spreadsheets, and ad-hoc experiments live beside the MBSE folder in the subsystem directory. They are implementation evidence, not replacements for the model or verification report.

### Interlinked README strategy

The repository should use a “README ladder” so the model can be discovered from the root without prior knowledge of the folder layout. No MBSE directory, version, or test definition should be more than two clicks away from a human-readable index.

| README level | Purpose | Required links |
|---|---|---|
| `README.md` | Project entry point. | PM&SE hub, subsystem READMEs, project requirements, issue board/filter, latest system-level test index. |
| `PM&SE/README.md` | Governance hub. | `IVV.md`, this lifecycle model, system-level tests, contracts, BOM, diagram-reading guide, and issue strategy. |
| `<subsystem>/README.md` | Subsystem entry point. | Owners, mission, requirements, latest MBSE version, rendered latest views, version list, test-plan index, contracts used, and current issue/milestone links. |
| `<subsystem>/MBSE/README.md` | MBSE navigation layer, especially when tests are split by version. | Version matrix, current baseline, scope notes, render command, version-local tests, subsystem-wide tests, and known modeling gaps. |
| `<subsystem>/MBSE/vX.Y/README.md` when present | Version-specific reading guide. | View order, change from prior version, source diagrams, rendered diagrams, linked tests, and implementation baseline. |
| `<subsystem>/MBSE/tests/README.md` | Verification-plan index. | Activity table, status, source model versions, expected evidence folders, linked GitHub issues, and linked reports. |
| `<subsystem>/MBSE/tests/<activity-id>/README.md` | Test-definition entry point. | Source views, verification-specific views, pass/fail criteria, required evidence, expected report path, owner, status, and linked issue. |

Rules for keeping the README ladder healthy:

1. Every new model version must be linked from the subsystem README and from the nearest MBSE README or tests README.
2. Every new test activity must have a stable activity ID, a README, an expected results path, and a link from a tests index.
3. Every activity README must link back upward to the subsystem test index and outward to the model version(s), contracts, and IVV policy it uses.
4. Every subsystem README should show at least the latest rendered PA view or a clearly labeled “latest views” section so diagrams are seen before readers reach source files.
5. If a README says a version or test is “model-defined,” it must also say whether execution evidence is pending, passed, failed, blocked, or waived.
6. Pull requests that add or rename MBSE files should update the corresponding README ladder in the same change.

### Turning MBSE-defined versions and tests into GitHub issues

Treat each functional version and each modeled verification activity as backlog source material. The model defines what work exists; GitHub Issues track who will execute it, by when, and with what evidence.

Use these issue types:

| Issue type | Source artifact | When to create | Definition of done |
|---|---|---|---|
| Functional-version issue | `*/MBSE/vX.Y/` | When a subsystem version is defined or selected for delivery. | Version model is linked, implementation/build artifacts are identified, required tests are linked, and the version gate is either passed, blocked, waived, or intentionally deferred. |
| Verification-activity issue | `*/MBSE/tests/<activity-id>/README.md` or `*/MBSE/vX.Y/tests/<activity-id>/README.md` | When a test is model-defined and ready to execute. | Evidence and report are committed under the expected results path, pass/fail rationale is recorded, README status is updated, and anomalies/waivers are linked. |
| Gate-closure issue | Subsystem or system test-plan table | When a functional version needs approval to advance. | All required verification-activity issues are closed or explicitly waived/deferred by the gate owner. |
| Anomaly / model-update issue | Failed report, missing evidence, or model mismatch | Immediately after a failed/blocked execution or design mismatch. | Root cause is dispositioned, model/test/implementation updates are committed, and any required retest issue is linked. |

Recommended labels:

- `mbse`, `ivv`, `gate`, `contract`, `anomaly`
- `subsystem:ADS`, `subsystem:AMS`, `subsystem:DPS`, `subsystem:OBCC`, `subsystem:PDM`, `subsystem:PDS-ESS`, `subsystem:SAA`, `subsystem:PMSE`
- `version:v0.1`, `version:v0.2`, `version:v0.3`, `version:v1.0`
- `kind:functional-version`, `kind:test-definition`, `kind:test-execution`, `kind:gate-closure`, `kind:model-update`
- `method:I`, `method:A`, `method:D`, `method:T`
- `status:model-defined`, `status:ready-for-execution`, `status:executing`, `status:report-review`, `status:passed`, `status:failed`, `status:blocked`, `status:waived`

Recommended milestones:

- One milestone per subsystem functional version, for example `ADS v1.0`, `PDM v0.2`, or `S&A v1.0`.
- One milestone for cross-subsystem closure, for example `CanSat v1.0 Flight Readiness`.
- Optional review milestones for major gates such as `PDR`, `CDR`, `SIR`, or `FRR` when the team is using formal gate reviews.

Recommended verification issue body:

```md
## MBSE source
- Activity ID:
- Subsystem / version:
- Test-definition README:
- Source model view(s):
- Contract(s) / IVV policy:

## Execution scope
- IADT method:
- Article / firmware / configuration to be tested:
- Required equipment and environment:
- Preconditions / blockers:

## Pass/fail criteria
- Copy or link the exact model-defined criteria here.
- Do not weaken criteria in the issue; update the model/test definition if the criteria are wrong.

## Evidence and report
- Expected evidence path: `<subsystem>/MBSE/tests/results/<activity-id>/`
- Required raw evidence:
- Required report:

## Closure checklist
- [ ] Evidence captured under the expected path
- [ ] Report references model baseline and as-tested configuration
- [ ] Pass/fail rationale recorded
- [ ] Deviations, waivers, and anomalies linked
- [ ] Tests README status updated
- [ ] Functional-version or gate issue updated
```

Recommended functional-version issue body:

```md
## Functional version
- Subsystem:
- Version / SSIV:
- MBSE folder:
- Delivery purpose:

## Model scope
- Physical components and links:
- Component exchanges:
- Allocated functions / chains:
- Constraints:
- Known model gaps or accepted scope decisions:

## Required implementation work
- [ ] Hardware/build artifacts identified
- [ ] Firmware/software artifacts identified
- [ ] Interface contracts checked
- [ ] README ladder updated

## Required verification
- [ ] Link required activity issues
- [ ] Link gate-closure issue, if any
- [ ] Link expected results paths

## Closure
- [ ] Required activity issues passed or dispositioned
- [ ] Reports committed
- [ ] Version status updated in README(s)
- [ ] Gate decision recorded
```

Operational rules:

1. The activity ID or version ID must appear in the issue title, branch name when practical, report path, and commit message.
2. Issues should link to README entries, not just raw `.d2` or `.png` files, so reviewers see context and pass/fail criteria.
3. Commits that update models or reports should reference the issue with `Refs #<issue>`; commits that close an execution activity should use `Closes #<issue>` only after the report and README status are updated.
4. A failed test should not disappear into comments. Open an anomaly or model-update issue, link it from the failed execution issue, and record whether the next action is model correction, implementation correction, waiver, or retest.
5. The GitHub project board should move work through: `Model-defined` → `Ready for execution` → `Executing` → `Report review` → `Passed/Closed`, `Failed/Anomaly`, or `Waived`.
6. A future automation script can parse `*/MBSE/**/tests/**/README.md` tables and create or update issues by stable activity ID. Until then, the README activity tables are the authoritative backlog seed.
