/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2024_2025            *
*                         file: def.h                       *
*                                                  (draft!) *
*************************************************************/

#define SUCCESS_STATE 0

#define LEXICAL_ANALYZE_MODE 1 // lexicalAnalyze
#define MAKE_LEXEMES_SEQUENSE 2 // ADD MODE
#define SYNTAX_ANALYZE_MODE 4
#define MAKE_AST 8 // ADD MODE
#define SEMANTIX_ANALYZE_MODE 16 // ADD MODE
#define MAKE_PREPARE 32 // ADD MODE
#define MAKE_C 64 // ADD MODE
#define MAKE_ASSEMBLY 128 // ADD MODE
#define MAKE_OBJECT 256 // ADD MODE
#define MAKE_BINARY 512 // ADD MODE
#define RUN_BINARY 1024 // ADD MODE

#define UNDEFINED_MODE 16384

#define INTERACTIVE_MODE 32768

#define SKIP_INTERACTIVE_IN_INTERACTIVE_MODE 65536

#define VIEW_INPUT_MODE 131072

#define VIEW_LEXEMS_AST_C_ASSEMBLY_NATIVE_OBJ_EXE_MODE 262144

#define FULL_COMPILER_MODE 2048 // !

#define DEBUG_MODE 4096

//#define DECLENUM(NAME, ...) typedef enum {__VA_ARGS__, size##NAME} NAME;
#define DECLENUM(NAME, ...) enum NAME {__VA_ARGS__, size##NAME};
#define GET_ENUM_SIZE(NAME) size##NAME
#define SET_QUADRUPLE_STR_MACRO_IN_ARRAY(ARRAY, NAME)\
ARRAY[MULTI_TOKEN_##NAME][0] = (char*)T_##NAME##_0;\
ARRAY[MULTI_TOKEN_##NAME][1] = (char*)T_##NAME##_1;\
ARRAY[MULTI_TOKEN_##NAME][2] = (char*)T_##NAME##_2;\
ARRAY[MULTI_TOKEN_##NAME][3] = (char*)T_##NAME##_3;