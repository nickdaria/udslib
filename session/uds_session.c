#include "uds_session.h"
#include "../protocol/uds_negative_response.h"
#include "../protocol/uds_services.h"

void uds_session_init(uds_session_t* session, uds_lookup_function_t* services_table, size_t services_table_len) {
    session->security_level = UDS_PROTOCOL_DEFAULT_SESSION;
    session->services_table = services_table;
    session->services_table_len = services_table_len;
}

/*
    Under the hood, service lookup is just the same as a function lookup, but has special handling for the service ID byte and NACK responses
*/
size_t uds_session_process_request(uds_session_t* session, uds_buffers_t* buffers) {
    //  Build response
    uds_response_data_t uds_response = {
        .send_response = true,
        .error_code = UDS_NRC_SERVICE_NOT_SUPPORTED
    };

    //  Extract SID
    uint8_t service_id = ((const uint8_t*)buffers->request_data)[UDS_PROTOCOL_SERVICE_IDX];

    //  Build child buffer struct with offset for response
    uds_buffers_t service_buffers = {
        .request_data = buffers->request_data + UDS_PROTOCOL_SERVICE_IDX + 1,
        .request_len = buffers->request_len - UDS_PROTOCOL_SERVICE_IDX - 1,
        .response_data = buffers->response_data + 1,
        .response_buf_len = buffers->response_buf_len - 1
    };

    bool service_found = false;
    size_t service_response_len = uds_lookup_function(session,
                                                    &uds_response,
                                                    service_id,
                                                    session->security_level,
                                                    session->services_table,
                                                    session->services_table_len,
                                                    &service_buffers,
                                                    &service_found);

    //  Override NACK code
    if(!service_found) {
        //  Service not found
        uds_response.error_code = UDS_NRC_SERVICE_NOT_SUPPORTED;
    }

    //  Build response
    if(uds_response.error_code == UDS_NRC_PR) {
        buffers->response_data[UDS_PROTOCOL_SERVICE_IDX] = service_id + UDS_PROTOCOL_POS_ACK_OFFSET;
        return service_response_len + 1;
    }
    else {
        buffers->response_data[UDS_PROTOCOL_SERVICE_IDX] = UDS_SID_NEGATIVE_RESPONSE;
        buffers->response_data[UDS_PROTOCOL_NEGATIVE_RESPONSE_SID_IDX] = service_id;
        buffers->response_data[UDS_PROTOCOL_NEGATIVE_RESPONSE_CODE_IDX] = uds_response.error_code;
        return UDS_PROTOCOL_NEGATIVE_RESPONSE_CODE_IDX + 1;
    }
}