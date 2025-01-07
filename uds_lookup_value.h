#pragma once

#include <stdint.h>
#include <stddef.h>
#include "uds_lookup_base.h"

typedef struct {
    /**
     * @brief Byte length of data
     * 
     */
    const size_t data_len;

    /**
     * @brief Mask to apply to data
     * 
     */
    const uint8_t data_mask;

    /**
     * @brief Bit shift to apply to data
     * 
     */
    const int8_t data_shift;

    /**
     * @brief If true, the data will be inverted before being used
     * 
     */
    const bool data_invert_endianess;
} uds_value_lookup_number_t;

typedef struct {
    /**
     * @brief Base structure for the lookup entry with name, ID and security level
     * 
     */
    const uds_resource_t base;

    /**
     * @brief Pointer to read (NULL to disable)
     * 
     */
    const uint8_t* data_read_ptr;

    /**
     * @brief Pointer to write (NULL to disable)
     * 
     */
    uint8_t* data_write_ptr;

    /**
     * @brief Security level required to write to this value
     * 
     */
    uint8_t data_write_security_level;

    /**
     * @brief Configuration for how the value is read/written
     * 
     */
    const uds_value_lookup_number_t data_cfg;
} uds_value_lookup_t;
