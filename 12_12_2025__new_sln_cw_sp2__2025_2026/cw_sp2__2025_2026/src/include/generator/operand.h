#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2024_2025            *
*                         file: operand.h                   *
*                                                  (draft!) *
*************************************************************/

#define OPERAND_CODER(A, B, C, M, R)\
if (A ==* B) C = makeValueCode(B, C, M);\
if (A ==* B) C = makeIdentifierCode(B, C, M);

unsigned char* makeValueCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);
unsigned char* makeIdentifierCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);