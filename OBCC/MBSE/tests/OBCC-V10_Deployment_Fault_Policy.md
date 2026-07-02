# OBCC deployment and runtime-fault policy baseline

**Policy version:** `OBCC-DEPLOY-FAULT-POLICY-v1.0`

**Owner:** OBCC.

**Applies to:** OBCC v1.0 deployment-gating, runtime fault-handling, mission rehearsal, and final readiness definitions (`OBCC-V05-GATE-001`, `OBCC-V06-GATE-001`, `OBCC-V09-GATE-001`, `OBCC-V10-FLIGHT-001`).

This policy freezes definition criteria only. It is not an execution report, does not modify D2/source diagrams, and does not claim pass/fail credit.

## 1. Ownership boundary

This is an OBCC-owned behavior policy, not a cross-subsystem safety-policy reallocation.

- ADS and AMS provide data plus status/age evidence under `PM&SE/contracts/sensor_obcc_freshness_contract.md` or an approved one-to-one implementation mapping. They do not decide deployment.
- PDM is responsible for deploying the parachute when OBCC commands deployment and for exposing the available actuator/servo status evidence. PDM does not own the OBCC emergency-deployment decision.
- OBCC owns operational mode, command validation, descent-state observability assessment, normal trigger evaluation, emergency-deploy request generation, safe/error-state handling, deployment-status interpretation for OBCC telemetry, and no-false-success behavior.

## 2. Required status vocabularies

### 2.1 OBCC operational mode

- `STANDBY`: telemetry/heartbeat remains active; all normal and emergency deployment requests are inhibited.
- `ON`: telemetry/heartbeat remains active; normal trigger and OBCC emergency-deploy policy may command deployment.
- `SAFE_ERROR`: OBCC has detected a critical condition that prevents normal operation or makes deployment-path interpretation unsafe. The reason shall be observable in telemetry or local trace.

### 2.2 Sensor freshness/status inputs

OBCC shall use the shared ADS/AMS status vocabulary when those data are consumed:

- `VALID`
- `STALE`
- `NO_DATA`
- `TIMEOUT`
- `SENSOR_FAULT`
- `INIT_FAIL`

`VALID` data are usable for normal trigger evaluation only when the shared contract's freshness predicate is true: `status == VALID`, required fields finite/in range, and `age_ms <= 400 ms` at the OBCC consumption point.

### 2.3 OBCC descent-state observability

- `DESCENT_OBSERVABLE`: all required inputs used by the configured OBCC deployment trigger are current, finite/in range, internally consistent, and fresh-valid under the applicable sensor contract or local getter contract; OBCC mode and scheduler progress are known.
- `DESCENT_DEGRADED`: at least one non-critical input is non-`VALID` or degraded, but the configured trigger can still be safely evaluated from the remaining required valid data and the degradation is telemetry-visible.
- `DESCENT_UNOBSERVABLE`: OBCC cannot safely decide whether descent/trigger conditions are present because a required input is `STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, `INIT_FAIL`, older than `400 ms`, missing since boot/reset, repeated beyond the freshness window, contradictory, out of range, or not correlated to the OBCC timebase.

## 3. Deployment decision rules

1. **Stand-by inhibit is absolute.** In `STANDBY`, OBCC shall not command parachute opening for a normal trigger or emergency request. It shall continue telemetry/heartbeat and publish the inhibit reason where supported.
2. **Normal trigger requires observable data.** OBCC may treat deployment trigger conditions as met only when all configured trigger inputs needed for that decision are `DESCENT_OBSERVABLE` or explicitly allowed `DESCENT_DEGRADED` by a controlled trigger definition.
3. **Emergency deploy is OBCC-owned and On-mode only.** In `ON`, if descent-state observability is lost (`DESCENT_UNOBSERVABLE`) and the deployment path is not known unsafe, OBCC shall issue an emergency-deploy request with a reason code rather than silently continuing as a normal run.
4. **Invalid data are not normal triggers.** `STALE`, `NO_DATA`, `TIMEOUT`, `SENSOR_FAULT`, `INIT_FAIL`, out-of-range, non-finite, or timebase-uncorrelated inputs shall never be interpreted as a normal valid trigger. They may only drive the emergency-deploy path when the On-mode policy above permits it.
5. **Deployment deadline.** In `ON`, a normal accepted trigger or accepted emergency-deploy request shall produce an OBCC open command to the PDM/deployment path such that the safe fixture/actuator observer reaches open within `<=5 s`, unless a deployment-path fault forces `SAFE_ERROR` / fault status instead.
6. **Deployment path fault blocks false success.** If OBCC detects or is informed of a PDM/servo/power/deployment-path fault, it shall not report deployment success unless independent actuator/position/current evidence or PDM feedback confirms open. It shall publish fault/safe/error status instead.
7. **No unmodeled bypass.** No serial-console, debug, or hidden path may command deployment for flight-credit evidence outside the OBCC mode gate and PDM/deployment command path.

## 4. Actuator/PDM status interpretation

OBCC-facing deployment status shall be mapped to these meanings for tests and reports, even if implementation names differ:

| Status | Meaning for OBCC verification |
|---|---|
| `NOT_COMMANDED` | No deployment command has been accepted for the current mode/trigger context. |
| `INHIBITED_STANDBY` | A normal or emergency deployment request was suppressed because OBCC is in `STANDBY`. |
| `COMMAND_SENT` | OBCC sent an open command to PDM/deployment path; this is not deployment success by itself. |
| `OPEN_IN_PROGRESS` | PDM/actuator response is underway and not yet confirmed. |
| `OPEN_CONFIRMED` | PDM feedback or independent safe-fixture/current/position observer confirms open. This is the only success state. |
| `NO_OPEN_CONFIRMED` | Observer/feedback confirms no open after a command or at the end of an inhibit/no-trigger branch. |
| `TIMEOUT` | Required open confirmation was not observed within the declared timing window. |
| `JAM_DETECTED` | Current/position/feedback evidence indicates jam or blocked travel. |
| `PDM_FAULT` | PDM reports fault or command path unavailable. |
| `UNKNOWN` | Status cannot be proven; never count as success. |

For strict OBCC tests, `COMMAND_SENT`, `OPEN_IN_PROGRESS`, `TIMEOUT`, `JAM_DETECTED`, `PDM_FAULT`, and `UNKNOWN` shall not be credited as successful deployment.

## 5. Runtime fault and safe/error criteria

- Runtime sensor/getter faults shall return bounded result/error codes or statuses and shall not block the scheduler.
- Non-critical runtime faults shall be telemetry-visible and degraded where possible.
- Critical runtime faults affecting RF, power, deployment path, mode/state, or the scheduler shall transition to a traceable safe/error state or a degraded state with explicit rationale. The system shall not masquerade as a normal successful run after a critical safe/error condition.
- For non-RF getter/bus faults during runtime-fault tests, the OBCC `<=4 s` telemetry-gap bound from `OBCC-V06-GATE-001` remains the selected gate criterion unless a later controlled definition changes it.
- RF-loss/radio-fault trials may lose downlink evidence during the RF fault, but local trace must show bounded behavior and the first post-restoration health frame shall disclose the fault/recovery within two scheduled telemetry intervals.

## 6. Evidence required for strict credit

Reports that claim deployment/fault-policy credit shall record:

- OBCC mode and command history.
- Sensor statuses, `age_ms`, sample IDs, and trigger-input validity used for each normal or emergency decision.
- Descent observability classification and reason code.
- Emergency-deploy request state (`none`, `inhibited`, `requested`, `blocked_by_fault`, or equivalent mapping).
- PDM/actuator status mapping from §4.
- Open-command timestamp, trigger/request timestamp, observer/feedback timestamp, and `<=5 s` timing calculation when applicable.
- Safe fixture or actuator surrogate configuration for repeated tests; live release requires separate authorization.
- Firmware/configuration IDs, UUT IDs, instrumentation IDs, clock correlation, deviations, and waivers.

## 7. Affected-test update map

| Target | Required update/use of this policy |
|---|---|
| `OBCC-V05-GATE-001` | Replace open emergency-policy TBDs with the Stand-by inhibit, On-mode emergency request, descent observability, and actuator-status criteria above. |
| `OBCC-V06-GATE-001` | Use this policy for runtime fault, emergency-deploy, safe/error, and `<=4 s` degradation interpretation; trace/stress tools and load profiles are execution records, not open definition blockers. |
| `OBCC-V09-GATE-001` | Use this policy for mission-rehearsal deployment/fault branches and no-false-success checks. |
| `OBCC-V10-FLIGHT-001` | Treat this policy as the selected OBCC-owned emergency/deployment/fault baseline for final closure; verify that detailed gate reports cite evidence or approved holds. |
| `SYS-DEPLOYMENT-SAFE-LIVE` | Reuse the ownership boundary: ADS/AMS provide data/status, PDM deploys when commanded, and OBCC owns mode/trigger/emergency/safe-error decisions. |

## 8. Residual follow-up

1. Update affected OBCC READMEs and D2/model views to reference this policy.
2. Map implementation-specific enum names, PDM feedback fields, and telemetry fields to the policy vocabularies above.
3. Execute the safe-fixture tests and archive evidence before claiming pass/fail credit.
