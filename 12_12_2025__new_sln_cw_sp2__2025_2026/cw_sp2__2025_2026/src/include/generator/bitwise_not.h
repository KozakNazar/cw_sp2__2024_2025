#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2024_2025            *
*                         file: bitwise_not.h               *
*                                                  (draft!) *
*************************************************************/

#define BITWISE_NOT_CODER(A, B, C, M, R)\
if (A ==* B) C = makeBitwiseNotCode(B, C, M);

unsigned char* makeBitwiseNotCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);