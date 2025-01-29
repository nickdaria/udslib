#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "../../udslib.h"
#include "../../protocol/uds_subfunction.h"
#include "../uds_service_framework.h"

/**
 *  Diagnostic Session Control (0x11)
 */

typedef struct {
	//  Subfunction: Desired session level
    //  * NOTE: This struct breaks out the supression bit for the response message, but some OEMs do not use it. In that case, just encode and decode the struct as it's used
    UDS_SUBFUNC_LV_t sessionType;

    //  (PDT) Power Down Time
	//	0-254s, 0xFF = failure or time not available
    size_t powerDownTime;
} UDS_11_ER_request_t;

typedef struct {
	UDS_11_ER_request_t request;
} UDS_11_ER_response;

extern UDS_SERVICE_IMPLEMENTATION_t UDS_11_ER;

#ifdef __cplusplus
}
#endif