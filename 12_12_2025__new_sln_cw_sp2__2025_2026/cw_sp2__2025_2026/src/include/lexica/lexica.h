#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2024_2025            *
*                         file: lexica.h                    *
*                                                  (draft!) *
*************************************************************/

/////#define IDENTIFIER_LEXEME_TYPE 2
/////#define VALUE_LEXEME_TYPE 4
#define VALUE_SIZE 4

#define MAX_TEXT_SIZE 8192
#define MAX_WORD_COUNT (MAX_TEXT_SIZE / 5)
#define MAX_LEXEM_SIZE 1024
#define EMPTY_TOKEN_LEXEM_ID 0
#define UNKNOWN_ELEMENT_ID 1 // (EMPTY_TOKEN_LEXEM_ID + 1)
#define MAX_KEYWORD_COUNT 64
#define MAX_VARIABLES_COUNT 32
#define MAX_LITERAL_COUNT 32

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

#define UNEXPEXTED_LEXEME_TYPE  UNKNOWN_ELEMENT_ID // 127
#define KEYWORD_LEXEME_TYPE 2
#define IDENTIFIER_LEXEME_TYPE 4 // #define LABEL_LEXEME_TYPE 8
#define VALUE_LEXEME_TYPE 8
#define UNEXPEXTED_LEXEME_TYPE 127

extern char tempStrFor_123[MAX_TEXT_SIZE/*?TODO:... MAX_ACCESSORY_STACK_SIZE_123 * 64*/];
extern unsigned long long int tempStrForCurrIndex;

#ifndef LEXEM_INFO_
#define LEXEM_INFO_
struct NonContainedLexemInfo;
struct LexemInfo {public:
	char lexemStr[MAX_LEXEM_SIZE];
	unsigned long long int lexemId;
	unsigned long long int tokenType;
	unsigned long long int ifvalue; // long long int 
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
	unsigned long long int ifvalue; // long long int
	unsigned long long int row;
	unsigned long long int col;
	// TODO: ...

	NonContainedLexemInfo();
	NonContainedLexemInfo(const LexemInfo& lexemInfo);
};
#endif

extern struct LexemInfo lexemesInfoTable[MAX_WORD_COUNT];
extern struct LexemInfo* lastLexemInfoInTable;

extern char identifierIdsTable[MAX_WORD_COUNT][MAX_LEXEM_SIZE];

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