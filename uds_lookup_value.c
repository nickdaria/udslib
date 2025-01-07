#include "uds_lookup_value.h"

uds_lookup_value_t uds_lookup_value_init_r(const uint16_t id, const char* name, const uint8_t security_level, const uint8_t* data_ptr, const size_t data_len) {
    uds_lookup_value_t entry = {
        .base = { id, name, security_level },
        .data_read_ptr = data_ptr,
        .data_write_ptr = NULL,
        .data_len = data_len
    };
    return entry;
}

uds_lookup_value_t uds_lookup_value_init_rw(const uint16_t id, const char* name, const uint8_t security_level, const uint8_t security_level_write, uint8_t* data_ptr, const size_t data_len) {
    uds_lookup_value_t entry = {
        .base = { id, name, security_level },
        .data_read_ptr = data_ptr,
        .data_write_ptr = data_ptr,
        .data_len = data_len
    };
    return entry;
}

uds_lookup_value_t uds_lookup_value_init_rw_distinct(const uint16_t id, const char* name, const uint8_t security_level, const uint8_t security_level_write, const uint8_t* data_read_ptr, uint8_t* data_write_ptr, const size_t data_len) {
    uds_lookup_value_t entry = {
        .base = { id, name, security_level },
        .data_read_ptr = data_read_ptr,
        .data_write_ptr = data_write_ptr,
        .data_len = data_len
    };
    return entry;
}