#include "34_requestDownload.h"
#include "../../protocol/uds_services.h"
UDS_SERVICE_IMPLEMENTATION_t UDS_34_RD = {
    .sid = UDS_SID_RD, .name = "RequestDownload",
    .pRequestSize = sizeof(UDS_34_RD_Request), .pResponseSize = sizeof(UDS_34_RD_Response),
    .clientEncodeRequest = uds_transfer_encode_request,
    .clientDecodeResponse = uds_transfer_decode_response,
    .serverPrepareResponse = uds_transfer_prepare_response,
    .serverEncodeResponse = uds_transfer_encode_response,
    .serverDecodeRequest = uds_transfer_decode_request
};
