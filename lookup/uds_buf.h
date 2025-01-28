#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/**
 * @brief Common struct for a data buffer with length
 * 
 */
typedef struct {
    uint8_t* data;
    const size_t buf_len;
} uds_buf_t;


/**
 * @brief Common struct for setting up request and response buffers and passing them through the UDS stack
 * 
 */
typedef struct {
    const uds_buf_t request;
    uds_buf_t response;
} uds_buffers_t;

/**
 * @brief Return a buffer with an offset location and shortened size
 * 
 * @param source Source buffer
 * @param offset Size of offset
 * @param success false if buffer ran out of space
 * @return uds_buf_t New buffer
 */
uds_buf_t uds_buf_offset(const uds_buf_t source, const size_t offset, bool* success);

#ifdef __cplusplus
}
#endif