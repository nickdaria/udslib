#ifdef __cplusplus

//  This is basically to make Arduino environments happy
extern "C" {
    #include "session/uds_session.h"
    #include "protocol/uds_protocol.h"
    #include "services/uds_services.h"
    #include "lookup/uds_lookup_value.h"
    #include "lookup/uds_lookup_function.h"
}

#endif