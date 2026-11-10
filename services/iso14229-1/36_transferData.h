#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include "../uds_service_framework.h"

typedef struct {
    uint8_t blockSequenceCounter; /* starts at 1, wraps from 0xff to 0 */
    const uint8_t* transferRequestParameterRecord;
    size_t transferRequestParameterRecordLen;
} UDS_36_TD_Request;

typedef struct {
    uint8_t blockSequenceCounter;
    const uint8_t* transferResponseParameterRecord;
    size_t transferResponseParameterRecordLen;
} UDS_36_TD_Response;

/* The application handler tracks transfer direction, expected counter,
   retransmissions, negotiated block length, and transferred byte count. */
extern UDS_SERVICE_IMPLEMENTATION_t UDS_36_TD;
#ifdef __cplusplus
}
#endif
