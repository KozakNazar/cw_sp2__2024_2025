#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2024_2025            *
*                         file: syntax.cpp                  *
*                                                  (draft!) *
*************************************************************/

#include "../../include/def.h"
#include "../../include/config.h"
#include "../../include/syntax/syntax.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
//#include <unordered_map>
#include <string>
#include <set>

#include "stdlib.h" // for exit() // TODO:...
#include "string.h"

using namespace std;

Grammar grammar = {
    GRAMMAR_LL2__2025
};

//#define DEBUG_STATES
//
//#define MAX_LEXEMS 256
////#define MAX_RULES 128
//#define MAX_SYMBOLS 64


struct ASTNode {
    std::string value;
    bool isTerminal;
    std::vector<ASTNode*> childrens;
    ASTNode* parent;

    ASTNode(const std::string& val, bool isTerminal) : isTerminal(isTerminal), value(val), parent(NULL) {}
    static void redirectLinks(std::vector<ASTNode*>& terminalChildrens) {
        for (ASTNode* node : terminalChildrens) {
            if (node == NULL /*!node->isTerminal*/) continue;
            //node->parent->childrens.push_back(node);
            //ASTNode_* parentNode = node->parent;
            //node->parent = NULL;
            //node = parentNode;
            while (node->parent != NULL) {
                node->parent->childrens.push_back(node);
                ASTNode* parentNode = node->parent;
                node->parent = NULL;
                node = parentNode;
            }
        }
    }
    ~ASTNode() { // use redirectLinks
        for (ASTNode* child : childrens) {
            delete child;
        }
    }
};
std::vector<ASTNode*> terminalChildrens;

ASTNode* addASTNodeToParent/*printStepAST*/(ASTNode* parent, char* lexemStr, char isTerminal) {

    if (lexemStr == NULL) {
        printf("Error: no lexem\n");
        exit(0); // TODO:...
    }

    ASTNode* node = new(std::nothrow) ASTNode(lexemStr, false); // std::string(lexemStr)
    if (node == nullptr) { // if (!node)
        printf("Error: no parent\n");
        exit(0); // TODO:...
    }

    node->parent = parent;

    return node;
}

void printAST(struct LexemInfo* lexemInfoTable, const ASTNode* node, int depth = 0) {
    static int lexemInfoTableIndexForPrintAST = 0; // ATTENTION: multithreading is not supported for this!
    if (!node) {
        return;
    }
    if (!depth) {
        lexemInfoTableIndexForPrintAST = 0;
    }

    for (unsigned int depthIndex = 0; depthIndex <= depth; ++depthIndex) {
        std::cout << "    " << "|";
    }

    std::cout << "--";
    if (node->isTerminal) {
        std::cout << "\"" << lexemInfoTable[lexemInfoTableIndexForPrintAST++].lexemStr << "\"";
    }
    else {
        std::cout << node->value;
    }
    std::cout << "\n";

    for (const ASTNode* child : node->childrens) {
        printAST(lexemInfoTable, child, depth + 1);
    }
}

void printASTToFile(struct LexemInfo* lexemInfoTable, const ASTNode* node, std::ofstream& outFile, int depth = 0) {
    static int lexemInfoTableIndexForPrintAST = 0; // ATTENTION: multithreading is not supported for this!
    if (!node) {
        return;
    }
    if (!depth) {
        lexemInfoTableIndexForPrintAST = 0;
    }

    for (unsigned int depthIndex = 0; depthIndex <= depth; ++depthIndex) {
        outFile << "    |";
    }
    outFile << "--";

    if (node->isTerminal) {
        outFile << "\"" << lexemInfoTable[lexemInfoTableIndexForPrintAST++].lexemStr << "\"";
    }
    else {
        outFile << node->value;
    }
    outFile << "\n";

    for (const ASTNode* child : node->childrens) {
        printASTToFile(lexemInfoTable, child, outFile, depth + 1);
    }
}

#define MAX_STRSTACK_SIZE 2048

char strStack[MAX_STRSTACK_SIZE][MAX_TOKEN_SIZE] = { '\0' };
ASTNode* nodeStack[MAX_STRSTACK_SIZE] = { NULL };

int strStackFirstFreeElementIndex = 0; // TODO: use reinit

void resetStack() {
    strStack[0][0] = '\0';
    strStackFirstFreeElementIndex = 0;
}

char isEmptyStack() { // FINIT STATE 0
    if (strStackFirstFreeElementIndex < 1) {
        return 0;
    }

    return 1;
}

void stackPush(char* stackNewElement, ASTNode* node) {
    if (stackNewElement == NULL) {
        printf("Error\n");
        exit(0); // TODO:...
    }

    if (strStackFirstFreeElementIndex < MAX_STRSTACK_SIZE) {
        nodeStack[strStackFirstFreeElementIndex] = node;
        strncpy(strStack[strStackFirstFreeElementIndex++], stackNewElement, MAX_TOKEN_SIZE);
        return;
    }

    printf("Stack error\n");
    exit(0); // TODO:...
}

ASTNode* stackPop() {
    if (strStackFirstFreeElementIndex) {
        return nodeStack[--strStackFirstFreeElementIndex];
    }

    printf("Stack error\n");
    exit(0); // TODO:...

    return NULL;
}

RHSConteiner* getActualRHSConteinerRHS(Grammar* grammar, struct LexemInfo* currTapeLexemInfoElement, struct LexemInfo* nextTapeLexemInfoElement, char* currStackElement) {
    if (grammar == NULL || currTapeLexemInfoElement == NULL || nextTapeLexemInfoElement == NULL || currStackElement == NULL) {
        printf("Error\n");
        exit(0); // TODO:...
    }

    for (MarkedRule* multiRule = grammar->multiRules; multiRule->firstMarksType; ++multiRule) {
        if (strcmp(multiRule->rule.lhs, currStackElement)) {
            continue;
        }

        for (int firstMarksIndex = 0; multiRule->firstMarks[firstMarksIndex][0] != '\0'; ++firstMarksIndex) {
            if (currTapeLexemInfoElement->tokenType == IDENTIFIER_LEXEME_TYPE && !strcmp(multiRule->firstMarks[firstMarksIndex], "ident_terminal")
                || currTapeLexemInfoElement->tokenType == VALUE_LEXEME_TYPE && !strcmp(multiRule->firstMarks[firstMarksIndex], "unsigned_value_terminal")
                || !strcmp(currTapeLexemInfoElement->lexemStr, multiRule->firstMarks[firstMarksIndex])) {
                if (multiRule->firstMarksType == LA_NOT) {
                    continue;
                }
            }
            else {
                if (multiRule->firstMarksType == LA_IS) {
                    continue;
                }
            }

            for (int rhsVariantIndex = 0; multiRule->rule.rhss[rhsVariantIndex].secondMarksType; ++rhsVariantIndex) {
                if (multiRule->rule.rhss[rhsVariantIndex].secondMarks[0][0] == '\0') {
                    return multiRule->rule.rhss + rhsVariantIndex;
                }
                for (int secondMarksIndex = 0; multiRule->rule.rhss[rhsVariantIndex].secondMarks[secondMarksIndex][0] != '\0'; ++secondMarksIndex) {
                    if (nextTapeLexemInfoElement->tokenType == IDENTIFIER_LEXEME_TYPE && !strcmp(multiRule->rule.rhss[rhsVariantIndex].secondMarks[secondMarksIndex], "ident_terminal")
                        || nextTapeLexemInfoElement->tokenType == VALUE_LEXEME_TYPE && !strcmp(multiRule->rule.rhss[rhsVariantIndex].secondMarks[secondMarksIndex], "unsigned_value_terminal")
                        || !strcmp(nextTapeLexemInfoElement->lexemStr, multiRule->rule.rhss[rhsVariantIndex].secondMarks[secondMarksIndex])) {
                        if (multiRule->rule.rhss[rhsVariantIndex].secondMarksType == LA_NOT) {
                            continue;
                        }
                    }
                    else {
                        if (multiRule->rule.rhss[rhsVariantIndex].secondMarksType == LA_IS) {
                            continue;
                        }
                    }

                    return multiRule->rule.rhss + rhsVariantIndex;
                }
            }
        }
    }

    return NULL;
}

void scrollTapeOneStep(struct LexemInfo** currLexemInfoElement, struct LexemInfo** nextLexemInfoElement) {
    ++* currLexemInfoElement;
    *nextLexemInfoElement = *currLexemInfoElement + 1;
}

struct LexemInfo* syntaxLL2(Grammar* grammar, char * ruleName, struct LexemInfo* lexemInfoTable, ASTNode** baseASTNode, struct LexemInfo** badLexemInfo) {
    struct LexemInfo* currTapeElement, * nextTapeElement;

    if (grammar == NULL || ruleName == NULL || lexemInfoTable == NULL || baseASTNode == NULL) {
        printf("Error\n");
        exit(0); // TODO:...
    }

    terminalChildrens.resize(0);

    // start state
    currTapeElement = lexemInfoTable;
    nextTapeElement = lexemInfoTable + 1;
#define CURRENT_STACK_TOP_ELEMENT strStack[strStackFirstFreeElementIndex - 1] // ( strStack[strStackFirstFreeElementIndex - 1] )
    resetStack();
    stackPush(ruleName, *baseASTNode = addASTNodeToParent(NULL, ruleName, false));

    while (isEmptyStack()) {
        //II
        if (currTapeElement->tokenType == IDENTIFIER_LEXEME_TYPE && !strcmp(CURRENT_STACK_TOP_ELEMENT, "ident_terminal")
            || currTapeElement->tokenType == VALUE_LEXEME_TYPE && !strcmp(CURRENT_STACK_TOP_ELEMENT, "unsigned_value_terminal")
            || !strcmp(currTapeElement->lexemStr, CURRENT_STACK_TOP_ELEMENT)) {
            // printf("Processed: \"%s\"\n", currTapeElement->lexemStr); // out // debug
            scrollTapeOneStep(&currTapeElement, &nextTapeElement);
            ASTNode* node = stackPop();
            if (node) {
                node->isTerminal = true;
            }
            terminalChildrens.push_back(node);
        }

        //I
        else {
            RHSConteiner* rhsConteiner = getActualRHSConteinerRHS(grammar, currTapeElement, nextTapeElement, CURRENT_STACK_TOP_ELEMENT);
            if (rhsConteiner == NULL) {
                //printf("Error: no rule\n");
                //exit(0);
                if (badLexemInfo != NULL) {
                    *badLexemInfo = currTapeElement;
                }
                return currTapeElement;
            }

            ASTNode* parent = stackPop();
            for (int rhsElementIndex = rhsConteiner->rhs_count - 1; rhsElementIndex >= 0; --rhsElementIndex) {
                stackPush(rhsConteiner->rhs[rhsElementIndex], addASTNodeToParent(parent, rhsConteiner->rhs[rhsElementIndex], false));
            }
        }
    }

    isEmptyStack(); // TODO: ... finite state

    ASTNode::redirectLinks(terminalChildrens);
    //printAST(lexemInfoTable, *baseASTNode);

    return currTapeElement;
}

//#define MAX_STACK_DEPTH 256
//#define MAX_AST_NODE_COUNT 65536

bool getIndexAfterFragmentSyntax(char* ruleName, int& lexemIndex, struct LexemInfo* lexemInfoTable, Grammar* grammar, int depth/* not used */) {
    struct LexemInfo* unexpectedLexemfailedTerminal = NULL;
    if (ruleName == NULL) {
        printf("Error: no start rule.\r\n");
        exit(0); // TODO:...
    }

    if (lexemInfoTable == NULL || grammar == NULL) {
        printf("Error\r\n");
        exit(0); // TODO:...
    }
    struct ASTNode* baseASTNode;
    struct LexemInfo* lastLexemInfo = syntaxLL2(grammar, ruleName, lexemInfoTable, &baseASTNode, &unexpectedLexemfailedTerminal);
    delete baseASTNode;
    lexemIndex = lastLexemInfo - lexemInfoTable;

    return unexpectedLexemfailedTerminal == NULL;
}

int syntaxAnalyze(struct LexemInfo* lexemInfoTable, Grammar* grammar, char syntaxlAnalyzeMode/* not used */, char* astFileName, char* errorMessagesPtrToLastBytePtr, bool viewAST) {
    struct ASTNode* astRoot = NULL;    
    struct LexemInfo* unexpectedLexemfailedTerminal = NULL; // TODO: ...

    struct LexemInfo* lastLexemInfo = syntaxLL2(grammar, grammar->start_symbol, lexemInfoTable, &astRoot, &unexpectedLexemfailedTerminal);

    if (lastLexemInfo->lexemStr[0] == '\0') {
        if (viewAST) {
            printAST(lexemInfoTable, astRoot);
        }
        std::ofstream astOFStream(astFileName, std::ofstream::out);
        printASTToFile(lexemInfoTable, astRoot, astOFStream);
        astOFStream.close();
        return SUCCESS_STATE;
    }
    else {
        unexpectedLexemfailedTerminal = lastLexemInfo; // TODO: ...
        printf("Parse failed.\r\n");
        printf("    (The predicted terminal does not match the expected one.\r\n    Unexpected terminal \"%s\" on line %lld at position %lld.)\r\n", unexpectedLexemfailedTerminal->lexemStr, unexpectedLexemfailedTerminal->row, unexpectedLexemfailedTerminal->col);
        errorMessagesPtrToLastBytePtr += sprintf(errorMessagesPtrToLastBytePtr, "Parse failed.\r\n");
        errorMessagesPtrToLastBytePtr += snprintf(errorMessagesPtrToLastBytePtr, MAX_LEXEM_SIZE + 128 + strlen("    (The predicted terminal does not match the expected one.\r\n    Unexpected terminal \"#\" on line # at position #.)\r\n"), "    (The predicted terminal does not match the expected one.\r\n    Unexpected terminal \"%s\" on line %lld at position %lld.)\r\n", unexpectedLexemfailedTerminal->lexemStr, unexpectedLexemfailedTerminal->row, unexpectedLexemfailedTerminal->col);
        //exit(0);
        return ~SUCCESS_STATE;
    }
}