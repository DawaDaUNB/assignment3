#ifndef DIRECTORY_H
#define DIRECTORY_H

typedef struct File File;

typedef struct Directory {
    struct Directory ** directories;
    char * name;
    File ** files;
    struct Directory *parent;
    int capacityDirectories;
    int capacityFiles;
} Directory;

Directory * createDirectory(char * name, Directory *parent);
Directory * createRoot(int size);

// Function declarations for utilities
void printIndent(int depth);
void listDirectory(Directory *dir, int depth);
void searchDirectory(Directory *dir, const char *target, char *path);
void freeDirectory(Directory *dir);
Directory * findDirectoryByPath(Directory *root, const char *path);

#endif