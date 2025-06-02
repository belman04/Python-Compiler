#ifndef LEXER_H // start of the header 
#define LEXER_H // custom header file for the lexer module

#define MAX_TOKEN_LENGTH 100 // maximum length of a token
#define MAX_TOKENS_PER_LINE 100 // maximum number of tokens per line

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

    // assignment operator
    TOKEN_ASSIGN,

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
    TOKEN_ELIF,
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
    char value[MAX_TOKEN_LENGTH]; // the value of the token, a character array to hold the value
} token;

// we bring the function here so that it can be used in other files
void tokenize_line(const char* line, int line_number); 

#endif // end of the header 