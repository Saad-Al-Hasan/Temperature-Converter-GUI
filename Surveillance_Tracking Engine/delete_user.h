#ifndef delete_user_h
#define delete_user_h
#include "user_type.h"
#include "utils.h"

/**
 * @struct DeleteUserManager
 * @brief Manager structure for handling user deletion operations
 *
 * This structure encapsulates all the necessary components for deleting users
 * from the system, including target identification, authentication, and the deletion function.
 */
typedef struct {
    char target_id[64];              /**< Target user ID to be deleted from the system */
    UserType target_type;            /**< Type of the target user (admin, faculty, student) */
    AdminAuth auth;                  /**< Administrative authentication credentials */
    int (*delete_user_by_id)(void);  /**< Function pointer to delete user operation */
} DeleteUserManager;

extern DeleteUserManager delete_user_manager;

#endif
