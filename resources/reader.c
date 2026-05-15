//reader.c

#include <stdio.h>
#include <stdlib.h>
#include "..\headers\reader.h"
#include "..\headers\util.h"
#include "..\headers\vmemu.h"

#define MAX_LINE_LENGTH 256

void processFile(FILE *file) {
    int tokenCount = 0;
    int tokenCap = 32;
    
    char** tokenAddresses = malloc(tokenCap * sizeof(char*));
    if (!tokenAddresses) {
    fprintf(stderr, "malloc fail");
    exit(1);
    }

    char opcode[11] = {0};
    int i = 0; //for opcode

    char c = fgetc(file);
    while (c != EOF)
    {
        if (c == '\n')
        {
            c = ' ';
        }

        if (c == '#'){
            while (
                c != '\n' &&
                c != EOF
            )
            c = fgetc(file);
            continue;
        }

        if (c == ' ') {
            if (i > 0){
                tokenAddresses[tokenCount] = malloc((getLen(opcode) + 1) * sizeof(char) + 1);

                cpyStr(tokenAddresses[tokenCount], opcode);

                tokenCount++;
            }
            opcode[0] = '\0';
            i = 0;
        }

        else{
            if (i < 10)
                opcode[i++] = c;
            opcode[i] = '\0';
        }
        
        if (tokenCount == tokenCap){
            tokenCap *= 2;
            char** tmp = realloc(tokenAddresses, tokenCap * sizeof(char*));

            if (!tmp){
                free(tokenAddresses);
                fprintf(stderr, "Failed to create memory for token adresses");
                exit(1);
            }

            tokenAddresses = tmp;
        }

        c = fgetc(file);
    }
    // add the last op
    if (i > 0)
    {
        if (tokenCount == tokenCap){
            tokenCap *= 2;
            char** tmp = realloc(tokenAddresses, tokenCap * sizeof(char*));
            if (!tmp){
                free(tokenAddresses);
                fprintf(stderr, "Failed to create memory for token adresses");
                exit(1);
            }
            tokenAddresses = tmp;
        }

        tokenAddresses[tokenCount] = malloc((getLen(opcode) + 1) * sizeof(char));

        cpyStr(tokenAddresses[tokenCount], opcode);

        tokenCount++;
    }
    
    parseAndExecute(tokenAddresses, tokenCount);

    fclose(file);
    return;
}