#include "7F_NACK.h"

size_t x7F_NACK_clientEncodeRequest(const void* pRequest, UdsBuffer ret_buf) {
    (void)pRequest;
    (void)ret_buf;
    return 0; // No client request encoding for 0x7F
}

bool x7F_NACK_clientDecodeResponse(void* outResponse, const UdsBuffer buf) {
    UDS_7F_NACK_Response* response = (UDS_7F_NACK_Response*)outResponse;

    if (!response || buf.bufLen < 2) {
        return false;
    }

    response->failedSID = buf.data[0];
    response->nrc = (UDS_NRC_t)buf.data[1];
    return true;
}

void x7F_NACK_serverPrepareResponse(const void* pRequest, void* pResponse, UdsBuffer ret_buf) {
    (void)pRequest;
    (void)pResponse;
    (void)ret_buf;
    // Not applicable — 7F is generated dynamically in error paths
}

size_t x7F_NACK_serverEncodeResponse(const void* pRequest, const void* pResponse, UdsBuffer ret_buf) {
    const UDS_7F_NACK_Response* response = (const UDS_7F_NACK_Response*)pResponse;

    if (!response || !ret_buf.data || ret_buf.bufLen < 2) {
        return 0;
    }

    ret_buf.data[0] = response->failedSID;
    ret_buf.data[1] = (uint8_t)response->nrc;

    return 2;
}

UDS_NRC_t x7F_NACK_serverDecodeRequest(void* outRequest, const UdsBuffer buf) {
    (void)outRequest;
    (void)buf;
    return UDS_NRC_SNS; // Negative response is not a valid request
}

UDS_SERVICE_IMPLEMENTATION_t UDS_7F_NACK = {
    .sid = UDS_SID_NEGATIVE_RESPONSE,
    .pRequestSize = 0,
    .pResponseSize = sizeof(UDS_7F_NACK_Response),
    .clientDecodeResponse = x7F_NACK_clientDecodeResponse,
    .clientEncodeRequest = x7F_NACK_clientEncodeRequest,
    .serverPrepareResponse = x7F_NACK_serverPrepareResponse,
    .serverEncodeResponse = x7F_NACK_serverEncodeResponse,
    .serverDecodeRequest = x7F_NACK_serverDecodeRequest
};
