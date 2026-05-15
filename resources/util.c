//util.c

#include "util.h"
#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

int getLen(char *str) {
    int len = 0;
    while (*(str + len) != '\0') {
        len++;
    }
    return len;
}

int compStr(char *str1, char *str2) {
    int i = 0;
    while (*(str1 + i) && *(str2 + i))
    {
        if (*(str1 + i) != *(str2 + i)) 
            return false;
        
        i++;
    }
    return *(str1 + i) == *(str2 + i);
}

void cpyStr(char *dest, const char *src) {
    if (dest == NULL || src == NULL) {
        return; // Handle null pointers gracefully
    }

    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0'; // Null-terminate the destination string
}

int powm(int bot, int top){
    if (bot == 0){
        return 0;
    }

    int result = 1;
    for (int i = 0; i < top; i++){
        result *= bot;
    }

    return result;
}

int s_strtoint(char* str){
    int i = 0;
    int result = 0;

    while (str[i] != '\0'){
        if (str[i] >= '0' && str[i] <= '9'){
            result = result * 10 + str[i] - '0';
        }
        else{
            return -1;
        }

        i++;
    }
    return result;
}

void freeInstructions(char** instructions, int iLen){
    //free the instructions
    for (int i = 0; i < iLen; i++){
        free(instructions[i]);
    }
    free(instructions);
}
