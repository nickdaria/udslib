#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "../../udslib.h"
#include "../../protocol/uds_subfunction.h"
#include "../uds_service_framework.h"

/**
 *  Read Data by Local Identifier (0x21)
 *      I have no real info on this one. I just know how Nissan uses it.
 */

typedef struct {
    uint8_t local_identifier;
} UDS_21_RDBLI_request_t;

typedef struct {
    UDS_21_RDBLI_request_t request;
    uds_buf_t value;
    size_t value_len;
} UDS_21_RDBLI_response_t;

extern UDS_SERVICE_IMPLEMENTATION_t UDS_21_RDBLI;

#ifdef __cplusplus
}
#endif