#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2024_2025            *
*                         file: less.h                      *
*                                                  (draft!) *
*************************************************************/

#define LESS_CODER(A, B, C, M, R)\
if (A ==* B) C = makeIsLessCode(B, C, M);

unsigned char* makeIsLessCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);