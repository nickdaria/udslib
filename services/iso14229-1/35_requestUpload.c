#include "35_requestUpload.h"
#include "../../protocol/uds_services.h"
UDS_SERVICE_IMPLEMENTATION_t UDS_35_RU = {
    .sid = UDS_SID_RU, .name = "RequestUpload",
    .pRequestSize = sizeof(UDS_35_RU_Request), .pResponseSize = sizeof(UDS_35_RU_Response),
    .clientEncodeRequest = uds_transfer_encode_request,
    .clientDecodeResponse = uds_transfer_decode_response,
    .serverPrepareResponse = uds_transfer_prepare_response,
    .serverEncodeResponse = uds_transfer_encode_response,
    .serverDecodeRequest = uds_transfer_decode_request
};
