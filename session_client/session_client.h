#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "../lookup/uds_buf.h"
#include "../protocol/uds_services.h"

uds_buf_t uds_client_prepare_request(UDS_SID_t service_id, const uds_buf_t buf);

#ifdef __cplusplus
}
#endif