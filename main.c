#include "hashtable.h"
#include "defs.h"


Token* generate_numbers(FILE* file, char first_number) {
    if (first_number == EOF) return NULL;

    Token* token = malloc(sizeof(*token));
    if (token == NULL) return NULL;

    int index = 0;
    char buffer[BUFFER_SIZE] = {0};

    int has_decimal_point = 0;
    int has_exponent = 0;
    int has_float_suffix = 0;

    token->type = TOKEN_INT;
    buffer[index++] = first_number;

    char current = fgetc(file);
    while (current != EOF && (isdigit(current) ||
            current == '.' ||
            current == 'e' || current == 'E' ||
            current == 'f' || current == 'F' ||
            current == 'd' || current == 'D')) {

        if (current == '.') {
            if (has_decimal_point) break;

            has_decimal_point = 1;
            token->type = TOKEN_DOUBLE;
        } 
        
        if (current == 'e' || current == 'E') {
            if (has_exponent) break;

            has_exponent = 1;
            token->type = TOKEN_DOUBLE;

            current = fgetc(file);
            if (current != EOF && (current == '+' || current == '-')) {
                char sign = current;
                current = fgetc(file);

                if (isdigit(current)) {
                    buffer[index++] = sign;
                    buffer[index++] = current;
                } else {
                    ungetc(current, file);
                    ungetc(sign, file);
                    fprintf(stderr, "Invalid Exponent: missing digits\n");
                    free(token);
                    return NULL;
                }
            }
        }

        if (current == 'f' || current == 'F') {
            if (has_float_suffix) break;

            has_float_suffix = 1;
            token->type = TOKEN_FLOAT;
        }

        buffer[index++] = current;
        current = fgetc(file);
    }

    buffer[index] = '\0';
    

    if (current != EOF && !isdigit(current) && !has_decimal_point) {
        ungetc(current, file);
    }

    if (token->type == TOKEN_FLOAT) {
        if (buffer[index - 1] == 'f' || buffer[index - 1] == 'F') {
            buffer[index - 1] = '\0';
        }
    }
    
    char *endchar;
    errno = 0;

    if (token->type == TOKEN_INT) {
        token->value.int_value = strtol(buffer, &endchar, 10);
    } else if (token->type == TOKEN_DOUBLE) {
        token->value.double_value = strtod(buffer, &endchar);
    } else if (token->type == TOKEN_FLOAT) {
        token->value.float_value = strtof(buffer, &endchar);
    }

    if (endchar == buffer) {
        fprintf(stderr, "Invalid number: no digits found\n");
        free(token);
        return NULL;
    }

    if (*endchar != '\0') {
        fprintf(stderr, "Invalid number: extra characters '%s'\n", endchar);
        free(token);
        return NULL;
    }

    if (errno == ERANGE) {
        fprintf(stderr, "Number out of range: %s\n", buffer);
        free(token);
        return NULL;
    }

    return token;
}


Token* generate_string(FILE* file, char first_letter) {
    if (first_letter == EOF) return NULL;

    Token* token = malloc(sizeof(*token));
    if (token == NULL) return NULL;

    int capacity = 3;
    int index = 0;
    char* buffer = malloc(sizeof(char) * capacity);

    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        free(token);
        return NULL;
    }

    buffer[index++] = first_letter;

    char current = fgetc(file);
    while (current != EOF && current != '"') {
        if (index >= capacity) {
            capacity *= 2;
            char* new_buffer = realloc(buffer, sizeof(char) * capacity);

            if (new_buffer == NULL) {
                fprintf(stderr, "Memory reallocation failed!\n");
                free(buffer);
                free(token);
                return NULL;
            }

            buffer = new_buffer;
        }

        buffer[index++] = current;
        current = fgetc(file);
    }

    if (index >= capacity) {
        capacity += 2;
        char* new_buffer = realloc(buffer, sizeof(char) * capacity);

        if (new_buffer == NULL) {
            fprintf(stderr, "Memory reallocation failed!\n");
            free(buffer);
            free(token);
            return NULL;
        }
    }

    buffer[index++] = current;
    buffer[index] = '\0';
    
    if (buffer != NULL) {
        token->type = TOKEN_STRING_LITERAL;
        token->value.string_value = strdup(buffer);
    } else {
        free(token);
        return NULL;
    }

    return token;
} 


Token* generate_keywords(FILE* file, char first_letter) {
    if (first_letter == EOF) return NULL;

    Token* token = malloc(sizeof(*token));
    if (token == NULL) return NULL;

    int index = 0;
    char buffer[KEYWORD_SIZE + 1] = {0};

    buffer[index++] = first_letter;

    char current = fgetc(file);

    while(current != EOF && (isalnum(current) || current == '_')) {
        buffer[index++] = current;
        current = fgetc(file);
    }

    buffer[index] = '\0';

    if (!isalpha(current) && current != EOF) {
        ungetc(current, file);
    }

    if (keywords_table == NULL) {
        init_keyword_table();
    }

    gpointer keyword_type = g_hash_table_lookup(keywords_table, buffer);

    if (keyword_type != NULL) {
        token->type = TOKEN_KEYWORD;
        token->value.keyword = GPOINTER_TO_INT(keyword_type);
        token->value.string_value = strdup(buffer);
    } else {
        token->type = TOKEN_IDENTIFIER;
        token->value.string_value = strdup(buffer);
    }

    return token;
}


Token* generate_preprocessor(FILE* file, char first_char) {
    if (first_char == EOF) return NULL;

    Token* token = malloc(sizeof(*token));
    if (token == NULL) return NULL;

    int capacity = 8;
    int index = 0;
    char* buffer = malloc(sizeof(char) * capacity);

    buffer[index++] = first_char;

    char current = fgetc(file);
    while (current != EOF && isalpha(current) && (index < PREPROCESSOR_SIZE - 1)) {
        if (index >= capacity) {
            capacity *= 2;
            char* new_buffer = realloc(buffer, sizeof(char) * capacity);

            if (new_buffer == NULL) {
                fprintf(stderr, "Memory reallocation failed!\n");
                free(buffer);
                free(token);
                return NULL;
            }

            buffer = new_buffer;
        }
        buffer[index++] = current;
        current = fgetc(file);
    }

    buffer[index] = '\0';

    if (current != EOF && !isalpha(current)) {
        ungetc(current, file);
    }

    if (preprocessor_table == NULL) {
        init_preprocessor_table();
    }

    gpointer preprocessor_type = g_hash_table_lookup(preprocessor_table, buffer);

    if (preprocessor_type != NULL) {
        token->type = TOKEN_PREPROCESSOR;
        token->value.preprocessor = GPOINTER_TO_INT(preprocessor_type);
        token->value.string_value = strdup(buffer);
    } else {
        fprintf(stderr, "UNKNOWN PREPROCESSOR DIRECTIVE: %s\n", buffer);
        free(token);
        return NULL;
    }

    return token;
}


Token* generate_punctuators(FILE* file, char first_char) {
    if (first_char == EOF) return NULL;

    Token* token = malloc(sizeof(*token));
    if (token == NULL) return NULL;

    char buffer[OPERATORS_SIZE + 1] = {0};
    int index = 0;

    buffer[index++] = first_char;

    char single_punctuators[] = "( ) [ ] { } \" ' ; : , .";
    if (strchr(single_punctuators, first_char)) {
        buffer[index] = '\0';

        if (operators_table == NULL) {
            init_operators_table();
        }

        gpointer punctuators_type = g_hash_table_lookup(operators_table, buffer);

        if (punctuators_type != NULL) {
            token->type = TOKEN_PUNCTUATOR;
            token->value.punctuator = GPOINTER_TO_INT(punctuators_type);
            token->value.string_value = strdup(buffer);
            return token;
        }
    } 

    char current = fgetc(file);
    while (current != EOF && ispunct(current)) {
        buffer[index++] = current;
        current = fgetc(file);
    }

    buffer[index] = '\0';

    if (current != EOF && !ispunct(current)) {
        ungetc(current, file);
    }

    if (operators_table == NULL) {
        init_operators_table();
    }

    gpointer punctuators_type = g_hash_table_lookup(operators_table, buffer);
    
    if (punctuators_type != NULL) {
        token->type = TOKEN_PUNCTUATOR;
        token->value.punctuator = GPOINTER_TO_INT(punctuators_type);
        token->value.string_value = strdup(buffer);
    } else {
        fprintf(stderr, "UNKNOWN OPERATOR: %s\n", buffer);
        free(token);
        return NULL;
    }

    return token;
}


TokenStream* lexer(FILE* file) {
    TokenStream* stream = init_tokens_stream();
    char current;
    current = fgetc(file);
    
    while (current != EOF) {
        if (isspace(current)) {
            current = fgetc(file);
            continue;

        } else if (current == '"') {
            Token* token_string = generate_string(file, current);

            if (token_string != NULL) {
                add_tokens_to_stream(stream, token_string);
                printf("FOUND A STRING: %s\n", token_string->value.string_value);
            }
            
        } else if (current == '#') {
            Token* token_preprocessor = generate_preprocessor(file, current);

            if (token_preprocessor != NULL) {
                add_tokens_to_stream(stream, token_preprocessor);
                printf("FOUND A PREPROCESSOR: %s\n", token_preprocessor->value.string_value);
            }

        } else if (isdigit(current)) {
            Token* token_number = generate_numbers(file, current);
            add_tokens_to_stream(stream, token_number);

            if (token_number->type == TOKEN_INT) {
                printf("FOUND INTEGER NUMBER %d\n", token_number->value.int_value);
            } else if (token_number->type == TOKEN_DOUBLE) {
                printf("FOUND DOUBLE NUMBER %lf\n", token_number->value.double_value);
            } else if (token_number->type == TOKEN_FLOAT) {
                printf("FOUND FLOAT NUMBER %f\n", token_number->value.float_value);
            } else {
                printf("UNKNOWN NUMBER\n");
            }

        } else if (isalpha(current) || current == '_') {
            Token* token_keyword = generate_keywords(file, current);
            add_tokens_to_stream(stream, token_keyword);

            if (token_keyword->type == TOKEN_KEYWORD) {
                printf("FOUND A KEYWORD: %s\n", token_keyword->value.string_value);
            } else {
                printf("FOUND A IDENTIFIER: %s\n", token_keyword->value.string_value);
            }

        } else if (ispunct(current)) {
            Token* token_punctuator = generate_punctuators(file, current);
            
            if (token_punctuator != NULL) {
                add_tokens_to_stream(stream, token_punctuator);
                printf("FOUND A OPERATOR: %s\n", token_punctuator->value.string_value);
            }


        }

        current = fgetc(file);
    }

    return stream;
}


int main() {
    FILE* file;
    file = fopen("test.c", "r");

    init_keyword_table();
    init_operators_table();
    init_preprocessor_table();

    if (file == NULL) {
        printf("Error: cannot open file\n");
        return 1;
    }

    TokenStream* stream = lexer(file);

    if (stream == NULL) {
        printf("Error: Lexer returned NULL\n");
        fclose(file);
        return 1;
    }

    free_tokens_stream(stream);
    cleanup_all_hash_table();
    fclose(file);

    return 0;
}
