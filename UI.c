#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "directory.h"
#include "file.h"

// Function to print the menu
void printMenu() {
    printf("\n===== File System Menu =====\n");
    printf("1. Create a New Directory\n");
    printf("2. Create a New File\n");
    printf("3. List Directory Contents\n");
    printf("4. Search for an Item\n");
    printf("5. Exit\n");
    printf("Please select an option (1-5): ");
}

// Function to handle creating a new directory
void createNewDirectory(Directory *root) {
    char parentPath[256];
    char dirName[256];

    printf("Enter the name of the new directory: ");
    scanf("%s", dirName);

    printf("Enter the path of the parent directory (e.g., 'root' for root): ");
    scanf("%s", parentPath);

    Directory *parentDir = findDirectoryByPath(root, parentPath);
    if (!parentDir) {
        printf("Error: Parent directory '%s' not found.\n", parentPath);
        return;
    }

    // Create the new directory under the parent directory
    createDirectory(dirName, parentDir);
    printf("Directory '%s' created under '%s'.\n", dirName, parentPath);
}

// Function to handle creating a new file
void createNewFile(Directory *root) {
    char parentPath[256];
    char fileName[256];
    float fileSize;

    printf("Enter the name of the new file: ");
    scanf("%s", fileName);

    printf("Enter the size of the file (in KB): ");
    scanf("%f", &fileSize);

    printf("Enter the path of the parent directory (e.g., 'root' for root): ");
    scanf("%s", parentPath);

    Directory *parentDir = findDirectoryByPath(root, parentPath);
    if (!parentDir) {
        printf("Error: Parent directory '%s' not found.\n", parentPath);
        return;
    }

    // Create the new file under the parent directory
    createFile(fileName, fileSize, parentDir);
    printf("File '%s' created under '%s'.\n", fileName, parentPath);
}

// Function to list the contents of a directory
void listDirectoryContents(Directory *root) {
    char path[256];

    printf("Enter the path of the directory to list (e.g., 'root' for root): ");
    scanf("%s", path);

    Directory *dir = findDirectoryByPath(root, path);
    if (!dir) {
        printf("Error: Directory '%s' not found.\n", path);
        return;
    }

    // List the directory contents
    printf("\nListing contents of directory '%s':\n", path);
    listDirectory(dir, 0);
}

// Function to search for a file or directory
void searchForItem(Directory *root) {
    char target[256];
    printf("Enter the name of the item to search for: ");
    scanf("%s", target);

    Directory *found = findDirectoryByPath(root, target);
    if (found) {
        printf("Found directory: %s\n", found->name);
    } else {
        printf("Directory '%s' not found.\n", target);
    }
}

// Function to handle invalid input and restart the menu loop
void handleInvalidInput() {
    while (getchar() != '\n'); // clear the input buffer
    printf("Invalid input. Please enter a number between 1 and 5.\n");
}

int main(int argc, char **argv) {
    Directory *root = createRoot(4);

    // Build some initial structure for testing
    Directory *first = createDirectory("First", root);
    Directory *second = createDirectory("Second", first);
    Directory *third = createDirectory("Third", second);

    createFile("readme.txt", 5.5, first);
    createFile("notes.doc", 12.2, second);
    createFile("image.png", 45.0, third);

    int choice;
    while (1) {
        printMenu();

        if (scanf("%d", &choice) != 1) {
            handleInvalidInput();
            continue;
        }

        switch (choice) {
            case 1:
                createNewDirectory(root);
                break;
            case 2:
                createNewFile(root);
                break;
            case 3:
                listDirectoryContents(root);
                break;
            case 4:
                searchForItem(root);
                break;
            case 5:
                printf("Exiting the program...\n");
                freeDirectory(root);
                return 0;
            default:
                handleInvalidInput();
        }
    }

    return 0;
}
