#ifndef id_pattern_h
#define id_pattern_h
#include "user_type.h"

/**
 * @struct IdPatternMatcher
 * @brief Pattern matcher for detecting user types based on ID format
 *
 * This structure provides functionality to analyze ID patterns and automatically
 * detect the corresponding user type based on predefined pattern matching rules.
 */
typedef struct {
    char pattern[64];                                   /**< Pattern string used for ID matching (max 63 chars + null terminator) */
    UserType detected_type;                             /**< The user type detected from the last pattern match */
    UserType (*detect_user_type)(const char *id);      /**< Function pointer to detect user type from given ID string */
} IdPatternMatcher;

extern IdPatternMatcher id_pattern_matcher;

#endif
