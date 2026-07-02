# Parachute Deployment Mechanism

Owners: @prigo11, @secoher26 

The function of this subsystem is to reliably deploy the parachute, controlling the descent speed of the CanSat for a safe landing. This mechanism automatically activates the parachute upon reaching a specified altitude or conditions, using an electromechanical system that ensures precise and successful deployment.

See [Understanding Capella Physical Diagrams](./../PM&SE//Understanding%20Capella%20Physical%20Diagrams/Understanding%20Capella%20Physical%20Diagrams.md) if needed.

## Integration, Verification, and Validation (IVV) Plan

The canonical PDM MBSE views are maintained as D2 sources with rendered PNGs next to them. The historical Capella raster exports remain linked as legacy references.

### PDM v0.1 canonical views

| View | D2 source | Rendered PNG | Legacy raster reference |
| --- | --- | --- | --- |
| Physical | [D2](MBSE/v0.1/PDM_v0.1_view1_physical.d2) | [PNG](MBSE/v0.1/PDM_v0.1_view1_physical.png) | [structure export](PDM_v0.1_S.png) |
| Logical | [D2](MBSE/v0.1/PDM_v0.1_view2_logical.d2) | [PNG](MBSE/v0.1/PDM_v0.1_view2_logical.png) | [structure export](PDM_v0.1_S.png) |
| Functional allocation | [D2](MBSE/v0.1/PDM_v0.1_view3_functional_allocation.d2) | [PNG](MBSE/v0.1/PDM_v0.1_view3_functional_allocation.png) | [structure export](PDM_v0.1_S.png), [fall-test export](PDM_v0.1_FC.png) |
| Fall-test functional chain | [D2](MBSE/v0.1/PDM_v0.1_view4_fall_test_chain.d2) | [PNG](MBSE/v0.1/PDM_v0.1_view4_fall_test_chain.png) | [fall-test export](PDM_v0.1_FC.png) |

The v0.1 fall-test chain uses the terminal-speed context from the [ESA](https://cansat.esa.int/wp-content/uploads/2023/09/T10_Parachute_Design_EN.pdf) CanSat guide.

### PDM v0.2 canonical views

| View | D2 source | Rendered PNG | Legacy raster reference |
| --- | --- | --- | --- |
| Physical | [D2](MBSE/v0.2/PDM_v0.2_view1_physical.d2) | [PNG](MBSE/v0.2/PDM_v0.2_view1_physical.png) | [structure export](PDM_v0.2_S.png) |
| Logical | [D2](MBSE/v0.2/PDM_v0.2_view2_logical.d2) | [PNG](MBSE/v0.2/PDM_v0.2_view2_logical.png) | [structure export](PDM_v0.2_S.png) |
| Functional allocation | [D2](MBSE/v0.2/PDM_v0.2_view3_functional_allocation.d2) | [PNG](MBSE/v0.2/PDM_v0.2_view3_functional_allocation.png) | [structure export](PDM_v0.2_S.png), [deployment-chain export](PDM_v0.2_FC.jpg) |
| Parachute deployment functional chain | [D2](MBSE/v0.2/PDM_v0.2_view4_parachute_deployment_chain.d2) | [PNG](MBSE/v0.2/PDM_v0.2_view4_parachute_deployment_chain.png) | [deployment-chain export](PDM_v0.2_FC.jpg) |

## Requirements

| **Requirement** | **Verification method** |
| --- | --- |
| The parachute deployment system must ensure a 100% success rate under predetermined atmospheric pressure and descent velocity conditions. | Flight Test |
| The mechanism must be able to activate the parachute within a maximum of 5 seconds after detecting the deployment point. | Simulations & Drop Test |
| The system must include the electromechanical activation system to avoid failures in parachute deployment. | Drop Test |
| The parachute must be designed with a maximum diameter of 30 cm, depending on verification points and mission requirements. | Parachute inspection |

### Success Criteria

The PDM subsystem has defined a reliable preliminary design capable of deploying the parachute within specified atmospheric conditions and timing constraints, while mitigating failure risks through electromechanical safeguards.

### Deployment confirmation evidence

PDM shall expose actuator/servo status evidence to OBCC for the shared `deployment_status` telemetry mapping; it does not declare deployment success from a command alone. Strict success requires `OPEN_CONFIRMED` from PDM feedback or independent safe-fixture/current/position observation. A command, PWM request, servo intent, `COMMAND_SENT`, or `OPEN_IN_PROGRESS` state is not success. If PDM reports inhibited, no-open, timeout, jam, fault, unknown, or cannot-prove-open evidence, OBCC/DPS consumers must preserve that non-success status and derived category instead of inferring deployment.

## Components

- [ ]  Micro Servo Motor 180 degrees.
- [ ]  Nylon Taffeta.
- [ ]  Nylon string.
- [ ]  Springs kit.
- [ ]  M2 screws.