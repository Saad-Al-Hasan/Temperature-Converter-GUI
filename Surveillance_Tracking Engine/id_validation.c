#include "id_validation.h"
#include "utils.h"
#include "trim_newline.h"
#include <stdio.h>
#include <string.h>

static int validate_id_impl(const char *id, UserType type) {
    const char *filename = (type == USER_STUDENT) ? STUDENT_LIST_FILE :
                          (type == USER_TEACHER) ? TEACHER_LIST_FILE :
                          (type == USER_ADMIN)   ? ADMIN_LIST_FILE : NULL;
    if (!filename) return 0;

    FILE *file = fopen(filename, "r");
    if (!file) return 0;

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        string_trimmer.trim_newline(line);
        char file_id[MAX_ID_LEN];
        // Extract only the first word from the line (ID)
        if (sscanf(line, "%s", file_id) == 1) {
            if (strcmp(file_id, id) == 0) {
                fclose(file);
                return 1; // ID matched
            }
        }
    }
    fclose(file);
    return 0; // Not found
}

IdValidator id_validator = {
    .id_to_validate = {0},
    .type_to_check = USER_UNKNOWN,
    .is_valid = 0,
    .validate_id = validate_id_impl
};
