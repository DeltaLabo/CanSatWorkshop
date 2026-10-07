#ifndef PMSE_SENSOR_OBCC_FRESHNESS_CONTRACT_H
#define PMSE_SENSOR_OBCC_FRESHNESS_CONTRACT_H

/*
 * PMSE-SENSOR-OBCC-FRESHNESS-v1.0 realization header.
 *
 * Owning model views:
 * - PM&SE/MBSE/v1.0/CANSAT_v1.0_view4_sensor_sample_delivery_chain.d2
 * - PM&SE/MBSE/v1.0/CANSAT_v1.0_view5_sensor_fault_handling_chain.d2
 * - PM&SE/MBSE/v1.0/CANSAT_v1.0_view6_telemetry_downlink_chain.d2
 * - ADS/MBSE/v1.0/ADS_v1.0_view2_logical.d2
 * - ADS/MBSE/v1.0/ADS_v1.0_view8_degraded_fault_chain.d2
 * - AMS/MBSE/v1.0/AMS_v1.0_view3_functional_allocation.d2
 * - AMS/MBSE/v1.0/AMS_v1.0_view4_atmospheric_measurement_chain.d2
 * - OBCC/MBSE/v1.0/OBCC_v1.0_view9_sensor_sample_delivery_chain.d2
 *
 * The constants, enum values, and metadata types below realize the modeled
 * sensor freshness semantics. Product semantic changes start in the PM&SE
 * system model, then flow through subsystem baselines and verification
 * definitions, and only then into this header.
 */

#include <stdint.h>
#ifndef __cplusplus
#include <stdbool.h>
#endif

#define SENSOR_OBCC_FRESHNESS_CONTRACT_VERSION "PMSE-SENSOR-OBCC-FRESHNESS-v1.0"
#define SENSOR_OBCC_SUBSYSTEM_ADS "ADS"
#define SENSOR_OBCC_SUBSYSTEM_AMS "AMS"
#define SENSOR_OBCC_NOMINAL_REQUEST_PERIOD_MS (200U)
#define SENSOR_OBCC_MAX_FRESH_AGE_MS (400U)
#define SENSOR_OBCC_TELEMETRY_PERIOD_MS (2000U)

/* Numeric values realize the modeled status vocabulary; keep stable unless the model changes. */
typedef enum SensorObccFreshnessStatus {
    VALID = 0,
    STALE = 1,
    NO_DATA = 2,
    TIMEOUT = 3,
    SENSOR_FAULT = 4,
    INIT_FAIL = 5
} SensorObccFreshnessStatus;

/* Realization of the modeled SensorSampleEnvelope metadata. */
typedef struct SensorObccResponseMetadata {
    const char *contract_version;
    const char *subsystem_id;       /* "ADS" or "AMS" */
    uint32_t sample_id;
    uint32_t sample_time_ms;
    uint32_t request_time_ms;       /* OBCC request or consumer timestamp */
    uint32_t age_ms;
    SensorObccFreshnessStatus status;
    bool payload_fields_valid;      /* True only when required payload fields are finite/in range. */
    uint32_t payload_field_status_mask; /* Optional field-status bits; 0 when unused or all clear. */
} SensorObccResponseMetadata;

static inline bool sensor_obcc_status_is_fresh_valid(
    SensorObccFreshnessStatus status,
    uint32_t age_ms,
    bool payload_fields_valid)
{
    return (status == VALID) &&
           (age_ms <= SENSOR_OBCC_MAX_FRESH_AGE_MS) &&
           payload_fields_valid;
}

static inline bool sensor_obcc_response_is_fresh_valid(
    const SensorObccResponseMetadata *response)
{
    return (response != 0) &&
           sensor_obcc_status_is_fresh_valid(
               response->status,
               response->age_ms,
               response->payload_fields_valid);
}

#endif /* PMSE_SENSOR_OBCC_FRESHNESS_CONTRACT_H */
