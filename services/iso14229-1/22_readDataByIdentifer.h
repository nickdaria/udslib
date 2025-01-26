#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "../../udslib.h"

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
} UDS_22_RDBI_query;

typedef struct {
    uint8_t* data;
    size_t len;
} UDS_22_RDBI_responseValue;

typedef struct {
    //  Associated request
    UDS_22_RDBI_query query;

    //  Data
    UDS_22_RDBI_responseValue* data_identifier_value;
} UDS_22_RDBI_response;

size_t UDS_22_RDBI_server_encodePositiveResponse(const UDS_22_RDBI_query* query, const UDS_22_RDBI_response* response, uint8_t* buf, const size_t len);

UDS_NRC_t UDS_22_RDBI_server_decodeRequest(UDS_22_RDBI_query* query, const size_t query_buf_size, const uint8_t* buf, const size_t len);
size_t UDS_22_RDBI_client_encodeRequest(const UDS_22_RDBI_query* query, uint8_t* buf, const size_t buf_len);

#ifdef __cplusplus
}
#endif