#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include <udslib.h>

size_t service_diagnostic_session_control(const uds_function_context_t* context, uds_response_data_t* uds_response, uds_buffers_t buffers);
size_t service_read_by_id(const uds_function_context_t* context, uds_response_data_t* uds_response, uds_buffers_t buffers);
size_t service_write_by_id(const uds_function_context_t* context, uds_response_data_t* uds_response, uds_buffers_t buffers);

size_t service_read_by_local_id(const uds_function_context_t* context, uds_response_data_t* uds_response, uds_buffers_t buffers);

uds_session_t session;

uint8_t test_8 = 0x12;
uint16_t test_16 = 0x1234;
uint32_t test_32 = 0x12345678;
uint64_t test_64 = 0x1234567890ABDEF0;

uds_lookup_value_t values[] = {
    {
        .base = {
            .id = 0x1234,
            .name = "Test 8",
            .security_level = UDS_PROTOCOL_DEFAULT_SESSION
        },
        .buf = {
            .data = &test_8,
            .bufLen = sizeof(test_8)
        },
        .data_write_ptr = &test_8,
        .numericType = true,
        .data_write_security_level = 0xC0
    },
    {
        .base = {
            .id = 0x1235,
            .name = "Test 16",
            .security_level = 0xC0
        },
        .buf = {
            .data = (uint8_t*)&test_16,
            .bufLen = sizeof(test_16)
        },
        .data_write_ptr = NULL,
        .numericType = true,
        .data_write_security_level = 0x00
    },
    {
        .base = {
            .id = 0x1236,
            .name = "Test 32",
            .security_level = 0xC0
        },
        .buf = {
            .data = (uint8_t*)&test_32,
            .bufLen = sizeof(test_32)
        },
        .data_write_ptr = &test_32,
        .numericType = true,
        .data_write_security_level = 0xC0
    },
    {
        .base = {
            .id = 0x1237,
            .name = "Test 64",
            .security_level = 0xC0
        },
        .buf = {
            .data = (uint8_t*)&test_64,
            .bufLen = sizeof(test_64)
        },
        .data_write_ptr = &test_64,
        .numericType = true,
        .data_write_security_level = 0xC0
    }
};

uds_lookup_function_t services[] = {
    {
        .base = {
            .id = UDS_SID_DIAGNOSTIC_SESSION_CONTROL,
            .name = "Diagnostic Session Control",
            .security_level = 0x01
        },
        .function = service_diagnostic_session_control
    },
    {
        .base = {
            .id = UDS_SID_RDBI, //  same as UDS_SID_READ_DATA_BY_IDENTIFIER
            .name = "Read Data By Identifier",
            .security_level = 0x01
        },
        .function = service_read_by_id
    },
    {
        .base = {
            .id = UDS_SID_WDBI, //  same as UDS_SID_WRITE_DATA_BY_IDENTIFIER
            .name = "Write Data By Identifier",
            .security_level = 0x30
        },
        .function = service_write_by_id
    },
    {
        .base = {
            .id = UDS_SID_RDBLI,
            .name = "Read Data By Local Identifier",
            .security_level = 0x01
        },
        .function = service_read_by_local_id
    }
};

void cmd_help() {
    printf("[Simple desktop playground for testing udslib]\n");
    printf("(this tool is made for use with the vscode debugger)\n");
    printf("\th - help\n");
    printf("\t[enter] - request UDS transmit data\n");
    printf("\t> XXXXXX Enter hex formatted data (no spaces) at the prompt to emulate UDS RX frames (without ISO-TP protocol)\n");
}

void cmd_hexdata(const uint8_t* buf, const size_t bufLen) {
    uint8_t response_buf[456];

    uds_buf_t request_buf_s = { .data = (uint8_t*)buf, .bufLen = bufLen };
    uds_buf_t response_buf_s = { .data = response_buf, .bufLen = sizeof(response_buf) };

    uds_buffers_t uds_bufs = {
        .request = request_buf_s,
        .response = response_buf_s
    };

    size_t response_len = uds_server_process_request(&session, uds_bufs, NULL);

    printf("Response: ");
    for (size_t i = 0; i < response_len; i++) {
        printf("%02X ", response_buf[i]);
    }
    printf("\n");
}

void cmd_enter() {
    
}

//  Obtain user input
size_t user_rx_cmd(uint8_t* buffer, const size_t buffer_size) {
    size_t length = 0;
    while (length < buffer_size) {
        int c = getchar();
        if (c == '\n' || c == EOF) {
            break;
        }
        buffer[length++] = c;
    }
    buffer[length] = '\0'; // Null-terminate for safety
    return length;
}

void usr_process_cmd(const uint8_t* buffer, const size_t length) {
    // Empty input
    if (length == 0) {
        cmd_enter();
        return;
    }

    // 'h' command
    if (length == 1 && buffer[0] == 'h') {
        cmd_help();
        return;
    }

    // Attempt to parse as hex
    uint8_t hex_buffer[128];
    size_t hex_len = 0;

    for (size_t i = 0; i < length; i += 2) {
        if (i + 1 >= length || !isxdigit(buffer[i]) || !isxdigit(buffer[i + 1])) {
            printf("[ERROR] Invalid hex input: '%c%c'\n", buffer[i], i + 1 < length ? buffer[i + 1] : ' ');
            return;
        }
        sscanf((const char*)&buffer[i], "%2hhX", &hex_buffer[hex_len++]);
    }

    // Call cmd_hexdata with the parsed hex buffer
    cmd_hexdata(hex_buffer, hex_len);
}

size_t service_diagnostic_session_control(const uds_function_context_t* context, uds_response_data_t* uds_response, uds_buffers_t buffers) {
    printf("Diagnostic session control");
    printf(" - Security: %d, ID: %d, Name: %s\n", context->security_level, context->resource->id, context->resource->name);

    //  Get session
    uds_session_t* session = (uds_session_t*)context->uds_session;

    //  Length check
    if(buffers.request.bufLen < 1) {
        uds_response->error_code = UDS_NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT;
        return 0;
    }

    //  Invalid session
    uint8_t desired_level = buffers.request.data[0];
    if(desired_level == 0) {
        uds_response->error_code = UDS_NRC_IMLOIF;
        return 0;
    }

    //  Enter requested level
    session->security_level = desired_level;

    //  Return positive response
    uds_response->error_code = UDS_NRC_PR;
    buffers.response.data[0] = desired_level;
    return 1;
}

size_t service_read_by_id(const uds_function_context_t* context, uds_response_data_t* uds_response, uds_buffers_t buffers) {
    printf("Read by local id");
    printf(" - Security: %d, ID: %d, Name: %s\n", context->security_level, context->resource->id, context->resource->name);

    //  Length check
    if(buffers.request.bufLen != 2) {
        uds_response->error_code = UDS_NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT;
        return 0;
    }

    //  Get local ID
    uint16_t local_id = (buffers.request.data[0] << 8) | buffers.request.data[1];

    //  Prepare response buffer
    size_t offset = 0;
    buffers.response.data[offset++] = local_id >> 8;
    buffers.response.data[offset++] = local_id & 0xFF;

    uds_buf_t shifted_response_buf = uds_buf_offset(buffers.response, offset, NULL);

    //  Find and return
    offset += uds_lookup_value_read(context->uds_session, uds_response, shifted_response_buf, local_id, context->security_level, values, sizeof(values) / sizeof(uds_lookup_value_t));
    return offset;
}

size_t service_write_by_id(const uds_function_context_t* context, uds_response_data_t* uds_response, uds_buffers_t buffers) {
    printf("Write by local id");
    printf(" - Security: %d, ID: %d, Name: %s\n", context->security_level, context->resource->id, context->resource->name);

    //  Length check
    if(buffers.request.bufLen < 2) {
        uds_response->error_code = UDS_NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT;
        return 0;
    }

    //  Get local ID
    uint16_t local_id = (buffers.request.data[0] << 8) | buffers.request.data[1];

    //  Get buffer with response data
    uds_buf_t shifted_request_data = uds_buf_offset(buffers.request, 2, NULL);

    //  Prepare response buffer
    size_t offset = 0;
    buffers.response.data[offset++] = local_id >> 8;
    buffers.response.data[offset++] = local_id & 0xFF;

    uds_buf_t shifted_response_data = uds_buf_offset(buffers.response, offset, NULL);

    //  Find and write
    offset += uds_lookup_value_write(context->uds_session, uds_response, shifted_response_data, local_id, context->security_level, shifted_request_data, values, sizeof(values) / sizeof(uds_lookup_value_t));
    return offset;
}

size_t service_read_by_local_id(const uds_function_context_t* context, uds_response_data_t* uds_response, uds_buffers_t buffers) {
    printf("Read by local id");
    printf(" - Security: %d, ID: %d, Name: %s\n", context->security_level, context->resource->id, context->resource->name);

    UDS_21_RDBLI_request_t request;
    uds_response->error_code = UDS_21_RDBLI.serverDecodeRequest(&request, buffers.request);

    //  Testing - just return incrementing bytes with length of request byte
    size_t length_of_test_data = request.local_identifier;
    size_t length_of_test_resp = length_of_test_data + 1;

    uds_buf_t response_buf = {
        .data = (uint8_t*)malloc(length_of_test_resp),
        .bufLen = length_of_test_resp
    };
    for(size_t i = 0; i <= length_of_test_data; i++) {
        response_buf.data[i] = (uint8_t)i;
    }

    UDS_21_RDBLI_response_t response = {
        .request = request,
        .value = response_buf,
        .value_len = length_of_test_data
    };
    size_t return_len = UDS_21_RDBLI.serverEncodeResponse(&response, buffers.response);
    free(response_buf.data);

    if(return_len == 0) {
        uds_response->error_code = UDS_NRC_RESPONSE_TOO_LONG;
    }

    return return_len;
}

//  Main loop
void playground() {
    // Get user input
    uint8_t buffer[256];
    size_t length = user_rx_cmd(buffer, sizeof(buffer));

    // Process user command
    usr_process_cmd(buffer, length);
}

void main() {
    uds_server_init(&session, services, sizeof(services) / sizeof(uds_lookup_function_t));

    cmd_help();
    while (1) {
        printf("> "); // Prompt user
        fflush(stdout); // Ensure prompt is visible
        playground();
    }
    return;
}