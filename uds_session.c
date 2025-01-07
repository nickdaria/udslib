#include "uds_session.h"

void uds_session_init(uds_session_t* session, uds_lookup_function_t* services_table, size_t services_table_len) {
    session->security_level = 0;
    session->services_table = services_table;
    session->services_table_len = services_table_len;
}