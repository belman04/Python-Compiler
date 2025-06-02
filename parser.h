#ifndef PARSER_H // start of the header 
#define PARSER_H // custom header file for the lexer module

#include "lexer.h" // include the lexer header file for token types and structures

// function to parse an array of tokens
void parse_tokens(token* tokens, int num_tokens, int line_number);

#endif // end of the header 