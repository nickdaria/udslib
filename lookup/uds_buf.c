#include "uds_buf.h"

uds_buf_t uds_buf_offset(const uds_buf_t source, const size_t offset, bool* success) {
    // Check for invalid offset
    if (offset > source.bufLen && success == NULL) {
        *success = false;
        return (uds_buf_t) {
            .data = source.data,
            .bufLen = 0
        };
    }

    //  Return valid offset
    uds_buf_t offset_buf = (uds_buf_t) {
        .data = source.data + offset,
        .bufLen = source.bufLen - offset
    };

    if(success != NULL) { *success = true; }
    return offset_buf;
}

void uds_straight_copy(uint8_t* destination, const uint8_t* source, size_t size) {
    // Copy bytes directly
    for (size_t i = 0; i < size; i++) {
        destination[i] = source[i];
    }
}

void uds_reverse_copy(uint8_t* destination, const uint8_t* source, size_t size) {
    // Copy bytes in reverse order (little-endian -> big-endian)
    for (size_t i = 0; i < size; i++) {
        destination[i] = source[size - 1 - i];
    }
}

size_t uds_big_endian_copy(uint8_t* destination, const uds_buf_t source, const bool numericType) {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    if(numericType) {
        uds_reverse_copy(destination, source.data, source.bufLen);
        return source.bufLen;
    }
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#else
    #error "Unsupported byte order"
#endif

    uds_straight_copy(destination, source.data, source.bufLen);
    return source.bufLen;
}