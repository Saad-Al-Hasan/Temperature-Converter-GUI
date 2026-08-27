#ifndef surveillance_tracking_engine_h
#define surveillance_tracking_engine_h
#define MAX_ID_LEN 50
#include <stdio.h>
#include <string.h>
#include "user_type.h"

/**
 * @struct AttendanceSystem
 * @brief Main attendance tracking system structure
 *
 * This structure manages the core attendance tracking functionality including
 * user identification, system state control, and attendance processing operations.
 * It supports both visible and hidden mode operations for surveillance purposes.
 */
typedef struct {
    char current_id[MAX_ID_LEN];        /**< Current user ID being tracked (max 50 characters) */
    int hidden_mode;                    /**< Flag indicating if system is running in hidden mode */
    int system_running;                 /**< Flag indicating if the tracking system is active */
    User current_user;                  /**< Current user data structure being processed */
    void (*run_attendance_system)(void); /**< Function pointer to execute attendance tracking */
} AttendanceSystem;

extern AttendanceSystem attendance_system;

#endif
