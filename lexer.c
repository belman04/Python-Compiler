#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

// function that takes a line of text and processes it for tokens
void tokenize_line(const char* line){
    char copy[256]; // a character array to hold a copy of the line
    // strcpy is a function to copy a string from one location to another, in this case, from line to copy
    strcpy(copy, line); 

    // strtok is a function to split a string into tokens based on delimiters, in this case, spaces, newlines, and tabs
    char* token = strtok(copy, " \n\t"); 

    // a loop to iterate through each token in the line
    while(token != NULL){ // 
        printf("Token: %s\n", token); 
        token = strtok(NULL, " \n\t"); // 
    }
}