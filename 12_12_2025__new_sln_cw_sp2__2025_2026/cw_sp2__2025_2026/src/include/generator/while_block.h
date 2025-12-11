#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2024_2025            *
*                         file: while_block.h               *
*                                                  (draft!) *
*************************************************************/

#define WHILE_BLOCK_CODER(A, B, C, M, R)\
if (A ==* B) C = makeWhileCycleCode(B, C, M);\
if (A ==* B) C = makeBlockBeginWhileCycleCode(B, C, M);\
if (A ==* B) C = make0LevelContinueOr1LevelIfContinueWhileCycleCode(B, C, M);\
if (A ==* B) C = make0LevelExitOr1LevelIfExitWhileCycleCode(B, C, M);\
if (A ==* B) C = makeEndWhileAfterWhileCycleCode(B, C, M);

unsigned char* makeWhileCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);
unsigned char* makeBlockBeginWhileCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);
unsigned char* make0LevelContinueOr1LevelIfContinueWhileCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);
unsigned char* make0LevelExitOr1LevelIfExitWhileCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);
unsigned char* makeEndWhileAfterWhileCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);