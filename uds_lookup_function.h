#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

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
    const uds_resource_t* resource;

    /**
     * @brief Security level when message handling was started
     * 
     */
    const uint8_t security_level;

    /**
     * @brief Pointer to uds_session_t for the current session
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
    const uint8_t* data,
    const size_t data_len,
    uint8_t* response_data,
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

    //  TODO: Peek & error callbacks
} uds_lookup_function_t;

/**
 * @brief Lookup a function and execute it with context if security access allows, otherwise return NACK security access denied
 * 
 * @param session Session to pass into functions
 * @param uds_response Response struct used to place UDS repsonse metadata
 * @param resource_id ID of the target resource
 * @param security_level Granted security level of the session
 * @param data Data buffer from the request
 * @param data_len Length of the data buffer
 * @param table Pointer to uds_lookup_function_t table
 * @param table_len Length of the uds_lookup_function_t table
 * @param response_data Buffer to place response data
 * @param response_len Total length of response data buffer
 * @param ret_found Returns true if function was found in table
 * @return size_t Length of response data placed in response_data buffer
 */
size_t uds_lookup_function(const void* session, 
                            uds_response_data_t* uds_response, 
                            const uint16_t resource_id, 
                            const uint8_t security_level, 
                            const uint8_t* data, 
                            const size_t data_len, 
                            const uds_lookup_function_t* table, 
                            const size_t table_len, 
                            uint8_t* response_data, 
                            const size_t response_len, 
                            bool* ret_found);


/**
 * @brief Initialize a function/service lookup entry
 * 
 * @param id ID of function/service
 * @param name Name (or NULL)
 * @param security_level Security level required to access this service
 * @param callback Callback function to run when this service is called
 * @return uds_lookup_function_t Output structure
 */
uds_lookup_function_t uds_lookup_function_init(const uint16_t id, const char* name, const uint8_t security_level, const uds_function_cb callback);

#ifdef __cplusplus
}
#endif