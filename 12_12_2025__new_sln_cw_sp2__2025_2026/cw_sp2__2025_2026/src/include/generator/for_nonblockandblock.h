#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2024_2025            *
*                         file: for.h                       *
*                                                  (draft!) *
*************************************************************/

#define FOR_CODER(A, B, C, M, R)\
if (A ==* B) C = makeForCycleCode(B, C, M);\
if (A ==* B) C = makeToOrDowntoCycleCode(B, C, M);\
if (A ==* B) C = makeDoCycleCode(B, C, M);\
if (A ==* B) C = makeSemicolonOrNullStatementOrEndBlockAfterForCycleCode(B, C, M);

unsigned char* makeForCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);
unsigned char* makeToOrDowntoCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);
unsigned char* makeDoCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);
unsigned char* makeSemicolonOrNullStatementOrEndBlockAfterForCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);