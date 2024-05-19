#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENTRIES 100
#define MAX_STRING 256

typedef struct {
    char website[MAX_STRING];
    char username[MAX_STRING];
    char password[MAX_STRING];
} PasswordEntry;

PasswordEntry entries[MAX_ENTRIES];
int entry_count = 0;

void add_password() {
    if (entry_count >= MAX_ENTRIES) {
        printf("Max entries reached!\n");
        return;
    }
    
    printf("Enter website: ");
    scanf("%s", entries[entry_count].website);
    
    printf("Enter username: ");
    scanf("%s", entries[entry_count].username);
    
    printf("Enter password: ");
    scanf("%s", entries[entry_count].password);
    
    entry_count++;
    printf("Password added successfully!\n");
}

void view_passwords() {
    if (entry_count == 0) {
        printf("No entries to display.\n");
        return;
    }
    
    for (int i = 0; i < entry_count; i++) {
        printf("Entry %d:\n", i + 1);
        printf("Website: %s\n", entries[i].website);
        printf("Username: %s\n", entries[i].username);
        printf("Password: %s\n", entries[i].password);
        printf("\n");
    }
}

void save_passwords(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file for writing.\n");
        return;
    }
    
    for (int i = 0; i < entry_count; i++) {
        fprintf(file, "%s %s %s\n", entries[i].website, entries[i].username, entries[i].password);
    }
    
    fclose(file);
    printf("Passwords saved to %s successfully!\n", filename);
}

void load_passwords(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file for reading.\n");
        return;
    }
    
    entry_count = 0;
    while (fscanf(file, "%s %s %s", entries[entry_count].website, entries[entry_count].username, entries[entry_count].password) == 3) {
        entry_count++;
        if (entry_count >= MAX_ENTRIES) {
            break;
        }
    }
    
    fclose(file);
    printf("Passwords loaded from %s successfully!\n", filename);
}

int main() {
    int choice;
    const char *filename = "passwords.txt";
    
    do {
        printf("\nPassword Manager Menu:\n");
        printf("1. Add a new password\n");
        printf("2. View passwords\n");
        printf("3. Save passwords to file\n");
        printf("4. Load passwords from file\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                add_password();
                break;
            case 2:
                view_passwords();
                break;
            case 3:
                save_passwords(filename);
                break;
            case 4:
                load_passwords(filename);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
    
    return 0;
}
