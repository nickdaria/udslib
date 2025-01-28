#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "../lookup/uds_buf.h"
#include "../protocol/uds_services.h"

/**
 * @brief Simple helper that sets the service ID and returns a pointer to an offset buffer
 * 
 * @param service_id 
 * @param buf 
 * @return uds_buf_t 
 */
uds_buf_t uds_client_prepare_request(UDS_SID_t service_id, const uds_buf_t buf);


#ifdef __cplusplus
}
#endif