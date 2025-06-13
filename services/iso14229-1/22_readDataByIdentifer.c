#include "22_readDataByIdentifer.h"

size_t x22_RDBI_clientEncodeRequest(const void* pRequest, UdsBuffer ret_buf) {
    const UDS_22_RDBI_Request* request = (const UDS_22_RDBI_Request*)pRequest;

    //  Safety
    if(pRequest == NULL || ret_buf.data == NULL) {
        return 0;
    }

    //  Size check
    if(ret_buf.bufLen < 2) {
        return 0;
    }

    //  Encode request
    size_t request_len = 0;

    //  PID
    ret_buf.data[request_len++] = (request->data_identifier >> 8) & 0xFF;
    ret_buf.data[request_len++] = request->data_identifier & 0xFF;

    //  Return
    return request_len;
}

bool x22_RDBI_clientDecodeResponse(void* outResponse, const UdsBuffer buf) {
    UDS_22_RDBI_Response* response = (UDS_22_RDBI_Response*)outResponse;

    //  Safety
    if(outResponse == NULL || buf.data == NULL || buf.bufLen < 2) {
        return false;
    }

    //  Decode PID
    response->data_identifier = (buf.data[0] << 8) | buf.data[1];

    //  Payload
    response->value_buf = &buf.data[2];
    response->value_len = buf.bufLen - 2;

    return true;
}

void x22_RDBI_serverPrepareResponse(const void* pRequest, void* pResponse, UdsBuffer ret_buf) {
    const UDS_22_RDBI_Request* request = (const UDS_22_RDBI_Request*)pRequest;
    UDS_22_RDBI_Response* response = (UDS_22_RDBI_Response*)pResponse;

    if(ret_buf.data == NULL || ret_buf.bufLen < 2) {
        response->value_buf = NULL;
        response->value_len = 0;
    }

    response->data_identifier = request->data_identifier;
    response->value_buf = &ret_buf.data[2];
    response->value_len = ret_buf.bufLen - 2;
}

size_t x22_RDBI_serverEncodeResponse(const void* pRequest, const void* pResponse, UdsBuffer ret_buf) {
    const UDS_22_RDBI_Request* request = (const UDS_22_RDBI_Request*)pRequest;
    const UDS_22_RDBI_Response* response = (const UDS_22_RDBI_Response*)pResponse;

    // Safety checks
    if (!request || !response || !ret_buf.data || ret_buf.bufLen < 2) {
        return 0;
    }

    size_t required_len = 2 + response->value_len;
    if (ret_buf.bufLen < required_len) {
        return 0;
    }

    size_t offset = 0;

    // Encode PID
    ret_buf.data[offset++] = (response->data_identifier >> 8) & 0xFF;
    ret_buf.data[offset++] = response->data_identifier & 0xFF;

    // Copy data payload
    for (size_t i = 0; i < response->value_len; i++) {
        ret_buf.data[offset++] = response->value_buf[i];
    }

    return offset;
}

UDS_NRC_t x22_RDBI_serverDecodeRequest(void* outRequest, const UdsBuffer buf) {
    UDS_22_RDBI_Request* request = (UDS_22_RDBI_Request*)outRequest;

    if (!request || !buf.data || buf.bufLen < 2) {
        return UDS_NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT;
    }

    request->data_identifier = (buf.data[0] << 8) | buf.data[1];

    return UDS_NRC_PR;  // Positive response
}

UDS_SERVICE_IMPLEMENTATION_t UDS_22_RDBI = {
    .sid = UDS_SID_RDBI,
    .pRequestSize = sizeof(UDS_22_RDBI_Request),
    .pResponseSize = sizeof(UDS_22_RDBI_Response),
    .clientEncodeRequest = x22_RDBI_clientEncodeRequest,
    .clientDecodeResponse = x22_RDBI_clientDecodeResponse,
    .serverPrepareResponse = x22_RDBI_serverPrepareResponse,
    .serverEncodeResponse = x22_RDBI_serverEncodeResponse,
    .serverDecodeRequest = x22_RDBI_serverDecodeRequest,
};