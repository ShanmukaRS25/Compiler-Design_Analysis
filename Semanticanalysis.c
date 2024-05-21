#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef enum {
    ID, NUM, ASSIGN, PLUS, SEMICOLON, END
} TokenType;

typedef struct {
    TokenType type;
    char lexeme[64];
} Token;

Token tokens[100];
int tokenIndex = 0;

void tokenize(const char *input) {
    const char *ptr = input;
    while (*ptr != '\0') {
        if (isspace(*ptr)) {
            ptr++;
            continue;
        }

        Token token;
        if (isalpha(*ptr)) {
            char buffer[64];
            int len = 0;
            while (isalpha(*ptr)) {
                buffer[len++] = *ptr++;
            }
            buffer[len] = '\0';
            token.type = ID;
            strcpy(token.lexeme, buffer);
        } else if (isdigit(*ptr)) {
            char buffer[64];
            int len = 0;
            while (isdigit(*ptr)) {
                buffer[len++] = *ptr++;
            }
            buffer[len] = '\0';
            token.type = NUM;
            strcpy(token.lexeme, buffer);
        } else if (*ptr == '+') {
            token.type = PLUS;
            token.lexeme[0] = '+';
            token.lexeme[1] = '\0';
            ptr++;
        } else if (*ptr == '=') {
            token.type = ASSIGN;
            token.lexeme[0] = '=';
            token.lexeme[1] = '\0';
            ptr++;
        } else if (*ptr == ';') {
            token.type = SEMICOLON;
            token.lexeme[0] = ';';
            token.lexeme[1] = '\0';
            ptr++;
        } else {
            printf("Unknown character: %c\n", *ptr);
            exit(1);
        }
        tokens[tokenIndex++] = token;
    }
    tokens[tokenIndex].type = END;
}
