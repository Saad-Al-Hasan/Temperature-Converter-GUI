#ifndef output_window_h
#define output_window_h
#include "user_type.h"

/**
 * @struct OutputManager
 * @brief Manager structure for handling output window operations and attendance recording
 *
 * This structure manages the output display functionality, including current user information,
 * display messages, and attendance recording operations for the system interface.
 */
typedef struct {
    User current_user;                                          /**< Currently active user in the system */
    char display_message[256];                                  /**< Buffer for storing display messages */
    void (*record_attendance)(const char *id, UserType type);  /**< Function pointer to record user attendance */
} OutputManager;

extern OutputManager output_manager;

#endif
