#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "../lookup/uds_buf.h"
#include "../protocol/uds_negative_response.h"

typedef struct {
    size_t (*clientEncodeRequest)(const void* request, uds_buf_t* ret_buf);
    bool (*clientDecodeResponse)(void* response, const uds_buf_t buf);
    size_t (*serverEncodeResponse)(const void* response, uds_buf_t* ret_buf);
    UDS_NRC_t (*serverDecodeRequest)(void* request, const uds_buf_t buf);
} UDS_SERVICE_IMPLEMENTATION_t;

#ifdef __cplusplus
}
#endif