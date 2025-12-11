#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2024_2025            *
*                         file: mod.cpp                     *
*                                                  (draft!) *
*************************************************************/

#include "../../include/def.h"
#include "../../include/generator/generator.h"
#include "../../include/lexica/lexica.h"
#include "stdio.h"

unsigned char* makeModCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) { // task
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_MOD);
	if (multitokenSize) {
		if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
			const unsigned char code__mov_eax_stackTopByECXMinus4[] = { 0x8B, 0x41, 0xFC };
			const unsigned char code__cdq[] = { 0x99 };
			const unsigned char code__idiv_stackTopByECX[] = { 0xF7, 0x39 };
			const unsigned char code__sub_ecx_4[] = { 0x83, 0xE9, 0x04 };
			const unsigned char code__mov_eax_edx[] = { 0x8B, 0xC2 };
			const unsigned char code__mov_toAddrFromECX_eax[] = { 0x89, 0x01 };

			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_eax_stackTopByECXMinus4, 3);
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__cdq, 1);
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__idiv_stackTopByECX, 2);
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__sub_ecx_4, 3);
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_eax_edx, 2);
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_toAddrFromECX_eax, 2);
		}
		else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192,"    ;\"%s\"\r\n", tokenStruct[MULTI_TOKEN_MOD][0]);
			//
			currBytePtr += sprintf((char*)currBytePtr, "    mov eax, dword ptr[ecx - 4]\r\n");
			currBytePtr += sprintf((char*)currBytePtr, "    cdq\r\n");
			currBytePtr += sprintf((char*)currBytePtr, "    idiv dword ptr [ecx]\r\n");
			currBytePtr += sprintf((char*)currBytePtr, "    sub ecx, 4\r\n");
			currBytePtr += sprintf((char*)currBytePtr, "    mov eax, edx\r\n");
			currBytePtr += sprintf((char*)currBytePtr, "    mov dword ptr [ecx], eax\r\n");
		}
		else if (generatorMode == C_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    //\"%s\"\r\n", tokenStruct[MULTI_TOKEN_MOD][0]);
			currBytePtr += sprintf((char*)currBytePtr, "    opTemp = opStack[opStackIndex - 1] %%= opStack[opStackIndex]; --opStackIndex;\r\n");
		}

		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}