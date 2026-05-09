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

## Github as a practical platform for engineering project management

A project following the life cycle described in this document might have the following structure as a Github repository:

```
└── repo-root/
    ├── systems-engineering/
    │   ├── operational-analysis/
    │   │   ├── organization-structure.d2
    │   │   ├── operational-activity-allocation.d2
    │   │   ├── oc1-collect-data.d2 # Example Operational Chain
    │   │   ├── operational-missions.md
    │   │   └── operational-capabilities.md
    │   ├── system-needs-analysis/
    │   │   ├── system-boundary.d2
    │   │   ├── fc1-telemetry.d2 # Example Functional Chain
    │   │   ├── system-missions.md
    │   │   └── system-capabilities.md
    │   │   └── viewpoints.md # Exhaustive list of viewpoints for the entire lifecycle 
    │   ├── informal-needs-and-desires/ # Any evidence: photos, CAD, interviews, textual requirements...
    │   │   ├── operation-site.jpg
    │   │   ├── operation-site-blueprint.dwg
    │   │   ├── existing-components.md
    │   │   ├── stakeholder1-feedback-grid.md
    │   │   └── stakeholder2-empathy-map.md
    │   │   └── stakeholder2-requirement-list.md
    │   ├── logical-architecture/
    │   │   ├── logical-structure.d2
    │   │   ├── logical-function-allocation.d2
    │   │   └── fc1-telemetry.d2 # Example Functional Chain
    │   └── physical-architecture/ # Note the recursivity in functional versions and tests
    │       ├── physical-structure.d2
    │       ├── logical-component-allocation.d2
    │       ├── physical-function-allocation.d2
    │       ├── fc1-telemetry.d2 # Example Functional Chain
    │       ├── functional-versions/
    │       │   └── v0.1/
    │       │       ├── physical-structure.d2
    │       │       ├── logical-component-allocation.d2
    │       │       ├── fc1-telemetry.d2 # Example Functional Chain
    │       │       ├── physical-function-allocation.d2
    │       │       └── tests/
    │       │           └── some-unit-test/
    │       │               ├── physical-structure.d2
    │       │               ├── logical-component-allocation.d2
    │       │               ├── physical-function-allocation.d2
    │       │               ├── fc1-bootstrap.d2 # Example Functional Chain within a test
    │       │               ├── experimental-data.csv
    │       │               └── report.tex
    │       └── tests/
    │           └── some-system-test/
    │               ├── physical-structure.d2
    │               ├── logical-component-allocation.d2
    │               ├── physical-function-allocation.d2
    │               ├── fc1-telemetry.d2 # Example Functional Chain within a test
    │               ├── experimental-data.csv
    │               ├── experimental-evidence.jpg
    │               └── report.tex
    └── some_specialty_engineering_or_subsystem_or_team/ # Non-MBSE files
        ├── code.c
        ├── blueprint.dwg
        └── test.py
```

By linking issues and commits to decision gates, tests, and viewpoints, model updates can be comfortably tracked.