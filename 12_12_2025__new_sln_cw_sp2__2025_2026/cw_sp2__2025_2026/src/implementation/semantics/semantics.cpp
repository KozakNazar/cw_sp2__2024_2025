#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2024_2025            *
*                         file: semantics.cpp               *
*                                                  (draft!) *
*************************************************************/
//#include "../../include/config.h"
#include "../../include/syntax/syntax.h"
#include "../../include/semantics/semantics.h"
#include "stdio.h"
#include "string.h"

//#include <iterator>
#include <regex>

unsigned long long int getPostDataSectionLexemIndex(LexemInfo* lexemInfoTable, Grammar* grammar) {
	int lexemIndex = 0;
	//struct LexemInfo* unexpectedLexemfailedTerminal = nullptr;

	if (getIndexAfterFragmentSyntax((char*)"program____part1", lexemIndex, lexemInfoTable, grammar, 0/*, &unexpectedLexemfailedTerminal*/)
		&& lexemInfoTable[lexemIndex].lexemStr[0] != '\0') {
		return lexemIndex;
	}

	printf("Error: No find data section end index!\r\n");
	return ~0;
}

int checkingInternalCollisionInDeclarations(LexemInfo* lexemInfoTable, Grammar* grammar, char(*identifierIdsTable)[MAX_LEXEM_SIZE], char ** errorMessagesPtrToLastBytePtr) {
//	int returnState = SUCCESS_STATE;
	unsigned long long int postDataSectionLexemIndex = 0;
	if (~0 == (postDataSectionLexemIndex = getPostDataSectionLexemIndex(lexemInfoTable, grammar))) { // TODO: ADD TO START CODE
		*errorMessagesPtrToLastBytePtr += sprintf(*errorMessagesPtrToLastBytePtr, "Error get of data section last lexem index.\r\n");
		return ~SUCCESS_STATE;
	}
	for (unsigned int index = 0; identifierIdsTable[index][0] != '\0'; ++index) {
		char isDeclaredIdentifier = 0;
		char isDeclaredIdentifierCollision = 0;
		unsigned int lexemIndex = 0;

		for (lexemIndex = 0; lexemIndex < postDataSectionLexemIndex; ++lexemIndex) {
			if (lexemesInfoTable[lexemIndex].tokenType == IDENTIFIER_LEXEME_TYPE) {
				if (!strncmp(identifierIdsTable[index], lexemesInfoTable[lexemIndex].lexemStr, MAX_LEXEM_SIZE)) {
					if (isDeclaredIdentifier) {
						isDeclaredIdentifierCollision = 1;
					}
					isDeclaredIdentifier = 1;
				}
			}
		}

		char isLabel = 0;
		char isDeclaredLabel = 0;
		char isDeclaredLabelCollision = 0;
		for (unsigned int lexemIndex = 0; lexemesInfoTable[lexemIndex].lexemStr[0] != '\0'; ++lexemIndex) {
			if (lexemesInfoTable[lexemIndex].tokenType != IDENTIFIER_LEXEME_TYPE || strncmp(identifierIdsTable[index], lexemesInfoTable[lexemIndex].lexemStr, MAX_LEXEM_SIZE)) {
				continue;
			}
			if (!strncmp(lexemesInfoTable[lexemIndex + 1].lexemStr, tokenStruct[MULTI_TOKEN_COLON][0], MAX_LEXEM_SIZE)) {
				if (isDeclaredLabel) {
					isDeclaredLabelCollision = 1;
				}
				isLabel = 1;
				isDeclaredLabel = 1;
			}
			if (lexemIndex && !strncmp(lexemesInfoTable[lexemIndex - 1].lexemStr, tokenStruct[MULTI_TOKEN_GOTO][0], MAX_LEXEM_SIZE)) {
				isLabel = 1;
			}
		}

//		//tryToGetKeyWord(struct LexemInfo* lexemInfoInTable);
//		if (SUCCESS_STATE != checkingCollisionInDeclarationsByKeyWords(identifierIdsTable[index])) {
//			return COLLISION_IK_STATE;
//		}

		if (isDeclaredIdentifierCollision) {
			printf("Collision(identifier/identifier): %s\r\n", identifierIdsTable[index]);
			*errorMessagesPtrToLastBytePtr += snprintf(*errorMessagesPtrToLastBytePtr, MAX_LEXEM_SIZE + strlen("Collision(identifier/identifier): #\r\n"), "Collision(identifier/identifier): %s\r\n", identifierIdsTable[index]);
			return COLLISION_II_STATE;
		}
		if (isDeclaredLabelCollision) {
			printf("Collision(label/label): %s\r\n", identifierIdsTable[index]);
			*errorMessagesPtrToLastBytePtr += snprintf(*errorMessagesPtrToLastBytePtr, MAX_LEXEM_SIZE + strlen("Collision(label/label): #\r\n"), "Collision(label/label): %s\r\n", identifierIdsTable[index]);
			return COLLISION_LL_STATE;
		}
		if (isDeclaredIdentifier && isLabel) {
			printf("Collision(identifier/label): %s\r\n", identifierIdsTable[index]);
			*errorMessagesPtrToLastBytePtr += snprintf(*errorMessagesPtrToLastBytePtr, MAX_LEXEM_SIZE + strlen("Collision(identifier/label): #\r\n"), "Collision(identifier/label): %s\r\n", identifierIdsTable[index]);
			return COLLISION_IL_STATE;
		}
		else if (!isDeclaredIdentifier && !isLabel && !isDeclaredLabel) {
			printf("Undeclared identifier: %s\r\n", identifierIdsTable[index]);
			*errorMessagesPtrToLastBytePtr += snprintf(*errorMessagesPtrToLastBytePtr, MAX_LEXEM_SIZE + strlen("Undeclared identifier: #\r\n"), "Undeclared identifier: %s\r\n", identifierIdsTable[index]);
			return COLLISION_I_STATE;
		}
		else if (isLabel && !isDeclaredLabel) {
			printf("Undeclared label: %s\r\n", identifierIdsTable[index]);
			*errorMessagesPtrToLastBytePtr += snprintf(*errorMessagesPtrToLastBytePtr, MAX_LEXEM_SIZE + strlen("Undeclared label: #\r\n"), "Undeclared label: %s\r\n", identifierIdsTable[index]);
			return COLLISION_L_STATE;
		}
	}

//	if (returnState == SUCCESS_STATE) {
		printf("Declaration verification was successful!\r\n");
//	}
//
	return SUCCESS_STATE;
}

int checkingVariableInitialization(LexemInfo* lexemInfoTable, Grammar* grammar, char(*identifierIdsTable)[MAX_LEXEM_SIZE], char** errorMessagesPtrToLastBytePtr) {
	int returnState = SUCCESS_STATE;

	unsigned long long int lastDataSectionLexemIndex = 0;
	if (~0 == (lastDataSectionLexemIndex = getPostDataSectionLexemIndex(lexemInfoTable, grammar))) { // TODO: ADD TO START CODE
		*errorMessagesPtrToLastBytePtr += sprintf(*errorMessagesPtrToLastBytePtr, "Error get of data section last lexem index.\r\n");
		return ~SUCCESS_STATE;
	}

	for (unsigned int index = 0; identifierIdsTable[index][0] != '\0'; ++index) {
		for (unsigned int lexemIndex = lastDataSectionLexemIndex; lexemesInfoTable[lexemIndex].lexemStr[0] != '\0'; ++lexemIndex) {
			if (lexemesInfoTable[lexemIndex].tokenType != IDENTIFIER_LEXEME_TYPE || strncmp(identifierIdsTable[index], lexemesInfoTable[lexemIndex].lexemStr, MAX_LEXEM_SIZE)) {
				continue;
			}
			if (!strncmp(lexemesInfoTable[lexemIndex + 1].lexemStr, tokenStruct[MULTI_TOKEN_COLON][0], MAX_LEXEM_SIZE)) {
				continue;
			}
			if (lexemIndex && !strncmp(lexemesInfoTable[lexemIndex - 1].lexemStr, tokenStruct[MULTI_TOKEN_GOTO][0], MAX_LEXEM_SIZE)) {
				continue;
			}

			int prevNonOpenParenthesesIndex = -1;
			for (; !strcmp(lexemesInfoTable[lexemIndex + prevNonOpenParenthesesIndex].lexemStr, "("); --prevNonOpenParenthesesIndex);
			if (!strncmp(lexemesInfoTable[lexemIndex + 1].lexemStr, tokenStruct[MULTI_TOKEN_RLBIND][0], MAX_LEXEM_SIZE)
				||					
				!strncmp(lexemesInfoTable[lexemIndex - 1].lexemStr, tokenStruct[MULTI_TOKEN_LRBIND][0], MAX_LEXEM_SIZE)
				||					
				//!strncmp(lexemesInfoTable[-1].lexemStr, tokenStruct[MULTI_TOKEN_INPUT][0], MAX_LEXEM_SIZE)					
				//||					
				//!strncmp(lexemesInfoTable[-2].lexemStr, tokenStruct[MULTI_TOKEN_INPUT][0], MAX_LEXEM_SIZE)					
				//||					
				!strncmp(lexemesInfoTable[lexemIndex + prevNonOpenParenthesesIndex].lexemStr, tokenStruct[MULTI_TOKEN_INPUT][0], MAX_LEXEM_SIZE)
				){						
				break;					
			}
			else if (!strncmp(lexemesInfoTable[lexemIndex + 1].lexemStr, "[", MAX_LEXEM_SIZE)) {
				bool bindDetect = false;
				int openBracketCount = 1;
				for (int tempLexemInfoInTableAddonScanIndex = lexemIndex + 2; lexemesInfoTable[tempLexemInfoInTableAddonScanIndex].lexemStr[0] != '\0'; ++tempLexemInfoInTableAddonScanIndex) {
					if (!strncmp(lexemesInfoTable[tempLexemInfoInTableAddonScanIndex].lexemStr, "["/*TODO: add to config.h*/, MAX_LEXEM_SIZE)) {
						++openBracketCount;
						continue;
					}

					if (!strncmp(lexemesInfoTable[tempLexemInfoInTableAddonScanIndex].lexemStr, "]"/*TODO: add to config.h*/, MAX_LEXEM_SIZE)) {
						if (!--openBracketCount) {
							if (!strncmp(lexemesInfoTable[tempLexemInfoInTableAddonScanIndex + 1].lexemStr, tokenStruct[MULTI_TOKEN_RLBIND][0], MAX_LEXEM_SIZE)) {
								bindDetect = true;
							}
							break;
						}
					}

				}
				if (bindDetect) {
					break;
				}
			}

			printf("Uninitialized: %s\r\n", identifierIdsTable[index]);			
			*errorMessagesPtrToLastBytePtr += snprintf(*errorMessagesPtrToLastBytePtr, MAX_LEXEM_SIZE + strlen("Uninitialized: #\r\n"), "Uninitialized: %s\r\n", identifierIdsTable[index]);
			returnState = UNINITIALIZED_I_STATE;					
			break;			
		}
	}
	
	if (returnState == SUCCESS_STATE) {
		printf("Variable initialization checking was successful!\r\n");
	}

	return returnState;
}

int checkingCollisionInDeclarationsByKeyWords(char(*identifierIdsTable)[MAX_LEXEM_SIZE], char** errorMessagesPtrToLastBytePtr) {
	int returnState = SUCCESS_STATE;
	
	char keywords_re[] = KEYWORDS_RE;
	char keywords_[sizeof(keywords_re)] = { '\0' };
	prepareKeyWordIdGetter(keywords_, keywords_re);

	for (unsigned int index = 0; identifierIdsTable[index][0] != '\0'; ++index) {
		if (std::regex_match(std::string(identifierIdsTable[index]), std::regex(keywords_re))) {
			printf("Declaration matches keyword: %s\r\n", identifierIdsTable[index]);
			*errorMessagesPtrToLastBytePtr += snprintf(*errorMessagesPtrToLastBytePtr, MAX_LEXEM_SIZE + strlen("Declaration matches keyword: #\r\n"), "Declaration matches keyword: %s\r\n", identifierIdsTable[index]);
			returnState = COLLISION_IK_STATE;
		}
	}

	printf("Declaration verification for keyword collision was successful!\r\n");
	return SUCCESS_STATE;
}

int semanticsAnalyze(LexemInfo* lexemInfoTable, Grammar* grammar, char(*identifierIdsTable)[MAX_LEXEM_SIZE], char* errorMessagesPtrToLastBytePtr){
	int returnState = SUCCESS_STATE;

	if (   SUCCESS_STATE != (returnState = checkingInternalCollisionInDeclarations(lexemesInfoTable, grammar, identifierIdsTable, &errorMessagesPtrToLastBytePtr))
#ifndef	DISABLE_CHECKING_VARIABLE_INITIALIZATION
		|| SUCCESS_STATE != (returnState = checkingVariableInitialization(lexemesInfoTable, grammar, identifierIdsTable, &errorMessagesPtrToLastBytePtr))
#endif
		|| SUCCESS_STATE != (returnState = checkingCollisionInDeclarationsByKeyWords(identifierIdsTable, &errorMessagesPtrToLastBytePtr))
		) {
		return returnState;
	}

	return SUCCESS_STATE;
}