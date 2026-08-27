#ifndef id_validation_h
#define id_validation_h
#include "user_type.h"

/**
 * @struct IdValidator
 * @brief Validator structure for ID validation operations
 *
 * This structure manages ID validation functionality, storing the ID to be validated,
 * the user type for validation context, validation results, and the validation function.
 */
typedef struct {
    char id_to_validate[64];                            /**< ID string to be validated (max 63 characters + null terminator) */
    UserType type_to_check;                             /**< User type context for validation rules */
    int is_valid;                                       /**< Validation result flag (1 for valid, 0 for invalid) */
    int (*validate_id)(const char *id, UserType type);  /**< Function pointer to ID validation operation */
} IdValidator;

extern IdValidator id_validator;

#endif
