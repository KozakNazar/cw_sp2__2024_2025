#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2024_2025            *
*                         file: greater_or_equal.h          *
*                                                  (draft!) *
*************************************************************/

#define GREATER_OR_EQUAL_CODER(A, B, C, M, R)\
if (A ==* B) C = makeIsGreaterOrEqualCode(B, C, M);

unsigned char* makeIsGreaterOrEqualCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);