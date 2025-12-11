#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2024_2025            *
*                         file: repeat_until.h              *
*                                                  (draft!) *
*************************************************************/

#define REPEAT_UNTIL_CODER(A, B, C, M, R)\
if (A ==* B) C = makeRepeatCycleCode(B, C, M);\
if (A ==* B) C = makeUntileCode(B, C, M);\
if (A ==* B) C = makeNullStatementAfterUntilCycleCode(B, C, M);

unsigned char* makeRepeatCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);
unsigned char* makeUntileCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);
unsigned char* makeNullStatementAfterUntilCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);