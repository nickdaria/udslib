#include "2E_writeDataByIdentifier.h"

size_t x2E_WDBI_clientEncodeRequest(const void* pRequest, UdsBuffer ret_buf) {
    const UDS_2E_WDBI_Request* request = (const UDS_2E_WDBI_Request*)pRequest;
    
    if(pRequest == NULL || ret_buf.data == NULL) {
        return 0;
    }
    
    if(ret_buf.bufLen < 2 + request->data_record_len) {
        return 0;
    }
    
    size_t offset = 0;
    
    ret_buf.data[offset++] = (request->data_identifier >> 8) & 0xFF;
    ret_buf.data[offset++] = request->data_identifier & 0xFF;
    
    for(size_t i = 0; i < request->data_record_len; i++) {
        ret_buf.data[offset++] = request->data_record[i];
    }
    
    return offset;
}

bool x2E_WDBI_clientDecodeResponse(void* outResponse, const UdsBuffer buf) {
    UDS_2E_WDBI_Response* response = (UDS_2E_WDBI_Response*)outResponse;
    
    if(outResponse == NULL || buf.data == NULL || buf.bufLen < 2) {
        return false;
    }
    
    response->data_identifier = (buf.data[0] << 8) | buf.data[1];
    
    return true;
}

void x2E_WDBI_serverPrepareResponse(const void* pRequest, void* pResponse, UdsBuffer ret_buf) {
    const UDS_2E_WDBI_Request* request = (const UDS_2E_WDBI_Request*)pRequest;
    UDS_2E_WDBI_Response* response = (UDS_2E_WDBI_Response*)pResponse;
    
    if(!request || !response) {
        return;
    }
    
    response->data_identifier = request->data_identifier;
}

size_t x2E_WDBI_serverEncodeResponse(const void* pRequest, const void* pResponse, UdsBuffer ret_buf) {
    const UDS_2E_WDBI_Request* request = (const UDS_2E_WDBI_Request*)pRequest;
    const UDS_2E_WDBI_Response* response = (const UDS_2E_WDBI_Response*)pResponse;
    
    if (!request || !response || !ret_buf.data || ret_buf.bufLen < 2) {
        return 0;
    }
    
    size_t offset = 0;
    
    ret_buf.data[offset++] = (response->data_identifier >> 8) & 0xFF;
    ret_buf.data[offset++] = response->data_identifier & 0xFF;
    
    return offset;
}

UDS_NRC_t x2E_WDBI_serverDecodeRequest(void* outRequest, const UdsBuffer buf) {
    UDS_2E_WDBI_Request* request = (UDS_2E_WDBI_Request*)outRequest;
    
    if (!request || !buf.data || buf.bufLen < 3) {
        return UDS_NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT;
    }
    
    request->data_identifier = (buf.data[0] << 8) | buf.data[1];
    request->data_record = &buf.data[2];
    request->data_record_len = buf.bufLen - 2;
    
    return UDS_NRC_PR;
}

UDS_SERVICE_IMPLEMENTATION_t UDS_2E_WDBI = {
    .sid = UDS_SID_WDBI,
    .pRequestSize = sizeof(UDS_2E_WDBI_Request),
    .pResponseSize = sizeof(UDS_2E_WDBI_Response),
    .clientEncodeRequest = x2E_WDBI_clientEncodeRequest,
    .clientDecodeResponse = x2E_WDBI_clientDecodeResponse,
    .serverPrepareResponse = x2E_WDBI_serverPrepareResponse,
    .serverEncodeResponse = x2E_WDBI_serverEncodeResponse,
    .serverDecodeRequest = x2E_WDBI_serverDecodeRequest,
};