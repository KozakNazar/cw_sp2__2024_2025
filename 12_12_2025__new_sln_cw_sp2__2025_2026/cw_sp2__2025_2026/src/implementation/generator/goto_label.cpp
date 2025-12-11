#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2024_2025            *
*                         file: goto_lable.cpp              *
*                                                  (draft!) *
*************************************************************/

#include <string>
#include <map>
//#include <utility>
#include <stack>

#include "../../include/def.h"
#include "../../include/generator/generator.h"
#include "../../include/lexica/lexica.h"
#include "stdio.h"

std::map<std::string, std::pair<unsigned long long int, std::stack<unsigned long long int>>> labelInfoTable;

unsigned char* makeLabelCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	unsigned char multitokenSize, multitokenSize_ = detectMultiToken(*lastLexemInfoInTable + 1, MULTI_TOKEN_NULL_STATEMENT);
	multitokenSize = detectMultiToken(*lastLexemInfoInTable + multitokenSize_ + 1, MULTI_TOKEN_COLON);
	if (multitokenSize) {
		multitokenSize += multitokenSize_;
	}
	if ((*lastLexemInfoInTable)->tokenType != IDENTIFIER_LEXEME_TYPE){
		return currBytePtr;
	}
	if (multitokenSize++) {
		if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
			//
		}
		else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    ;ident \"%s\"(as label) previous \"%s\"\r\n", (*lastLexemInfoInTable)->lexemStr, tokenStruct[MULTI_TOKEN_COLON][0]);
		}
		else if (generatorMode == C_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    //ident \"%s\"(as label) previous \"%s\"\r\n", (*lastLexemInfoInTable)->lexemStr, tokenStruct[MULTI_TOKEN_COLON][0]);
		}

		labelInfoTable[(*lastLexemInfoInTable)->lexemStr].first = (unsigned long long int)currBytePtr;

		while (!labelInfoTable[(*lastLexemInfoInTable)->lexemStr].second.empty()) {
			if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
				*(unsigned int*)labelInfoTable[(*lastLexemInfoInTable)->lexemStr].second.top() = (unsigned int)(currBytePtr - (unsigned char*)labelInfoTable[(*lastLexemInfoInTable)->lexemStr].second.top() - 4);
			}
			labelInfoTable[(*lastLexemInfoInTable)->lexemStr].second.pop();
		}

		if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
			//
		}
		else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
			currBytePtr += snprintf((char*)currBytePtr, 8192, "LABEL@%016llX:\r\n", (unsigned long long int) & labelInfoTable[(*lastLexemInfoInTable)->lexemStr].first);
		}
		else if (generatorMode == C_CODER_MODE) {
			currBytePtr += snprintf((char*)currBytePtr, 8192, "LABEL__%016llX:\r\n", (unsigned long long int) & labelInfoTable[(*lastLexemInfoInTable)->lexemStr].first);
		}

		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}

unsigned char* makeGotoLabelCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_GOTO);
	if (multitokenSize++) {
		if ((*lastLexemInfoInTable + 1)->tokenType != IDENTIFIER_LEXEME_TYPE) {
			return currBytePtr;
		}
		if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
			const unsigned char code__jmp_offset[] = { 0xE9, 0x00, 0x00, 0x00, 0x00 };

			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__jmp_offset, 5);
		}
		else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    ;\"%s\" previous ident \"%s\"(as label)\r\n", tokenStruct[MULTI_TOKEN_GOTO][0], (*lastLexemInfoInTable)[1].lexemStr);
		}
		else if (generatorMode == C_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    //\"%s\" previous ident \"%s\"(as label)\r\n", tokenStruct[MULTI_TOKEN_GOTO][0], (*lastLexemInfoInTable)[1].lexemStr);
		}

		if (labelInfoTable.find((*lastLexemInfoInTable)[1].lexemStr) == labelInfoTable.end()) {
			labelInfoTable[(*lastLexemInfoInTable)[1].lexemStr].first = ~0;
		}

		if (labelInfoTable[(*lastLexemInfoInTable)[1].lexemStr].first == ~0) {
			labelInfoTable[(*lastLexemInfoInTable)[1].lexemStr].second.push((unsigned long long int)(currBytePtr - 4));
		}
		else if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
			*(unsigned int*)(currBytePtr - 4) = (unsigned int)((unsigned char*)labelInfoTable[(*lastLexemInfoInTable)[1].lexemStr].first - currBytePtr);
		}

		if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
			//
		}
		else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    jmp LABEL@%016llX\r\n", (unsigned long long int) & labelInfoTable[(*lastLexemInfoInTable)[1].lexemStr].first);
		}
		else if (generatorMode == C_CODER_MODE) {
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    goto LABEL__%016llX;\r\n", (unsigned long long int) & labelInfoTable[(*lastLexemInfoInTable)[1].lexemStr].first);
		}

		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}