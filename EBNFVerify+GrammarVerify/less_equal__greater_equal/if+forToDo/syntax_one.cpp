#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // lexica__2025                 *
*                         file: syntax_one.cpp              *
*                                                  (draft!) *
*************************************************************/

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

//int syntaxAnalyze(       LexemInfo* lexemInfoTable, Grammar* grammar, char syntaxlAnalyzeMode, char* astFileName, char* errorMessagesPtrToLastBytePtr, bool viewAST);
//int syntaxAnalyze(struct LexemInfo* lexemInfoTable, Grammar* grammar, char syntaxlAnalyzeMode/* not used */, char* astFileName, char* errorMessagesPtrToLastBytePtr, bool viewAST);

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>
#include <set>

#include "stdlib.h" // for exit() // TODO:...
#include "string.h"

//#define DEFAULT_INPUT_FILE "../base_test_programs_2025/file1.k03"
// #define AST_OUTPUT_FILE "../base_test_programs_2025/ast.txt"
//#define DEFAULT_INPUT_FILE "../other_test_programs_2025/file4.k03"
//#define AST_OUTPUT_FILE "../base_test_programs_2025/ast.txt"
#define DEFAULT_INPUT_FILE "file1.k03"
#define AST_OUTPUT_FILE "ast.txt"

unsigned char errorMessagesPtrToLastBytePtr[8 * 1024 * 1024] = { '\0' };

#define SUCCESS_STATE 0

#define DEBUG_MODE 4096

#define RERUN_MODE

#define VALUE_SIZE 4

#define MAX_TEXT_SIZE 8192
#define MAX_WORD_COUNT (MAX_TEXT_SIZE / 5)
#define MAX_LEXEM_SIZE 1024
#define MAX_VARIABLES_COUNT 256
#define MAX_KEYWORD_COUNT 64

#define KEYWORD_LEXEME_TYPE 1
#define IDENTIFIER_LEXEME_TYPE 2 // #define LABEL_LEXEME_TYPE 8
#define VALUE_LEXEME_TYPE 4
#define UNEXPEXTED_LEXEME_TYPE 127

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

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include <fstream>
#include <iostream>
//#include <algorithm>
#include <iterator>
#include <regex>

//struct LexemInfo {
//	char lexemStr[MAX_LEXEM_SIZE];
//	unsigned int lexemId;
//	unsigned int tokenType;
//	unsigned int ifvalue;
//	unsigned int row;
//	unsigned int col;
//	// TODO: ...
//};

#define MAX_ACCESSORY_STACK_SIZE_123 128

char tempStrFor_123[MAX_TEXT_SIZE/*?TODO:... MAX_ACCESSORY_STACK_SIZE_123 * 64*/] = {'\0'};
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
LexemInfo::LexemInfo(const char * lexemStr, unsigned long long int lexemId, unsigned long long int tokenType, unsigned long long int ifvalue, unsigned long long int row, unsigned long long int col) {
	strncpy(this->lexemStr, lexemStr, MAX_LEXEM_SIZE);
	this->lexemId = lexemId;
	this->tokenType = tokenType;
	this->ifvalue = ifvalue;
	this->row = row;
	this->col = col;
}
LexemInfo::LexemInfo(const NonContainedLexemInfo& nonContainedLexemInfo){
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
unsigned int getIdentifierId(char(*identifierIdsTable)[MAX_LEXEM_SIZE], char* str) {
	unsigned int index = 0;
	for (; identifierIdsTable[index][0] != '\0'; ++index) {
		if (!strncmp(identifierIdsTable[index], str, MAX_LEXEM_SIZE)) {
			return index;
		}
	}
	strncpy(identifierIdsTable[index], str, MAX_LEXEM_SIZE);
	identifierIdsTable[index + 1][0] = '\0'; // not necessarily for zero-init identifierIdsTable
	return index;
}

// try to get identifier
unsigned int tryToGetIdentifier(struct LexemInfo* lexemInfoInTable, char(*identifierIdsTable)[MAX_LEXEM_SIZE]) {
	char * identifiers_re = (char*) IDENTIFIERS_RE;
	//char identifiers_re[] = "_[A-Z][A-Z][A-Z][A-Z][A-Z][A-Z][A-Z]";

	if (std::regex_match(std::string(lexemInfoInTable->lexemStr), std::regex(identifiers_re))) {
		lexemInfoInTable->lexemId = getIdentifierId(identifierIdsTable, lexemInfoInTable->lexemStr);
		lexemInfoInTable->tokenType = IDENTIFIER_LEXEME_TYPE;
		return SUCCESS_STATE;
	}

	return ~SUCCESS_STATE;
}

// try to get value
unsigned int tryToGetUnsignedValue(struct LexemInfo* lexemInfoInTable) {
	char * unsignedvalues_re = (char*) UNSIGNEDVALUES_RE;
	//char unsignedvalues_re[] = "0|[1-9][0-9]*";

	if (std::regex_match(std::string(lexemInfoInTable->lexemStr), std::regex(unsignedvalues_re))) {
		lexemInfoInTable->ifvalue = atoi(lastLexemInfoInTable->lexemStr);
		lexemInfoInTable->lexemId = MAX_VARIABLES_COUNT + MAX_KEYWORD_COUNT;
		lexemInfoInTable->tokenType = VALUE_LEXEME_TYPE;
		return SUCCESS_STATE;
	}

	return ~SUCCESS_STATE;
}

extern int commentRemover(char* text, const char* openStrSpc, const char* closeStrSpc); /* {
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
} */

void prepareKeyWordIdGetter(char* keywords_, char* keywords_re) {
	if (keywords_ == NULL || keywords_re == NULL) {
		return;
	}

	for (char* keywords_re_ = keywords_re, *keywords__ = keywords_; (*keywords_re_ != '\0') ? 1 : (*keywords__ = '\0', 0); (*keywords_re_ != '\\' || (keywords_re_[1] != '+' && keywords_re_[1] != '*' && keywords_re_[1] != '|')) ? *keywords__++ = *keywords_re_ : 0, ++keywords_re_);
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

	for (; lexemInKeywords_ = strstr(lexemInKeywords_, lexemStr), lexemInKeywords_ != NULL && lexemInKeywords_[lexemStrLen] != '|' && lexemInKeywords_[lexemStrLen] != '\0'; ++lexemInKeywords_);

	return lexemInKeywords_ - keywords_ + baseId;
}

// try to get KeyWord
char tryToGetKeyWord(struct LexemInfo* lexemInfoInTable) {
	char * keywords_re = (char*) KEYWORDS_RE;
	//char keywords_re[] = ";|<<|>>|\\+|-|\\*|,|==|!=|:|\\(|\\)|NAME|DATA|BODY|END|EXIT|CONTINUE|GET|PUT|IF|ELSE|FOR|TO|DOWNTO|DO|WHILE|REPEAT|UNTIL|GOTO|DIV|MOD|<=|>=|NOT|AND|OR|INTEGER16";
	//char keywords_re[] = ";|<<|\\+\\+|--|\\*\\*|==|\\(|\\)|!=|:|name|data|body|end|get|put|for|to|downto|do|while|continue|exit|repeat|until|if|goto|div|mod|le|ge|not|and|or|long|int";
	char keywords_[sizeof(KEYWORDS_RE)] = { '\0' };
	prepareKeyWordIdGetter(keywords_, keywords_re);

	if (std::regex_match(std::string(lexemInfoInTable->lexemStr), std::regex(keywords_re))) {
		lexemInfoInTable->lexemId = getKeyWordId(keywords_, lexemInfoInTable->lexemStr, MAX_VARIABLES_COUNT);
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
	char * tokens_re = (char*) TOKENS_RE;
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
extern size_t loadSource(char** text, char* fileName); /* {
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
} */

void writeBytesToFile(const char* output_file, unsigned char* byteImage, unsigned long long int imageSize);
int syntaxAnalyze(struct LexemInfo* lexemInfoTable, Grammar* grammar, char syntaxlAnalyzeMode/* not used */, char* astFileName, char* errorMessagesPtrToLastBytePtr, bool viewAST);

int main_syntax(int argc, char* argv[]) {
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

void writeBytesToFile(const char* output_file, unsigned char* byteImage, unsigned long long int imageSize) {
	if (!output_file || !byteImage) {
		perror("Error in write image to file");
		exit(EXIT_FAILURE);
	}

	FILE* outfile = fopen(output_file, "wb");
	if (!outfile) {
		perror("Error opening output file");
		exit(EXIT_FAILURE);
	}

	if (imageSize) {
		fwrite(byteImage, 1, imageSize, outfile);
	}

	fclose(outfile);
	printf("File \"%s\" saved.\n", output_file);
}

using namespace std;


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

struct LexemInfo* syntaxLL2(Grammar* grammar, char* ruleName, struct LexemInfo* lexemInfoTable, ASTNode** baseASTNode, struct LexemInfo** badLexemInfo) {
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