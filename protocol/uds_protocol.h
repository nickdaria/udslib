#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "uds_services.h"
#include "uds_negative_response.h"
#include "uds_data_identifiers.h"

/**
 * @brief Index in a transmission buffer of the UDS service byte
 * 
 */
#define UDS_PROTOCOL_SERVICE_IDX 0

/**
 * @brief Index in a negative response buffer of the service ID
 * 
 */
#define UDS_PROTOCOL_NEGATIVE_RESPONSE_SID_IDX 1

/**
 * @brief Index in a negative response buffer of the error code
 * 
 */
#define UDS_PROTOCOL_NEGATIVE_RESPONSE_CODE_IDX 2

/**
 * @brief Default session as defined by UDS protocol
 * 
 */
#define UDS_PROTOCOL_DEFAULT_SESSION 0x01

/**
 * @brief Service byte offset for positive acknowledgement
 * 
 */
#define UDS_PROTOCOL_POS_ACK_OFFSET 0x40


#ifdef __cplusplus
}
#endif