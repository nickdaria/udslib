#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

#include "../protocol/uds_protocol.h"
#include "../lookup/uds_lookup_function.h"

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
    uds_lookup_function_t* services_table;

    /**
     * @brief Number of entries in the service table
     * 
     */
    size_t services_table_len;
} uds_session_t;

/**
 * @brief Helper function to initialize a UDS session. You can also just populate the struct manually.
 * 
 * @param session 
 * @param services_table 
 * @param services_table_len 
 */
void uds_session_init(uds_session_t* session, uds_lookup_function_t* services_table, size_t services_table_len);

/**
 * @brief Recieves a full request buffer, processes it, and returns a response buffer
 */
size_t uds_session_process_request(uds_session_t* session, uds_buffers_t* buffers);

#ifdef __cplusplus
}
#endif