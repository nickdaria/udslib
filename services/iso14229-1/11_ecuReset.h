#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "../../udslib.h"

/**
 *  ECU Reset (0x11)
 *      https://piembsystech.com/ecu-reset-service-identifier-0x11-uds-protocol/
 * 
 *      [Accepts]
 *     - Reset type
 * 
 *      [Response]
 *      - B0: Subfunction (Reset Type)
 *      - Execute Reset
 * 
 *      [NACK Response]
 */

//  ECU Reset Types
typedef enum {
    UDS_PROTOCOL_ECU_RESET_HARD = 0x01,
    UDS_PROTOCOL_ECU_RESET_KEY_OFF_ON = 0x02,
    UDS_PROTOCOL_ECU_RESET_SOFT = 0x03,
    UDS_PROTOCOL_ECU_RESET_ENABLE_RAPID_POWER_SHUTDOWN = 0x04,
    UDS_PROTOCOL_ECU_RESET_DISABLE_RAPID_POWER_SHUTDOWN = 0x05,

    /* 0x06-0x3F ISO SAE Reserved */

    /* 0x40-0x5F Vehicle Manufacturer Specific */

    /* 0x70-0x7E System Supplier Specific */
} uds_protocol_ecuReset_t;

#ifdef __cplusplus
}
#endif