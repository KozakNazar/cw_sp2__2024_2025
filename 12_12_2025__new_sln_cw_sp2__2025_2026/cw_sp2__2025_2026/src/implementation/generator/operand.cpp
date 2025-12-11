#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2024_2025            *
*                         file: identifier_or_value.cpp     *
*                                                  (draft!) *
*************************************************************/

#include "../../include/def.h"
#include "../../include/generator/generator.h"
#include "../../include/lexica/lexica.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

unsigned char* makeValueCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	if ((*lastLexemInfoInTable)->tokenType == VALUE_LEXEME_TYPE) {
		if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
			const unsigned char code__add_ecx_4[] = { 0x83, 0xC1, 0x04 };
			const unsigned char code__mov_eax_value[] = { 0xB8, 0x00, 0x00, 0x00, 0x00 };
			unsigned char code__mov_toAddrFromECX_eax[] = { 0x89, 0x01 };
			//		const unsigned char* valueParts = (const unsigned char*)&(*lastLexemInfoInTable)->ifvalue;
			//		code__mov_toAddrFromECX_value[2] = valueParts[0];
			//		code__mov_toAddrFromECX_value[3] = valueParts[1];
			//		code__mov_toAddrFromECX_value[4] = valueParts[2];
			//		code__mov_toAddrFromECX_value[5] = valueParts[3];

			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__add_ecx_4, 3);
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_eax_value, 5);
			*(unsigned int*)(currBytePtr - 4) = (unsigned int)(*lastLexemInfoInTable)->ifvalue;
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_toAddrFromECX_eax, 2);
		}
		else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    ;\"%lld\"\r\n", (*lastLexemInfoInTable)->ifvalue);
			//
			currBytePtr += sprintf((char*)currBytePtr, "    add ecx, 4\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    mov eax, 0%08Xh\r\n", (int)(*lastLexemInfoInTable)->ifvalue);
			currBytePtr += sprintf((char*)currBytePtr, "    mov dword ptr [ecx], eax\r\n");
		}
		else if (generatorMode == C_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    //\"%lld\"\r\n", (*lastLexemInfoInTable)->ifvalue);
			//
			currBytePtr += sprintf((char*)currBytePtr, "    opStack[++opStackIndex] = opTemp = 0x%08X;\r\n", (int)(*lastLexemInfoInTable)->ifvalue);
		}

		return ++ * lastLexemInfoInTable, currBytePtr;
	}

	return currBytePtr;
}

unsigned char* makeIdentifierCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	if ((*lastLexemInfoInTable)->tokenType == IDENTIFIER_LEXEME_TYPE) {
		bool findComplete = false;
		unsigned long long int variableIndex = 0;
		for (; identifierIdsTable[variableIndex][0] != '\0'; ++variableIndex) {
			if (!strncmp((*lastLexemInfoInTable)->lexemStr, identifierIdsTable[variableIndex], MAX_LEXEM_SIZE)) {
				findComplete = true;
				break;
			}
		}
		if (!findComplete) {
			printf("\r\nError!\r\n");
			exit(0);
		}

		variableIndex *= VALUE_SIZE;

		if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
			unsigned char code__mov_eax_edi[] = { 0x8B, 0xC7 };
			unsigned char code__add_eax_variableOffsetInDataSection[] = { 0x05, 0x00, 0x00, 0x00, 0x00 };
			const unsigned char code__mov_eax_valueByAdrressInEAX[] = { 0x8B, 0x00 };
			const unsigned char code__add_ecx_4[] = { 0x83, 0xC1, 0x04 };
			const unsigned char code__mov_toAddrFromECX_eax[] = { 0x89, 0x01 };
			const unsigned char* variableIndexValueParts = (const unsigned char*)&variableIndex;
			code__add_eax_variableOffsetInDataSection[1] = variableIndexValueParts[0];
			code__add_eax_variableOffsetInDataSection[2] = variableIndexValueParts[1];
			code__add_eax_variableOffsetInDataSection[3] = variableIndexValueParts[2];
			code__add_eax_variableOffsetInDataSection[4] = variableIndexValueParts[3];

			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_eax_edi, 2);
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__add_eax_variableOffsetInDataSection, 5);
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_eax_valueByAdrressInEAX, 2);
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__add_ecx_4, 3);
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_toAddrFromECX_eax, 2);
		}
		else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    ;\"%s\"\r\n", (*lastLexemInfoInTable)->lexemStr);
			//
			currBytePtr += sprintf((char*)currBytePtr, "    mov eax, edi\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    add eax, 0%08Xh\r\n", (int)variableIndex);
			currBytePtr += sprintf((char*)currBytePtr, "    mov eax, dword ptr[eax]\r\n");
			currBytePtr += sprintf((char*)currBytePtr, "    add ecx, 4\r\n");
			currBytePtr += sprintf((char*)currBytePtr, "    mov dword ptr [ecx], eax\r\n");
		}
		else if (generatorMode == C_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    //\"%s\"\r\n", (*lastLexemInfoInTable)->lexemStr);
			//
			currBytePtr += sprintf((char*)currBytePtr, "    opStack[++opStackIndex] = opTemp = data[0x%08X];\r\n", (int)variableIndex);
		}

		return ++ * lastLexemInfoInTable, currBytePtr;
	}

	return currBytePtr;
}