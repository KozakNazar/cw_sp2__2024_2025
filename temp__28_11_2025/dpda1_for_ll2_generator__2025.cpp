#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "../cw_sp2__2025_2026/src/include/def.h"
#include "../cw_sp2__2025_2026/src/include/config.h"
#include "../cw_sp2__2025_2026/src/include/syntax/syntax.h"

#include "../built_src/dpda1forll2.hpp"

#define MAX_RULES 356

#define MAX_TOKEN_SIZE 128
//#define MAX_RTOKEN_COUNT 12

//typedef struct {
//	char lhs[MAX_TOKEN_SIZE];
//	int rhs_count;
//	char rhs[MAX_RTOKEN_COUNT][MAX_TOKEN_SIZE];
//	//
//	char las[MAX_TOKEN_SIZE]; // lookahead
//} Rule;
//
//typedef struct { // TODO: add lookahead info
//	Rule rules[MAX_RULES];
//	int rule_count;
//	char start_symbol[MAX_TOKEN_SIZE];
//} Grammar;

Grammar grammar = {
	GRAMMAR_LL2__2025
};

//#include "../built_src/config2.h"
//Grammar grammar_123 = { GRAMMAR_123 };

DPDA1Program dpdaProgram123;

void addAnigilateInstruction(/*no args*/) {

}

void addAnigilateInstructions(/*no args*/) {


}

char getLexemId(char* str) { // and terminal
	exit(0);
	return 123;
}

const char* getLexemStrById(char id) {
	return "123";
}

unsigned long long int getLexemTypeById(char id) {


//#define KEYWORD_LEXEME_TYPE 1
//#define IDENTIFIER_LEXEME_TYPE 2 // #define LABEL_LEXEME_TYPE 8
//#define VALUE_LEXEME_TYPE 4
//#define UNEXPEXTED_LEXEME_TYPE 127


	return UNEXPEXTED_LEXEME_TYPE;
}

#if 0
void addNonTerminalInterpretationInstruction(DPDA1Program* dpdaProgramPtr, Rule* rule/*, int instructionIndex*/) {
	if (!dpdaProgramPtr || !rule) {
		return;
	}

	//lookahead symbol

	unsigned int lookahead = getNonterminlId(rule->las);
	unsigned int nonterminlId = getNonterminlId(rule->lhs);

	(*dpdaProgramPtr)[lookahead][nonterminlId].tapeAction = NO_SCROLL;
	StackUpdate* stackUpdate = &(*dpdaProgramPtr)[lookahead][nonterminlId].stackUpdate;
	stackUpdate->stackAction = PUSH; // StackAction::
	//unsigned int * stackAddon = (unsigned int*) stackUpdate->stackAddon;

	for (int rhsIndex = 0; rhsIndex < rule->rhs_count; ++rhsIndex) {
		stackUpdate->stackAddon[rhsIndex] = getNonterminlId(rule->rhs[rhsIndex]);
	}
	stackUpdate->stackAddon[rule->rhs_count] = 0;

	//int* stackAddonLastElementPtr = stackUpdate->stackAddon;	
	//while (*(stackAddonLastElementPtr++));
	//++stackAddonLastElementPtr;
	//	for (; stackAddonLastElementPtr < stackUpdate->stackAddon; --stackAddonLastElementPtr) {
	//		*(dpda1->stack_above_top++) = *stackAddonLastElementPtr;
	//	}

}
#endif

void addNonTerminalInterpretationInstructions(DPDA1Program* dpdaProgramPtr, Grammar* grammar) {
	if (!dpdaProgramPtr) {
		return;
	}

}

char getLexemId(char * lexemStr);

// used
// init f
void initBuild_All“˘ÚDeadStatesToDeadState__DPDA1forLL2(Grammar& grammar, DPDA1Program& dpda1Program, DPDA1IndexingForSecondElement& dpda1IndexingForSecondElement) {
	// MIN_TERMIN
	// All Symbol
	char emptyStringCode = getLexemId((char*)"");
	char deadStateCode = getLexemId((char*)"DEAD_STATE");
	for (char toptapeAndStackCode = 255; toptapeAndStackCode++;) {
#define ROW_INDEX toptapeAndStackCode
#define COLUMN_INDEX toptapeAndStackCode
		for (char tapeCode = 255; tapeCode++;) {
			if (dpda1Program[toptapeAndStackCode][tapeCode].tapeAction == deadStateCode) {
				continue;
			}
			if (dpda1Program[toptapeAndStackCode][toptapeAndStackCode].tapeAction == -1) { // ... // ????
				printf("Error: no support model\r\n");
				exit(0);
			}

			dpda1Program[ROW_INDEX][COLUMN_INDEX].stackUpdate.stackAction = PUSH; // no POP prev state (used for detect error) // NEW 08.2025

			dpda1Program[ROW_INDEX][COLUMN_INDEX].tapeAction = SCROLL_TO_RIGHT;

//08.2025	dpda1Program[toptapeAndStackCode][toptapeAndStackCode].stackUpdate.stackAction = POP; // (2)
//08.2025	dpda1Program[toptapeAndStackCode][toptapeAndStackCode].stackUpdate.stackAction = PUSH; // (!)
//08.2025	dpda1Program[toptapeAndStackCode][toptapeAndStackCode].stackUpdate.stackAction = PUSH; // (!)

			//dpda1Program[ROW_INDEX][columnIndex].stackUpdate.stackAddon[rhsVariantAddonIndex][rTokekIndex] = emptyElementCode;

			dpda1Program[ROW_INDEX][COLUMN_INDEX].rhsVariantAddonIndexMask = 0; // NEW 08.2025

			dpda1Program[ROW_INDEX][COLUMN_INDEX].stackUpdate.stackAddon[0/*rhsVariantAddonIndex NEW 08.2025*/][0] = deadStateCode;
			for (unsigned int rTokekIndex = 1; rTokekIndex < MAX_RTOKEN_COUNT; ++rTokekIndex) {
				dpda1Program[ROW_INDEX][COLUMN_INDEX].stackUpdate.stackAddon[0/*rhsVariantAddonIndex NEW 08.2025*/][rTokekIndex] = emptyStringCode; // (!)
			}

//			? dpda1IndexingForSecondElement;
//			dpda1IndexingForSecondElement[][] = 0; // NOT USE // 08.2025
		}
#undef ROW_INDEX
#undef COLUMN_INDEX
	}
}

// set -1 

// used
void buildDeadState__DPDA1forLL2(Grammar& grammar, DPDA1Program& dpda1Program, DPDA1IndexingForSecondElement& dpda1IndexingForSecondElement) {
	// MIN_TERMIN
	// All Symbol
	//  for (char toptapeAndStackCode = 255; false && toptapeAndStackCode++;) {
	//  	for (char tapeCode = 255; tapeCode++;) {
	//  		if (dpda1Program[toptapeAndStackCode][toptapeAndStackCode].tapeAction == -1) {
	//  			printf("Error: no support model\r\n");
	//  			exit(0);
	//  		}
	//  
	//  		dpda1Program[toptapeAndStackCode][toptapeAndStackCode].tapeAction = SCROLL_TO_RIGHT;
	//  		dpda1Program[toptapeAndStackCode][toptapeAndStackCode].stackUpdate.stackAction = POP; // (2)
	//  
	//  		? dpda1IndexingForSecondElement;
	//  	}
	//  }

	//char deadStateCode = getLexemId((char*)"DEAD_STATE");
	//char passStateCode = getLexemId((char*)"PASS_STATE");

//		for (char tapeCode = 255; tapeCode++;) {
//			if (dpda1Program[tapeCode][deadStateCode].tapeAction == -1) {
//				dpda1Program[tapeCode][deadStateCode].tapeAction = SCROLL_TO_RIGHT;
//				dpda1Program[tapeCode][deadStateCode].stackUpdate.stackAction = NOTHING;
//			}
//			else {
//				printf("Error\r\n");
//				exit(0);
//			}
//		}

		// no use dpda1IndexingForSecondElement (dpda1IndexingForSecondElement only for instruction PUSH)
		// for other init 0 for dpda1IndexingForSecondElement






		// + ‰ÂÂ‚Ó ‚Ë‚Ó‰Û
		


		char emptyStringCode = getLexemId((char*)"");
		char deadStateCode = getLexemId((char*)"DEAD_STATE");
		for (char tapeCode = 255; tapeCode++;) {
#define ROW_INDEX tapeCode
#define COLUMN_INDEX deadStateCode			
				// tape
				dpda1Program[ROW_INDEX][COLUMN_INDEX].tapeAction = SCROLL_TO_RIGHT;

				// stack
				dpda1Program[ROW_INDEX][COLUMN_INDEX].stackUpdate.stackAction = NOTHING;
				dpda1Program[ROW_INDEX][COLUMN_INDEX].rhsVariantAddonIndexMask = 0; // not useed for dead state
				for (unsigned int rTokekIndex = 0; rTokekIndex < MAX_RTOKEN_COUNT; ++rTokekIndex) { // not useed for dead state
					dpda1Program[ROW_INDEX][COLUMN_INDEX].stackUpdate.stackAddon[0/*rhsVariantAddonIndex NEW 08.2025*/][rTokekIndex] = emptyStringCode; // (!)
				}
#undef ROW_INDEX
#undef COLUMN_INDEX
		}
}

// used
// tape scroll
void buildAcceptTapeElement__DPDA1forLL2(Grammar& grammar, DPDA1Program& dpda1Program, DPDA1IndexingForSecondElement& dpda1IndexingForSecondElement) {
	// MIN_TERMIN
	// All Symbol -> only non-terminal
	char emptyStringCode = getLexemId((char*)"");
	for (char tapeAndTopStackCode = 255; tapeAndTopStackCode++;) {
#define ROW_INDEX tapeAndTopStackCode
#define COLUMN_INDEX tapeAndTopStackCode
		for (char tapeCode = 255; tapeCode++;) {
			//if (dpda1Program[toptapeAndStackCode][toptapeAndStackCode].tapeAction == -1) { // ?
			//	printf("Error: no support model\r\n");
			//	exit(0);
			//}

			// tape
			dpda1Program[ROW_INDEX][COLUMN_INDEX].tapeAction = SCROLL_TO_RIGHT; // SHIFT

			// stack
			dpda1Program[ROW_INDEX][COLUMN_INDEX].stackUpdate.stackAction = POP; // (2)
			dpda1Program[ROW_INDEX][COLUMN_INDEX].rhsVariantAddonIndexMask = 0; // not useed for accept state (? dpda1IndexingForSecondElement; ==> ignore => mask 0)
			for (unsigned int rTokekIndex = 0; rTokekIndex < MAX_RTOKEN_COUNT; ++rTokekIndex) { // not useed for dead state
				dpda1Program[ROW_INDEX][COLUMN_INDEX].stackUpdate.stackAddon[0/*rhsVariantAddonIndex NEW 08.2025*/][rTokekIndex] = emptyStringCode; // (!)
			}		
		}
#undef ROW_INDEX
#undef COLUMN_INDEX
	}
}

// tape scroll
void preBildDPDA1forLL2(Grammar& grammar, DPDA1Program& dpda1Program, DPDA1IndexingForSecondElement& dpda1IndexingForSecondElement) {
	// set -1

	// dpda1IndexingForSecondElement[rowIndex][columnIndex]; // -1

	// MIN_TERMIN
	// All Symbol

	for (char topStackCode = 255; topStackCode++;) {
		//if no dead state
		for (char tapeCode = 255; tapeCode++;) {
			// if no setted (-1)

			//if no dead state

			if (dpda1Program[tapeCode][topStackCode].tapeAction == -1) {
				dpda1Program[tapeCode][topStackCode].tapeAction = SCROLL_TO_RIGHT;
			
			}
				TapeAction tapeAction; // (1)
			StackUpdate stackUpdate; // (2)
		}

	}

}

// TODO: add dead state (SCROLL STATE) and to state (SCROLL STATE)!
void buildDPDA1forLL2_(Grammar& grammar, DPDA1Program& dpda1Program, DPDA1IndexingForSecondElement& dpda1IndexingForSecondElement) {
	// TODO: add dead state (SCROLL STATE) and to state (SCROLL STATE)!

	char toPassStateCode = getLexemId((char*)"TO_PASS_STATE");

	char passStateCode = getLexemId((char*)"PASS_STATE");

	for (char topStackCode = 255; topStackCode++;) {
		//if no dead state
			for (char firstMarkCode = 255; topStackCode != passStateCode && firstMarkCode++;) {
				// if no setted (-1)
				
				//if no dead state
			}

	}


}

// used
//?// two table //+//
// STACK_POP_AND_MULTIPLIPUSH
void buildRulePartForDPDA1forLL2(Grammar & grammar, DPDA1Program & dpda1Program, DPDA1IndexingForSecondElement& dpda1IndexingForSecondElement) {
	char emptyElementCode = getLexemId((char*)"");
	char deadStateCode = getLexemId((char*)"DEAD_STATE");

//#define BUILD_C2P_AST_TYPE_BY_DPDA1
#ifndef BUILD_C2P_AST_TYPE_BY_DPDA1
#define	BUILD_P2C_AST_TYPE_BY_DPDA1 // TODO: no default
#endif
//#if !defined(BUILD_AST_BY_DPDA1) || defined(BUILD_P2C_AST_TYPE_BY_DPDA1)

#ifdef BUILD_P2C_AST_TYPE_BY_DPDA1
	char popStackInFoutStateCode = getLexemId((char*)"POP_STACK_IN_F_OUT_STATE");
#endif
	for (MarkedRule* multiRule = grammar.multiRules; multiRule->firstMarksType; ++multiRule) {
		char* currSteckElement = multiRule->rule.lhs;
		char columnIndex = getLexemId(multiRule->rule.lhs);

//		multiRule->firstMarksType;

		// firstMarkCode = 0 ==> ""
		for (char firstMarkCode = 255; firstMarkCode++;){
			const char * firstMarkStr = getLexemStrById(firstMarkCode);
			unsigned long long int lexemTypeByFirstMarkCode = getLexemTypeById(firstMarkCode);

//			if (lexemTypeByFirstMarkCode == IDENTIFIER_LEXEME_TYPE && !strcmp(multiRule->firstMarks[firstMarksIndex], "ident_terminal")
//				|| lexemTypeByFirstMarkCode == VALUE_LEXEME_TYPE && !strcmp(multiRule->firstMarks[firstMarksIndex], "unsigned_value_terminal")
//				|| firstMarkCode == getLexemId(multiRule->firstMarks[firstMarksIndex])) {
//				if (multiRule->firstMarksType == LA_NOT) {
//					continue;
//				}
//			}
//			else {
//				if (multiRule->firstMarksType == LA_IS) {
//					continue;
//				}
//			}
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
			for (int firstMarksIndex = 0; multiRule->firstMarks[firstMarksIndex][0] != '\0'; ++firstMarksIndex) {
				if (lexemTypeByFirstMarkCode == IDENTIFIER_LEXEME_TYPE && !strcmp(multiRule->firstMarks[firstMarksIndex], "ident_terminal")
					|| lexemTypeByFirstMarkCode == VALUE_LEXEME_TYPE && !strcmp(multiRule->firstMarks[firstMarksIndex], "unsigned_value_terminal")
					|| firstMarkCode == getLexemId(multiRule->firstMarks[firstMarksIndex])) {
					if (multiRule->firstMarksType == LA_NOT) {
						continue;
					}
				}
				else {
					if (multiRule->firstMarksType == LA_IS) {
						continue;
					}
				}

#define ROW_INDEX firstMarksIndex

				if (dpda1Program[ROW_INDEX][columnIndex].tapeAction != -1) {
					printf("No support model\r\n.");
					exit(0);
				}

				dpda1Program[ROW_INDEX][columnIndex].tapeAction = NO_SCROLL;
				dpda1Program[ROW_INDEX][columnIndex].stackUpdate.stackAction = PUSH;
				for (int rhsVariantIndex = 0; multiRule->rule.rhss[rhsVariantIndex].secondMarksType; ++rhsVariantIndex) {
					//if (multiRule->rule.rhss[rhsVariantIndex].secondMarks[0][0] == '\0') {
					//    return multiRule->rule.rhss + rhsVariantIndex;
					//}
//#ifdef BUILD_AST_BY_DPDA1
//					dpda1Program[ROW_INDEX][columnIndex].stackUpdate.stackAction = STACK_POP_AND_MULTIPLIPUSH; // NEW 08.2025
//#else
					dpda1Program[ROW_INDEX][columnIndex].stackUpdate.stackAction = STACK_POP_AND_MULTIPLIPUSH; // NEW 08.2025
//#endif

#ifdef BUILD_P2C_AST_TYPE_BY_DPDA1
					bool popStackInFoutStateCodeMarker = true;
#endif
					for (int rhsElementIndex = 0; rhsElementIndex < MAX_RTOKEN_COUNT; ++rhsElementIndex)
						if (rhsElementIndex < multiRule->rule.rhss[rhsVariantIndex].rhs_count) dpda1Program[ROW_INDEX][columnIndex].stackUpdate.stackAddon[rhsVariantIndex][rhsElementIndex]
							//= getLexemTId(multiRule->rule.rhss[rhsVariantIndex].rhs[rhsElementIndex]);
					        = getLexemId(multiRule->rule.rhss[rhsVariantIndex].rhs[rhsElementIndex]);
#ifdef BUILD_P2C_AST_TYPE_BY_DPDA1
						else if (popStackInFoutStateCodeMarker) {
							dpda1Program[ROW_INDEX][columnIndex].stackUpdate.stackAddon[rhsVariantIndex][rhsElementIndex] = popStackInFoutStateCode;
							popStackInFoutStateCodeMarker = false;
						}
#endif
						else dpda1Program[ROW_INDEX][columnIndex].stackUpdate.stackAddon[rhsVariantIndex][rhsElementIndex] = emptyElementCode;

#ifdef BUILD_P2C_AST_TYPE_BY_DPDA1
					if (popStackInFoutStateCodeMarker) {
						//
						printf("Error: overflow of rhss size\r\n");
						exit(0);
				    }
#endif

//#if !defined(BUILD_AST_BY_DPDA1) || defined(BUILD_P2C_AST_TYPE_BY_DPDA1)
#ifdef BUILD_P2C_AST_TYPE_BY_DPDA1
					//char popStackInFoutStateCode = getLexemId((char*)"POP_STACK_IN_F_OUT_STATE");
#endif


//#ifdef BUILD_AST_BY_DPDA1
//					lastRHSElementIndex
//					//dpda1Program[ROW_INDEX][columnIndex].stackUpdate.stackAction = STACK_POP_AND_MULTIPLIPUSH; // NEW 08.2025
//#else


					// 

					for (char secondMarkCode = 255; secondMarkCode++;) {
					    // TODO: set 255 to start
						dpda1IndexingForSecondElement[secondMarkCode][columnIndex] = 255;
					}

					// char value = rhsVariantIndex; // no used
				
					for (char secondMarkCode = 255; secondMarkCode++;) {
						//char columnIndex = getLexemTId(multiRule->firstMarks);
						const char* secondMarkStr = getLexemStrById(secondMarkCode);
						unsigned long long int lexemTypeBySecondMarkCode = getLexemTypeById(secondMarkCode);
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						for (int secondMarksIndexForCurrentRHS = 0; multiRule->rule.rhss[rhsVariantIndex].secondMarks[secondMarksIndexForCurrentRHS][0] != '\0'; ++secondMarksIndexForCurrentRHS) {
							char secondMarkCodeForCurrentRHS = getLexemId(multiRule->rule.rhss[rhsVariantIndex].secondMarks[secondMarksIndexForCurrentRHS]);
							if (lexemTypeBySecondMarkCode == IDENTIFIER_LEXEME_TYPE && !strcmp(multiRule->rule.rhss[rhsVariantIndex].secondMarks[secondMarksIndexForCurrentRHS], "ident_terminal")
								|| lexemTypeBySecondMarkCode == VALUE_LEXEME_TYPE && !strcmp(multiRule->rule.rhss[rhsVariantIndex].secondMarks[secondMarksIndexForCurrentRHS], "unsigned_value_terminal")
								|| secondMarkCode == secondMarkCodeForCurrentRHS) {
								if (multiRule->rule.rhss[rhsVariantIndex].secondMarksType == LA_NOT) {
									continue;
								}
							}
							else {
								if (multiRule->rule.rhss[rhsVariantIndex].secondMarksType == LA_IS) {
									continue;
								}
							}

#define	ROW_INDEX_FOR_SECOND_TABLE secondMarkCode

							//char* currSecondMark = multiRule->rule.rhss[rhsVariantIndex].secondMarks[secondMarksIndex];
//							char rowIndexForSecondTable = getLexemTId(multiRule->rule.rhss[rhsVariantIndex].secondMarks[secondMarksIndexForCurrentRHS]);

							if (dpda1IndexingForSecondElement[ROW_INDEX_FOR_SECOND_TABLE][columnIndex] != -1
								&& dpda1IndexingForSecondElement[ROW_INDEX_FOR_SECOND_TABLE][columnIndex] != rhsVariantIndex) {
								printf("No support model or model consider error.\r\n");
								exit(0);
							}	

							dpda1IndexingForSecondElement[ROW_INDEX_FOR_SECOND_TABLE][columnIndex] = rhsVariantIndex;
#undef ROW_INDEX_FOR_SECOND_TABLE
						}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					}

					int rhsVariantAddonIndex = rhsVariantIndex + 1;
					if (!multiRule->rule.rhss[rhsVariantAddonIndex].secondMarksType) {
						bool needStateToDeadState = false;

						// scan
						for (char secondMarkCode = 255; secondMarkCode++;) {
							const char* secondMarkStr = getLexemStrById(secondMarkCode);
							if (dpda1IndexingForSecondElement[secondMarkCode][columnIndex] == 255) { // !!.
								needStateToDeadState = true;
								dpda1IndexingForSecondElement[secondMarkCode][columnIndex] = rhsVariantAddonIndex;
							}
						}

						// add "to dead" state
						if (needStateToDeadState) {
							dpda1Program[ROW_INDEX][columnIndex].stackUpdate.stackAddon[rhsVariantAddonIndex][0/*rhsVariantIndex*/] = deadStateCode;
							for (int rhsElementIndex = 1; rhsElementIndex < MAX_RTOKEN_COUNT; ++rhsElementIndex)
								dpda1Program[ROW_INDEX][columnIndex].stackUpdate.stackAddon[rhsVariantAddonIndex][rhsElementIndex] = emptyElementCode;
						}
					}
				}
#undef ROW_INDEX
//#undef ROW_INDEX_FOR_SECOND_TABLE
			}
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
		}
    }
}


#include <string>
#include <map>
//#include <utility>
#include <stack>

//std::map<std::string, std::pair<unsigned long long int, std::stack<unsigned long long int>>> labelInfoTable__;

#define IDENTIFIER_LEXEM_MIN_ID 0
#define IDENTIFIER_LEXEM_MAX_ID (IDENTIFIER_LEXEM_MIN_ID + 31)

// SPLIT TERMINAL AND NONTERMINAL
#define TERMINAL_AND_NONTERMINAL_LEXEM_MIN_ID (IDENTIFIER_LEXEM_MAX_ID + 1)
#define TERMINAL_AND_NONTERMINAL_LEXEM_MAX_ID (IDENTIFIER_LEXEM_MIN_ID + 190)

#define LITERAL_LEXEM_MAX_ID (TERMINAL_AND_NONTERMINAL_LEXEM_MAX_ID + 1)
#define LITERAL_LEXEM_MAX_ID 254 // (LITERAL_LEXEM_MAX_ID + 31)

#define EMPTY_LEXEM_ID 255

std::map<std::string, int> terminalAndNonTerminalLexemIds;

int terminalAndNonTerminalIdsInitPart1() {
	int lastNonUsedid = TERMINAL_AND_NONTERMINAL_LEXEM_MIN_ID;

	for (MarkedRule* multiRule = grammar.multiRules; multiRule->firstMarksType; ++multiRule) {
		if (terminalAndNonTerminalLexemIds.find(multiRule->rule.lhs) == terminalAndNonTerminalLexemIds.end()) {
			terminalAndNonTerminalLexemIds[multiRule->rule.lhs] = lastNonUsedid++;
		}

		for (int firstMarksIndex = 0; multiRule->firstMarks[firstMarksIndex][0] != '\0'; ++firstMarksIndex) {
			if (terminalAndNonTerminalLexemIds.find(multiRule->firstMarks[firstMarksIndex]) == terminalAndNonTerminalLexemIds.end()) {
				terminalAndNonTerminalLexemIds[multiRule->firstMarks[firstMarksIndex]] = lastNonUsedid++;
			}

			for (int rhsVariantIndex = 0; multiRule->rule.rhss[rhsVariantIndex].secondMarksType; ++rhsVariantIndex) {
				for (int secondMarksIndex = 0; multiRule->rule.rhss[rhsVariantIndex].secondMarks[secondMarksIndex][0] != '\0'; ++secondMarksIndex) {
					if (terminalAndNonTerminalLexemIds.find(multiRule->rule.rhss[rhsVariantIndex].secondMarks[secondMarksIndex]) == terminalAndNonTerminalLexemIds.end()) {
						terminalAndNonTerminalLexemIds[multiRule->rule.rhss[rhsVariantIndex].secondMarks[secondMarksIndex]] = lastNonUsedid++;
					}
				}

				for (int rhsElementIndex = 0; multiRule->rule.rhss[rhsVariantIndex].rhs[rhsElementIndex][0] != '\0'; ++rhsElementIndex) {
					if (terminalAndNonTerminalLexemIds.find(multiRule->rule.rhss[rhsVariantIndex].rhs[rhsElementIndex]) == terminalAndNonTerminalLexemIds.end()) {
						terminalAndNonTerminalLexemIds[multiRule->rule.rhss[rhsVariantIndex].rhs[rhsElementIndex]] = lastNonUsedid++;
					}
				}

			}
		}
	}

	if (lastNonUsedid > TERMINAL_AND_NONTERMINAL_LEXEM_MAX_ID) {
		printf("Error: maximum number of lexems exceeded\n");
		exit(0);
	}

	return lastNonUsedid;
}

void terminalAndNonTerminalIdsInitPart2(struct LexemInfo* lexemInfoTable, int lastNonUsedid) {
	if (lexemInfoTable == NULL) {
		printf("Error\n");
		exit(0);
	}


	for (; lexemInfoTable->lexemStr[0] != '\0'; ++lexemInfoTable) {
		if (terminalAndNonTerminalLexemIds.find(lexemInfoTable->lexemStr) == terminalAndNonTerminalLexemIds.end()) {
			terminalAndNonTerminalLexemIds[lexemInfoTable->lexemStr] = lastNonUsedid++;
		}
	}
}


void terminalAndNonTerminalIdsInit(struct LexemInfo* lexemInfoTable/*, int lastNonUsedid !!!!!!!!!!! */) {
	if (lexemInfoTable == NULL) {
		printf("Error\n");
		exit(0);
	}

	int lastNonUsedid = terminalAndNonTerminalIdsInitPart1();
	terminalAndNonTerminalLexemIds[""] = EMPTY_LEXEM_ID; // lastNonUsedid++;
	terminalAndNonTerminalIdsInitPart2(lexemInfoTable, lastNonUsedid);
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//char getLexemTId(char* lexemStr) { // getLexemId
//	return 0;
//}

#define REMOVE___OR_NOT struct LexemInfo* lexemInfoTable

void buildDPDA1forLL2(REMOVE___OR_NOT, Grammar& grammar, DPDA1Program& dpda1Program, DPDA1IndexingForSecondElement& dpda1IndexingForSecondElement) {

	// init codes
	terminalAndNonTerminalIdsInit(lexemInfoTable/*, int lastNonUsedid !!!!!!!!!!! */);


	// dead state
	buildDeadState__DPDA1forLL2(grammar, dpda1Program, dpda1IndexingForSecondElement);

	// set -1 // to dead state
	initBuild_All“˘ÚDeadStatesToDeadState__DPDA1forLL2(grammar, dpda1Program, dpda1IndexingForSecondElement);


	// 123
	buildRulePartForDPDA1forLL2(grammar, dpda1Program, dpda1IndexingForSecondElement);

	//
	// 123
	//
	buildAcceptTapeElement__DPDA1forLL2(grammar, dpda1Program, dpda1IndexingForSecondElement);

	// dpda1IndexingForSecondElement[rowIndex][columnIndex]; // -1

	// MIN_TERMIN
	// All Symbol

}


int main() {

	// TODO: ...

	return 0;
}