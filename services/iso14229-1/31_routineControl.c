#include "31_routineControl.h"

size_t x31_RC_clientEncodeRequest(const void* pRequest, UdsBuffer ret_buf) {
    const UDS_31_RC_Request* request = (const UDS_31_RC_Request*)pRequest;

    if (!request || !ret_buf.data || ret_buf.bufLen < 3) {
        return 0;
    }

    size_t len = 0;
    ret_buf.data[len++] = request->routineControlType.raw;
    ret_buf.data[len++] = (request->routineIdentifier >> 8) & 0xFF;
    ret_buf.data[len++] = request->routineIdentifier & 0xFF;

    if (request->routineControlOptionBuf && request->routineControlOptionBufLen > 0 &&
        (len + request->routineControlOptionBufLen <= ret_buf.bufLen)) {
        memcpy(&ret_buf.data[len], request->routineControlOptionBuf, request->routineControlOptionBufLen);
        len += request->routineControlOptionBufLen;
    }

    return len;
}

bool x31_RC_clientDecodeResponse(void* outResponse, const UdsBuffer buf) {
    UDS_31_RC_Response* response = (UDS_31_RC_Response*)outResponse;

    if (!response || !buf.data || buf.bufLen < 4) {
        return false;
    }

    size_t offset = 0;
    response->routineControlType.raw = buf.data[offset++];
    response->routineIdentifier = ((uint16_t)buf.data[offset] << 8) | buf.data[offset + 1];
    offset += 2;
    response->routineInfo = buf.data[offset++];

    response->routineStatusRecordBuf = (uint8_t*)&buf.data[offset];
    response->routineStatusRecordBufLen = buf.bufLen - offset;

    return true;
}

UDS_NRC_t x31_RC_serverDecodeRequest(void* outRequest, const UdsBuffer buf) {
    UDS_31_RC_Request* request = (UDS_31_RC_Request*)outRequest;

    if (!request || !buf.data) {
        return UDS_NRC_GENERAL_PROGRAMMING_FAILURE;
    }

	if(buf.bufLen < 3) {
		return UDS_NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT;
	}

    size_t offset = 0;
    request->routineControlType.raw = buf.data[offset++];
    request->routineIdentifier = ((uint16_t)buf.data[offset] << 8) | buf.data[offset + 1];
    offset += 2;

    request->routineControlOptionBuf = (uint8_t*)&buf.data[offset];
    request->routineControlOptionBufLen = buf.bufLen - offset;

    return UDS_NRC_PR;
}

void x31_RC_serverPrepareResponse(const void* pRequest, void* pResponse, UdsBuffer ret_buf) {
    const UDS_31_RC_Request* request = (const UDS_31_RC_Request*)pRequest;
    UDS_31_RC_Response* response = (UDS_31_RC_Response*)pResponse;

    if (!request || !response) return;

    response->routineControlType = request->routineControlType;
    response->routineIdentifier = request->routineIdentifier;
    response->routineInfo = 0x00;  // default or app-specific value
    response->routineStatusRecordBuf = NULL;
    response->routineStatusRecordBufLen = 0;
}

size_t x31_RC_serverEncodeResponse(const void* pRequest, const void* pResponse, UdsBuffer ret_buf) {
    const UDS_31_RC_Response* response = (const UDS_31_RC_Response*)pResponse;
    const UDS_31_RC_Request* request = (const UDS_31_RC_Request*)pRequest;

    if (!response || !ret_buf.data || ret_buf.bufLen < 4) {
        return 0;
    }

    size_t len = 0;
    ret_buf.data[len++] = response->routineControlType.raw;
    ret_buf.data[len++] = (response->routineIdentifier >> 8) & 0xFF;
    ret_buf.data[len++] = response->routineIdentifier & 0xFF;
    ret_buf.data[len++] = response->routineInfo;

    if (response->routineStatusRecordBuf && response->routineStatusRecordBufLen > 0 &&
        len + response->routineStatusRecordBufLen <= ret_buf.bufLen) {
        memcpy(&ret_buf.data[len], response->routineStatusRecordBuf, response->routineStatusRecordBufLen);
        len += response->routineStatusRecordBufLen;
    }

    if (request->routineControlType.protocol.suppressPosRspMsgIndicationBit) {
        return 0;
    }

    return len;
}

UDS_SERVICE_IMPLEMENTATION_t UDS_31_RC = {
    .sid = UDS_SID_RC,
    .pRequestSize = sizeof(UDS_31_RC_Request),
    .pResponseSize = sizeof(UDS_31_RC_Response),
    .clientDecodeResponse = x31_RC_clientDecodeResponse,
    .clientEncodeRequest = x31_RC_clientEncodeRequest,
    .serverPrepareResponse = x31_RC_serverPrepareResponse,
    .serverEncodeResponse = x31_RC_serverEncodeResponse,
    .serverDecodeRequest = x31_RC_serverDecodeRequest
};
