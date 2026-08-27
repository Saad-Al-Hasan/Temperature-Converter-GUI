#ifndef user_type_h
#define user_type_h

/**
 * @enum UserType
 * @brief Enumeration of different user types in the system
 *
 * Defines the various types of users that can exist in the system,
 * from unknown users to administrators with different privilege levels.
 */
typedef enum {
    USER_UNKNOWN,   /**< Unknown or unidentified user type */
    USER_STUDENT,   /**< Student user with basic privileges */
    USER_TEACHER,   /**< Teacher/Faculty user with elevated privileges */
    USER_ADMIN      /**< Administrator user with full system access */
} UserType;


/**
 * @struct User
 * @brief Core user data structure
 *
 * Contains the essential information for representing a user in the system,
 * including identification, name, and user type classification.
 */
typedef struct {
    char id[64];        /**< Unique user identifier (max 63 characters + null terminator) */
    char name[100];     /**< User's full name (max 99 characters + null terminator) */
    UserType type;      /**< Classification of user type and privileges */
} User;

#endif
