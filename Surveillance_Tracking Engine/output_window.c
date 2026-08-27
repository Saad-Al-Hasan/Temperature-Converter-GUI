#include "output_window.h"
#include "get_current_time.h"
#include "entry_exit.h"
#include "personal_log.h"
#include "log_update.h"
#include "user_type.h"
#include <stdio.h>
#include <string.h>
#include "utils.h"

#define MAX_NAME_LEN 100
#define MAX_LINE_LEN 256

// Helper to retrieve name by ID from the user file
static int find_user_name(const char *id, UserType type, char *out_name, size_t name_size) {
    const char *filename = (type == USER_STUDENT) ? "student_list.txt" :
                          (type == USER_TEACHER) ? "teacher_list.txt" :
                          (type == USER_ADMIN)   ? "admin_list.txt" : NULL;

    if (!filename) return 0;

    FILE *file = fopen(filename, "r");
    if (!file) return 0;

    char line[MAX_LINE_LEN];
    while (fgets(line, sizeof(line), file)) {
        char file_id[MAX_ID_LEN], name[MAX_NAME_LEN];
        if (sscanf(line, "%s %s", file_id, name) == 2) {
            if (strcmp(file_id, id) == 0) {
                strncpy(out_name, name, name_size - 1);
                out_name[name_size - 1] = '\0';
                fclose(file);
                return 1;
            }
        }
    }

    fclose(file);
    return 0;
}

static void record_attendance_impl(const char *id, UserType type) {
    char date_str[20], time_str[15], datetime_console[40];

    // Update current user in manager
    strcpy(output_manager.current_user.id, id);
    output_manager.current_user.type = type;

    time_manager.get_current_time(date_str, time_str, datetime_console);

    int is_entry = !entry_exit_tracker.check_user_status(id, type);
    personal_log_manager.create_personal_log(id, date_str, time_str, is_entry, type);
    log_manager.update_log(id, date_str, time_str, is_entry, type);

    // Lookup name
    char name[MAX_NAME_LEN] = "Unknown";
    find_user_name(id, type, name, sizeof(name));
    strcpy(output_manager.current_user.name, name);

    snprintf(output_manager.display_message, sizeof(output_manager.display_message),
             "%s ID: %s (%s) marked as %s.", datetime_console, id, name, is_entry ? "Entry" : "Exit");

    printf("%s\n", output_manager.display_message);
}

OutputManager output_manager = {
    .current_user = {{0}, {0}, USER_UNKNOWN},
    .display_message = {0},
    .record_attendance = record_attendance_impl
};
