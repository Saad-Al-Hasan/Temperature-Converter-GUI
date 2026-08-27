#include "log_update.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_NAME_LEN 100
#define MAX_LINE_LEN 256

// Helper: get name from ID and user type
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

// Write new date headers
static void write_date_to_all_files(const char *date_str) {
    const char *log_files[] = {STUDENT_LOG_FILE, TEACHER_LOG_FILE, ADMIN_LOG_FILE};
    for (int i = 0; i < 3; i++) {
        FILE *log = fopen(log_files[i], "a+");
        if (!log) continue;
        fprintf(log, "\n%s\n------------------\n", date_str);
        fclose(log);
    }
    strcpy(log_manager.last_logged_date, date_str);
    log_manager.date_initialized = 1;
}

static void update_log_impl(const char *id, const char *date_str, const char *time_str, int is_entry, UserType type) {
    const char *log_file = (type == USER_STUDENT) ? STUDENT_LOG_FILE :
                          (type == USER_TEACHER) ? TEACHER_LOG_FILE :
                          ADMIN_LOG_FILE;

    // Update manager state
    strcpy(log_manager.current_user.id, id);
    log_manager.current_user.type = type;
    strcpy(log_manager.current_date, date_str);
    strcpy(log_manager.current_time, time_str);
    log_manager.is_entry = is_entry;

    if (!log_manager.date_initialized || strcmp(log_manager.last_logged_date, date_str) != 0) {
        write_date_to_all_files(date_str);
    }

    FILE *log = fopen(log_file, "a+");
    if (!log) return;

    char name[MAX_NAME_LEN] = "Unknown";
    find_user_name(id, type, name, sizeof(name));
    strcpy(log_manager.current_user.name, name);

    fprintf(log, "%s | %s | %s | Time : %s\n", id, name, is_entry ? "ENTRY" : "EXIT", time_str);
    fclose(log);
}

LogManager log_manager = {
    .last_logged_date = {0},
    .date_initialized = 0,
    .current_user = {{0}, {0}, USER_UNKNOWN},
    .current_date = {0},
    .current_time = {0},
    .is_entry = 0,
    .update_log = update_log_impl
};
