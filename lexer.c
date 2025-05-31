#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

//types of tokens
typedef enum {
    TOKEN_IDENTIFIER, 
    TOKEN_NUMBER,
    TOKEN_STRING,

    // arithmetic operators
    TOKEN_ADD,
    TOKEN_SUB,
    TOKEN_MUL,
    TOKEN_DIV,
    TOKEN_INT_DIV,   

    // assignment operators
    TOKEN_ASSIGN,
    TOKEN_ADD_ASSIGN,
    TOKEN_SUB_ASSIGN,
    TOKEN_MUL_ASSIGN,
    TOKEN_DIV_ASSIGN,
    TOKEN_INT_DIV_ASSIGN,
    
    // comparison operators
    TOKEN_GREATER_THAN,
    TOKEN_LESS_THAN,
    TOKEN_EQUAL,
    TOKEN_NOT_EQUAL,
    TOKEN_GREATER_THAN_OR_EQUAL,
    TOKEN_LESS_THAN_OR_EQUAL,

    // logical operators
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_NOT,
    
    // functions
    TOKEN_PRINT,

    // control flow
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_WHILE,

    // punctuation
    TOKEN_COMMA,
    TOKEN_COLON,
    TOKEN_LEFT_PAREN,
    TOKEN_RIGHT_PAREN,
    TOKEN_LEFT_BRACKET,
    TOKEN_RIGHT_BRACKET,

    TOKEN_UNKNOWN

} tokenType;


// a structure to hold a token
typedef struct{
    tokenType type; // the type of the token
    char value[64]; // the value of the token, a character array to hold the value
} token;

// a function to identify a token
token identify_token(char* input){
    token t;
    strcpy(t.value, input); // copy the word to the token value

    // check for control flow
    if(strcmp(input, "if") == 0){ // strcmp is a function to compare two strings
        t.type = TOKEN_IF; // set the token type to if
        return t; // return the token
    } else if(strcmp(input, "else") == 0){
        t.type = TOKEN_ELSE;
        return t; // return the token
    } else if(strcmp(input, "while") == 0){
        t.type = TOKEN_WHILE;
        return t; // return the token
    }

    // check for arithmetic operators
    if(strcmp(input, "+") == 0){ // strcmp is a function to compare two strings, it returns 0 if they are equal
        t.type = TOKEN_ADD; // set the token type to add
        return t; // return the token
    } else if(strcmp(input, "-") == 0){
        t.type = TOKEN_SUB;
        return t; // return the token
    } else if(strcmp(input, "*") == 0){
        t.type = TOKEN_MUL;
        return t; // return the token
    } else if(strcmp(input, "/") == 0){
        t.type = TOKEN_DIV;
        return t; // return the token
    } else if(strcmp(input, "//") == 0){
        t.type = TOKEN_INT_DIV;
        return t; // return the token
    }

    // check for assignment operators
    if(strcmp(input, "=") == 0){ // strcmp is a function to compare two strings
        t.type = TOKEN_ASSIGN; // set the token type to assign
        return t; // return the token
    } else if(strcmp(input, "+=") == 0){
        t.type = TOKEN_ADD_ASSIGN;
        return t; // return the token
    } else if(strcmp(input, "-=") == 0){
        t.type = TOKEN_SUB_ASSIGN;
        return t; // return the token
    } else if(strcmp(input, "*=") == 0){
        t.type = TOKEN_MUL_ASSIGN;
        return t; // return the token
    } else if(strcmp(input, "/=") == 0){
        t.type = TOKEN_DIV_ASSIGN;
        return t; // return the token
    } else if(strcmp(input, "//=") == 0){
        t.type = TOKEN_INT_DIV_ASSIGN;
        return t; // return the token
    }

    // check for comparison operators
    if(strcmp(input, ">") == 0){ // strcmp is a function to compare two strings
        t.type = TOKEN_GREATER_THAN; // set the token type to greater than
        return t; // return the token
    } else if(strcmp(input, "<") == 0){
        t.type = TOKEN_LESS_THAN;
        return t; // return the token
    } else if(strcmp(input, "==") == 0){
        t.type = TOKEN_EQUAL;
        return t; // return the token
    } else if(strcmp(input, "!=") == 0){
        t.type = TOKEN_NOT_EQUAL;
        return t; // return the token
    } else if(strcmp(input, ">=") == 0){
        t.type = TOKEN_GREATER_THAN_OR_EQUAL;
        return t; // return the token
    } else if(strcmp(input, "<=") == 0){
        t.type = TOKEN_LESS_THAN_OR_EQUAL;
        return t; // return the token
    }

    // check for logical operators
    if(strcmp(input, "and") == 0){ // strcmp is a function to compare two strings
        t.type = TOKEN_AND; // set the token type to and
        return t; // return the token
    } else if(strcmp(input, "or") == 0){
        t.type = TOKEN_OR;
        return t; // return the token
    } else if(strcmp(input, "not") == 0){
        t.type = TOKEN_NOT;
        return t; // return the token
    }

    // check for punctuation
    if(strcmp(input, ",") == 0){ // strcmp is a function to compare two strings
        t.type = TOKEN_COMMA; // set the token type to comma
        return t; // return the token
    } else if(strcmp(input, ":") == 0){
        t.type = TOKEN_COLON;
        return t; // return the token
    } else if(strcmp(input, "(") == 0){
        t.type = TOKEN_LEFT_PAREN;
        return t; // return the token
    } else if(strcmp(input, ")") == 0){
        t.type = TOKEN_RIGHT_PAREN;
        return t; // return the token
    } else if(strcmp(input, "[") == 0){
        t.type = TOKEN_LEFT_BRACKET;
        return t; // return the token
    } else if(strcmp(input, "]") == 0){
        t.type = TOKEN_RIGHT_BRACKET;
        return t; // return the token
    }

    // check for functions
    if(strcmp(input, "print") == 0){ // strcmp is a function to compare two strings
        t.type = TOKEN_PRINT; // set the token type to print
        return t; // return the token
    }

    // check if the input is a number
    if(isdigit(input[0])){ // isdigit is a function to check if a character is a digit    }
        t.type = TOKEN_NUMBER; // set the token type to number
        return t; // return the token
    }

    // check if the input is an identifier (a variable name)
    if(isalpha(input[0])){ // isalpha is a function to check if a character is an alphabetic character
        t.type = TOKEN_IDENTIFIER; // set the token type to identifier
        return t; // return the token
    }

    // check if the input is a string, strlen is a function to get the length of a string
    if(input[0] == '"' && input[strlen(input) - 1] == '"'){ // check if the first and last characters are double quotes
        t.type = TOKEN_STRING; // set the token type to string
        return t; // return the token
    }

    // if nothing matches, set the token type to unknown
    t.type = TOKEN_UNKNOWN;
    return t;
}

const char* token_type_to_string(tokenType type) {
    switch(type) {
        case TOKEN_IDENTIFIER: return "TOKEN_IDENTIFIER";
        case TOKEN_NUMBER: return "TOKEN_NUMBER";
        case TOKEN_STRING: return "TOKEN_STRING";
        case TOKEN_ADD: return "TOKEN_ADD";
        case TOKEN_SUB: return "TOKEN_SUB";
        case TOKEN_MUL: return "TOKEN_MUL";
        case TOKEN_DIV: return "TOKEN_DIV";
        case TOKEN_INT_DIV: return "TOKEN_INT_DIV";
        case TOKEN_ASSIGN: return "TOKEN_ASSIGN";
        case TOKEN_ADD_ASSIGN: return "TOKEN_ADD_ASSIGN";
        case TOKEN_SUB_ASSIGN: return "TOKEN_SUB_ASSIGN";
        case TOKEN_MUL_ASSIGN: return "TOKEN_MUL_ASSIGN";
        case TOKEN_DIV_ASSIGN: return "TOKEN_DIV_ASSIGN";
        case TOKEN_INT_DIV_ASSIGN: return "TOKEN_INT_DIV_ASSIGN";
        case TOKEN_GREATER_THAN: return "TOKEN_GREATER_THAN";
        case TOKEN_LESS_THAN: return "TOKEN_LESS_THAN";
        case TOKEN_EQUAL: return "TOKEN_EQUAL";
        case TOKEN_NOT_EQUAL: return "TOKEN_NOT_EQUAL";
        case TOKEN_GREATER_THAN_OR_EQUAL: return "TOKEN_GREATER_THAN_OR_EQUAL";
        case TOKEN_LESS_THAN_OR_EQUAL: return "TOKEN_LESS_THAN_OR_EQUAL";
        case TOKEN_AND: return "TOKEN_AND";
        case TOKEN_OR: return "TOKEN_OR";
        case TOKEN_NOT: return "TOKEN_NOT";
        case TOKEN_PRINT: return "TOKEN_PRINT";
        case TOKEN_IF: return "TOKEN_IF";
        case TOKEN_ELSE: return "TOKEN_ELSE";
        case TOKEN_WHILE: return "TOKEN_WHILE";
        case TOKEN_COMMA: return "TOKEN_COMMA";
        case TOKEN_COLON: return "TOKEN_COLON";
        case TOKEN_LEFT_PAREN: return "TOKEN_LEFT_PAREN";
        case TOKEN_RIGHT_PAREN: return "TOKEN_RIGHT_PAREN";
        case TOKEN_LEFT_BRACKET: return "TOKEN_LEFT_BRACKET";
        case TOKEN_RIGHT_BRACKET: return "TOKEN_RIGHT_BRACKET";
        case TOKEN_UNKNOWN: return "TOKEN_UNKNOWN";
        default: return "UNKNOWN_TOKEN";
    }
}

// function that takes a line of text and processes it for tokens
void tokenize_line(const char* line){
    char copy[256]; // a character array to hold a copy of the line

    // strcpy is a function to copy a string from one location to another, in this case, from line to copy
    strcpy(copy, line); 

    // ignore comments
    char* comment_start = strchr(copy, '#'); // strchr is a function to find the first occurrence of a character in a string
    if (comment_start != NULL){
        *comment_start = '\0'; // set the character at the comment start to null, effectively removing the comment
    }

    char* input = strtok(copy, " \n\t");

    // a loop to iterate through each token in the line
    while(input != NULL){ 
        token t = identify_token(input); // call the identify_token function to get the token
        printf("Token: %s, Type: %s\n", t.value, token_type_to_string(t.type));
        input = strtok(NULL, " \n\t"); // get the next token
    }
}