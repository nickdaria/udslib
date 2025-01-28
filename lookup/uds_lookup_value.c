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
        uds_response->error_code = UDS_NRC_ROOR;
        return 0;
    }

    //  Read security level is 0 (disabled)
    if(value_entry->base.security_level == 0) {
        uds_response->error_code = UDS_NRC_ROOR;
        return 0;
    }

    //  Security level not met
    if(security_level < value_entry->base.security_level) {
        uds_response->error_code = UDS_NRC_SAD;
        return 0;
    }

    //  Not enough room
    if(response_data.bufLen < value_entry->buf.bufLen) {
        uds_response->error_code = UDS_NRC_RTL;
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
                    const uds_buf_t data_to_write,
                    const uds_lookup_value_t* value_entry) 
{
    //  Write pointer not set
    if(value_entry->data_write_ptr == NULL) {
        uds_response->error_code = UDS_NRC_ROOR;
        return 0;
    }

    //  Write security level is 0 (disabled)
    if(value_entry->data_write_security_level == 0) {
        uds_response->error_code = UDS_NRC_ROOR;
        return 0;
    }

    //  Security level not met
    if(security_level < value_entry->data_write_security_level) {
        uds_response->error_code = UDS_NRC_SAD;
        return 0;
    }

    //  Length mismatch
    if(data_to_write.bufLen != value_entry->buf.bufLen) {
        uds_response->error_code = UDS_NRC_IMLOIF;
        return 0;
    }

    //  Execute write
    uds_big_endian_copy(value_entry->data_write_ptr, data_to_write, value_entry->numericType);

    //  Done
    uds_response->error_code = UDS_NRC_PR;

    return 0;
}

size_t uds_lookup_value_write(const void* session, 
                                uds_response_data_t* uds_response,
                                uds_buf_t response_data,
                                const uint16_t resource_id, 
                                const uint8_t security_level, 
                                const uds_buf_t request_data,
                                const uds_lookup_value_t* table, 
                                const size_t table_len) 
{
    if(uds_response == NULL || table == NULL || response_data.data == NULL) {
        return false;
    }

    for(size_t i = 0; i < table_len; i++) {
        if(table[i].base.id == resource_id) {
            return value_write(session, uds_response, response_data, resource_id, security_level, request_data, &table[i]);
        }
    }

    //  Not found
    uds_response->error_code = UDS_NRC_SUBFUNCTION_NOT_SUPPORTED;
    return 0;
}