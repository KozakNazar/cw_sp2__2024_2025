#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2024_2025            *
*                         file: bitwise_or.h                *
*                                                  (draft!) *
*************************************************************/

#define BITWISE_OR_CODER(A, B, C, M, R)\
if (A ==* B) C = makeBitwiseOrCode(B, C, M);

unsigned char* makeBitwiseOrCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);