#include "10_diagnosticSessionControl.h"

size_t x10_DSC_clientEncodeRequest(const void* pRequest, UdsBuffer ret_buf) {
    const UDS_10_DSC_Request* request = (const UDS_10_DSC_Request*)pRequest;

    // Safety check
    if (pRequest == NULL || ret_buf.data == NULL) {
        return 0;
    }

    // Size check
    if (ret_buf.bufLen < 1) {
        return 0;
    }

    // Encode request
    size_t request_len = 0;

    // Desired session level
    ret_buf.data[request_len++] = request->desiredSessionLevel.raw;

    return request_len;
}

bool x10_DSC_clientDecodeResponse(void* outResponse, const UdsBuffer buf) {
    UDS_10_DSC_Response* response = (UDS_10_DSC_Response*)outResponse;

    // Safety check
    if (outResponse == NULL || buf.data == NULL || buf.bufLen < 1) {
        return false;
    }

    // Decode response
    response->desiredSessionLevel.raw = buf.data[0];

    return true;
}

void x10_DSC_serverPrepareResponse(const void* pRequest, void* pResponse, UdsBuffer ret_buf) {
    const UDS_10_DSC_Request* request = (const UDS_10_DSC_Request*)pRequest;
    UDS_10_DSC_Response* response = (UDS_10_DSC_Response*)pResponse;

    response->desiredSessionLevel = request->desiredSessionLevel;
}

size_t x10_DSC_serverEncodeResponse(const void* pRequest, const void* pResponse, UdsBuffer ret_buf) {
    const UDS_10_DSC_Request* request = (const UDS_10_DSC_Request*)pRequest;
    const UDS_10_DSC_Response* response = (const UDS_10_DSC_Response*)pResponse;

    // Safety check
    if (response == NULL || ret_buf.data == NULL || ret_buf.bufLen < 1) {
        return 0;
    }

    // Encode response
    size_t response_len = 0;

    // Desired session level
    ret_buf.data[response_len++] = response->desiredSessionLevel.raw;
    
    //  No response bit
    if(request->desiredSessionLevel.protocol.suppressPosRspMsgIndicationBit) {
        return 0;
    }

    return response_len;
}

UDS_NRC_t x10_DSC_serverDecodeRequest(void* outRequest, const UdsBuffer buf) {
    UDS_10_DSC_Request* rQuery = (UDS_10_DSC_Request*)outRequest;

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

UDS_SERVICE_IMPLEMENTATION_t UDS_10_DSC = {
    .sid = UDS_SID_DSC,
    .pRequestSize = sizeof(UDS_10_DSC_Request),
    .pResponseSize = sizeof(UDS_10_DSC_Response),
    .clientDecodeResponse = x10_DSC_clientDecodeResponse,
    .clientEncodeRequest = x10_DSC_clientEncodeRequest,
    .serverPrepareResponse = x10_DSC_serverPrepareResponse,
    .serverEncodeResponse = x10_DSC_serverEncodeResponse,
    .serverDecodeRequest = x10_DSC_serverDecodeRequest
};