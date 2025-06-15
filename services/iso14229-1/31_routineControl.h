#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <udslib.h>
#include "../uds_service_framework.h"

#include <stdint.h>
#include <stdbool.h>

/*
    Routine Control (0x31)
        https://piembsystech.com/routinecontrol-0x31-service-uds-protocol/

        [Accepts]
        - RCTP Routine Control Type (LEV)
		- RI Routine Identifier
		- RCCO Routine Control Option Record

        [Response]
        - DID and response data

        [Order of operations (ISO)]

        [NACK Response]
		- 0x12: Sub-function not supported
        - 0x13: Length of message is invalid or too many requests at once
        - 0x22: Conditions not correct
        - 0x24: Request sequence error
        - 0x31: Request out of range (DID not supported)
        - 0x33: Security access denied
        - 0x72: General programming failure
*/

typedef enum {
	/* 0x00 = ISO reserved */
	UDS_31_RC_LEV_RCTP_START_ROUTINE = 0x01,
	UDS_31_RC_LEV_RCTP_STOP_ROUTINE = 0x02,
	UDS_31_RC_LEV_RCTP_REQUEST_ROUTINE_RESULTS = 0x03,
	/* 0x03 - 0x7F = ISO reserved */
} UDS_31_RC_LEV_RCTP_t;

typedef struct {
	/// @brief Routine control type
	/// @note UDS_31_RC_LEV_RCTP_t
	UDS_SUBFUNC_LV_t routineControlType;

	/// @brief Identifier for routine type
	uint16_t routineIdentifier;

	/// @brief Pointer to provided argument buffer
	uint8_t* routineControlOptionBuf;

	/// @brief Length of provided argument buffer
	size_t routineControlOptionBufLen;
} UDS_31_RC_Request;

typedef struct {
	/// @brief Routine control type
	/// @note UDS_31_RC_LEV_RCTP_t
	UDS_SUBFUNC_LV_t routineControlType;

	/// @brief Identifier for routine type
	uint16_t routineIdentifier;

	/// @brief Byte for manufacturer implementation
	uint8_t routineInfo;

	/// @brief Pointer to provided argument buffer
	uint8_t* routineStatusRecordBuf;

	/// @brief Length of provided argument buffer
	size_t routineStatusRecordBufLen;
} UDS_31_RC_Response;

extern UDS_SERVICE_IMPLEMENTATION_t UDS_31_RC;

#ifdef __cplusplus
}
#endif