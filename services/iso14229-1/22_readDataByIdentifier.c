#include "22_readDataByIdentifer.h"

size_t x22_RDBI_serverEncodeResponse(const void* response, uds_buf_t* ret_buf) {
    const UDS_22_RDBI_response* rResponse = (const UDS_22_RDBI_response*)response;

    //  Safety
    if(rResponse == NULL || rResponse->query.data_identifier == NULL || rResponse->data_identifier_value == NULL || ret_buf == NULL || ret_buf->data == NULL) {
        return 0;
    }

    //  Calculate required size
    size_t did_size = rResponse->query.elements_count * 2;
    size_t did_value_size = 0;
    for(size_t i = 0; i < rResponse->query.elements_count; i++) {
        did_value_size += rResponse->data_identifier_value[i].buf_len;
    }

    //  Sufficient buffer length check
    if (did_size + did_value_size > ret_buf->buf_len) {
        return 0;
    }

    size_t offset = 0;

    for(size_t i = 0; i < rResponse->query.elements_count; i++) {
        //  MSB
        ret_buf->data[offset++] = (rResponse->query.data_identifier[i] >> 8) & 0xFF;

        //  LSB
        ret_buf->data[offset++] = rResponse->query.data_identifier[i] & 0xFF;

        //  Copy data
        for(size_t j = 0; j < rResponse->data_identifier_value[i].buf_len; j++) {
            ret_buf->data[offset++] = ((uint8_t*)rResponse->data_identifier_value[i].data)[j];
        }
    }

    return offset;
}

size_t x22_RDBI_clientGetNextDID(const uds_buf_t* buf, uint16_t* ret_DID) {
    //  Safety
    if(buf == NULL || ret_DID == NULL) {
        return 0;
    }

    //  Minimum length check
    if (buf->buf_len < 2) {
        return 0;
    }

    //  Return result
    *ret_DID = (uint16_t)( (buf->data[0] << 8) | buf->data[1] );

    //  Have caller offset by 2
    return 2;
}

size_t x22_RDBI_clientGetNextValue(const uds_buf_t* buf, const size_t DID_size, uds_buf_t* ret_value) {
    //  Safety
    if(buf == NULL || ret_value->data == NULL) {
        return 0;
    }

    //  Input minimum length check
    if (buf->buf_len < DID_size) {
        return 0;
    }

    //  Output minimum length check
    if (ret_value->buf_len < DID_size) {
        return 0;
    }

    //  Copy data
    for(size_t i = 0; i < DID_size; i++) {
        ret_value->data[i] = buf->data[i];
    }

    //  Return result
    return DID_size;
}

UDS_NRC_t x22_RDBI_serverDecodeRequest(void* query, const uds_buf_t buf) {
    UDS_22_RDBI_query* rQuery = (UDS_22_RDBI_query*)query;

    //  Safety
    if(rQuery == NULL || rQuery->data_identifier == NULL || buf.data == NULL) {
        return UDS_NRC_IMLOIF;
    }
    
    //  Minimum length check
    if (buf.buf_len < 2) {
        return UDS_NRC_IMLOIF;
    }

    //  Modulo 2 Division Check
    if (buf.buf_len % 2 != 0) {
        return UDS_NRC_IMLOIF;
    }

    //  Too long check
    size_t element_count = buf.buf_len / 2;
    if (element_count > rQuery->elements_size) {
        return UDS_NRC_RESPONSE_TOO_LONG;
    }

    //  Populate query structure
    rQuery->elements_count = element_count;
    for(size_t i = 0; i < element_count; i++) {
        rQuery->data_identifier[i] = (uint16_t)( (buf.data[i * 2] << 8) | buf.data[(i * 2) + 1] );
    }

    return UDS_NRC_PR;
}

size_t x22_RDBI_clientEncodeRequest(const void* query, uds_buf_t* ret_buf) {
    const UDS_22_RDBI_query* rQuery = (const UDS_22_RDBI_query*)query;

    //  DID argument check
    if(rQuery->data_identifier == NULL) {
        return 0;
    }
    
    //  Query argument check
    if(rQuery->elements_count == 0) {
        return 0;
    }
    
    //  Sufficient buffer length check
    if(ret_buf->buf_len < rQuery->elements_count * 2 || rQuery->elements_count > (SIZE_MAX / 2)) {
        return 0;
    }

    //  Encode
    size_t offset = 0;
    for(size_t i = 0; i < rQuery->elements_count; i++) {
        //  MSB
        ret_buf->data[offset++] = (rQuery->data_identifier[i] >> 8) & 0xFF;

        //  LSB
        ret_buf->data[offset++] = rQuery->data_identifier[i] & 0xFF;
    }

    return offset;
}

UDS_SERVICE_IMPLEMENTATION_t UDS_22_RDBI = {
    .clientEncodeRequest = x22_RDBI_clientEncodeRequest,
    .clientDecodeResponse = NULL,
    .serverEncodeResponse = x22_RDBI_serverEncodeResponse,
    .serverDecodeRequest = x22_RDBI_serverDecodeRequest,
};