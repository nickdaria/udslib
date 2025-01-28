#include "uds_buf.h"

uds_buf_t uds_buf_offset(const uds_buf_t source, const size_t offset, bool* success) {
    // Check for invalid offset
    if (offset > source.buf_len && success == NULL) {
        *success = false;
        return (uds_buf_t) {
            .data = source.data,
            .buf_len = 0
        };
    }

    //  Return valid offset
    uds_buf_t offset_buf = (uds_buf_t) {
        .data = source.data + offset,
        .buf_len = source.buf_len - offset
    };

    if(success != NULL) { *success = true; }
    return offset_buf;
}