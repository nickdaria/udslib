#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "../../udslib.h"
#include "../../protocol/uds_subfunction.h"

/**
 *  Read Data by Local Identifier (0x21)
 *      I have no real info on this one. I just know how Nissan uses it.
 */

typedef struct {
    uint8_t local_identifier;
} UDS_21_RDBLI_query;

typedef struct {
    UDS_21_RDBLI_query query;
    uds_buf_t* value;
    size_t value_len;
} UDS_21_RDBLI_response;

size_t UDS_21_RDBLI_server_encodePositiveResponse(const UDS_21_RDBLI_response* response, uds_buf_t* ret_buf);

bool UDS_21_RDBLI_client_decodePositiveResponse(UDS_21_RDBLI_response* response, uds_buf_t* buf);

UDS_NRC_t UDS_21_RDBLI_server_decodeRequest(UDS_21_RDBLI_query* query, uds_buf_t* buf);

size_t UDS_21_client_encodeRequest(const UDS_21_RDBLI_query* query, uds_buf_t ret_buf);

#ifdef __cplusplus
}
#endif