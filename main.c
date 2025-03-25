#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "directory.h"

// Need to create root directory as part of main
// IMPORTANT! These use the POINTER values of the folders/directories as params
// This means NOT passing string of name directly in. 
// May want to make a method for that.

int main(int argc, char **argv)
{
    Directory *root = createRoot(4);

    // Build structure: root/First/Second/Third
    Directory *first = createDirectory("First", root);
    Directory *second = createDirectory("Second", first);
    Directory *third = createDirectory("Third", second);

    // Add some files
    createFile("readme.txt", 5.5, first);
    createFile("notes.doc", 12.2, second);
    createFile("image.png", 45.0, third);

    // Test valid path
    Directory *found = findDirectoryByPath(root, "First/Second/Third");
    if (found) {
        printf("Found directory: %s\n", found->name);
    } else {
        printf("Directory not found\n");
    }

    // Test invalid path
    // Find these at the last section of the function.c file
    found = findDirectoryByPath(root, "First/Fake");
    if (found) {
        printf("Found directory: %s\n", found->name);
    } else {
        printf("Directory not found\n");
    }

    // Test listing contents from root
    printf("\nListing full directory structure from root:\n");
    listDirectory(root, 0);

    return EXIT_SUCCESS;
}
