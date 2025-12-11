#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2024_2025            *
*                         file: for.cpp                     *
*                                                  (draft!) *
*************************************************************/

#include "../../include/def.h"
#include "../../include/generator/generator.h"
#include "../../include/lexica/lexica.h"
#include "stdio.h"
#include "string.h"

unsigned char* makeForCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_FOR);
	if (multitokenSize) {
		if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
			//
		}
		else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    ;\"%s\"\r\n", tokenStruct[MULTI_TOKEN_FOR][0]);
		}
		else if (generatorMode == C_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    //\"%s\"\r\n", tokenStruct[MULTI_TOKEN_FOR][0]);
		}

		lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize++] = **lastLexemInfoInTable;

		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}

unsigned char* makeToOrDowntoCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) { // TODO: add assemblyBytePtr
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_DOWNTO);
	bool toMode = false;
	if (!multitokenSize) {
		toMode = !!(multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_TO));
	}
	if (multitokenSize
		&&
		lexemInfoTransformationTempStackSize
		&&
		!strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, tokenStruct[MULTI_TOKEN_FOR][0], MAX_LEXEM_SIZE)
		) {
		if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
			const unsigned char code__dec_addrFromEBX[] = { 0xFF, 0x0B }; // dec dword ptr [ebx] // init
			const unsigned char code__inc_addrFromEBX[] = { 0xFF, 0x03 }; // inc dword ptr [ebx] // init
			const unsigned char code__push_ebx[] = { 0x53 };       // push ebx	

			if (toMode) {
				currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__dec_addrFromEBX, 2); // init
			}
			else {
				currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__inc_addrFromEBX, 2); // init
			}
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__push_ebx, 1);
		}
		else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
			if (toMode) {
				currBytePtr += sprintf((char*)currBytePtr, "\r\n");
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    ;\"%s\" (after \"%s\")\r\n", tokenStruct[MULTI_TOKEN_TO][0], tokenStruct[MULTI_TOKEN_FOR][0]);
			}
			else {
				currBytePtr += sprintf((char*)currBytePtr, "\r\n");
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    ;\"%s\" (after \"%s\")\r\n", tokenStruct[MULTI_TOKEN_DOWNTO][0], tokenStruct[MULTI_TOKEN_FOR][0]);
			}
		}
		else if (generatorMode == C_CODER_MODE) {
			if (toMode) {
				currBytePtr += sprintf((char*)currBytePtr, "\r\n");
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    //\"%s\" (after \"%s\")\r\n", tokenStruct[MULTI_TOKEN_TO][0], tokenStruct[MULTI_TOKEN_FOR][0]);
			}
			else {
				currBytePtr += sprintf((char*)currBytePtr, "\r\n");
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    //\"%s\" (after \"%s\")\r\n", tokenStruct[MULTI_TOKEN_DOWNTO][0], tokenStruct[MULTI_TOKEN_FOR][0]);
			}
		}

		lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize++] = **lastLexemInfoInTable;
		lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].ifvalue = (unsigned long long int)currBytePtr;

		if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
			//
		}
		else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
			if (toMode) {
				currBytePtr += sprintf((char*)currBytePtr, "    dec dword ptr [ebx]\r\n"); // start from (index - 1)
			}
			else {
				currBytePtr += sprintf((char*)currBytePtr, "    inc dword ptr [ebx]\r\n"); // start from (index + 1)
			}
			currBytePtr += sprintf((char*)currBytePtr, "    push ebx\r\n");
			if (toMode) {
				currBytePtr += snprintf((char*)currBytePtr, 8192, "LABEL@AFTER_TO_%016llX:\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr);
			}
			else {
				currBytePtr += snprintf((char*)currBytePtr, 8192, "LABEL@AFTER_DOWNTO_%016llX:\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr);
			}
		}
		else if (generatorMode == C_CODER_MODE) {
			if (toMode) {
				currBytePtr += sprintf((char*)currBytePtr, "    --data[lastBindDataIndex];\r\n"); // start from (index - 1)
			}
			else {
				currBytePtr += sprintf((char*)currBytePtr, "    ++data[lastBindDataIndex];\r\n"); // start from (index + 1)
			}
			currBytePtr += sprintf((char*)currBytePtr, "    contextStack[++contextStackIndex] = lastBindDataIndex;\r\n");
			if (toMode) {
				currBytePtr += snprintf((char*)currBytePtr, 8192, "LABEL__AFTER_TO_%016llX:\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr);
			}
			else {
				currBytePtr += snprintf((char*)currBytePtr, 8192, "LABEL__AFTER_DOWNTO_%016llX:\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr);
			}
		}

		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}

unsigned char* makeDoCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	bool blockMode = false;
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_DO);
	unsigned char multitokenSizeAddon = 0;
	if (multitokenSize) {
		multitokenSizeAddon = detectMultiToken(*lastLexemInfoInTable + multitokenSize, MULTI_TOKEN_BEGIN_BLOCK);
		if (multitokenSizeAddon) {
			blockMode = true;
			multitokenSize += multitokenSizeAddon;
		}
	}
	if (multitokenSize) {
		bool toMode = false;
		if (lexemInfoTransformationTempStackSize && !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, tokenStruct[MULTI_TOKEN_TO][0], MAX_LEXEM_SIZE)) {
			toMode = true;
		}
		else if (lexemInfoTransformationTempStackSize < 2
			|| strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, tokenStruct[MULTI_TOKEN_DOWNTO][0], MAX_LEXEM_SIZE)
			|| strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].lexemStr, tokenStruct[MULTI_TOKEN_FOR][0], MAX_LEXEM_SIZE)
			) {
			return currBytePtr;
		}
		if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
			const unsigned char code__mov_ebx_addrFromESP[] = { 0x8B, 0x1C, 0x24 };                   // mov ebx, dword ptr [esp]
			const unsigned char code__cmp_addrFromEBX_eax[] = { 0x39, 0x03 };                         // cmp dword ptr [ebx], eax
			const unsigned char code__jge_offset[] = { 0x0F, 0x8D, 0x00, 0x00, 0x00, 0x00 }; // jge ?? ?? ?? ??
			const unsigned char code__jle_offset[] = { 0x0F, 0x8E, 0x00, 0x00, 0x00, 0x00 }; // jle ?? ?? ?? ??

			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_ebx_addrFromESP, 3);
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__cmp_addrFromEBX_eax, 2);
			if (toMode) {
				currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__jge_offset, 6);
				lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].ifvalue = (unsigned long long int)(currBytePtr - 4);
			}
			else {
				currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__jle_offset, 6);
				lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].ifvalue = (unsigned long long int)(currBytePtr - 4);
			}
		}
		else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
			if (toMode) {
				currBytePtr += sprintf((char*)currBytePtr, "\r\n");
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    ;\"%s\" (after \"%s\" after \"%s\")\r\n", tokenStruct[MULTI_TOKEN_DO][0], tokenStruct[MULTI_TOKEN_TO][0], tokenStruct[MULTI_TOKEN_FOR][0]);
			}
			else {
				currBytePtr += sprintf((char*)currBytePtr, "\r\n");
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    ;\"%s\" (after \"%s\" after \"%s\")\r\n", tokenStruct[MULTI_TOKEN_DO][0], tokenStruct[MULTI_TOKEN_DOWNTO][0], tokenStruct[MULTI_TOKEN_FOR][0]);
			}
		}
		else if (generatorMode == C_CODER_MODE) {
			if (toMode) {
				currBytePtr += sprintf((char*)currBytePtr, "\r\n");
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    //\"%s\" (after \"%s\" after \"%s\")\r\n", tokenStruct[MULTI_TOKEN_DO][0], tokenStruct[MULTI_TOKEN_TO][0], tokenStruct[MULTI_TOKEN_FOR][0]);
			}
			else {
				currBytePtr += sprintf((char*)currBytePtr, "\r\n");
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    //\"%s\" (after \"%s\" after \"%s\")\r\n", tokenStruct[MULTI_TOKEN_DO][0], tokenStruct[MULTI_TOKEN_DOWNTO][0], tokenStruct[MULTI_TOKEN_FOR][0]);
			}
		}

		if (toMode) {
			lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].ifvalue = (unsigned long long int)(currBytePtr - 4);
		}
		else {
			lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].ifvalue = (unsigned long long int)(currBytePtr - 4);
		}

		if (blockMode) {
			lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize++] = (*lastLexemInfoInTable)[multitokenSize - multitokenSizeAddon];
		}
		else {
			lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize++] = (*lastLexemInfoInTable)[0];
		}

		if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
			const unsigned char code__inc_addrFromEBX[] = { 0xFF, 0x03 };                         // inc dword ptr [ebx]
			const unsigned char code__dec_addrFromEBX[] = { 0xFF, 0x0B };                         // dec dword ptr [ebx]

			if (toMode) {
				currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__inc_addrFromEBX, 2);
			}
			else {
				currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__dec_addrFromEBX, 2);
			}
		}
		else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "    mov ebx, dword ptr [esp]\r\n");
			currBytePtr += sprintf((char*)currBytePtr, "    cmp dword ptr [ebx], eax\r\n");
			if (toMode) {
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    jge LABEL@EXIT_FOR_%016llX\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 3].lexemStr);
				currBytePtr += sprintf((char*)currBytePtr, "    inc dword ptr [ebx]\r\n");
			}
			else {
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    jle LABEL@EXIT_FOR_%016llX\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 3].lexemStr);
				currBytePtr += sprintf((char*)currBytePtr, "    dec dword ptr [ebx]\r\n");
			}
		}
		else if (generatorMode == C_CODER_MODE) {
			if (toMode) {
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    if (data/*OLD: opStack*/[contextStack[contextStackIndex]] >= opTemp) goto LABEL__EXIT_FOR_%016llX;\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 3].lexemStr);
				currBytePtr += sprintf((char*)currBytePtr, "    ++data/*OLD: opStack*/[contextStack[contextStackIndex]];\r\n");
			}
			else {
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    if (data/*OLD: opStack*/[contextStack[contextStackIndex]] <= opTemp) goto LABEL__EXIT_FOR_%016llX;\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 3].lexemStr);
				currBytePtr += sprintf((char*)currBytePtr, "    --data/*OLD: opStack*/[contextStack[contextStackIndex]];\r\n");
			}
		}

		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}

unsigned char* makePostForCode_(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode, bool toMode) {
	if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
		const unsigned char code__jmp_offset[] = { 0xE9, 0x00, 0x00, 0x00, 0x00 };

		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__jmp_offset, 5);
	}
	else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
		//
	}
	else if (generatorMode == C_CODER_MODE) {
		//
	}

	if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
		*(unsigned int*)(currBytePtr - 4) = (unsigned int)((unsigned char*)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].ifvalue - currBytePtr);
		*(unsigned int*)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 3].ifvalue = (unsigned int)(currBytePtr - (unsigned char*)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 3].ifvalue - 4);
	}

	if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
		const unsigned char code__add_esp_4[] = { 0x83, 0xC4, 0x04 };

		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__add_esp_4, 3);
	}
	else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
		if (toMode) {
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    jmp LABEL@AFTER_TO_%016llX\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].lexemStr);
		}
		else {
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    jmp LABEL@AFTER_DOWNTO_%016llX\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].lexemStr);
		}
		currBytePtr += snprintf((char*)currBytePtr, 8192, "LABEL@EXIT_FOR_%016llX:\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 3].lexemStr);
		currBytePtr += sprintf((char*)currBytePtr, "    add esp, 4; add esp, 8\r\n");
	}
	else if (generatorMode == C_CODER_MODE) {
		if (toMode) {
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    goto LABEL__AFTER_TO_%016llX;\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].lexemStr);
		}
		else {
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    goto LABEL__AFTER_DOWNTO_%016llX;\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].lexemStr);
		}
		currBytePtr += snprintf((char*)currBytePtr, 8192, "LABEL__EXIT_FOR_%016llX:\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 3].lexemStr);
		currBytePtr += sprintf((char*)currBytePtr, "    --contextStackIndex;\r\n");
	}

	return currBytePtr;
}

unsigned char* makeSemicolonOrNullStatementOrEndBlockAfterForCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) { // Or Ender!
	bool toMode = false;
	bool blockMode = false;
	unsigned char multitokenSize = 0;
	if (!lexemInfoTransformationTempStackSize) {
		return currBytePtr;
	}
	if (!strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, tokenStruct[MULTI_TOKEN_BEGIN_BLOCK][0], MAX_LEXEM_SIZE)) {
		blockMode = true;
		multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_END_BLOCK);
	}
	else if (!strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, tokenStruct[MULTI_TOKEN_DO][0], MAX_LEXEM_SIZE)) {
		multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_SEMICOLON);
		if (!multitokenSize) multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_NULL_STATEMENT);
	}
	if (multitokenSize
		&&
		lexemInfoTransformationTempStackSize > 2
		&&
		!strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 3].lexemStr, tokenStruct[MULTI_TOKEN_FOR][0], MAX_LEXEM_SIZE)
		&& (
			!strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].lexemStr, tokenStruct[MULTI_TOKEN_DOWNTO][0], MAX_LEXEM_SIZE)
			||
			(toMode = !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].lexemStr, tokenStruct[MULTI_TOKEN_TO][0], MAX_LEXEM_SIZE))
			)		
		) {
		if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
			//
		}
		else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    ;\"%s\" (after \"%s\")\r\n", (*lastLexemInfoInTable)->lexemStr, tokenStruct[MULTI_TOKEN_FOR][0]);
		}
		else if (generatorMode == C_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    //\"%s\" (after \"%s\")\r\n", (*lastLexemInfoInTable)->lexemStr, tokenStruct[MULTI_TOKEN_FOR][0]);
		}

		currBytePtr = makePostForCode_(lastLexemInfoInTable, currBytePtr, generatorMode, toMode);

		lexemInfoTransformationTempStackSize -= 3;
		if (blockMode) { // no remove token after non-block "for"
			*lastLexemInfoInTable += multitokenSize;
		}
		else { // no remove token after non-block "for" and use recursion for possible multilevel "for"
			return makeSemicolonOrNullStatementOrEndBlockAfterForCycleCode(lastLexemInfoInTable, currBytePtr, generatorMode);
		}
		return currBytePtr;
	}

	return currBytePtr;
}