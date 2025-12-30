#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include "../../udslib.h"
#include "../uds_service_framework.h"
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint16_t data_identifier;
    uint8_t* data_record;
    size_t data_record_len;
} UDS_2E_WDBI_Request;

typedef struct {
    uint16_t data_identifier;
} UDS_2E_WDBI_Response;

extern UDS_SERVICE_IMPLEMENTATION_t UDS_2E_WDBI;

#ifdef __cplusplus
}
#endif