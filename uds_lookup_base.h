#pragma once

#include <stdint.h>
#include <stddef.h>

/**
 * @brief Base struct for UDS resources in tables
 * 
 */
typedef struct {
    /**
     * @brief Name for this resource
     * 
     */
    const char* name;

    /**
     * @brief User defined ID for this resource
     * 
     * In some cases (like UDS services), only the lower 8 bits are used
     */
    const uint16_t id;

    /**
     * @brief Security level required to access this resource
     *  0 = Always accessible
     */
    const uint8_t security_level;
} uds_resource_t;