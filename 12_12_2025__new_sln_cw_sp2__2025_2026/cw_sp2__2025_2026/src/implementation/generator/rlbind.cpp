#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2024_2025            *
*                         file: rlbind.cpp                  *
*                                                  (draft!) *
*************************************************************/

#include "../../include/def.h"
#include "../../include/generator/generator.h"
#include "../../include/lexica/lexica.h"
#include "stdio.h"

unsigned char* makeRightToLeftBindCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_RLBIND);
	if (multitokenSize) {
		if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
			const unsigned char code__mov_eax_stackTopByECX[] = { 0x8B, 0x01 };
			const unsigned char code__mov_ebx_stackTopByECXMinus4[] = { 0x8B, 0x59, 0xFC };
			const unsigned char code__sub_ecx_8[] = { 0x83, 0xE9, 0x08 };
			const unsigned char code__add_ebx_edi[] = { 0x03, 0xDF };
			const unsigned char code__mov_addrFromEBX_eax[] = { 0x89, 0x03 };
			const unsigned char code__mov_ecx_edi[] = { 0x8B, 0xCF };
			const unsigned char code__add_ecx_24576[] = { 0x81, 0xC1, 0x00, 0x60, 0x00, 0x00 };

			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_eax_stackTopByECX, 2);
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_ebx_stackTopByECXMinus4, 3);
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__sub_ecx_8, 3);
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__add_ebx_edi, 2);
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_addrFromEBX_eax, 2);
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_ecx_edi, 2);
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__add_ecx_24576, 6);
		}
		else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    ;\"%s\"\r\n", tokenStruct[MULTI_TOKEN_RLBIND][0]);
			//
			currBytePtr += sprintf((char*)currBytePtr, "    mov eax, dword ptr[ecx]\r\n");
			currBytePtr += sprintf((char*)currBytePtr, "    mov ebx, dword ptr[ecx - 4]\r\n");
			currBytePtr += sprintf((char*)currBytePtr, "    sub ecx, 8\r\n");
			currBytePtr += sprintf((char*)currBytePtr, "    add ebx, edi\r\n");
			currBytePtr += sprintf((char*)currBytePtr, "    mov dword ptr [ebx], eax\r\n");
			currBytePtr += sprintf((char*)currBytePtr, "    mov ecx, edi ; reset second stack\r\n");
			currBytePtr += sprintf((char*)currBytePtr, "    add ecx, 24576 ; reset second stack\r\n");
		}
		else if (generatorMode == C_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    //\"%s\"\r\n", tokenStruct[MULTI_TOKEN_RLBIND][0]);
			currBytePtr += sprintf((char*)currBytePtr, "    lastBindDataIndex = opStack[opStackIndex - 1];\r\n");
			currBytePtr += sprintf((char*)currBytePtr, "    data[lastBindDataIndex] = opTemp = opStack[opStackIndex], opStackIndex = 0;\r\n");
		}

		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}