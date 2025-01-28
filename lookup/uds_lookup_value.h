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

typedef struct {
    /**
     * @brief Base structure for the lookup entry with name, ID and security level
     * 
     */
    uds_resource_t base;

    /**
     * @brief Data read location & byte size
     * 
     */
    const uds_buf_t buf;
    
    /**
     * @brief Used to reverse byte order on little endian systems
     * 
     */
    const bool numericType;

    
    /**
     * @brief Pointer to write (NULL to disable, or buf.data to write to same location as read)
     * 
     */
    void* data_write_ptr;

    /**
     * @brief Security level required to write to this value
     * 
     */
    uint8_t data_write_security_level;
} uds_lookup_value_t;

//  TODO: Docs
size_t uds_lookup_value_read(const void* session, uds_response_data_t* uds_response, uds_buf_t response_data, const uint16_t resource_id, const uint8_t security_level, const uds_lookup_value_t* table, const size_t table_len);

//  TODO: Docs
size_t uds_lookup_value_write(const void* session, uds_response_data_t* uds_response, uds_buf_t response_data, const uint16_t resource_id, const uint8_t security_level, const uint8_t* data, const size_t data_len, const uds_lookup_value_t* table, const size_t table_len);

#ifdef __cplusplus
}
#endif