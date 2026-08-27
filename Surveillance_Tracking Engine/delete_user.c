#include "delete_user.h"
#include "encapsulation_process.h"
#include "id_pattern.h"
#include "trim_newline.h"
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LEN 256
#define PASSWORD_FILE "admin_pass.txt"
#define MAX_PASSWORD_LEN 100

static int delete_user_by_id_impl(void) {
    char password[MAX_PASSWORD_LEN];

    // Read stored password
    FILE *pf = fopen(PASSWORD_FILE, "r");
    if (!pf) {
        printf("Error: Could not open password file.\n");
        return 0;
    }
    char stored_password[MAX_PASSWORD_LEN];
    if (!fgets(stored_password, sizeof(stored_password), pf)) {
        printf("Error reading password.\n");
        fclose(pf);
        return 0;
    }
    string_trimmer.trim_newline(stored_password);
    fclose(pf);

    // Prompt for password
    printf("Enter admin password: ");
    secure_input.get_hidden_input(password, sizeof(password));
    string_trimmer.trim_newline(password);

    if (strcmp(password, stored_password) != 0) {
        printf("Incorrect password. Access denied.\n");
        return 0;
    }

    delete_user_manager.auth.is_authenticated = 1;
    printf("\nAdministrator Verified.\n\n");

    int choice;
    printf("What type of user to delete?\n");
    printf("1. Student\n2. Faculty\n3. Admin\n");
    printf("Enter choice (1-3): ");
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return 0;
    }
    getchar(); // Clear newline

    const char *filename = NULL;
    switch (choice) {
        case 1:
            filename = "student_list.txt";
            delete_user_manager.target_type = USER_STUDENT;
            break;
        case 2:
            filename = "teacher_list.txt";
            delete_user_manager.target_type = USER_TEACHER;
            break;
        case 3:
            filename = "admin_list.txt";
            delete_user_manager.target_type = USER_ADMIN;
            break;
        default:
            printf("Invalid choice.\n");
            return 0;
    }

    printf("Enter ID to delete: ");
    if (fgets(delete_user_manager.target_id, sizeof(delete_user_manager.target_id), stdin) == NULL) {
        printf("Error reading ID.\n");
        return 0;
    }
    string_trimmer.trim_newline(delete_user_manager.target_id);

    // Validate ID pattern
    UserType detected_type = id_pattern_matcher.detect_user_type(delete_user_manager.target_id);
    if (detected_type == USER_UNKNOWN) {
        printf("Invalid ID pattern.\n");
        return 0;
    }

    // Prepare temp file for safe update
    FILE *original = fopen(filename, "r");
    if (!original) {
        perror("Failed to open original file");
        return 0;
    }
    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        perror("Failed to open temporary file");
        fclose(original);
        return 0;
    }

    char line[MAX_LINE_LEN];
    int found = 0;
    while (fgets(line, sizeof(line), original)) {
        char id_in_line[MAX_ID_LEN];
        sscanf(line, "%s", id_in_line);
        if (strcmp(id_in_line, delete_user_manager.target_id) != 0) {
            fputs(line, temp);
        } else {
            found = 1;
        }
    }
    fclose(original);
    fclose(temp);

    if (!found) {
        printf("ID not found. Nothing deleted.\n");
        remove("temp.txt");
        return 0;
    }

    // Overwrite original file
    remove(filename);
    rename("temp.txt", filename);
    printf("User ID %s deleted successfully from %s.\n", delete_user_manager.target_id, filename);
    return 1;
}

DeleteUserManager delete_user_manager = {
    .target_id = {0},
    .target_type = USER_UNKNOWN,
    .auth = {{0}, 0},
    .delete_user_by_id = delete_user_by_id_impl
};
