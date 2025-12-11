#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2024_2025            *
*                         file: not_equal.h                 *
*                                                  (draft!) *
*************************************************************/

#define NOT_EQUAL_CODER(A, B, C, M, R)\
if (A ==* B) C = makeIsNotEqualCode(B, C, M);

unsigned char* makeIsNotEqualCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);