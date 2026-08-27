#include "personal_log.h"
#include "utils.h"
#include "date_recheck.h"
#include "status_update.h"
#include "user_type.h"
#include <stdio.h>
#include <string.h>

#define MAX_NAME_LEN 100
#define MAX_LINE_LEN 256

// Helper to get name from user file based on ID
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

static void create_personal_log_impl(const char *id, const char *date_str, const char *time_str, int is_entry, UserType type) {
    // Update manager state
    strcpy(personal_log_manager.user_info.id, id);
    personal_log_manager.user_info.type = type;
    strcpy(personal_log_manager.current_date, date_str);
    strcpy(personal_log_manager.current_time, time_str);
    personal_log_manager.is_entry = is_entry;

    const char *dir = (type == USER_STUDENT) ? STUDENT_DIR :
                     (type == USER_TEACHER) ? TEACHER_DIR : ADMIN_DIR;

    snprintf(personal_log_manager.log_filename, sizeof(personal_log_manager.log_filename),
             "%s%s.txt", dir, id);

    FILE *file = fopen(personal_log_manager.log_filename, "a+");
    if (!file) {
        perror("Opening user file failed");
        return;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    if (size == 0) {
        // Get the name to include it in the header
        char name[MAX_NAME_LEN] = "Unknown";
        find_user_name(id, type, name, sizeof(name));
        strcpy(personal_log_manager.user_info.name, name);

        fprintf(file, "ID: %s\n", id);
        fprintf(file, "Name: %s\n", name);
        fprintf(file, "Status: %s\n", is_entry ? "IN" : "OUT");
    }

    rewind(file);
    int section_exists = date_checker.check_date_exists(file, date_str);
    fclose(file);

    file = fopen(personal_log_manager.log_filename, "a");
    if (!section_exists) {
        fprintf(file, "\n\n%s\n------------\n", date_str);
    }

    fprintf(file, "%s: %s\n", is_entry ? "Entry" : "Exit", time_str);
    fclose(file);

    status_manager.update_status(personal_log_manager.log_filename, is_entry ? "IN" : "OUT");
}

PersonalLogManager personal_log_manager = {
    .user_info = {{0}, {0}, USER_UNKNOWN},
    .log_filename = {0},
    .current_date = {0},
    .current_time = {0},
    .is_entry = 0,
    .create_personal_log = create_personal_log_impl
};
