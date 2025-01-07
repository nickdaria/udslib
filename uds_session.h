#pragma once

#include <stdint.h>
#include <stddef.h>

#include "uds_lookup_function.h"

typedef struct {
    /**
     * @brief Active session security level
     * 
     */
    uint8_t security_level;

    /**
     * @brief Pointer to array of services to look up
     * 
     */
    uds_function_lookup_t* services_table;

    /**
     * @brief Number of entries in the service table
     * 
     */
    size_t services_table_len;
} uds_session_t;