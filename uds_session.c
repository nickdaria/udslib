#include "uds_session.h"

void uds_session_init(uds_session_t* session, uds_lookup_function_t* services_table, size_t services_table_len) {
    session->security_level = UDS_PROTOCOL_DEFAULT_SESSION;
    session->services_table = services_table;
    session->services_table_len = services_table_len;
}

/*
    Under the hood, service lookup is just the same as a function lookup, but has special handling for the service ID byte and NACK responses
*/
size_t uds_session_process_request(uds_session_t* session, const uint8_t* request_buf, const size_t request_len, uint8_t* response_buf, const size_t response_buf_len) {
    //  Build response
    uds_response_data_t uds_response = {
        .send_response = true,
        .error_code = UDS_NACK_SERVICE_NOT_SUPPORTED
    };

    uint8_t service_id = request_buf[UDS_PROTOCOL_SERVICE_IDX];
    const uint8_t* data_without_header = request_buf + UDS_PROTOCOL_SERVICE_IDX + 1;
    size_t data_without_header_len = request_len - UDS_PROTOCOL_SERVICE_IDX - 1;

    //  Offset response to make room for service ID
    uint8_t* offset_response = response_buf + 1;
    size_t offset_response_len = response_buf_len - 1;

    bool service_found = false;
    size_t service_response_len = uds_lookup_function(session,
                                                    &uds_response,
                                                    service_id,
                                                    session->security_level,
                                                    data_without_header,
                                                    data_without_header_len,
                                                    session->services_table,
                                                    session->services_table_len,
                                                    offset_response,
                                                    offset_response_len,
                                                    &service_found);

    //  Override NACK code
    if(!service_found) {
        //  Service not found
        uds_response.error_code = UDS_NACK_SERVICE_NOT_SUPPORTED;
    }

    //  Build response
    if(uds_response.error_code == UDS_NACK_OK) {
        response_buf[UDS_PROTOCOL_SERVICE_IDX] = service_id + UDS_PROTOCOL_POS_ACK_OFFSET;
        return service_response_len + 1;
    }
    else {
        response_buf[UDS_PROTOCOL_SERVICE_IDX] = UDS_SERVICE_NEGATIVE_RESPONSE;
        response_buf[UDS_PROTOCOL_NEGATIVE_RESPONSE_SID_IDX] = service_id;
        response_buf[UDS_PROTOCOL_NEGATIVE_RESPONSE_CODE_IDX] = uds_response.error_code;
        return UDS_PROTOCOL_NEGATIVE_RESPONSE_CODE_IDX + 1;
    }
}