#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef enum {
    T_PLUS,
    T_MINUS,
    T_STAR,
    T_SLASH,
    T_INT,
} TokenType;


typedef struct {
    TokenType type;
    int value;
} Token;
