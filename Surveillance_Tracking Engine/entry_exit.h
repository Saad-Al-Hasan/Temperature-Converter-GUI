#ifndef entry_exit_h
#define entry_exit_h
#include "user_type.h"

/**
 * @struct EntryExitTracker
 * @brief Tracker structure for monitoring user entry and exit activities
 *
 * This structure maintains tracking information for user access control,
 * including entry/exit counts and status verification functionality.
 */
typedef struct {
    char user_id[64];                                               /**< Unique identifier for the user being tracked */
    UserType user_type;                                             /**< Type/category of the user (admin, faculty, student) */
    int entry_count;                                                /**< Number of times user has entered the system */
    int exit_count;                                                /**< Number of times user has exited the system */
    int (*check_user_status)(const char *id, UserType type);       /**< Function pointer to verify user status and permissions */
} EntryExitTracker;

extern EntryExitTracker entry_exit_tracker;

#endif
