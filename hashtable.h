#include "data.h"

GHashTable* hash_table = NULL;
void init_key_word_table() {
    if (hash_table != NULL) {
        return;
    }

    hash_table = g_hash_table_new(g_str_hash, g_str_equal);

    // Logical Keywords
    g_hash_table_insert(hash_table, g_strdup("if"), GINT_TO_POINTER(KEYWORD_IF));
    g_hash_table_insert(hash_table, g_strdup("else"), GINT_TO_POINTER(KEYWORD_ELSE));
    g_hash_table_insert(hash_table, g_strdup("switch"), GINT_TO_POINTER(KEYWORD_SWITCH));
    g_hash_table_insert(hash_table, g_strdup("case"), GINT_TO_POINTER(KEYWORD_CASE));
    g_hash_table_insert(hash_table, g_strdup("default"), GINT_TO_POINTER(KEYWORD_DEFAULT));
    g_hash_table_insert(hash_table, g_strdup("do"), GINT_TO_POINTER(KEYWORD_DO));
    g_hash_table_insert(hash_table, g_strdup("while"), GINT_TO_POINTER(KEYWORD_WHILE));
    g_hash_table_insert(hash_table, g_strdup("for"), GINT_TO_POINTER(KEYWORD_FOR));
    g_hash_table_insert(hash_table, g_strdup("exit"), GINT_TO_POINTER(KEYWORD_EXIT));
    g_hash_table_insert(hash_table, g_strdup("return"), GINT_TO_POINTER(KEYWORD_RETURN));
    g_hash_table_insert(hash_table, g_strdup("continue"), GINT_TO_POINTER(KEYWORD_CONTINUE));
    g_hash_table_insert(hash_table, g_strdup("break"), GINT_TO_POINTER(KEYWORD_BREAK));

    // Type Keywords
    g_hash_table_insert(hash_table, g_strdup("void"), GINT_TO_POINTER(KEYWORD_VOID));
    g_hash_table_insert(hash_table, g_strdup("int"), GINT_TO_POINTER(KEYWORD_INT));
    g_hash_table_insert(hash_table, g_strdup("char"), GINT_TO_POINTER(KEYWORD_CHAR));
    g_hash_table_insert(hash_table, g_strdup("double"), GINT_TO_POINTER(KEYWORD_DOUBLE));
    g_hash_table_insert(hash_table, g_strdup("float"), GINT_TO_POINTER(KEYWORD_FLOAT));
    g_hash_table_insert(hash_table, g_strdup("bool"), GINT_TO_POINTER(KEYWORD_BOOL));
    g_hash_table_insert(hash_table, g_strdup("const"), GINT_TO_POINTER(KEYWORD_CONST));
    g_hash_table_insert(hash_table, g_strdup("struct"), GINT_TO_POINTER(KEYWORD_STRUCT));
    g_hash_table_insert(hash_table, g_strdup("union"), GINT_TO_POINTER(KEYWORD_UNION));
    g_hash_table_insert(hash_table, g_strdup("enum"), GINT_TO_POINTER(KEYWORD_ENUM));
    g_hash_table_insert(hash_table, g_strdup("typedef"), GINT_TO_POINTER(KEYWORD_TYPEDEF));

    // Memory Classes and Modificators
    g_hash_table_insert(hash_table, g_strdup("static"), GINT_TO_POINTER(KEYWORD_STATIC));
    g_hash_table_insert(hash_table, g_strdup("extern"), GINT_TO_POINTER(KEYWORD_EXTERN));
    g_hash_table_insert(hash_table, g_strdup("auto"), GINT_TO_POINTER(KEYWORD_AUTO));
    g_hash_table_insert(hash_table, g_strdup("register"), GINT_TO_POINTER(KEYWORD_REGISTER));
    g_hash_table_insert(hash_table, g_strdup("volatile"), GINT_TO_POINTER(KEYWORD_VOLATILE));

    // Constants
    g_hash_table_insert(hash_table, g_strdup("true"), GINT_TO_POINTER(KEYWORD_TRUE));
    g_hash_table_insert(hash_table, g_strdup("false"), GINT_TO_POINTER(KEYWORD_FALSE));
    g_hash_table_insert(hash_table, g_strdup("NULL"), GINT_TO_POINTER(KEYWORD_NULL));

    // Special Keywords
    g_hash_table_insert(hash_table, g_strdup("sizeof"), GINT_TO_POINTER(KEYWORD_SIZEOF));
    g_hash_table_insert(hash_table, g_strdup("#include"), GINT_TO_POINTER(KEYWORD_PREPROCESSOR));
    g_hash_table_insert(hash_table, g_strdup("#define"), GINT_TO_POINTER(KEYWORD_PREPROCESSOR));
}
