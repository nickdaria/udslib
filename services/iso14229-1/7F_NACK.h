#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "../../udslib.h"
#include "../../protocol/uds_negative_response.h"
#include "../uds_service_framework.h"

typedef struct {
    uint8_t failedSID;
    UDS_NRC_t nrc;
} UDS_7F_NACK_Response;

extern UDS_SERVICE_IMPLEMENTATION_t UDS_7F_NACK;

#ifdef __cplusplus
}
#endif