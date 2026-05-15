//main.c

#include <stdio.h>
#include <stdlib.h>
#include "./headers/util.h"
#include "./headers/reader.h"

#define true 1
#define false 0

int validateArgs(int argc, char *argv[]) {
        //--------------------- Argument Validation ---------------------//
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filepath>\n", argv[0]);
        return false;
    }
    if (argc > 2) {
        fprintf(stderr, "Too many arguments provided. Only one file path is expected.\n");
        return false;
    }
    return true;
}

void exitWithError(const char *message, void* ptr) {
    fprintf(stderr, "%s\n", message);
    free(ptr);
    exit(1);
}

int main(int argc, char *argv[]) {

    if (!validateArgs(argc, argv)) {
        return 1;
    }
    // Get the file path from command line arguments
    char *filepathraw = argv[1];
   
    // Get the length of the file path
    int len = getLen(filepathraw);
    // Validate file name length for .cnn extension
    if (len < 4) {
        exitWithError("File name too short", NULL);
    }

    //allocating memory for the file path
    char* filepath = malloc(sizeof(char) * (len + 1)); // +1 for the null terminator
    
    //check if memory allocation was successful
    if (filepath == NULL) {
        exitWithError("Memory allocation failed", NULL);
    }

    //save start of filepath to free later
    char* filestart = filepath;
    
    //saving file path from command line argument
    while (*filepathraw != '\0') {
        *filepath = *filepathraw;
        filepath++;
        filepathraw++;
    }
    *filepath = '\0';
    
    // Validate file extension
    if (!compStr(filestart + len - 4, ".cnn") &&
        !compStr(filestart + len - 4, ".cvm")) {
        exitWithError("Invalid file extension", filestart);
    }
    // Open the file for reading
    FILE *file = fopen(filestart, "r");
    if (file == NULL) {
        exitWithError("Could not open file", filestart);
    }

    //process the file here
    processFile(file);

    return 0;
}
