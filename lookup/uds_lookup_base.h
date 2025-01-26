#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

/**
 * @brief Base struct for UDS resources in tables
 * 
 */
typedef struct {
    /**
     * @brief User defined ID for this resource
     * 
     * In some cases (like UDS services), only the lower 8 bits are used
     */
    const uint16_t id;

    /**
     * @brief Name for this resource
     * 
     */
    const char* name;

    /**
     * @brief Security level required to access this resource
     *  0 = Disabled/Inaccessible
     *  1 = Default session
     */
    const uint8_t security_level;
} uds_resource_t;

typedef struct {
    uint8_t* data;
    const size_t len;
} uds_buf_t;

/**
 * @brief Common struct for setting up query and response buffers and passing them through the UDS stack
 * 
 */
typedef struct {
    const uds_buf_t* request;
    uds_buf_t* response;
} uds_buffers_t;

#ifdef __cplusplus
}
#endif