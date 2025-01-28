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

#ifdef __cplusplus
}
#endif