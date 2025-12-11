#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2025_2026            *
*                         file: index.h                     *
*                                                  (draft!) *
*************************************************************/

#define INDEX_CODER(A, B, C, M, R)\
if (A ==* B) C = makeIndexCode(B, C, M);

unsigned char* makeIndexCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);