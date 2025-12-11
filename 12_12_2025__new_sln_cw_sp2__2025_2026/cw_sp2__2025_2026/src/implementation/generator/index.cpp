#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2025_2026            *
*                         file: index.cpp                   *
*                                                  (draft!) *
*************************************************************/

#include "../../include/def.h"
#include "../../include/config.h"
#include "../../include/generator/generator.h"
#include "../../include/lexica/lexica.h"
#include "stdio.h"
#include "string.h"

unsigned char* makeIndexCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	unsigned char multitokenSize = 0;
	multitokenSize = !strncmp(lastLexemInfoInTable[0][0].lexemStr, "INDEX", MAX_LEXEM_SIZE);
	if (multitokenSize) {
		if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
		    const unsigned char code__mov_eax_stackTopByECX[] = { 0x8B, 0x01 };
			const unsigned char code__imul_eax_immediate[] = { 0x69, 0xC0, 0x00, 0x00, 0x00, 0x00 };
		    const unsigned char code__sub_ecx_4[] = { 0x83, 0xE9, 0x04 };
		    const unsigned char code__add_stackTopByECX_eax[] = { 0x01, 0x01 };
			//const unsigned char code__mov_eax_stackTopByECX[] = { 0x8B, 0x01 };
		    
		    currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_eax_stackTopByECX, 2);
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__imul_eax_immediate, 6);
			*(unsigned int*)(currBytePtr - 4) = ARRAY_INTERVAL;
		    currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__sub_ecx_4, 3);
		    currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__add_stackTopByECX_eax, 2);
		    currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_eax_stackTopByECX, 2);
		}
		else if(generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    ;\"INDEX\"\r\n");
			currBytePtr += sprintf((char*)currBytePtr, "    mov eax, dword ptr[ecx]\r\n");
			currBytePtr += sprintf((char*)currBytePtr, "    imul eax, %d\r\n", ARRAY_INTERVAL);
			currBytePtr += sprintf((char*)currBytePtr, "    sub ecx, 4\r\n");
			currBytePtr += sprintf((char*)currBytePtr, "    add dword ptr[ecx], eax\r\n");
			currBytePtr += sprintf((char*)currBytePtr, "    mov eax, dword ptr[ecx]\r\n");
		}
		else if (generatorMode == C_CODER_MODE) {
			currBytePtr += sprintf((char*)currBytePtr, "\r\n");
			currBytePtr += snprintf((char*)currBytePtr, 8192, "    //\"INDEX\"\r\n");
			currBytePtr += sprintf((char*)currBytePtr, "    opTemp = opStack[opStackIndex - 1] += %d * opStack[opStackIndex--]);\r\n", ARRAY_INTERVAL);
		}

		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}