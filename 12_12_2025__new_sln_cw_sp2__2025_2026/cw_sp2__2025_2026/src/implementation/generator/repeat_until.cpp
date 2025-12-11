#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2024_2025            *
*                         file: repeat_until.cpp            *
*                                                  (draft!) *
*************************************************************/

#include "../../include/def.h"
#include "../../include/generator/generator.h"
#include "../../include/lexica/lexica.h"
#include "stdio.h"
#include "string.h"

unsigned char* makeRepeatCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_REPEAT);
	if (multitokenSize) {
		if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
			//
		}
		else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    ;\"%s\"\r\n", tokenStruct[MULTI_TOKEN_REPEAT][0]);
		}
		else if (generatorMode == C_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    //\"%s\"\r\n", tokenStruct[MULTI_TOKEN_REPEAT][0]);
		}

		lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize++] = **lastLexemInfoInTable;
		lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].ifvalue = (unsigned long long int)currBytePtr;

		if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
			//
		}
		else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
			currBytePtr += snprintf((char*)currBytePtr, 8192, "LABEL@REPEAT_%016llX:\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr);
		}
		else if (generatorMode == C_CODER_MODE) {
			currBytePtr += snprintf((char*)currBytePtr, 8192, "LABEL__REPEAT_%016llX:\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr);
		}

		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}

unsigned char* makeUntileCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) { // Or Ender!
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_UNTIL);
	if (multitokenSize
		&& lexemInfoTransformationTempStackSize
		&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, tokenStruct[MULTI_TOKEN_REPEAT][0], MAX_LEXEM_SIZE)
		) {
		if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
			//
		}
		else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    ;%s\r\n", tokenStruct[MULTI_TOKEN_UNTIL][0]);
		}
		else if (generatorMode == C_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    //%s\r\n", tokenStruct[MULTI_TOKEN_UNTIL][0]);
		}

		lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize++] = **lastLexemInfoInTable;

		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}

unsigned char* makeNullStatementAfterUntilCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_NULL_STATEMENT);
	if (multitokenSize) {
		if (lexemInfoTransformationTempStackSize < 2
			|| strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, tokenStruct[MULTI_TOKEN_UNTIL][0], MAX_LEXEM_SIZE)
			|| strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].lexemStr, tokenStruct[MULTI_TOKEN_REPEAT][0], MAX_LEXEM_SIZE)
			) {
			return currBytePtr;
		}
		if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
			const unsigned char code__cmp_eax_0[] = { 0x83, 0xF8, 0x00 };
			const unsigned char code__jnz_offset[] = { 0x0F, 0x85, 0x00, 0x00, 0x00, 0x00 };

			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__cmp_eax_0, 3);
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__jnz_offset, 6);
			*(unsigned int*)(currBytePtr - 4) = (unsigned int)((unsigned char*)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].ifvalue - currBytePtr);
		}
		else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    ;after cond expresion (after \"%s\" after \"%s\")\r\n", tokenStruct[MULTI_TOKEN_UNTIL][0], tokenStruct[MULTI_TOKEN_REPEAT][0]);
			//
			currBytePtr += sprintf((char*)currBytePtr, "    cmp eax, 0\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    jnz LABEL@REPEAT_%016llX\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].lexemStr);
		}
		else if (generatorMode == C_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    //after cond expresion (after \"%s\" after \"%s\")\r\n", tokenStruct[MULTI_TOKEN_UNTIL][0], tokenStruct[MULTI_TOKEN_REPEAT][0]);
			//
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    if(opTemp != 0) goto LABEL__REPEAT_%016llX\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].lexemStr);
		}

		lexemInfoTransformationTempStackSize -= 2;
		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}