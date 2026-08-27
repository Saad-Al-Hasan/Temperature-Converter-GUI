#include "entry_exit.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

static int check_user_status_impl(const char *id, UserType type) {
    char filename[128], line[512];
    const char *dir = (type == USER_STUDENT) ? STUDENT_DIR :
                     (type == USER_TEACHER) ? TEACHER_DIR : ADMIN_DIR;
    snprintf(filename, sizeof(filename), "%s%s.txt", dir, id);

    FILE *file = fopen(filename, "r");
    if (!file) return 0;

    entry_exit_tracker.entry_count = 0;
    entry_exit_tracker.exit_count = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "Entry:")) entry_exit_tracker.entry_count++;
        if (strstr(line, "Exit:")) entry_exit_tracker.exit_count++;
    }
    fclose(file);

    return (entry_exit_tracker.entry_count > entry_exit_tracker.exit_count);
}

EntryExitTracker entry_exit_tracker = {
    .user_id = {0},
    .user_type = USER_UNKNOWN,
    .entry_count = 0,
    .exit_count = 0,
    .check_user_status = check_user_status_impl
};
