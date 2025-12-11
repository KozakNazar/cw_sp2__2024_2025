#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2024_2025            *
*                         file: null_statement.h            *
*                                                  (draft!) *
*************************************************************/

#define NON_CONTEXT_NULL_STATEMENT(A, B, C, M, R)\
if (A ==* B) C = makeNullStatementAfterNonContextCode(B, C, M);

unsigned char* makeNullStatementAfterNonContextCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);