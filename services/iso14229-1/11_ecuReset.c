#include "11_ecuReset.h"
#include "../../protocol/uds_subfunction.h"

size_t UDS_11_ER_server_encodePositiveResponse(const UDS_11_ER_request_t* query, uint8_t* buf, const size_t buf_len) {
    //  Safety
    if(query == NULL || buf == NULL || buf_len == 0) {
        return 0;
    }

    //  Encode response
    size_t response_len;

    //  Reset type
    buf[response_len++] = query->resetType;

    //  Power Down Time (if ERPSD)
    if(query->powerDownTime == UDS_ER_LEV_RT_ECU_RESET_ERPSD && buf_len >= 2) {
        buf[response_len++] = query->powerDownTime;
    }

    return response_len;
}

UDS_NRC_t UDS_11_ER_server_decodeRequest(UDS_11_ER_request_t* query, bool* suppressPosRspMsgIndicationBit, const uint8_t* buf, const size_t buf_len) {
    //  Safety
    if(query == NULL || buf == NULL || buf_len == 0) {
        return UDS_NRC_IMLOIF;
    }

    //  Decode subfunction and suppressPosRspMsgIndicationBit
    UDS_SUBFUNC_LV_t subfunc = uds_subfunc_decode(buf[0]);

    //  Return suppressPosRspMsgIndicationBit
    if(suppressPosRspMsgIndicationBit != NULL) {
        *suppressPosRspMsgIndicationBit = subfunc.suppressPosRspMsgIndicationBit;
    }

    //  Decode reset type
    query->resetType = subfunc.subfunction;

    //  Power down type (if ERPSD)
    if(query->resetType == UDS_ER_LEV_RT_ECU_RESET_ERPSD) {
        if(buf_len < 2) {
            return UDS_NRC_IMLOIF;
        }

        query->powerDownTime = buf[1];
    }

    return UDS_NRC_PR;
}