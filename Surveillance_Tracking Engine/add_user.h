#ifndef add_user_h
#define add_user_h
#include "user_type.h"
#include "utils.h"

/**
 * @struct AddUserManager
 * @brief Manager structure for handling user addition operations
 *
 * This structure encapsulates all the necessary components for adding new users
 * to the system, including user data, authentication, and the addition function.
 */
typedef struct {
    User new_user;              /**< New user data to be added to the system */
    AdminAuth auth;             /**< Administrative authentication credentials */
    int (*add_new_user)(void);  /**< Function pointer to add new user operation */
} AddUserManager;

extern AddUserManager add_user_manager;
#endif
