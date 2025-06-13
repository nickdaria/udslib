#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "../../udslib.h"
#include "../uds_service_framework.h"

#include <stdint.h>
#include <stdbool.h>

/*
    Read Data By Identifier (0x22) - Single PID implementation
        https://piembsystech.com/read-data-by-identifier-0x22-service-in-uds-protocol/

        [Accepts]
        - 1 Data Identifier (DID)

        [Response]
        - DID and response data

        [Order of operations (ISO)]

        [NACK Response]
        - 0x13: Length of message is invalid or too many requests at once
        - 0x14: Response too long
        - 0x22: Conditions not correct
        - 0x31: Request out of range (DID not supported)
        - 0x33: Security access denied
*/

typedef struct {
    //  Identifier data array & data length array
    uint16_t data_identifier;
} UDS_22_RDBI_Request;

typedef struct {
    /// @brief PID
    uint16_t data_identifier;

    /// @brief Pointer to data to copy
    /// @note In callback, this is set the UDS buffer location in case you need to dynamically generate data instead of pointing to an existing buffer
    uint8_t* value_buf;

    /// @brief Length of data
    /// @note In callback, this is set the available UDS buffer size to use
    size_t value_len;
} UDS_22_RDBI_Response;

extern UDS_SERVICE_IMPLEMENTATION_t UDS_22_RDBI;

#ifdef __cplusplus
}
#endif