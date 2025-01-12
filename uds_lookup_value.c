#include "uds_lookup_value.h"
#include "uds_protocol.h"
#include <string.h>

/*
    Read Handler
*/
size_t value_read(const void* session, 
                    uds_response_data_t* uds_response, 
                    const uint16_t resource_id, 
                    const uint8_t security_level, 
                    const uds_lookup_value_t* value_entry, 
                    uint8_t* response_data, 
                    const size_t response_len)
{
    //  Read pointer not set
    if(value_entry->data_read_ptr == NULL) {
        uds_response->error_code = UDS_NACK_SUBFUNCTION_NOT_SUPPORTED;
        return 0;
    }

    //  Read security level is 0 (disabled)
    if(value_entry->data_read_ptr == 0) {
        uds_response->error_code = UDS_NACK_SUBFUNCTION_NOT_SUPPORTED;
        return 0;
    }

    //  Security level not met
    if(security_level < value_entry->base.security_level) {
        uds_response->error_code = UDS_NACK_SECURITY_ACCESS_DENIED;
        return 0;
    }

    //  Copy data
    memcpy(response_data, value_entry->data_read_ptr, value_entry->data_len);

    //  Positive ack
    uds_response->error_code = UDS_NACK_OK;

    //  Done
    return value_entry->data_len;
}

size_t uds_lookup_value_read(const void* session, 
                                uds_response_data_t* uds_response, 
                                const uint16_t resource_id, 
                                const uint8_t security_level, 
                                const uds_lookup_value_t* table, 
                                const size_t table_len, 
                                uint8_t* response_data, 
                                const size_t response_len) 
{
    if(uds_response == NULL || table == NULL || response_data == NULL || response_len == 0) {
        return false;
    }

    for(size_t i = 0; i < table_len; i++) {
        if(table[i].base.id == resource_id) {
            return value_read(session, uds_response, resource_id, security_level, &table[i], response_data, response_len);
        }
    }

    uds_response->error_code = UDS_NACK_SUBFUNCTION_NOT_SUPPORTED;
    return 0;
}

size_t value_write(const void* session, 
                    uds_response_data_t* uds_response, 
                    const uint16_t resource_id, 
                    const uint8_t security_level, 
                    const uint8_t* data, 
                    const size_t data_len, 
                    const uds_lookup_value_t* value_entry, 
                    uint8_t* response_data, 
                    const size_t response_len) 
{
    //  Write pointer not set
    if(value_entry->data_write_ptr == NULL) {
        uds_response->error_code = UDS_NACK_SUBFUNCTION_NOT_SUPPORTED;
        return 0;
    }

    //  Write security level is 0 (disabled)
    if(value_entry->data_write_security_level == 0) {
        uds_response->error_code = UDS_NACK_SUBFUNCTION_NOT_SUPPORTED;
        return 0;
    }

    //  Security level not met
    if(security_level < value_entry->data_write_security_level) {
        uds_response->error_code = UDS_NACK_SUBFUNCTION_NOT_SUPPORTED_IN_ACTIVE_SESSION;
        return 0;
    }

    //  Length mismatch
    if(data_len != value_entry->data_len) {
        uds_response->error_code = UDS_NACK_INVALID_FORMAT;
        return 0;
    }

    //  Execute write
    memcpy(value_entry->data_write_ptr, data, data_len);

    //  Done
    uds_response->error_code = UDS_NACK_OK;

    return 0;
}

size_t uds_lookup_value_write(const void* session, 
                                uds_response_data_t* uds_response,
                                const uint16_t resource_id, 
                                const uint8_t security_level, 
                                const uint8_t* data, 
                                const size_t data_len, 
                                const uds_lookup_value_t* table, 
                                const size_t table_len, 
                                uint8_t* response_data, 
                                const size_t response_len) 
{
    if(uds_response == NULL || table == NULL || response_data == NULL || response_len == 0) {
        return false;
    }

    for(size_t i = 0; i < table_len; i++) {
        if(table[i].base.id == resource_id) {
            return value_write(session, uds_response, resource_id, security_level, data, data_len, &table[i], response_data, response_len);
        }
    }

    //  Not found
    uds_response->error_code = UDS_NACK_SUBFUNCTION_NOT_SUPPORTED;
    return 0;
}

/*
    Initializers
*/
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