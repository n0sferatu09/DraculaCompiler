#include "hashtable.h"
#include "defs.h"


Token *generate_numbers(FILE *file, char first_number) {
    Token *token = malloc(sizeof(Token));
    if (token == NULL) return NULL;

    char buffer[BUFFER_SIZE + 1] = {0};
    int index = 0;
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

        if (index < BUFFER_SIZE) {
            buffer[index++] = current;
        }

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


Token *generate_keywords(FILE *file, char first_letter) {
    Token *token = malloc(sizeof(Token));
    if (token == NULL) return NULL;

    char buffer[KEYWORD_SIZE + 1] = {0};
    int index = 0;

    buffer[index++] = first_letter;

    char current = fgetc(file);

    while(isalpha(current) && current != EOF) {
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
    } else {
        token->type = TOKEN_IDENTIFIER;
        token->value.string_value = strdup(buffer);
    }

    return token;
}


Token *generate_punctuators(FILE *file, char first_char) {
    Token *token = malloc(sizeof(Token));
    if (token == NULL) return NULL;

    char buffer[OPERATORS_SIZE + 1] = {0};
    int index = 0;
    
    buffer[index++] = first_char;

    char current = fgetc(file);
    while (current != EOF && ispunct(current) && (index < OPERATORS_SIZE - 1)) {
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

    gpointer punctuator_type = g_hash_table_lookup(operators_table, buffer);

    if (punctuator_type != NULL) {
        token->type = GPOINTER_TO_INT(punctuator_type);
        token->value.string_value = strdup(buffer);
    } else {
        free(token);
        return NULL;
    }

    return token;
}


void lexer(FILE *file) {
    char current;
    current = fgetc(file);
    
    while (current != EOF) {
        if (isspace(current)) {
            current = fgetc(file);
            continue;

        } else if (ispunct(current)) {
            Token *token_punctuator = generate_punctuators(file, current);
            printf("FOUND A OPERATOR: %s\n", token_punctuator->value.string_value);

            free(token_punctuator->value.string_value);
            free(token_punctuator);
        } else if (isdigit(current)) {
            Token *token_number = generate_numbers(file, current);

            if (token_number->type == TOKEN_INT) {
                printf("FOUND INTEGER NUMBER %d\n", token_number->value.int_value);
            } else if (token_number->type == TOKEN_DOUBLE) {
                printf("FOUND DOUBLE NUMBER %lf\n", token_number->value.double_value);
            } else if (token_number->type == TOKEN_FLOAT) {
                printf("FOUND FLOAT NUMBER %f\n", token_number->value.float_value);
            } else {
                printf("UNKNOWN NUMBER\n");
            }
            
            free(token_number);

        } else if (isalpha(current)) {
            Token *token_keyword = generate_keywords(file, current);

            if (token_keyword->value.keyword == KEYWORD_EXIT) {
                printf("FOUND KEYWORD: EXIT\n");
            } else if (token_keyword->value.keyword == KEYWORD_IF) {
                printf("FOUND KEYWORD: IF\n");
            } else if (token_keyword->value.keyword == KEYWORD_ELSE) {
                printf("FOUND KEYWORD: ELSE\n");
            } else if (token_keyword->value.keyword == KEYWORD_WHILE) {
                printf("FOUND KEYWORD: WHILE\n");
            } else if (token_keyword->value.keyword == KEYWORD_FOR) {
                printf("FOUND KEYWORD: FOR\n");
            } else if (token_keyword->type == TOKEN_IDENTIFIER) {
                printf("FOUND IDENTIFIER %s\n", token_keyword->value.string_value);
                free(token_keyword->value.string_value);
            } else {
                printf("UNKNOWN KEYWORD\n");
            }

            free(token_keyword);

        }

        current = fgetc(file);
    }
}


int main() {
    FILE *file;
    file = fopen("test.unn", "r");

    if (file == NULL) {
        printf("Error: cannot open file\n");
        return 1;
    }

    cleanup_all_hash_table();
    lexer(file);
    fclose(file);
    return 0;
}
