#ifndef AST_H // start of the header
#define AST_H // custom header file for the Abstract Syntax Tree (AST) module

// this header will define the structure of the ast (abstract syntax tree) 
typedef enum {
    AST_ASSIGNMENT,
    AST_ARITHMETIC,
    AST_IF,
    AST_ELSE,
    AST_WHILE,
    AST_PRINT,
    AST_LOGICAL,
    AST_COMPARISON,
    AST_FUNCTION_CALL
} ASTNodeType;

// this structure will represent a node in the ast
typedef struct ASTNode {
    ASTNodeType type; // type of the AST node
    char value1[64];  // first value associated with the AST node
    char value2[64];  // second value associated with the AST node
    char value3[64];  // third value associated with the AST node
    struct ASTNode* left; // pointer to the left child node
    struct ASTNode* right; // pointer to the right child node
} ASTNode;

// functions to create, print, and free ast nodes
ASTNode* create_ast_node(ASTNodeType type, const char* val1, const char* val2, const char* val3);
void print_ast(ASTNode* root, int indent); // function to print the AST in a readable format
void free_ast(ASTNode* root); // function to free the memory allocated for the AST

#endif // end of the header
