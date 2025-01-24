#include "uds_subfunction.h"
#include "uds_protocol.h"

UDS_SUBFUNC_LV_t uds_subfunc_decode(uint8_t subfunc_byte) {
    UDS_SUBFUNC_LV_t subfunc = {
        .subfunction = subfunc_byte & UDS_PROTOCOL_SUBFUNCTION_MASK,
        .suppressPosRspMsgIndicationBit = (subfunc_byte & UDS_PROTOCOL_SUBFUNCTION_SUPPRESS_POSITIVE_RESPONSE_MASK) != 0
    };

    return subfunc;
}

uint8_t uds_subfunc_encode(const UDS_SUBFUNC_LV_t subfunc) {
    uint8_t subfunc_byte = 0;

    // Set the subfunction bits
    subfunc_byte |= (subfunc.subfunction & UDS_PROTOCOL_SUBFUNCTION_MASK);

    // Set the suppress positive response indication bit if required
    if (subfunc.suppressPosRspMsgIndicationBit) {
        subfunc_byte |= UDS_PROTOCOL_SUBFUNCTION_SUPPRESS_POSITIVE_RESPONSE_MASK;
    }

    return subfunc_byte;
}