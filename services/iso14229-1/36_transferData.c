#include "36_transferData.h"
#include "../../protocol/uds_services.h"
#include <string.h>

static size_t encode_request(const void* p, UdsBuffer buf) {
    const UDS_36_TD_Request* r = p;
    if (!r || !buf.data || buf.bufLen < 1 ||
        (r->transferRequestParameterRecordLen && !r->transferRequestParameterRecord) ||
        r->transferRequestParameterRecordLen > buf.bufLen - 1) return 0;
    buf.data[0] = r->blockSequenceCounter;
    if (r->transferRequestParameterRecordLen)
        memcpy(buf.data + 1, r->transferRequestParameterRecord, r->transferRequestParameterRecordLen);
    return 1 + r->transferRequestParameterRecordLen;
}

static UDS_NRC_t decode_request(void* p, UdsBuffer buf) {
    UDS_36_TD_Request* r = p;
    if (!r || !buf.data || buf.bufLen < 1) return UDS_NRC_IMLOIF;
    r->blockSequenceCounter = buf.data[0];
    r->transferRequestParameterRecord = buf.data + 1;
    r->transferRequestParameterRecordLen = buf.bufLen - 1;
    return UDS_NRC_PR;
}

static void prepare_response(const void* request, void* response, UdsBuffer buf) {
    (void)buf;
    if (!request || !response) return;
    UDS_36_TD_Response* r = response;
    r->blockSequenceCounter = ((const UDS_36_TD_Request*)request)->blockSequenceCounter;
    r->transferResponseParameterRecord = NULL;
    r->transferResponseParameterRecordLen = 0;
}

static size_t encode_response(const void* request, const void* response, UdsBuffer buf) {
    const UDS_36_TD_Request* q = request;
    const UDS_36_TD_Response* r = response;
    if (!q || !r || !buf.data || buf.bufLen < 1 ||
        r->blockSequenceCounter != q->blockSequenceCounter ||
        (r->transferResponseParameterRecordLen && !r->transferResponseParameterRecord) ||
        r->transferResponseParameterRecordLen > buf.bufLen - 1) return 0;
    buf.data[0] = r->blockSequenceCounter;
    if (r->transferResponseParameterRecordLen)
        memcpy(buf.data + 1, r->transferResponseParameterRecord, r->transferResponseParameterRecordLen);
    return 1 + r->transferResponseParameterRecordLen;
}

static bool decode_response(void* response, UdsBuffer buf) {
    UDS_36_TD_Response* r = response;
    if (!r || !buf.data || buf.bufLen < 1) return false;
    r->blockSequenceCounter = buf.data[0];
    r->transferResponseParameterRecord = buf.data + 1;
    r->transferResponseParameterRecordLen = buf.bufLen - 1;
    return true;
}

UDS_SERVICE_IMPLEMENTATION_t UDS_36_TD = {
    .sid = UDS_SID_TD, .name = "TransferData",
    .pRequestSize = sizeof(UDS_36_TD_Request), .pResponseSize = sizeof(UDS_36_TD_Response),
    .clientEncodeRequest = encode_request, .clientDecodeResponse = decode_response,
    .serverPrepareResponse = prepare_response, .serverEncodeResponse = encode_response,
    .serverDecodeRequest = decode_request
};
