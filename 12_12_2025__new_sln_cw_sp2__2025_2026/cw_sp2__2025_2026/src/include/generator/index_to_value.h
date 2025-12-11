#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2025_2026            *
*                         file: index_to_value.h            *
*                                                  (draft!) *
*************************************************************/

#define INDEX_TO_VALUE_CODER(A, B, C, M, R)\
if (A ==* B) C = makeIndexToValueCode(B, C, M);

unsigned char* makeIndexToValueCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);