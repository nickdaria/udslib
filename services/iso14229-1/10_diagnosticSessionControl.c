#include "10_diagnosticSessionControl.h"

size_t x10_DSC_serverEncodeResponse(const void* response, uds_buf_t ret_buf) {
    const UDS_10_DSC_response* rResponse = (const UDS_10_DSC_response*)response;

    // Safety check
    if (response == NULL || ret_buf.data == NULL || ret_buf.bufLen < 1) {
        return 0;
    }

    // Encode response
    size_t response_len = 0;

    // Desired session level
    ret_buf.data[response_len++] = rResponse->request.desiredSessionLevel.raw;

    return response_len;
}

bool x10_DSC_clientDecodeResponse(void* response, const uds_buf_t buf) {
    UDS_10_DSC_response* rResponse = (UDS_10_DSC_response*)response;

    // Safety check
    if (response == NULL || buf.data == NULL || buf.bufLen < 1) {
        return false;
    }

    // Decode response
    rResponse->request.desiredSessionLevel.raw = buf.data[0];

    return true;
}

UDS_NRC_t x10_DSC_serverDecodeRequest(void* request, const uds_buf_t buf) {
    UDS_10_DSC_request_t* rQuery = (UDS_10_DSC_request_t*)request;

    // Safety check
    if (rQuery == NULL || buf.data == NULL) {
        return UDS_NRC_IMLOIF;
    }

    // Size check
    if (buf.bufLen < 1) {
        return UDS_NRC_IMLOIF;
    }

    // Decode subfunction (desiredSessionLevel)
    rQuery->desiredSessionLevel.raw = buf.data[0];

    return UDS_NRC_PR;
}

size_t x10_DSC_clientEncodeRequest(const void* request, uds_buf_t ret_buf) {
    const UDS_10_DSC_request_t* rQuery = (const UDS_10_DSC_request_t*)request;

    // Safety check
    if (rQuery == NULL || ret_buf.data == NULL) {
        return 0;
    }

    // Size check
    if (ret_buf.bufLen < 1) {
        return 0;
    }

    // Encode request
    size_t request_len = 0;

    // Desired session level
    ret_buf.data[request_len++] = rQuery->desiredSessionLevel.raw;

    return request_len;
}

UDS_SERVICE_IMPLEMENTATION_t UDS_10_DSC = {
    .sid = UDS_SID_DSC,
    .clientDecodeResponse = x10_DSC_clientDecodeResponse,
    .clientEncodeRequest = x10_DSC_clientEncodeRequest,
    .serverEncodeResponse = x10_DSC_serverEncodeResponse,
    .serverDecodeRequest = x10_DSC_serverDecodeRequest
};