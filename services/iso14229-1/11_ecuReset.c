#include "11_ecuReset.h"
#include "../../protocol/uds_subfunction.h"

size_t UDS_11_ER_server_encodePositiveResponse(const UDS_11_ER_request_t* query, uint8_t* buf, const size_t buf_len) {
    //  Safety
    if(query == NULL || buf == NULL || buf_len == 0) {
        return 0;
    }

    //  Encode response
    size_t response_len = 0;

    //  Reset type
    buf[response_len++] = uds_subfunc_encode(query->resetType);

    //  Power Down Time (if ERPSD)
    if(query->resetType.subfunction == UDS_ER_LEV_RT_ECU_RESET_ERPSD && buf_len >= 2) {
        buf[response_len++] = query->powerDownTime;
    }

    return response_len;
}

UDS_NRC_t UDS_11_ER_server_decodeRequest(UDS_11_ER_request_t* query, const uint8_t* buf, const size_t buf_len) {
    //  Safety
    if(query == NULL || buf == NULL) {
        return UDS_NRC_IMLOIF;
    }

    //  Size check
    if(buf_len < 1) {
        return UDS_NRC_IMLOIF;
    }

    //  Decode subfunction (resetType) and suppressPosRspMsgIndicationBit from subfunction byte
    query->resetType = uds_subfunc_decode(buf[0]);

    //  Power down type (if ERPSD)
    if(query->resetType.subfunction == UDS_ER_LEV_RT_ECU_RESET_ERPSD) {
        //  Size check (power down type expected)
        if(buf_len < 2) {
            return UDS_NRC_IMLOIF;
        }

        query->powerDownTime = buf[1];
    }

    return UDS_NRC_PR;
}

size_t UDS_11_ER_client_encodeRequest(const UDS_11_ER_request_t* query, uint8_t* buf, const size_t buf_len) {
    //  Safety
    if(query == NULL || buf == NULL || buf_len == 0) {
        return 0;
    }

    //  Size check
    if(buf_len < 1) {
        return 0;
    }

    //  Encode request
    size_t request_len = 0;

    //  Reset type
    buf[request_len++] = uds_subfunc_encode(query->resetType);

    //  Power Down Time (if ERPSD)
    if(query->resetType.subfunction == UDS_ER_LEV_RT_ECU_RESET_ERPSD && buf_len >= 2) {
        buf[request_len++] = query->powerDownTime;
    }

    return request_len;
}