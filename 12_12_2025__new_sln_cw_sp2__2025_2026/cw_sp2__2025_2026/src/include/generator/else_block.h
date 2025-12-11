#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 //                              *
*                         file: else.h                      *
*                                                  (draft!) *
*************************************************************/

#define ELSE_BLOCK_CODER(A, B, C, M, R)\
if (A ==* B) C = makeElseCode(B, C, M);\
if (A ==* B) C = makeEndBlockAfterElseCode(B, C, M);

unsigned char* makeElseCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);
unsigned char* makeEndBlockAfterElseCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);
//TODO: for non-block//unsigned char* makeSemicolonOrNullStatementAfterElseCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);
//////: unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_SEMICOLON);
//////: stack+ if (!multitokenSize) multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_NULL_STATEMENT);