#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2024_2025            *
*                         file: greater.h                   *
*                                                  (draft!) *
*************************************************************/

#define GREATER_CODER(A, B, C, M, R)\
if (A ==* B) C = makeIsGreaterCode(B, C, M);

unsigned char* makeIsGreaterCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);