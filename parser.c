#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "lexer.h"
#include "ast.h"

ASTNode* ast_root = NULL; // root of the ast
ASTNode* ast_last = NULL; // last node in the ast, used for appending new nodes

// function to check if a token is an identifier or a number
int is_id_or_num(token t) {
    return t.type == TOKEN_IDENTIFIER || t.type == TOKEN_NUMBER;
}

// function to check if a token is an arithmetic operator
int is_arithmetic_op(token t) {
    return t.type == TOKEN_ADD || t.type == TOKEN_SUB ||
           t.type == TOKEN_MUL || t.type == TOKEN_DIV || t.type == TOKEN_INT_DIV;
}

// function to check if a token is a comparison operator
int is_comparison_op(token t) {
    return t.type == TOKEN_GREATER_THAN || t.type == TOKEN_LESS_THAN ||
           t.type == TOKEN_EQUAL || t.type == TOKEN_NOT_EQUAL ||
           t.type == TOKEN_GREATER_THAN_OR_EQUAL || t.type == TOKEN_LESS_THAN_OR_EQUAL;
}

// function to check if a token is a logical operator
int is_logical_op(token t) {
    return t.type == TOKEN_AND || t.type == TOKEN_OR || t.type == TOKEN_NOT;
}

// function to parse tokens and print the corresponding statements
void parse_tokens(token* tokens, int token_count, int line_number) {
    printf("-- Parsing line %d --\n", line_number);

    for (int i = 0; i < token_count; i++) {
        // arithmetic Assignment: a = a + 1, b = b - 2, etc.
        if (i + 4 < token_count &&
            tokens[i].type == TOKEN_IDENTIFIER &&
            tokens[i + 1].type == TOKEN_ASSIGN &&
            is_id_or_num(tokens[i + 2]) &&
            is_arithmetic_op(tokens[i + 3]) &&
            is_id_or_num(tokens[i + 4])) {
            // printf("Arithmetic Assignment: %s = %s %s %s\n", tokens[i].value, tokens[i + 2].value, tokens[i + 3].value, tokens[i + 4].value);
            // this is where you would create an AST node for the assignment
            ASTNode* node = create_ast_node(AST_ARITHMETIC, tokens[i].value, tokens[i + 3].value, tokens[i + 4].value);
            
            if (!ast_root) ast_root = node;
            else ast_last->right = node;
            ast_last = node;

            printf("Created AST node for arithmetic assignment: %s = ... %s %s\n", tokens[i].value, tokens[i + 3].value, tokens[i + 4].value);

            i += 4;
            continue;
        }

        // assignment: a = 5, a = b
        if (i + 2 < token_count &&
            tokens[i].type == TOKEN_IDENTIFIER &&
            tokens[i + 1].type == TOKEN_ASSIGN &&
            is_id_or_num(tokens[i + 2])) {
            // printf("Assignment: %s = %s\n", tokens[i].value, tokens[i + 2].value);
            ASTNode* node = create_ast_node(AST_ASSIGNMENT, tokens[i].value, tokens[i + 2].value, "");
            
            if (!ast_root) ast_root = node;
            else ast_last->right = node;
            ast_last = node;

            printf("Created AST node for assignment: %s = %s\n", tokens[i].value, tokens[i + 2].value);

            i += 2;
            continue;
        }

        // if statements simple: if a > 5:
        if (i + 4 < token_count &&
            tokens[i].type == TOKEN_IF &&
            is_id_or_num(tokens[i + 1]) &&
            is_comparison_op(tokens[i + 2]) &&
            is_id_or_num(tokens[i + 3]) &&
            tokens[i + 4].type == TOKEN_COLON) {
            // printf("If statement: if %s %s %s:\n", tokens[i + 1].value, tokens[i + 2].value, tokens[i + 3].value);
            ASTNode* node = create_ast_node(AST_IF, tokens[i + 1].value, tokens[i + 2].value, tokens[i + 3].value);

            if (!ast_root) ast_root = node;
            else ast_last->right = node;
            ast_last = node;

            printf("Created AST node for if statement: if %s %s %s:\n", tokens[i + 1].value, tokens[i + 2].value, tokens[i + 3].value);
            
            i += 4;
            continue;
        }

        // if statement with logical operator: if a > 5 and b < 10:
        if (i + 8 < token_count &&
            tokens[i].type == TOKEN_IF &&
            is_id_or_num(tokens[i + 1]) &&
            is_comparison_op(tokens[i + 2]) &&
            is_id_or_num(tokens[i + 3]) &&
            tokens[i + 4].type == TOKEN_AND &&
            is_id_or_num(tokens[i + 5]) &&
            is_comparison_op(tokens[i + 6]) &&
            is_id_or_num(tokens[i + 7]) &&
            tokens[i + 8].type == TOKEN_COLON) {
            // printf("If statement with logical operator: if %s %s %s and %s %s %s:\n",
            //        tokens[i + 1].value, tokens[i + 2].value, tokens[i + 3].value,
            //        tokens[i + 5].value, tokens[i + 6].value, tokens[i + 7].value);
            ASTNode* node = create_ast_node(AST_IF, tokens[i + 1].value, tokens[i + 2].value, tokens[i + 3].value);
            ASTNode* logical_node = create_ast_node(AST_LOGICAL, tokens[i + 5].value, tokens[i + 6].value, tokens[i + 7].value);
            
            node->left = logical_node; // link the logical node to the if node

            if (!ast_root) ast_root = node;
            else ast_last->right = node;
            ast_last = node;

            printf("Created AST node for if statement with logical operator: if %s %s %s and %s %s %s:\n",
                   tokens[i + 1].value, tokens[i + 2].value, tokens[i + 3].value,
                   tokens[i + 5].value, tokens[i + 6].value, tokens[i + 7].value);

            i += 8;
            continue;
        }

        // else statement:
        if (i + 1 < token_count &&
            tokens[i].type == TOKEN_ELSE &&
            tokens[i + 1].type == TOKEN_COLON) {
            // printf("Else statement:\n");
            ASTNode* node = create_ast_node(AST_ELSE, "", "", "");
            if (!ast_root) ast_root = node;
            else ast_last->right = node;
            ast_last = node;

            printf("Created AST node for else statement:\n");

            i += 1;
            continue;
        }

        // elif statement: elif a < 10:
        if (i + 4 < token_count &&
            tokens[i].type == TOKEN_ELIF &&
            is_id_or_num(tokens[i + 1]) &&
            is_comparison_op(tokens[i + 2]) &&
            is_id_or_num(tokens[i + 3]) &&
            tokens[i + 4].type == TOKEN_COLON) {
            // printf("Elif statement: elif %s %s %s:\n", tokens[i + 1].value, tokens[i + 2].value, tokens[i + 3].value);
            ASTNode* node = create_ast_node(AST_IF, tokens[i + 1].value, tokens[i + 2].value, tokens[i + 3].value);

            if (!ast_root) ast_root = node;
            else ast_last->right = node;
            ast_last = node;

            printf("Created AST node for elif statement: elif %s %s %s:\n", tokens[i + 1].value, tokens[i + 2].value, tokens[i + 3].value);

            i += 4;
            continue;
        }

        //print statements 
        if (tokens[i].type == TOKEN_PRINT) {
            if (i + 3 < token_count &&
                tokens[i + 1].type == TOKEN_LEFT_PAREN &&
                tokens[i + 2].type == TOKEN_STRING &&
                tokens[i + 3].type == TOKEN_RIGHT_PAREN) {
                // printf("Print statement: print(%s)\n", tokens[i + 2].value);
                ASTNode* node = create_ast_node(AST_PRINT, tokens[i + 2].value, "", "");

                if (!ast_root) ast_root = node;
                else ast_last->right = node;
                ast_last = node;

                printf("Created AST node for print statement: print(%s)\n", tokens[i + 2].value);

                i += 3;
                continue;
            }
            if (i + 3 < token_count &&
                tokens[i + 1].type == TOKEN_LEFT_PAREN &&
                (is_id_or_num(tokens[i + 2])) &&
                tokens[i + 3].type == TOKEN_RIGHT_PAREN) {
                // printf("Print statement: print(%s)\n", tokens[i + 2].value);
                ASTNode* node = create_ast_node(AST_PRINT, tokens[i + 2].value, "", "");

                if (!ast_root) ast_root = node;
                else ast_last->right = node;
                ast_last = node;

                printf("Created AST node for print statement: print(%s)\n", tokens[i + 2].value);

                i += 3;
                continue;
            }
            if (i + 5 < token_count &&
                tokens[i + 1].type == TOKEN_LEFT_PAREN &&
                (tokens[i + 2].type == TOKEN_STRING || is_id_or_num(tokens[i + 2])) &&
                tokens[i + 3].type == TOKEN_COMMA &&
                is_id_or_num(tokens[i + 4]) &&
                tokens[i + 5].type == TOKEN_RIGHT_PAREN) {
                // printf("Print statement with multiple arguments: print(%s, %s)\n", tokens[i + 2].value, tokens[i + 4].value);
                ASTNode* node = create_ast_node(AST_PRINT, tokens[i + 2].value, tokens[i + 4].value, "");

                if (!ast_root) ast_root = node;
                else ast_last->right = node;
                ast_last = node;

                printf("Created AST node for print statement with multiple arguments: print(%s, %s)\n", tokens[i + 2].value, tokens[i + 4].value);

                i += 5;
                continue;
            }
            if (i + 7 < token_count &&
                tokens[i + 1].type == TOKEN_LEFT_PAREN &&
                (tokens[i + 2].type == TOKEN_STRING || is_id_or_num(tokens[i + 2])) &&
                tokens[i + 3].type == TOKEN_COMMA &&
                is_id_or_num(tokens[i + 4]) &&
                tokens[i + 5].type == TOKEN_COMMA &&
                is_id_or_num(tokens[i + 6]) &&
                tokens[i + 7].type == TOKEN_RIGHT_PAREN) {
                // printf("Print statement with three arguments: print(%s, %s, %s)\n",
                //     tokens[i + 2].value, tokens[i + 4].value, tokens[i + 6].value);
                ASTNode* node = create_ast_node(AST_PRINT, tokens[i + 2].value, tokens[i + 4].value, tokens[i + 6].value);
                if (!ast_root) ast_root = node;
                else ast_last->right = node;
                ast_last = node;

                printf("Created AST node for print statement with three arguments: print(%s, %s, %s)\n",
                       tokens[i + 2].value, tokens[i + 4].value, tokens[i + 6].value);
                       
                i += 7;
                continue;
            }
        }

        // function call: add(a)
        if (i + 3 < token_count &&
            tokens[i + 1].type == TOKEN_LEFT_PAREN &&
            is_id_or_num(tokens[i + 2]) &&
            tokens[i + 3].type == TOKEN_RIGHT_PAREN) {
            // printf("Function call: %s(%s)\n", tokens[i].value, tokens[i + 2].value);
            ASTNode* node = create_ast_node(AST_FUNCTION_CALL, tokens[i].value, tokens[i + 2].value, "");

            if (!ast_root) ast_root = node;
            else ast_last->right = node;
            ast_last = node;

            printf("Created AST node for function call: %s(%s)\n", tokens[i].value, tokens[i + 2].value);

            i += 3;
            continue;
        }

        // while loop: while a < 10:
        if (i + 4 < token_count &&
            tokens[i].type == TOKEN_WHILE &&
            is_id_or_num(tokens[i + 1]) &&
            is_comparison_op(tokens[i + 2]) &&
            is_id_or_num(tokens[i + 3]) &&
            tokens[i + 4].type == TOKEN_COLON) {
            // printf("While loop: while %s %s %s:\n", tokens[i + 1].value, tokens[i + 2].value, tokens[i + 3].value);
            ASTNode* node = create_ast_node(AST_WHILE, tokens[i + 1].value, tokens[i + 2].value, tokens[i + 3].value);

            if (!ast_root) ast_root = node;
            else ast_last->right = node;
            ast_last = node;

            printf("Created AST node for while loop: while %s %s %s:\n", tokens[i + 1].value, tokens[i + 2].value, tokens[i + 3].value);

            i += 4;
            continue;
        }

        // arithmetic operation: 5 + 10, a - 2
        if (i + 2 < token_count &&
            is_arithmetic_op(tokens[i + 1]) &&
            is_id_or_num(tokens[i + 2])) {
            // printf("Arithmetic operation: %s %s %s\n", tokens[i].value, tokens[i + 1].value, tokens[i + 2].value);
            ASTNode* node = create_ast_node(AST_ARITHMETIC, tokens[i].value, tokens[i + 1].value, tokens[i + 2].value);

            if (!ast_root) ast_root = node;
            else ast_last->right = node;
            ast_last = node;

            printf("Created AST node for arithmetic operation: %s %s %s\n", tokens[i].value, tokens[i + 1].value, tokens[i + 2].value);

            i += 2;
            continue;
        }

        // comparison: a > 5, b < 10
        if (i + 2 < token_count &&
            is_comparison_op(tokens[i + 1]) &&
            is_id_or_num(tokens[i + 2])) {
            // printf("Comparison: %s %s %s\n", tokens[i].value, tokens[i + 1].value, tokens[i + 2].value);
            ASTNode* node = create_ast_node(AST_COMPARISON, tokens[i].value, tokens[i + 1].value, tokens[i + 2].value);

            if (!ast_root) ast_root = node;
            else ast_last->right = node;
            ast_last = node;

            printf("Created AST node for comparison: %s %s %s\n", tokens[i].value, tokens[i + 1].value, tokens[i + 2].value);

            i += 2;
            continue;
        }

        // logical operation: a and b
        if (i + 2 < token_count &&
            is_logical_op(tokens[i + 1]) &&
            is_id_or_num(tokens[i + 2])) {
            // printf("Logical operation: %s %s %s\n", tokens[i].value, tokens[i + 1].value, tokens[i + 2].value);
            ASTNode* node = create_ast_node(AST_LOGICAL, tokens[i].value, tokens[i + 1].value, tokens[i + 2].value);

            if (!ast_root) ast_root = node;
            else ast_last->right = node;
            ast_last = node;

            printf("Created AST node for logical operation: %s %s %s\n", tokens[i].value, tokens[i + 1].value, tokens[i + 2].value);
            
            i += 2;
            continue;
        }

        printf("Syntax error or unrecognized statement at token %d: %s\n", i, tokens[i].value);
    }

    printf("-- End of parsing line %d --\n\n", line_number);
}