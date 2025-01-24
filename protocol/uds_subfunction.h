#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t subfunction;
    bool suppressPosRspMsgIndicationBit;
} UDS_SUBFUNC_LV_t;

/**
 * @brief Extract subfunction and suppressPosRspMsgIndicationBit from subfunction byte
 * 
 * @param subfunc_byte Raw byte from UDS request
 * @return UDS_SUBFUNC_LV_t Subfunction and suppressPosRspMsgIndicationBit extracted from subfunc_byte
 */
UDS_SUBFUNC_LV_t uds_subfunc_decode(uint8_t subfunc_byte);

/**
 * @brief Encode subfunction and suppressPosRspMsgIndicationBit into a single byte
 * 
 * @param subfunc Struct containing service and suppressPosRspMsgIndicationBit
 * @return uint8_t Raw byte to send on bus
 */
uint8_t uds_subfunc_encode(const UDS_SUBFUNC_LV_t subfunc);

#ifdef __cplusplus
}
#endif