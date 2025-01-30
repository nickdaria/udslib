#include "uds_client.h"
#include "../protocol/uds_protocol.h"

size_t uds_client_build_request(const UDS_SERVICE_IMPLEMENTATION_t* service, const void* requestStruct, uds_buf_t ret_buf) {
    //  Safety
    if(service == NULL || requestStruct == NULL || ret_buf.data == NULL || ret_buf.bufLen == 0) {
        return 0;
    }

    //  Safety
    if(service->clientEncodeRequest == NULL) {
        return 0;
    }

    //  Assemble request
    size_t offset = 0;

    //  Place SID
    ret_buf.data[offset++] = service->sid;

    //  Offset return buffer
    uds_buf_t serviceBuf = uds_buf_offset(ret_buf, offset, NULL);

    //  Execute request
    size_t svcRet = service->clientEncodeRequest(requestStruct, serviceBuf);
    offset += svcRet;

    //  Check for error
    if(svcRet == 0) {
        return 0;
    }

    //  Return total size
    return offset;
}

UDS_SID_t uds_client_response_get_sid(const uds_buf_t buf) 
{
    //  Safety
    if(buf.bufLen < 1) {
        return (UDS_SID_t)0xFF;
    }

    //  Extract byte
    uint8_t sid_byte = buf.data[0];

    //  Negative response
    if(sid_byte == UDS_SID_NR) {
        return UDS_SID_NR;
    }

    //  Positive response
    if(sid_byte >= UDS_PROTOCOL_POS_ACK_OFFSET) {
        return (UDS_SID_t)(sid_byte - UDS_PROTOCOL_POS_ACK_OFFSET);
    }

    //  Invalid
    return (UDS_SID_t)0xFF;
}

bool uds_client_response_decode(const UDS_SERVICE_IMPLEMENTATION_t* service, const uds_buf_t response_buf, void* response_struct) 
{
    //  Safety
    if(response_struct == NULL || response_buf.data == NULL) { return false; }

    //  SID
    UDS_SID_t sid = uds_client_response_get_sid(response_buf);

    //  Safety
    if(sid == (UDS_SID_t)0xFF) { return false; }

    //  Offset buffer for data-only service code
    bool offset_ok;
    uds_buf_t offset_response = uds_buf_offset(response_buf, 1, &offset_ok);
    if(!offset_ok) { return false; }

    //  Verify service method exists
    if(service->clientDecodeResponse == NULL) { return false; }

    //  Call service method
    return service->clientDecodeResponse(response_struct, response_buf);
}
