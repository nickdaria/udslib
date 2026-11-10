#include "download_upload_codec.h"
#include <string.h>

size_t uds_transfer_encode_request(const void* p, UdsBuffer buf) {
    const UDS_TransferRequest* r = p;
    if (!r || !buf.data || !r->memoryAddress || !r->memorySize ||
        !r->memoryAddressLen || r->memoryAddressLen > 15 ||
        !r->memorySizeLen || r->memorySizeLen > 15) return 0;
    size_t len = 2u + r->memoryAddressLen + r->memorySizeLen;
    if (buf.bufLen < len) return 0;
    buf.data[0] = r->dataFormatIdentifier;
    buf.data[1] = (uint8_t)((r->memorySizeLen << 4) | r->memoryAddressLen);
    memcpy(buf.data + 2, r->memoryAddress, r->memoryAddressLen);
    memcpy(buf.data + 2 + r->memoryAddressLen, r->memorySize, r->memorySizeLen);
    return len;
}

UDS_NRC_t uds_transfer_decode_request(void* p, UdsBuffer buf) {
    UDS_TransferRequest* r = p;
    if (!r || !buf.data || buf.bufLen < 4) return UDS_NRC_IMLOIF;
    uint8_t address_len = buf.data[1] & 0x0f;
    uint8_t size_len = buf.data[1] >> 4;
    if (!address_len || !size_len || buf.bufLen != (size_t)2 + address_len + size_len)
        return UDS_NRC_IMLOIF;
    r->dataFormatIdentifier = buf.data[0];
    r->memoryAddressLen = address_len;
    r->memorySizeLen = size_len;
    r->memoryAddress = buf.data + 2;
    r->memorySize = buf.data + 2 + address_len;
    return UDS_NRC_PR;
}

void uds_transfer_prepare_response(const void* request, void* response, UdsBuffer buf) {
    (void)request; (void)buf;
    if (!response) return;
    UDS_TransferResponse* r = response;
    r->maxNumberOfBlockLength = NULL;
    r->maxNumberOfBlockLengthLen = 0;
}

size_t uds_transfer_encode_response(const void* request, const void* response, UdsBuffer buf) {
    (void)request;
    const UDS_TransferResponse* r = response;
    if (!r || !buf.data || !r->maxNumberOfBlockLength ||
        !r->maxNumberOfBlockLengthLen || r->maxNumberOfBlockLengthLen > 15 ||
        buf.bufLen < (size_t)1 + r->maxNumberOfBlockLengthLen) return 0;
    bool nonzero = false;
    for (uint8_t i = 0; i < r->maxNumberOfBlockLengthLen; ++i)
        nonzero |= r->maxNumberOfBlockLength[i] != 0;
    if (!nonzero) return 0;
    buf.data[0] = r->maxNumberOfBlockLengthLen << 4;
    memcpy(buf.data + 1, r->maxNumberOfBlockLength, r->maxNumberOfBlockLengthLen);
    return 1u + r->maxNumberOfBlockLengthLen;
}

bool uds_transfer_decode_response(void* response, UdsBuffer buf) {
    UDS_TransferResponse* r = response;
    if (!r || !buf.data || buf.bufLen < 2 || (buf.data[0] & 0x0f)) return false;
    uint8_t len = buf.data[0] >> 4;
    if (!len || buf.bufLen != (size_t)1 + len) return false;
    bool nonzero = false;
    for (uint8_t i = 0; i < len; ++i) nonzero |= buf.data[i + 1] != 0;
    if (!nonzero) return false;
    r->maxNumberOfBlockLengthLen = len;
    r->maxNumberOfBlockLength = buf.data + 1;
    return true;
}
