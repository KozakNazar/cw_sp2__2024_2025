#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2024_2025            *
*                         file: input.cpp                   *
*                                                  (draft!) *
*************************************************************/

#include "../../include/def.h"
#include "../../include/generator/generator.h"
#include "../../include/lexica/lexica.h"
#include "stdio.h"

unsigned char* makeGetCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_INPUT);
	if (multitokenSize) {
		if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
			const unsigned char code__mov_eax_stackTopByECX[] = { 0x8B, 0x01 };
			const unsigned char code__mov_edx_address[] = { 0xBA, 0x00, 0x00, 0x00, 0x00 };
			const unsigned char code__add_edx_esi[] = { 0x03, 0xD6 };
			const unsigned char code__push_ecx[] = { 0x51 };
			//const unsigned char code__push_ebx[] = { 0x53 };
			const unsigned char code__push_esi[] = { 0x56 };
			const unsigned char code__push_edi[] = { 0x57 };
			const unsigned char code__call_edx[] = { 0xFF, 0xD2 };
			const unsigned char code__pop_edi[] = { 0x5F };
			const unsigned char code__pop_esi[] = { 0x5E };
			//const unsigned char code__pop_ebx[] = { 0x5B };
			const unsigned char code__pop_ecx[] = { 0x59 };
			const unsigned char code__mov_ebx_valueByAdrressInECX[] = { 0x8B, 0x19 };
			const unsigned char code__sub_ecx_4[] = { 0x83, 0xE9, 0x04 };
			const unsigned char code__add_ebx_edi[] = { 0x33, 0xDF };
			const unsigned char code__mov_stackTopByEBX_eax[] = { 0x89, 0x03 };
			const unsigned char code__mov_ecx_edi[] = { 0x8B, 0xCF };
			const unsigned char code__add_ecx_24576[] = { 0x81, 0xC1, 0x00, 0x60, 0x00, 0x00 };

			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_eax_stackTopByECX, 2);
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_edx_address, 5);
			*(unsigned int*)&(currBytePtr[-4]) = (unsigned int)getProcOffset;
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__add_edx_esi, 2);
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__push_ecx, 1);
			//currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__push_ebx, 1);
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__push_esi, 1);
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__push_edi, 1);
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__call_edx, 2);
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__pop_edi, 1);
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__pop_esi, 1);
			//currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__pop_ebx, 1);
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__pop_ecx, 1);
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_ebx_valueByAdrressInECX, 2);
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__sub_ecx_4, 3);
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__add_ebx_edi, 2);
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_stackTopByEBX_eax, 2);
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_ecx_edi, 2);
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__add_ecx_24576, 6);
		}
		else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    ;\"%s\"\r\n", tokenStruct[MULTI_TOKEN_INPUT][0]);
			//
			currBytePtr += sprintf((char*)currBytePtr, "    mov eax, dword ptr[ecx]\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    mov edx, 0%08Xh\r\n", (unsigned int)getProcOffset);
			currBytePtr += sprintf((char*)currBytePtr, "    add edx, esi\r\n");
			currBytePtr += sprintf((char*)currBytePtr, "    push ecx\r\n");
			currBytePtr += sprintf((char*)currBytePtr, "    ;push ebx\r\n");
			currBytePtr += sprintf((char*)currBytePtr, "    push esi\r\n");
			currBytePtr += sprintf((char*)currBytePtr, "    push edi\r\n");
			currBytePtr += sprintf((char*)currBytePtr, "    call edx\r\n");
			currBytePtr += sprintf((char*)currBytePtr, "    pop edi\r\n");
			currBytePtr += sprintf((char*)currBytePtr, "    pop esi\r\n");
			currBytePtr += sprintf((char*)currBytePtr, "    ;pop ebx\r\n");
			currBytePtr += sprintf((char*)currBytePtr, "    pop ecx\r\n");
			currBytePtr += sprintf((char*)currBytePtr, "    mov ebx, dword ptr[ecx]\r\n");
			currBytePtr += sprintf((char*)currBytePtr, "    sub ecx, 4\r\n");
			currBytePtr += sprintf((char*)currBytePtr, "    add ebx, edi\r\n");
			currBytePtr += sprintf((char*)currBytePtr, "    mov dword ptr [ebx], eax\r\n");
			currBytePtr += sprintf((char*)currBytePtr, "    mov ecx, edi ; reset second stack\r\n");
			currBytePtr += sprintf((char*)currBytePtr, "    add ecx, 24576 ; reset second stack\r\n");
		}
		else if (generatorMode == C_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    //\"%s\"\r\n", tokenStruct[MULTI_TOKEN_INPUT][0]);
			currBytePtr += sprintf((char*)currBytePtr, "    (void)scanf_s(\"%%d\", &opTemp);\r\n");
			currBytePtr += sprintf((char*)currBytePtr, "    data[opStack[opStackIndex]] = opTemp, opStackIndex = 0;\r\n");
		}

		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}