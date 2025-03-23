#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "directory.h"

void checkAndResizeFileSpace(Directory *parent);
void checkAndResizeDirectorySpace(Directory *parent);
void addDToParent(Directory *parent, Directory *child);
void addFToParent(Directory *parent, File *file);

// Need to create root directory as part of main
// IMPORTANT! These use the POINTER values of the folders/directories as params
// This means NOT passing string of name directly in. 
// May want to make a method for that.

// Create the initial root directory for easy naming and keeping track
// Can rewrite this to take in a name if you want
Directory * createRoot(int size) {
    Directory * directory = (Directory *)malloc(sizeof(Directory));
    if (!directory) {
        printf("Failed to create directory\n");
        exit(1);
    }
    directory -> name = "root";
    directory -> parent = NULL;
    // Create pointer list of what will be child directories
    directory -> directories = (Directory **)malloc(size * sizeof(Directory*));
    if (!directory->directories) {
        printf("Failed to create directories\n");
        exit(1);
    }
    // Initialize them to NULL
    for (int i =0; i < size; i++) {
        directory->directories[i] = NULL;
    }
    directory -> files = (File **)malloc(size * sizeof(File*));
    if (!directory->files) {
        printf("Failed to create files\n");
        exit(1);
    }
    // Initialize them to NULL
    for (int i =0; i < size; i++) {
        directory->files[i] = NULL;
    }
    directory -> capacityDirectories = size;
    directory -> capacityFiles = size;
    return directory;
}

// This doesn't have full memory handling yet in case of failure, no 'free' or skip
// Ideally need to add a 'success/fail' on new allocation to pass back to 
// calling create so it can free what it created
void checkAndResizeDirectorySpace(Directory *parent) {
    // check how many things are already in its directories array
    // if full, increase size
    
    // If space, just go back, otherwise it continues
    for (int i = 0; i < parent->capacityDirectories; i++) {
        if (parent->directories[i] == NULL) {
            // Found a free spot, no need to resize
            return;
        }
    }

    int newSize = parent->capacityDirectories + 4;
    struct Directory ** newDirectories = (struct Directory **)realloc(parent->directories, newSize * sizeof(struct Directory*)); 
    if (newDirectories==NULL) {
        printf("Failed to allocate more space in directory list\n");
        exit(1);
    }

    parent->directories = newDirectories;
    //Initialize the new ones to NULL
    for (int i = parent->capacityDirectories; i < newSize; i++){
        parent->directories[i] = NULL;
    } 

    parent->capacityDirectories = newSize;
}

void checkAndResizeFileSpace(Directory *parent){
    // check how many things are already in its files array
    // If space, just go back, otherwise it continues
    for (int i = 0; i < parent->capacityFiles; i++) {
        if (parent->files[i] == NULL) {
            // Found a free spot, no need to resize
            return;
        }
    }

    int newSize = parent->capacityFiles + 4;
    struct File ** newFiles = (struct File **)realloc(parent->files, newSize * sizeof(struct File*)); 
    if (newFiles==NULL) {
        printf("Failed to allocate more space in files list\n");
        exit(1);
    }

    parent->files = newFiles;
    //Initialize the new ones to NULL
    for (int i = parent->capacityFiles; i < newSize; i++){
        parent->files[i] = NULL;
    } 

    parent->capacityFiles = newSize;
}


// Create Directory, passing in pointer to parent directory
Directory * createDirectory(char * name, Directory *parent) {
    // make the new directory
    Directory * directory = (Directory *)malloc(sizeof(Directory));
    if (!directory) {
        printf("Failed to create directory\n");
        exit(1);
    }

    // initialize its list of directories, using the current size of parent
    directory -> directories = (Directory **)malloc(parent->capacityDirectories * sizeof(Directory*));    
    if (!directory->directories) {
        printf("Failed to create directories\n");
        free(directory);
        exit(1);
    }
    // Initialize them to NULL
    for (int i =0; i < parent->capacityDirectories; i++) {
        directory->directories[i] = NULL;
    }

    // initialize its list of files, using the current size of parent
    directory -> files = (File **)malloc(parent->capacityFiles * sizeof(File*));    
     if (!directory->files) {
        printf("Failed to create files\n");
        free(directory);
        exit(1);
    }
    // Initialize them to NULL
    for (int i =0; i < parent->capacityFiles; i++) {
        directory->files[i] = NULL;
    }

    // Set rest of variables
    directory -> name = name;
    directory -> parent = parent;
    directory->capacityDirectories=parent->capacityDirectories;
    directory->capacityFiles=parent->capacityFiles;

    // Add it to the parent directory's directory list
    addDToParent(parent, directory);
    return directory;
}

// Create a file, passing in pointer of directory
File * createFile(char * name, float size, Directory *parent) {
    File * file = (File*)malloc(sizeof(File));
    if (!file) {
        printf("Failed to create file\n");
        exit(1);
    }
    file -> name = name;
    file -> parent = parent;
    file -> size = size;
    // Method to link File to directory
    addFToParent(parent, file);
    return file;
}

// Add to parent (directory), needs to check for size allocation and realloc when needed
void addDToParent(Directory *parent, Directory *child) {
    // First check existence, create error msg if needed
    if (!parent) {
        printf("Parent directory does not exist. Try again and choose one that does.\n");
        // If cannot assign it, free it and prompt to try again
        free(child->name);
        free(child->directories);
        free(child->files);
        free(child);
    }
    // Check size, and realloc to be larger if needed
    checkAndResizeDirectorySpace(parent);
    
   // Add it to first available spot in current pointer array
    for (int i = 0; i < parent->capacityDirectories; i++) {
        if (parent->directories[i] == NULL) {
            parent->directories[i] = child;
            printf("I added the folder %s to the folder %s\n", child->name, parent->name);
            return;
        }
    }
}

void addFToParent(Directory *parent, File *file){
    // Need to add to 'files' of parent
    // First check existence, create error msg if needed
    if (!parent) {
        printf("Parent directory does not exist\n");
        free(file->name);
        free(file);
    }

    // Ccheck size, and realloc to be larger if needed
    checkAndResizeFileSpace(parent);

    // Add it to first available spot in current pointer array
    for (int i = 0; i < parent->capacityFiles; i++) {
        if (parent->files[i] == NULL) {
            parent->files[i] = file;
            printf("I added the file %s to the folder %s\n", file->name, parent->name);
            return;
        }
    }
}