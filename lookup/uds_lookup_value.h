#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "uds_lookup_base.h"
#include "uds_response_data.h"

typedef struct {
    /**
     * @brief Base structure for the lookup entry with name, ID and security level
     * 
     */
    uds_resource_t base;

    /**
     * @brief Pointer to read (NULL to disable)
     * 
     */
    const void* data_read_ptr;

    /**
     * @brief Pointer to write (NULL to disable)
     * 
     */
    void* data_write_ptr;

    /**
     * @brief Security level required to write to this value
     * 
     */
    uint8_t data_write_security_level;

    /**
     * @brief Byte length of data
     * 
     */
    const size_t data_len;
} uds_lookup_value_t;

//  TODO: Docs
size_t uds_lookup_value_read(const void* session, uds_response_data_t* uds_response, const uint16_t resource_id, const uint8_t security_level, const uds_lookup_value_t* table, const size_t table_len, uint8_t* response_data, const size_t response_len);

//  TODO: Docs
size_t uds_lookup_value_write(const void* session, uds_response_data_t* uds_response, const uint16_t resource_id, const uint8_t security_level, const uint8_t* data, const size_t data_len, const uds_lookup_value_t* table, const size_t table_len, uint8_t* response_data, const size_t response_len);

// /**
//  * @brief Read only value lookup entry
//  * 
//  * @param id ID of value
//  * @param name Name of value (or NULL)
//  * @param security_level Security level required to read this value
//  * @param data_ptr Pointer to data to read
//  * @param data_len Length of data (typically just sizeof(DATA))
//  */
// uds_lookup_value_t uds_lookup_value_init_r(const uint16_t id, const char* name, const uint8_t security_level, const uint8_t* data_ptr, const size_t data_len);

// /**
//  * @brief Read/write value lookup entry that can read or write to the same pointer
//  * 
//  * @param id ID of value
//  * @param name Name of value (or NULL)
//  * @param security_level Security level required to read this value
//  * @param security_level_write Security level required to write this value
//  * @param data_ptr Pointer to data to R/W
//  * @param data_len Length of data - typically just sizeof(xxxxxxx)
//  */
// uds_lookup_value_t uds_lookup_value_init_rw(const uint16_t id, const char* name, const uint8_t security_level, const uint8_t security_level_write, uint8_t* data_ptr, const size_t data_len);

// /**
//  * @brief Read/write (w/ distinct pointers) value lookup entry. Useful for reading live data and writing to a mailbox or read-buffer.
//  * 
//  * @param id ID of value
//  * @param name Name of value (or NULL)
//  * @param security_level Security level required to read this value
//  * @param security_level_write Security level required to write this value
//  * @param data_read_ptr Pointer to read data from
//  * @param data_write_ptr Pointer to write data to (typically a queue/mailbox or read buffer)
//  * @param data_len Length of data - typically just sizeof(xxxxxxx)
//  */
// uds_lookup_value_t uds_lookup_value_init_rw_distinct(const uint16_t id, const char* name, const uint8_t security_level, const uint8_t security_level_write, const uint8_t* data_read_ptr, uint8_t* data_write_ptr, const size_t data_len);

#ifdef __cplusplus
}
#endif