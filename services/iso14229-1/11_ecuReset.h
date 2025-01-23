#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "../../udslib.h"

/**
 *  ECU Reset (0x11)
 *      https://piembsystech.com/ecu-reset-service-identifier-0x11-uds-protocol/
 * 
 *      [Accepts]
 *     - Reset type
 * 
 *      [Response]
 *      - B0: Subfunction (Reset Type)
 *      - Execute Reset
 * 
 *      [NACK Response]
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
	//  (LEV_RT_) Reset Type
    UDS_11_ER_LEV_RT_t resetType;

    //  (PDT) Power Down Time
    size_t powerDownTime;
} UDS_11_ER_query_t;

//  Encoding outgoing response
size_t UDS_11_ER_response_encode(const UDS_11_ER_query_t* query, const UDS_NRC_t response, void* buf, const size_t buf_len);

//  Decoding incoming response
UDS_NRC_t UDS_11_ER_response_decode(UDS_11_ER_query_t* response, const void* buf, const size_t len);

//  Encoding outgoing request
size_t UDS_11_ER_request_encode(const UDS_11_ER_query_t* query, void* buf);

//  Decoding incoming request
UDS_NRC_t UDS_11_ER_request_decode(UDS_11_ER_query_t* query, const void* buf, const size_t len);

#ifdef __cplusplus
}
#endif