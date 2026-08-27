#ifndef get_current_time_h
#define get_current_time_h
#include <stdint.h>


/**
 * @struct CompactDateTime
 * @brief Compact bit-field representation of date and time
 *
 * This structure uses bit fields to store date and time information
 * in a memory-efficient format using only 32 bits total.
 */
typedef struct {
    uint32_t year   : 12;  /**< Year value (0-4095) */
    uint32_t month  : 4;   /**< Month value (1-12) */
    uint32_t day    : 5;   /**< Day value (1-31) */
    uint32_t hour   : 5;   /**< Hour value (0-23) */
    uint32_t minute : 6;   /**< Minute value (0-59) */
} CompactDateTime;


/**
 * @struct TimeManager
 * @brief Manager structure for handling time operations and formatting
 *
 * This structure provides various time representations and functions
 * for retrieving and formatting current time information.
 */
typedef struct {
    char date_str[20];                /**< Formatted date string buffer */
    char time_str[15];                /**< Formatted time string buffer */
    char datetime_console[40];        /**< Console-formatted datetime string buffer */
    CompactDateTime compact_time;     /**< Compact bit-field time representation */
    void (*get_current_time)(char *date_str, char *time_str, char *datetime_console);  /**< Function pointer to retrieve current time */
} TimeManager;

extern TimeManager time_manager;

#endif
