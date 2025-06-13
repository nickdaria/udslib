#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "uds_lookup_base.h"
#include "uds_response_data.h"
#include "uds_buf.h"

/**
 * @brief Struct passed into functions to provide execution context
 * 
 */
typedef struct {
    /**
     * @brief Pointer to the resource information for the current function
     * 
     */
    const uds_resource_t* resource;

    /**
     * @brief Security level when message handling was started
     * 
     */
    const uint8_t security_level;

    /**
     * @brief Pointer to UdsServer for the current session
     * 
     */
    void* uds_session;
} uds_function_context_t;

/**
 * @brief Function signature for callbacks run by function lookup
 * 
 */
typedef size_t(*uds_function_cb)(
    const uds_function_context_t* context,
    uds_response_data_t* uds_response,
    UdsBufferCollection buffers,
    void* usrParameter
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

    //  TODO: Peek & error callbacks
} uds_lookup_function_t;

/**
 * @brief Lookup a function and execute it with context if security access allows, otherwise return NACK security access denied
 */
size_t uds_lookup_function(const void* session, 
                            uds_response_data_t* uds_response, 
                            const uint16_t resource_id, 
                            const uint8_t security_level, 
                            const uds_lookup_function_t* table, 
                            const size_t table_len, 
                            UdsBufferCollection buffers,
                            bool* ret_found,
                            void* usrParameter);

#ifdef __cplusplus
}
#endif