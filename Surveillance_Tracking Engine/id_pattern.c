#include "id_pattern.h"
#include <string.h>

static UserType detect_user_type_impl(const char *id) {
    size_t len = strlen(id);
    if (strchr(id, '-') && len >= 13 && len <= 13) return USER_STUDENT;
    if (strstr(id, "@gmail.com")) return USER_TEACHER;
    if (strncmp(id, "admin", 5) == 0) return USER_ADMIN;
    return USER_UNKNOWN;
}

IdPatternMatcher id_pattern_matcher = {
    .pattern = {0},
    .detected_type = USER_UNKNOWN,
    .detect_user_type = detect_user_type_impl
};
