#include "encapsulation_process.h"
#include <conio.h>
#include <stdio.h>

static void get_hidden_input_impl(char *buffer, size_t size) {
    int i = 0;
    char ch;
    while (1) {
        ch = _getch();
        if (ch == '\r') {
            buffer[i] = '\0';
            printf("\n");
            break;
        } else if (ch == '\b') {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else if (i < size - 1) {
            buffer[i++] = ch;
            printf("*");
        }
    }
}

SecureInput secure_input = {
    .buffer = {0},
    .buffer_size = 0,
    .get_hidden_input = get_hidden_input_impl
};
