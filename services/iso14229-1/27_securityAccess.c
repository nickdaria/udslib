#include "27_securityAccess.h"
#include "../../protocol/uds_services.h"
#include <string.h>

static bool valid_type(uint8_t type) { return type >= 1 && type <= 0x7e; }

static size_t encode_request(const void* p, UdsBuffer buf) {
    const UDS_27_SA_Request* r = p;
    if (!r || !buf.data || !valid_type(r->securityAccessType) ||
        (r->securityAccessType % 2 == 0 && r->securityAccessDataRecordLen == 0) ||
        (r->securityAccessDataRecordLen && !r->securityAccessDataRecord) ||
        buf.bufLen < 1 || r->securityAccessDataRecordLen > buf.bufLen - 1) return 0;
    buf.data[0] = r->securityAccessType;
    if (r->securityAccessDataRecordLen)
        memcpy(buf.data + 1, r->securityAccessDataRecord, r->securityAccessDataRecordLen);
    return 1 + r->securityAccessDataRecordLen;
}

static UDS_NRC_t decode_request(void* p, UdsBuffer buf) {
    UDS_27_SA_Request* r = p;
    if (!r || !buf.data || buf.bufLen < 1) return UDS_NRC_IMLOIF;
    if (!valid_type(buf.data[0])) return UDS_NRC_SFNF;
    if (!(buf.data[0] & 1) && buf.bufLen == 1) return UDS_NRC_IMLOIF;
    r->securityAccessType = buf.data[0];
    r->securityAccessDataRecord = buf.data + 1;
    r->securityAccessDataRecordLen = buf.bufLen - 1;
    return UDS_NRC_PR;
}

static void prepare_response(const void* request, void* response, UdsBuffer buf) {
    (void)buf;
    if (!request || !response) return;
    UDS_27_SA_Response* r = response;
    r->securityAccessType = ((const UDS_27_SA_Request*)request)->securityAccessType;
    r->securitySeed = NULL;
    r->securitySeedLen = 0;
}

static size_t encode_response(const void* request, const void* response, UdsBuffer buf) {
    const UDS_27_SA_Response* r = response;
    const UDS_27_SA_Request* q = request;
    if (!q || !r || !buf.data || buf.bufLen < 1 ||
        r->securityAccessType != q->securityAccessType ||
        ((q->securityAccessType & 1) && (!r->securitySeed || !r->securitySeedLen)) ||
        (!(q->securityAccessType & 1) && r->securitySeedLen) ||
        r->securitySeedLen > buf.bufLen - 1) return 0;
    buf.data[0] = r->securityAccessType;
    if (r->securitySeedLen) memcpy(buf.data + 1, r->securitySeed, r->securitySeedLen);
    return 1 + r->securitySeedLen;
}

static bool decode_response(void* response, UdsBuffer buf) {
    UDS_27_SA_Response* r = response;
    if (!r || !buf.data || buf.bufLen < 1 || !valid_type(buf.data[0]) ||
        ((buf.data[0] & 1) && buf.bufLen == 1) ||
        (!(buf.data[0] & 1) && buf.bufLen != 1)) return false;
    r->securityAccessType = buf.data[0];
    r->securitySeed = buf.data + 1;
    r->securitySeedLen = buf.bufLen - 1;
    return true;
}

UDS_SERVICE_IMPLEMENTATION_t UDS_27_SA = {
    .sid = UDS_SID_SA, .name = "SecurityAccess",
    .pRequestSize = sizeof(UDS_27_SA_Request),
    .pResponseSize = sizeof(UDS_27_SA_Response),
    .clientEncodeRequest = encode_request, .clientDecodeResponse = decode_response,
    .serverPrepareResponse = prepare_response, .serverEncodeResponse = encode_response,
    .serverDecodeRequest = decode_request
};
