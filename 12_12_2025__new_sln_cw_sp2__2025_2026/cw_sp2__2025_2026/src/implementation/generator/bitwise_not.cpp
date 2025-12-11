#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2024_2025            *
*                         file: bitwise_not.cpp             *
*                                                  (draft!) *
*************************************************************/

#include "../../include/def.h"
#include "../../include/generator/generator.h"
#include "../../include/lexica/lexica.h"
#include "stdio.h"

unsigned char* makeBitwiseNotCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_BITWISE_NOT);
	if (multitokenSize) {
		if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
			const unsigned char code__not_stackTopByECX[] = { 0xF7, 0x11 };
			const unsigned char code__mov_eax_stackTopByECX[] = { 0x8B, 0x01 };

			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__not_stackTopByECX, 2);
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_eax_stackTopByECX, 3);
		}
		else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    ;\"%s\"\r\n", tokenStruct[MULTI_TOKEN_BITWISE_NOT][0]);
			//
			currBytePtr += sprintf((char*)currBytePtr, "    not dword ptr[ecx]\r\n");
			currBytePtr += sprintf((char*)currBytePtr, "    mov eax, dword ptr[ecx]\r\n");
		}
		else if (generatorMode == C_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    //\"%s\"\r\n", tokenStruct[MULTI_TOKEN_BITWISE_NOT][0]);
			currBytePtr += sprintf((char*)currBytePtr, "    opTemp = opStack[opStackIndex] = ~opStack[opStackIndex];\r\n");
		}

		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}