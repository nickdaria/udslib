#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include "../uds_service_framework.h"

/* Odd access types request a seed; the next even type sends its key.
   Record pointers borrow their input buffer and must remain valid during encoding. */
typedef struct {
    uint8_t securityAccessType;
    const uint8_t* securityAccessDataRecord; /* seed request record or key */
    size_t securityAccessDataRecordLen;
} UDS_27_SA_Request;

typedef struct {
    uint8_t securityAccessType;
    const uint8_t* securitySeed; /* required for seed response, absent for key response */
    size_t securitySeedLen;
} UDS_27_SA_Response;

/* Seed generation, key validation, attempt counters and delay timers belong to
   the application handler, which can return 0x24, 0x35, 0x36 or 0x37. */
extern UDS_SERVICE_IMPLEMENTATION_t UDS_27_SA;
#ifdef __cplusplus
}
#endif
