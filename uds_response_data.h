#pragma once

#include <stdint.h>
#include <stddef.h>

/**
 * @brief UDS response data set by commands to be sent back in the response
 * 
 */
typedef struct {
    /**
     * @brief False to disable sending a response
     * 
     */
    bool send_response;

    /**
     * @brief Error code response (0 = OK, > 0 = NACK/7F)
     * 
     */
    uint8_t error_code;
} uds_response_data_t;

/*
    This struct is automatically populated by the session code
*/