#include "uds_client.h"

uds_buf_t uds_client_prepare_request(UDS_SID_t service_id, const uds_buf_t buf) {
    //  Safety
    if(buf.buf_len < 1) {
        return (uds_buf_t) {
            .data = NULL,
            .buf_len = 0
        };
    }

    //  Service ID
    buf.data[0] = service_id;

    //  Offset ret buf
    return uds_buf_offset(buf, 1, NULL);
}