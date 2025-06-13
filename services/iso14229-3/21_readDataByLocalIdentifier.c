#include "21_readDataByLocalIdentifier.h"

size_t x21_RDBLI_serverEncodePositiveResponse(const void* response, UdsBuffer ret_buf) {
    const UDS_21_RDBLI_response_t* rResponse = (const UDS_21_RDBLI_response_t*)response;

    //  Safety
    if(rResponse == NULL || rResponse->value.data == NULL || ret_buf.data == NULL) {
        return 0;
    }

    //  Sufficient buffer length check
    if (ret_buf.bufLen < rResponse->value_len + 1) {
        return 0;
    }

    size_t offset = 0;

    //  Copy identifier
    ret_buf.data[offset++] = rResponse->request.local_identifier;

    //  Copy data
    for(size_t i = 0; i < rResponse->value_len; i++) {
        ret_buf.data[offset++] = rResponse->value.data[i];
    }

    return offset;
}

bool x21_RDBLI_decodePositiveResponse(void* response, UdsBuffer buf) {
    UDS_21_RDBLI_response_t* rResponse = (UDS_21_RDBLI_response_t*)response;

    //  Safety
    if(response == NULL || rResponse->value.data == NULL || buf.data == NULL) {
        return false;
    }

    //  Minimum length check
    if(buf.bufLen < 1) {
        return false;
    }

    size_t offset = 0;

    //  Copy identifier
    rResponse->request.local_identifier = buf.data[offset++];

    //  Copy data
    for(size_t i = 0; i < buf.bufLen - 1; i++) {
        rResponse->value.data[i] = buf.data[offset++];
    }

    //  Save value size
    rResponse->value_len = offset - 1;
    
    //  Return data length
    return true;
}

UDS_NRC_t x21_RDBLI_serverDecodeRequest(void* request, UdsBuffer buf) {
    //  Safety
    if(request == NULL || buf.data == NULL) {
        return UDS_NRC_IMLOIF;
    }

    UDS_21_RDBLI_request_t* rQuery = (UDS_21_RDBLI_request_t*)request;

    //  Minimum length check
    if (buf.bufLen != 1) {
        return UDS_NRC_IMLOIF;
    }

    //  Copy identifier
    rQuery->local_identifier = buf.data[0];

    return UDS_NRC_PR;
}

size_t x21_RDBLI_clientEncodeRequest(const void* request, UdsBuffer ret_buf) {
    //  Safety
    if(request == NULL || ret_buf.data == NULL) {
        return 0;
    }

    const UDS_21_RDBLI_request_t* rQuery = (const UDS_21_RDBLI_request_t*)request;

    //  Sufficient buffer length check
    if (ret_buf.bufLen < 1) {
        return 0;
    }

    //  Copy identifier
    ret_buf.data[0] = rQuery->local_identifier;

    return 1;
}

UDS_SERVICE_IMPLEMENTATION_t UDS_21_RDBLI = (UDS_SERVICE_IMPLEMENTATION_t) {
    .sid = UDS_SID_RDBLI,
    .clientEncodeRequest = x21_RDBLI_clientEncodeRequest,
    .clientDecodeResponse = x21_RDBLI_decodePositiveResponse,
    .serverEncodeResponse = x21_RDBLI_serverEncodePositiveResponse,
    .serverDecodeRequest = x21_RDBLI_serverDecodeRequest,
};