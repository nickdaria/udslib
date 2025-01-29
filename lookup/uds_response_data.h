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
     * @brief True to skip sending a response - typically set to suppressPosRspMsgIndicationBit extracted by uds_subfunc_decode
     * 
     */
    bool suppress_response;

    /**
     * @brief Error code response (0 = OK, > 0 = NACK/7F)
     * 
     */
    UDS_NRC_t error_code;
} uds_response_data_t;

#ifdef __cplusplus
}
#endif