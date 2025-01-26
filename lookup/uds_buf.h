#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

/**
 * @brief Common struct for a data buffer with length
 * 
 */
typedef struct {
    uint8_t* data;
    const size_t len;
} uds_buf_t;

/**
 * @brief Common struct for setting up query and response buffers and passing them through the UDS stack
 * 
 */
typedef struct {
    const uds_buf_t request;
    uds_buf_t response;
} uds_buffers_t;

#ifdef __cplusplus
}
#endif