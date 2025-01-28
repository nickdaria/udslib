#include <string.h>

#include "uds_lookup_value.h"
#include "../protocol/uds_negative_response.h"

/*
    Read Handler
*/
size_t value_read(const void* session, 
                    uds_response_data_t* uds_response, 
                    const uint16_t resource_id, 
                    const uint8_t security_level, 
                    const uds_lookup_value_t* value_entry, 
                    uds_buf_t response_data)
{
    //  Read pointer not set
    if(value_entry->buf.data == NULL) {
        uds_response->error_code = UDS_NRC_SUBFUNCTION_NOT_SUPPORTED;
        return 0;
    }

    //  Read security level is 0 (disabled)
    if(value_entry->base.security_level == 0) {
        uds_response->error_code = UDS_NRC_SUBFUNCTION_NOT_SUPPORTED;
        return 0;
    }

    //  Security level not met
    if(security_level < value_entry->base.security_level) {
        uds_response->error_code = UDS_NRC_SECURITY_ACCESS_DENIED;
        return 0;
    }

    //  Not enough room
    if(response_data.bufLen < value_entry->buf.bufLen) {
        uds_response->error_code = UDS_NRC_RESPONSE_TOO_LONG;
        return 0;
    }

    //  Positive ack
    uds_response->error_code = UDS_NRC_PR;

    //  Copy data
    return uds_big_endian_copy(response_data.data, value_entry->buf, value_entry->numericType);
}

size_t uds_lookup_value_read(const void* session, 
                                uds_response_data_t* uds_response, 
                                uds_buf_t response_data,
                                const uint16_t resource_id, 
                                const uint8_t security_level, 
                                const uds_lookup_value_t* table, 
                                const size_t table_len) 
{
    if(uds_response == NULL || table == NULL || response_data.data == NULL) {
        return false;
    }

    for(size_t i = 0; i < table_len; i++) {
        if(table[i].base.id == resource_id) {
            return value_read(session, uds_response, resource_id, security_level, &table[i], response_data);
        }
    }

    uds_response->error_code = UDS_NRC_SUBFUNCTION_NOT_SUPPORTED;
    return 0;
}

size_t value_write(const void* session, 
                    uds_response_data_t* uds_response, 
                    uds_buf_t response_data,
                    const uint16_t resource_id, 
                    const uint8_t security_level, 
                    const uint8_t* data, 
                    const size_t data_len, 
                    const uds_lookup_value_t* value_entry) 
{
    //  Write pointer not set
    if(value_entry->data_write_ptr == NULL) {
        uds_response->error_code = UDS_NRC_SUBFUNCTION_NOT_SUPPORTED;
        return 0;
    }

    //  Write security level is 0 (disabled)
    if(value_entry->data_write_security_level == 0) {
        uds_response->error_code = UDS_NRC_SUBFUNCTION_NOT_SUPPORTED;
        return 0;
    }

    //  Security level not met
    if(security_level < value_entry->data_write_security_level) {
        uds_response->error_code = UDS_NRC_SUBFUNCTION_NOT_SUPPORTED_IN_ACTIVE_SESSION;
        return 0;
    }

    //  Length mismatch
    if(data_len != value_entry->buf.bufLen) {
        uds_response->error_code = UDS_NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT;
        return 0;
    }

    //  Execute write
    memcpy(value_entry->data_write_ptr, data, value_entry->buf.bufLen);

    //  Done
    uds_response->error_code = UDS_NRC_PR;

    return 0;
}

size_t uds_lookup_value_write(const void* session, 
                                uds_response_data_t* uds_response,
                                uds_buf_t response_data,
                                const uint16_t resource_id, 
                                const uint8_t security_level, 
                                const uint8_t* data, 
                                const size_t data_len, 
                                const uds_lookup_value_t* table, 
                                const size_t table_len) 
{
    if(uds_response == NULL || table == NULL || response_data.data == NULL) {
        return false;
    }

    for(size_t i = 0; i < table_len; i++) {
        if(table[i].base.id == resource_id) {
            return value_write(session, uds_response, response_data, resource_id, security_level, data, data_len, &table[i]);
        }
    }

    //  Not found
    uds_response->error_code = UDS_NRC_SUBFUNCTION_NOT_SUPPORTED;
    return 0;
}