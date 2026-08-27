#include "date_recheck.h"
#include <string.h>

static int check_date_exists_impl(FILE *file, const char *date_str) {
    rewind(file);
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, date_str)) return 1;
    }
    return 0;
}

DateChecker date_checker = {
    .target_date = {0},
    .file_ptr = NULL,
    .check_date_exists = check_date_exists_impl
};
