#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2024_2025            *
*                         file: preparer.h                  *
*                                                  (draft!) *
*************************************************************/

int precedenceLevel(char* lexemStr);
bool isLeftAssociative(char* lexemStr);
bool isSplittingOperator(char* lexemStr);
void makePrepare4IdentifierOrValue(struct LexemInfo** lastLexemInfoInTable, struct LexemInfo** lastTempLexemInfoInTable);
void makePrepare4Operators(struct LexemInfo** lastLexemInfoInTable, struct LexemInfo** lastTempLexemInfoInTable);
void makePrepare4LeftParenthesis(struct LexemInfo** lastLexemInfoInTable, struct LexemInfo** lastTempLexemInfoInTable);
void makePrepare4RightParenthesis(struct LexemInfo** lastLexemInfoInTable, struct LexemInfo** lastTempLexemInfoInTable);
unsigned int makePrepareEnder(struct LexemInfo** lastLexemInfoInTable, struct LexemInfo** lastTempLexemInfoInTable);
long long int getPrevNonParenthesesIndex(struct LexemInfo* lexemInfoInTable, unsigned long long currIndex);
long long int getEndOfNewPrevExpressioIndex(struct LexemInfo* lexemInfoInTable, unsigned long long currIndex);
unsigned long long int getNextEndOfExpressionIndex(struct LexemInfo* lexemInfoInTable, unsigned long long prevEndOfExpressionIndex);
void makePrepare(struct LexemInfo* lexemInfoInTable, struct LexemInfo** lastLexemInfoInTable, struct LexemInfo** lastTempLexemInfoInTable);