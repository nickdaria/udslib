#include "3E_testerPresent.h"

size_t x3E_TP_clientEncodeRequest(const void* pRequest, UdsBuffer ret_buf) {
    const UDS_3E_TP_Request* request = (const UDS_3E_TP_Request*)pRequest;

    // Safety checks
    if (pRequest == NULL || ret_buf.data == NULL) {
        return 0;
    }

    // Buffer overflow check
    if (ret_buf.bufLen < 1) {
        return 0;
    }

    // Encode request
    size_t request_len = 0;

    // Subfunction (suppression bit only)
    ret_buf.data[request_len++] = request->subfunction.raw;

    return request_len;
}

bool x3E_TP_clientDecodeResponse(void* outResponse, const UdsBuffer buf) {
    UDS_3E_TP_Response* response = (UDS_3E_TP_Response*)outResponse;

    // Safety
    if (outResponse == NULL || buf.data == NULL || buf.bufLen < 1) {
        return false;
    }

    // Decode response
    response->subfunction.raw = buf.data[0];

    return true;
}

void x3E_TP_serverPrepareResponse(const void* pRequest, void* pResponse, UdsBuffer ret_buf) {
    const UDS_3E_TP_Request* request = (const UDS_3E_TP_Request*)pRequest;
    UDS_3E_TP_Response* response = (UDS_3E_TP_Response*)pResponse;

    if(!request || !response) {
        return;
    }
    
    response->subfunction = request->subfunction;
}

size_t x3E_TP_serverEncodeResponse(const void* pRequest, const void* pResponse, UdsBuffer ret_buf) {
    const UDS_3E_TP_Request* request = (const UDS_3E_TP_Request*)pRequest;
    const UDS_3E_TP_Response* response = (const UDS_3E_TP_Response*)pResponse;

    // Safety checks
    if (pResponse == NULL || ret_buf.data == NULL || ret_buf.bufLen < 1) {
        return 0;
    }

    // Buffer overflow check
    if (ret_buf.bufLen < 1) {
        return 0;
    }

    // Encode response
    size_t response_len = 0;

    // Subfunction (suppression bit only)
    ret_buf.data[response_len++] = response->subfunction.raw;

    return response_len;
}

UDS_NRC_t x3E_TP_serverDecodeRequest(void* outRequest, const UdsBuffer buf) {
    UDS_3E_TP_Request* request = (UDS_3E_TP_Request*)outRequest;

    // Safety checks
    if (outRequest == NULL || buf.data == NULL) {
        return UDS_NRC_IMLOIF;
    }

    // Size check
    if (buf.bufLen < 1) {
        return UDS_NRC_IMLOIF;
    }

    // Decode subfunction (suppression bit only)
    request->subfunction.raw = buf.data[0];

    return UDS_NRC_PR;
}


UDS_SERVICE_IMPLEMENTATION_t UDS_3E_TP = {
    .sid = UDS_SID_TP,
    .pRequestSize = sizeof(UDS_3E_TP_Request),
    .pResponseSize = sizeof(UDS_3E_TP_Response),
    .clientDecodeResponse = x3E_TP_clientDecodeResponse,
    .clientEncodeRequest = x3E_TP_clientEncodeRequest,
    .serverPrepareResponse = x3E_TP_serverPrepareResponse,
    .serverEncodeResponse = x3E_TP_serverEncodeResponse,
    .serverDecodeRequest = x3E_TP_serverDecodeRequest
};