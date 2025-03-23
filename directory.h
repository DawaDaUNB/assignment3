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
#endif