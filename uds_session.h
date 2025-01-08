#pragma once

#include <stdint.h>
#include <stddef.h>

#include "uds_protocol.h"
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
 * 
 * @param session 
 * @param request_buf 
 * @param request_len 
 * @param response_buf 
 * @param response_buf_len 
 * @return size_t 
 */
size_t uds_session_process_request(uds_session_t* session, const uint8_t* request_buf, const size_t request_len, uint8_t* response_buf, const size_t response_buf_len);