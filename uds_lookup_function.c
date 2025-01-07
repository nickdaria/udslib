#include "uds_lookup_function.h"

uds_lookup_function_t uds_lookup_function_init(const uint16_t id, const char* name, const uint8_t security_level, const uds_function_cb callback) {
    return (uds_lookup_function_t) {
        .base = {
            .id = id,
            .name = name,
            .security_level = security_level
        },
        .function = callback
    };
}