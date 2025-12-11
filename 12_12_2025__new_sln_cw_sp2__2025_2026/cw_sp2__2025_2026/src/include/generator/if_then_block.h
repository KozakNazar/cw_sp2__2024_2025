#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 //                              *
*                         file: if_then_block.h             *
*                                                  (draft!) *
*************************************************************/

#define IF_THEN_BLOCK_CODER(A, B, C, M, R)\
if (A ==* B) C = makeIfCode(B, C, M);\
if (A ==* B) C = makeThenBlockCodeAfterIfCode(B, C, M);\
if (A ==* B) C = makeEndBlockAfterThenCodeAfterIfCode(B, C, M);

unsigned char* makeIfCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);
unsigned char* makeThenBlockCodeAfterIfCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);
unsigned char* makeEndBlockAfterThenCodeAfterIfCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);
//TODO: for non-block//unsigned char* makeSemicolonOrNullStatementAfterThenCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);
//////: unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_SEMICOLON);
//////: stack+ if (!multitokenSize) multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_NULL_STATEMENT);