#include "surveillance_tracking_engine.h"
#include "utils.h"
#include "encapsulation_process.h"
#include "trim_newline.h"
#include "id_pattern.h"
#include "id_validation.h"
#include "output_window.h"
#include "add_user.h"
#include "delete_user.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

static void run_attendance_system_impl(void) {
    attendance_system.system_running = 1;
    attendance_system.hidden_mode = 0;

    printf("=== Surveillance / Tracking Engine ===\n");

    while (attendance_system.system_running) {
        printf("\nEnter ID: ");

        if (attendance_system.hidden_mode) {
            secure_input.get_hidden_input(attendance_system.current_id, sizeof(attendance_system.current_id));
        } else {
            if (fgets(attendance_system.current_id, sizeof(attendance_system.current_id), stdin) == NULL) {
                break;
            }
            string_trimmer.trim_newline(attendance_system.current_id);
        }

        if (strcmp(attendance_system.current_id, "exit") == 0) {
            attendance_system.system_running = 0;
            break;
        }

        if (!attendance_system.hidden_mode && strcmp(attendance_system.current_id, "hidden") == 0) {
            attendance_system.hidden_mode = 1;
            printf("Hidden mode activated.\n");
            continue;
        }

        if (attendance_system.hidden_mode) {
            if (strcmp(attendance_system.current_id, "unhide") == 0) {
                attendance_system.hidden_mode = 0;
                printf("Hidden mode deactivated.\n");
                continue;
            }
            if (strcmp(attendance_system.current_id, "update-time") == 0) {
                _tzset();
                printf("Time updated.\n");
                continue;
            }
        }

        if (strcmp(attendance_system.current_id, "add") == 0) {
            add_user_manager.add_new_user();
            continue;
        }

        if (strcmp(attendance_system.current_id, "delete") == 0) {
            delete_user_manager.delete_user_by_id();
            continue;
        }

        UserType type = id_pattern_matcher.detect_user_type(attendance_system.current_id);
        if (type == USER_UNKNOWN) {
            printf("Invalid ID pattern.\n");
            continue;
        }

        if (!id_validator.validate_id(attendance_system.current_id, type)) {
            printf("ID not found in list.\n");
            continue;
        }

        // Update current user info
        strcpy(attendance_system.current_user.id, attendance_system.current_id);
        attendance_system.current_user.type = type;

        output_manager.record_attendance(attendance_system.current_id, type);
    }
}

AttendanceSystem attendance_system = {
    .current_id = {0},
    .hidden_mode = 0,
    .system_running = 0,
    .current_user = {{0}, {0}, USER_UNKNOWN},
    .run_attendance_system = run_attendance_system_impl
};
