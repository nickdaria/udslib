#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <udslib.h>

uds_session_t session;

void cmd_help() {
    printf("[Simple desktop playground for testing udslib]\n");
    printf("(this tool is made for use with the vscode debugger)\n");
    printf("\th - help\n");
    printf("\t[enter] - request UDS transmit data\n");
    printf("\t> XXXXXX Enter hex formatted data (no spaces) at the prompt to emulate UDS RX frames (without ISO-TP protocol)\n");
}

void cmd_hexdata(const uint8_t* buf, const size_t len) {
    uint8_t response_buf[256];
    size_t response_len = uds_session_process_request(&session, buf, len, response_buf, sizeof(response_buf));

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

size_t service_diagnostic_session_control(const uds_function_context_t* context, uds_response_data_t* uds_response, const uint8_t* data, const size_t data_len, uint8_t* response_data, const size_t response_len_max) {
    printf("Diagnostic session control");
    printf(" - Security: %d, ID: %d, Name: %s\n", context->security_level, context->resource->id, context->resource->name);

    //  Get session
    uds_session_t* session = (uds_session_t*)context->uds_session;

    //  Length check
    if(data_len < 1) {
        uds_response->error_code = UDS_NACK_INVALID_FORMAT;
        return 0;
    }

    //  Enter requested level
    session->security_level = data[0];

    //  Return positive response
    uds_response->error_code = UDS_NACK_OK;
    response_data[0] = data[0];
    return 1;
}

size_t service_read_by_local_id(const uds_function_context_t* context, uds_response_data_t* uds_response, const uint8_t* data, const size_t data_len, uint8_t* response_data, const size_t response_len_max) {
    printf("Read by local id");
    printf(" - Security: %d, ID: %d, Name: %s\n", context->security_level, context->resource->id, context->resource->name);

    //  Return a response
    response_data[0] = 0x01;
    response_data[1] = 0x02;
    response_data[2] = 0x03;
    response_data[3] = 0x04;

    uds_response->error_code = UDS_NACK_OK;
    uds_response->send_response = true;
    return 4;
}

size_t service_write_by_local_id(const uds_function_context_t* context, uds_response_data_t* uds_response, const uint8_t* data, const size_t data_len, uint8_t* response_data, const size_t response_len_max) {
    printf("Write by local id");
    printf(" - Security: %d, ID: %d, Name: %s\n", context->security_level, context->resource->id, context->resource->name);

    //  Return a response
    response_data[0] = 0x01;
    response_data[1] = 0x02;
    response_data[2] = 0x03;
    response_data[3] = 0x04;

    uds_response->error_code = UDS_NACK_OK;
    uds_response->send_response = true;
    return 4;
}

uds_lookup_function_t services[] = {
    {
        .base = {
            .id = UDS_SERVICE_DIAGNOSTIC_SESSION_CONTROL,
            .name = "Diagnostic Session Control",
            .security_level = 1
        },
        .function = service_diagnostic_session_control
    },
    {
        .base = {
            .id = UDS_SERVICE_READ_DATA_BY_IDENTIFIER,
            .name = "Read Data By Identifier",
            .security_level = 1
        },
        .function = service_read_by_local_id
    },
    {
        .base = {
            .id = UDS_SERVICE_WRITE_DATA_BY_IDENTIFIER,
            .name = "Write Data By Identifier",
            .security_level = 0x30
        },
        .function = service_write_by_local_id
    }
};

//  Main loop
void playground() {
    // Get user input
    uint8_t buffer[256];
    size_t length = user_rx_cmd(buffer, sizeof(buffer));

    // Process user command
    usr_process_cmd(buffer, length);
}

void main() {
    uds_session_init(&session, services, sizeof(services) / sizeof(uds_lookup_function_t));

    cmd_help();
    while (1) {
        printf("> "); // Prompt user
        fflush(stdout); // Ensure prompt is visible
        playground();
    }
    return;
}