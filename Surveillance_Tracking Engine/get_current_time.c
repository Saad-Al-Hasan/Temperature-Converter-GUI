#include "get_current_time.h"
#include <time.h>
#include <string.h>

// Helper function (internal use only)
static void pack_to_bitfield(struct tm *t, CompactDateTime *dt) {
    *dt = (CompactDateTime){
        .year   = t->tm_year + 1900,
        .month  = t->tm_mon + 1,
        .day    = t->tm_mday,
        .hour   = t->tm_hour,
        .minute = t->tm_min
    };
}

static void get_current_time_impl(char *date_str, char *time_str, char *datetime_console) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    // Store in bitfield
    pack_to_bitfield(t, &time_manager.compact_time);

    // Format strings
    strftime(date_str, 20, "%d.%m.%Y", t);
    strftime(time_str, 15, "%I:%M:%S%p", t);
    strftime(datetime_console, 40, "[%d.%m.%Y %I:%M:%S%p]", t);

    // Update internal storage
    strcpy(time_manager.date_str, date_str);
    strcpy(time_manager.time_str, time_str);
    strcpy(time_manager.datetime_console, datetime_console);
}

TimeManager time_manager = {
    .date_str = {0},
    .time_str = {0},
    .datetime_console = {0},
    .compact_time = {0},
    .get_current_time = get_current_time_impl
};
