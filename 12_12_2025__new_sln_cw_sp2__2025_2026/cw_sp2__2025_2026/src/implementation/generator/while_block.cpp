#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2024_2025            *
*                         file: while.cpp                   *
*                                                  (draft!) *
*************************************************************/

#include "../../include/def.h"
#include "../../include/generator/generator.h"
#include "../../include/lexica/lexica.h"
#include "stdio.h"
#include "string.h"

unsigned char* makeWhileCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_WHILE);
	if (multitokenSize) {
		lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize++] = **lastLexemInfoInTable;
		lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize++] = **lastLexemInfoInTable;
		lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].ifvalue = (unsigned long long int)currBytePtr;

		if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
			//
		}
		else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    ;\"%s\"\r\n", tokenStruct[MULTI_TOKEN_WHILE][0]);
			//
			currBytePtr += snprintf((char*)currBytePtr, 8192, "LABEL@WHILE_%016llX:\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].lexemStr);
		}
		else if (generatorMode == C_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    //\"%s\"\r\n", tokenStruct[MULTI_TOKEN_WHILE][0]);
			//
			currBytePtr += snprintf((char*)currBytePtr, 8192, "LABEL__WHILE_%016llX:\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].lexemStr);
		}

		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}

unsigned char* makeBlockBeginWhileCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_BEGIN_BLOCK);
	if (multitokenSize) {
		if (lexemInfoTransformationTempStackSize < 2
			|| strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].lexemStr, tokenStruct[MULTI_TOKEN_WHILE][0], MAX_LEXEM_SIZE)
			|| strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, tokenStruct[MULTI_TOKEN_WHILE][0], MAX_LEXEM_SIZE)
			) {
			return currBytePtr;
		}
		if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
			const unsigned char code__cmp_eax_0[] = { 0x83, 0xF8, 0x00 };
			const unsigned char code__jz_offset[] = { 0x0F, 0x84, 0x00, 0x00, 0x00, 0x00 };

			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__cmp_eax_0, 3);
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__jz_offset, 6);
		}
		else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    ;after cond expresion (after \"%s\")\r\n", tokenStruct[MULTI_TOKEN_WHILE][0]);
		}
		else if (generatorMode == C_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    //after cond expresion (after \"%s\")\r\n", tokenStruct[MULTI_TOKEN_WHILE][0]);
		}

		lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].ifvalue = (unsigned long long int)(currBytePtr - 4);

		//lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize++] = lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1];
		//OLD//strncpy(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize++ - 1].lexemStr, MAX_LEXEM_SIZE);
		strcpy(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize].lexemStr, "CE_WHILE");
		++lexemInfoTransformationTempStackSize;
		//lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize++] = lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1];
		//OLD//strncpy(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize++ - 1].lexemStr, MAX_LEXEM_SIZE);
		strcpy(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize].lexemStr, "CE_WHILE");
		++lexemInfoTransformationTempStackSize;

		if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
			//
		}
		else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "    cmp eax, 0\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    jz LABEL@AFTER_WHILE_%016llX\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 3].lexemStr);
		}
		else if (generatorMode == C_CODER_MODE) {
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    if (opTemp == 0) goto LABEL__AFTER_WHILE_%016llX;\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 3].lexemStr);
		}

		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}

unsigned char* make0LevelContinueOr1LevelIfContinueWhileCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	// No suport multi-if-continue: TODO: add a check for this to the semantics
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_CONTINUE_WHILE);
	if (multitokenSize) {
		if (
			lexemInfoTransformationTempStackSize >= 6
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, tokenStruct[MULTI_TOKEN_THEN_BLOCK][0], MAX_LEXEM_SIZE)
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].lexemStr, tokenStruct[MULTI_TOKEN_IF][0], MAX_LEXEM_SIZE)
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 5].lexemStr, tokenStruct[MULTI_TOKEN_WHILE][0], MAX_LEXEM_SIZE)
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 6].lexemStr, tokenStruct[MULTI_TOKEN_WHILE][0], MAX_LEXEM_SIZE)
			) {

			if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
				const unsigned char code__jmp_offset[] = { 0xE9, 0x00, 0x00, 0x00, 0x00 }; // jmp

				currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__jmp_offset, 5);
			}
			else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
				currBytePtr += sprintf((char*)currBytePtr, "\r\n");
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    ;continue while (in \"then\"-part of %s-operator)\r\n", tokenStruct[MULTI_TOKEN_WHILE][0]);
			}
			else if (generatorMode == C_CODER_MODE) {
				currBytePtr += sprintf((char*)currBytePtr, "\r\n");
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    //continue while (in \"then\"-part of %s-operator)\r\n", tokenStruct[MULTI_TOKEN_WHILE][0]);
			}

			//lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 4].ifvalue = (unsigned long long int)(currBytePtr - 4);
			if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
				*(unsigned int*)(currBytePtr - 4) = (unsigned int)((unsigned char*)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 6].ifvalue - currBytePtr);
			}
			strncpy(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 4].lexemStr, tokenStruct[MULTI_TOKEN_CONTINUE_WHILE][0], MAX_LEXEM_SIZE);

			if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
				//
			}
			else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    jmp LABEL@WHILE_%016llX\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 6].lexemStr);
			}
			else if (generatorMode == C_CODER_MODE) {
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    goto LABEL__WHILE_%016llX;\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 6].lexemStr);
			}

			return *lastLexemInfoInTable += multitokenSize, currBytePtr;
		}
		else if ( // ELSE_IF__
			lexemInfoTransformationTempStackSize >= 7
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, tokenStruct[MULTI_TOKEN_THEN_BLOCK][0], MAX_LEXEM_SIZE)
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].lexemStr, "IF", MAX_LEXEM_SIZE)
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 3].lexemStr, tokenStruct[MULTI_TOKEN_ELSE_IF][0], MAX_LEXEM_SIZE)
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 6].lexemStr, tokenStruct[MULTI_TOKEN_WHILE][0], MAX_LEXEM_SIZE)
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 7].lexemStr, tokenStruct[MULTI_TOKEN_WHILE][0], MAX_LEXEM_SIZE)
			) {

			if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
				const unsigned char code__jmp_offset[] = { 0xE9, 0x00, 0x00, 0x00, 0x00 }; // jmp

				currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__jmp_offset, 5);
			}
			else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
				currBytePtr += sprintf((char*)currBytePtr, "\r\n");
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    ;continue while (in \"then\"-part of %s-operator)\r\n", tokenStruct[MULTI_TOKEN_WHILE][0]);
			}
			else if (generatorMode == C_CODER_MODE) {
				currBytePtr += sprintf((char*)currBytePtr, "\r\n");
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    //continue while (in \"then\"-part of %s-operator)\r\n", tokenStruct[MULTI_TOKEN_WHILE][0]);
			}

			//lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 4].ifvalue = (unsigned long long int)(currBytePtr - 4);
			if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
				*(unsigned int*)(currBytePtr - 4) = (unsigned int)((unsigned char*)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 7].ifvalue - currBytePtr);
			}
			strncpy(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 5].lexemStr, tokenStruct[MULTI_TOKEN_CONTINUE_WHILE][0], MAX_LEXEM_SIZE);

			if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
				//
			}
			else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    jmp LABEL@WHILE_%016llX\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 7].lexemStr);
			}
			else if (generatorMode == C_CODER_MODE) {
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    goto LABEL__WHILE_%016llX;\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 7].lexemStr);
			}

			return *lastLexemInfoInTable += multitokenSize, currBytePtr;
		}
		else if (
			lexemInfoTransformationTempStackSize >= 5
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, tokenStruct[MULTI_TOKEN_ELSE_BLOCK][0], MAX_LEXEM_SIZE)
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 4].lexemStr, tokenStruct[MULTI_TOKEN_WHILE][0], MAX_LEXEM_SIZE)
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 5].lexemStr, tokenStruct[MULTI_TOKEN_WHILE][0], MAX_LEXEM_SIZE)
			) {
			if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
				const unsigned char code__jmp_offset[] = { 0xE9, 0x00, 0x00, 0x00, 0x00 }; // jmp

				currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__jmp_offset, 5);
			}
			else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
				currBytePtr += sprintf((char*)currBytePtr, "\r\n");
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    ;continue while (in \"else\"-part of %s-operator)\r\n", tokenStruct[MULTI_TOKEN_WHILE][0]);
			}
			else if (generatorMode == C_CODER_MODE) {
				currBytePtr += sprintf((char*)currBytePtr, "\r\n");
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    //continue while (in \"else\"-part of %s-operator)\r\n", tokenStruct[MULTI_TOKEN_WHILE][0]);
			}

			//lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 3].ifvalue = (unsigned long long int)(currBytePtr - 4);
			if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
				*(unsigned int*)(currBytePtr - 4) = (unsigned int)((unsigned char*)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 5].ifvalue - currBytePtr);
			}
			strncpy(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 3].lexemStr, tokenStruct[MULTI_TOKEN_CONTINUE_WHILE][0], MAX_LEXEM_SIZE);

			if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
				//
			}
			else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    jmp LABEL@WHILE_%016llX\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 5].lexemStr);
			}
			else if (generatorMode == C_CODER_MODE) {
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    goto LABEL__WHILE_%016llX;\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 5].lexemStr);
			}

			return *lastLexemInfoInTable += multitokenSize, currBytePtr;
		}
		else if (lexemInfoTransformationTempStackSize >= 4
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 3].lexemStr, tokenStruct[MULTI_TOKEN_WHILE][0], MAX_LEXEM_SIZE)
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 4].lexemStr, tokenStruct[MULTI_TOKEN_WHILE][0], MAX_LEXEM_SIZE)
			) {
			if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
				const unsigned char code__jmp_offset[] = { 0xE9, 0x00, 0x00, 0x00, 0x00 }; // jmp

				currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__jmp_offset, 5);
			}
			else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
				currBytePtr += sprintf((char*)currBytePtr, "\r\n");
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    ;continue while (in \"%s\")\r\n", tokenStruct[MULTI_TOKEN_WHILE][0]);
			}
			else if (generatorMode == C_CODER_MODE) {
				currBytePtr += sprintf((char*)currBytePtr, "\r\n");
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    //continue while (in \"%s\")\r\n", tokenStruct[MULTI_TOKEN_WHILE][0]);
			}

			//lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].ifvalue = (unsigned long long int)(currBytePtr - 4);
			if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
				*(unsigned int*)(currBytePtr - 4) = (unsigned int)((unsigned char*)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 4].ifvalue - currBytePtr);
			}
			strncpy(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].lexemStr, tokenStruct[MULTI_TOKEN_CONTINUE_WHILE][0], MAX_LEXEM_SIZE);

			if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
				//
			}
			else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    jmp LABEL@WHILE_%016llX\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 4].lexemStr);
			}
			else if (generatorMode == C_CODER_MODE) {
				currBytePtr  += snprintf((char*)currBytePtr, 8192, "    goto LABEL__WHILE_%016llX;\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 4].lexemStr);
			}

			return *lastLexemInfoInTable += multitokenSize, currBytePtr;
		}
	}

	return currBytePtr;
}

unsigned char* make0LevelExitOr1LevelIfExitWhileCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	// No suport multi-if-exit: TODO: add a check for this to the semantics
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_EXIT_WHILE);
	if (multitokenSize) {
		if (
			lexemInfoTransformationTempStackSize >= 6
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, tokenStruct[MULTI_TOKEN_THEN_BLOCK][0], MAX_LEXEM_SIZE)
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].lexemStr, tokenStruct[MULTI_TOKEN_IF][0], MAX_LEXEM_SIZE)
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 5].lexemStr, tokenStruct[MULTI_TOKEN_WHILE][0], MAX_LEXEM_SIZE)
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 6].lexemStr, tokenStruct[MULTI_TOKEN_WHILE][0], MAX_LEXEM_SIZE)
			) {
			if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
				const unsigned char code__jmp_offset[] = { 0xE9, 0x00, 0x00, 0x00, 0x00 }; // jmp

				currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__jmp_offset, 5);
			}
			else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
				currBytePtr += sprintf((char*)currBytePtr, "\r\n");
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    ;exit while (in \"then\"-part of %s-operator)\r\n", tokenStruct[MULTI_TOKEN_WHILE][0]);
			}
			else if (generatorMode == C_CODER_MODE) {
				currBytePtr += sprintf((char*)currBytePtr, "\r\n");
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    //exit while (in \"then\"-part of %s-operator)\r\n", tokenStruct[MULTI_TOKEN_WHILE][0]);
			}

			lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 3].ifvalue = (unsigned long long int)(currBytePtr - 4);
			strncpy(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 3].lexemStr, tokenStruct[MULTI_TOKEN_EXIT_WHILE][0], MAX_LEXEM_SIZE);

			if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
				//
			}
			else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    jmp LABEL@AFTER_WHILE_%016llX\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 5].lexemStr);
			}
			else if (generatorMode == C_CODER_MODE) {
				currBytePtr  += snprintf((char*)currBytePtr, 8192, "    goto LABEL__AFTER_WHILE_%016llX;\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 5].lexemStr);
			}

			return *lastLexemInfoInTable += multitokenSize, currBytePtr;
		}
		else if ( // ELSE_IF__
			lexemInfoTransformationTempStackSize >= 7
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, tokenStruct[MULTI_TOKEN_THEN_BLOCK][0], MAX_LEXEM_SIZE)
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].lexemStr, "IF", MAX_LEXEM_SIZE)
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 3].lexemStr, tokenStruct[MULTI_TOKEN_ELSE_IF][0], MAX_LEXEM_SIZE)
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 6].lexemStr, tokenStruct[MULTI_TOKEN_WHILE][0], MAX_LEXEM_SIZE)
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 7].lexemStr, tokenStruct[MULTI_TOKEN_WHILE][0], MAX_LEXEM_SIZE)
			) {
			if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
				const unsigned char code__jmp_offset[] = { 0xE9, 0x00, 0x00, 0x00, 0x00 }; // jmp

				currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__jmp_offset, 5);
			}
			else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
				currBytePtr += sprintf((char*)currBytePtr, "\r\n");
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    ;exit while (in \"then\"-part of %s-operator)\r\n", tokenStruct[MULTI_TOKEN_WHILE][0]);
			}
			else if (generatorMode == C_CODER_MODE) {
				currBytePtr += sprintf((char*)currBytePtr, "\r\n");
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    //exit while (in \"then\"-part of %s-operator)\r\n", tokenStruct[MULTI_TOKEN_WHILE][0]);
			}

			lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 4].ifvalue = (unsigned long long int)(currBytePtr - 4);
			strncpy(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 4].lexemStr, tokenStruct[MULTI_TOKEN_EXIT_WHILE][0], MAX_LEXEM_SIZE);

			if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
				//
			}
			else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    jmp LABEL@AFTER_WHILE_%016llX\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 6].lexemStr);
			}
			else if (generatorMode == C_CODER_MODE) {
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    goto LABEL__AFTER_WHILE_%016llX;\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 6].lexemStr);
			}

			return *lastLexemInfoInTable += multitokenSize, currBytePtr;
		}
		else if (
			lexemInfoTransformationTempStackSize >= 5
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, tokenStruct[MULTI_TOKEN_ELSE_BLOCK][0], MAX_LEXEM_SIZE)
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 4].lexemStr, tokenStruct[MULTI_TOKEN_WHILE][0], MAX_LEXEM_SIZE)
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 5].lexemStr, tokenStruct[MULTI_TOKEN_WHILE][0], MAX_LEXEM_SIZE)
			) {
			if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
				const unsigned char code__jmp_offset[] = { 0xE9, 0x00, 0x00, 0x00, 0x00 }; // jmp

				currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__jmp_offset, 5);
			}
			else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
				currBytePtr += sprintf((char*)currBytePtr, "\r\n");
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    ;exit while (in \"else\"-part of %s-operator)\r\n", tokenStruct[MULTI_TOKEN_WHILE][0]);
			}
			else if (generatorMode == C_CODER_MODE) {
				currBytePtr += sprintf((char*)currBytePtr, "\r\n");
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    //exit while (in \"else\"-part of %s-operator)\r\n", tokenStruct[MULTI_TOKEN_WHILE][0]);
			}

			lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].ifvalue = (unsigned long long int)(currBytePtr - 4);
			strncpy(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].lexemStr, tokenStruct[MULTI_TOKEN_EXIT_WHILE][0], MAX_LEXEM_SIZE);

			if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
				//
			}
			else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    jmp LABEL@AFTER_WHILE_%016llX\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 4].lexemStr);
			}
			else if (generatorMode == C_CODER_MODE) {
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    goto LABEL__AFTER_WHILE_%016llX;\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 4].lexemStr);
			}

			return *lastLexemInfoInTable += multitokenSize, currBytePtr;
		}
		else if (lexemInfoTransformationTempStackSize >= 4
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 3].lexemStr, tokenStruct[MULTI_TOKEN_WHILE][0], MAX_LEXEM_SIZE)
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 4].lexemStr, tokenStruct[MULTI_TOKEN_WHILE][0], MAX_LEXEM_SIZE)
			) {
			if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
				const unsigned char code__jmp_offset[] = { 0xE9, 0x00, 0x00, 0x00, 0x00 }; // jmp

				currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__jmp_offset, 5);
			}
			else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
				currBytePtr += sprintf((char*)currBytePtr, "\r\n");
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    ;exit while (in \"%s\")\r\n", tokenStruct[MULTI_TOKEN_WHILE][0]);
			}
			else if (generatorMode == C_CODER_MODE) {
				currBytePtr += sprintf((char*)currBytePtr, "\r\n");
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    //exit while (in \"%s\")\r\n", tokenStruct[MULTI_TOKEN_WHILE][0]);
			}

			lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].ifvalue = (unsigned long long int)(currBytePtr - 4);
			strncpy(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, tokenStruct[MULTI_TOKEN_EXIT_WHILE][0], MAX_LEXEM_SIZE);

			if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
				//
			}
			else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    jmp LABEL@AFTER_WHILE_%016llX\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 3].lexemStr);
			}
			else if (generatorMode == C_CODER_MODE) {
				currBytePtr += snprintf((char*)currBytePtr, 8192, "    goto LABEL__AFTER_WHILE_%016llX;\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 3].lexemStr);
			}

			return *lastLexemInfoInTable += multitokenSize, currBytePtr;
		}
	}

	return currBytePtr;
}

unsigned char* makePostWhileCode_(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode, unsigned char){
//	if (!strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].lexemStr, tokenStruct[MULTI_TOKEN_CONTINUE_WHILE][0], MAX_LEXEM_SIZE)) {
//		*(unsigned int*)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].ifvalue = (unsigned int)((unsigned char*)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].ifvalue - currBytePtr - 4);
//	}

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
		*(unsigned int*)(currBytePtr - 4) = (unsigned int)((unsigned char*)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 4].ifvalue - currBytePtr);
		*(unsigned int*)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 3].ifvalue = (unsigned int)(currBytePtr - (unsigned char*)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 3].ifvalue - 4);
		if (!strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, tokenStruct[MULTI_TOKEN_EXIT_WHILE][0], MAX_LEXEM_SIZE)) {
			*(unsigned int*)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].ifvalue = (unsigned int)(currBytePtr - (unsigned char*)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].ifvalue - 4);
		}
	}

	if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
		//
	}
	else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
		currBytePtr += snprintf((char*)currBytePtr, 8192, "    jmp LABEL@WHILE_%016llX\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 4].lexemStr);
		currBytePtr += snprintf((char*)currBytePtr, 8192, "LABEL@AFTER_WHILE_%016llX:\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 3].lexemStr);
	}
	else if (generatorMode == C_CODER_MODE) {
		currBytePtr += snprintf((char*)currBytePtr, 8192, "    goto LABEL__WHILE_%016llX;\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 4].lexemStr);
		currBytePtr += snprintf((char*)currBytePtr, 8192, "LABEL__AFTER_WHILE_%016llX:\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 3].lexemStr);
	}

	return currBytePtr;
}

unsigned char* makeEndWhileAfterWhileCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) { // Or Ender!
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_END_BLOCK);
	if (multitokenSize
		&& lexemInfoTransformationTempStackSize >= 4
		&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 3].lexemStr, tokenStruct[MULTI_TOKEN_WHILE][0], MAX_LEXEM_SIZE)
		&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 4].lexemStr, tokenStruct[MULTI_TOKEN_WHILE][0], MAX_LEXEM_SIZE)
		) {
		if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
			//
		}
		else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    ;end of while\r\n");
		}
		else if (generatorMode == C_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    //end of while\r\n");
		}

		currBytePtr = makePostWhileCode_(lastLexemInfoInTable, currBytePtr, generatorMode, 0);

		lexemInfoTransformationTempStackSize -= 4;
		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}