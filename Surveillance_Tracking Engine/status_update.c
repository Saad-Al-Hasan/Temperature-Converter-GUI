#include "status_update.h"
#include <stdio.h>
#include <string.h>

static void update_status_impl(const char *filename, const char *status) {
    // Update manager state
    strcpy(status_manager.filename, filename);
    strcpy(status_manager.current_status, status);

    FILE *file = fopen(filename, "r");
    if (!file) return;

    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        fclose(file);
        return;
    }

    char line[256];
    int updated = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "Status:", 7) == 0) {
            fprintf(temp, "Status: %s\n", status);
            updated = 1;
        } else {
            fputs(line, temp);
        }
    }

    if (!updated) {
        fprintf(temp, "Status: %s\n", status);
    }

    fclose(file);
    fclose(temp);
    remove(filename);
    rename("temp.txt", filename);
}

StatusManager status_manager = {
    .filename = {0},
    .current_status = {0},
    .update_status = update_status_impl
};
