#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2024_2025            *
*                         file: add.h                       *
*                                                  (draft!) *
*************************************************************/

#define ADD_CODER(A, B, C, M, R)\
if (A ==* B) C = makeAddCode(B, C, M);

unsigned char* makeAddCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);