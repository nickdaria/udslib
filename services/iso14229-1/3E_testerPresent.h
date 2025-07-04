#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "../../udslib.h"
#include "../../protocol/uds_subfunction.h"
#include "../uds_service_framework.h"

typedef struct {
    //  "Zero subfunction" which is solely present to provide the suppression bit
    UDS_SUBFUNC_LV_t subfunction;

    //  TODO: Implement session parameter record support
} UDS_3E_TP_Request;

typedef struct {
    UDS_SUBFUNC_LV_t subfunction;
} UDS_3E_TP_Response;

extern UDS_SERVICE_IMPLEMENTATION_t UDS_3E_TP;

#ifdef __cplusplus
}
#endif