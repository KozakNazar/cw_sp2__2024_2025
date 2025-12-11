#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2024_2025            *
*                         file: semicolon.hxx               *
*                                                  (draft!) *
*************************************************************/

#define NON_CONTEXT_SEMICOLON_CODER(A, B, C, M, R)\
/* (1) Ignore phase*/if (A ==* B) C = makeSemicolonAfterNonContextCode(B, C, M);\
/* (2) Ignore phase*/if (A ==* B) C = makeSemicolonIgnoreContextCode(B, C, M);

unsigned char* makeSemicolonAfterNonContextCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);
unsigned char* makeSemicolonIgnoreContextCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);