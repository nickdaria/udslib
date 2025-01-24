#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "uds_services.h"
#include "uds_negative_response.h"
#include "uds_data_identifiers.h"

//  TODO: Migrate this to the mnemonic from section 8.2 of the UDS protocol?

/**
 * @brief UDS version (based on 2.0.0.0 as of ISO14229-1_2013)
 * 
 */
#define UDS_PROTOCOL_VERSION_MAJOR      2
#define UDS_PROTOCOL_VERSION_MINOR      0
#define UDS_PROTOCOL_VERSION_REVISION   0
#define UDS_PROTOCOL_VERSION_B4         0
#define UDS_PROTOCOL_VERSION_LENGTH     4
#define UDS_PROTOCOL_VERSION ((UDS_PROTOCOL_VERSION_MAJOR << 24) | (UDS_PROTOCOL_VERSION_MINOR << 16) | (UDS_PROTOCOL_VERSION_REVISION << 8) | UDS_PROTOCOL_VERSION_B4)

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
 * @brief Index of the subfunction byte in supported services
 * 
 */
#define UDS_PROTOCOL_SUBFUNCTION_IDX 1

/**
 * @brief Mask for the subfunction within the subfunction byte
 * 
 */
#define UDS_PROTOCOL_SUBFUNCTION_MASK 0x7F

/**
 * @brief Mask for the suppressPosRspMsgIndicationBit
 * 
 */
#define UDS_PROTOCOL_SUBFUNCTION_SUPPRESS_POSITIVE_RESPONSE_MASK 0x80

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