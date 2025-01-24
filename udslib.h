#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/*
    udslib
        - uds_session.h - set up a table of services and handle requests
        - uds_protocol.h - constants used by the library from the UDS ISO 14229-1 standard
        - uds_lookup_value.h - build a lookup table of values to read and/or write
        - uds_lookup_function.h - build a lookup table of functions to call
        - uds_services.h - structs, decoding, and encoding for ISO 14299-1 services
*/

#include "session_server/uds_server.h"
#include "protocol/uds_protocol.h"
#include "services/uds_services.h"
#include "lookup/uds_lookup_value.h"
#include "lookup/uds_lookup_function.h"

#define UDSLIB_VERSION_MAJOR         0
#define UDSLIB_VERSION_MINOR         1
#define UDSLIB_VERSION_REVISION      1
#define UDSLIB_VERSION_CHECK(maj, min) ((maj==ISOTP_MAJOR_VERSION) && (min<=ISOTP_MINOR_VERSION))

#ifdef __cplusplus
}
#endif