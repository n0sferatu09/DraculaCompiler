#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <glib.h>


typedef enum {
    ENUM_START_MARKER,

    // Basic DataType
    TOKEN_INT,
    TOKEN_CHAR,
    TOKEN_FLOAT,
    TOKEN_DOUBLE,

    // Keywords
    TOKEN_KEYWORD,

    // Indentifier and Literal
    TOKEN_PUNCTUATOR,
    TOKEN_PREPROCESSOR,
    TOKEN_IDENTIFIER,
    TOKEN_STRING_LITERAL,

    // Special Tokens
    TOKEN_COMMENT,

} TokenType;


typedef enum {
    KEYWORD_START_MARKER,
    
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

    // Special Keywords
    KEYWORD_SIZEOF,
} TokenKeyword;


typedef enum {
    PREPROCESSOR_START_MARKER,
    
    // Preprocessor Directive
    TOKEN_INCLUDE,
    TOKEN_DEFINE,
    TOKEN_UNDEF,
    TOKEN_IFDEF,
    TOKEN_IFNDEF,
    TOKEN_SHARP_IF,
    TOKEN_SHARP_ELSE,
    TOKEN_SHARP_ELIF,
    TOKEN_ENDIF,
    TOKEN_ERROR,
    TOKEN_WARNING,
    TOKEN_PRAGMA,

} TokenPreprocessor;


typedef enum {
    PUNCTUATOR_START_MARKER,
    
    // Separators
    TOKEN_OPEN_PAREN,
    TOKEN_CLOSE_PAREN,
    TOKEN_OPEN_BRACE,
    TOKEN_CLOSE_BRACE,
    TOKEN_OPEN_BRACKET,
    TOKEN_CLOSE_BRACKET,
    TOKEN_DOUBLE_QUOTES,
    TOKEN_SINGLE_QUOTES,
    TOKEN_SEMICOLON,
    TOKEN_COLON,
    TOKEN_COMMA,

    // Success Operators
    TOKEN_DOT,
    TOKEN_ARROW,

    // Arithmetic Operators
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_PERCENT,

    // Increment and Decrement
    TOKEN_INCREMENT,
    TOKEN_DECREMENT,

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
    TOKEN_BIT_AND_EQUALS,
    TOKEN_BIT_OR_EQUALS,
    TOKEN_BIT_XOR_EQUALS,
    TOKEN_LEFT_SHIFT_EQUALS,
    TOKEN_RIGHT_SHIFT_EQUALS,

} TokenPunctuator;


typedef struct {
    TokenType type;
    union {
        int int_value;
        char char_value;
        char *string_value;
        float float_value;
        double double_value;
        TokenKeyword keyword;
        TokenPunctuator punctuator;
        TokenPreprocessor preprocessor;
    } value;

    int line;
    int column;
} Token;


typedef struct {
    Token** tokens;
    int count;
    int capacity;
} TokenStream;


TokenStream* init_tokens_stream() {
    TokenStream* stream = malloc(sizeof(TokenStream));
    stream->tokens = malloc(sizeof(Token*) * 16);
    stream->count = 0;
    stream->capacity = 16;

    return stream;
}


void add_tokens_to_stream(TokenStream* stream, Token* token) {
    if (token == NULL) return;

    if (stream->count >= stream->capacity) {
        stream->capacity *= 2;
        stream->tokens = realloc(stream->tokens, sizeof(Token*) * stream->capacity);
        
        if (stream->tokens == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
    }


    stream->tokens[stream->count++] = token;
}


void free_tokens_stream(TokenStream* stream) {
    for (int i = 0; i < stream->count; i++) {
        Token* token = stream->tokens[i];
        if (token->type == TOKEN_IDENTIFIER || token->type == TOKEN_PUNCTUATOR || token->type == TOKEN_PREPROCESSOR) {
            free(token->value.string_value);
        }
        
        free(token);
    }

    free(stream->tokens);
}
