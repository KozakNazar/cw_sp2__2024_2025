#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2024_2025            *
*                         file: output.hxx                  *
*                                                  (draft!) *
*************************************************************/

#define OUTPUT_CODER(A, B, C, M, R)\
if (A ==* B) C = makePutCode(B, C, M);

unsigned char* makePutCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);