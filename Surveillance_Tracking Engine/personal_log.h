#ifndef personal_log_h
#define personal_log_h
#include "user_type.h"

/**
 * @struct PersonalLogManager
 * @brief Manager structure for handling personal log operations
 *
 * This structure manages personal logging functionality including user information,
 * log file management, timestamp tracking, and log creation operations for different
 * types of users in the system.
 */
typedef struct {
    User user_info;                 /**< User information for the log owner */
    char log_filename[128];         /**< Filename for the personal log file */
    char current_date[20];          /**< Current date string for log entries */
    char current_time[15];          /**< Current time string for log entries */
    int is_entry;                   /**< Flag indicating if this is a log entry */
    void (*create_personal_log)(const char *id, const char *date_str, const char *time_str, int is_entry, UserType type);  /**< Function pointer to create personal log entries */
} PersonalLogManager;

extern PersonalLogManager personal_log_manager;

#endif
