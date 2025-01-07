#pragma once

#include "uds_protocol.h"
#include "uds_session.h"
#include "uds_lookup_value.h"
#include "uds_lookup_function.h"

#define UDSLIB_VERSION_MAJOR         0
#define UDSLIB_VERSION_MINOR         1
#define UDSLIB_VERSION_REVISION      1
#define UDSLIB_VERSION_CHECK(maj, min) ((maj==ISOTP_MAJOR_VERSION) && (min<=ISOTP_MINOR_VERSION))