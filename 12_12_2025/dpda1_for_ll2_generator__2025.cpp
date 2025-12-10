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

#define IDENT_METETERMINAL_LEXEM_STR "ident_terminal"
#define IDENT_METETERMINAL_LEXEM_ID (KEYWORD_LEXEM_MAX_ID + 1)
#define IDENTIFIER_LEXEM_MIN_ID (IDENT_METETERMINAL_LEXEM_ID + 1)
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

#define DEAD_STATE_ID 253
#define	POP_STACK_IN_F_OUT_STATE_ID 254
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
	else {
		ifBadLexemeInfo.tokenType = UNEXPEXTED_LEXEME_TYPE;
	}

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

//void addAnigilateInstruction(/*no args*/) {}
//
//void addAnigilateInstructions(/*no args*/) {}

#include <string>
#include <map>
//#include <utility>
#include <stack>



std::map<std::string, int> terminalAndNonTerminalLexemIds;

int getLexemId(char* str) { // and terminal
	if (terminalAndNonTerminalLexemIds.find(str) == terminalAndNonTerminalLexemIds.end())
		return UNKNOWN_ELEMENT_ID;
	else
		return terminalAndNonTerminalLexemIds[str];
}

//bool getLexemStr(char id, std::string & lexemStr) {
//	for (auto iterator = terminalAndNonTerminalLexemIds.begin(); iterator != terminalAndNonTerminalLexemIds.end(); ++iterator)
//		if (iterator->second == id){
//			lexemStr = iterator->first;
//			return true;
//		}
//
//	return false;
//}

//unsigned long long int getLexemTypeById(char id) {
//
//
//	//#define KEYWORD_LEXEME_TYPE 1
//	//#define IDENTIFIER_LEXEME_TYPE 2 // #define LABEL_LEXEME_TYPE 8
//	//#define VALUE_LEXEME_TYPE 4
//	//#define UNEXPEXTED_LEXEME_TYPE 127
//
//
//	return UNEXPEXTED_LEXEME_TYPE;
//}

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

/*
void addNonTerminalInterpretationInstructions(DPDA1Program* dpdaProgramPtr, Grammar* grammar) {
	if (!dpdaProgramPtr) {
		return;
	}

}
*/

//char getLexemId(char * lexemStr);

// used --> not used
void buildDeadState__DPDA1forLL2__OLD(Grammar& grammar, DPDA1Program& dpda1Program, DPDA1IndexingForSecondElement& dpda1IndexingForSecondElement) {
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






		// + дерево виводу
		
		//char emptyStringCode = getLexemId((char*)"");
		//char deadStateCode = getLexemId((char*)"DEAD_STATE");
		unsigned char tapeCode = 0; do {
#define ROW_INDEX tapeCode
#define COLUMN_INDEX DEAD_STATE_ID			
				// tape
				dpda1Program[ROW_INDEX][COLUMN_INDEX].tapeAction = SCROLL_TO_RIGHT;

				// stack
				dpda1Program[ROW_INDEX][COLUMN_INDEX].stackUpdate.stackAction = NOTHING;
				dpda1Program[ROW_INDEX][COLUMN_INDEX].rhsVariantAddonIndexMask = 0; // not useed for dead state
				for (unsigned int rTokekIndex = 0; rTokekIndex < MAX_RTOKEN_COUNT; ++rTokekIndex) { // not useed for dead state
					dpda1Program[ROW_INDEX][COLUMN_INDEX].stackUpdate.stackAddon[0/*rhsVariantAddonIndex NEW 08.2025*/][rTokekIndex] = EMPTY_TOKEN_LEXEM_ID; // (!)
				}
#undef ROW_INDEX
#undef COLUMN_INDEX
		} while (++tapeCode);
}

/*
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
*/



int nonTerminalIdsInit(Grammar& grammar, int lastNonUsedid) {
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

void terminalAndNonTerminalIdsInitPart2(struct LexemInfo* lexemInfoTable, int lastNonUsedid) {
	if (lexemInfoTable == NULL) {
		printf("Error\n");
		exit(0);
	}

	if (true) {
		printf("Error\n");
		exit(0);
	}

	for (; lexemInfoTable->lexemStr[0] != '\0'; ++lexemInfoTable) {
		if (terminalAndNonTerminalLexemIds.find(lexemInfoTable->lexemStr) == terminalAndNonTerminalLexemIds.end()) {
			terminalAndNonTerminalLexemIds[lexemInfoTable->lexemStr] = lastNonUsedid++;
		}
	}
}

// set FREE_STATE_ID // -1
void dpda1forLL2SetInitStateAndInitIndexing__DELETE(Grammar& grammar, DPDA1Program& dpda1Program, DPDA1IndexingForSecondElement& dpda1IndexingForSecondElement) {
	unsigned char tapeCode = 0; do {
		unsigned char topStackCode = 0; do {
//#define ROW_INDEX tapeCode
//#define COLUMN_INDEX toptapeAndStackCode
			dpda1Program[tapeCode][topStackCode].stackUpdate.stackAction = POP_AND_MULTIPLIPUSH; // no POP prev state (used for detect error) // NEW 08.2025
			dpda1Program[tapeCode][topStackCode].tapeAction = NO_SCROLL; // !
			dpda1Program[tapeCode][topStackCode].rhsVariantAddonIndexMask = 0; // 0 to ignore dpda1IndexingForSecondElement[][] for now
			dpda1Program[tapeCode][topStackCode].stackUpdate.stackAddon[0/*rhsVariantAddonIndex NEW 08.2025*/][0] = FREE_STATE_ID;
			for (unsigned int rTokekIndex = 1; rTokekIndex < MAX_RTOKEN_COUNT; ++rTokekIndex) {
				dpda1Program[tapeCode][topStackCode].stackUpdate.stackAddon[0/*rhsVariantAddonIndex NEW 08.2025*/][rTokekIndex] = EMPTY_TOKEN_LEXEM_ID; // (!)
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
void setAllStatesToDeadStateAndInitIndexing(Grammar& grammar, DPDA1Program& dpda1Program, DPDA1IndexingForSecondElement& dpda1IndexingForSecondElement) {
	unsigned char tapeCode = 0; do {	
		unsigned char topStackCode = 0; do {
//#define ROW_INDEX tapeCode
//#define COLUMN_INDEX topStackCode
			//if (dpda1Program[toptapeAndStackCode][toptapeAndStackCode].tapeAction == FREE_STATE_ID) { // ... // ????
			//	printf("Error: no support model\r\n");
			//	exit(0);
			//}
			dpda1Program[tapeCode][topStackCode].stackUpdate.stackAction = POP_AND_MULTIPLIPUSH; // no POP prev state (used for detect error) // NEW 08.2025
			dpda1Program[tapeCode][topStackCode].tapeAction = SCROLL_TO_RIGHT;
			//08.2025	dpda1Program[toptapeAndStackCode][toptapeAndStackCode].stackUpdate.stackAction = POP; // (2)
			//08.2025	dpda1Program[toptapeAndStackCode][toptapeAndStackCode].stackUpdate.stackAction = PUSH; // (!)
			//08.2025	dpda1Program[toptapeAndStackCode][toptapeAndStackCode].stackUpdate.stackAction = PUSH; // (!)
						//dpda1Program[ROW_INDEX][columnIndex].stackUpdate.stackAddon[rhsVariantAddonIndex][rTokekIndex] = emptyElementCode;
			dpda1Program[tapeCode][topStackCode].rhsVariantAddonIndexMask = 0; // 0 to ignore dpda1IndexingForSecondElement[][] for now
			dpda1Program[tapeCode][topStackCode].stackUpdate.stackAddon[0/*rhsVariantAddonIndex NEW 08.2025*/][0] = DEAD_STATE_ID;
			for (unsigned int rTokekIndex = 1; rTokekIndex < MAX_RTOKEN_COUNT; ++rTokekIndex) {
				dpda1Program[tapeCode][topStackCode].stackUpdate.stackAddon[0/*rhsVariantAddonIndex NEW 08.2025*/][rTokekIndex] = EMPTY_TOKEN_LEXEM_ID; // (!)
			}
				
			// TODO: set 255 to start				
			dpda1IndexingForSecondElement[tapeCode][topStackCode] = ~0;
//#undef ROW_INDEX
//#undef COLUMN_INDEX
		} while (++topStackCode);
	} while (++tapeCode);
}

void terminalAndNonTerminalIdsInit(Grammar& grammar, struct LexemInfo* lexemInfoTable/*, int lastNonUsedid !!!!!!!!!!! */) {
	if (lexemInfoTable == NULL) {
		printf("Error\n");
		exit(0);
	}


	/*

	#define KEYWORD_LEXEM_MIN_ID (UNKNOWN_ELEMENT_ID + 1)
	#define KEYWORD_LEXEM_MAX_ID (KEYWORD_LEXEM_MIN_ID + MAX_KEYWORD_COUNT)

	#define IDENTIFIER_LEXEM_MIN_ID (KEYWORD_LEXEM_MAX_ID + 1)
	#define IDENTIFIER_LEXEM_MAX_ID (IDENTIFIER_LEXEM_MIN_ID + MAX_VARIABLES_COUNT)

	#define LITERAL_LEXEM_MIN_ID (IDENTIFIER_LEXEM_MAX_ID + 1)
	#define LITERAL_LEXEM_MAX_ID (LITERAL_LEXEM_MIN_ID + MAX_LITERAL_COUNT)

	// SPLIT TERMINAL AND NONTERMINAL // V
	//#define TERMINAL_AND_NONTERMINAL_LEXEM_MIN_ID (IDENTIFIER_LEXEM_MAX_ID + 1)
	//#define TERMINAL_AND_NONTERMINAL_LEXEM_MAX_ID (IDENTIFIER_LEXEM_MIN_ID + 190)
	#define NONTERMINAL_LEXEM_MIN_ID (IDENTIFIER_LEXEM_MAX_ID + 1)
	#define NONTERMINAL_LEXEM_MAX_ID 252
	//#define  253
	#define DEAD_STATE_ID 254
	//#define ...                    255

	*/





	;

	terminalAndNonTerminalLexemIds[""] = EMPTY_TOKEN_LEXEM_ID; // no exist in code, but exit as abstract zero lenght element // lastNonUsedid++;
	//terminalAndNonTerminalLexemIds[] = UNKNOWN_ELEMENT_ID; // no exist in code and no exit as abstract element

//#define EMPTY_TOKEN_LEXEM_ID 0
//#define UNKNOWN_ELEMENT_ID 1 // (EMPTY_TOKEN_LEXEM_ID + 1)

//EMPTY_TOKEN_LEXEM_ID
//UNKNOWN_ELEMENT_ID (EMPTY_TOKEN_LEXEM_ID + 1)

//	char emptyElementCode = getLexemId((char*)"");
//	char deadStateCode = getLexemId((char*)"DEAD_STATE");

	/* EMPTY_TOKEN_LEXEM_ID *///terminalAndNonTerminalLexemIds[""] = EMPTY_TOKEN_LEXEM_ID; // lastNonUsedid++; // !!!!!!!!!!!!!!!!



	terminalAndNonTerminalLexemIds[IDENT_METETERMINAL_LEXEM_STR] = IDENT_METETERMINAL_LEXEM_ID;
	terminalAndNonTerminalLexemIds[UNSIGNED_VALUE_METATERMINAL_LEXEM_STR] = UNSIGNED_VALUE_METATERMINAL_LEXEM_ID;

	int lastNonUsedid = NONTERMINAL_LEXEM_MIN_ID;
	lastNonUsedid = nonTerminalIdsInit(grammar, lastNonUsedid);

	//  !
	//	if (lastNonUsedid > NONTERMINAL_LEXEM_MAX_ID) {
	//		printf("Error: maximum number of lexems exceeded.\n");
	//		exit(0);
	//	}

		// terminalAndNonTerminalLexemIds["DEAD_STATE"] = DEAD_STATE_ID; // NOT INIT
		//                                                FREE_STATE_ID;

	if (lastNonUsedid);

	if (false) terminalAndNonTerminalIdsInitPart2(lexemInfoTable, lastNonUsedid); // TERMINAL INIT AFTER SCAN SOURCE
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//char getLexemTId(char* lexemStr) { // getLexemId
//	return 0;
//}

// used
//?// two table //+//
// STACK_POP_AND_MULTIPLIPUSH
void buildRulePartForDPDA1forLL2(Grammar & grammar, DPDA1Program & dpda1Program, DPDA1IndexingForSecondElement& dpda1IndexingForSecondElement) {
    // POP_STACK_IN_F_OUT_STATE_ID no impl.
	// ALL CODE FOR IDENT AND UNSIGNED VALUE

	//char emptyElementCode = getLexemId((char*)"");
	//char deadStateCode = getLexemId((char*)"DEAD_STATE");

////#define BUILD_C2P_AST_TYPE_BY_DPDA1
//#ifndef BUILD_C2P_AST_TYPE_BY_DPDA1
//#define	BUILD_P2C_AST_TYPE_BY_DPDA1 // TODO: no default
//#endif
////#if !defined(BUILD_AST_BY_DPDA1) || defined(BUILD_P2C_AST_TYPE_BY_DPDA1)

//#ifdef BUILD_P2C_AST_TYPE_BY_DPDA1
//	char popStackInFoutStateCode = getLexemId((char*)"POP_STACK_IN_F_OUT_STATE"); // POP_STACK_IN_F_OUT_STATE_ID
//#endif
	for (MarkedRule* multiRule = grammar.multiRules; multiRule->firstMarksType; ++multiRule) {
		unsigned char stackTopElementFirstCode = getLexemId(multiRule->rule.lhs); // char* currSteckElement = multiRule->rule.lhs;

		//unsigned char stackTopElementFirstCode = stackTopElementCode__;
		unsigned char stackTopElementLastCode = stackTopElementFirstCode;
		if (stackTopElementFirstCode == IDENT_METETERMINAL_LEXEM_ID) { // THIS SHOULD NEVER HAPPEN !
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
				for (int firstMarksIndex = 0; multiRule->firstMarks[firstMarksIndex][0] != '\0'; ++firstMarksIndex) {
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

						// not init or not to dead state
						if (//dpda1Program[ROW_INDEX][columnIndexSelector].tapeAction != -1
							dpda1Program[firstMarkCode][stackTopElementCode].tapeAction != SCROLL_TO_RIGHT
							||
							dpda1Program[firstMarkCode][stackTopElementCode].stackUpdate.stackAction != POP_AND_MULTIPLIPUSH
							||
							dpda1Program[firstMarkCode][stackTopElementCode].rhsVariantAddonIndexMask != 0
							||
							dpda1Program[firstMarkCode][stackTopElementCode].stackUpdate.stackAddon[0][0] != DEAD_STATE_ID
							||
							dpda1Program[firstMarkCode][stackTopElementCode].stackUpdate.stackAddon[0][1] != EMPTY_TOKEN_LEXEM_ID
							) { // ?
							printf("ERROR: no support model\r\n.");
							exit(0);
						}

						dpda1Program[firstMarkCode][stackTopElementCode].tapeAction = NO_SCROLL;
						dpda1Program[firstMarkCode][stackTopElementCode].stackUpdate.stackAction = PUSH;
						int rhsVariantAddonIndex = 1;
						for (int rhsVariantIndex = 0; multiRule->rule.rhss[rhsVariantIndex].secondMarksType; ++rhsVariantIndex, ++rhsVariantAddonIndex) {
							//if (multiRule->rule.rhss[rhsVariantIndex].secondMarks[0][0] == '\0') {
							//    return multiRule->rule.rhss + rhsVariantIndex;
							//}
		//#ifdef BUILD_AST_BY_DPDA1
		//					dpda1Program[firstMarkCode][stackTopElementCode].stackUpdate.stackAction = STACK_POP_AND_MULTIPLIPUSH; // NEW 08.2025
		//#else
							dpda1Program[firstMarkCode][stackTopElementCode].stackUpdate.stackAction = POP_AND_MULTIPLIPUSH; // NEW 08.2025
		//#endif

#ifdef BUILD_P2C_AST_TYPE_BY_DPDA1
							bool popStackInFoutStateCodeMarker = true;
#endif
							for (int rhsElementIndex = 0; rhsElementIndex < MAX_RTOKEN_COUNT; ++rhsElementIndex)
								if (rhsElementIndex < multiRule->rule.rhss[rhsVariantIndex].rhs_count) dpda1Program[firstMarkCode][stackTopElementCode].stackUpdate.stackAddon[rhsVariantIndex][rhsElementIndex]
									//= getLexemTId(multiRule->rule.rhss[rhsVariantIndex].rhs[rhsElementIndex]);
									= getLexemId(multiRule->rule.rhss[rhsVariantIndex].rhs[rhsElementIndex]);
#ifdef BUILD_P2C_AST_TYPE_BY_DPDA1
								else if (popStackInFoutStateCodeMarker) {
									dpda1Program[firstMarkCode][stackTopElementCode].stackUpdate.stackAddon[rhsVariantIndex][rhsElementIndex] = POP_STACK_IN_F_OUT_STATE_ID;
									popStackInFoutStateCodeMarker = false;
								}
#endif
								else dpda1Program[firstMarkCode][stackTopElementCode].stackUpdate.stackAddon[rhsVariantIndex][rhsElementIndex] = EMPTY_TOKEN_LEXEM_ID;

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
								for (int secondMarksIndexForCurrentRHS = 0; multiRule->rule.rhss[rhsVariantIndex].secondMarks[secondMarksIndexForCurrentRHS][0] != '\0'; ++secondMarksIndexForCurrentRHS) {
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



//#define ROW_INDEX_FOR_SECOND_TABLE secondMarkCode

									//char* currSecondMark = multiRule->rule.rhss[rhsVariantIndex].secondMarks[secondMarksIndex];
		//							char rowIndexForSecondTable = getLexemTId(multiRule->rule.rhss[rhsVariantIndex].secondMarks[secondMarksIndexForCurrentRHS]);

									if (dpda1IndexingForSecondElement[secondMarkCode][stackTopElementCode] != ~0) {
										if (dpda1IndexingForSecondElement[secondMarkCode][stackTopElementCode] != rhsVariantIndex) {
											printf("ERROR: no support model or model consider error.\r\n");
											exit(0);
										}
										else {
											printf("WARNING: multi-indexing.\r\n");

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
						//
						if (multiRule->rule.rhss[0].secondMarksType) { // + if second mark used, first rhs variant type will be set
							if (multiRule->rule.rhss[rhsVariantAddonIndex].secondMarksType) {
								printf("No support model or model consider error.\r\n");
								exit(0);
							}

							dpda1Program[firstMarkCode][stackTopElementCode].rhsVariantAddonIndexMask = ~0;
		
							//
							bool needStateToDeadState = false;

							// scan
							unsigned char secondMarkCode = 0; do {
								//const char* secondMarkStr = getLexemStr(secondMarkCode);
								if (dpda1IndexingForSecondElement[secondMarkCode][stackTopElementCode] == 255) { // !!.
									needStateToDeadState = true;
									dpda1IndexingForSecondElement[secondMarkCode][stackTopElementCode] = rhsVariantAddonIndex;
								}
							} while (++secondMarkCode);

							// add "to dead"-state // --> ...
							if (needStateToDeadState) {
								dpda1Program[firstMarkCode][stackTopElementCode].stackUpdate.stackAddon[rhsVariantAddonIndex][0/*rhsVariantIndex*/] = DEAD_STATE_ID;
								for (int rhsElementIndex = 1; rhsElementIndex < MAX_RTOKEN_COUNT; ++rhsElementIndex)
									dpda1Program[firstMarkCode][stackTopElementCode].stackUpdate.stackAddon[rhsVariantAddonIndex][rhsElementIndex] = EMPTY_TOKEN_LEXEM_ID;
							}
						}
						else {						
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

	// set default 0-index for non-setted elements
	unsigned char secondMarkCode = 0; do {
		unsigned char topStackCode = 0; do {
			if (dpda1IndexingForSecondElement[secondMarkCode][topStackCode] == ~0) {
				dpda1IndexingForSecondElement[secondMarkCode][topStackCode] = 0;
			}
		} while (++topStackCode);
	} while (++secondMarkCode);
}

// used
// tape scroll
void buildAcceptTapeElement__DPDA1forLL2(Grammar& grammar, DPDA1Program& dpda1Program, DPDA1IndexingForSecondElement& dpda1IndexingForSecondElement) {
    // ALL IDENT <-to-> ALL IDENT
	// ALL UNSIGNED VALUE <-to-> ALL UNSIGNED VALUE

	// ALL CODE FOR IDENT AND UNSIGNED VALUE
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

#define REMOVE___OR_NOT struct LexemInfo* lexemInfoTable

void buildDPDA1forLL2(Grammar& grammar, DPDA1Program& dpda1Program, DPDA1IndexingForSecondElement& dpda1IndexingForSecondElement, REMOVE___OR_NOT) {

	// init codes
	terminalAndNonTerminalIdsInit(grammar, lexemInfoTable/*, int lastNonUsedid !!!!!!!!!!! */);

	//for (const auto& [key, value] : terminalAndNonTerminalLexemIds) { // Using Structured Bindings (C++17 and later)
	//	std::cout << "Key: \"" << key << "\", Value: " << value << std::endl;
	//}
	for (const auto& pair : terminalAndNonTerminalLexemIds) { // Using a Range-Based For Loop (C++11 and later)
		std::cout << "Key: \"" << pair.first << "\", Value: " << pair.second << std::endl;
	}


	// dead state
	//buildDeadState__DPDA1forLL2(grammar, dpda1Program, dpda1IndexingForSecondElement); // TERMINAL INIT AFTER SCAN SOURCE
	//return;
	// set 255 (-1) // to dead state
	setAllStatesToDeadStateAndInitIndexing(grammar, dpda1Program, dpda1IndexingForSecondElement);

	// 123
	buildRulePartForDPDA1forLL2(grammar, dpda1Program, dpda1IndexingForSecondElement);

	return;

	//
	// 123
	//
	buildAcceptTapeElement__DPDA1forLL2(grammar, dpda1Program, dpda1IndexingForSecondElement);

	// dpda1IndexingForSecondElement[rowIndex][columnIndex]; // -1

	// MIN_TERMIN
	// All Symbol

}


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
		{
			//dpda1.data = data; !!!
			dpda1.dpdaProgram = &dpdaProgram;
			dpda1.dpdaIndexingForSecondElement = &dpdaIndexingForSecondElement;
			dpda1.run = runner3;
			dpda1.stack_above_top = dpda1.stack + SAVE_OFFSET;


			*dpda1.stack_above_top = '\0';
			buildDPDA1forLL2(grammar, *dpda1.dpdaProgram, *dpda1.dpdaIndexingForSecondElement, lexemesInfoTable);
		}
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