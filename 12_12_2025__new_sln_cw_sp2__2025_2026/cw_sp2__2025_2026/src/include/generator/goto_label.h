#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2024_2025            *
*                         file: goto_lable.h                *
*                                                  (draft!) *
*************************************************************/

#include <string>
#include <map>
//#include <utility>
#include <stack>

extern std::map<std::string, std::pair<unsigned long long int, std::stack<unsigned long long int>>> labelInfoTable;

#define LABEL_GOTO_LABELE_CODER(A, B, C, M, R)\
if (A ==* B) C = makeLabelCode(B, C, M);\
if (A ==* B) C = makeGotoLabelCode(B, C, M);

unsigned char* makeLabelCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);

unsigned char* makeGotoLabelCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);