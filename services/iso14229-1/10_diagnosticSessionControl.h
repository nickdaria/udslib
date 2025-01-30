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

//  Sessions recognized by the ISO 14229-1 standard
typedef enum {
    /* 0x00 (ISOSAERESRVD) ISO SAE Reserved */

    UDS_DSC_SESSION_DS                  = 0x01,  // Default Session
    UDS_DSC_SESSION_DEFAULT             = UDS_DSC_SESSION_DS,

    UDS_DSC_SESSION_PRGS                = 0x02,  // Programming Session
    UDS_DSC_SESSION_PROGRAMMING         = UDS_DSC_SESSION_PRGS,

    UDS_DSC_SESSION_EXTDSD              = 0x03,  // Extended Diagnostic Session
    UDS_DSC_SESSION_EXTENDED            = UDS_DSC_SESSION_EXTDSD,

    UDS_DSC_SESSION_SSDS                = 0x04,  // Safety System Diagnostic Session
    UDS_DSC_SESSION_SAFETY              = UDS_DSC_SESSION_SSDS,

    /* 0x05-0x3F (ISO Reserved) */

    /* 0x40-0x5F (VMS) Vehicle Manufacturer Specific */

    /* 0x60-0x7E (SSS) System Supplier Specific */

    /* 0x7E (ISOSAERESRVD) ISO SAE Reserved */
    UDS_DSC_SESSION_MAX               = 0x7F   // Maximum value
} UDS_10_DSC_SESSION_t;

typedef struct {
	//  Subfunction: Desired session level
    //  * NOTE: This struct breaks out the supression bit for the response message, but some OEMs do not use it. In that case, just encode and decode the struct as it's used
    UDS_SUBFUNC_LV_t desiredSessionLevel;

    //  TODO: Implement session parameter record support
} UDS_10_DSC_request_t;

typedef struct {
	UDS_10_DSC_request_t request;
} UDS_10_DSC_response_t;

extern UDS_SERVICE_IMPLEMENTATION_t UDS_10_DSC;

#ifdef __cplusplus
}
#endif