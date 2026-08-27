#ifndef date_recheck_h
#define date_recheck_h
#include <stdio.h>

/**
 * @struct DateChecker
 * @brief Structure for checking date existence in files
 *
 * This structure provides functionality to verify if a specific date exists
 * within a file, encapsulating the target date, file pointer, and check function.
 */
typedef struct {
    char target_date[20];                                           /**< Target date string to search for (max 19 chars + null terminator) */
    FILE *file_ptr;                                                 /**< File pointer for the file to be searched */
    int (*check_date_exists)(FILE *file, const char *date_str);     /**< Function pointer to check if date exists in file */
} DateChecker;

extern DateChecker date_checker;
#endif
