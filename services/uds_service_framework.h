#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "../lookup/uds_buf.h"
#include "../protocol/uds_negative_response.h"

typedef struct {
    /**
     * @brief SID for this service
     * 
     */
    const uint8_t sid;

    /**
     * @brief Encodes a request to be sent to a server
     * 
     */
    size_t (*clientEncodeRequest)(const void* request, uds_buf_t ret_buf);

    /**
     * @brief Decodes a response from a server
     * 
     */
    bool (*clientDecodeResponse)(void* response, const uds_buf_t buf);

    /**
     * @brief 
     * 
     */
    size_t (*serverEncodeResponse)(const void* response, uds_buf_t ret_buf);

    /**
     * @brief 
     * 
     */
    UDS_NRC_t (*serverDecodeRequest)(void* request, const uds_buf_t buf);
} UDS_SERVICE_IMPLEMENTATION_t;

#ifdef __cplusplus
}
#endif