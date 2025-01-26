#include "11_ecuReset.h"
#include "../../protocol/uds_subfunction.h"

size_t UDS_11_ER_server_encodePositiveResponse(const UDS_11_ER_request_t* query, uds_buf_t* ret_buf) {
    //  Safety
    if(query == NULL || ret_buf->data == NULL) {
        return 0;
    }

    //  Encode response
    size_t response_len = 0;

    //  Reset type
    ret_buf->data[response_len++] = uds_subfunc_encode(query->resetType);

    //  Power Down Time (if ERPSD)
    if(query->resetType.subfunction == UDS_ER_LEV_RT_ECU_RESET_ERPSD && ret_buf->buf_len >= 2) {
        ret_buf->data[response_len++] = query->powerDownTime;
    }

    return response_len;
}

UDS_NRC_t UDS_11_ER_server_decodeRequest(UDS_11_ER_request_t* query, uds_buf_t* buf) {
    //  Safety
    if(query == NULL || buf == NULL) {
        return UDS_NRC_IMLOIF;
    }

    //  Size check
    if(buf->buf_len < 1) {
        return UDS_NRC_IMLOIF;
    }

    //  Decode subfunction (resetType) and suppressPosRspMsgIndicationBit from subfunction byte
    query->resetType = uds_subfunc_decode(buf->data[0]);

    //  Power down type (if ERPSD)
    if(query->resetType.subfunction == UDS_ER_LEV_RT_ECU_RESET_ERPSD) {
        //  Size check (power down type expected)
        if(buf->buf_len < 2) {
            return UDS_NRC_IMLOIF;
        }

        query->powerDownTime = buf->data[1];
    }

    return UDS_NRC_PR;
}

size_t UDS_11_ER_client_encodeRequest(const UDS_11_ER_request_t* query, uds_buf_t* ret_buf) {
    //  Safety
    if(query == NULL || ret_buf->data == NULL) {
        return 0;
    }

    //  Size check
    if(ret_buf->buf_len < 1) {
        return 0;
    }

    //  Encode request
    size_t request_len = 0;

    //  Reset type
    ret_buf->data[request_len++] = uds_subfunc_encode(query->resetType);

    //  Power Down Time (if ERPSD)
    if(query->resetType.subfunction == UDS_ER_LEV_RT_ECU_RESET_ERPSD && ret_buf->buf_len >= 2) {
        ret_buf->data[request_len++] = query->powerDownTime;
    }

    return request_len;
}