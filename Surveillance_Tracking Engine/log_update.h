#ifndef log_update_h
#define log_update_h
#include "user_type.h"

/**
 * @struct LogManager
 * @brief Manager structure for handling user activity logging operations
 *
 * This structure manages all aspects of user activity logging, including tracking
 * current user sessions, managing timestamps, and providing logging functionality
 * for entry and exit operations.
 */
typedef struct {
    char last_logged_date[20];  /**< Last date when logging activity occurred */
    int date_initialized;       /**< Flag indicating if date has been initialized */
    User current_user;          /**< Currently active user data */
    char current_date[20];      /**< Current system date string */
    char current_time[15];      /**< Current system time string */
    int is_entry;               /**< Flag indicating if this is an entry (1) or exit (0) log */
    void (*update_log)(const char *id, const char *date_str, const char *time_str, int is_entry, UserType type);  /**< Function pointer to update log with user activity */
} LogManager;

extern LogManager log_manager;

#endif
