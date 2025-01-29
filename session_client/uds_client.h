#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "../services/uds_service_framework.h"
#include "../lookup/uds_buf.h"
#include "../protocol/uds_services.h"

/**
 * @brief Executes a services request build routine into a provided buffer
 * 
 * @param service Pointer to service implementation struct
 * @param requestStruct Pointer to service-specific request struct
 * @param buffers Buffer to place response into
 * @return size_t Size of request (or 0 if failed to generate due to missing function or buffer size contraints)
 */
size_t uds_client_build_request(const UDS_SERVICE_IMPLEMENTATION_t* service, const void* requestStruct, uds_buf_t ret_buf);

/**
 * @brief Called on a new message to get the service ID and instantiate the appropriate response struct type
 * 
 * @param buf Buffer containing response data
 * @return UDS_SID_t Service ID (or 0xFF if invalid/no data)
 */
UDS_SID_t uds_client_response_get_sid(const uds_buf_t buf);

/**
 * @brief Called after getting the SID of a response with that responses struct to load the response data into
 * 
 * @param service Service framework implementation which must include clientDecodeResponse
 * @param response_buf Buffer containing response data
 * @param response_struct Pointer to response struct you initialized based on uds_client_response_get_sid
 * @return true Successfully deoded response
 * @return false Failed to decode response (thrown by response method or calling method safeties)
 */
bool uds_client_response_decode(const UDS_SERVICE_IMPLEMENTATION_t* service, const uds_buf_t response_buf, void* response_struct);

#ifdef __cplusplus
}
#endif