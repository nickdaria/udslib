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

void main() {

}