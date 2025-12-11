#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2024_2025            *
*                         file: semantics.h                 *
*                                                  (draft!) *
*************************************************************/

#include "../../include/def.h"
#include "../../include/generator/generator.h"
#include "../../include/lexica/lexica.h"

#define	DISABLE_CHECKING_VARIABLE_INITIALIZATION

#define COLLISION_II_STATE    128
#define COLLISION_LL_STATE    129
#define COLLISION_IL_STATE    130
#define COLLISION_I_STATE     132
#define COLLISION_L_STATE     136
#define COLLISION_IK_STATE    144
#define UNINITIALIZED_I_STATE 160

#define NO_IMPLEMENT_CODE_STATE 256

unsigned long long int getPostDataSectionLexemIndex(LexemInfo* lexemInfoTable, Grammar* grammar);
int checkingInternalCollisionInDeclarations(LexemInfo* lexemInfoTable, Grammar* grammar, char(*identifierIdsTable)[MAX_LEXEM_SIZE], char** errorMessagesPtrToLastBytePtr);
int checkingVariableInitialization(LexemInfo* lexemInfoTable, Grammar* grammar, char(*identifierIdsTable)[MAX_LEXEM_SIZE], char** errorMessagesPtrToLastBytePtr);
int checkingCollisionInDeclarationsByKeyWords(char(*identifierIdsTable)[MAX_LEXEM_SIZE], char** errorMessagesPtrToLastBytePtr);
int semanticsAnalyze(LexemInfo* lexemInfoTable, Grammar* grammar, char(*identifierIdsTable)[MAX_LEXEM_SIZE], char* errorMessagesPtrToLastBytePtr);