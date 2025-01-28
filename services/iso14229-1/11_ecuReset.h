#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "../../udslib.h"
#include "../../protocol/uds_subfunction.h"
#include "../uds_service_framework.h"

/**
 *  ECU Reset (0x11)
 *      https://piembsystech.com/ecu-reset-service-identifier-0x11-uds-protocol/
 */

//  ECU Reset Types
typedef enum {
	UDS_ER_LEV_RT_ECU_RESET_HR             	= 0x01,		//  Hard Reset
	UDS_ER_LEV_RT_ECU_RESET_KOFFONR      	= 0x02,		//  Key Off On Reset
	UDS_ER_LEV_RT_ECU_RESET_SR            	= 0x03,		//  Soft Reset
	UDS_ER_LEV_RT_ECU_RESET_ERPSD 			= 0x04,		//	Enable rapid power shutdown
	UDS_ER_LEV_RT_ECU_RESET_DRPSD 			= 0x05,		//	Disable rapid power shutdown

	/* 0x06-0x3F (ISOSAERESRVD) ISO SAE Reserved */

	/* 0x40-0x5F (VMS) Vehicle Manufacturer Specific */

	/* 0x70-0x7E (SSS) System Supplier Specific */

	UDS_ER_LEV_RT_MAX						= 0x7F		//	Maximum value
} UDS_11_ER_LEV_RT_t;

typedef struct {
	//  (UDS_11_ER_LEV_RT_t) Reset Type
	//	- subfunction = reset type
	//	- suppressPosRspMsgIndicationBit
    UDS_SUBFUNC_LV_t resetType;

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