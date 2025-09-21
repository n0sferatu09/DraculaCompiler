#include "data.h"


GHashTable* keywords_table = NULL;
GHashTable* operators_table = NULL;
GHashTable* preprocessor_table = NULL;

void init_keyword_table() {
    if (keywords_table != NULL) {
        return;
    }

    if (keywords_table == NULL) {
        keywords_table = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);
    }

    // Logical Keywords
    g_hash_table_insert(keywords_table, g_strdup("if"), GINT_TO_POINTER(KEYWORD_IF));
    g_hash_table_insert(keywords_table, g_strdup("else"), GINT_TO_POINTER(KEYWORD_ELSE));
    g_hash_table_insert(keywords_table, g_strdup("switch"), GINT_TO_POINTER(KEYWORD_SWITCH));
    g_hash_table_insert(keywords_table, g_strdup("case"), GINT_TO_POINTER(KEYWORD_CASE));
    g_hash_table_insert(keywords_table, g_strdup("default"), GINT_TO_POINTER(KEYWORD_DEFAULT));
    g_hash_table_insert(keywords_table, g_strdup("do"), GINT_TO_POINTER(KEYWORD_DO));
    g_hash_table_insert(keywords_table, g_strdup("while"), GINT_TO_POINTER(KEYWORD_WHILE));
    g_hash_table_insert(keywords_table, g_strdup("for"), GINT_TO_POINTER(KEYWORD_FOR));
    g_hash_table_insert(keywords_table, g_strdup("exit"), GINT_TO_POINTER(KEYWORD_EXIT));
    g_hash_table_insert(keywords_table, g_strdup("return"), GINT_TO_POINTER(KEYWORD_RETURN));
    g_hash_table_insert(keywords_table, g_strdup("continue"), GINT_TO_POINTER(KEYWORD_CONTINUE));
    g_hash_table_insert(keywords_table, g_strdup("break"), GINT_TO_POINTER(KEYWORD_BREAK));

    // Type Keywords
    g_hash_table_insert(keywords_table, g_strdup("void"), GINT_TO_POINTER(KEYWORD_VOID));
    g_hash_table_insert(keywords_table, g_strdup("int"), GINT_TO_POINTER(KEYWORD_INT));
    g_hash_table_insert(keywords_table, g_strdup("char"), GINT_TO_POINTER(KEYWORD_CHAR));
    g_hash_table_insert(keywords_table, g_strdup("double"), GINT_TO_POINTER(KEYWORD_DOUBLE));
    g_hash_table_insert(keywords_table, g_strdup("float"), GINT_TO_POINTER(KEYWORD_FLOAT));
    g_hash_table_insert(keywords_table, g_strdup("bool"), GINT_TO_POINTER(KEYWORD_BOOL));
    g_hash_table_insert(keywords_table, g_strdup("const"), GINT_TO_POINTER(KEYWORD_CONST));
    g_hash_table_insert(keywords_table, g_strdup("struct"), GINT_TO_POINTER(KEYWORD_STRUCT));
    g_hash_table_insert(keywords_table, g_strdup("union"), GINT_TO_POINTER(KEYWORD_UNION));
    g_hash_table_insert(keywords_table, g_strdup("enum"), GINT_TO_POINTER(KEYWORD_ENUM));
    g_hash_table_insert(keywords_table, g_strdup("typedef"), GINT_TO_POINTER(KEYWORD_TYPEDEF));

    // Memory Classes anators
    g_hash_table_insert(keywords_table, g_strdup("static"), GINT_TO_POINTER(KEYWORD_STATIC));
    g_hash_table_insert(keywords_table, g_strdup("extern"), GINT_TO_POINTER(KEYWORD_EXTERN));
    g_hash_table_insert(keywords_table, g_strdup("auto"), GINT_TO_POINTER(KEYWORD_AUTO));
    g_hash_table_insert(keywords_table, g_strdup("register"), GINT_TO_POINTER(KEYWORD_REGISTER));
    g_hash_table_insert(keywords_table, g_strdup("volatile"), GINT_TO_POINTER(KEYWORD_VOLATILE));

    // Constants
    g_hash_table_insert(keywords_table, g_strdup("true"), GINT_TO_POINTER(KEYWORD_TRUE));
    g_hash_table_insert(keywords_table, g_strdup("false"), GINT_TO_POINTER(KEYWORD_FALSE));

    // Special Keywords
    g_hash_table_insert(keywords_table, g_strdup("sizeof"), GINT_TO_POINTER(KEYWORD_SIZEOF));
}


void init_preprocessor_table() {
    if (preprocessor_table != NULL) {
        return;
    }

    if (preprocessor_table == NULL) {
        preprocessor_table = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);
    }

    g_hash_table_insert(preprocessor_table, g_strdup("#include"), GINT_TO_POINTER(TOKEN_INCLUDE));
    g_hash_table_insert(preprocessor_table, g_strdup("#define"), GINT_TO_POINTER(TOKEN_DEFINE));
    g_hash_table_insert(preprocessor_table, g_strdup("#undef"), GINT_TO_POINTER(TOKEN_UNDEF));
    g_hash_table_insert(preprocessor_table, g_strdup("#ifdef"), GINT_TO_POINTER(TOKEN_IFDEF));
    g_hash_table_insert(preprocessor_table, g_strdup("#ifndef"), GINT_TO_POINTER(TOKEN_IFNDEF));
    g_hash_table_insert(preprocessor_table, g_strdup("#if"), GINT_TO_POINTER(TOKEN_SHARP_IF));
    g_hash_table_insert(preprocessor_table, g_strdup("#else"), GINT_TO_POINTER(TOKEN_SHARP_ELSE));
    g_hash_table_insert(preprocessor_table, g_strdup("#elif"), GINT_TO_POINTER(TOKEN_SHARP_ELIF));
    g_hash_table_insert(preprocessor_table, g_strdup("#endif"), GINT_TO_POINTER(TOKEN_ENDIF));
    g_hash_table_insert(preprocessor_table, g_strdup("#error"), GINT_TO_POINTER(TOKEN_ERROR));
    g_hash_table_insert(preprocessor_table, g_strdup("#warning"), GINT_TO_POINTER(TOKEN_WARNING));
    g_hash_table_insert(preprocessor_table, g_strdup("#pragma"), GINT_TO_POINTER(TOKEN_PRAGMA));
}


void init_operators_table() {
    if (operators_table != NULL) {
        return;
    }
    
    if (operators_table == NULL) {
        operators_table = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);
    }
    
    // Arithmetic Operators
    g_hash_table_insert(operators_table, g_strdup("+"), GINT_TO_POINTER(TOKEN_PLUS));
    g_hash_table_insert(operators_table, g_strdup("-"), GINT_TO_POINTER(TOKEN_MINUS));
    g_hash_table_insert(operators_table, g_strdup("*"), GINT_TO_POINTER(TOKEN_STAR));
    g_hash_table_insert(operators_table, g_strdup("/"), GINT_TO_POINTER(TOKEN_SLASH));
    g_hash_table_insert(operators_table, g_strdup("%"), GINT_TO_POINTER(TOKEN_PERCENT));

    // Comment
    g_hash_table_insert(operators_table, g_strdup("//"), GINT_TO_POINTER(TOKEN_COMMENT));

    // Assignment Operators
    g_hash_table_insert(operators_table, g_strdup("="), GINT_TO_POINTER(TOKEN_ASSIGN));
    g_hash_table_insert(operators_table, g_strdup("+="), GINT_TO_POINTER(TOKEN_PLUS_ASSIGN));
    g_hash_table_insert(operators_table, g_strdup("-="), GINT_TO_POINTER(TOKEN_MINUS_ASSIGN));
    g_hash_table_insert(operators_table, g_strdup("*="), GINT_TO_POINTER(TOKEN_STAR_ASSIGN));
    g_hash_table_insert(operators_table, g_strdup("/="), GINT_TO_POINTER(TOKEN_SLASH_ASSIGN));
    g_hash_table_insert(operators_table, g_strdup("%="), GINT_TO_POINTER(TOKEN_PERCENT_ASSIGN));

    // Increment and Decrement
    g_hash_table_insert(operators_table, g_strdup("++"), GINT_TO_POINTER(TOKEN_INCREMENT));
    g_hash_table_insert(operators_table, g_strdup("--"), GINT_TO_POINTER(TOKEN_DECREMENT));

    // Equals Operators
    g_hash_table_insert(operators_table, g_strdup("=="), GINT_TO_POINTER(TOKEN_EQUALS));
    g_hash_table_insert(operators_table, g_strdup("!="), GINT_TO_POINTER(TOKEN_NOT_EQUALS));
    g_hash_table_insert(operators_table, g_strdup("<"), GINT_TO_POINTER(TOKEN_LESS_THAN));
    g_hash_table_insert(operators_table, g_strdup(">"), GINT_TO_POINTER(TOKEN_GREATER_THAN));
    g_hash_table_insert(operators_table, g_strdup("<="), GINT_TO_POINTER(TOKEN_LESS_EQUALS));
    g_hash_table_insert(operators_table, g_strdup(">="), GINT_TO_POINTER(TOKEN_GREATER_EQUALS));

    // Logic Operators
    g_hash_table_insert(operators_table, g_strdup("&&"), GINT_TO_POINTER(TOKEN_AND));
    g_hash_table_insert(operators_table, g_strdup("||"), GINT_TO_POINTER(TOKEN_OR));
    g_hash_table_insert(operators_table, g_strdup("!"), GINT_TO_POINTER(TOKEN_NOT));

    // Bitwise Operators
    g_hash_table_insert(operators_table, g_strdup("&"), GINT_TO_POINTER(TOKEN_BIT_AND));
    g_hash_table_insert(operators_table, g_strdup("|"), GINT_TO_POINTER(TOKEN_BIT_OR));
    g_hash_table_insert(operators_table, g_strdup("^"), GINT_TO_POINTER(TOKEN_BIT_XOR));
    g_hash_table_insert(operators_table, g_strdup("~"), GINT_TO_POINTER(TOKEN_BIT_NOT));
    g_hash_table_insert(operators_table, g_strdup("<<"), GINT_TO_POINTER(TOKEN_LEFT_SHIFT));
    g_hash_table_insert(operators_table, g_strdup(">>"), GINT_TO_POINTER(TOKEN_RIGHT_SHIFT));
    g_hash_table_insert(operators_table, g_strdup("&="), GINT_TO_POINTER(TOKEN_BIT_AND_EQUALS));
    g_hash_table_insert(operators_table, g_strdup("|="), GINT_TO_POINTER(TOKEN_BIT_OR_EQUALS));
    g_hash_table_insert(operators_table, g_strdup("^="), GINT_TO_POINTER(TOKEN_BIT_XOR_EQUALS));
    g_hash_table_insert(operators_table, g_strdup("<<="), GINT_TO_POINTER(TOKEN_LEFT_SHIFT_EQUALS));
    g_hash_table_insert(operators_table, g_strdup(">>="), GINT_TO_POINTER(TOKEN_RIGHT_SHIFT_EQUALS));

    // Punctuators
    g_hash_table_insert(operators_table, g_strdup("("), GINT_TO_POINTER(TOKEN_OPEN_PAREN));
    g_hash_table_insert(operators_table, g_strdup(")"), GINT_TO_POINTER(TOKEN_CLOSE_PAREN));
    g_hash_table_insert(operators_table, g_strdup("{"), GINT_TO_POINTER(TOKEN_OPEN_BRACE));
    g_hash_table_insert(operators_table, g_strdup("}"), GINT_TO_POINTER(TOKEN_CLOSE_BRACE));
    g_hash_table_insert(operators_table, g_strdup("["), GINT_TO_POINTER(TOKEN_OPEN_BRACKET));
    g_hash_table_insert(operators_table, g_strdup("]"), GINT_TO_POINTER(TOKEN_CLOSE_BRACKET));
    g_hash_table_insert(operators_table, g_strdup("\""), GINT_TO_POINTER(TOKEN_DOUBLE_QUOTES));
    g_hash_table_insert(operators_table, g_strdup("\'"), GINT_TO_POINTER(TOKEN_SINGLE_QUOTES));
    g_hash_table_insert(operators_table, g_strdup(";"), GINT_TO_POINTER(TOKEN_SEMICOLON));
    g_hash_table_insert(operators_table, g_strdup(":"), GINT_TO_POINTER(TOKEN_COLON));
    g_hash_table_insert(operators_table, g_strdup(","), GINT_TO_POINTER(TOKEN_COMMA));

    // Success Operators
    g_hash_table_insert(operators_table, g_strdup("."), GINT_TO_POINTER(TOKEN_DOT));
    g_hash_table_insert(operators_table, g_strdup("->"), GINT_TO_POINTER(TOKEN_ARROW));
}


void cleanup_all_hash_table(void) {
    if (keywords_table != NULL) {
        g_hash_table_destroy(keywords_table);
        keywords_table = NULL;
    }

    if (operators_table != NULL) {
        g_hash_table_destroy(operators_table);
        operators_table = NULL;
    }

    if (preprocessor_table != NULL) {
        g_hash_table_destroy(preprocessor_table);
        preprocessor_table = NULL;
    }
}
