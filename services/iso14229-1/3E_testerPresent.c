#include "3E_testerPresent.h"

size_t x3E_TP_serverEncodeResponse(const void* response, uds_buf_t ret_buf) {
    const UDS_3E_TP_response_t* rResponse = (const UDS_3E_TP_response_t*)response;

    // Safety checks
    if (response == NULL || ret_buf.data == NULL) {
        return 0;
    }

    // Buffer overflow check
    if (ret_buf.bufLen < 1) {
        return 0;
    }

    // Encode response
    size_t response_len = 0;

    // Subfunction (suppression bit only)
    ret_buf.data[response_len++] = rResponse->request.subfunction.raw;

    return response_len;
}

bool x3E_TP_clientDecodeResponse(void* response, const uds_buf_t buf) {
    UDS_3E_TP_response_t* rResponse = (UDS_3E_TP_response_t*)response;

    // Safety
    if (response == NULL || buf.data == NULL || buf.bufLen < 1) {
        return false;
    }

    // Decode response
    rResponse->request.subfunction.raw = buf.data[0];

    return true;
}

UDS_NRC_t x3E_TP_serverDecodeRequest(void* request, const uds_buf_t buf) {
    UDS_3E_TP_request_t* rQuery = (UDS_3E_TP_request_t*)request;

    // Safety checks
    if (rQuery == NULL || buf.data == NULL) {
        return UDS_NRC_IMLOIF;
    }

    // Size check
    if (buf.bufLen < 1) {
        return UDS_NRC_IMLOIF;
    }

    // Decode subfunction (suppression bit only)
    rQuery->subfunction.raw = buf.data[0];

    return UDS_NRC_PR;
}

size_t x3E_TP_clientEncodeRequest(const void* request, uds_buf_t ret_buf) {
    const UDS_3E_TP_request_t* rQuery = (const UDS_3E_TP_request_t*)request;

    // Safety checks
    if (rQuery == NULL || ret_buf.data == NULL) {
        return 0;
    }

    // Buffer overflow check
    if (ret_buf.bufLen < 1) {
        return 0;
    }

    // Encode request
    size_t request_len = 0;

    // Subfunction (suppression bit only)
    ret_buf.data[request_len++] = rQuery->subfunction.raw;

    return request_len;
}

UDS_SERVICE_IMPLEMENTATION_t UDS_3E_TP = {
    .sid = UDS_SID_TP,
    .clientDecodeResponse = x3E_TP_clientDecodeResponse,
    .clientEncodeRequest = x3E_TP_clientEncodeRequest,
    .serverEncodeResponse = x3E_TP_serverEncodeResponse,
    .serverDecodeRequest = x3E_TP_serverDecodeRequest
};