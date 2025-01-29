#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

typedef union {
    //  The raw byte, as some manufacturers (Nissan) ignore the supression bit and use it anyways
    uint8_t raw;
    
    //  The proper implementation
    struct {
        uint8_t subfunction : 7;
        bool suppressPosRspMsgIndicationBit : 1;
    } protocol;
} UDS_SUBFUNC_LV_t;

#ifdef __cplusplus
}
#endif