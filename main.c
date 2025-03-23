#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "directory.h"

// Need to create root directory as part of main
// IMPORTANT! These use the POINTER values of the folders/directories as params
// This means NOT passing string of name directly in. 
// May want to make a method for that.

int main(int argc, char * * argv)
{
    int size = 4;
    Directory * root = createRoot(size);

    // Example code
    Directory * firstFolder = createDirectory("First", root);
    File * firstFile = createFile("My first file", 25, firstFolder);

    EXIT_SUCCESS;
}
