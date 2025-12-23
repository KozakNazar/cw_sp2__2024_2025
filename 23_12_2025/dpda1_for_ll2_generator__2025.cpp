#define _CRT_SECURE_NO_WARNINGS
/*******************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2024_2025                   *
*                         file: dpda1_for_ll2_generator__2025.cpp  *
*                                                         (draft!) *
********************************************************************/

#include "def.h"
#include "config.h"
#include "syntax.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
//#include <unordered_map>
#include <string>
#include <set>

#include "stdio.h" 
#include "stdlib.h" // for exit() // TODO:...
#include "string.h"
#ifdef _WIN32
#include <io.h>      // _chsize_s
#else
#include <unistd.h>  // ftruncate (POSIX)
#endif

//#include <wchar.h>
#define ARROW_RIGHT L"\u2192"
#define EPSILON     L"\u03B5"
#define DELTA       L"\u03B4"
#define LAMBDA      L"\u03BB"

#include <cstdlib>
#include <clocale>
#include <cwchar>
//#include <stdexcept>

#include <fstream>
#include <iostream>
//#include <algorithm>
#include <iterator>
#include <regex>

using namespace std;

Grammar grammar = {
	GRAMMAR_LL2__2025
};

#define DOC_PATH "built_doc/"
#define NPDA "NPDA"
#define GRAMMAR "Grammar"

char rhs_buffer[MAX_LEXEM_SIZE * MAX_RTOKEN_COUNT] = { 0 };
wchar_t rhs_buffer_w[MAX_LEXEM_SIZE * MAX_RTOKEN_COUNT] = { 0 };
char part_buffer[MAX_LEXEM_SIZE * 3 + 1024] = { 0 };
wchar_t part_buffer_w[MAX_LEXEM_SIZE * 3 + 1024] = { 0 };

//wchar_t* wcharArray = new wchar_t[(MAX_LEXEM_SIZE * 3 + 1024) * MAX_RULES * 12];
wchar_t* wcharOneLineArray = new wchar_t[(MAX_LEXEM_SIZE * 3 + 1024)];

std::map<std::string, unsigned char> terminalAndNonTerminalLexemIds;
////std::map<unsigned char, std::string> terminalAndNonTerminalLexemStrs__copy;

////void buildTerminalAndNonTerminalLexemStrs__copy() {
////	for (auto iterator = terminalAndNonTerminalLexemIds.begin(); iterator != terminalAndNonTerminalLexemIds.end(); ++iterator)
////		terminalAndNonTerminalLexemStrs__copy[iterator->second] = iterator->first;
////}

unsigned char getLexemId(char* str) {
	if (str == nullptr)
		return UNKNOWN_ELEMENT_ID;
	auto element = terminalAndNonTerminalLexemIds.find(str);
	if (element == terminalAndNonTerminalLexemIds.end())
		return UNKNOWN_ELEMENT_ID;
	else
		return element->second;
}

////bool getLexemStr(unsigned char id, std::string& lexemStr) {
////	if (terminalAndNonTerminalLexemStrs__copy.empty()) {
////		for (auto iterator = terminalAndNonTerminalLexemIds.begin(); iterator != terminalAndNonTerminalLexemIds.end(); ++iterator)
////			if (iterator->second == id) {
////				lexemStr = iterator->first;
////				return true;
////			}
////	}
////	else {
////		auto element = terminalAndNonTerminalLexemStrs__copy.find(id);
////		if (element != terminalAndNonTerminalLexemStrs__copy.end()) {
////			lexemStr = element->second;
////			return true;
////		}
////	}
////
////	return false;
////}

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

void buildGrammar() {
	setlocale(LC_ALL, "en_US.UTF-8");

	FILE* f = fopen(DOC_PATH GRAMMAR "_ANSI.txt", "w+");
	if (!f) {
		printf(DOC_PATH NPDA "_ANSI.txt    [ :( ]\r\n");
		return;
	}

	FILE* fw = fopen(DOC_PATH GRAMMAR "_UNICODE.txt", "w+"); //FILE* fw = fopen(GRAMMAR"_UNICODE.txt", "w, ccs=UTF-8");	
	if (!f) {
		fclose(f);
		printf(DOC_PATH GRAMMAR "_UNICODE.txt [ :( ]\r\n");
		return;
	}

	fprintf(f, "G = (\n");
	fprintf(fw, "G = (\n");

	fprintf(f, "    N = {\n");
	fprintf(fw, "    N = {\n");

	terminalAndNonTerminalLexemIds[IDENTIFIER_METATERMINAL_LEXEM_STR] = IDENTIFIER_METATERMINAL_LEXEM_ID;
	terminalAndNonTerminalLexemIds[UNSIGNED_VALUE_METATERMINAL_LEXEM_STR] = UNSIGNED_VALUE_METATERMINAL_LEXEM_ID;

	keyWordAndNonTerminalIdsInit(grammar, NONTERMINAL_LEXEM_MIN_ID);

	//bool noFirstElement = false;
	for (const auto& pair : terminalAndNonTerminalLexemIds) { // Using a Range-Based For Loop (C++11 and later)
		if (pair.second >= NONTERMINAL_LEXEM_MIN_ID) {
			fprintf(f, "        %s ", pair.first.c_str());
			fprintf(fw, "        %s ", pair.first.c_str());
			//if (noFirstElement) {
			//	fprintf(f, ",\n");
			//	fprintf(fw, ",\n");
			//}
			//else {
			//	fprintf(f, "\n");
			//	fprintf(fw, "\n");
			//	noFirstElement = true;
			//}
			fprintf(f, "\n");
			fprintf(fw, "\n");
		}
	}
	fprintf(f, "    },\n    T = {\n");
	fprintf(fw, "    },\n    T = {\n");

	//noFirstElement = false;
	for (const auto& pair : terminalAndNonTerminalLexemIds) { // Using a Range-Based For Loop (C++11 and later)
		if (pair.second < NONTERMINAL_LEXEM_MIN_ID) {
			fprintf(f, "        %s ", pair.first.c_str());
			fprintf(fw, "        %s ", pair.first.c_str());
			//if (noFirstElement) {
			//	fprintf(f, ",\n");
			//	fprintf(fw, ",\n");
			//}
			//else {
			//	fprintf(f, "\n");
			//	fprintf(fw, "\n");
			//	noFirstElement = true;
			//}
			fprintf(f, "\n");
			fprintf(fw, "\n");
		}
	}
	fprintf(f, "    },\n    P = {\n");
	fprintf(fw, "    },\n    P = {\n");

	bool skipNextEptyRule = false; /* this will not always work (only for variants of this coursework) */
	for (MarkedRule* multiRule = grammar.multiRules; multiRule->firstMarksType; ++multiRule) {
		if (skipNextEptyRule && multiRule->rule.rhss[0].rhs[0][0] == '\0') {
			skipNextEptyRule = false;
			continue;
		}

		for (int rhsVariantIndex = 0; multiRule->rule.rhss[rhsVariantIndex].secondMarksType; ++rhsVariantIndex) {
			fprintf(f, "        %s ", multiRule->rule.lhs);
			fprintf(fw, "        %s ", multiRule->rule.lhs);

			fprintf(f, "->");
			fwprintf(fw, L"%ls", ARROW_RIGHT); // fwprintf(fw, L"%lc", 0x2192);

			char* rhs_buffer_ = (char*)rhs_buffer;
			rhs_buffer[0] = '\0';
			if (rhsVariantIndex && multiRule->rule.rhss[rhsVariantIndex].rhs[0][0] == '\0')
				skipNextEptyRule = true;
			else
				skipNextEptyRule = false;
			for (int rhsElementIndex = 0; !rhsElementIndex || multiRule->rule.rhss[rhsVariantIndex].rhs[rhsElementIndex][0] != '\0'; ++rhsElementIndex) {
				if (multiRule->rule.rhss[rhsVariantIndex].rhs[rhsElementIndex][0] == '\0') {
					fprintf(f, " \"\"");
					fwprintf(fw, L" %ls", EPSILON);
				}
				else {
					fprintf(f, " %s", multiRule->rule.rhss[rhsVariantIndex].rhs[rhsElementIndex]);
					fprintf(fw, " %s", multiRule->rule.rhss[rhsVariantIndex].rhs[rhsElementIndex]);
				}
			}
			
			fprintf(f, "\n");
			fprintf(fw, "\n");
		}
	}
	fprintf(f, "    },\n    S = %s\n)", PROGRAM_RULE_STR);
	fprintf(fw, "    },\n    S = %s\n)", PROGRAM_RULE_STR);

	fclose(f);
	fclose(fw);

	printf(DOC_PATH GRAMMAR "_ANSI.txt    [ ok ]\r\n");
	printf(DOC_PATH GRAMMAR "_UNICODE.txt [ ok ]\r\n");
}

void buildDeltaFunctionOfNPDA() {
	setlocale(LC_ALL, "en_US.UTF-8");

	FILE* f = fopen(DOC_PATH NPDA "_ANSI.txt", "w+");
	if (!f) {
		printf(DOC_PATH NPDA "_ANSI.txt       [ :( ]\r\n");
		return;
	}	
	
	FILE* fw = fopen(DOC_PATH NPDA "_UNICODE.txt", "w+"); //FILE* fw = fopen(DOC_PATH NPDA "_UNICODE.txt", "w, ccs=UTF-8");	
	if (!fw) {
		fclose(f);
		printf(DOC_PATH NPDA "_UNICODE.txt    [ :( ]\r\n");
		return;
	}

	bool skipNextEptyRule = false; /* this will not always work (only for variants of this coursework) */
	for (MarkedRule* multiRule = grammar.multiRules; multiRule->firstMarksType; ++multiRule) {
		if (multiRule->rule.rhss[0].rhs[0][0] == '\0') {
			skipNextEptyRule = false;
			continue;
		}

		fprintf(f, "D(q,\"\"");
		fwprintf(fw, L"%ls(q,%ls", DELTA, EPSILON);

		fprintf(f, ",%s) ", multiRule->rule.lhs);
		fprintf(fw, ",%s) ", multiRule->rule.lhs);

		fprintf(f, "-> {");
		fwprintf(fw, L"%ls {", ARROW_RIGHT); // fwprintf(fw, L"%lc {", 0x2192);

		size_t curr_rhs_buffer_len;
		for (int rhsVariantIndex = 0; multiRule->rule.rhss[rhsVariantIndex].secondMarksType; ++rhsVariantIndex) {
			if (rhsVariantIndex) {
				fprintf(f, ",");
				fprintf(fw, ",");
			}

			fprintf(f, "(q,");
			fwprintf(fw, L"(q,");

			if (multiRule->rule.rhss[rhsVariantIndex].rhs[0][0] == '\0')
				skipNextEptyRule = true;
			else
				skipNextEptyRule = false;
			for (int rhsElementIndex = 0; !rhsElementIndex || multiRule->rule.rhss[rhsVariantIndex].rhs[rhsElementIndex][0] != '\0'; ++rhsElementIndex) {
				if (multiRule->rule.rhss[rhsVariantIndex].rhs[rhsElementIndex][0] == '\0'){
					fprintf(f, " \"\"");
					fwprintf(fw, L" %ls", EPSILON);
				}
				else{
					fprintf(f, " %s", multiRule->rule.rhss[rhsVariantIndex].rhs[rhsElementIndex]);
					fprintf(fw, " %s", multiRule->rule.rhss[rhsVariantIndex].rhs[rhsElementIndex]);
				}
			}

			fprintf(f, " )");
			fprintf(fw, " )");

			if (!multiRule[0].rule.rhss[rhsVariantIndex + 1].secondMarksType &&
				multiRule[1].firstMarksType &&
				!strncmp(multiRule[0].rule.lhs, multiRule[1].rule.lhs, MAX_LEXEM_SIZE)) {
				//size_t part_buffer_len = strlen(part_buffer);

				++multiRule;
				rhsVariantIndex = -1;

				if (skipNextEptyRule && multiRule->rule.rhss[0].rhs[0][0] == '\0') {
					multiRule += 2;
					rhsVariantIndex = 0;
					skipNextEptyRule = false;
				}
				else {				
					long pos = ftell(f);
					if (pos > 0) {
						fseek(f, -1, SEEK_END);
						fseek(fw, -1, SEEK_END);
						int last = fgetc(f);
						if (last != ',') {
							fseek(f, 0, SEEK_END);
							fseek(fw, 0, SEEK_END);
							fputc(',', f);
							fputc(',', fw);
						}
					}
					else {
						fputc(',', f);
						fputc(',', fw);
					}			
				}
			}
		}
		long pos = ftell(f);
		if (pos > 0) {
			fseek(f, -1, SEEK_END);
			int last = fgetc(f);
			if (last == ',') {
#ifdef _WIN32
				__int64 new_size = (__int64)ftell(f) - 1;
				_chsize_s(_fileno(f), new_size);
#else
				ftruncate(fileno(f), ftell(f) - 1);
#endif
			}
			fseek(f, 0, SEEK_END);
		}

		fprintf(f, "}\n");
		fprintf(fw, "}\n");
	}

	fprintf(f, "\n");
	fprintf(fw, "\n");

	//noFirstElement = false;
	for (const auto& pair : terminalAndNonTerminalLexemIds) { // Using a Range-Based For Loop (C++11 and later)
		if (pair.second < NONTERMINAL_LEXEM_MIN_ID) {
			fprintf(f, "D(q,");
			fwprintf(fw, L"%ls(q,", DELTA);

			fprintf(f, "%s,%s) ", pair.first.c_str(), pair.first.c_str());
			fprintf(fw, "%s,%s) ", pair.first.c_str(), pair.first.c_str());

			fprintf(f, "-> {(q,\"\")}");
			fwprintf(fw, L"%ls {(q,%ls)}", ARROW_RIGHT, EPSILON); // fwprintf(fw, L"%lc {", 0x2192);

			//if (noFirstElement) {
			//	fprintf(f, ",\n");
			//	fprintf(fw, ",\n");
			//}
			//else {
			//	fprintf(f, "\n");
			//	fprintf(fw, "\n");
			//	noFirstElement = true;
			//}
			fprintf(f, "\n");
			fprintf(fw, "\n");
		}
	}

	fclose(f);
	fclose(fw);

	printf(DOC_PATH NPDA "_ANSI.txt       [ ok ]\r\n");
	printf(DOC_PATH NPDA "_UNICODE.txt    [ ok ]\r\n");
}


void main() {
	buildGrammar();
	buildDeltaFunctionOfNPDA();
	
	return;
}