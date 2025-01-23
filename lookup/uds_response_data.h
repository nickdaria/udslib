#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include "../protocol/uds_negative_response.h"

/**
 * @brief UDS response data set by commands to be sent back in the response
 * 
 */
typedef struct {
    /**
     * @brief False to disable sending a response (if service has subfunction, set this to bit 7 - suppressPosRspMsgIndicationBit)
     * 
     */
    bool send_response;

    /**
     * @brief Error code response (0 = OK, > 0 = NACK/7F)
     * 
     */
    UDS_NRC_t error_code;
} uds_response_data_t;

#ifdef __cplusplus
}
#endif