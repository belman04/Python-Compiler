#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"
#include "parser.h"

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
    } else if(strcmp(input, "elif") == 0){
        t.type = TOKEN_ELIF;
        return t; // return the tokem
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

    // check for assignment operator
    if(strcmp(input, "=") == 0){ // strcmp is a function to compare two strings
        t.type = TOKEN_ASSIGN; // set the token type to assign
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
    if(isalpha(input[0])){
        if (strcmp(input, "print") == 0) {
            t.type = TOKEN_PRINT;
            return t;
        }
        t.type = TOKEN_IDENTIFIER; 
        return t;
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
        case TOKEN_ELIF: return "TOKEN_ELIF";
        case TOKEN_COMMA: return "TOKEN_COMMA";
        case TOKEN_COLON: return "TOKEN_COLON";
        case TOKEN_LEFT_PAREN: return "TOKEN_LEFT_PAREN";
        case TOKEN_RIGHT_PAREN: return "TOKEN_RIGHT_PAREN";
        case TOKEN_LEFT_BRACKET: return "TOKEN_LEFT_BRACKET";
        case TOKEN_RIGHT_BRACKET: return "TOKEN_RIGHT_BRACKET";
        case TOKEN_UNKNOWN: return "TOKEN_UNKNOWN";
        default: return "Error: Unknown token type";
    }
}

// function that takes a line of text and processes it for tokens
void tokenize_line(const char* line, int line_number) {
    token tokens[MAX_TOKENS_PER_LINE]; // maximum of 100 tokens per line
    int token_index = 0; // index for the tokens array

    char token_buffer[MAX_TOKEN_LENGTH]; // buffer to hold the current token
    int index = 0; // index for the token buffer
    int i = 0; // index for the input line
    int in_string = 0; // flag to indicate if we are inside a string

    while (line[i] != '\0') { // while we haven't reached the end of the line
        char c = line[i]; // get the current character

        if (c == '#') break; // to ignore comments 

        if (in_string) { // if we are inside a string
            token_buffer[index++] = c; // add the character to the token buffer
            if (c == '"') { // if we reach the end of the string
                token_buffer[index] = '\0'; // we terminate the string
                token t = identify_token(token_buffer); // identify the token
                if (t.type == TOKEN_UNKNOWN) {
                    printf("Error: unknown token in line %d: %s", line_number, line);
                } else {
                    printf("Token: %s, Type: %s\n", t.value, token_type_to_string(t.type));
                    tokens[token_index++] = t; // store the token in the tokens array
                }
                index = 0; // reset the index
                in_string = 0; // reset the flag
            }
        } else if (isspace(c)) { // if the character is a whitespace
            if (index > 0) { // if we have a token in the buffer
                token_buffer[index] = '\0'; // terminate the token string
                token t = identify_token(token_buffer); // identify the token
                if (t.type == TOKEN_UNKNOWN) {
                    printf("Error: unknown token in line %d: %s", line_number, line);
                } else {
                    printf("Token: %s, Type: %s\n", t.value, token_type_to_string(t.type));
                    tokens[token_index++] = t; // store the token in the tokens array
                }
                index = 0;
            }
        } else if (c == '(' || c == ')' || c == ':' || c == ',') { // if the character is a punctuation mark
            if (index > 0) { // if we have a token in the buffer
                token_buffer[index] = '\0'; // terminate the token string
                token t = identify_token(token_buffer); // identify the token
                if (t.type == TOKEN_UNKNOWN) {
                    printf("Error: unknown token in line %d: %s", line_number, line);
                } else {
                    printf("Token: %s, Type: %s\n", t.value, token_type_to_string(t.type));
                    tokens[token_index++] = t; // store the token in the tokens array
                }
                index = 0; // reset the index
            }
            token_buffer[0] = c; // store the punctuation mark in the buffer
            token_buffer[1] = '\0'; // terminate the string
            token t = identify_token(token_buffer); // identify the token
            if (t.type == TOKEN_UNKNOWN) {
                printf("Error: unknown token in line %d: %s", line_number, line);
            } else {
                printf("Token: %s, Type: %s\n", t.value, token_type_to_string(t.type)); 
                tokens[token_index++] = t; // store the token in the tokens array
            }
        } else if (c == '"') { // if we encounter a double quote, we start a string
            token_buffer[index++] = c; // add the double quote to the token buffer
            in_string = 1; // set the flag to indicate we are inside a string
        } else { // if the character is not a whitespace, punctuation, or a double quote
            token_buffer[index++] = c; // add the character to the token buffer
        }

        i++; // move to the next character        

    }

    if (index > 0) { // if we have a token in the buffer after processing the line
        token_buffer[index] = '\0'; // terminate the token string
        token t = identify_token(token_buffer); // identify the token
        if (t.type == TOKEN_UNKNOWN) {
            printf("Error: unknown token in line %d: %s", line_number, line);
        } else {
            printf("Token: %s, Type: %s\n", t.value, token_type_to_string(t.type));
            tokens[token_index++] = t; // store the token in the tokens array
        }
    }

    parse_tokens(tokens, token_index, line_number); // parse the tokens for the line
}