#define _CRT_SECURE_NO_WARNINGS
/******************************************************************
* N.Kozak // Lviv'2024-2025 // lexica__2025                       *
*                         file: dpda1_for_ll2_generator__2025.cpp *
*                                                  (draft!)       *
*******************************************************************/
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include <fstream>
#include <iostream>
//#include <algorithm>
#include <iterator>
#include <regex>

//#define DPDA1_TABLE_NAME tableName
//#define CONCAT_NAME_(N1, N2) N1##N2
//#define CONCAT_NAME(N1, N2) CONCAT_NAME_(N1, N2) // EXPAND

#define CONCAT_NAME_(N1, N2) N1##N2
#define CONCAT_NAME(N1, N2) CONCAT_NAME_(N1, N2) // EXPAND
#define BY_DPDA1_TABLE_NAME(N2) CONCAT_NAME(DPDA1_TABLE_NAME, N2)

#define CONST_STRING_(N) #N
#define CONST_STRING(N) CONST_STRING_(N) // EXPAND

#define DPDA1_TABLE_NAME language
#define DPDA1_FILE_NAME BY_DPDA1_TABLE_NAME(.hpp)

#undef INCLUDE_TO_SOLUTION

#ifdef INCLUDE_TO_SOLUTION

#include "../cw_sp2__2025_2026/src/include/def.h"
#include "../cw_sp2__2025_2026/src/include/config.h"
#include "../cw_sp2__2025_2026/src/include/syntax/syntax.h"

#else


#define ARRAY_INTERVAL 128


#define USE_REVERSE_ASSIGNMENT
#define USE_COMPARE_WITH_EQUAL

/*
#ifdef USE_REVERSE_ASSIGNMENT
#define IF_USE_REVERSE_ASSIGNMENT(...) __VA_ARGS__
#define IF_NONUSE_REVERSE_ASSIGNMENT(...)
#else
#define IF_USE_REVERSE_ASSIGNMENT(...)
#define IF_NONUSE_REVERSE_ASSIGNMENT(...) __VA_ARGS__
#endif

#ifdef USE_COMPARE_WITH_EQUAL
#define IF_USE_COMPARE_WITH_EQUAL(...) __VA_ARGS__
#define IF_NONUSE_COMPARE_WITH_EQUAL(...)
#else
#define IF_USE_COMPARE_WITH_EQUAL(...)
#define IF_NONUSE_COMPARE_WITH_EQUAL(...) __VA_ARGS__
#endif
*/
#define LA_IS  2
#define LA_NOT 4


#include "LexicaByRegExAndSyntaxByLL2protototype.h";

//#define DECLENUM(NAME, ...) typedef enum {__VA_ARGS__, size##NAME} NAME;
//#define DECLENUM(NAME, ...) enum NAME {__VA_ARGS__, size##NAME};
//#define GET_ENUM_SIZE(NAME) size##NAME
//#define SET_QUADRUPLE_STR_MACRO_IN_ARRAY(ARRAY, NAME)\
//ARRAY[MULTI_TOKEN_##NAME][0] = (char*)T_##NAME##_0;\
//ARRAY[MULTI_TOKEN_##NAME][1] = (char*)T_##NAME##_1;\
//ARRAY[MULTI_TOKEN_##NAME][2] = (char*)T_##NAME##_2;\
//ARRAY[MULTI_TOKEN_##NAME][3] = (char*)T_##NAME##_3;

#define MAX_RULES 356

#define MAX_TOKEN_SIZE 128
#define MAX_RTOKEN_COUNT 16

#define MAX_RHSCONTEINER_COUNT 3

#define MAX_MARK_COUNT 16

typedef struct {
	char secondMarksType;
	char secondMarks[MAX_MARK_COUNT][MAX_TOKEN_SIZE];
	int rhs_count;
	char rhs[MAX_RTOKEN_COUNT][MAX_TOKEN_SIZE];
} RHSConteiner;

typedef struct {
	char lhs[MAX_TOKEN_SIZE];
	RHSConteiner rhss[MAX_RHSCONTEINER_COUNT];
} Rule;

typedef struct {
	char firstMarksType;
	char firstMarks[MAX_MARK_COUNT][MAX_TOKEN_SIZE];
	Rule rule;
} MarkedRule;

typedef struct {
	MarkedRule multiRules[MAX_RULES];
	char start_symbol[MAX_TOKEN_SIZE];
} Grammar;

Grammar grammar = {
	GRAMMAR_LL2__2025
};

bool getIndexAfterFragmentSyntax(char* ruleName, int& lexemIndex, struct LexemInfo* lexemInfoTable, Grammar* grammar, int depth/* not used */);



//#define DEFAULT_INPUT_FILE "../base_test_programs_2025/file1.k03"
// #define AST_OUTPUT_FILE "../base_test_programs_2025/ast.txt"
//#define DEFAULT_INPUT_FILE "../other_test_programs_2025/file4.k03"
//#define AST_OUTPUT_FILE "../base_test_programs_2025/ast.txt"
#define DEFAULT_INPUT_FILE "../base_test_programs_2025/file1.k03"
#define AST_OUTPUT_FILE "ast.txt"

unsigned char errorMessagesPtrToLastBytePtr[8 * 1024 * 1024] = { '\0' };

#define SUCCESS_STATE 0

#define DEBUG_MODE 4096

#define RERUN_MODE

#define VALUE_SIZE 4

#define MAX_TEXT_SIZE 8192
#define MAX_WORD_COUNT (MAX_TEXT_SIZE / 5)
#define MAX_LEXEM_SIZE 1024
#define EMPTY_TOKEN_LEXEM_ID 0
#define UNKNOWN_ELEMENT_ID 1 // (EMPTY_TOKEN_LEXEM_ID + 1)
#define MAX_KEYWORD_COUNT 64
#define MAX_VARIABLES_COUNT 32
#define MAX_LITERAL_COUNT 32

//std::map<std::string, std::pair<unsigned long long int, std::stack<unsigned long long int>>> labelInfoTable__;

//#define MAX_KEYWORD_COUNT 64
//#define MAX_VARIABLES_COUNT 32
//#define MAX_LITERAL_COUNT 32

//#define EMPTY_TOKEN_LEXEM_ID 0; // lastNonUsedid++;

//#define UNKNOWN_ELEMENT_ID (EMPTY_TOKEN_LEXEM_ID + 1) // 1 // 127 // for TYPE!

#define KEYWORD_LEXEM_MIN_ID (UNKNOWN_ELEMENT_ID + 1)
#define KEYWORD_LEXEM_MAX_ID (KEYWORD_LEXEM_MIN_ID + MAX_KEYWORD_COUNT)

#define IDENTIFIER_METATERMINAL_LEXEM_STR "ident_terminal"
#define IDENTIFIER_METATERMINAL_LEXEM_ID (KEYWORD_LEXEM_MAX_ID + 1)
#define IDENTIFIER_LEXEM_MIN_ID (IDENTIFIER_METATERMINAL_LEXEM_ID + 1)
#define IDENTIFIER_LEXEM_MAX_ID (IDENTIFIER_LEXEM_MIN_ID + MAX_VARIABLES_COUNT)

#define UNSIGNED_VALUE_METATERMINAL_LEXEM_STR "unsigned_value_terminal"
#define UNSIGNED_VALUE_METATERMINAL_LEXEM_ID (IDENTIFIER_LEXEM_MAX_ID + 1)
#define LITERAL_LEXEM_MIN_ID (UNSIGNED_VALUE_METATERMINAL_LEXEM_ID + 1)
#define LITERAL_LEXEM_MAX_ID (LITERAL_LEXEM_MIN_ID + MAX_LITERAL_COUNT)

// SPLIT TERMINAL AND NONTERMINAL // V
//#define TERMINAL_AND_NONTERMINAL_LEXEM_MIN_ID (IDENTIFIER_LEXEM_MAX_ID + 1)
//#define TERMINAL_AND_NONTERMINAL_LEXEM_MAX_ID (IDENTIFIER_LEXEM_MIN_ID + 190)
#define NONTERMINAL_LEXEM_MIN_ID (LITERAL_LEXEM_MAX_ID + 1)
#define NONTERMINAL_LEXEM_MAX_ID 250
#define PROGRAM_RULE_STR "program_rule" // TODO: add to config.h (LexicaByRegExAndSyntaxByLL2protototype.h)
#define PROGRAM_RULE_ID NONTERMINAL_LEXEM_MAX_ID

#define DEAD_STATE_STR "_#DS" // "DEAD_STATE__for_tests__remove"
#define DEAD_STATE_ID 253
#define	MARKER_OF_STRUCTURE_ID 254 // <null>-marker on out-tape
#define FREE_STATE_ID 255


//terminalAndNonTerminalLexemIds["ident_terminal"] = IDENT_METATERMINL_TOKEN_LEXEM_ID;
//terminalAndNonTerminalLexemIds["unsigned_value_terminal"] = EMPTY_TOKEN_LEXEM_ID;

//#define BUILD_C2P_AST_TYPE_BY_DPDA1
//#ifndef BUILD_C2P_AST_TYPE_BY_DPDA1
//	#define	POP_STACK_IN_F_OUT_STATE
// 
//#define EMPTY_LEXEM_ID 255






#define UNEXPEXTED_LEXEME_TYPE  UNKNOWN_ELEMENT_ID // 127
#define KEYWORD_LEXEME_TYPE 2
#define IDENTIFIER_LEXEME_TYPE 4 // #define LABEL_LEXEME_TYPE 8
#define VALUE_LEXEME_TYPE 8
#define NONTERMINAL_LEXEME_TYPE 16 // NEW

#ifndef LEXEM_INFO_
#define LEXEM_INFO_
struct NonContainedLexemInfo;
struct LexemInfo {
public:
	char lexemStr[MAX_LEXEM_SIZE];
	unsigned long long int lexemId;
	unsigned long long int tokenType;
	unsigned long long int ifvalue;
	unsigned long long int row;
	unsigned long long int col;
	// TODO: ...

	LexemInfo();
	LexemInfo(const char* lexemStr, unsigned long long int lexemId, unsigned long long int tokenType, unsigned long long int ifvalue, unsigned long long int row, unsigned long long int col);
	LexemInfo(const NonContainedLexemInfo& nonContainedLexemInfo);
};
#endif

#ifndef NON_CONTAINED_LEXEM_INFO_
#define NON_CONTAINED_LEXEM_INFO_
struct LexemInfo;
struct NonContainedLexemInfo {
	//char lexemStr[MAX_LEXEM_SIZE]; 
	char* lexemStr;
	unsigned long long int lexemId;
	unsigned long long int tokenType;
	unsigned long long int ifvalue;
	unsigned long long int row;
	unsigned long long int col;
	// TODO: ...

	NonContainedLexemInfo();
	NonContainedLexemInfo(const LexemInfo& lexemInfo);
};
#endif

void printLexemes(struct LexemInfo* lexemInfoTable, char printBadLexeme/* = 0*/);
void printLexemesToFile(struct LexemInfo* lexemInfoTable, char printBadLexeme, const char* filename);
unsigned int getIdentifierId(char(*identifierIdsTable)[MAX_LEXEM_SIZE], char* str);
unsigned int tryToGetIdentifier(struct LexemInfo* lexemInfoInTable, char(*identifierIdsTable)[MAX_LEXEM_SIZE]);
unsigned int tryToGetUnsignedValue(struct LexemInfo* lexemInfoInTable);
int commentRemover(char* text, const char* openStrSpc/* = "//"*/, const char* closeStrSpc/* = "\n"*/);
void prepareKeyWordIdGetter(char* keywords_, char* keywords_re);
unsigned int getKeyWordId(char* keywords_, char* lexemStr, unsigned int baseId);
char tryToGetKeyWord(struct LexemInfo* lexemInfoInTable);
void setPositions(const char* text, struct LexemInfo* lexemInfoTable);
struct LexemInfo lexicalAnalyze(struct LexemInfo* lexemInfoInPtr, char(*identifierIdsTable)[MAX_LEXEM_SIZE]);
struct LexemInfo tokenize(char* text, struct LexemInfo** lastLexemInfoInTable, char(*identifierIdsTable)[MAX_LEXEM_SIZE], struct LexemInfo(*lexicalAnalyzeFunctionPtr)(struct LexemInfo*, char(*)[MAX_LEXEM_SIZE]));



#define MAX_ACCESSORY_STACK_SIZE_123 128

char tempStrFor_123[MAX_TEXT_SIZE/*?TODO:... MAX_ACCESSORY_STACK_SIZE_123 * 64*/] = { '\0' };
unsigned long long int tempStrForCurrIndex = 0;

struct LexemInfo lexemesInfoTable[MAX_WORD_COUNT];// = { { "", 0, 0, 0 } };
struct LexemInfo* lastLexemInfoInTable = lexemesInfoTable; // first for begin

char identifierIdsTable[MAX_WORD_COUNT][MAX_LEXEM_SIZE] = { "" };

LexemInfo::LexemInfo() {
	lexemStr[0] = '\0';
	lexemId = 0;
	tokenType = 0;
	ifvalue = 0;
	row = ~0;
	col = ~0;
}
LexemInfo::LexemInfo(const char* lexemStr, unsigned long long int lexemId, unsigned long long int tokenType, unsigned long long int ifvalue, unsigned long long int row, unsigned long long int col) {
	strncpy(this->lexemStr, lexemStr, MAX_LEXEM_SIZE);
	this->lexemId = lexemId;
	this->tokenType = tokenType;
	this->ifvalue = ifvalue;
	this->row = row;
	this->col = col;
}
LexemInfo::LexemInfo(const NonContainedLexemInfo& nonContainedLexemInfo) {
	strncpy(lexemStr, nonContainedLexemInfo.lexemStr, MAX_LEXEM_SIZE);
	lexemId = nonContainedLexemInfo.lexemId;
	tokenType = nonContainedLexemInfo.tokenType;
	ifvalue = nonContainedLexemInfo.ifvalue;
	row = nonContainedLexemInfo.row;
	col = nonContainedLexemInfo.col;
}

NonContainedLexemInfo::NonContainedLexemInfo() {
	(lexemStr = tempStrFor_123 + tempStrForCurrIndex)[0] = '\0';
	tempStrForCurrIndex += 32;// MAX_LEXEM_SIZE;
	lexemId = 0;
	tokenType = 0;
	ifvalue = 0;
	row = ~0;
	col = ~0;
}
NonContainedLexemInfo::NonContainedLexemInfo(const LexemInfo& lexemInfo) {
	//strncpy(lexemStr, lexemInfo.lexemStr, MAX_LEXEM_SIZE); // 
	lexemStr = (char*)lexemInfo.lexemStr;
	lexemId = lexemInfo.lexemId;
	tokenType = lexemInfo.tokenType;
	ifvalue = lexemInfo.ifvalue;
	row = lexemInfo.row;
	col = lexemInfo.col;
}

void printLexemes(struct LexemInfo* lexemInfoTable, char printBadLexeme) {
	if (printBadLexeme) {
		printf("Bad lexeme:\r\n");
	}
	else {
		printf("Lexemes table:\r\n");
	}
	printf("-------------------------------------------------------------------\r\n");
	//printf("index\t\tlexeme\t\tid\ttype\tifvalue\trow\tcol\r\n");
	printf("index           lexeme          id      type    ifvalue row     col\r\n");
	printf("-------------------------------------------------------------------\r\n");
	for (unsigned long long int index = 0; (!index || !printBadLexeme) && lexemInfoTable[index].lexemStr[0] != '\0'; ++index) {
		printf("%5llu%17s%12llu%10llu%11llu%4lld%8lld\r\n", index, lexemInfoTable[index].lexemStr, lexemInfoTable[index].lexemId, lexemInfoTable[index].tokenType, lexemInfoTable[index].ifvalue, lexemInfoTable[index].row, lexemInfoTable[index].col);
	}
	printf("-------------------------------------------------------------------\r\n\r\n");

	return;
}

void printLexemesToFile(struct LexemInfo* lexemInfoTable, char printBadLexeme, const char* filename) {
	FILE* file = fopen(filename, "wb");
	if (!file) {
		perror("Failed to open file");
		return;
	}

	if (printBadLexeme) {
		fprintf(file, "Bad lexeme:\r\n");
	}
	else {
		fprintf(file, "Lexemes table:\r\n");
	}
	fprintf(file, "-------------------------------------------------------------------\r\n");
	//fprintf(file, "index\t\tlexeme\t\tid\ttype\tifvalue\trow\tcol\r\n");
	fprintf(file, "index           lexeme          id      type    ifvalue row     col\r\n");
	fprintf(file, "-------------------------------------------------------------------\r\n");

	for (unsigned long long int index = 0; (!index || !printBadLexeme) && lexemInfoTable[index].lexemStr[0] != '\0'; ++index) {
		fprintf(file, "%5llu%17s%12llu%10llu%11llu%4lld%8lld\r\n",
			index,
			lexemInfoTable[index].lexemStr,
			lexemInfoTable[index].lexemId,
			lexemInfoTable[index].tokenType,
			lexemInfoTable[index].ifvalue,
			lexemInfoTable[index].row,
			lexemInfoTable[index].col);
	}
	fprintf(file, "-------------------------------------------------------------------\r\n\r\n");

	fclose(file);
}

// get identifier id
unsigned int getIdentifierId(char(*identifierIdsTable)[MAX_LEXEM_SIZE], char* str, unsigned int baseId) {
	unsigned int index = 0;
	for (; identifierIdsTable[index][0] != '\0'; ++index) {
		if (!strncmp(identifierIdsTable[index], str, MAX_LEXEM_SIZE)) {
			return index;
		}
	}
	strncpy(identifierIdsTable[index], str, MAX_LEXEM_SIZE);
	identifierIdsTable[index + 1][0] = '\0'; // not necessarily for zero-init identifierIdsTable
	return baseId + index;
}

// try to get identifier
unsigned int tryToGetIdentifier(struct LexemInfo* lexemInfoInTable, char(*identifierIdsTable)[MAX_LEXEM_SIZE]) {
	char* identifiers_re = (char*)IDENTIFIERS_RE;
	//char identifiers_re[] = "_[A-Z][A-Z][A-Z][A-Z][A-Z][A-Z][A-Z]";

	if (std::regex_match(std::string(lexemInfoInTable->lexemStr), std::regex(identifiers_re))) {
		lexemInfoInTable->lexemId = getIdentifierId(identifierIdsTable, lexemInfoInTable->lexemStr, IDENTIFIER_LEXEM_MIN_ID);
		lexemInfoInTable->tokenType = IDENTIFIER_LEXEME_TYPE;
		return SUCCESS_STATE;
	}

	return ~SUCCESS_STATE;
}

// try to get value
unsigned int tryToGetUnsignedValue(struct LexemInfo* lexemInfoInTable) {
	char* unsignedvalues_re = (char*)UNSIGNEDVALUES_RE;
	//char unsignedvalues_re[] = "0|[1-9][0-9]*";

	if (std::regex_match(std::string(lexemInfoInTable->lexemStr), std::regex(unsignedvalues_re))) {
		lexemInfoInTable->ifvalue = atoi(lastLexemInfoInTable->lexemStr);
		lexemInfoInTable->lexemId = LITERAL_LEXEM_MIN_ID /*+ ?*/;
		lexemInfoInTable->tokenType = VALUE_LEXEME_TYPE;
		return SUCCESS_STATE;
	}

	return ~SUCCESS_STATE;
}

int commentRemover(char* text, const char* openStrSpc, const char* closeStrSpc) {
	bool eofAlternativeCloseStrSpcType = false;
	bool explicitCloseStrSpc = true;
	if (!strcmp(closeStrSpc, "\n")) {
		eofAlternativeCloseStrSpcType = true;
		explicitCloseStrSpc = false;
	}

	unsigned int commentSpace = 0;

	unsigned int textLength = strlen(text);               // strnlen(text, MAX_TEXT_SIZE);
	unsigned int openStrSpcLength = strlen(openStrSpc);   // strnlen(openStrSpc, MAX_TEXT_SIZE);
	unsigned int closeStrSpcLength = strlen(closeStrSpc); // strnlen(closeStrSpc, MAX_TEXT_SIZE);
	if (!closeStrSpcLength) {
		return -1; // no set closeStrSpc
	}
	unsigned char oneLevelComment = 0;
	if (!strncmp(openStrSpc, closeStrSpc, MAX_LEXEM_SIZE)) {
		oneLevelComment = 1;
	}

	for (unsigned int index = 0; index < textLength; ++index) {
		if (!strncmp(text + index, closeStrSpc, closeStrSpcLength) && (explicitCloseStrSpc || commentSpace)) {
			if (commentSpace == 1 && explicitCloseStrSpc) {
				for (unsigned int index2 = 0; index2 < closeStrSpcLength; ++index2) {
					text[index + index2] = ' ';
				}
			}
			else if (commentSpace == 1 && !explicitCloseStrSpc) {
				index += closeStrSpcLength - 1;
			}
			oneLevelComment ? commentSpace = !commentSpace : commentSpace = 0;
		}
		else if (!strncmp(text + index, openStrSpc, openStrSpcLength)) {
			oneLevelComment ? commentSpace = !commentSpace : commentSpace = 1;
		}

		if (commentSpace && text[index] != ' ' && text[index] != '\t' && text[index] != '\r' && text[index] != '\n') {
			text[index] = ' ';
		}

	}

	if (commentSpace && !eofAlternativeCloseStrSpcType) {
		return -1;
	}

	return 0;
}

void prepareKeyWordIdGetter(char* keywords_, char* keywords_re) {
	if (keywords_ == NULL || keywords_re == NULL) {
		return;
	}
//#define KEYWORDS_RE       ";|:=|=:|\\+|-|\\*|,|==|!=|:|\\[|\\]|\\(|\\)|\\{|\\}|NAME|DATA|BODY|END|BREAK|CONTINUE|GET|PUT|IF|ELSE|FOR|TO|DOWNTO|DO|WHILE|REPEAT|UNTIL|GOTO|DIV|MOD|<=|>=|NOT|AND|OR|INTEGER16"
	for (char* keywords_re_ = keywords_re, *keywords__ = keywords_; (*keywords_re_ != '\0') ? 1 : (*keywords__ = '\0', 0); (*keywords_re_ != '\\' || (
		keywords_re_[1] != '+' && 
		keywords_re_[1] != '*' && 
		keywords_re_[1] != '|' &&
		keywords_re_[1] != '[' &&
		keywords_re_[1] != ']' &&
		keywords_re_[1] != '(' &&
		keywords_re_[1] != ')' &&
		keywords_re_[1] != '{' &&
		keywords_re_[1] != '}'
		)) ? *keywords__++ = *keywords_re_ : 0, ++keywords_re_);
	while (*keywords_=='|'? *keywords_ = 31 : 0, *keywords_++ != '\0');
}

unsigned int getKeyWordId(char* keywords_, char* lexemStr, unsigned int baseId) {
	if (keywords_ == NULL || lexemStr == NULL) {
		return ~0;
	}
	char* lexemInKeywords_ = keywords_;
	size_t lexemStrLen = strlen(lexemStr);
	if (!lexemStrLen) {
		return ~0;
	}
	lexemInKeywords_ = strstr(lexemInKeywords_, lexemStr);
	//for (; lexemInKeywords_ = strstr(lexemInKeywords_, lexemStr), lexemInKeywords_ != NULL && lexemInKeywords_[lexemStrLen] != '|' && lexemInKeywords_[lexemStrLen] != '\0'; ++lexemInKeywords_);

	//return lexemInKeywords_ - keywords_ + baseId;

	unsigned int id = 0;
	for (; keywords_ < lexemInKeywords_; ++keywords_)
		if (*keywords_ == 31) ++id;

	return id + baseId;
}

// try to get KeyWord
char tryToGetKeyWord(struct LexemInfo* lexemInfoInTable) {
	char* keywords_re = (char*)KEYWORDS_RE;
	//char keywords_re[] = ";|<<|>>|\\+|-|\\*|,|==|!=|:|\\(|\\)|NAME|DATA|BODY|END|EXIT|CONTINUE|GET|PUT|IF|ELSE|FOR|TO|DOWNTO|DO|WHILE|REPEAT|UNTIL|GOTO|DIV|MOD|<=|>=|NOT|AND|OR|INTEGER16";
	//char keywords_re[] = ";|<<|\\+\\+|--|\\*\\*|==|\\(|\\)|!=|:|name|data|body|end|get|put|for|to|downto|do|while|continue|exit|repeat|until|if|goto|div|mod|le|ge|not|and|or|long|int";
	char keywords_[sizeof(KEYWORDS_RE)] = { '\0' };
	prepareKeyWordIdGetter(keywords_, keywords_re);

	if (std::regex_match(std::string(lexemInfoInTable->lexemStr), std::regex(keywords_re))) {
		lexemInfoInTable->lexemId = getKeyWordId(keywords_, lexemInfoInTable->lexemStr, KEYWORD_LEXEM_MIN_ID);
		lexemInfoInTable->tokenType = KEYWORD_LEXEME_TYPE;
		return SUCCESS_STATE;
	}

	return ~SUCCESS_STATE;
}

void setPositions(const char* text, struct LexemInfo* lexemInfoTable) {
	unsigned long long int line_number = 1;
	const char* pos = text, * line_start = text;

	if (lexemInfoTable) while (*pos != '\0' && lexemInfoTable->lexemStr[0] != '\0') {
		const char* line_end = strchr(pos, '\n');
		if (!line_end) {
			line_end = text + strlen(text);
		}

		char line_[4096], * line = line_; //!! TODO: ...
		strncpy(line, pos, line_end - pos);
		line[line_end - pos] = '\0';

		for (char* found_pos; lexemInfoTable->lexemStr[0] != '\0' && (found_pos = strstr(line, lexemInfoTable->lexemStr)); line += strlen(lexemInfoTable->lexemStr), ++lexemInfoTable) {
			lexemInfoTable->row = line_number;
			lexemInfoTable->col = found_pos - line_ + 1ull;
		}
		line_number++;
		pos = line_end;
		if (*pos == '\n') {
			pos++;
		}
	}
}

struct LexemInfo lexicalAnalyze(struct LexemInfo* lexemInfoInPtr, char(*identifierIdsTable)[MAX_LEXEM_SIZE]) {
	struct LexemInfo ifBadLexemeInfo; // = { 0 };

	if (tryToGetKeyWord(lexemInfoInPtr) == SUCCESS_STATE);
	else if (tryToGetIdentifier(lexemInfoInPtr, identifierIdsTable) == SUCCESS_STATE);
	else if (tryToGetUnsignedValue(lexemInfoInPtr) == SUCCESS_STATE);
	else ifBadLexemeInfo.tokenType = UNEXPEXTED_LEXEME_TYPE;

	return ifBadLexemeInfo;
}

struct LexemInfo tokenize(char* text, struct LexemInfo** lastLexemInfoInTable, char(*identifierIdsTable)[MAX_LEXEM_SIZE], struct LexemInfo(*lexicalAnalyzeFunctionPtr)(struct LexemInfo*, char(*)[MAX_LEXEM_SIZE])) {
	char* tokens_re = (char*)TOKENS_RE;
	//char tokens_re[] = ";|<<|>>|\\+|-|\\*|,|==|!=|:|\\(|\\)|<=|>=|[_0-9A-Za-z]+|[^ \t\r\f\v\n]";
	//char tokens_re[] = "<<|\\+\\+|--|\\*\\*|==|\\(|\\)|!=|[_0-9A-Za-z]+|[^ \t\r\f\v\n]";
	std::regex tokens_re_(tokens_re);
	struct LexemInfo ifBadLexemeInfo; // = { 0 };
	std::string stringText(text);

	for (std::sregex_token_iterator end, tokenIterator(stringText.begin(), stringText.end(), tokens_re_); tokenIterator != end; ++tokenIterator, ++ * lastLexemInfoInTable) {
		std::string str = *tokenIterator;
		strncpy((*lastLexemInfoInTable)->lexemStr, str.c_str(), MAX_LEXEM_SIZE);
		if ((ifBadLexemeInfo = (*lexicalAnalyzeFunctionPtr)(*lastLexemInfoInTable, identifierIdsTable)).tokenType == UNEXPEXTED_LEXEME_TYPE) {
			break;
		}
	}

	setPositions(text, lexemesInfoTable);

	if (ifBadLexemeInfo.tokenType == UNEXPEXTED_LEXEME_TYPE) {
		strncpy(ifBadLexemeInfo.lexemStr, (*lastLexemInfoInTable)->lexemStr, MAX_LEXEM_SIZE);
		ifBadLexemeInfo.row = (*lastLexemInfoInTable)->row;
		ifBadLexemeInfo.col = (*lastLexemInfoInTable)->col;
	}

	return ifBadLexemeInfo;
}

// after using this function use free(void *) function to release text buffer
size_t loadSource(char** text, char* fileName) {
	if (!fileName) {
		printf("No input file name\r\n");
		return 0;
	}

	FILE* file = fopen(fileName, "rb");

	if (file == NULL) {
		printf("File not loaded\r\n");
		return 0;
	}

	fseek(file, 0, SEEK_END);
	long fileSize_ = ftell(file);
	if (fileSize_ >= MAX_TEXT_SIZE) {
		printf("the file(%ld bytes) is larger than %d bytes\r\n", fileSize_, MAX_TEXT_SIZE);
		fclose(file);
		exit(2); // TODO: ...
		//return 0;
	}
	size_t fileSize = fileSize_;
	rewind(file);

	if (!text) {
		printf("Load source error\r\n");
		return 0;
	}
	*text = (char*)malloc(sizeof(char) * (fileSize + 1));
	if (*text == NULL) {
		fputs("Memory error", stderr);
		fclose(file);
		exit(2); // TODO: ...
		//return 0;
	}

	size_t result = fread(*text, sizeof(char), fileSize, file);
	if (result != fileSize) {
		fputs("Reading error", stderr);
		fclose(file);
		exit(3); // TODO: ...
		//return 0;
	}
	(*text)[fileSize] = '\0';

	fclose(file);

	return fileSize;
}

// freom syntax.cpp
struct ASTNode {
	std::string value;
	bool isTerminal;
	std::vector<ASTNode*> childrens;
	ASTNode* parent;

	ASTNode(const std::string& val, bool isTerminal) : isTerminal(isTerminal), value(val), parent(NULL) {}
#ifdef INCLUDE_TO_SOLUTION_
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
#endif
	~ASTNode() { // use redirectLinks
		for (ASTNode* child : childrens) {
			delete child;
		}
	}
};


#endif

#include "../built_src/dpda1forll2.hpp"
//#include "built_src/dpda1forll2.hpp"

#ifdef INCLUDE_TO_SOLUTION
#define MAX_RULES 356

#define MAX_TOKEN_SIZE 128
#endif
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

#ifdef INCLUDE_TO_SOLUTION
Grammar grammar = {
	GRAMMAR_LL2__2025
};
#endif

//#include "../built_src/config2.h"
//Grammar grammar_123 = { GRAMMAR_123 };

DPDA1Program dpdaProgram123;

#include <string>
#include <map>
//#include <utility>
#include <stack>


std::map<std::string, unsigned char> terminalAndNonTerminalLexemIds;
std::map<unsigned char, std::string> terminalAndNonTerminalLexemStrs__copy;

void buildTerminalAndNonTerminalLexemStrs__copy() {
	for (auto iterator = terminalAndNonTerminalLexemIds.begin(); iterator != terminalAndNonTerminalLexemIds.end(); ++iterator)
		terminalAndNonTerminalLexemStrs__copy[iterator->second] = iterator->first;
}

unsigned char getLexemId(char* str) {
	if(str == nullptr) 
		return UNKNOWN_ELEMENT_ID;
	auto element = terminalAndNonTerminalLexemIds.find(str);
	if (element == terminalAndNonTerminalLexemIds.end())
		return UNKNOWN_ELEMENT_ID;
	else
		return element->second;
}

bool getLexemStr(unsigned char id, std::string& lexemStr) {
	if (terminalAndNonTerminalLexemStrs__copy.empty()) {
		for (auto iterator = terminalAndNonTerminalLexemIds.begin(); iterator != terminalAndNonTerminalLexemIds.end(); ++iterator)
			if (iterator->second == id) {
				lexemStr = iterator->first;
				return true;
			}
	}
	else {
		auto element = terminalAndNonTerminalLexemStrs__copy.find(id);
		if (element != terminalAndNonTerminalLexemStrs__copy.end()) {
			lexemStr = element->second;
			return true;
		}
	}

	return false;
}

int keyWordAndNonTerminalIdsInit(Grammar& grammar, int lastNonUsedid) {
	char* keywords_re = (char*)KEYWORDS_RE;
	char keywords_[sizeof(KEYWORDS_RE)] = { '\0' };
	prepareKeyWordIdGetter(keywords_, keywords_re);

	for (MarkedRule* multiRule = grammar.multiRules; multiRule->firstMarksType; ++multiRule) {
		if (terminalAndNonTerminalLexemIds.find(multiRule->rule.lhs) == terminalAndNonTerminalLexemIds.end()) {
			if (std::regex_match(std::string(multiRule->rule.lhs), std::regex(keywords_re))) {
				terminalAndNonTerminalLexemIds[multiRule->rule.lhs] = getKeyWordId(keywords_, multiRule->rule.lhs, KEYWORD_LEXEM_MIN_ID);
			}
			else {
				terminalAndNonTerminalLexemIds[multiRule->rule.lhs] = lastNonUsedid++;
			}
		}

		for (int firstMarksIndex = 0; multiRule->firstMarks[firstMarksIndex][0] != '\0'; ++firstMarksIndex) {
			if (terminalAndNonTerminalLexemIds.find(multiRule->firstMarks[firstMarksIndex]) == terminalAndNonTerminalLexemIds.end()) {
				if (std::regex_match(std::string(multiRule->firstMarks[firstMarksIndex]), std::regex(keywords_re))) {
					terminalAndNonTerminalLexemIds[multiRule->firstMarks[firstMarksIndex]] = getKeyWordId(keywords_, multiRule->firstMarks[firstMarksIndex], KEYWORD_LEXEM_MIN_ID);
				}
				else {
					terminalAndNonTerminalLexemIds[multiRule->firstMarks[firstMarksIndex]] = lastNonUsedid++;
				}
			}

			for (int rhsVariantIndex = 0; multiRule->rule.rhss[rhsVariantIndex].secondMarksType; ++rhsVariantIndex) {
				for (int secondMarksIndex = 0; multiRule->rule.rhss[rhsVariantIndex].secondMarks[secondMarksIndex][0] != '\0'; ++secondMarksIndex) {
					if (terminalAndNonTerminalLexemIds.find(multiRule->rule.rhss[rhsVariantIndex].secondMarks[secondMarksIndex]) == terminalAndNonTerminalLexemIds.end()) {
						if (std::regex_match(std::string(multiRule->rule.rhss[rhsVariantIndex].secondMarks[secondMarksIndex]), std::regex(keywords_re))) {
							terminalAndNonTerminalLexemIds[multiRule->rule.rhss[rhsVariantIndex].secondMarks[secondMarksIndex]] = getKeyWordId(keywords_, multiRule->rule.rhss[rhsVariantIndex].secondMarks[secondMarksIndex], KEYWORD_LEXEM_MIN_ID);
						}
						else {
							terminalAndNonTerminalLexemIds[multiRule->rule.rhss[rhsVariantIndex].secondMarks[secondMarksIndex]] = lastNonUsedid++;
						}
					}
				}

				for (int rhsElementIndex = 0; multiRule->rule.rhss[rhsVariantIndex].rhs[rhsElementIndex][0] != '\0'; ++rhsElementIndex) {
					if (terminalAndNonTerminalLexemIds.find(multiRule->rule.rhss[rhsVariantIndex].rhs[rhsElementIndex]) == terminalAndNonTerminalLexemIds.end()) {
						if (std::regex_match(std::string(multiRule->rule.rhss[rhsVariantIndex].rhs[rhsElementIndex]), std::regex(keywords_re))) {
							terminalAndNonTerminalLexemIds[multiRule->rule.rhss[rhsVariantIndex].rhs[rhsElementIndex]] = getKeyWordId(keywords_, multiRule->rule.rhss[rhsVariantIndex].rhs[rhsElementIndex], KEYWORD_LEXEM_MIN_ID);
						}
						else {
							terminalAndNonTerminalLexemIds[multiRule->rule.rhss[rhsVariantIndex].rhs[rhsElementIndex]] = lastNonUsedid++;
						}
					}
				}

			}
		}
	}

	if (lastNonUsedid > NONTERMINAL_LEXEM_MAX_ID) {
		printf("Error: maximum number of lexems exceeded.\n");
		exit(0);
	}

	return lastNonUsedid;
}

//void terminalAndNonTerminalIdsInitPart2(struct LexemInfo* lexemInfoTable, int lastNonUsedid) {
//	if (lexemInfoTable == NULL) {
//		printf("Error\n");
//		exit(0);
//	}
//
//	if (true) {
//		printf("Error\n");
//		exit(0);
//	}
//
//	for (; lexemInfoTable->lexemStr[0] != '\0'; ++lexemInfoTable) {
//		if (terminalAndNonTerminalLexemIds.find(lexemInfoTable->lexemStr) == terminalAndNonTerminalLexemIds.end()) {
//			terminalAndNonTerminalLexemIds[lexemInfoTable->lexemStr] = lastNonUsedid++;
//		}
//	}
//}

// set FREE_STATE_ID // -1
void dpda1forLL2SetInitStateAndInitIndexing__DELETE(Grammar& grammar, DPDA1Program& dpda1Program, DPDA1Instructions& dpda1Instructions, PrecursorIds& precursorIds, DPDA1IndexingForSecondElement& dpda1IndexingForSecondElement) {
	unsigned char code = 0; do {
		//if (dpda1Program[toptapeAndStackCode][toptapeAndStackCode].tapeAction == FREE_STATE_ID) { // ... // ????
		//	printf("Error: no support model\r\n");
		//	exit(0);
		//}
		dpda1Instructions[code].stackUpdate.stackAction = POP_AND_MULTIPLIPUSH; // no POP prev state (used for detect error) // NEW 08.2025
		dpda1Instructions[code].tapeAction = SCROLL_TO_RIGHT;
		//08.2025	dpda1Program[codee].stackUpdate.stackAction = POP; // (2)
		//08.2025	dpda1Program[codee].stackUpdate.stackAction = PUSH; // (!)
		//08.2025	dpda1Program[codee].stackUpdate.stackAction = PUSH; // (!)
					//dpda1Program[code].stackUpdate.stackAddon[rhsVariantAddonIndex][rTokekIndex] = emptyElementCode;
		dpda1Instructions[code].rhsVariantAddonIndexMask = 0; // 0 to ignore dpda1IndexingForSecondElement[][] for now		
		for (int rhsVariantIndex = 0; rhsVariantIndex < MAX_RHSCONTEINER_COUNT_IN_PDA; ++rhsVariantIndex) {
			dpda1Instructions[code].stackUpdate.stackAddon[rhsVariantIndex][0] = FREE_STATE_ID;
			for (unsigned int rTokekIndex = 1; rTokekIndex < MAX_RTOKEN_COUNT; ++rTokekIndex) {
				dpda1Instructions[code].stackUpdate.stackAddon[rhsVariantIndex][rTokekIndex] = EMPTY_TOKEN_LEXEM_ID; // (!)
			}
		}
	} while (++code);

	unsigned char tapeCode = 0; do {
		unsigned char topStackCode = 0; do {
//#define ROW_INDEX tapeCode
//#define COLUMN_INDEX toptapeAndStackCode
			dpda1Program[tapeCode][topStackCode].stackUpdate.stackAction = POP_AND_MULTIPLIPUSH; // no POP prev state (used for detect error) // NEW 08.2025
			dpda1Program[tapeCode][topStackCode].tapeAction = NO_SCROLL; // !
			dpda1Program[tapeCode][topStackCode].rhsVariantAddonIndexMask = 0; // 0 to ignore dpda1IndexingForSecondElement[][] for now
			for (int rhsVariantIndex = 0; rhsVariantIndex < MAX_RHSCONTEINER_COUNT_IN_PDA; ++rhsVariantIndex) {
				dpda1Program[tapeCode][topStackCode].stackUpdate.stackAddon[rhsVariantIndex][0] = FREE_STATE_ID;
				for (unsigned int rTokekIndex = 1; rTokekIndex < MAX_RTOKEN_COUNT; ++rTokekIndex) {
					dpda1Program[tapeCode][topStackCode].stackUpdate.stackAddon[rhsVariantIndex][rTokekIndex] = EMPTY_TOKEN_LEXEM_ID; // (!)
				}
			}

			// TODO: set 255 to start				
			dpda1IndexingForSecondElement[tapeCode][topStackCode] = ~0;
//#undef ROW_INDEX
//#undef COLUMN_INDEX
		} while (++topStackCode);
	} while (++tapeCode);
}

// used
// init f
void setAllStatesToDeadStateAndInitIndexing(Grammar& grammar, DPDA1Program& dpda1Program, DPDA1Instructions& dpda1Instructions, PrecursorIds & precursorIds, DPDA1IndexingForSecondElement& dpda1IndexingForSecondElement) {
	unsigned char code = 0; do {
		//if (dpda1Program[toptapeAndStackCode][toptapeAndStackCode].tapeAction == FREE_STATE_ID) { // ... // ????
		//	printf("Error: no support model\r\n");
		//	exit(0);
		//}
		dpda1Instructions[code].stackUpdate.stackAction = POP_AND_MULTIPLIPUSH; // no POP prev state (used for detect error) // NEW 08.2025
		dpda1Instructions[code].tapeAction = NO_SCROLL;
		//08.2025	dpda1Program[codee].stackUpdate.stackAction = POP; // (2)
		//08.2025	dpda1Program[codee].stackUpdate.stackAction = PUSH; // (!)
		//08.2025	dpda1Program[codee].stackUpdate.stackAction = PUSH; // (!)
					//dpda1Program[code].stackUpdate.stackAddon[rhsVariantAddonIndex][rTokekIndex] = emptyElementCode;
		dpda1Instructions[code].rhsVariantAddonIndexMask = 0; // 0 to ignore dpda1IndexingForSecondElement[][] for now
		for (int rhsVariantIndex = 0; rhsVariantIndex < MAX_RHSCONTEINER_COUNT_IN_PDA; ++rhsVariantIndex) {
			dpda1Instructions[code].stackUpdate.stackAddon[rhsVariantIndex][0] = DEAD_STATE_ID;
			for (unsigned int rTokekIndex = 1; rTokekIndex < MAX_RTOKEN_COUNT; ++rTokekIndex) {
				dpda1Instructions[code].stackUpdate.stackAddon[rhsVariantIndex][rTokekIndex] = EMPTY_TOKEN_LEXEM_ID; // (!)
			}
		}
	} while (++code);

	unsigned char tapeCode = 0; do {	
		unsigned char topStackCode = 0; do {
//#define ROW_INDEX tapeCode
//#define COLUMN_INDEX topStackCode
			//if (dpda1Program[toptapeAndStackCode][toptapeAndStackCode].tapeAction == FREE_STATE_ID) { // ... // ????
			//	printf("Error: no support model\r\n");
			//	exit(0);
			//}
			//OLD:
			dpda1Program[tapeCode][topStackCode].stackUpdate.stackAction = POP_AND_MULTIPLIPUSH; // no POP prev state (used for detect error) // NEW 08.2025
			dpda1Program[tapeCode][topStackCode].tapeAction = NO_SCROLL;
			//08.2025	dpda1Program[toptapeAndStackCode][toptapeAndStackCode].stackUpdate.stackAction = POP; // (2)
			//08.2025	dpda1Program[toptapeAndStackCode][toptapeAndStackCode].stackUpdate.stackAction = PUSH; // (!)
			//08.2025	dpda1Program[toptapeAndStackCode][toptapeAndStackCode].stackUpdate.stackAction = PUSH; // (!)
						//dpda1Program[ROW_INDEX][columnIndex].stackUpdate.stackAddon[rhsVariantAddonIndex][rTokekIndex] = emptyElementCode;
			dpda1Program[tapeCode][topStackCode].rhsVariantAddonIndexMask = 0; // 0 to ignore dpda1IndexingForSecondElement[][] for now			
			for (int rhsVariantIndex = 0; rhsVariantIndex < MAX_RHSCONTEINER_COUNT_IN_PDA; ++rhsVariantIndex) {
				dpda1Program[tapeCode][topStackCode].stackUpdate.stackAddon[rhsVariantIndex][0] = DEAD_STATE_ID;
				for (unsigned int rTokekIndex = 1; rTokekIndex < MAX_RTOKEN_COUNT; ++rTokekIndex) {
					dpda1Program[tapeCode][topStackCode].stackUpdate.stackAddon[rhsVariantIndex][rTokekIndex] = EMPTY_TOKEN_LEXEM_ID; // (!)
				}
			}
						
			// TODO: set 255 to start				
			dpda1IndexingForSecondElement[tapeCode][topStackCode] = ~0;

#ifdef DEAD_STATE_ID // regardless of the value DEAD_STATE_ID will be encoded as 0
			precursorIds[tapeCode][topStackCode] = 0;
#endif
//#undef ROW_INDEX
//#undef COLUMN_INDEX
		} while (++topStackCode);
	} while (++tapeCode);
}

void terminalAndNonTerminalIdsInit(Grammar& grammar) {
	terminalAndNonTerminalLexemIds[""] = EMPTY_TOKEN_LEXEM_ID; // no exist in code, but exit as abstract zero lenght element // lastNonUsedid++;
	//terminalAndNonTerminalLexemIds[] = UNKNOWN_ELEMENT_ID; // no exist in code and no exit as abstract element

	terminalAndNonTerminalLexemIds[IDENTIFIER_METATERMINAL_LEXEM_STR] = IDENTIFIER_METATERMINAL_LEXEM_ID;
	terminalAndNonTerminalLexemIds[UNSIGNED_VALUE_METATERMINAL_LEXEM_STR] = UNSIGNED_VALUE_METATERMINAL_LEXEM_ID;
	
	keyWordAndNonTerminalIdsInit(grammar, NONTERMINAL_LEXEM_MIN_ID);

	terminalAndNonTerminalLexemIds[PROGRAM_RULE_STR] = PROGRAM_RULE_ID;
	terminalAndNonTerminalLexemIds[DEAD_STATE_STR] = DEAD_STATE_ID;
}

void setDPDA1InstructionByPrecursorId(MarkedRule& multiRule/*, DPDA1Program& dpda1Program*/, DPDA1Instructions& dpda1Instructions, unsigned char precursorId) {
	bool stateIsNotDefault = false;
	bool stateIsTwiñeChanged = false;
	// not init or not to dead state
	if (//dpda1Program[ROW_INDEX][columnIndexSelector].tapeAction != -1
		dpda1Instructions[precursorId].tapeAction != NO_SCROLL
		||
		dpda1Instructions[precursorId].stackUpdate.stackAction != POP_AND_MULTIPLIPUSH
		||
		dpda1Instructions[precursorId].rhsVariantAddonIndexMask != 0
		||
		dpda1Instructions[precursorId].stackUpdate.stackAddon[0][0] != DEAD_STATE_ID
		||
		dpda1Instructions[precursorId].stackUpdate.stackAddon[0][1] != EMPTY_TOKEN_LEXEM_ID
		) { // ?
		//printf("ERROR: no support model\r\n.");
		stateIsNotDefault = true;
		//exit(0);
	}

	/* default */stateIsTwiñeChanged |= dpda1Instructions[precursorId].tapeAction != NO_SCROLL;
	/* default */dpda1Instructions[precursorId].tapeAction = NO_SCROLL;
	/* defaule */stateIsTwiñeChanged |= dpda1Instructions[precursorId].stackUpdate.stackAction != POP_AND_MULTIPLIPUSH;
	/* defaule */dpda1Instructions[precursorId].stackUpdate.stackAction = POP_AND_MULTIPLIPUSH;
	stateIsTwiñeChanged |= dpda1Instructions[precursorId].rhsVariantAddonIndexMask != (unsigned char)~0;
	dpda1Instructions[precursorId].rhsVariantAddonIndexMask = (unsigned char)~0;
	int rhsVariantIndex = 0;
	for (; multiRule.rule.rhss[rhsVariantIndex].secondMarksType; ++rhsVariantIndex) {
		//if (multiRule->rule.rhss[rhsVariantIndex].secondMarks[0][0] == '\0') {
		//    return multiRule->rule.rhss + rhsVariantIndex;
		//}
		if (/*TODO: REMOVE*/false && dpda1Instructions[precursorId].stackUpdate.stackAction != POP_AND_MULTIPLIPUSH) {
			printf("ERROR: no support model\r\n.");
			exit(0);
		}
		//#ifdef BUILD_AST_BY_DPDA1
		//					dpda1Program[firstMarkCode][stackTopElementCode].stackUpdate.stackAction = POP_AND_MULTIPLIPUSH; // NEW 08.2025
		//#else
		/*TODO: REMOVE*/false && (dpda1Instructions[precursorId].stackUpdate.stackAction = POP_AND_MULTIPLIPUSH); // NEW 08.2025
//#endif

#ifdef USE_PRE_ORDER_MARKER
		bool popStackInFoutStateCodeMarker = true;
#endif
		for (int rhsElementIndex = 0; rhsElementIndex < MAX_RTOKEN_COUNT; ++rhsElementIndex)
			if (rhsElementIndex < multiRule.rule.rhss[rhsVariantIndex].rhs_count) {
				unsigned char newStackElement = getLexemId(multiRule.rule.rhss[rhsVariantIndex].rhs[rhsElementIndex]);
				stateIsTwiñeChanged |= dpda1Instructions[precursorId].stackUpdate.stackAddon[rhsVariantIndex][rhsElementIndex] != newStackElement;
				dpda1Instructions[precursorId].stackUpdate.stackAddon[rhsVariantIndex][rhsElementIndex] = newStackElement;
				//= getLexemTId(multiRule->rule.rhss[rhsVariantIndex].rhs[rhsElementIndex]);
				// = getLexemId(multiRule->rule.rhss[rhsVariantIndex].rhs[rhsElementIndex]);
			}
#ifdef USE_PRE_ORDER_MARKER
			else if (popStackInFoutStateCodeMarker) {
				stateIsTwiñeChanged |= dpda1Instructions[precursorId].stackUpdate.stackAddon[rhsVariantIndex][rhsElementIndex] != MARKER_OF_STRUCTURE_ID;
				dpda1Instructions[precursorId].stackUpdate.stackAddon[rhsVariantIndex][rhsElementIndex] = MARKER_OF_STRUCTURE_ID;
				popStackInFoutStateCodeMarker = false;
			}
#endif
			else {
				stateIsTwiñeChanged |= dpda1Instructions[precursorId].stackUpdate.stackAddon[rhsVariantIndex][rhsElementIndex] != EMPTY_TOKEN_LEXEM_ID;
				dpda1Instructions[precursorId].stackUpdate.stackAddon[rhsVariantIndex][rhsElementIndex] = EMPTY_TOKEN_LEXEM_ID;
			}

#ifdef USE_PRE_ORDER_MARKER
		if (popStackInFoutStateCodeMarker) {
			//
			printf("Error: overflow of rhss size\r\n");
			exit(0);
		}
#endif

		//#if !defined(BUILD_AST_BY_DPDA1) || defined(BUILD_P2C_AST_TYPE_BY_DPDA1)
#ifdef USE_PRE_ORDER_MARKER
					//char popStackInFoutStateCode = getLexemId((char*)"POP_STACK_IN_F_OUT_STATE");
#endif

							// not init or not to dead state
		if (stateIsNotDefault && stateIsTwiñeChanged) { // ?
			printf("ERROR: no support model\r\n.");
			exit(0);
		}

////		if (precursorId > (unsigned char)~0) {
////			printf("ERROR: no support model\r\n.");
////			exit(0);
////		}
////		precursorIds[firstMarkCode][stackTopElementCode] = multiRuleIndex
////#ifdef DEAD_STATE_ID // regardless of the value DEAD_STATE_ID will be encoded as 0
////			+ 1
////#endif
////#ifndef NO_ACCEPTANCE_BEHAVIOR
////			+ 1
////#endif
////			;

		//#ifdef BUILD_AST_BY_DPDA1
		//					lastRHSElementIndex
		//					//dpda1Program[ROW_INDEX][columnIndexSelector].stackUpdate.stackAction = STACK_POP_AND_MULTIPLIPUSH; // NEW 08.2025
		//#else


	}
}







// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//char getLexemTId(char* lexemStr) { // getLexemId
//	return 0;
//}

// used
//?// two table //+//
// STACK_POP_AND_MULTIPLIPUSH
void buildRulePartForDPDA1forLL2(Grammar & grammar, DPDA1Program & dpda1Program, DPDA1Instructions& dpda1Instructions, PrecursorIds & precursorIds, DPDA1IndexingForSecondElement& dpda1IndexingForSecondElement) {

	int aCount = 0; // REMOVE

    // MARKER_OF_STRUCTURE_ID no impl.
	// ALL CODE FOR IDENT AND UNSIGNED VALUE

	//char emptyElementCode = getLexemId((char*)"");
	//char deadStateCode = getLexemId((char*)"DEAD_STATE");

////#define BUILD_C2P_AST_TYPE_BY_DPDA1
//#ifndef BUILD_C2P_AST_TYPE_BY_DPDA1
//#define	BUILD_P2C_AST_TYPE_BY_DPDA1 // TODO: no default
//#endif
////#if !defined(BUILD_AST_BY_DPDA1) || defined(BUILD_P2C_AST_TYPE_BY_DPDA1)

//#ifdef BUILD_P2C_AST_TYPE_BY_DPDA1
//	char popStackInFoutStateCode = getLexemId((char*)"POP_STACK_IN_F_OUT_STATE"); // MARKER_OF_STRUCTURE_ID
//#endif
	for (MarkedRule* multiRule = grammar.multiRules; multiRule->firstMarksType; ++multiRule) {
		unsigned int multiRuleIndex = multiRule - grammar.multiRules;
		unsigned char stackTopElementFirstCode = getLexemId(multiRule->rule.lhs); // char* currSteckElement = multiRule->rule.lhs;

		//unsigned char stackTopElementFirstCode = stackTopElementCode__;
		unsigned char stackTopElementLastCode = stackTopElementFirstCode;
		if (stackTopElementFirstCode == IDENTIFIER_METATERMINAL_LEXEM_ID) { // THIS SHOULD NEVER HAPPEN !
			//stackTopElementFirstCode = IDENT_METETERMINAL_LEXEM_ID;
			stackTopElementLastCode = IDENTIFIER_LEXEM_MAX_ID;

		}
		else if (stackTopElementFirstCode == UNSIGNED_VALUE_METATERMINAL_LEXEM_ID) { // THIS SHOULD NEVER HAPPEN !
			//stackTopElementFirstCode = UNSIGNED_VALUE_METATERMINAL_LEXEM_ID;
			stackTopElementLastCode = LITERAL_LEXEM_MAX_ID;
		}
		for (unsigned char stackTopElementCode = stackTopElementFirstCode; stackTopElementCode <= stackTopElementLastCode; ++stackTopElementCode) {

			//		multiRule->firstMarksType;

					// firstMarkCode = 0 ==> ""
			unsigned char firstMarkCode = 0; do {
				//const char * firstMarkStr = getLexemStrById(firstMarkCode);
				//unsigned long long int lexemTypeByFirstMarkCode = getLexemTypeById(firstMarkCode);

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
				bool firstMarkCodeIsUsed = true;
				for (int firstMarksIndex = 0; multiRule->firstMarks[firstMarksIndex][0] != '\0'; ++firstMarksIndex) {
					unsigned char firstMarkCodeByRule = getLexemId(multiRule->firstMarks[firstMarksIndex]);
					if (multiRule->firstMarksType == LA_NOT
						&& (
							firstMarkCode == firstMarkCodeByRule
							||
							firstMarkCodeByRule == IDENTIFIER_METATERMINAL_LEXEM_ID
							&&
							firstMarkCode >= IDENTIFIER_METATERMINAL_LEXEM_ID
							&&
							firstMarkCode <= IDENTIFIER_LEXEM_MAX_ID
							||
							firstMarkCodeByRule == UNSIGNED_VALUE_METATERMINAL_LEXEM_ID
							&&
							firstMarkCode >= UNSIGNED_VALUE_METATERMINAL_LEXEM_ID
							&&
							firstMarkCode <= LITERAL_LEXEM_MAX_ID
							)
						) {
						firstMarkCodeIsUsed = false;
					}
					else if (multiRule->firstMarksType == LA_IS
						&& (
							firstMarkCode != firstMarkCodeByRule
							||
							firstMarkCodeByRule == IDENTIFIER_METATERMINAL_LEXEM_ID
							&&
							firstMarkCode < IDENTIFIER_METATERMINAL_LEXEM_ID
							&&
							firstMarkCode > IDENTIFIER_LEXEM_MAX_ID
							||
							firstMarkCodeByRule == UNSIGNED_VALUE_METATERMINAL_LEXEM_ID
							&&
							firstMarkCode < UNSIGNED_VALUE_METATERMINAL_LEXEM_ID
							&&
							firstMarkCode > LITERAL_LEXEM_MAX_ID
							)
						) {
						firstMarkCodeIsUsed = false;
					}
				}
				if(firstMarkCodeIsUsed){
#if 0
					unsigned char firstMarkCodeByRule = getLexemId(multiRule->firstMarks[firstMarksIndex]);						
					if (multiRule->firstMarksType == LA_NOT
							&& (
								firstMarkCode == firstMarkCodeByRule
								||
								firstMarkCodeByRule == IDENT_METETERMINAL_LEXEM_ID
								&&
								firstMarkCode >= IDENT_METETERMINAL_LEXEM_ID
								&&
								firstMarkCode <= IDENTIFIER_LEXEM_MAX_ID
								||
								firstMarkCodeByRule == UNSIGNED_VALUE_METATERMINAL_LEXEM_ID
								&&
								firstMarkCode >= UNSIGNED_VALUE_METATERMINAL_LEXEM_ID
								&&
								firstMarkCode <= LITERAL_LEXEM_MAX_ID
								)
							) {
							continue;						
					}										
					else if (multiRule->firstMarksType == LA_IS
							&& (
								firstMarkCode != firstMarkCodeByRule
								||
								firstMarkCodeByRule == IDENT_METETERMINAL_LEXEM_ID
								&&
								firstMarkCode < IDENT_METETERMINAL_LEXEM_ID
								&&
								firstMarkCode > IDENTIFIER_LEXEM_MAX_ID
								||
								firstMarkCodeByRule == UNSIGNED_VALUE_METATERMINAL_LEXEM_ID
								&&
								firstMarkCode < UNSIGNED_VALUE_METATERMINAL_LEXEM_ID
								&&
								firstMarkCode > LITERAL_LEXEM_MAX_ID
								)
							) {
							continue;	
					}
#endif


					////if (/*lexemTypeByFirstMarkCode == IDENTIFIER_LEXEME_TYPE && !strcmp(multiRule->firstMarks[firstMarksIndex], "ident_terminal")
					////	|| lexemTypeByFirstMarkCode == VALUE_LEXEME_TYPE && !strcmp(multiRule->firstMarks[firstMarksIndex], "unsigned_value_terminal")
					////	||*/firstMarkCode == getLexemId(multiRule->firstMarks[firstMarksIndex])) {
					////	if (multiRule->firstMarksType == LA_NOT) {
					////		continue;
					////	}
					////}
					////else {
					////	if (multiRule->firstMarksType == LA_IS) {
					////		continue;
					////	}
					////}
					////
					////unsigned char firstMarkCodeFirstCode = firstMarkCode;
					////unsigned char firstMarkCodeLastCode = firstMarkCode;
					////if (firstMarkCode == IDENT_METETERMINAL_LEXEM_ID) {
					////	firstMarkCodeFirstCode = IDENT_METETERMINAL_LEXEM_ID;
					////	firstMarkCodeLastCode = IDENTIFIER_LEXEM_MAX_ID;
					////
					////}
					////else if (firstMarkCode == UNSIGNED_VALUE_METATERMINAL_LEXEM_ID) {
					////	firstMarkCodeFirstCode = UNSIGNED_VALUE_METATERMINAL_LEXEM_ID;
					////	firstMarkCodeLastCode = LITERAL_LEXEM_MAX_ID;
					////}
					//for (unsigned char firstMarkCodeSelector = firstMarkCodeFirstCode; firstMarkCodeSelector <= firstMarkCodeLastCode; ++firstMarkCodeSelector) {
//#define ROW_INDEX firstMarkCodeSelector // firstMarksIndex


					//if (firstMarkCode == 0 && stackTopElementCode == 158) {
					//	printf("0: !\r\n");
					//}

					bool stateIsNotDefault = false;
					bool stateIsTwiñeChanged = false;
						// not init or not to dead state
						if (//dpda1Program[ROW_INDEX][columnIndexSelector].tapeAction != -1
							dpda1Program[firstMarkCode][stackTopElementCode].tapeAction != NO_SCROLL
							||
							dpda1Program[firstMarkCode][stackTopElementCode].stackUpdate.stackAction != POP_AND_MULTIPLIPUSH
							||
							dpda1Program[firstMarkCode][stackTopElementCode].rhsVariantAddonIndexMask != 0
							||
							dpda1Program[firstMarkCode][stackTopElementCode].stackUpdate.stackAddon[0][0] != DEAD_STATE_ID
							||
							dpda1Program[firstMarkCode][stackTopElementCode].stackUpdate.stackAddon[0][1] != EMPTY_TOKEN_LEXEM_ID
							) { // ?
							//printf("ERROR: no support model\r\n.");
							stateIsNotDefault = true;
							//exit(0);
						}

						/* default */stateIsTwiñeChanged |= dpda1Program[firstMarkCode][stackTopElementCode].tapeAction != NO_SCROLL;
						/* default */dpda1Program[firstMarkCode][stackTopElementCode].tapeAction = NO_SCROLL;
						/* defaule */stateIsTwiñeChanged |= dpda1Program[firstMarkCode][stackTopElementCode].stackUpdate.stackAction != POP_AND_MULTIPLIPUSH;
						/* defaule */dpda1Program[firstMarkCode][stackTopElementCode].stackUpdate.stackAction = POP_AND_MULTIPLIPUSH;
						stateIsTwiñeChanged |= dpda1Program[firstMarkCode][stackTopElementCode].rhsVariantAddonIndexMask != (unsigned char)~0;
						dpda1Program[firstMarkCode][stackTopElementCode].rhsVariantAddonIndexMask = (unsigned char)~0;
						int rhsVariantIndex = 0;
						for (; multiRule->rule.rhss[rhsVariantIndex].secondMarksType; ++rhsVariantIndex) {
							//if (multiRule->rule.rhss[rhsVariantIndex].secondMarks[0][0] == '\0') {
							//    return multiRule->rule.rhss + rhsVariantIndex;
							//}
							if (/*TODO: REMOVE*/false && dpda1Program[firstMarkCode][stackTopElementCode].stackUpdate.stackAction != POP_AND_MULTIPLIPUSH) {
								printf("ERROR: no support model\r\n.");
								exit(0);
							}
		//#ifdef BUILD_AST_BY_DPDA1
		//					dpda1Program[firstMarkCode][stackTopElementCode].stackUpdate.stackAction = POP_AND_MULTIPLIPUSH; // NEW 08.2025
		//#else
							/*TODO: REMOVE*/false && (dpda1Program[firstMarkCode][stackTopElementCode].stackUpdate.stackAction = POP_AND_MULTIPLIPUSH); // NEW 08.2025
		//#endif
							
#ifdef USE_PRE_ORDER_MARKER
							bool popStackInFoutStateCodeMarker = true;
#endif
							for (int rhsElementIndex = 0; rhsElementIndex < MAX_RTOKEN_COUNT; ++rhsElementIndex)
								if (rhsElementIndex < multiRule->rule.rhss[rhsVariantIndex].rhs_count) {
									unsigned char newStackElement = getLexemId(multiRule->rule.rhss[rhsVariantIndex].rhs[rhsElementIndex]);
									stateIsTwiñeChanged |= dpda1Program[firstMarkCode][stackTopElementCode].stackUpdate.stackAddon[rhsVariantIndex][rhsElementIndex] != newStackElement;
									dpda1Program[firstMarkCode][stackTopElementCode].stackUpdate.stackAddon[rhsVariantIndex][rhsElementIndex] = newStackElement;
										//= getLexemTId(multiRule->rule.rhss[rhsVariantIndex].rhs[rhsElementIndex]);
										// = getLexemId(multiRule->rule.rhss[rhsVariantIndex].rhs[rhsElementIndex]);
								}
#ifdef USE_PRE_ORDER_MARKER
								else if (popStackInFoutStateCodeMarker) {
									stateIsTwiñeChanged |= dpda1Program[firstMarkCode][stackTopElementCode].stackUpdate.stackAddon[rhsVariantIndex][rhsElementIndex] != MARKER_OF_STRUCTURE_ID;
									dpda1Program[firstMarkCode][stackTopElementCode].stackUpdate.stackAddon[rhsVariantIndex][rhsElementIndex] = MARKER_OF_STRUCTURE_ID;
									popStackInFoutStateCodeMarker = false;
								}
#endif
								else { 
									stateIsTwiñeChanged |= dpda1Program[firstMarkCode][stackTopElementCode].stackUpdate.stackAddon[rhsVariantIndex][rhsElementIndex] != EMPTY_TOKEN_LEXEM_ID;
									dpda1Program[firstMarkCode][stackTopElementCode].stackUpdate.stackAddon[rhsVariantIndex][rhsElementIndex] = EMPTY_TOKEN_LEXEM_ID; 
								}

#ifdef USE_PRE_ORDER_MARKER
							if (popStackInFoutStateCodeMarker) {
								//
								printf("Error: overflow of rhss size\r\n");
								exit(0);
							}
#endif

							//#if !defined(BUILD_AST_BY_DPDA1) || defined(BUILD_P2C_AST_TYPE_BY_DPDA1)
#ifdef USE_PRE_ORDER_MARKER
					//char popStackInFoutStateCode = getLexemId((char*)"POP_STACK_IN_F_OUT_STATE");
#endif

							// not init or not to dead state
							if (stateIsNotDefault && stateIsTwiñeChanged) { // ?
								printf("ERROR: no support model\r\n.");
								exit(0);
							}
							
							unsigned int precursorId = multiRuleIndex
#ifdef DEAD_STATE_ID // regardless of the value DEAD_STATE_ID will be encoded as 0	
								+ 1
#endif
#ifndef NO_ACCEPTANCE_BEHAVIOR							
								+ 1
#endif	
								;

							if (precursorId > (unsigned char)~0) {
								printf("ERROR: no support model\r\n.");
								exit(0);
							}

							setDPDA1InstructionByPrecursorId(*multiRule, dpda1Instructions, (unsigned char)precursorId);
	
							precursorIds[firstMarkCode][stackTopElementCode] = precursorId;


//#ifdef BUILD_AST_BY_DPDA1
//					lastRHSElementIndex
//					//dpda1Program[ROW_INDEX][columnIndexSelector].stackUpdate.stackAction = STACK_POP_AND_MULTIPLIPUSH; // NEW 08.2025
//#else


					// 

					//for (char secondMarkCode = 255; secondMarkCode++;) {
					//    // TODO: set 255 to start
					//	dpda1IndexingForSecondElement[secondMarkCode][columnIndexSelector] = 255; // = ~0;
					//}

					// char value = rhsVariantIndex; // no used

							unsigned char secondMarkCode = 0; do {
								//char columnIndex = getLexemTId(multiRule->firstMarks);
								//const char* secondMarkStr = getLexemStr(secondMarkCode, lexemStr);
								//unsigned long long int lexemTypeBySecondMarkCode = getLexemTypeById(secondMarkCode);
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
								bool secondMarkCodeIsUsed = true;
								if (multiRule->rule.rhss[rhsVariantIndex].secondMarks[0/* for secondMarksIndexForCurrentRHS == 0 */][0] == '\0'/*.secondMarksType*/) { // ! TODO: ...

									//if (secondMarkCode == 0 && stackTopElementCode == 168) {
									//	printf("!\r\n");
									//}

									secondMarkCodeIsUsed = false; // !
								}
								for (int secondMarksIndexForCurrentRHS = 0; multiRule->rule.rhss[rhsVariantIndex].secondMarks[secondMarksIndexForCurrentRHS][0] != '\0'; ++secondMarksIndexForCurrentRHS) {
									unsigned char secondMarkCodeForCurrentRHS = getLexemId(multiRule->rule.rhss[rhsVariantIndex].secondMarks[secondMarksIndexForCurrentRHS]);
									if (multiRule->rule.rhss[rhsVariantIndex].secondMarksType == LA_NOT
										&& (
											secondMarkCode == secondMarkCodeForCurrentRHS
											||
											secondMarkCodeForCurrentRHS == IDENTIFIER_METATERMINAL_LEXEM_ID
											&&
											secondMarkCode >= IDENTIFIER_METATERMINAL_LEXEM_ID
											&&
											secondMarkCode <= IDENTIFIER_LEXEM_MAX_ID
											||
											secondMarkCodeForCurrentRHS == UNSIGNED_VALUE_METATERMINAL_LEXEM_ID
											&&
											secondMarkCode >= UNSIGNED_VALUE_METATERMINAL_LEXEM_ID
											&&
											secondMarkCode <= LITERAL_LEXEM_MAX_ID
											)
										) {
										secondMarkCodeIsUsed = false;
									}
									else if (multiRule->rule.rhss[rhsVariantIndex].secondMarksType == LA_IS
										&& (
											secondMarkCode != secondMarkCodeForCurrentRHS
											||
											secondMarkCodeForCurrentRHS == IDENTIFIER_METATERMINAL_LEXEM_ID
											&&
											secondMarkCode < IDENTIFIER_METATERMINAL_LEXEM_ID
											&&
											secondMarkCode > IDENTIFIER_LEXEM_MAX_ID
											||
											secondMarkCodeForCurrentRHS == UNSIGNED_VALUE_METATERMINAL_LEXEM_ID
											&&
											secondMarkCode < UNSIGNED_VALUE_METATERMINAL_LEXEM_ID
											&&
											secondMarkCode > LITERAL_LEXEM_MAX_ID
											)
										) {
										secondMarkCodeIsUsed = false;
									}
									//else if (!multiRule->rule.rhss[rhsVariantIndex].secondMarks[0/*?*/][0] == '\0'/*.secondMarksType*/) { // ! TODO: ...
									//	//continue; // !
									//}
									else if (multiRule->rule.rhss[rhsVariantIndex].secondMarks[0/*?*/][0] == '\0'/*.secondMarksType*/) { // ! TODO: REMOVE 

										//if (secondMarkCode == 0 && stackTopElementCode == 168) {
										//	printf("!\r\n");
										//}

										secondMarkCodeIsUsed = false; // !
									}
								}
								if (secondMarkCodeIsUsed) {
									////char secondMarkCodeForCurrentRHS = getLexemId(multiRule->rule.rhss[rhsVariantIndex].secondMarks[secondMarksIndexForCurrentRHS]);
									////if (/*lexemTypeBySecondMarkCode == IDENTIFIER_LEXEME_TYPE && !strcmp(multiRule->rule.rhss[rhsVariantIndex].secondMarks[secondMarksIndexForCurrentRHS], "ident_terminal")
									////	|| lexemTypeBySecondMarkCode == VALUE_LEXEME_TYPE && !strcmp(multiRule->rule.rhss[rhsVariantIndex].secondMarks[secondMarksIndexForCurrentRHS], "unsigned_value_terminal")
									////	||*/secondMarkCode == secondMarkCodeForCurrentRHS) {
									////	if (multiRule->rule.rhss[rhsVariantIndex].secondMarksType == LA_NOT) {
									////		continue;
									////	}
									////}
									////else {
									////	if (multiRule->rule.rhss[rhsVariantIndex].secondMarksType == LA_IS) {
									////		continue;
									////	}
									////}
#if 0
									unsigned char secondMarkCodeForCurrentRHS = getLexemId(multiRule->rule.rhss[rhsVariantIndex].secondMarks[secondMarksIndexForCurrentRHS]);
									if (multiRule->rule.rhss[rhsVariantIndex].secondMarksType == LA_NOT
										&& (
											secondMarkCode == secondMarkCodeForCurrentRHS
											||
											secondMarkCodeForCurrentRHS == IDENT_METETERMINAL_LEXEM_ID
											&&
											secondMarkCode >= IDENT_METETERMINAL_LEXEM_ID
											&&
											secondMarkCode <= IDENTIFIER_LEXEM_MAX_ID
											||
											secondMarkCodeForCurrentRHS == UNSIGNED_VALUE_METATERMINAL_LEXEM_ID
											&&
											secondMarkCode >= UNSIGNED_VALUE_METATERMINAL_LEXEM_ID
											&&
											secondMarkCode <= LITERAL_LEXEM_MAX_ID
											)
										) {
										continue;
									}
									else if (multiRule->rule.rhss[rhsVariantIndex].secondMarksType == LA_IS
										&& (
											secondMarkCode != secondMarkCodeForCurrentRHS
											||
											secondMarkCodeForCurrentRHS == IDENT_METETERMINAL_LEXEM_ID
											&&
											secondMarkCode < IDENT_METETERMINAL_LEXEM_ID
											&&
											secondMarkCode > IDENTIFIER_LEXEM_MAX_ID
											||
											secondMarkCodeForCurrentRHS == UNSIGNED_VALUE_METATERMINAL_LEXEM_ID
											&&
											secondMarkCode < UNSIGNED_VALUE_METATERMINAL_LEXEM_ID
											&&
											secondMarkCode > LITERAL_LEXEM_MAX_ID
											)
										) {
										continue;
									}
									else if (!multiRule->rule.rhss[rhsVariantIndex].secondMarks[0/*?*/][0] == '\0'/*.secondMarksType*/) { // ! TODO: ...
										//continue; // !
									}
#endif


//#define ROW_INDEX_FOR_SECOND_TABLE secondMarkCode

									//char* currSecondMark = multiRule->rule.rhss[rhsVariantIndex].secondMarks[secondMarksIndex];
		//							char rowIndexForSecondTable = getLexemTId(multiRule->rule.rhss[rhsVariantIndex].secondMarks[secondMarksIndexForCurrentRHS]);

									//if (secondMarkCode == 101 && stackTopElementCode == 153) {
									//	printf("!\r\n");
									//}

									if (dpda1IndexingForSecondElement[secondMarkCode][stackTopElementCode] != (unsigned char)~0) {

										//if (multiRule->rule.rhss[rhsVariantIndex].secondMarks[0/*?*/][0] == '\0'/*.secondMarksType*/) { // ! TODO: ...
										//	//printf("!\r\n");
										//	if (secondMarkCode == 0 && stackTopElementCode == 168) {
										//		printf("!\r\n");
										//	}
//
//
										//}


										if (dpda1IndexingForSecondElement[secondMarkCode][stackTopElementCode] != rhsVariantIndex) {
											printf("ERROR: no support model or model consider error.\r\n");
											exit(0);
										}
										else {
											// printf("WARNING: multi-indexing.\r\n"); // normal!

										}
									}

									////unsigned char secondMarkCodeFirstCode = secondMarkCode;
									////unsigned char secondMarkCodeLastCode = secondMarkCode;
									////if (secondMarkCode == IDENT_METETERMINAL_LEXEM_ID) {
									////	secondMarkCodeFirstCode = IDENT_METETERMINAL_LEXEM_ID;
									////	secondMarkCodeLastCode = IDENTIFIER_LEXEM_MAX_ID;
									////
									////}
									////else if (secondMarkCode == UNSIGNED_VALUE_METATERMINAL_LEXEM_ID) {
									////	secondMarkCodeFirstCode = UNSIGNED_VALUE_METATERMINAL_LEXEM_ID;
									////	secondMarkCodeLastCode = LITERAL_LEXEM_MAX_ID;
									////}
									//for (unsigned char secondMarkCodeSelector = secondMarkCodeFirstCode; secondMarkCodeSelector <= secondMarkCodeLastCode; ++secondMarkCodeSelector) {
//#undef ROW_INDEX_FOR_SECOND_TABLE
//#define ROW_INDEX_FOR_SECOND_TABLE secondMarkCodeSelector
										//dpda1IndexingForSecondElement[ROW_INDEX_FOR_SECOND_TABLE][columnIndexSelector] = rhsVariantIndex;
										dpda1IndexingForSecondElement[secondMarkCode][stackTopElementCode] = rhsVariantIndex;
										++aCount;
									//}

//#undef ROW_INDEX_FOR_SECOND_TABLE
								}
								// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
								// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
								// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
							} while (++secondMarkCode);
#if 0
							 // } !
							/*int */rhsVariantAddonIndex = rhsVariantIndex + 1; // REMOVE
							if ( false && !multiRule->rule.rhss[rhsVariantAddonIndex].secondMarksType) {
								bool needStateToDeadState = false;

								// scan
								unsigned char secondMarkCode = 0; do {
									//const char* secondMarkStr = getLexemStr(secondMarkCode);
									if (dpda1IndexingForSecondElement[secondMarkCode][stackTopElementCodeSelector] == 255) { // !!.
										needStateToDeadState = true;
										dpda1IndexingForSecondElement[secondMarkCode][stackTopElementCodeSelector] = rhsVariantAddonIndex;
									}
								} while (++secondMarkCode);

								// add "to dead" state // --> ...
								if (needStateToDeadState) {
									dpda1Program[firstMarkCodeSelector][stackTopElementCodeSelector].stackUpdate.stackAddon[rhsVariantAddonIndex][0/*rhsVariantIndex*/] = DEAD_STATE_ID;
									for (int rhsElementIndex = 1; rhsElementIndex < MAX_RTOKEN_COUNT; ++rhsElementIndex)
										dpda1Program[firstMarkCodeSelector][stackTopElementCodeSelector].stackUpdate.stackAddon[rhsVariantAddonIndex][rhsElementIndex] = EMPTY_TOKEN_LEXEM_ID;
								}
							}
#endif
						}
						// MOVE!
						if (false && multiRule->rule.rhss[0].secondMarks[0][0] != '\0'/*multiRule->rule.rhss[0].secondMarksType _ */) { // + if second mark used, first rhs variant type will be set
							if (multiRule->rule.rhss[rhsVariantIndex].secondMarksType) {
								printf("No support model or model consider error.\r\n");
								exit(0);
							}

							if (dpda1Program[firstMarkCode][stackTopElementCode].rhsVariantAddonIndexMask != (unsigned char)~0) {
								printf("Error.\r\n");
								exit(0);
							}
							dpda1Program[firstMarkCode][stackTopElementCode].rhsVariantAddonIndexMask = ~0; // !!! // MOVE
		
							//
							bool needStateToDeadState = false;

							// scan
							unsigned char secondMarkCode = 0; do {
								//const char* secondMarkStr = getLexemStr(secondMarkCode);
								if (dpda1IndexingForSecondElement[secondMarkCode][stackTopElementCode] == 255) { // !!.
									needStateToDeadState = true;
									dpda1IndexingForSecondElement[secondMarkCode][stackTopElementCode] = rhsVariantIndex;
								}
							} while (++secondMarkCode);

							// add "to dead"-state // --> ...
							if (needStateToDeadState) {
								dpda1Program[firstMarkCode][stackTopElementCode].stackUpdate.stackAddon[rhsVariantIndex][0/*rhsVariantIndex*/] = DEAD_STATE_ID;
								for (int rhsElementIndex = 1; rhsElementIndex < MAX_RTOKEN_COUNT; ++rhsElementIndex)
									dpda1Program[firstMarkCode][stackTopElementCode].stackUpdate.stackAddon[rhsVariantIndex][rhsElementIndex] = EMPTY_TOKEN_LEXEM_ID;
							}
						}
						else if (false) {						
							//
							dpda1Program[firstMarkCode][stackTopElementCode].rhsVariantAddonIndexMask = 0; // not useed for accept state (? dpda1IndexingForSecondElement; ==> ignore => mask 0)
						}
//#undef ROW_INDEX						
//#undef COLUMN_INDEX // +
						//#undef ROW_INDEX_FOR_SECOND_TABLE
					//}
				}
				////////////////////////////////////////////////////////////////////////////////////////////////////////
				////////////////////////////////////////////////////////////////////////////////////////////////////////
				////////////////////////////////////////////////////////////////////////////////////////////////////////
			} while (++firstMarkCode);
		}
	}
	aCount;
#if 1
	// II
	for (MarkedRule* multiRule = grammar.multiRules; true && multiRule->firstMarksType; ++multiRule) {
		unsigned char stackTopElementFirstCode = getLexemId(multiRule->rule.lhs);

		unsigned char stackTopElementLastCode = stackTopElementFirstCode;
		if (stackTopElementFirstCode == IDENTIFIER_METATERMINAL_LEXEM_ID) // THIS SHOULD NEVER HAPPEN !
			stackTopElementLastCode = IDENTIFIER_LEXEM_MAX_ID;
		else if (stackTopElementFirstCode == UNSIGNED_VALUE_METATERMINAL_LEXEM_ID) // THIS SHOULD NEVER HAPPEN !
			stackTopElementLastCode = LITERAL_LEXEM_MAX_ID;

		for (unsigned char stackTopElementCode = stackTopElementFirstCode; stackTopElementCode <= stackTopElementLastCode; ++stackTopElementCode) {
			unsigned char firstMarkCode = 0; do {
				bool firstMarkCodeIsUsed = true;
				for (int firstMarksIndex = 0; multiRule->firstMarks[firstMarksIndex][0] != '\0'; ++firstMarksIndex) {
					unsigned char firstMarkCodeByRule = getLexemId(multiRule->firstMarks[firstMarksIndex]);
					if (multiRule->firstMarksType == LA_NOT
						&& (
							firstMarkCode == firstMarkCodeByRule
							||
							firstMarkCodeByRule == IDENTIFIER_METATERMINAL_LEXEM_ID
							&&
							firstMarkCode >= IDENTIFIER_METATERMINAL_LEXEM_ID
							&&
							firstMarkCode <= IDENTIFIER_LEXEM_MAX_ID
							||
							firstMarkCodeByRule == UNSIGNED_VALUE_METATERMINAL_LEXEM_ID
							&&
							firstMarkCode >= UNSIGNED_VALUE_METATERMINAL_LEXEM_ID
							&&
							firstMarkCode <= LITERAL_LEXEM_MAX_ID
							)
						) {
						firstMarkCodeIsUsed = false;
					}
					else if (multiRule->firstMarksType == LA_IS
						&& (
							firstMarkCode != firstMarkCodeByRule
							||
							firstMarkCodeByRule == IDENTIFIER_METATERMINAL_LEXEM_ID
							&&
							firstMarkCode < IDENTIFIER_METATERMINAL_LEXEM_ID
							&&
							firstMarkCode > IDENTIFIER_LEXEM_MAX_ID
							||
							firstMarkCodeByRule == UNSIGNED_VALUE_METATERMINAL_LEXEM_ID
							&&
							firstMarkCode < UNSIGNED_VALUE_METATERMINAL_LEXEM_ID
							&&
							firstMarkCode > LITERAL_LEXEM_MAX_ID
							)
						) {
						firstMarkCodeIsUsed = false;
					}
				}
				if (firstMarkCodeIsUsed) {
					int rhsVariantIndex = 0;
					for (; multiRule->rule.rhss[rhsVariantIndex].secondMarksType; ++rhsVariantIndex);
					// MOVE!
					if (multiRule->rule.rhss[0].secondMarks[0][0] != '\0'/*multiRule->rule.rhss[0].secondMarksType _ */) { // + if second mark used, first rhs variant type will be set
						if (multiRule->rule.rhss[rhsVariantIndex].secondMarksType) {
							printf("No support model or model consider error.\r\n");
							exit(0);
						}

						if (dpda1Program[firstMarkCode][stackTopElementCode].rhsVariantAddonIndexMask != (unsigned char)~0) {
							printf("Error.\r\n");
							exit(0);
						}
						//dpda1Program[firstMarkCode][stackTopElementCode].rhsVariantAddonIndexMask = ~0; // !!! // MOVE

						//
						bool needStateToDeadState = false;

						// scan
						unsigned char secondMarkCode = 0; do {
							//const char* secondMarkStr = getLexemStr(secondMarkCode);
							if (dpda1IndexingForSecondElement[secondMarkCode][stackTopElementCode] == 255) { // !!.
								needStateToDeadState = true;
								dpda1IndexingForSecondElement[secondMarkCode][stackTopElementCode] = rhsVariantIndex;
							}
						} while (++secondMarkCode);

						// add "to dead"-state // --> ...
						if (needStateToDeadState) {
							dpda1Program[firstMarkCode][stackTopElementCode].stackUpdate.stackAddon[rhsVariantIndex][0/*rhsVariantIndex*/] = DEAD_STATE_ID;
							for (int rhsElementIndex = 1; rhsElementIndex < MAX_RTOKEN_COUNT; ++rhsElementIndex)
								dpda1Program[firstMarkCode][stackTopElementCode].stackUpdate.stackAddon[rhsVariantIndex][rhsElementIndex] = EMPTY_TOKEN_LEXEM_ID;
						}
					}
					else {
						//
						dpda1Program[firstMarkCode][stackTopElementCode].rhsVariantAddonIndexMask = 0; // not useed for accept state (? dpda1IndexingForSecondElement; ==> ignore => mask 0)
					}
				}
			} while (++firstMarkCode);
		}
	}
#endif

#if 0
	// not init or not to dead state
	if (//dpda1Program[ROW_INDEX][columnIndexSelector].tapeAction != -1
		dpda1Program[firstMarkCode][stackTopElementCode].tapeAction != NO_SCROLL
		||
		dpda1Program[firstMarkCode][stackTopElementCode].stackUpdate.stackAction != POP_AND_MULTIPLIPUSH
		||
		dpda1Program[firstMarkCode][stackTopElementCode].rhsVariantAddonIndexMask != 0
		||
		dpda1Program[firstMarkCode][stackTopElementCode].stackUpdate.stackAddon[0][0] != DEAD_STATE_ID
		||
		dpda1Program[firstMarkCode][stackTopElementCode].stackUpdate.stackAddon[0][1] != EMPTY_TOKEN_LEXEM_ID
		) { // ?
		//printf("ERROR: no support model\r\n.");
		stateIsNotDefault = true;
		//exit(0);
	}
#endif

	// table refuse
	unsigned char firstMarkCode = 0; do {
		unsigned char topStackCode = 0; do {
			//if (dpda1Program[firstMarkCode][topStackCode] == (unsigned char)~0) {
			//	dpda1Program[firstMarkCode][topStackCode] = 0;
			//}
		} while (++topStackCode);
	} while (++firstMarkCode);

	// set default 0-index for non-setted elements
	unsigned char secondMarkCode = 0; do {
		unsigned char topStackCode = 0; do {
			if (dpda1IndexingForSecondElement[secondMarkCode][topStackCode] == (unsigned char)~0) {
				dpda1IndexingForSecondElement[secondMarkCode][topStackCode] = 0;
			}
		} while (++topStackCode);
	} while (++secondMarkCode);
}

// for buildDPDA2forLL2
void  buildRulePartForDPDA2forLL2() { // use (TODO) // print_pda_by_transition_table_to_file
 // q0 (POP), q1(SCROLL_TO_RIGHT), q2, q3, q4, q5 ... (PUSH) 
	//(q, part)
	// //             0x00                0x01               0x02              0x03              0x04  
	//         q0 q1 q2 q3 q4 a5 | q0 q1 q2 q3 q4 a5 | q0 q1 q2 q3 q4 q5    |              |
}

char rhs_buffer[MAX_LEXEM_SIZE * MAX_RTOKEN_COUNT] = { 0 };
char part_buffer[MAX_LEXEM_SIZE * 3 + 1024] = { 0 };
//TODO: gen second table for Str!!
//typedef PDAInstruction DPDA1Program[LL2_SYMBOL_NUMBER][LL2_MAX_STATES];
void print_pda_by_transition_table_to_file(DPDA1Program& dpda1Program, DPDA1Instructions& dpda1Instructions, PrecursorIds& precursorIds, DPDA1IndexingForSecondElement& dpda1IndexingForSecondElement, bool useShortTable = false) {
	FILE* f = fopen(CONST_STRING(DPDA1_FILE_NAME), "w");
	if (!f) {
		perror("fopen");
		return;
	}

	fprintf(f, "#define _CRT_SECURE_NO_WARNINGS\n\n");
	fprintf(f, "//#define LL2_SYMBOL_NUMBER 256\n");
	//fprintf(f, "//#define STATE_NUMBER %d\n\n", state_counter);
	fprintf(f, "//#define LL2_MAX_STATES 256\n");
	fprintf(f, "//#define LL2_PRECURSOR_COUNT 256\n");  

	fprintf(f, "\n");

	fprintf(f, "%s %s = {\n", CONST_STRING(DPDA1ReverseInstructions), CONST_STRING(DPDA1_TABLE_NAME) CONST_STRING(DPDA1ReverseInstructions));
	for (unsigned int precursorId = 0; precursorId < LL2_PRECURSOR_COUNT; ++precursorId) {
	//{0, NO_SCROLL, {PUSH, {123, 123, 4, 0}}},
		printf("\r%d                      ", precursorId);
		fprintf(f, "/* %3d */ { 0x%02hhX", precursorId, dpda1Instructions[precursorId].rhsVariantAddonIndexMask);
		//.rhsVariantAddonIndexMask;

		if (dpda1Instructions[precursorId].tapeAction == NO_SCROLL) {
			fprintf(f, ", NO_SCROLL      ,");
		}
		else if (dpda1Instructions[precursorId].tapeAction == SCROLL_TO_RIGHT) {
			fprintf(f, ", SCROLL_TO_RIGHT,");
		}
		else {
			printf("ERROR: no support model\r\n.");
			fclose(f);
			exit(0);
		}

		//fprintf(f, ", { ");

		if (dpda1Instructions[precursorId].stackUpdate.stackAction == POP_AND_MULTIPLIPUSH) {
			fprintf(f, " { POP_AND_MULTIPLIPUSH, { ");
		}
		else {
			printf("ERROR: no support model\r\n.");
			fclose(f);
			exit(0);
		}

		for (int rhsVariantIndex = 0; rhsVariantIndex < MAX_RHSCONTEINER_COUNT_IN_PDA; ++rhsVariantIndex) {
			char* part_buffer_ = (char*)part_buffer;
			part_buffer[0] = '\0';
			fprintf(f, "{");
			bool printSeparator = false;
			for (int rhsElementIndex = MAX_RTOKEN_COUNT - 1; rhsElementIndex > -1; --rhsElementIndex) {
				if (dpda1Instructions[precursorId].stackUpdate.stackAddon[rhsVariantIndex][rhsElementIndex] == EMPTY_TOKEN_LEXEM_ID)
					continue;

				if (printSeparator) {
					part_buffer_ += sprintf(part_buffer_, ",");
				}

				printSeparator = true;

				part_buffer_ += sprintf(part_buffer_, " 0x%02X", dpda1Instructions[precursorId].stackUpdate.stackAddon[rhsVariantIndex][rhsElementIndex]);
			}
			if (useShortTable) {
				if (rhsVariantIndex < MAX_RHSCONTEINER_COUNT_IN_PDA - 1)
					fprintf(f, "%-59s }, ", part_buffer);
				else
					fprintf(f, "%-59s } ", part_buffer);
			}
			else {
				if (printSeparator) {
					part_buffer_ += sprintf(part_buffer_, " /* reverse sequence of sequence:");
					//printSeparator = false;
					for (int rhsElementIndex = 0; rhsElementIndex < MAX_RTOKEN_COUNT - 1 && dpda1Instructions[precursorId].stackUpdate.stackAddon[rhsVariantIndex][rhsElementIndex] != EMPTY_TOKEN_LEXEM_ID; ++rhsElementIndex) {
						//if (printSeparator) {
						//	part_buffer_ += sprintf(part_buffer_, " ");
						//}
						//
						//printSeparator = true;

						std::string lexemStr("");
						if (getLexemStr(dpda1Instructions[precursorId].stackUpdate.stackAddon[rhsVariantIndex][rhsElementIndex], lexemStr)) {
							part_buffer_ += sprintf(part_buffer_, " %s", lexemStr.c_str());
						}
						else {
							part_buffer_ += sprintf(part_buffer_, " 0x%02X", dpda1Instructions[precursorId].stackUpdate.stackAddon[rhsVariantIndex][rhsElementIndex]);
							//part_buffer_ += sprintf(part_buffer_, ",x%02X)->{(q,%s)}*/", topStackCode, rhs_buffer);
						}

						//part_buffer_ += sprintf(part_buffer_, "%s", dpda1Instructions[precursorId].stackUpdate.stackAddon[rhsVariantIndex][rhsElementIndex]);
						//
						//if (rhsElementIndex < MAX_RTOKEN_COUNT - 1) {
						//	part_buffer_ += sprintf(part_buffer_, " ");
						//}
					}
					part_buffer_ += sprintf(part_buffer_, " */ ");
				}
				else {
					part_buffer_ += sprintf(part_buffer_, " /* empty sequence */ ");
				}
				if (rhsVariantIndex < MAX_RHSCONTEINER_COUNT_IN_PDA - 1)
					fprintf(f, "%-182s }, ", part_buffer);
				else
					fprintf(f, "%-182s } ", part_buffer);
			}
		}

		fprintf(f, "} } },\n");

	}
	printf("\r\n");
	fprintf(f, "};\n");

	fprintf(f, "\n");

	if (false && "dead_state"[0] != -1) {
		for (int stateIndex = 0; stateIndex < LL2_MAX_STATES; ++stateIndex) {
			fprintf(f, "#define Q%03d %d\n", stateIndex, stateIndex);
		}
	}

	fprintf(f, "%s %s = {\n", CONST_STRING(PrecursorIds), CONST_STRING(DPDA1_TABLE_NAME) CONST_STRING(DPDA1ProgramByPrecursors));
	if (useShortTable)
		fprintf(f, "//         ");
	else
		fprintf(f, "//                                                         ");

	printf("\n");
	std::string lexemStr("");
	for (int topStackCode = 0; topStackCode < LL2_MAX_STATES; ++topStackCode) {
		printf("\r%d                      ", topStackCode);
		if (useShortTable)
			fprintf(f, "  0x%02X ", topStackCode);
		else {
			if (topStackCode == EMPTY_TOKEN_LEXEM_ID) {
				sprintf(part_buffer, "  \"\" ");
				//fprintf(f, "  %s ", lexemStr.c_str());
			}
			else if (topStackCode && getLexemStr(topStackCode, lexemStr)) {
				sprintf(part_buffer, "  %s ", lexemStr.c_str());
				//fprintf(f, "  %s ", lexemStr.c_str());
			}
			else {
				sprintf(part_buffer, " 0x%02X ", topStackCode);
				//fprintf(f, " \\x%02X ", topStackCode);
			}
			fprintf(f, " %-139s ", part_buffer);
		}
	}

	printf("\n");
	fprintf(f, "\n");
	//unsigned int precursorId = 0;
	for (int firstMarkCode = 0; firstMarkCode < LL2_SYMBOL_NUMBER; ++firstMarkCode) {
		for (int rhsVariantIndex = 0; rhsVariantIndex < MAX_RHSCONTEINER_COUNT && !(rhsVariantIndex && useShortTable); ++rhsVariantIndex) {
			printf("\r%d                      ", firstMarkCode);		
			std::string lexemStr("");
			if (useShortTable) {
				fprintf(f, "/* 0x%02X */ { ", firstMarkCode);
			}
			else {
				if (firstMarkCode == EMPTY_TOKEN_LEXEM_ID) {
					if (rhsVariantIndex)
						sprintf(part_buffer, "// \"\"");
					else
						sprintf(part_buffer, "/* \"\"");
				}
				else if (getLexemStr(firstMarkCode, lexemStr)) {
					if (rhsVariantIndex)
						sprintf(part_buffer, "// %s", lexemStr.c_str());
					else
						sprintf(part_buffer, "/* %s", lexemStr.c_str());
				}
				else {
					if (rhsVariantIndex)
						sprintf(part_buffer, "// 0x%02X", firstMarkCode);
					else
						sprintf(part_buffer, "/* 0x%02X", firstMarkCode);
				}
				if (rhsVariantIndex)
					fprintf(f, "%-50s (v%1d)   | ", part_buffer, rhsVariantIndex);
				else {
					//if (useShortTable)
					//	fprintf(f, "%-50s */ { ", part_buffer);
					//else	
					fprintf(f, "%-50s (v%1d)*/ { ", part_buffer, rhsVariantIndex);
				}
			}

			for (int topStackCode = 0; topStackCode < LL2_MAX_STATES; ++topStackCode) {
				if (//dpda1Program[firstMarkCode][topStackCode].tapeAction == NO_SCROLL &&
					dpda1Program[firstMarkCode][topStackCode].stackUpdate.stackAction == POP_AND_MULTIPLIPUSH) { // no cond
					if (useShortTable)
						fprintf(f, " %3d ", precursorIds[firstMarkCode][topStackCode]);
					else {
						char* part_buffer_ = (char*)part_buffer;
						part_buffer[0] = '\0';
						char* rhs_buffer_ = (char*)rhs_buffer;
						rhs_buffer[0] = '\0';
						std::string lexemStr("");
						//...
						for (int rhsElementIndex = 0; rhsElementIndex < MAX_RTOKEN_COUNT && dpda1Program[firstMarkCode][topStackCode].stackUpdate.stackAddon[rhsVariantIndex][rhsElementIndex] != EMPTY_TOKEN_LEXEM_ID; ++rhsElementIndex) {
							//if (rhsElementIndex) {
							//	rhs_buffer_ += sprintf(rhs_buffer_, " ");
							//}

							unsigned char rhsElementId = dpda1Program[firstMarkCode][topStackCode].stackUpdate.stackAddon[rhsVariantIndex][rhsElementIndex];

							//if (rhsElementId == EMPTY_TOKEN_LEXEM_ID) {
							//	rhs_buffer_ += sprintf(rhs_buffer_, "\"\"");
							//} else 
							if (getLexemStr(rhsElementId, lexemStr)) {
								rhs_buffer_ += sprintf(rhs_buffer_, "%s", lexemStr.c_str());
							}
							else if (rhsElementId >= IDENTIFIER_LEXEM_MIN_ID && rhsElementId <= IDENTIFIER_LEXEM_MAX_ID) {
								rhs_buffer_ += sprintf(rhs_buffer_, "%s", IDENTIFIER_METATERMINAL_LEXEM_STR);
							}
							else if (rhsElementId >= IDENTIFIER_LEXEM_MIN_ID && rhsElementId <= IDENTIFIER_LEXEM_MAX_ID) {
								rhs_buffer_ += sprintf(rhs_buffer_, "%s", UNSIGNED_VALUE_METATERMINAL_LEXEM_STR);
							}
							else {
								rhs_buffer_ += sprintf(rhs_buffer_, "x%02X", rhsElementId);
							}

							if (rhsElementIndex < MAX_RTOKEN_COUNT && dpda1Program[firstMarkCode][topStackCode].stackUpdate.stackAddon[rhsVariantIndex][rhsElementIndex] != EMPTY_TOKEN_LEXEM_ID) {
								rhs_buffer_ += sprintf(rhs_buffer_, " ");
							}
						}

						if (dpda1Program[firstMarkCode][topStackCode].tapeAction == SCROLL_TO_RIGHT) {
							//fprintf(f, "/*D(q,\"\",%s)->{(q,", lexemStr.c_str());
							if (firstMarkCode == EMPTY_TOKEN_LEXEM_ID) {
								part_buffer_ += sprintf(part_buffer_, "/*D(q,\"\"");
							}
							else if (getLexemStr(firstMarkCode, lexemStr)) {
								part_buffer_ += sprintf(part_buffer_, "/*D(q,%s", lexemStr.c_str());
							}
							else {
								part_buffer_ += sprintf(part_buffer_, "/*D(q,x%02X", firstMarkCode);
							}
						}
						else {
							part_buffer_ += sprintf(part_buffer_, "/*D(q,\"\"");
						}

						if (topStackCode == EMPTY_TOKEN_LEXEM_ID) {
							if(rhs_buffer[0] == '\0')
								part_buffer_ += sprintf(part_buffer_, ",\"\")->{(q,\"\")}*/");
							else
								part_buffer_ += sprintf(part_buffer_, ",\"\")->{(q,%s)}*/", rhs_buffer);
						}
						else if (getLexemStr(topStackCode, lexemStr)) {
							if(rhs_buffer[0] == '\0')
								part_buffer_ += sprintf(part_buffer_, ",%s)->{(q,\"\")}*/", lexemStr.c_str());
							else
								part_buffer_ += sprintf(part_buffer_, ",%s)->{(q,%s)}*/", lexemStr.c_str(), rhs_buffer);
						}
						else {
							if(rhs_buffer[0] == '\0')
								part_buffer_ += sprintf(part_buffer_, ",0x%02X)->{(q,\"\")}*/", topStackCode);
							else
								part_buffer_ += sprintf(part_buffer_, ",0x%02X)->{(q,%s)}*/", topStackCode, rhs_buffer);
						}

						//if (useShortTable)
						//	fprintf(f, "%-50s */ { ", part_buffer);
						//else
						fprintf(f, "%-135s %3d", part_buffer, precursorIds[firstMarkCode][topStackCode]);
					}

					//for (int rhsElementIndex = 0; rhsElementIndex < MAX_RTOKEN_COUNT && dpda1Program[firstMarkCode][topStackCode].stackUpdate.stackAddon[rhsElementIndex][0] != '\0'; ++rhsElementIndex)
					//	dpda1Program[firstMarkCode][topStackCode].stackUpdate.stackAddon[rhsElementIndex];
					//	unsigned int stackAddon[MAX_RHSCONTEINER_COUNT_IN_PDA][MAX_RTOKEN_COUNT];

				}
				else if (dpda1Program[firstMarkCode][topStackCode].tapeAction == SCROLL_TO_RIGHT // REMOVE !
					&& dpda1Program[firstMarkCode][topStackCode].stackUpdate.stackAction == POP_AND_MULTIPLIPUSH/*!*/) { // accept
					if (firstMarkCode == topStackCode) {
						if (firstMarkCode == EMPTY_TOKEN_LEXEM_ID) {
							fprintf(f, "/*D(q,\"\",S)->{(q,\"\")}*/");
						}
						if (getLexemStr(firstMarkCode, lexemStr)) {
							fprintf(f, "/*D(q,%s,S)->{(q,%s)}*/", lexemStr.c_str(), lexemStr.c_str());
						}
						else {
							fprintf(f, "/*D(q,\\x%02X,S)->{(q,\\x%02X)}*/", firstMarkCode, topStackCode);
						}
					}
					else {
						printf("ERROR: no support model\r\n.");
						fclose(f);
						exit(0);
					}
				}
				else {
					printf("Error.\r\n");
					fclose(f);
					exit(0);
				}
				if (topStackCode < LL2_MAX_STATES - 1) {
					if (rhsVariantIndex)
						fprintf(f, "| ");
					else
						fprintf(f, ", ");
				}
			}
			if (rhsVariantIndex)
				fprintf(f, " | \n");
			else
				fprintf(f, " }%s\n", firstMarkCode < LL2_SYMBOL_NUMBER - 1 ? "," : "");
		
		}

	}
	printf("\n");
	fprintf(f, "};\n");

	fprintf(f, "\n");
 
	fprintf(f, "%s %s = {\n", CONST_STRING(DPDA1IndexingForSecondElement), CONST_STRING(DPDA1_TABLE_NAME) CONST_STRING(DPDA1IndexingForSecondElement));
	for (int secondMarkCode = 0; secondMarkCode < LL2_SYMBOL_NUMBER; ++secondMarkCode) {
		fprintf(f, "{ ");
		for (int topStackCode = 0; topStackCode < LL2_MAX_STATES; ++topStackCode) {
			if (topStackCode)
				fprintf(f, ", ");
			fprintf(f, "%1d", dpda1IndexingForSecondElement[secondMarkCode][topStackCode]);
		}
		fprintf(f, " },\n");
	}
//	for (unsigned int precursorId = 0; precursorId < LL2_PRECURSOR_COUNT; ++precursorId){
//	for (int finitStatesIndex = 0; finitStatesIndex < finit_states_count; ++finitStatesIndex) {
//		fprintf(f, "Q%03d%s", finit_states[finitStatesIndex], finitStatesIndex + 1 == finit_states_count ? " " : ", ");
//	}
	fprintf(f, "};\n");

	fclose(f);
}

// used
// tape scroll
void buildAcceptTapeElement__DPDA1forLL2(Grammar& grammar, DPDA1Program& dpda1Program, DPDA1Instructions& dpda1Instructions, PrecursorIds& precursorIds, DPDA1IndexingForSecondElement& dpda1IndexingForSecondElement) {
    // ALL IDENT <-to-> ALL IDENT
	// ALL UNSIGNED VALUE <-to-> ALL UNSIGNED VALUE

	// ALL CODE FOR IDENT AND UNSIGNED VALUE
	// MIN_TERMIN
	// All Symbol -> only non-terminal
	// char emptyStringCode = getLexemId((char*)"");

#ifdef NO_ACCEPTANCE_BEHAVIOR
	return;
#endif

	unsigned char acceptPrecursorId = 
#ifdef DEAD_STATE_ID // regardless of the value DEAD_STATE_ID will be encoded as 0				
		1 +
#endif				
		0;

	unsigned char tapeAndTopStackCode = 0; do {

		if (tapeAndTopStackCode >= NONTERMINAL_LEXEM_MIN_ID && tapeAndTopStackCode <= NONTERMINAL_LEXEM_MAX_ID
			//|| tapeAndTopStackCode == DEAD_STATE_ID
			//|| tapeAndTopStackCode == MARKER_OF_STRUCTURE_ID
			//|| tapeAndTopStackCode == FREE_STATE_ID
			)
			continue;


		auto & currDPDA1Element = dpda1Program[tapeAndTopStackCode][tapeAndTopStackCode];

			// not init or not to dead state
			if (//dpda1Program[ROW_INDEX][columnIndexSelector].tapeAction != -1
//				currDPDA1Element.tapeAction != SCROLL_TO_RIGHT
//				||
//				currDPDA1Element.stackUpdate.stackAction != POP_AND_MULTIPLIPUSH
//				||
//				currDPDA1Element.rhsVariantAddonIndexMask != 0
//				||
//				currDPDA1Element.stackUpdate.stackAddon[0][0] != EMPTY_TOKEN_LEXEM_ID
//				&& (
//					currDPDA1Element.stackUpdate.stackAddon[0][0] != DEAD_STATE_ID
//					||
//					currDPDA1Element.stackUpdate.stackAddon[0][1] != EMPTY_TOKEN_LEXEM_ID
//					)


				currDPDA1Element.stackUpdate.stackAction != POP_AND_MULTIPLIPUSH ||
				currDPDA1Element.rhsVariantAddonIndexMask != 0 ||
				(currDPDA1Element.tapeAction != NO_SCROLL ||
					currDPDA1Element.stackUpdate.stackAddon[0][0] != DEAD_STATE_ID ||
					currDPDA1Element.stackUpdate.stackAddon[0][1] != EMPTY_TOKEN_LEXEM_ID)
				&&
				(currDPDA1Element.tapeAction != SCROLL_TO_RIGHT ||
					currDPDA1Element.stackUpdate.stackAddon[0][0] != EMPTY_TOKEN_LEXEM_ID)
			){
				printf("ERROR: no support model\r\n.");
				exit(0);
			}

			//tape
			currDPDA1Element.tapeAction = SCROLL_TO_RIGHT; // SHIFT

			// stack
			// dpda1Program[tapeAndTopStackCode][tapeAndTopStackCode].stackUpdate.stackAction = POP_AND_MULTIPLIPUSH;
			// dpda1Program[tapeAndTopStackCode][tapeAndTopStackCode].rhsVariantAddonIndexMask = 0; // not useed for accept state (? dpda1IndexingForSecondElement; ==> ignore => mask 0)
			for (unsigned int rTokekIndex = 0; rTokekIndex < MAX_RTOKEN_COUNT; ++rTokekIndex) { // not useed for dead state
				currDPDA1Element.stackUpdate.stackAddon[0/*rhsVariantAddonIndex*/][rTokekIndex] = EMPTY_TOKEN_LEXEM_ID;
			}
	
			precursorIds[tapeAndTopStackCode][tapeAndTopStackCode] = acceptPrecursorId;

	} while (++tapeAndTopStackCode);

////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////

	bool stateIsNotDefault = false;
	bool stateIsTwiñeChanged = false;
	// not init or not to dead state
	if (//dpda1Program[ROW_INDEX][columnIndexSelector].tapeAction != -1
		dpda1Instructions[acceptPrecursorId].tapeAction != NO_SCROLL
		||
		dpda1Instructions[acceptPrecursorId].stackUpdate.stackAction != POP_AND_MULTIPLIPUSH
		||
		dpda1Instructions[acceptPrecursorId].rhsVariantAddonIndexMask != 0
		||
		dpda1Instructions[acceptPrecursorId].stackUpdate.stackAddon[0][0] != DEAD_STATE_ID
		||
		dpda1Instructions[acceptPrecursorId].stackUpdate.stackAddon[0][1] != EMPTY_TOKEN_LEXEM_ID
		) { // ?
		//printf("ERROR: no support model\r\n.");
		stateIsNotDefault = true;
		//exit(0);
	}

	auto& currDPDA1Instruction = dpda1Instructions[acceptPrecursorId];

	// not init or not to dead state
	if (currDPDA1Instruction.stackUpdate.stackAction != POP_AND_MULTIPLIPUSH ||
		currDPDA1Instruction.rhsVariantAddonIndexMask != 0 ||
		(currDPDA1Instruction.tapeAction != NO_SCROLL ||
			currDPDA1Instruction.stackUpdate.stackAddon[0][0] != DEAD_STATE_ID ||
			currDPDA1Instruction.stackUpdate.stackAddon[0][1] != EMPTY_TOKEN_LEXEM_ID)
		&&
		(currDPDA1Instruction.tapeAction != SCROLL_TO_RIGHT ||
			currDPDA1Instruction.stackUpdate.stackAddon[0][0] != EMPTY_TOKEN_LEXEM_ID)
		) {
		printf("ERROR: no set accep instruction.\r\n.");
		exit(0);
	}

	//tape
	currDPDA1Instruction.tapeAction = SCROLL_TO_RIGHT; // SHIFT

	// stack
	// dpda1Program[tapeAndTopStackCode][tapeAndTopStackCode].stackUpdate.stackAction = POP_AND_MULTIPLIPUSH;
	// dpda1Program[tapeAndTopStackCode][tapeAndTopStackCode].rhsVariantAddonIndexMask = 0; // not useed for accept state (? dpda1IndexingForSecondElement; ==> ignore => mask 0)
	for (unsigned int rTokekIndex = 0; rTokekIndex < MAX_RTOKEN_COUNT; ++rTokekIndex) { // not useed for dead state
		currDPDA1Instruction.stackUpdate.stackAddon[0/*rhsVariantAddonIndex => mask 0*/][rTokekIndex] = EMPTY_TOKEN_LEXEM_ID;
	}

}

void buildDPDA1forLL2(Grammar& grammar, DPDA1Program& dpda1Program, DPDA1Instructions& dpda1Instructions, PrecursorIds& precursorIds, DPDA1IndexingForSecondElement& dpda1IndexingForSecondElement, bool useShortTable = false) {
	// init codes
	terminalAndNonTerminalIdsInit(grammar/*, lexemInfoTable*//*, int lastNonUsedid ! */);

	//for (const auto& [key, value] : terminalAndNonTerminalLexemIds) { // Using Structured Bindings (C++17 and later)
	//	std::cout << "Key: \"" << key << "\", Value: " << value << std::endl;
	//}
	for (const auto& pair : terminalAndNonTerminalLexemIds) { // Using a Range-Based For Loop (C++11 and later)
		std::cout << "Key: \"" << pair.first << "\", Value: " << (unsigned int)pair.second << std::endl;
	}

	buildTerminalAndNonTerminalLexemStrs__copy();

	// dead state
	//buildDeadState__DPDA1forLL2(grammar, dpda1Program, dpda1IndexingForSecondElement); // TERMINAL INIT AFTER SCAN SOURCE
	//return;
	// set 255 (-1) // to dead state
	setAllStatesToDeadStateAndInitIndexing(grammar, dpda1Program, dpda1Instructions, precursorIds, dpda1IndexingForSecondElement);

	// rules part
	buildRulePartForDPDA1forLL2(grammar, dpda1Program, dpda1Instructions, precursorIds, dpda1IndexingForSecondElement);

	// accept part
	buildAcceptTapeElement__DPDA1forLL2(grammar, dpda1Program, dpda1Instructions, precursorIds, dpda1IndexingForSecondElement);

	// dpda1IndexingForSecondElement[rowIndex][columnIndex]; // -1

	// MIN_TERMIN
	// All Symbol

	print_pda_by_transition_table_to_file(dpda1Program, dpda1Instructions, precursorIds, dpda1IndexingForSecondElement, useShortTable);
}

unsigned char data_in_buffer[MAX_WORD_COUNT] = { EMPTY_TOKEN_LEXEM_ID };
void buildInputTapeByLexemTable(struct LexemInfo* lexemInfoTable, unsigned char * data_in_buffer) {
	for (unsigned long long int index = 0; lexemInfoTable[index].lexemStr[0] != '\0'; ++index) {
		//index, 
		//lexemInfoTable[index].lexemStr,
		//lexemInfoTable[index].lexemId,
		//lexemInfoTable[index].tokenType,
		//lexemInfoTable[index].ifvalue,
		//lexemInfoTable[index].row,
		//lexemInfoTable[index].col;
		if (lexemInfoTable[index].lexemId <= (unsigned char)~0)
			*data_in_buffer++ = lexemInfoTable[index].lexemId;
		else {
			printf("Lexem id error.\r\n");
			exit(0);
		}
	}
	data_in_buffer = EMPTY_TOKEN_LEXEM_ID;
}
unsigned char data_out_buffer[MAX_WORD_COUNT] = { EMPTY_TOKEN_LEXEM_ID };

void buildStructuredLexemInfoTable(struct LexemInfo* lexemInfoTable, unsigned char* tape, struct LexemInfo* structuredLexemInfoTable) {
	printf("Warning: add EMPTY_TOKEN_LEXEM_ID to end of out tape.");
	
	if (!lexemInfoTable || !structuredLexemInfoTable)
		return; // !

	for (; *tape != EMPTY_TOKEN_LEXEM_ID; ++tape, ++structuredLexemInfoTable) { // EMPTY_TOKEN_LEXEM_ID
		if (*tape == lexemInfoTable->lexemId) {
			//index, 
			//lexemInfoTable[index].lexemStr,
			//lexemInfoTable[index].lexemId,
			//lexemInfoTable[index].tokenType,
			//lexemInfoTable[index].ifvalue,
			//lexemInfoTable[index].row,
			//lexemInfoTable[index].col;

			*structuredLexemInfoTable = *lexemInfoTable; //  default assign constr
#if 0
			strncpy(structuredLexemInfoTable->lexemStr, lexemInfoTable->lexemStr, MAX_LEXEM_SIZE);
			structuredLexemInfoTable->lexemId = lexemInfoTable->lexemId; // *tape
			structuredLexemInfoTable->tokenType = lexemInfoTable->tokenType;
			structuredLexemInfoTable->ifvalue = lexemInfoTable->ifvalue;
			structuredLexemInfoTable->row = lexemInfoTable->row;
			structuredLexemInfoTable->col = lexemInfoTable->col;
			++lexemInfoTable;
#endif
			//++structuredLexemInfoTable;

		}
		else {
			std::string lexemStr;
			bool lexemHasString = getLexemStr(*tape, lexemStr);
			if (lexemHasString)
				strncpy(structuredLexemInfoTable->lexemStr, lexemInfoTable->lexemStr, MAX_LEXEM_SIZE);
			else
				structuredLexemInfoTable->lexemStr[0] = '\0';
			structuredLexemInfoTable->lexemId = *tape;
			structuredLexemInfoTable->tokenType = NONTERMINAL_LEXEME_TYPE;// lexemInfoTable->tokenType; // NONTERMINAL
			structuredLexemInfoTable->ifvalue = 0;
			structuredLexemInfoTable->row = lexemInfoTable[1].row; // position of next terminal
			structuredLexemInfoTable->col = lexemInfoTable[1].col; // position of next terminal
			//++structuredLexemInfoTable;
		}
	}

	structuredLexemInfoTable->lexemStr[0] = '\0';
	structuredLexemInfoTable->lexemId = EMPTY_TOKEN_LEXEM_ID;// *tape;
	structuredLexemInfoTable->tokenType = NONTERMINAL_LEXEME_TYPE;
	structuredLexemInfoTable->ifvalue = 0;
	structuredLexemInfoTable->row = ~0;
	structuredLexemInfoTable->col = ~0;
	++structuredLexemInfoTable;
	
//	for (unsigned long long int index = 0; lexemInfoTable[index].lexemStr[0] != '\0'; ++index) {
//		//index, 
//		//lexemInfoTable[index].lexemStr,
//		//lexemInfoTable[index].lexemId,
//		//lexemInfoTable[index].tokenType,
//		//lexemInfoTable[index].ifvalue,
//		//lexemInfoTable[index].row,
//		//lexemInfoTable[index].col;
//		if (lexemInfoTable[index].lexemId <= (unsigned char)~0)
//			*data_in_buffer++ = lexemInfoTable[index].lexemId;
//		else {
//			printf("Lexem id error.\r\n");
//			exit(0);
//		}
//	}
}

//unsigned char data_out_buffer[MAX_WORD_COUNT] = { '\0' }; // struct LexemInfo* syntaxLL2(Grammar* grammar, char * ruleName, struct LexemInfo* lexemInfoTable, ASTNode** baseASTNode, struct LexemInfo** badLexemInfo)
bool buildASTFByOutputTape(struct LexemInfo* structuredLexemInfoTable, ASTNode** baseASTNode) {
	if (structuredLexemInfoTable == nullptr || baseASTNode == nullptr) {
		return false;
	}

	ASTNode* stackOfASTParentNode[MAX_RULES] = { nullptr };
	ASTNode** stackOfASTParentNodeAboveTop = stackOfASTParentNode;

	for (*baseASTNode = nullptr; structuredLexemInfoTable; ++structuredLexemInfoTable) {
		if (structuredLexemInfoTable->lexemId >= KEYWORD_LEXEM_MIN_ID && structuredLexemInfoTable->lexemId <= LITERAL_LEXEM_MAX_ID) {
			ASTNode* node = new(std::nothrow) ASTNode(structuredLexemInfoTable->lexemStr, true);
			if (!node || !stackOfASTParentNodeAboveTop[-1]) {
				printf("Memory error.\n");
				if (*baseASTNode) {
					delete* baseASTNode;
				}
				return false;
			}	
			stackOfASTParentNodeAboveTop[-1]->childrens.push_back(node);
		}	
		else if (structuredLexemInfoTable->lexemId >= NONTERMINAL_LEXEM_MIN_ID && structuredLexemInfoTable->lexemId <= NONTERMINAL_LEXEM_MAX_ID) {
			ASTNode* node = new(std::nothrow) ASTNode(structuredLexemInfoTable->lexemStr, false);
			if (!node) {
				printf("Memory error.\n");
				if (*baseASTNode) {
					delete* baseASTNode;
				}
				return false;
			}
			if (stackOfASTParentNodeAboveTop > stackOfASTParentNode) {
				if (stackOfASTParentNodeAboveTop[-1]) {
					stackOfASTParentNodeAboveTop[-1]->childrens.push_back(node);
				}
				else {
					if (baseASTNode) {
						delete* baseASTNode;
					}
					return false;
				}
			}
			else if (*baseASTNode == nullptr) *baseASTNode = node; // if (*baseASTNode == nullptr) *baseASTNode = node; // !
			*stackOfASTParentNodeAboveTop++ = node;
		}
		else if (structuredLexemInfoTable->lexemId == MARKER_OF_STRUCTURE_ID) {
			--stackOfASTParentNodeAboveTop;
		}
		else {
			if (baseASTNode) {
				delete* baseASTNode;
			}
			printf("Error code of structured tape.\n");
			return false;
		}
	}

	return true;
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

#if 0
//DPDA1Instructions dpda1Instructions;
//PrecursorIds precursorIds;
//DPDA1IndexingForSecondElement dpdaIndexingForSecondElement;

#include CONST_STRING(DPDA1_FILE_NAME) // #include "fileName.h" 
struct LexemInfo structuredLexemInfoTable[MAX_WORD_COUNT];
int syntaxAnalyzeUsePDA(struct LexemInfo* lexemInfoTable, Grammar* grammar, char syntaxlAnalyzeMode/* not used */, char* astFileName, char* errorMessagesPtrToLastBytePtr, bool viewAST) {

	//const char* fname = CONST_STRING(DPDA1_TABLE_NAME.h);

	//struct LexemInfo* lexemInfoTable;
#if 0
	dpda1.data_in = data_in_buffer; // ?
	dpda1.data_out = data_out_buffer; // ?
	dpda1.dpdaProgram = &dpdaProgram; // ?
	dpda1.dpda1Instructions = &dpda1Instructions; // ?
	dpda1.precursorIds = &precursorIds; // ?
	dpda1.dpdaIndexingForSecondElement = &dpdaIndexingForSecondElement; // ?
	dpda1.run = runner3; // ?
	dpda1.stack_above_top = dpda1.stack + SAVE_OFFSET; // ?
#endif
	//buildDPDA1forLL2(grammar, *dpda1.dpdaProgram, *dpda1.dpda1Instructions, *dpda1.precursorIds, *dpda1.dpdaIndexingForSecondElement, lexemesInfoTable);


	// init +/-

	// convert
	//void buildDataInFromLexemTable(struct LexemInfo* lexemInfoTable, unsigned char* data_in_buffer);
	
	struct ASTNode* astRoot = NULL;
	struct LexemInfo* unexpectedLexemfailedTerminal = NULL; // TODO: ...
	buildInputTapeByLexemTable(lexemesInfoTable, data_in_buffer);
	static char result = tryToAcceptDPDA(
		&BY_DPDA1_TABLE_NAME(DPDA1ProgramByPrecursors),
		&BY_DPDA1_TABLE_NAME(DPDA1ReverseInstructions),
		&BY_DPDA1_TABLE_NAME(DPDA1IndexingForSecondElement),
		PROGRAM_RULE_ID,
		data_in_buffer,
		data_out_buffer); // *dpda1.stack_above_top++ = PROGRAM_RULE_ID;
	buildStructuredLexemInfoTable(lexemesInfoTable, data_out_buffer, structuredLexemInfoTable);
	if (buildASTFByOutputTape(structuredLexemInfoTable, &astRoot)) {
		printf("Error of AST biuild.\n");
		exit(0);
	}


	//struct LexemInfo* lastLexemInfo = syntaxLL2(grammar, grammar->start_symbol, lexemInfoTable, &astRoot, &unexpectedLexemfailedTerminal);

	if (dpda1.data_in == EMPTY_TOKEN_LEXEM_ID) {
		if (viewAST) {
			printAST(lexemInfoTable, astRoot);
		}
		std::ofstream astOFStream(astFileName, std::ofstream::out);
		printASTToFile(lexemInfoTable, astRoot, astOFStream);
		astOFStream.close();
		return SUCCESS_STATE;
	}
	else {
		/* struct LexemInfo* */unexpectedLexemfailedTerminal = lexemesInfoTable + (dpda1.data_in - data_in_buffer); // TODO: ...
		printf("Parse failed.\r\n");
		printf("    (The predicted terminal does not match the expected one.\r\n    Unexpected terminal \"%s\" on line %lld at position %lld.)\r\n", unexpectedLexemfailedTerminal->lexemStr, unexpectedLexemfailedTerminal->row, unexpectedLexemfailedTerminal->col);
		errorMessagesPtrToLastBytePtr += sprintf(errorMessagesPtrToLastBytePtr, "Parse failed.\r\n");
		errorMessagesPtrToLastBytePtr += snprintf(errorMessagesPtrToLastBytePtr, MAX_LEXEM_SIZE + 128 + strlen("    (The predicted terminal does not match the expected one.\r\n    Unexpected terminal \"#\" on line # at position #.)\r\n"), "    (The predicted terminal does not match the expected one.\r\n    Unexpected terminal \"%s\" on line %lld at position %lld.)\r\n", unexpectedLexemfailedTerminal->lexemStr, unexpectedLexemfailedTerminal->row, unexpectedLexemfailedTerminal->col);
		//exit(0);
		return ~SUCCESS_STATE;
	}


}

//unsigned char errorMessagesPtrToLastBytePtr[8 * 1024 * 1024] = { '\0' };
//struct LexemInfo structuredLexemInfoTable[MAX_WORD_COUNT];
int main(int argc, char* argv[]) {
	char* text;
	char fileName[128] = DEFAULT_INPUT_FILE;
	char choice[2] = { fileName[0], fileName[1] };
	system("CLS");
	std::cout << "Enter file name(Enter \"" << choice[0] << "\" to use default \"" DEFAULT_INPUT_FILE "\"):";
	std::cin >> fileName;
	if (fileName[0] == choice[0] && fileName[1] == '\0') {
		fileName[1] = choice[1];
	}
	size_t sourceSize = loadSource(&text, fileName);
	if (!sourceSize) {
#ifdef RERUN_MODE
		(void)getchar();
		printf("\nEnter 'y' to rerun program action(to pass action enter other key): ");
		char valueByGetChar = getchar();
		if (valueByGetChar == 'y' || valueByGetChar == 'Y') {
			system((std::string("\"") + argv[0] + "\"").c_str());
		}
		return 0;
#else
		printf("Press Enter to exit . . .");
		(void)getchar();
		return 0;
#endif
	}
	printf("Original source:\r\n");
	printf("-------------------------------------------------------------------\r\n");
	printf("%s\r\n", text);
	printf("-------------------------------------------------------------------\r\n\r\n");
	int commentRemoverResult = commentRemover(text, COMMENT_BEGIN_STR, COMMENT_END_STR);
	if (commentRemoverResult) {
		printf("Comment remover return %d\r\n", commentRemoverResult);
		printf("Press Enter to exit . . .");
		(void)getchar();
		return 0;
	}
	printf("Source after comment removing:\r\n");
	printf("-------------------------------------------------------------------\r\n");
	printf("%s\r\n", text);
	printf("-------------------------------------------------------------------\r\n\r\n");

	struct LexemInfo ifBadLexemeInfo = tokenize(text, &lastLexemInfoInTable, identifierIdsTable, lexicalAnalyze);

	if (ifBadLexemeInfo.tokenType == UNEXPEXTED_LEXEME_TYPE) {
		UNEXPEXTED_LEXEME_TYPE;
		ifBadLexemeInfo.tokenType;
		printf("Lexical analysis detected unexpected lexeme\r\n");
		printLexemes(&ifBadLexemeInfo, 1);
	}
	else {
		printLexemes(lexemesInfoTable, 0);

		if (0/*SUCCESS*/ != syntaxAnalyzeUsePDA(lexemesInfoTable, &grammar, !"char syntaxlAnalyzeMode/* not used */", (char*)"astFileName"".ast", (char*)errorMessagesPtrToLastBytePtr, true)) {		
			// printf("Syntax analyze error\n");
		}
			
		return 0;
#if 0
		errorMessagesPtrToLastBytePtr[0] = '\0';
		unsigned char* errorMessagesPtrToLastBytePtr_ = errorMessagesPtrToLastBytePtr;
		if (SUCCESS_STATE != syntaxAnalyze(lexemesInfoTable, &grammar, 0, (char*)AST_OUTPUT_FILE, (char*)&errorMessagesPtrToLastBytePtr, true)) {
			(void)getchar();
			printf("\r\nPress Enter: ");
			(void)getchar();
			system("CLS");
			fflush(stdin);
			fflush(stdout);
			fflush(stderr);
			//(void)getchar();
			printf("No command line arguments are entered, so you are working in interactive mode.\r\n");
			printf("\nEnter 'y' to rerun (to pass action enter other key): ");
			char valueByGetChar = getchar();
			if (valueByGetChar == 'y' || valueByGetChar == 'Y') {
				system("CLS");
				fflush(stdin);
				fflush(stdout);
				fflush(stderr);
				system((std::string("\"") + argv[0] + "\"").c_str());
			}
			else {
				return 0;
			}
		}
#endif
	}

	free(text);

	(void)getchar();
#ifdef RERUN_MODE
	printf("\nEnter 'y' to rerun (to pass action enter other key): ");
	char valueByGetChar = getchar();
	if (valueByGetChar == 'y' || valueByGetChar == 'Y') {
		system((std::string("\"") + argv[0] + "\"").c_str());
	}
#endif

	return 0;
}
#else

DPDA1Program dpda1Program; // REMOVE
DPDA1Instructions dpda1Instructions;
PrecursorIds precursorIds;
DPDA1IndexingForSecondElement dpdaIndexingForSecondElement;

int main(int argc, char* argv[]) {
	//dpda1.data = data; !!!
	//dpda1.data_in = 
	//dpda1.data_out =
//	dpda1.dpdaProgram = &dpdaProgram;
//	dpda1.dpda1ReverseInstructions = &dpda1ReverseInstructions;
//	dpda1.precursorIds = &precursorIds;
//	dpda1.dpdaIndexingForSecondElement = &dpdaIndexingForSecondElement;
//	dpda1.run = runner3; // !
//	dpda1.stack_above_top = dpda1.stack + SAVE_OFFSET; // !

	//*dpda1.stack_above_top++ = getLexemId((char*)"program_rule");
	buildDPDA1forLL2(grammar, dpda1Program, dpda1Instructions/**dpda1.dpda1ReverseInstructions*/, precursorIds, dpdaIndexingForSecondElement/*, true*/);

	(void)getchar();
#ifdef RERUN_MODE
	printf("\nEnter 'y' to rerun (to pass action enter other key): ");
	char valueByGetChar = getchar();
	if (valueByGetChar == 'y' || valueByGetChar == 'Y') {
		system((std::string("\"") + argv[0] + "\"").c_str());
	}
#endif

	return 0;
}
#endif