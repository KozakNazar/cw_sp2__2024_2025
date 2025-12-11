#define _CRT_SECURE_NO_WARNINGS
// TODO: CHANGE BY fRESET() TO END
/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2024_2025            *
*                         file: generator.cpp               *
*                                                  (draft!) *
*************************************************************/

//#define IDENTIFIER_LEXEME_TYPE 2
//#define VALUE_LEXEME_TYPE 4
//#define VALUE_SIZE 4

#ifndef __cplusplus
#define bool int
#define false 0
#define true 1
#endif

#include "../../../src/include/def.h"
#include "../../../src/include/config.h"
#include "../../../src/include/generator/generator.h"
#include "../../../src/include/lexica/lexica.h"
#include "../../../src/include/syntax/syntax.h"
#include "../../../src/include/semantics/semantics.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define DEBUG_MODE_BY_ASSEMBLY
//#define C_CODER_MODE                   0x01
//#define ASSEMBLY_X86_WIN32_CODER_MODE  0x02
//#define OBJECT_X86_WIN32_CODER_MODE    0x04
//#define MACHINE_CODER_MODE             0x08
//
//unsigned char generatorMode = MACHINE_CODER_MODE;

#define MAX_TEXT_SIZE 8192
#define MAX_GENERATED_TEXT_SIZE (MAX_TEXT_SIZE * 6)
#define GENERATED_TEXT_SIZE_ 32768
//#define GENERATED_TEXT_SIZE (MAX_TEXT_SIZE % MAX_GENERATED_TEXT_SIZE) // ?


#define SUCCESS_STATE 0



#define MAX_OUTTEXT_SIZE (8*8192*1024)
unsigned char outText[MAX_OUTTEXT_SIZE] = ""; // !!!
#define MAX_TEXT_SIZE 8192
#define MAX_WORD_COUNT (MAX_TEXT_SIZE / 5)
#define MAX_LEXEM_SIZE 1024

struct LabelOffsetInfo {
	char labelStr[MAX_LEXEM_SIZE];
	unsigned char* labelBytePtr;
	// TODO: ...
};
struct LabelOffsetInfo labelsOffsetInfoTable[MAX_WORD_COUNT] = { { "", NULL/*, 0, 0*/ } };
struct LabelOffsetInfo* lastLabelOffsetInfoInTable = labelsOffsetInfoTable; // first for begin

struct GotoPositionInfo { // TODO: by Index
	char labelStr[MAX_LEXEM_SIZE];
	unsigned char* gotoInstructionPositionPtr;
	// TODO: ...
};
struct GotoPositionInfo gotoPositionsInfoTable[MAX_WORD_COUNT] = { { "", NULL/*, 0, 0*/ } }; // TODO: by Index
struct GotoPositionInfo* lastGotoPositionInfoInTable = gotoPositionsInfoTable; // first for begin

////////////////////////////////

//#include "src/include/generator/generator.h"

//unsigned char generatorMode = MACHINE_CODER_MODE;

char* tokenStruct[MAX_TOKEN_STRUCT_ELEMENT_COUNT][MAX_TOKEN_STRUCT_ELEMENT_PART_COUNT] = { NULL };

INIT_TOKEN_STRUCT_NAME();

unsigned char detectMultiToken(struct LexemInfo* lexemInfoTable, enum TokenStructName tokenStructName) {
	if (lexemInfoTable == NULL) {
		return false;
	}

	if (!strncmp(lexemInfoTable[0].lexemStr, tokenStruct[tokenStructName][0], MAX_LEXEM_SIZE)
		&& (tokenStruct[tokenStructName][1] == NULL || tokenStruct[tokenStructName][1][0] == '\0' || !strncmp(lexemInfoTable[1].lexemStr, tokenStruct[tokenStructName][1], MAX_LEXEM_SIZE))
		&& (tokenStruct[tokenStructName][2] == NULL || tokenStruct[tokenStructName][2][0] == '\0' || !strncmp(lexemInfoTable[2].lexemStr, tokenStruct[tokenStructName][2], MAX_LEXEM_SIZE))
		&& (tokenStruct[tokenStructName][3] == NULL || tokenStruct[tokenStructName][3][0] == '\0' || !strncmp(lexemInfoTable[3].lexemStr, tokenStruct[tokenStructName][3], MAX_LEXEM_SIZE))) {

		return !!(tokenStruct[tokenStructName][0] != NULL && tokenStruct[tokenStructName][0][0] != '\0')
			 + !!(tokenStruct[tokenStructName][1] != NULL && tokenStruct[tokenStructName][1][0] != '\0')
			 + !!(tokenStruct[tokenStructName][2] != NULL && tokenStruct[tokenStructName][2][0] != '\0')
			 + !!(tokenStruct[tokenStructName][3] != NULL && tokenStruct[tokenStructName][3][0] != '\0')
			;
	}
	else {
		return 0;
	}
}

unsigned char createMultiToken(struct LexemInfo** lexemInfoTable, enum TokenStructName tokenStructName) {
	if (lexemInfoTable == NULL || *lexemInfoTable == NULL) {
		return false;
	}

	if (tokenStruct[tokenStructName][0] != NULL && tokenStruct[tokenStructName][0][0] != '\0') {
		strncpy(lexemInfoTable[0][0].lexemStr, tokenStruct[tokenStructName][0], MAX_LEXEM_SIZE);
		lexemInfoTable[0][0].lexemId = 0;
		lexemInfoTable[0][0].tokenType = 0;
		lexemInfoTable[0][0].ifvalue = 0;
		lexemInfoTable[0][0].row = ~0;
		lexemInfoTable[0][0].col = ~0;

		++* lexemInfoTable;
	}
	else {
		return 0;
	}
	if (tokenStruct[tokenStructName][1] != NULL && tokenStruct[tokenStructName][1][0] != '\0') {
		strncpy((*lexemInfoTable)->lexemStr, tokenStruct[tokenStructName][1], MAX_LEXEM_SIZE);
		lexemInfoTable[0][0].lexemId = 0;
		lexemInfoTable[0][0].tokenType = 0;
		lexemInfoTable[0][0].ifvalue = 0;
		lexemInfoTable[0][0].row = ~0;
		lexemInfoTable[0][0].col = ~0;
		++* lexemInfoTable;
	}
	else {
		return 1;
	}
	if (tokenStruct[tokenStructName][2] != NULL && tokenStruct[tokenStructName][2][0] != '\0') {
		strncpy((*lexemInfoTable)->lexemStr, tokenStruct[tokenStructName][2], MAX_LEXEM_SIZE);
		lexemInfoTable[0][0].lexemId = 0;
		lexemInfoTable[0][0].tokenType = 0;
		lexemInfoTable[0][0].ifvalue = 0;
		lexemInfoTable[0][0].row = ~0;
		lexemInfoTable[0][0].col = ~0;
		++* lexemInfoTable;
	}
	else {
		return 2;
	}
	if (tokenStruct[tokenStructName][3] != NULL && tokenStruct[tokenStructName][3][0] != '\0') {
		strncpy((*lexemInfoTable)->lexemStr, tokenStruct[tokenStructName][3], MAX_LEXEM_SIZE);
		lexemInfoTable[0][0].lexemId = 0;
		lexemInfoTable[0][0].tokenType = 0;
		lexemInfoTable[0][0].ifvalue = 0;
		lexemInfoTable[0][0].row = ~0;
		lexemInfoTable[0][0].col = ~0;
		++* lexemInfoTable;
	}
	else {
		return 3;
	}

	return 4;
}


//#define MAX_ACCESSORY_STACK_SIZE 128
struct NonContainedLexemInfo lexemInfoTransformationTempStack[MAX_ACCESSORY_STACK_SIZE];
unsigned long long int lexemInfoTransformationTempStackSize = 0;

//


//unsigned long long int getVariableOffset(char* identifierStr) {
//	for (unsigned long long int index = 0; identifierIdsTable[index][0] != '\0'; ++index) {
//		if (!strncmp(identifierIdsTable[index], identifierStr, MAX_LEXEM_SIZE)) {
//			return START_DATA_OFFSET + sizeof(CODEGEN_DATA_TYPE) * index;
//		}
//	}
//
//	return OUT_DATA_OFFSET;
//}

unsigned char* outBytes2Code(unsigned char* currBytePtr, unsigned char* fragmentFirstBytePtr, unsigned long long int bytesCout) {
	for (; bytesCout--; *currBytePtr++ = *fragmentFirstBytePtr++);
	return currBytePtr;
}

unsigned char* makeEndProgramCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
		const unsigned char code__xor_eax_eax[] = { 0x33, 0xC0 };
		const unsigned char code__ret[] = { 0xC3 };

		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__xor_eax_eax, 2);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__ret, 1);
	}
	else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
		currBytePtr += sprintf((char*)currBytePtr, "\r\n");
		//currBytePtr += sprintf((char*)currBytePtr, "imul ebp, 4\r\n");
		//currBytePtr += sprintf((char*)currBytePtr, "add esp, ebp\r\n");
		//currBytePtr += sprintf((char*)currBytePtr, "xor ebp, ebp;\r\n");

		currBytePtr += sprintf((char*)currBytePtr, "    xor eax, eax\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    ret\r\n");

		currBytePtr += sprintf((char*)currBytePtr, "\r\n\r\n");

		currBytePtr += sprintf((char*)currBytePtr, "end start\r\n");

		currBytePtr += sprintf((char*)currBytePtr, "\r\n\r\n");
	}
	else if (generatorMode == C_CODER_MODE) {
		currBytePtr += sprintf((char*)currBytePtr, "\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    return 0;\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "}");
	}

	return currBytePtr;
}

unsigned char* makeTitle(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
		//
	}
	else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
		currBytePtr += sprintf((char*)currBytePtr, ".686\r\n");
		currBytePtr += sprintf((char*)currBytePtr, ".model flat, stdcall\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "option casemap : none\r\n");
	}
	else if (generatorMode == C_CODER_MODE) {
		currBytePtr += sprintf((char*)currBytePtr, "#define _CRT_SECURE_NO_WARNINGS\r\n\r\n");
		//currBytePtr += sprintf((char*)currBytePtr, ".model flat, stdcall\r\n");
		//currBytePtr += sprintf((char*)currBytePtr, "option casemap : none\r\n");
	}

	return currBytePtr;
}

unsigned char* makeDependenciesDeclaration(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
		//
	}
	else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
		currBytePtr += sprintf((char*)currBytePtr, "\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "GetStdHandle proto STDCALL, nStdHandle : DWORD\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "ExitProcess proto STDCALL, uExitCode : DWORD\r\n");
		currBytePtr += sprintf((char*)currBytePtr, ";MessageBoxA PROTO hwnd : DWORD, lpText : DWORD, lpCaption : DWORD, uType : DWORD\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "ReadConsoleA proto STDCALL, hConsoleInput : DWORD, lpBuffer : DWORD, nNumberOfCharsToRead : DWORD, lpNumberOfCharsRead : DWORD, lpReserved : DWORD\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "WriteConsoleA proto STDCALL, hConsoleOutput : DWORD, lpBuffert : DWORD, nNumberOfCharsToWrite : DWORD, lpNumberOfCharsWritten : DWORD, lpReserved : DWORD\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "wsprintfA PROTO C : VARARG\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "GetConsoleMode PROTO STDCALL, hConsoleHandle:DWORD, lpMode : DWORD\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "SetConsoleMode PROTO STDCALL, hConsoleHandle:DWORD, dwMode : DWORD\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "ENABLE_LINE_INPUT EQU 0002h\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "ENABLE_ECHO_INPUT EQU 0004h\r\n");
	}
	else if (generatorMode == C_CODER_MODE) {
		currBytePtr += sprintf((char*)currBytePtr, "#include \"stdio.h\"\r\n\r\n");
	}

#ifdef DEBUG_MODE_BY_ASSEMBLY

#endif

	return currBytePtr;
}

unsigned char* makeDataSection(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
		//
	}
	else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
		currBytePtr += sprintf((char*)currBytePtr, "\r\n");
		currBytePtr += sprintf((char*)currBytePtr, ".data\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    data_start db 32768 dup (0)\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    ;title_msg db \"Output:\", 0\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    valueTemp_msg db 256 dup(0)\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    valueTemp_fmt db \"%%d\", 10, 13, 0\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    ;NumberOfCharsWritten dd 0\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    hConsoleInput dd 0\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    hConsoleOutput dd 0\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    buffer db 128 dup(0)\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    readOutCount dd ?\r\n");
	}
	else if (generatorMode == C_CODER_MODE) {
		currBytePtr += sprintf((char*)currBytePtr, "int data[8192] = {0};\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "int contextStack[8192] = {0}, contextStackIndex = 0;\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "int opStack[8192] = {0}, opStackIndex = 0, opTemp = 0;\r\n"); 
		currBytePtr += sprintf((char*)currBytePtr, "int lastBindDataIndex = 0;\r\n");
	}

	return currBytePtr;
}

unsigned char* makeBeginProgramCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
		//
	}
	else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
		currBytePtr += sprintf((char*)currBytePtr, "\r\n");
		currBytePtr += sprintf((char*)currBytePtr, ".code\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "start:\r\n");
	}
	else if (generatorMode == C_CODER_MODE) {
		currBytePtr += sprintf((char*)currBytePtr, "\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "int main() {\r\n");
	}

	return currBytePtr;
}

unsigned char* makeInitCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	//	unsigned char code__call_NexInstructionLabel[]          = { 0xE8, 0x00, 0x00, 0x00, 0x00 };      
	//	                                                                                                 
	//	unsigned char code__pop_esi[]                           = { 0x5E };                              
	//	unsigned char code__sub_esi_5[]                         = { 0x83, 0xEE, 0x05 };                  
	//	unsigned char code__mov_edi_esi[]                       = { 0x8B, 0xFE };                        
	//	unsigned char code__add_edi_dataOffsetMinusCodeOffset[] = { 0xE8, 0xC7, 0x00, 0x00, 0x00, 0x00 }; 
	//	//unsigned char code__xor_ebp_ebp[]                       = { 0x33, 0xED };                     
	//	unsigned char code__mov_ecx_edi[]                       = { 0x8B, 0xCF };                       
	//	unsigned char code__add_ecx_512[]                       = { 0x81, 0xC1, 0x00, 0x02, 0x00, 0x00 };
	//	unsigned char code__jmp_initConsole[] = { 0xEB, 0x7C };
	//
	//	currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__call_NexInstructionLabel, 5);
	//	currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__pop_esi, 1);
	//	currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__sub_esi_5, 3);
	//	currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_edi_esi, 2);
	//	currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__add_edi_dataOffsetMinusCodeOffset, 6);
	//	*(unsigned int *)(currBytePtr - 4) = dataOffsetMinusCodeOffset;
	//	//currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__xor_ebp_ebp, 2);
	//	currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_ecx_edi, 2);
	//	currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__add_ecx_512, 6);

	if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
		//
	}
	else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
		currBytePtr += sprintf((char*)currBytePtr, "\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    db 0E8h, 00h, 00h, 00h, 00h; call NexInstruction\r\n");
		currBytePtr += sprintf((char*)currBytePtr, ";NexInstruction:\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    pop esi\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    sub esi, 5\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    mov edi, esi\r\n");//printf("    mov edi, offset data_start\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    add edi, 0%08Xh\r\n", (int)dataOffsetMinusCodeOffset);
		//currBytePtr += sprintf((char*)currBytePtr, "    xor ebp, ebp\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    mov ecx, edi\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    add ecx, 24576\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    jmp initConsole\r\n");

		currBytePtr += sprintf((char*)currBytePtr, "    putProc PROC\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        push eax\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        push offset valueTemp_fmt\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        push offset valueTemp_msg\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        call wsprintfA\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        add esp, 12\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        ;push 40h\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        ;push offset title_msg\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        ;push offset valueTemp_msg;\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        ;push 0\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        ;call MessageBoxA\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        push 0\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        push 0; offset NumberOfCharsWritten\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        push eax; NumberOfCharsToWrite\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        push offset valueTemp_msg\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        push hConsoleOutput\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        call WriteConsoleA\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        ret\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    putProc ENDP\r\n");

		currBytePtr += sprintf((char*)currBytePtr, "\r\n\r\n");

		//currBytePtr += sprintf((char*)currBytePtr, "    getProc PROC\r\n");
		//currBytePtr += sprintf((char*)currBytePtr, "        push eax\r\n");
		//currBytePtr += sprintf((char*)currBytePtr, "        push offset valueTemp_fmt\r\n");
		//currBytePtr += sprintf((char*)currBytePtr, "        push offset valueTemp_msg\r\n");
		//currBytePtr += sprintf((char*)currBytePtr, "        call wsprintfA\r\n");
		//currBytePtr += sprintf((char*)currBytePtr, "        add esp, 12\r\n");
		//currBytePtr += sprintf((char*)currBytePtr, "\r\n");
		//currBytePtr += sprintf((char*)currBytePtr, "        push 40h\r\n");
		//currBytePtr += sprintf((char*)currBytePtr, "        push offset title_msg\r\n");
		//currBytePtr += sprintf((char*)currBytePtr, "        push offset valueTemp_msg;\r\n");
		//currBytePtr += sprintf((char*)currBytePtr, "        push 0\r\n");
		//currBytePtr += sprintf((char*)currBytePtr, "        call MessageBoxA\r\n");
		//currBytePtr += sprintf((char*)currBytePtr, "\r\n");
		//currBytePtr += sprintf((char*)currBytePtr, "        ret\r\n");
		//currBytePtr += sprintf((char*)currBytePtr, "    getProc ENDP\r\n");

		currBytePtr += sprintf((char*)currBytePtr, "    getProc PROC\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        push ebp\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        mov ebp, esp\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        push 0\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        push offset readOutCount\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        push 15\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        push offset buffer + 1\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        push hConsoleInput\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        call ReadConsoleA\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        lea esi, offset buffer\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        add esi, readOutCount\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        sub esi, 2\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        call string_to_int\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        mov esp, ebp\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        pop ebp\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        ret\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    getProc ENDP\r\n");

		currBytePtr += sprintf((char*)currBytePtr, "\r\n");

		currBytePtr += sprintf((char*)currBytePtr, "    string_to_int PROC\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    ;  input: ESI - string\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    ; output: EAX - value\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        xor eax, eax\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        mov ebx, 1\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        xor ecx, ecx\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "convert_loop :\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        movzx ecx, byte ptr[esi]\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        cmp ecx, '+'\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        jz done\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        cmp ecx, '-'\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        jz neg_and_done\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        test ecx, ecx\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        jz done\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        sub ecx, '0'\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        imul ecx, ebx\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        add eax, ecx\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        imul ebx, ebx, 10\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        dec esi\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        jmp convert_loop\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "neg_and_done:\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        neg eax\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "done:\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "        ret\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    string_to_int ENDP\r\n");

		currBytePtr += sprintf((char*)currBytePtr, "\r\n");

		currBytePtr += sprintf((char*)currBytePtr, "    initConsole:\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    push -10\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    call GetStdHandle\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    mov hConsoleInput, eax\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    push -11\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    call GetStdHandle\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    mov hConsoleOutput, eax\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    \r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    ;push ecx\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    ;push ebx\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    ;push esi\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    ;push edi\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    ;push offset mode\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    ;push hConsoleInput\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    ;call GetConsoleMode\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    ;mov ebx, eax\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    ;or ebx, ENABLE_LINE_INPUT \r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    ;or ebx, ENABLE_ECHO_INPUT\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    ;push ebx\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    ;push hConsoleInput\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    ;call SetConsoleMode\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    ;pop edi\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    ;pop esi\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    ;pop ebx\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    ;pop ecx\r\n");
	}
	else if (generatorMode == C_CODER_MODE) {
	    //currBytePtr += sprintf((char*)currBytePtr, "    int data[8192] = {0};\r\n");
	    //currBytePtr += sprintf((char*)currBytePtr, "    int contextStack[8192] = {0}, contextStackIndex = 0;\r\n");
	    //currBytePtr += sprintf((char*)currBytePtr, "    int opStack[8192] = {0}, opStackIndex = 0, opTemp = 0;;\r\n");
	    //currBytePtr += sprintf((char*)currBytePtr, "    int lastBindDataIndex = 0;\r\n");
		//
		currBytePtr += sprintf((char*)currBytePtr, "    contextStackIndex = 0;\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    opStackIndex = 0;\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    opTemp = 0;\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    lastBindDataIndex = 0;\r\n");
	}

#ifdef DEBUG_MODE_BY_ASSEMBLY


#endif

	return currBytePtr;
}

//
#include "../../../src/include/preparer/preparer.h"
//
//
#include "../../../src/include/generator/bitwise_not.h"
#include "../../../src/include/generator/bitwise_and.h"
#include "../../../src/include/generator/bitwise_or.h"
#include "../../../src/include/generator/not.h"
#include "../../../src/include/generator/and.h"
#include "../../../src/include/generator/or.h"
//		  
#include "../../../src/include/generator/add.h"
#include "../../../src/include/generator/sub.h"
#include "../../../src/include/generator/mul.h"
#include "../../../src/include/generator/div.h"
#include "../../../src/include/generator/mod.h" 
//
#include "../../../src/include/generator/null_statement.h"
#include "../../../src/include/generator/operand.h"
#include "../../../src/include/generator/input.h"
#include "../../../src/include/generator/output.h"
#include "../../../src/include/generator/equal.h"
#include "../../../src/include/generator/not_equal.h"
#include "../../../src/include/generator/less.h"
#include "../../../src/include/generator/greater.h"
#include "../../../src/include/generator/less_or_equal.h"
#include "../../../src/include/generator/greater_or_equal.h"
#include "../../../src/include/generator/rlbind.h"
#include "../../../src/include/generator/lrbind.h"
#include "../../../src/include/generator/index.h"
#include "../../../src/include/generator/index_to_value.h"
#include "../../../src/include/generator/goto_label.h"
#include "../../../src/include/generator/if_then_block.h"
#include "../../../src/include/generator/else_if_then_block.h"
#include "../../../src/include/generator/else_block.h"
#include "../../../src/include/generator/for_nonblockandblock.h"
#include "../../../src/include/generator/while_block.h"
#include "../../../src/include/generator/repeat_until.h"
//		  
#include "../../../src/include/generator/semicolon.h"
//
#include "../../../src/include/generator/block.h"

unsigned char* initMake(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	//return currBytePtr;
	unsigned long long int lastDataSectionLexemIndex = getPostDataSectionLexemIndex(*lastLexemInfoInTable, &grammar);
	if(lastDataSectionLexemIndex == ~0) {
		printf("Error: bad section!\r\n");
		exit(0);
	}

	labelInfoTable.clear(); /* It's not pretty. TODO: change it. */

	*lastLexemInfoInTable += lastDataSectionLexemIndex;
	return currBytePtr;
}

unsigned char* makeSaveHWStack(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
		const unsigned char code__mov_ebp_esp[] = { 0x8B, 0xEC };

		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_ebp_esp, 2);
	}
	else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
		currBytePtr += sprintf((char*)currBytePtr, "\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    ;hw stack save(save esp)\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    mov ebp, esp\r\n");
	}
	else if (generatorMode == C_CODER_MODE) {
		//
	}

	return currBytePtr;
}

unsigned char* makeResetHWStack(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {
		const unsigned char code__mov_esp_ebp[] = { 0x8B, 0xE5 };

		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_esp_ebp, 2);
	}
	else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {
		currBytePtr += sprintf((char*)currBytePtr, "\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    ;hw stack reset(restore esp)\r\n");
		currBytePtr += sprintf((char*)currBytePtr, "    mov esp, ebp\r\n");
	}
	else if (generatorMode == C_CODER_MODE) {
		//
	}

#ifdef DEBUG_MODE_BY_ASSEMBLY


#endif

	return currBytePtr;
}

unsigned char* noMake(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr) {
	if (!strncmp((*lastLexemInfoInTable)->lexemStr, T_NAME_0, MAX_LEXEM_SIZE)
		|| !strncmp((*lastLexemInfoInTable)->lexemStr, T_DATA_0, MAX_LEXEM_SIZE)
		|| !strncmp((*lastLexemInfoInTable)->lexemStr, T_BODY_0, MAX_LEXEM_SIZE)
		|| !strncmp((*lastLexemInfoInTable)->lexemStr, T_DATA_TYPE_0, MAX_LEXEM_SIZE)
		|| !strncmp((*lastLexemInfoInTable)->lexemStr, T_COMA_0, MAX_LEXEM_SIZE)
		|| !strncmp((*lastLexemInfoInTable)->lexemStr, T_BEGIN_0, MAX_LEXEM_SIZE)
		|| !strncmp((*lastLexemInfoInTable)->lexemStr, T_END_0, MAX_LEXEM_SIZE)
		) {

		return ++ * lastLexemInfoInTable, currBytePtr;
	}

	return currBytePtr;
}

unsigned char* createPattern() {

	return NULL;
}

unsigned char* getObjectCodeBytePtr(unsigned char* baseBytePtr, unsigned char generatorMode) {

	if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {

	}
	else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {

	}
	else if (generatorMode == C_CODER_MODE) {

	}

	return baseBytePtr + baseOperationObjectOffset;
}

unsigned char* getImageCodeBytePtr(unsigned char* baseBytePtr, unsigned char generatorMode) {

	if (generatorMode == MACHINE_X86_WIN32_CODER_MODE) {

	}
	else if (generatorMode == ASSEMBLY_X86_WIN32_CODER_MODE) {

	}
	else if (generatorMode == C_CODER_MODE) {

	}

	return baseBytePtr + baseOperationOffset;
}

unsigned char* makeCode(struct LexemInfo** lastLexemInfoInTable/*TODO:...*/, unsigned char* currBytePtr, unsigned char generatorMode) { // TODO:...
	currBytePtr = makeTitle(lastLexemInfoInTable, currBytePtr, generatorMode);
	currBytePtr = makeDependenciesDeclaration(lastLexemInfoInTable, currBytePtr, generatorMode);

	currBytePtr = makeDataSection(lastLexemInfoInTable, currBytePtr, generatorMode);

	currBytePtr = makeBeginProgramCode(lastLexemInfoInTable, currBytePtr, generatorMode);
	memset(tempStrFor_123, 0, sizeof(tempStrFor_123)); // not necessary
	lexemInfoTransformationTempStackSize = 0;
	tempStrForCurrIndex = 0;
	for (int index = 0; true && index < MAX_ACCESSORY_STACK_SIZE; ++index) {
		/* !TODO: WHILE! */(lexemInfoTransformationTempStack[index].lexemStr = tempStrFor_123 + tempStrForCurrIndex)[0] = '\0';
		tempStrForCurrIndex += 32;// MAX_LEXEM_SIZE;
		lexemInfoTransformationTempStack[index].lexemId = 0; // not necessary
		lexemInfoTransformationTempStack[index].tokenType = 0; // not necessary
		lexemInfoTransformationTempStack[index].ifvalue = 0; // not necessary
		lexemInfoTransformationTempStack[index].row = ~0; // not necessary
		lexemInfoTransformationTempStack[index].col = ~0; // not necessary
	}
	currBytePtr = makeInitCode(lastLexemInfoInTable, currBytePtr, generatorMode);
	currBytePtr = initMake(lastLexemInfoInTable, currBytePtr, generatorMode);
	currBytePtr = makeSaveHWStack(lastLexemInfoInTable, currBytePtr, generatorMode);
	for (struct LexemInfo* lastLexemInfoInTable_; lastLexemInfoInTable_ = *lastLexemInfoInTable, (*lastLexemInfoInTable)->lexemStr[0] != '\0';) {

		LABEL_GOTO_LABELE_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);

		//
		IF_THEN_BLOCK_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		ELSE_IF_THEN_BLOCK_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		ELSE_BLOCK_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		//

		//currBytePtr = makeForCycleCode(lastLexemInfoInTable, currBytePtr);
		//currBytePtr = makeToOrDowntoCycleCode(lastLexemInfoInTable, currBytePtr);
		//currBytePtr = makeDoCycleCode(lastLexemInfoInTable, currBytePtr);
		//currBytePtr = makeSemicolonAfterForCycleCode(lastLexemInfoInTable, currBytePtr);
		FOR_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);

		//
		WHILE_BLOCK_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		//

		//
		REPEAT_UNTIL_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		//

		//if (lastLexemInfoInTable_ == *lastLexemInfoInTable) currBytePtr = makeValueCode(lastLexemInfoInTable, currBytePtr);
		//if (lastLexemInfoInTable_ == *lastLexemInfoInTable) currBytePtr = makeIdentifierCode(lastLexemInfoInTable, currBytePtr);
		OPERAND_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);

		//if (lastLexemInfoInTable_ == *lastLexemInfoInTable) currBytePtr = makeNotCode(lastLexemInfoInTable, currBytePtr);
		BITWISE_NOT_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		BITWISE_AND_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		BITWISE_OR_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		NOT_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		AND_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		OR_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);

		EQUAL_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		NOT_EQUAL_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		LESS_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		GREATER_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		LESS_OR_EQUAL_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		GREATER_OR_EQUAL_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);

		//if (lastLexemInfoInTable_ == *lastLexemInfoInTable) currBytePtr = makeAddCode(lastLexemInfoInTable, currBytePtr);
		//if (lastLexemInfoInTable_ == *lastLexemInfoInTable) currBytePtr = makeSubCode(lastLexemInfoInTable, currBytePtr);
		//if (lastLexemInfoInTable_ == *lastLexemInfoInTable) currBytePtr = makeMulCode(lastLexemInfoInTable, currBytePtr);
		//if (lastLexemInfoInTable_ == *lastLexemInfoInTable) currBytePtr = makeDivCode(lastLexemInfoInTable, currBytePtr);
		//if (lastLexemInfoInTable_ == *lastLexemInfoInTable) currBytePtr = makeModCode(lastLexemInfoInTable, currBytePtr);
		ADD_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		SUB_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		MUL_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		DIV_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		MOD_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);

		//if (lastLexemInfoInTable_ == *lastLexemInfoInTable) currBytePtr = makeRightToLeftBindCode(lastLexemInfoInTable, currBytePtr);
		//if (lastLexemInfoInTable_ == *lastLexemInfoInTable) currBytePtr = makeLeftToRightBindCode(lastLexemInfoInTable, currBytePtr);
		INPUT_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		OUTPUT_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);

		//if (lastLexemInfoInTable_ == *lastLexemInfoInTable) currBytePtr = makeGetCode(lastLexemInfoInTable, currBytePtr);
		//if (lastLexemInfoInTable_ == *lastLexemInfoInTable) currBytePtr = makePutCode(lastLexemInfoInTable, currBytePtr);
		RLBIND_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		LRBIND_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);

		INDEX_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		INDEX_TO_VALUE_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);

		///* (1) Ignore phase*/if (lastLexemInfoInTable_ == *lastLexemInfoInTable) currBytePtr = makeSemicolonAfterNonContextCode(lastLexemInfoInTable, currBytePtr);
		///* (2) Ignore phase*/if (lastLexemInfoInTable_ == *lastLexemInfoInTable) currBytePtr = makeSemicolonIgnoreContextCode(lastLexemInfoInTable, currBytePtr);
		NON_CONTEXT_SEMICOLON_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);		
		NON_CONTEXT_BLOCK_CODER(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);
		NON_CONTEXT_NULL_STATEMENT(lastLexemInfoInTable_, lastLexemInfoInTable, currBytePtr, generatorMode, NULL);

		if (lastLexemInfoInTable_ == *lastLexemInfoInTable) {
			currBytePtr = noMake(lastLexemInfoInTable, currBytePtr);
		}

		if (lastLexemInfoInTable_ == *lastLexemInfoInTable) {
			printf("\r\nError in the code generator! \"%s\" - unexpected token!\r\n", (*lastLexemInfoInTable)->lexemStr);
			exit(0);
		}

	}

	currBytePtr = makeResetHWStack(lastLexemInfoInTable, currBytePtr, generatorMode);
	currBytePtr = makeEndProgramCode(lastLexemInfoInTable, currBytePtr, generatorMode);

	return currBytePtr;
}

//unsigned char outCode[GENERATED_TEXT_SIZE] = { '\0' };
void viewCode(unsigned char* outCodePtr, unsigned long long int outCodePrintSize, unsigned char align) {
	printf("\r\n;            +0x0 +0x1 +0x2 +0x3 +0x4 +0x5 +0x6 +0x7 +0x8 +0x9 +0xA +0xB +0xC +0xD +0xE +0xF ");
	printf("\r\n;0x00000000: ");
	unsigned long long int outCodePrintIndex = outCodePrintSize - 1;
	for (unsigned long long int index = 0; index <= outCodePrintIndex;) {
		printf("0x%02X ", outCodePtr[index]);
		if (!(++index % align)) {
			unsigned long long int indexMinus16 = index - align;
			do {
				//printf("0x%02X ", outCodePtr[index]);
				if (outCodePtr[indexMinus16] >= 32 && outCodePtr[indexMinus16] <= 126) {
					printf("%c", outCodePtr[indexMinus16]);
				}
				else {
					printf(" ");
					//printf("%2c", 32);
				}
			} while (++indexMinus16 % align);

			printf("\r\n;0x%08X: ", (unsigned int)index);
		}
	}
}