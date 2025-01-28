#include "uds_client.h"

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

    //  Execute request
    size_t svcRet = service->clientEncodeRequest(requestStruct, ret_buf);
    offset += svcRet;

    //  Check for error
    if(svcRet == 0) {
        return 0;
    }

    //  Return total size
    return offset;
}