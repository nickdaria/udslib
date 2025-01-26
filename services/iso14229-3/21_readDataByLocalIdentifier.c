#include "21_readDataByLocalIdentifier.h"

size_t UDS_21_RDBLI_server_encodePositiveResponse(const UDS_21_RDBLI_response* response, uds_buf_t* ret_buf) {
    //  Safety
    if(response == NULL || response->value == NULL || ret_buf->data == NULL) {
        return 0;
    }

    //  Sufficient buffer length check
    if (response->value->buf_len > ret_buf->buf_len) {
        return 0;
    }

    size_t offset = 0;

    //  Copy identifier
    ret_buf->data[offset++] = response->query.local_identifier;

    //  Copy data
    for(size_t i = 0; i < response->value_len; i++) {
        ret_buf->data[offset++] = response->value->data[i];
    }

    return offset;
}

bool UDS_21_RDBLI_client_decodePositiveResponse(UDS_21_RDBLI_response* response, uds_buf_t* buf) {
    //  Safety
    if(response == NULL || response->value == NULL || buf->data == NULL) {
        return false;
    }

    //  Minimum length check
    if(buf->buf_len < 1) {
        return false;
    }

    size_t offset = 0;

    //  Copy identifier
    response->query.local_identifier = buf->data[offset++];

    //  Copy data
    for(size_t i = 0; i < buf->buf_len - 1; i++) {
        response->value->data[i] = buf->data[offset++];
    }

    //  Save value size
    response->value_len = offset - 1;
    
    //  Return data length
    return true;
}

UDS_NRC_t UDS_21_RDBLI_server_decodeRequest(UDS_21_RDBLI_query* query, uds_buf_t* buf) {
    //  Safety
    if(query == NULL || buf->data == NULL) {
        return UDS_NRC_IMLOIF;
    }

    //  Minimum length check
    if (buf->buf_len != 1) {
        return UDS_NRC_IMLOIF;
    }

    //  Copy identifier
    query->local_identifier = buf->data[0];

    return UDS_NRC_PR;
}

size_t UDS_21_client_encodeRequest(const UDS_21_RDBLI_query* query, uds_buf_t ret_buf) {
    //  Safety
    if(query == NULL || ret_buf.data == NULL) {
        return 0;
    }

    //  Sufficient buffer length check
    if (ret_buf.buf_len < 1) {
        return 0;
    }

    //  Copy identifier
    ret_buf.data[0] = query->local_identifier;

    return 1;
}
