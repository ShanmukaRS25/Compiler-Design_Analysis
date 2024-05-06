
#include <stdio.h>
#include <ctype.h>
#include <string.h>


typedef enum {
    TOKEN_INT,
    TOKEN_FLOAT,
    TOKEN_IDENTIFIER,
    TOKEN_OPERATOR,
    TOKEN_UNKNOWN
} TokenType;

// Token structure
typedef struct {
    TokenType type;
    char value[50];
} Token;

// Function to classify characters as operators
int is_operator(char c) {
    return strchr("+-*/=", c) != NULL;
}

// Function to perform lexical analysis
void tokenize(char *input) {
    char *ptr = input;
    Token token;
    
    // Iterate through the input string
    while (*ptr != '\0') {
        // Skip whitespace characters
        if (isspace(*ptr)) {
            ptr++;
            continue;
        }
        
        // Check if the character is an operator
        if (is_operator(*ptr)) {
            // Handle operators
            token.type = TOKEN_OPERATOR;
            token.value[0] = *ptr;
            token.value[1] = '\0';
            printf("Operator: %s\n", token.value);
            ptr++;
            continue;
        }
        
        // Check if the character is a digit
        if (isdigit(*ptr)) {
            // Handle integers and floats
            char *start = ptr;
            while (isdigit(*ptr) || *ptr == '.') {
                ptr++;
            }
            strncpy(token.value, start, ptr - start);
            token.value[ptr - start] = '\0';
            if (strchr(token.value, '.') != NULL) {
                token.type = TOKEN_FLOAT;
            } else {
                token.type = TOKEN_INT;
            }
            printf("Number: %s\n", token.value);
            continue;
        }
        
        // Handle identifiers
        if (isalpha(*ptr)) {
            char *start = ptr;
            while (isalnum(*ptr)) {
                ptr++;
            }
            strncpy(token.value, start, ptr - start);
            token.value[ptr - start] = '\0';
            token.type = TOKEN_IDENTIFIER;
            printf("Identifier: %s\n", token.value);
            continue;
        }
        
        // Unknown token
        token.type = TOKEN_UNKNOWN;
        token.value[0] = *ptr;
        token.value[1] = '\0';
        printf("Unknown: %s\n", token.value);
        ptr++;
    }
}

int main() {
    char input[100];
    printf("Enter expression: ");
    fgets(input, sizeof(input), stdin);
    tokenize(input);
    return 0;
}
