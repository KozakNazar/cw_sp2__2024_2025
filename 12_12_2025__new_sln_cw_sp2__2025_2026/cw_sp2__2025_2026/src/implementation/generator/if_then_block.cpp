#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2024_2025            *
*                         file: if_then.cpp                 *
*                                                  (draft!) *
*************************************************************/

#include "../../include/def.h"
#include "../../include/generator/generator.h"
#include "../../include/lexica/lexica.h"
#include "stdio.h"
#include "string.h"

unsigned char* makeIfCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_IF);
	//if (!multitokenSize 
	//	&& tokenStruct[MULTI_TOKEN_IF][1][0] == '('
	//	&& !strncmp((*lastLexemInfoInTable)->lexemStr, tokenStruct[MULTI_TOKEN_IF][0], MAX_LEXEM_SIZE)) {
	//	multitokenSize = 1;
	//}
	if (multitokenSize) {
		if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
			//
		}
		else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    ;\"%s\"\r\n", tokenStruct[MULTI_TOKEN_IF][0]);
		}
		else if (generatorMode == C_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    //\"%s\"\r\n", tokenStruct[MULTI_TOKEN_IF][0]);
		}

		lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize++] = **lastLexemInfoInTable;

		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}

unsigned char* makeThenBlockCodeAfterIfCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_THEN_BLOCK);
	//if (!multitokenSize && tokenStruct[MULTI_TOKEN_IF][1][0] == '(') {
	//	multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_NULL_STATEMENT);
	//}
	if (multitokenSize
		&& lexemInfoTransformationTempStackSize
		&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, tokenStruct[MULTI_TOKEN_IF][0], MAX_LEXEM_SIZE)
		&& (lexemInfoTransformationTempStackSize < 2 || strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].lexemStr, tokenStruct[MULTI_TOKEN_ELSE_IF][0], MAX_LEXEM_SIZE))
		) { 
		if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
			const unsigned char code__cmp_eax_0[] = { 0x83, 0xF8, 0x00 };
			const unsigned char code__jz_offset[] = { 0x0F, 0x84, 0x00, 0x00, 0x00, 0x00 };

			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__cmp_eax_0, 3);
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__jz_offset, 6);
		}
		else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    ;after cond expresion (after \"%s\")\r\n", tokenStruct[MULTI_TOKEN_IF][0]);
		}
		else if (generatorMode == C_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    //after cond expresion (after \"%s\")\r\n", tokenStruct[MULTI_TOKEN_IF][0]);
		}

		lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize++] = **lastLexemInfoInTable;
		/*The lexem info table will be changed and will need to be rebuilt. TODO: change the implementation!*/strncpy(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, tokenStruct[MULTI_TOKEN_THEN_BLOCK][0], MAX_LEXEM_SIZE);
		lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].ifvalue = (unsigned long long int)(currBytePtr - 4);

		if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
			//
		}
		else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "    cmp eax, 0\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    jz LABEL@AFTER_THEN_%016llX\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr);
		}
		else if (generatorMode == C_CODER_MODE) {
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    if (opTemp == 0) goto LABEL__AFTER_THEN_%016llX;\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr);
		}

		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}

unsigned char* makePostThenCodeAfterIfCode_(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
		const unsigned char code__mov_eax_1[] = { 0xB8, 0x01, 0x00, 0x00, 0x00 };

		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_eax_1, 5);

		*(unsigned int*)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].ifvalue = (unsigned int)(currBytePtr - (unsigned char*)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].ifvalue - 4);
	}
	else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
		currBytePtr += sprintf((char*)currBytePtr, "    mov eax, 1\r\n");
		currBytePtr += snprintf((char*)currBytePtr, 8192, "LABEL@AFTER_THEN_%016llX:\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr);
	}
	else if (generatorMode == C_CODER_MODE) {
		currBytePtr += sprintf((char*)currBytePtr, "    opTemp = 1;\r\n");
		currBytePtr += snprintf((char*)currBytePtr, 8192, "LABEL__AFTER_THEN_%016llX:\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr);
	}

	return currBytePtr;
}

unsigned char* makeEndBlockAfterThenCodeAfterIfCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) { // Or Ender!
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_END_BLOCK);
    //TODO: for non-block//unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_SEMICOLON);
	//TODO: for non-block//stack+ if (!multitokenSize) multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_NULL_STATEMENT);
	if (multitokenSize
		&&
		lexemInfoTransformationTempStackSize >= 2
		&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].lexemStr, tokenStruct[MULTI_TOKEN_IF][0], MAX_LEXEM_SIZE)
		&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, tokenStruct[MULTI_TOKEN_THEN_BLOCK][0], MAX_LEXEM_SIZE)
		&& (lexemInfoTransformationTempStackSize < 3 || strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 3].lexemStr, tokenStruct[MULTI_TOKEN_ELSE_IF][0], MAX_LEXEM_SIZE))
		) {
		if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
			//
		}
		else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    ;\"%s\" (after \"then\"-part of %s-operator)\r\n", tokenStruct[MULTI_TOKEN_SEMICOLON][0], tokenStruct[MULTI_TOKEN_IF][0]);
		}
		else if (generatorMode == C_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    //\"%s\" (after \"then\"-part of %s-operator)\r\n", tokenStruct[MULTI_TOKEN_SEMICOLON][0], tokenStruct[MULTI_TOKEN_IF][0]);
		}

		currBytePtr = makePostThenCodeAfterIfCode_(lastLexemInfoInTable, currBytePtr, generatorMode);

		lexemInfoTransformationTempStackSize -= 2;
		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}