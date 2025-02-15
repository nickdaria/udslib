#include "uds_server.h"
#include "../protocol/uds_negative_response.h"
#include "../protocol/uds_services.h"

void uds_server_init(uds_session_t* session, const uds_lookup_function_t* services_table, const size_t services_table_len) {
    session->security_level = UDS_PROTOCOL_DEFAULT_SESSION;
    session->services_table = (uds_lookup_function_t*)services_table;
    session->services_table_len = services_table_len;
    session->usrParameter = NULL;
}

/*
    Under the hood, service lookup is just the same as a function lookup, but has special handling for the service ID byte and NACK responses
*/
size_t uds_server_process_request(uds_session_t* session, uds_buffers_t buffers, void* usrParameter) {
    //  Build response
    uds_response_data_t uds_response = {
        .suppress_response = false,
        .error_code = UDS_NRC_SERVICE_NOT_SUPPORTED
    };

    //  Extract SID
    uint8_t service_id = buffers.request.data[UDS_PROTOCOL_SERVICE_IDX];

    //  Build child buffer struct with offset for response
    uds_buffers_t service_buffers = {
        .request = uds_buf_offset(buffers.request, 1, NULL),
        .response = uds_buf_offset(buffers.response, 1, NULL)
    };

    bool service_found = false;
    size_t service_response_len = uds_lookup_function(session,
                                                    &uds_response,
                                                    service_id,
                                                    session->security_level,
                                                    session->services_table,
                                                    session->services_table_len,
                                                    service_buffers,
                                                    &service_found,
                                                    usrParameter);

    //  Override NACK code
    if(!service_found) {
        //  Service not found
        uds_response.error_code = UDS_NRC_SERVICE_NOT_SUPPORTED;
    }

    //  Response not desired
    if(uds_response.suppress_response) {
        return 0;
    }

    //  Build response
    if(uds_response.error_code == UDS_NRC_PR) {
        buffers.response.data[UDS_PROTOCOL_SERVICE_IDX] = service_id + UDS_PROTOCOL_POS_ACK_OFFSET;
        return service_response_len + 1;
    }
    else {
        buffers.response.data[UDS_PROTOCOL_SERVICE_IDX] = UDS_SID_NEGATIVE_RESPONSE;
        buffers.response.data[UDS_PROTOCOL_NEGATIVE_RESPONSE_SID_IDX] = service_id;
        buffers.response.data[UDS_PROTOCOL_NEGATIVE_RESPONSE_CODE_IDX] = uds_response.error_code;
        return UDS_PROTOCOL_NEGATIVE_RESPONSE_CODE_IDX + 1;
    }
}