#include "uds_lookup_function.h"
#include "../protocol/uds_negative_response.h"

size_t function_run(const void* session, 
                    uds_response_data_t* uds_response, 
                    const uint16_t resource_id, 
                    const uint8_t security_level,
                    const uds_lookup_function_t* function_entry, 
                    uds_buffers_t buffers,
                    void* usrParameter) 
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
        .uds_session = (void*)session,
    };

    //  Run function
    return function_entry->function(&uds_context, uds_response, buffers, usrParameter);
}

size_t uds_lookup_function(const void* session, 
                            uds_response_data_t* uds_response, 
                            const uint16_t resource_id, 
                            const uint8_t security_level, 
                            const uds_lookup_function_t* table, 
                            const size_t table_len, 
                            uds_buffers_t buffers,
                            bool* ret_found,
                            void* usrParameter)
{
    if(uds_response == NULL || table == NULL || buffers.request.data == NULL || buffers.response.data == NULL) {
        return 0;
    }
    
    for(size_t i = 0; i < table_len; i++) {
        if(table[i].base.id == resource_id) {
            if(ret_found != NULL) { *ret_found = true; }
            return function_run(session, uds_response, resource_id, security_level, &table[i], buffers, usrParameter);
        }
    }

    //  No match
    if(ret_found != NULL) { *ret_found = false; }
    return 0;
}