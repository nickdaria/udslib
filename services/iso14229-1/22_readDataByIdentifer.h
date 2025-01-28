#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "../../udslib.h"
#include "../uds_service_framework.h"

#include <stdint.h>
#include <stdbool.h>

/*
    Read Data By Identifier (0x22)
        https://piembsystech.com/read-data-by-identifier-0x22-service-in-uds-protocol/

        [Accepts]
        - Data Identifier (DID) or list of DIDs

        [Response]
        - List of DIDs and data

        [Order of operations (ISO)]
        - Decode the request
        - Fulfill each ID
            - If the ID is not supported, simply omit from result
            - If the ID is not authorized, return NRC 0x33
            - If the ID condition check is not okay, return NRC 0x22
        - Encode the response
            - If no IDs were fulfilled, return NRC 0x31
            - If total response length is too long, return NRC 0x14
        - Send the response

        [NACK Response]
        - 0x13: Length of message is invalid or too many requests at once
        - 0x14: Response too long
        - 0x22: Conditions not correct
        - 0x31: Request out of range (DID not supported)
        - 0x33: Security access denied
*/

typedef struct {
    //  Identifier data array & data length array
    uint16_t* data_identifier;

    //  Count of elements
    size_t elements_count;

    //  Total size of allocated space
    size_t elements_size;
} UDS_22_RDBI_request;

typedef struct {
    //  Associated request
    UDS_22_RDBI_request request;

    //  Data
    uds_buf_t* data_identifier_value;
} UDS_22_RDBI_response;

extern UDS_SERVICE_IMPLEMENTATION_t UDS_22_RDBI;

#ifdef __cplusplus
}
#endif