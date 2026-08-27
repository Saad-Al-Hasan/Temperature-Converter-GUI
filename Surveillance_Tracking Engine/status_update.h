#ifndef status_update_h
#define status_update_h

/**
 * @struct StatusManager
 * @brief Manager structure for handling file status updates
 *
 * This structure manages status tracking for files, maintaining current status
 * information and providing functionality to update status values.
 */
typedef struct {
    char filename[128];                                                      /**< Name of the file being tracked */
    char current_status[10];                                                 /**< Current status of the file */
    void (*update_status)(const char *filename, const char *status);        /**< Function pointer to update file status */
} StatusManager;

extern StatusManager status_manager;

#endif
