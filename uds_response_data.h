#pragma once

#include <stdint.h>
#include <stddef.h>

/**
 * @brief UDS response data set by commands to be sent back in the response
 * 
 */
typedef struct {
    bool send_response;
    uint8_t service_id;
    uint8_t error_code;
} uds_response_data_t;

/*
    This struct is automatically populated by the session code
*/