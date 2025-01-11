#include "uds_lookup_function.h"
#include "uds_protocol.h"

uds_lookup_function_t uds_lookup_function_init(const uint16_t id, const char* name, const uint8_t security_level, const uds_function_cb callback) {
    return (uds_lookup_function_t) {
        .base = {
            .id = id,
            .name = name,
            .security_level = security_level
        },
        .function = callback
    };
}

bool uds_lookup_function(const void* session, uds_response_data_t* uds_response, const uint16_t resource_id, const uint8_t security_level, const uint8_t* data, const size_t data_len, const uds_lookup_function_t* table, const size_t table_len, uint8_t* response_data, const size_t response_len, size_t* response_ret_len) {
    if(uds_response == NULL || table == NULL || response_data == NULL || response_len == 0) {
        return false;
    }
    
    for(size_t i = 0; i < table_len; i++) {
        if(table[i].base.id == resource_id) {
            //  ID match
            if(security_level >= table[i].base.security_level) {
                //  Security authorized, run function
                uds_function_context_t uds_context = {
                    .resource = &table[i].base,
                    .security_level = security_level,
                    .uds_session = (void*)session
                };

                *response_ret_len = table[i].function(&uds_context, uds_response, data, data_len, response_data, response_len);

            }
            else {
                //  Security not authorized
                uds_response->error_code = UDS_NACK_SECURITY_ACCESS_DENIED;
            }

            //  Function found
            return true;
        }
    }

    //  No match
    return false;
}