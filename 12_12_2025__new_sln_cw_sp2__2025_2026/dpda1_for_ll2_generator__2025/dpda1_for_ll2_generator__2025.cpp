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

#define NPDA "NPDA" // "..\"
#define GRAMMAR "Grammar" // "..\"

char rhs_buffer[MAX_LEXEM_SIZE * MAX_RTOKEN_COUNT] = { 0 };
wchar_t rhs_buffer_w[MAX_LEXEM_SIZE * MAX_RTOKEN_COUNT] = { 0 };
char part_buffer[MAX_LEXEM_SIZE * 3 + 1024] = { 0 };
wchar_t part_buffer_w[MAX_LEXEM_SIZE * 3 + 1024] = { 0 };

//wchar_t* wcharArray = new wchar_t[(MAX_LEXEM_SIZE * 3 + 1024) * MAX_RULES * 12];
wchar_t* wcharOneLineArray = new wchar_t[(MAX_LEXEM_SIZE * 3 + 1024)];

void buildGrammar(/*const char * filename*/) {
	setlocale(LC_ALL, "en_US.UTF-8");

	FILE* f = fopen(GRAMMAR"_ANSI.txt", "w");
	FILE* fw = fopen(GRAMMAR"_UNICODE.txt", "w"); //FILE* fw = fopen(GRAMMAR"_UNICODE.txt", "w, ccs=UTF-8");

	bool skipNextEptyRule = false; /* this will not always work (only for variants of this coursework) */
	for (MarkedRule* multiRule = grammar.multiRules; multiRule->firstMarksType; ++multiRule) {
		if (multiRule->rule.rhss[0].rhs[0][0] == '\0') {
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
			if (multiRule->rule.rhss[rhsVariantIndex].rhs[0][0] == '\0')
				skipNextEptyRule = true;
			else
				skipNextEptyRule = false;
			for (int rhsElementIndex = 0; !rhsElementIndex || multiRule->rule.rhss[rhsVariantIndex].rhs[rhsElementIndex][0] != '\0'; ++rhsElementIndex) {
				if (multiRule->rule.rhss[rhsVariantIndex].rhs[rhsElementIndex][0] == '\0') {
					fprintf(f, " \"\"");
					fwprintf(fw, L"%ls", EPSILON);
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

	printf(GRAMMAR"_ANSI.txt    [ ok ]\r\n");
	printf(GRAMMAR"_UNICODE.txt [ ok ]\r\n");
}

void buildNPDA_(/*const char * filename*/) {
	setlocale(LC_ALL, "en_US.UTF-8");

//	FILE* f = fopen(NPDA"_ANSI.txt", "w"); // not use '\r'
//	FILE* fw = fopen(NPDA"_UNICODE.txt", "w, ccs=UTF-8"); // not use '\r'

	bool skipNextEptyRule = false; /* this will not always work (only for variants of this coursework) */
	for (MarkedRule* multiRule = grammar.multiRules; multiRule->firstMarksType; ++multiRule) {
		if (multiRule->rule.rhss[0].rhs[0][0] == '\0') {
			skipNextEptyRule = false;
			continue;
		}
		char* part_buffer_ = (char*)part_buffer;
		part_buffer[0] = '\0';
		part_buffer_ += sprintf(part_buffer_, "D(q,\"\",%s) -> {", multiRule->rule.lhs);
		size_t curr_rhs_buffer_len;
		for (int rhsVariantIndex = 0; multiRule->rule.rhss[rhsVariantIndex].secondMarksType; ++rhsVariantIndex) {	
			if (rhsVariantIndex)
				part_buffer_ += sprintf(part_buffer_, ",");
			
			char* rhs_buffer_ = (char*)rhs_buffer;
			rhs_buffer[0] = '\0';
			if (multiRule->rule.rhss[rhsVariantIndex].rhs[0][0] == '\0')
				skipNextEptyRule = true;
			else
				skipNextEptyRule = false;
			for (int rhsElementIndex = 0; !rhsElementIndex || multiRule->rule.rhss[rhsVariantIndex].rhs[rhsElementIndex][0] != '\0'; ++rhsElementIndex) {
				if(multiRule->rule.rhss[rhsVariantIndex].rhs[rhsElementIndex][0] == '\0')
					rhs_buffer_ += sprintf(rhs_buffer_, " \"\"");
				else
					rhs_buffer_ += sprintf(rhs_buffer_, " %s", multiRule->rule.rhss[rhsVariantIndex].rhs[rhsElementIndex]);
			}
//			curr_rhs_buffer_len = strlen(rhs_buffer);
//			if (rhs_buffer[curr_rhs_buffer_len - 1] == ' ') rhs_buffer[curr_rhs_buffer_len - 1] = '\0';

			part_buffer_ += sprintf(part_buffer_, "(q,%s )", rhs_buffer);

			if (!multiRule[0].rule.rhss[rhsVariantIndex + 1].secondMarksType &&
				multiRule[1].firstMarksType &&
				!strncmp(multiRule[0].rule.lhs, multiRule[1].rule.lhs, MAX_LEXEM_SIZE)) {
				size_t part_buffer_len = strlen(part_buffer);

				//part_buffer_ += sprintf(part_buffer_, ",");
				++multiRule;
				rhsVariantIndex = -1;

				if (skipNextEptyRule && multiRule->rule.rhss[0].rhs[0][0] == '\0') {
					multiRule += 2;
					rhsVariantIndex = 0;
					skipNextEptyRule = false;
				}
				else if (part_buffer[part_buffer_len - 1] != ',') {
					part_buffer[part_buffer_len] = ',';
					part_buffer[part_buffer_len + 1] = '\0';
					++part_buffer_;
				}

			}
		}
		curr_rhs_buffer_len = strlen(rhs_buffer);
		if (rhs_buffer[curr_rhs_buffer_len - 1] == ',') rhs_buffer[curr_rhs_buffer_len - 1] = '\0';
		part_buffer_ += sprintf(part_buffer_, "}");
		printf("%s\n", part_buffer);
	}
}


void buildNPDA(/*const char * filename*/) {
	setlocale(LC_ALL, "en_US.UTF-8");

	FILE* f = fopen(NPDA"_ANSI.txt", "w+");
	FILE* fw = fopen(NPDA"_UNICODE.txt", "w+"); //FILE* fw = fopen(GRAMMAR"_UNICODE.txt", "w, ccs=UTF-8");

	bool skipNextEptyRule = false; /* this will not always work (only for variants of this coursework) */
	for (MarkedRule* multiRule = grammar.multiRules; multiRule->firstMarksType; ++multiRule) {
		if (multiRule->rule.rhss[0].rhs[0][0] == '\0') {
			skipNextEptyRule = false;
			continue;
		}
//		char* part_buffer_ = (char*)part_buffer;
//		part_buffer[0] = '\0';
		//part_buffer_ += sprintf(part_buffer_, "D(q,\"\",%s) -> {", multiRule->rule.lhs);

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
				//part_buffer_ += sprintf(part_buffer_, ",");

			fprintf(f, "(q,");
			fwprintf(fw, L"(q,");

//			char* rhs_buffer_ = (char*)rhs_buffer;
//			rhs_buffer[0] = '\0';
			if (multiRule->rule.rhss[rhsVariantIndex].rhs[0][0] == '\0')
				skipNextEptyRule = true;
			else
				skipNextEptyRule = false;
			for (int rhsElementIndex = 0; !rhsElementIndex || multiRule->rule.rhss[rhsVariantIndex].rhs[rhsElementIndex][0] != '\0'; ++rhsElementIndex) {
				if (multiRule->rule.rhss[rhsVariantIndex].rhs[rhsElementIndex][0] == '\0'){
					fprintf(f, " \"\"");
					fwprintf(fw, L" %ls", EPSILON);
				}
					//rhs_buffer_ += sprintf(rhs_buffer_, " \"\"");
				else{
					fprintf(f, " %s", multiRule->rule.rhss[rhsVariantIndex].rhs[rhsElementIndex]);
					fprintf(fw, " %s", multiRule->rule.rhss[rhsVariantIndex].rhs[rhsElementIndex]);
				}
			}
			//curr_rhs_buffer_len = strlen(rhs_buffer);
			//if (rhs_buffer[curr_rhs_buffer_len - 1] == ' ') rhs_buffer[curr_rhs_buffer_len - 1] = '\0';
            //
			//fseek(f, -1, SEEK_END);
			//if (fgetc(f) == ' ') {
			//	fseek(f, -1, SEEK_CUR); // Повертаємось
			//	fputc(';', f);          // Міняємо
			//}

			//part_buffer_ += sprintf(part_buffer_, "%s )", rhs_buffer);
			fprintf(f, " )");
			fprintf(fw, " )");

			if (!multiRule[0].rule.rhss[rhsVariantIndex + 1].secondMarksType &&
				multiRule[1].firstMarksType &&
				!strncmp(multiRule[0].rule.lhs, multiRule[1].rule.lhs, MAX_LEXEM_SIZE)) {
				size_t part_buffer_len = strlen(part_buffer);

				//part_buffer_ += sprintf(part_buffer_, ",");
				++multiRule;
				rhsVariantIndex = -1;

				//long pos = ftell(f);
				//if (pos) fseek(f, -1, SEEK_END);
				if (skipNextEptyRule && multiRule->rule.rhss[0].rhs[0][0] == '\0') {
					multiRule += 2;
					rhsVariantIndex = 0;
					skipNextEptyRule = false;
				}
				//else if (part_buffer[part_buffer_len - 1] != ',') {
				//	part_buffer[part_buffer_len] = ',';
				//	part_buffer[part_buffer_len + 1] = '\0';
				//	++part_buffer_;
				//}
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


//				//fseek(f, -1, SEEK_END);            // На останній символ
//				else if (fgetc(f) != ',') {             // Якщо не кома
//					fputc(',', f);                 // Додати кому
//				}

			}
		}
//		curr_rhs_buffer_len = strlen(rhs_buffer);
//		if (rhs_buffer[curr_rhs_buffer_len - 1] == ',') rhs_buffer[curr_rhs_buffer_len - 1] = '\0';

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

//		fseek(f, -1, SEEK_END);       // На останній символ
//		if (fgetc(f) == ',') {        // Якщо кома
//#ifdef _WIN32
//			__int64 new_size = (__int64)ftell(f) - 1;
//			_chsize_s(_fileno(f), new_size);
//#else
//			ftruncate(fileno(f), ftell(f) - 1);
//#endif
//		}

		//part_buffer_ += sprintf(part_buffer_, "}");
		//printf("%s\n", part_buffer);

		fprintf(f, "}\n");
		fprintf(fw, "}\n");


	}

	fclose(f);
	fclose(fw);

	printf(NPDA"_ANSI.txt    [ ok ]\r\n");
	printf(NPDA"_UNICODE.txt [ ok ]\r\n");
}


void main() {
	//buildGrammar();
	buildNPDA();
	
	return;
}