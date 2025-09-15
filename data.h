#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <glib.h>


typedef enum {
    // Basic DataType
    TOKEN_INT,
    TOKEN_CHAR,
    TOKEN_FLOAT,
    TOKEN_DOUBLE,

    // Keywords
    TOKEN_KEYWORD,

    // Indentifier and Literal
    TOKEN_IDENTIFIER,
    TOKEN_STRING_LITERAL,

    // Separators
    TOKEN_OPEN_PAREN,
    TOKEN_CLOSE_PAREN,
    TOKEN_OPEN_BRACE,
    TOKEN_CLOSE_BRACE,
    TOKEN_OPEN_BRACKET,
    TOKEN_CLOSE_BRACKET,
    TOKEN_SEMICOLON,
    TOKEN_COLON,
    TOKEN_COMMA,
    TOKEN_DOT,


    // Arithmetic Operators
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_PERCENT,

    // Assignment Operators
    TOKEN_ASSIGN,
    TOKEN_PLUS_ASSIGN,
    TOKEN_MINUS_ASSIGN,
    TOKEN_STAR_ASSIGN,
    TOKEN_SLASH_ASSIGN,
    TOKEN_PERCENT_ASSIGN,

    // Equals Operators
    TOKEN_EQUALS,
    TOKEN_NOT_EQUALS,
    TOKEN_LESS_THAN,
    TOKEN_GREATER_THAN,
    TOKEN_LESS_EQUALS,
    TOKEN_GREATER_EQUALS,

    // Logic Operators
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_NOT,

    // Bitwise Operators
    TOKEN_BIT_AND,
    TOKEN_BIT_OR,
    TOKEN_BIT_XOR,
    TOKEN_BIT_NOT,
    TOKEN_LEFT_SHIFT,
    TOKEN_RIGHT_SHIFT,

    // Special Tokens
    TOKEN_EOF,
    TOKEN_ERROR,
    TOKEN_COMMENT,
} TokenType;


typedef enum {
    // Logical Keywords
    KEYWORD_IF,
    KEYWORD_ELSE,
    KEYWORD_SWITCH,
    KEYWORD_CASE,
    KEYWORD_DEFAULT,
    KEYWORD_DO,
    KEYWORD_WHILE,
    KEYWORD_EXIT,
    KEYWORD_FOR,
    KEYWORD_RETURN,
    KEYWORD_CONTINUE,
    KEYWORD_BREAK,

    // Type Keywords
    KEYWORD_VOID,
    KEYWORD_INT,
    KEYWORD_CHAR,
    KEYWORD_DOUBLE,
    KEYWORD_FLOAT,
    KEYWORD_BOOL,
    KEYWORD_CONST,
    KEYWORD_STRUCT,
    KEYWORD_UNION,
    KEYWORD_ENUM,
    KEYWORD_TYPEDEF,
    
    // Memory Classes and Modificators
    KEYWORD_STATIC,
    KEYWORD_EXTERN,
    KEYWORD_AUTO,
    KEYWORD_REGISTER,
    KEYWORD_VOLATILE,
    
    // Constants
    KEYWORD_TRUE,
    KEYWORD_FALSE,
    KEYWORD_NULL,

    // Special Keywords
    KEYWORD_SIZEOF,
    KEYWORD_PREPROCESSOR,
} TokenKeyword;


typedef struct {
    TokenType type;
    union {
        int int_value;
        char char_value;
        char *string_value;
        float float_value;
        double double_value;
        TokenKeyword keyword;
    } value;

    int line;
    int column;
} Token;


typedef struct {
    Token** tokens;
    int count;
    int capacity;
} TokenStream;


TokenStream* init_token_stream() {
    TokenStream* stream = malloc(sizeof(Token*) * 2);
    stream->count = 0;
    stream->capacity = 2;

    return stream;
}

