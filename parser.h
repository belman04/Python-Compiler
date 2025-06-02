#ifndef PARSER_H // start of the header 
#define PARSER_H // custom header file for the lexer module

#include "lexer.h" // include the lexer header file for token types and structures

typedef struct { // structure to represent an AST node (Abstract syntax tree)
    char node_type[32]; // type of the AST node 
    token token_data;  // token data associated with the AST node
} ASTNode; 

// function to parse an array of tokens
void parse_tokens(token* tokens, int num_tokens, int line_number);

#endif // end of the header 