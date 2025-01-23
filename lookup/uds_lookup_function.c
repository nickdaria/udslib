#include "uds_lookup_function.h"
#include "../protocol/uds_negative_response.h"

size_t function_run(const void* session, 
                    uds_response_data_t* uds_response, 
                    const uint16_t resource_id, 
                    const uint8_t security_level, 
                    const uint8_t* data, 
                    const size_t data_len, 
                    const uds_lookup_function_t* function_entry, 
                    uint8_t* response_data, 
                    const size_t response_len) 
{
    //  Function pointer not set
    if(function_entry == NULL || function_entry->function == NULL) {
        uds_response->error_code = UDS_NRC_SUBFUNCTION_NOT_SUPPORTED;
        return 0;
    }

    //  Security level not met
    if(security_level < function_entry->base.security_level) {
        uds_response->error_code = UDS_NRC_SUBFUNCTION_NOT_SUPPORTED_IN_ACTIVE_SESSION;
        return 0;
    }

    //  Security authorized, run function
    uds_function_context_t uds_context = {
        .resource = &function_entry->base,
        .security_level = security_level,
        .uds_session = (void*)session
    };

    //  Run function
    return function_entry->function(&uds_context, uds_response, data, data_len, response_data, response_len);
}

size_t uds_lookup_function(const void* session, 
                            uds_response_data_t* uds_response, 
                            const uint16_t resource_id, 
                            const uint8_t security_level, 
                            const uint8_t* data, 
                            const size_t data_len, 
                            const uds_lookup_function_t* table, 
                            const size_t table_len, 
                            uint8_t* response_data, 
                            const size_t response_len, 
                            bool* ret_found) 
{
    if(uds_response == NULL || table == NULL || response_data == NULL || response_len == 0) {
        return 0;
    }
    
    for(size_t i = 0; i < table_len; i++) {
        if(table[i].base.id == resource_id) {
            if(ret_found != NULL) { *ret_found = true; }
            return function_run(session, uds_response, resource_id, security_level, data, data_len, &table[i], response_data, response_len);
        }
    }

    //  No match
    if(ret_found != NULL) { *ret_found = false; }
    return 0;
}

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