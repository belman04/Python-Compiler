#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

// function to create a new ast node
ASTNode* create_ast_node(ASTNodeType type, const char* val1, const char* val2, const char* val3) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode)); // allocate memory for the new node
    node->type = type; // set the type of the AST node
    strncpy(node->value1, val1, sizeof(node->value1)); // copy the first value into the node
    strncpy(node->value2, val2, sizeof(node->value2)); // copy the second value into the node
    strncpy(node->value3, val3, sizeof(node->value3)); // copy the third value into the node
    node->left = NULL; // initialize the left child to NULL
    node->right = NULL; // initialize the right child to NULL
    return node;
}

// function to print the ast in a readable format
void print_ast(ASTNode* root, int indent) {
    if (!root) return; // if the root is NULL, return
    for (int i = 0; i < indent; i++) printf("  "); // prints indentation for better readability

    // switch to determine the type of ast node and print it
    switch (root->type) { 
        case AST_ASSIGNMENT:
            printf("Assignment: %s = %s\n", root->value1, root->value2);
            break;
        case AST_ARITHMETIC:
            printf("Arithmetic: %s %s %s\n", root->value1, root->value2, root->value3);
            break;
        case AST_IF:
            printf("If: %s %s %s\n", root->value1, root->value2, root->value3);
            break;
        case AST_ELSE:
            printf("Else\n");
            break;
        case AST_WHILE:
            printf("While: %s %s %s\n", root->value1, root->value2, root->value3);
            break;
        case AST_PRINT:
            printf("Print: %s\n", root->value1);
            break;
        case AST_LOGICAL:
            printf("Logical: %s %s %s\n", root->value1, root->value2, root->value3);
            break;
        case AST_COMPARISON:
            printf("Comparison: %s %s %s\n", root->value1, root->value2, root->value3);
            break;
        case AST_FUNCTION_CALL:
            printf("Function call: %s(%s)\n", root->value1, root->value2);
            break;
    }

    if (root->left) print_ast(root->left, indent + 1); // recursively print the left child with increased indentation
    if (root->right) print_ast(root->right, indent + 1); // recursively print the right child with increased indentation
}

// function to free the memory allocated for the ast
void free_ast(ASTNode* root) { 
    if (!root) return; // if the root is NULL, return
    free_ast(root->left); // recursively free the left child
    free_ast(root->right); // recursively free the right child
    free(root); // free the memory allocated for the current node
}
