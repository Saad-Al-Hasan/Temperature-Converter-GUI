#ifndef utils_h
#define utils_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include "user_type.h"

#define MAX_ID_LEN 64
#define STUDENT_LIST_FILE "student_list.txt"
#define TEACHER_LIST_FILE "teacher_list.txt"
#define ADMIN_LIST_FILE   "admin_list.txt"
#define STUDENT_LOG_FILE "student_attendance_log.txt"
#define TEACHER_LOG_FILE "teacher_attendance_log.txt"
#define ADMIN_LOG_FILE   "admin_attendance_log.txt"
#define STUDENT_DIR "students/"
#define TEACHER_DIR "teachers/"
#define ADMIN_DIR   "admins/"


/**
 * @struct AdminAuth
 * @brief Structure for administrator authentication
 *
 * This structure stores authentication credentials and status for
 * administrative operations in the system.
 */
typedef struct {
    char password[100];     /**< Administrative password */
    int is_authenticated;   /**< Authentication status flag (1 if authenticated, 0 otherwise) */
} AdminAuth;


/**
 * @struct UtilsInterface
 * @brief Interface structure for utility functions
 *
 * This structure provides function pointers to various utility operations
 * that can be used throughout the application for common string and data
 * manipulation tasks.
 */
typedef struct {
    void (*trim_newline)(char *str);    /**< Function pointer to trim newline characters from strings */
} UtilsInterface;

extern UtilsInterface utils;

#endif
