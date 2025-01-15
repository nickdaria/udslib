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

//  Indexes
#define UDS_PROTOCOL_22_DID_IDX_MSB 1
#define UDS_PROTOCOL_22_DID_IDX_LSB 2
#define UDS_PROTOCOL_22_DATA_IDX 3

//  Wrapper struct
typedef struct {
    //  Identifiers in request
    uint16_t* dataIdentifier;
    size_t dataIdentifier_len;

    //  Data to send
    void* value;

    //  Individual lengths of data elements
    size_t* value_len;
} uds_protocol_22_readDataByIdentifier_t;

//  Extract Function
bool uds_protocol_22_readDataByIdentifier_decode(uds_protocol_22_readDataByIdentifier_t* ret, const uint8_t* buf, const size_t buf_len);

//  Encode Function
bool uds_protocol_22_readDataByIdentifier_encode(uds_protocol_22_readDataByIdentifier_t* in, uint8_t* buf, size_t buf_len);

#ifdef __cplusplus
}
#endif