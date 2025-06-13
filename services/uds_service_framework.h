#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "../lookup/uds_buf.h"
#include "../protocol/uds_negative_response.h"
#include "../services/uds_service_framework.h"

typedef struct {
    /**
     * @brief SID for this service
     * 
     */
    const uint8_t sid;
    const char* name;

    /// @brief Size of the request structure
    const size_t pRequestSize;

    /// @brief Size of the response structure
    const size_t pResponseSize;

    /**
     * @brief Encodes a request to be sent to a server
     * 
     */
    const size_t (*clientEncodeRequest)(const void* pRequest, UdsBuffer ret_buf);

    /**
     * @brief Decodes a response from a server
     * 
     */
    const bool (*clientDecodeResponse)(void* outResponse, const UdsBuffer buf);

    /**
     * @brief 
     * 
     */
    const void (*serverPrepareResponse)(const void* pRequest, void* pResponse, UdsBuffer ret_buf);

    /**
     * @brief 
     * 
     */
    const size_t (*serverEncodeResponse)(const void* pRequest, const void* pResponse, UdsBuffer ret_buf);

    /**
     * @brief 
     * 
     */
    const UDS_NRC_t (*serverDecodeRequest)(void* outRequest, const UdsBuffer buf);
} UDS_SERVICE_IMPLEMENTATION_t;

typedef UDS_NRC_t (*UdsServiceHandlerCallback)(const void* request_struct, void* response_struct, void* usrParam);

typedef struct {
    /// @brief Function to call when this service recieves a request
    const UdsServiceHandlerCallback request;

    /// @brief The implementation that handles encoding/decoding
    const UDS_SERVICE_IMPLEMENTATION_t* implementation;
} UdsServiceHandlerEntry;

#ifdef __cplusplus
}
#endif