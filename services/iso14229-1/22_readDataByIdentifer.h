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
    size_t* data_identifier_len;

    //  Count of elements
    size_t elements_count;
} uds_22_rdbi_query;

typedef struct {
    //  Associated request
    uds_22_rdbi_query query;

    //  Data
    void* data_identifier_value;
    size_t* data_identifier_value_len;
} uds_22_rdbi_response;

//  Encoding outgoing response
size_t uds_22_rdbi_encode_response(const uds_22_rdbi_query* query, const uds_22_rdbi_response* response, void* buf);

//  Decoding incoming response
UDS_NRC_t uds_22_rdbi_decode_response(uds_22_rdbi_response* response, const void* buf, const size_t len);

//  Encoding outgoing request
size_t uds_22_rdbi_encode_query(const uds_22_rdbi_query* query, void* buf);

//  Decoding incoming request
UDS_NRC_t uds_22_rdbi_decode_query(uds_22_rdbi_query* query, const void* buf, const size_t len);

#ifdef __cplusplus
}
#endif