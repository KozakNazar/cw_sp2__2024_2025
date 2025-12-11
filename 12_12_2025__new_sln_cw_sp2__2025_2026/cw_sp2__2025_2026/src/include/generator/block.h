#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2025_2026            *
*                         file: semicolon.h                 *
*                                                  (draft!) *
*************************************************************/

#define NON_CONTEXT_BLOCK_CODER(A, B, C, M, R)\
/* (1) Ignore phase*/if (A ==* B) C = makeBeginBlockAfterNonContextCode(B, C, M);\
/* (2) Ignore phase*/if (A ==* B) C = makeBeginBlockIgnoreContextCode(B, C, M);\
/* (1) Ignore phase*/if (A == *B) C = makeEndBlockAfterNonContextCode(B, C, M);\
/* (2) Ignore phase*/if (A == *B) C = makeEndBlockIgnoreContextCode(B, C, M);

unsigned char* makeBeginBlockAfterNonContextCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);
unsigned char* makeBeginBlockIgnoreContextCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);
unsigned char* makeEndBlockAfterNonContextCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);
unsigned char* makeEndBlockIgnoreContextCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);