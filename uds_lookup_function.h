#pragma once

#include <stdint.h>
#include <stddef.h>

#include "uds_lookup_base.h"
#include "uds_response_data.h"

/**
 * @brief Struct passed into functions to provide execution context
 * 
 */
typedef struct {
    /**
     * @brief Pointer to the resource information for the current function
     * 
     */
    uds_resource_t* resource_id;

    /**
     * @brief Pointer to uds_session_t for the current session
     * 
     */
    void* uds_session_t;
} uds_function_context_t;

/**
 * @brief Function signature for callbacks run by function lookup
 * 
 */
typedef void(*uds_function_cb)(
    uds_function_context_t* context,
    uds_response_data_t* uds_response,
    uint8_t* response_data,
    size_t* response_len,
    const size_t response_len_max
);

/**
 * @brief Instance of a function lookup entry
 * 
 */
typedef struct {
    /**
     * @brief Base structure for the resource entry with name, ID and security level
     * 
     */
    const uds_resource_t base;

    /**
     * @brief Callback function to run when this function is called
     * 
     */
    const uds_function_cb function;
} uds_function_lookup_t;