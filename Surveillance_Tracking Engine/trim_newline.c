#include "trim_newline.h"
#include <string.h>

static void trim_newline_impl(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

StringTrimmer string_trimmer = {
    .target_string = NULL,
    .trim_newline = trim_newline_impl
};
