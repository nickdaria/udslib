#include "11_ecuReset.h"
#include "../../protocol/uds_subfunction.h"

size_t x11_ER_serverEncodeResponse(const void* response, uds_buf_t ret_buf) {
    const UDS_11_ER_response* rResponse = (const UDS_11_ER_response*)response;
    
    //  Safety
    if(response == NULL || ret_buf.data == NULL) {
        return 0;
    }

    //  Encode response
    size_t response_len = 0;

    //  Reset type
    ret_buf.data[response_len++] = rResponse->request.resetType.raw;

    //  Power Down Time (if ERPSD)
    if(rResponse->request.resetType.protocol.subfunction == UDS_ER_LEV_RT_ECU_RESET_ERPSD && ret_buf.bufLen >= 2) {
        ret_buf.data[response_len++] = rResponse->request.powerDownTime;
    }

    return response_len;
}

bool x11_ER_clientDecodeResponse(void* response, const uds_buf_t buf) {
    UDS_11_ER_response* rResponse = (UDS_11_ER_response*)response;

    //  Safety
    if(response == NULL || buf.data == NULL || buf.bufLen < 1) {
        return false;
    }

    //  Decode response
    rResponse->request.resetType.raw = buf.data[0];

    //  Power down time
    if(buf.bufLen > 1) {
        rResponse->request.powerDownTime = buf.data[1];
    }
    else {
        //  Failure state
        rResponse->request.powerDownTime = 0xFF;
    }

    return true;
}

UDS_NRC_t x11_ER_serverDecodeRequest(void* request, const uds_buf_t buf) {
    UDS_11_ER_request_t* rQuery = (UDS_11_ER_request_t*)request;

    //  Safety
    if(rQuery == NULL || buf.data == NULL) {
        return UDS_NRC_IMLOIF;
    }

    //  Size check
    if(buf.bufLen < 1) {
        return UDS_NRC_IMLOIF;
    }

    //  Decode subfunction (resetType) and suppressPosRspMsgIndicationBit from subfunction byte
    rQuery->resetType.raw = buf.data[0];

    //  Power down type (if ERPSD)
    if(rQuery->resetType.protocol.subfunction == UDS_ER_LEV_RT_ECU_RESET_ERPSD) {
        //  Size check (power down type expected)
        if(buf.bufLen < 2) {
            return UDS_NRC_IMLOIF;
        }

        rQuery->powerDownTime = buf.data[1];
    }

    return UDS_NRC_PR;
}

size_t x11_ER_clientEncodeRequest(const void* request, uds_buf_t ret_buf) {
    const UDS_11_ER_request_t* rQuery = (const UDS_11_ER_request_t*)request;

    //  Safety
    if(rQuery == NULL || ret_buf.data == NULL) {
        return 0;
    }

    //  Size check
    if(ret_buf.bufLen < 1) {
        return 0;
    }

    //  Encode request
    size_t request_len = 0;

    //  Reset type
    ret_buf.data[request_len++] = rQuery->resetType.raw;

    //  Power Down Time (if ERPSD)
    if(rQuery->resetType.protocol.subfunction == UDS_ER_LEV_RT_ECU_RESET_ERPSD && ret_buf.bufLen >= 2) {
        ret_buf.data[request_len++] = rQuery->powerDownTime;
    }

    return request_len;
}

UDS_SERVICE_IMPLEMENTATION_t UDS_11_ER = {
    .sid = UDS_SID_ER,
    .clientDecodeResponse = x11_ER_clientDecodeResponse,
    .clientEncodeRequest = x11_ER_clientEncodeRequest,
    .serverEncodeResponse = x11_ER_serverEncodeResponse,
    .serverDecodeRequest = x11_ER_serverDecodeRequest
};