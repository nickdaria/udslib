#pragma once
#include "../uds_service_framework.h"

/* Address and size are big-endian byte strings, 1..15 bytes each. This keeps
   the full ISO addressAndLengthFormatIdentifier range available. */
typedef struct {
    uint8_t dataFormatIdentifier;
    const uint8_t* memoryAddress;
    uint8_t memoryAddressLen;
    const uint8_t* memorySize;
    uint8_t memorySizeLen;
} UDS_TransferRequest;

typedef struct {
    const uint8_t* maxNumberOfBlockLength; /* full 0x36 message length, incl. SID/counter */
    uint8_t maxNumberOfBlockLengthLen; /* 1..15, high nibble of LFI */
} UDS_TransferResponse;

size_t uds_transfer_encode_request(const void*, UdsBuffer);
UDS_NRC_t uds_transfer_decode_request(void*, UdsBuffer);
void uds_transfer_prepare_response(const void*, void*, UdsBuffer);
size_t uds_transfer_encode_response(const void*, const void*, UdsBuffer);
bool uds_transfer_decode_response(void*, UdsBuffer);
