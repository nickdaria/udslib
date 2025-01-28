#include "21_readDataByLocalIdentifier.h"

size_t x21_RDBLI_serverEncodePositiveResponse(const void* response, uds_buf_t* ret_buf) {
    const UDS_21_RDBLI_response* rResponse = (const UDS_21_RDBLI_response*)response;

    //  Safety
    if(rResponse == NULL || rResponse->value.data == NULL || ret_buf->data == NULL) {
        return 0;
    }

    //  Sufficient buffer length check
    if (ret_buf->buf_len < rResponse->value_len + 1) {
        return 0;
    }

    size_t offset = 0;

    //  Copy identifier
    ret_buf->data[offset++] = rResponse->query.local_identifier;

    //  Copy data
    for(size_t i = 0; i < rResponse->value_len; i++) {
        ret_buf->data[offset++] = rResponse->value.data[i];
    }

    return offset;
}

bool x21_RDBLI_decodePositiveResponse(void* response, uds_buf_t buf) {
    UDS_21_RDBLI_response* rResponse = (UDS_21_RDBLI_response*)response;

    //  Safety
    if(response == NULL || rResponse->value.data == NULL || buf.data == NULL) {
        return false;
    }

    //  Minimum length check
    if(buf.buf_len < 1) {
        return false;
    }

    size_t offset = 0;

    //  Copy identifier
    rResponse->query.local_identifier = buf.data[offset++];

    //  Copy data
    for(size_t i = 0; i < buf.buf_len - 1; i++) {
        rResponse->value.data[i] = buf.data[offset++];
    }

    //  Save value size
    rResponse->value_len = offset - 1;
    
    //  Return data length
    return true;
}

UDS_NRC_t x21_RDBLI_serverDecodeRequest(void* query, uds_buf_t buf) {
    //  Safety
    if(query == NULL || buf.data == NULL) {
        return UDS_NRC_IMLOIF;
    }

    UDS_21_RDBLI_query* rQuery = (UDS_21_RDBLI_query*)query;

    //  Minimum length check
    if (buf.buf_len != 1) {
        return UDS_NRC_IMLOIF;
    }

    //  Copy identifier
    rQuery->local_identifier = buf.data[0];

    return UDS_NRC_PR;
}

size_t x21_RDBLI_clientEncodeRequest(const void* query, uds_buf_t* ret_buf) {
    //  Safety
    if(query == NULL || ret_buf == NULL || ret_buf->data == NULL) {
        return 0;
    }

    const UDS_21_RDBLI_query* rQuery = (const UDS_21_RDBLI_query*)query;

    //  Sufficient buffer length check
    if (ret_buf->buf_len < 1) {
        return 0;
    }

    //  Copy identifier
    ret_buf->data[0] = rQuery->local_identifier;

    return 1;
}

UDS_SERVICE_IMPLEMENTATION_t UDS_21_RDBLI = (UDS_SERVICE_IMPLEMENTATION_t) {
    .clientEncodeRequest = x21_RDBLI_clientEncodeRequest,
    .clientDecodeResponse = x21_RDBLI_decodePositiveResponse,
    .serverEncodeResponse = x21_RDBLI_serverEncodePositiveResponse,
    .serverDecodeRequest = x21_RDBLI_serverDecodeRequest,
};