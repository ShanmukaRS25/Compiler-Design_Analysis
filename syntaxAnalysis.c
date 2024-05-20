The syntax analyzer checks the source code for syntactical correctness based on the rules defined by a context-free grammar (CFG).
  ## create a simple lexer to tokenize the input.###
  #include <stdio.h>
#include <ctype.h>

typedef enum { 
    PLUS, MINUS, TIMES, DIVIDE, LPAREN, RPAREN, ID, END 
} TokenType;

typedef struct {
    TokenType type;
    char value;
} Token;

Token tokens[100];
int currentTokenIndex = 0;

void tokenize(const char *input) {
    const char *ptr = input;
    while (*ptr != '\0') {
        if (isspace(*ptr)) {
            ptr++;
            continue;
        }
        Token token;
        if (*ptr == '+') token.type = PLUS;
        else if (*ptr == '-') token.type = MINUS;
        else if (*ptr == '*') token.type = TIMES;
        else if (*ptr == '/') token.type = DIVIDE;
        else if (*ptr == '(') token.type = LPAREN;
        else if (*ptr == ')') token.type = RPAREN;
        else if (isalpha(*ptr)) token.type = ID;
        else {
            printf("Error: Unknown character '%c'\n", *ptr);
            return;
        }
        token.value = *ptr;
        tokens[currentTokenIndex++] = token;
        ptr++;
    }
    tokens[currentTokenIndex].type = END; // End token
}
##########  recursive descent parser. ################

#include <stdio.h>
#include <ctype.h>

typedef enum { 
    PLUS, MINUS, TIMES, DIVIDE, LPAREN, RPAREN, ID, END 
} TokenType;

typedef struct {
    TokenType type;
    char value;
} Token;

Token tokens[100];
int currentTokenIndex = 0;

void tokenize(const char *input);
void E();
void EPrime();
void T();
void TPrime();
void F();
void match(TokenType expected);

void tokenize(const char *input) {
    const char *ptr = input;
    while (*ptr != '\0') {
        if (isspace(*ptr)) {
            ptr++;
            continue;
        }
        Token token;
        if (*ptr == '+') token.type = PLUS;
        else if (*ptr == '-') token.type = MINUS;
        else if (*ptr == '*') token.type = TIMES;
        else if (*ptr == '/') token.type = DIVIDE;
        else if (*ptr == '(') token.type = LPAREN;
        else if (*ptr == ')') token.type = RPAREN;
        else if (isalpha(*ptr)) token.type = ID;
        else {
            printf("Error: Unknown character '%c'\n", *ptr);
            return;
        }
        token.value = *ptr;
        tokens[currentTokenIndex++] = token;
        ptr++;
    }
    tokens[currentTokenIndex].type = END; // End token
}

Token currentToken() {
    return tokens[currentTokenIndex];
}

void advance() {
    currentTokenIndex++;
}

void match(TokenType expected) {
    if (currentToken().type == expected) {
        advance();
    } else {
        printf("Syntax Error: Expected token type %d but got %d\n", expected, currentToken().type);
    }
}

void E() {
    T();
    EPrime();
}

void EPrime() {
    if (currentToken().type == PLUS) {
        match(PLUS);
        T();
        EPrime();
    } else if (currentToken().type == MINUS) {
        match(MINUS);
        T();
        EPrime();
    }
}

void T() {
    F();
    TPrime();
}

void TPrime() {
    if (currentToken().type == TIMES) {
        match(TIMES);
        F();
        TPrime();
    } else if (currentToken().type == DIVIDE) {
        match(DIVIDE);
        F();
        TPrime();
    }
}

void F() {
    if (currentToken().type == LPAREN) {
        match(LPAREN);
        E();
        match(RPAREN);
    } else if (currentToken().type == ID) {
        match(ID);
    } else {
        printf("Syntax Error: Unexpected token type %d\n", currentToken().type);
    }
}

int main() {
    const char *input = "a + b * (c + d)";
    tokenize(input);
    E();
    if (currentToken().type == END) {
        printf("Parsing completed successfully.\n");
    } else {
        printf("Syntax Error: Unexpected token at end of input.\n");
    }
    return 0;
}
