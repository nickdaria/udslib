#include "uds_server.h"
#include "../protocol/uds_negative_response.h"
#include "../protocol/uds_services.h"
#include <string.h>  // for memset

static const UdsServiceHandlerEntry* find_handler_entry(const UdsSession* session, uint8_t service_id) {
    for (size_t i = 0; i < session->services_table_len; i++) {
        const UdsServiceHandlerEntry* entry = &session->services_table[i];
        if (entry && entry->implementation && entry->implementation->sid == service_id) {
            // Do not break for constant timing
            return entry;
        }
    }
    return NULL;
}

static size_t build_negative_response(UdsBuffer response, uint8_t original_sid, UDS_NRC_t code) {
    response.data[UDS_PROTOCOL_SERVICE_IDX] = UDS_SID_NEGATIVE_RESPONSE;
    response.data[UDS_PROTOCOL_NEGATIVE_RESPONSE_SID_IDX] = original_sid;
    response.data[UDS_PROTOCOL_NEGATIVE_RESPONSE_CODE_IDX] = code;
    return UDS_PROTOCOL_NEGATIVE_RESPONSE_CODE_IDX + 1;
}

static size_t build_positive_response(UdsBuffer response, uint8_t original_sid, size_t payload_len) {
    response.data[UDS_PROTOCOL_SERVICE_IDX] = original_sid + UDS_PROTOCOL_POS_ACK_OFFSET;
    return payload_len + 1;
}

void uds_server_init(UdsSession* session, const UdsServiceHandlerEntry* services_table, const size_t services_table_len) {
    session->security_level = UDS_PROTOCOL_DEFAULT_SESSION;
    session->services_table = services_table;
    session->services_table_len = services_table_len;
    session->usrParameter = NULL;
}

size_t uds_server_process_request(UdsSession* session, UdsBufferCollection buffers, void* usrParameter) {
    if (!session || !buffers.request.data || buffers.request.bufLen < 1) {
        return 0;
    }

    const uint8_t service_id = buffers.request.data[UDS_PROTOCOL_SERVICE_IDX];

    const UdsServiceHandlerEntry* handler_entry = find_handler_entry(session, service_id);
    if (!handler_entry || !handler_entry->implementation || !handler_entry->request) {
        return build_negative_response(buffers.response, service_id, UDS_NRC_SERVICE_NOT_SUPPORTED);
    }

    const UDS_SERVICE_IMPLEMENTATION_t* impl = handler_entry->implementation;

    if (!impl->serverDecodeRequest || !impl->serverEncodeResponse) {
        return build_negative_response(buffers.response, service_id, UDS_NRC_SERVICE_NOT_SUPPORTED);
    }

    // Create request/response structs dynamically on stack
    uint8_t requestStruct[impl->pRequestSize];
    uint8_t responseStruct[impl->pResponseSize];
    memset(requestStruct, 0, impl->pRequestSize);
    memset(responseStruct, 0, impl->pResponseSize);

    // Create service sub-buffers (SID already consumed)
    UdsBufferCollection service_buffers = {
        .request = uds_buf_offset(buffers.request, 1, NULL),
        .response = uds_buf_offset(buffers.response, 1, NULL)
    };

    // Decode
    UDS_NRC_t decode_result = impl->serverDecodeRequest(requestStruct, service_buffers.request);
    if (decode_result != UDS_NRC_PR) {
        return build_negative_response(buffers.response, service_id, decode_result);
    }

    //  Prepare Response (if available)
    if(impl->serverPrepareResponse) {
        impl->serverPrepareResponse(requestStruct, responseStruct, service_buffers.response);
    }

    // Handle
    UDS_NRC_t handler_result = handler_entry->request(session, requestStruct, responseStruct, usrParameter);
    if (handler_result != UDS_NRC_PR) {
        return build_negative_response(buffers.response, service_id, handler_result);
    }

    // Encode response
    size_t payload_len = impl->serverEncodeResponse(requestStruct, responseStruct, service_buffers.response);
    if (payload_len == 0) {
        return build_negative_response(buffers.response, service_id, UDS_NRC_GENERAL_PROGRAMMING_FAILURE);
    }

    // Return final response
    return build_positive_response(buffers.response, service_id, payload_len);
}
