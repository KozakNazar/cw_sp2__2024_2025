#define _CRT_SECURE_NO_WARNINGS
/*******************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2024_2025                   *
*                         file: dpda1_for_ll2_generator__2025.cpp  *
*                                                         (draft!) *
********************************************************************/

#include "../cw_sp2__2025_2026/src/include/def.h"
#include "../cw_sp2__2025_2026/src/include/config.h"
#include "../cw_sp2__2025_2026/src/include/syntax/syntax.h"

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

using namespace std;

Grammar grammar = {
	GRAMMAR_LL2__2025
};

#define DOC_PATH "../built_doc/"
#define NPDA "NPDA"
#define GRAMMAR "Grammar"

char rhs_buffer[MAX_LEXEM_SIZE * MAX_RTOKEN_COUNT] = { 0 };
wchar_t rhs_buffer_w[MAX_LEXEM_SIZE * MAX_RTOKEN_COUNT] = { 0 };
char part_buffer[MAX_LEXEM_SIZE * 3 + 1024] = { 0 };
wchar_t part_buffer_w[MAX_LEXEM_SIZE * 3 + 1024] = { 0 };

//wchar_t* wcharArray = new wchar_t[(MAX_LEXEM_SIZE * 3 + 1024) * MAX_RULES * 12];
wchar_t* wcharOneLineArray = new wchar_t[(MAX_LEXEM_SIZE * 3 + 1024)];

void buildGrammarRule() {
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

	bool skipNextEptyRule = false; /* this will not always work (only for variants of this coursework) */
	for (MarkedRule* multiRule = grammar.multiRules; multiRule->firstMarksType; ++multiRule) {
		if (skipNextEptyRule && multiRule->rule.rhss[0].rhs[0][0] == '\0') {
			skipNextEptyRule = false;
			continue;
		}

		for (int rhsVariantIndex = 0; multiRule->rule.rhss[rhsVariantIndex].secondMarksType; ++rhsVariantIndex) {
			fprintf(f, "%s ", multiRule->rule.lhs);
			fprintf(fw, "%s ", multiRule->rule.lhs);

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
		fwprintf(fw, L"D(q,%ls", EPSILON);

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

	fclose(f);
	fclose(fw);

	printf(DOC_PATH NPDA "_ANSI.txt       [ ok ]\r\n");
	printf(DOC_PATH NPDA "_UNICODE.txt    [ ok ]\r\n");
}


void main() {
	buildGrammarRule();
	buildDeltaFunctionOfNPDA();
	
	return;
}