#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include "../uds_service_framework.h"

typedef struct {
    const uint8_t* transferRequestParameterRecord;
    size_t transferRequestParameterRecordLen;
} UDS_37_RTE_Request;

typedef struct {
    const uint8_t* transferResponseParameterRecord;
    size_t transferResponseParameterRecordLen;
} UDS_37_RTE_Response;

/* Both records are optional. Application handler validates transfer completion. */
extern UDS_SERVICE_IMPLEMENTATION_t UDS_37_RTE;
#ifdef __cplusplus
}
#endif
