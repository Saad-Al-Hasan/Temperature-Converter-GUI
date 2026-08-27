#include "add_user.h"
#include "encapsulation_process.h"
#include "id_pattern.h"
#include "trim_newline.h"
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LEN 256
#define PASSWORD_FILE "admin_pass.txt"
#define MAX_PASSWORD_LEN 100

static int add_new_user_impl(void) {
    char password[MAX_PASSWORD_LEN];

    // Initialize auth structure
    add_user_manager.auth.is_authenticated = 0;

    // Open and read the stored password
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

    // Prompt for password from user
    printf("Enter admin password: ");
    secure_input.get_hidden_input(password, sizeof(password));
    string_trimmer.trim_newline(password);

    if (strcmp(password, stored_password) != 0) {
        printf("Incorrect password. Access denied.\n");
        return 0;
    }

    add_user_manager.auth.is_authenticated = 1;
    printf("\nAdministrator Detected.\n\n");

    int choice;
    printf("What type of user?\n");
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
            add_user_manager.new_user.type = USER_STUDENT;
            break;
        case 2:
            filename = "teacher_list.txt";
            add_user_manager.new_user.type = USER_TEACHER;
            break;
        case 3:
            filename = "admin_list.txt";
            add_user_manager.new_user.type = USER_ADMIN;
            break;
        default:
            printf("Invalid choice.\n");
            return 0;
    }

    // ID input
    printf("Enter new ID: ");
    if (fgets(add_user_manager.new_user.id, sizeof(add_user_manager.new_user.id), stdin) == NULL) {
        printf("Error reading ID.\n");
        return 0;
    }
    string_trimmer.trim_newline(add_user_manager.new_user.id);

    // Validate ID pattern
    UserType detected_type = id_pattern_matcher.detect_user_type(add_user_manager.new_user.id);
    if (detected_type == USER_UNKNOWN) {
        printf("Invalid ID pattern.\n");
        return 0;
    }

    // Cross-check detected type vs chosen type
    if (detected_type != add_user_manager.new_user.type) {
        printf("Pattern does not match selected user type.\n");
        return 0;
    }

    // Name input
    printf("Enter name (no spaces): ");
    if (fgets(add_user_manager.new_user.name, sizeof(add_user_manager.new_user.name), stdin) == NULL) {
        printf("Error reading name.\n");
        return 0;
    }
    string_trimmer.trim_newline(add_user_manager.new_user.name);

    // Check for existing ID
    FILE *check = fopen(filename, "r");
    if (check) {
        char line[MAX_LINE_LEN];
        while (fgets(line, sizeof(line), check)) {
            char existing_id[MAX_ID_LEN];
            sscanf(line, "%s", existing_id); // Only compare ID
            if (strcmp(existing_id, add_user_manager.new_user.id) == 0) {
                printf("ID already exists in the list.\n");
                fclose(check);
                return 0;
            }
        }
        fclose(check);
    }

    // Append new user
    FILE *file = fopen(filename, "a");
    if (!file) {
        perror("Failed to open file");
        return 0;
    }
    fprintf(file, "%s %s\n", add_user_manager.new_user.id, add_user_manager.new_user.name);
    fclose(file);

    printf("ID and name added successfully to %s.\n", filename);
    return 1;
}

AddUserManager add_user_manager = {
    .new_user = {{0}, {0}, USER_UNKNOWN},
    .auth = {{0}, 0},
    .add_new_user = add_new_user_impl
};
