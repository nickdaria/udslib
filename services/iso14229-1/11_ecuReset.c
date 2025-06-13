#include "11_ecuReset.h"
#include "../../protocol/uds_subfunction.h"

size_t x11_ER_clientEncodeRequest(const void* pRequest, UdsBuffer ret_buf) {
    const UDS_11_ER_Request* request = (const UDS_11_ER_Request*)pRequest;

    //  Safety
    if(pRequest == NULL || ret_buf.data == NULL) {
        return 0;
    }

    //  Size check
    if(ret_buf.bufLen < 1) {
        return 0;
    }

    //  Encode request
    size_t request_len = 0;

    //  Reset type
    ret_buf.data[request_len++] = request->resetType.raw;

    //  Power Down Time (if ERPSD)
    if(request->resetType.protocol.subfunction == UDS_ER_LEV_RT_ECU_RESET_ERPSD && ret_buf.bufLen >= 2) {
        ret_buf.data[request_len++] = request->powerDownTime;
    }

    return request_len;
}

bool x11_ER_clientDecodeResponse(void* outResponse, const UdsBuffer buf) {
    UDS_11_ER_Response* response = (UDS_11_ER_Response*)outResponse;

    //  Safety
    if(outResponse == NULL || buf.data == NULL || buf.bufLen < 1) {
        return false;
    }

    //  Decode response
    response->resetType.raw = buf.data[0];

    //  Power down time
    if(buf.bufLen > 1) {
        response->powerDownTime = buf.data[1];
    }
    else {
        //  Failure state
        response->powerDownTime = 0xFF;
    }

    return true;
}

void x11_ER_serverPrepareResponse(const void* pRequest, void* pResponse, UdsBuffer ret_buf) {
    const UDS_11_ER_Request* request = (const UDS_11_ER_Request*)pRequest;
    UDS_11_ER_Response* response = (UDS_11_ER_Response*)pResponse;

    if(!request || !response) {
        return;
    }

    response->powerDownTime = request->powerDownTime;
    response->resetType = response->resetType;
}

size_t x11_ER_serverEncodeResponse(const void* pRequest, const void* pResponse, UdsBuffer ret_buf) {
    const UDS_11_ER_Request* request = (const UDS_11_ER_Request*)pRequest;
    const UDS_11_ER_Response* response = (const UDS_11_ER_Response*)pResponse;
    
    //  Safety
    if(response == NULL || ret_buf.data == NULL) {
        return 0;
    }

    //  Encode response
    size_t response_len = 0;

    //  Reset type
    ret_buf.data[response_len++] = response->resetType.raw;

    //  Power Down Time (if ERPSD)
    if(response->resetType.protocol.subfunction == UDS_ER_LEV_RT_ECU_RESET_ERPSD && ret_buf.bufLen >= 2) {
        ret_buf.data[response_len++] = response->powerDownTime;
    }

    //  No response bit
    if(request->resetType.protocol.suppressPosRspMsgIndicationBit) {
        return 0;
    }

    return response_len;
}

UDS_NRC_t x11_ER_serverDecodeRequest(void* outRequest, const UdsBuffer buf) {
    UDS_11_ER_Request* request = (UDS_11_ER_Request*)outRequest;

    //  Safety
    if(request == NULL || buf.data == NULL) {
        return UDS_NRC_IMLOIF;
    }

    //  Size check
    if(buf.bufLen < 1) {
        return UDS_NRC_IMLOIF;
    }

    //  Decode subfunction (resetType) and suppressPosRspMsgIndicationBit from subfunction byte
    request->resetType.raw = buf.data[0];

    //  Power down type (if ERPSD)
    if(request->resetType.protocol.subfunction == UDS_ER_LEV_RT_ECU_RESET_ERPSD) {
        //  Size check (power down type expected)
        if(buf.bufLen < 2) {
            return UDS_NRC_IMLOIF;
        }

        request->powerDownTime = buf.data[1];
    }

    return UDS_NRC_PR;
}

UDS_SERVICE_IMPLEMENTATION_t UDS_11_ER = {
    .sid = UDS_SID_ER,
    .pRequestSize = sizeof(UDS_11_ER_Request),
    .pResponseSize = sizeof(UDS_11_ER_Response),
    .clientDecodeResponse = x11_ER_clientDecodeResponse,
    .clientEncodeRequest = x11_ER_clientEncodeRequest,
    .serverPrepareResponse = x11_ER_serverPrepareResponse,
    .serverEncodeResponse = x11_ER_serverEncodeResponse,
    .serverDecodeRequest = x11_ER_serverDecodeRequest
};