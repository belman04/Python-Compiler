#include <stdio.h> // standard library header for input/output operations
#include "lexer.h" // custom header file for the lexer module

int main(){
    FILE* file = fopen("test.py", "r"); // to open the file "test.py" and read it
    // FILE* is a pointer to a file object
    // fopen is function to open a file
    // r means read mode

    // if there's no file
    if(!file){
        printf("Error opening file");
        return 1; // a non-zero return value indicates an error, it could also be other values like -1, 2 
    }

    char line[256]; // character array to hold each line of the file

    // a loop to read each line from the file
    while(fgets(line, sizeof(line), file)){
        printf("-> Line: %s", line);
        tokenize_line(line); 
    }
    // fgets is a function to read a line from the file, the arguments are:
        // line is the character array where the line will be stored
        // sizeof(line) is a function to get the size of the line array
        // file is the file pointer
        
    // print is a function to print the line to the console, the %s means a string will be printed
    // tokenize is a function to process the line for tokens

    fclose(file); // a function to clse the file 
    return 0; // a return value of 0 indicates success
}