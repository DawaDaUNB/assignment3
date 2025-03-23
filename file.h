#ifndef FILE_H
#define FILE_H
#include "directory.h"

typedef struct File {
    char * name;
    float size;
    Directory * parent;
 } File;

File * createFile(char * name, float size, Directory *parent);

#endif