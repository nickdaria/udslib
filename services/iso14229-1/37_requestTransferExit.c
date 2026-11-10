#include "37_requestTransferExit.h"
#include "../../protocol/uds_services.h"
#include <stdint.h>
#include <string.h>

static size_t encode_request(const void* p, UdsBuffer buf) {
    const UDS_37_RTE_Request* r = p;
    if (!r || (r->transferRequestParameterRecordLen && !r->transferRequestParameterRecord) ||
        r->transferRequestParameterRecordLen > buf.bufLen ||
        (r->transferRequestParameterRecordLen && !buf.data)) return SIZE_MAX;
    if (r->transferRequestParameterRecordLen)
        memcpy(buf.data, r->transferRequestParameterRecord, r->transferRequestParameterRecordLen);
    return r->transferRequestParameterRecordLen;
}

static UDS_NRC_t decode_request(void* p, UdsBuffer buf) {
    UDS_37_RTE_Request* r = p;
    if (!r || (buf.bufLen && !buf.data)) return UDS_NRC_IMLOIF;
    r->transferRequestParameterRecord = buf.data;
    r->transferRequestParameterRecordLen = buf.bufLen;
    return UDS_NRC_PR;
}

static void prepare_response(const void* request, void* response, UdsBuffer buf) {
    (void)request; (void)buf;
    if (!response) return;
    UDS_37_RTE_Response* r = response;
    r->transferResponseParameterRecord = NULL;
    r->transferResponseParameterRecordLen = 0;
}

static size_t encode_response(const void* request, const void* response, UdsBuffer buf) {
    (void)request;
    const UDS_37_RTE_Response* r = response;
    if (!r || (r->transferResponseParameterRecordLen && !r->transferResponseParameterRecord) ||
        r->transferResponseParameterRecordLen > buf.bufLen ||
        (r->transferResponseParameterRecordLen && !buf.data)) return SIZE_MAX;
    if (r->transferResponseParameterRecordLen)
        memcpy(buf.data, r->transferResponseParameterRecord, r->transferResponseParameterRecordLen);
    return r->transferResponseParameterRecordLen;
}

static bool decode_response(void* response, UdsBuffer buf) {
    UDS_37_RTE_Response* r = response;
    if (!r || (buf.bufLen && !buf.data)) return false;
    r->transferResponseParameterRecord = buf.data;
    r->transferResponseParameterRecordLen = buf.bufLen;
    return true;
}

UDS_SERVICE_IMPLEMENTATION_t UDS_37_RTE = {
    .sid = UDS_SID_RTE, .name = "RequestTransferExit",
    .pRequestSize = sizeof(UDS_37_RTE_Request), .pResponseSize = sizeof(UDS_37_RTE_Response),
    .clientEncodeRequest = encode_request, .clientDecodeResponse = decode_response,
    .serverPrepareResponse = prepare_response, .serverEncodeResponse = encode_response,
    .serverDecodeRequest = decode_request,
    .emptyRequestPayloadAllowed = true, .emptyResponsePayloadAllowed = true
};
