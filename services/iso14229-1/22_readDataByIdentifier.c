#include "22_readDataByIdentifer.h"

size_t UDS_22_RDBI_server_encodePositiveResponse(const UDS_22_RDBI_query* query, const UDS_22_RDBI_response* response, uint8_t* buf, const size_t len) {
    //  Safety
    if(query == NULL || query->data_identifier == NULL || response == NULL || response->data_identifier_value == NULL || response->data_identifier_value == NULL || buf == NULL) {
        return 0;
    }

    //  Calculate required size
    size_t did_size = query->elements_count * 2;
    size_t did_value_size = 0;
    for(size_t i = 0; i < query->elements_count; i++) {
        did_value_size += response->data_identifier_value[i].len;
    }

    //  Sufficient buffer length check
    if (did_size + did_value_size > len) {
        return 0;
    }

    size_t offset = 0;

    for(size_t i = 0; i < query->elements_count; i++) {
        //  MSB
        buf[offset++] = (query->data_identifier[i] >> 8) & 0xFF;

        //  LSB
        buf[offset++] = query->data_identifier[i] & 0xFF;

        //  Copy data
        for(size_t j = 0; j < response->data_identifier_value[i].len; j++) {
            buf[offset++] = ((uint8_t*)response->data_identifier_value[i].data)[j];
        }
    }

    return offset;
}

size_t UDS_22_RDBI_client_decodePositiveResponse() {
    
}

size_t UDS_22_RDBI_client_getNextDID(const uint8_t* buf, const size_t len, uint16_t* ret_DID) {
    //  Safety
    if(buf == NULL || ret_DID == NULL) {
        return 0;
    }

    //  Minimum length check
    if (len < 2) {
        return 0;
    }

    //  Return result
    *ret_DID = (uint16_t)( (buf[0] << 8) | buf[1] );

    //  Have caller offset by 2
    return 2;
}

size_t UDS_22_RDBI_client_getNextValue(const uint8_t* buf, const size_t len, const size_t DID_size, uint8_t* ret_value_ptr) {
    //  Safety
    if(buf == NULL || ret_value_ptr == NULL) {
        return 0;
    }

    //  Minimum length check
    if (len < DID_size) {
        return 0;
    }

    //  Copy data
    for(size_t i = 0; i < DID_size; i++) {
        ret_value_ptr[i] = buf[i];
    }

    //  Return result
    return DID_size;
}

UDS_NRC_t UDS_22_RDBI_server_decodeRequest(UDS_22_RDBI_query* query, const size_t query_buf_size, const uint8_t* buf, const size_t len) {
    //  Safety
    if(query == NULL || query->data_identifier == NULL || buf == NULL) {
        return UDS_NRC_IMLOIF;
    }
    
    //  Minimum length check
    if (len < 2) {
        return UDS_NRC_IMLOIF;
    }

    //  Modulo 2 Division Check
    if (len % 2 != 0) {
        return UDS_NRC_IMLOIF;
    }

    //  Too long check
    size_t element_count = len / 2;
    if (element_count > query_buf_size) {
        return UDS_NRC_RESPONSE_TOO_LONG;
    }

    //  Populate query structure
    query->elements_count = element_count;
    for(size_t i = 0; i < element_count; i++) {
        query->data_identifier[i] = (uint16_t)( (buf[i * 2] << 8) | buf[(i * 2) + 1] );
    }

    return UDS_NRC_PR;
}

size_t UDS_22_RDBI_client_encodeRequest(const UDS_22_RDBI_query* query, uint8_t* buf, const size_t buf_len) {
    //  DID argument check
    if(query->data_identifier == NULL) {
        return 0;
    }
    
    //  Query argument check
    if(query->elements_count == 0) {
        return 0;
    }
    
    //  Sufficient buffer length check
    if(buf_len < query->elements_count * 2 || query->elements_count > (SIZE_MAX / 2)) {
        return 0;
    }

    //  Encode
    size_t offset = 0;
    for(size_t i = 0; i < query->elements_count; i++) {
        //  MSB
        buf[offset++] = (query->data_identifier[i] >> 8) & 0xFF;

        //  LSB
        buf[offset++] = query->data_identifier[i] & 0xFF;
    }

    return offset;
}