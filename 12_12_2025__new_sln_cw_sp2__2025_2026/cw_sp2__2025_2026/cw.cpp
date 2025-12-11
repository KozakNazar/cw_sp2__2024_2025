#define _CRT_SECURE_NO_WARNINGS  // for using sscanf in VS
/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2025_2026            *
*                         file: cw.cpp                      *
*                                                  (draft!) *
*************************************************************/
//#pragma comment(linker, "/STACK:516777216")

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <windows.h>
//#include <winbase.h>
//#include <winuser.h>
//#include <shlobj.h>
//#include <shlwapi.h>
//#include <objbase.h>
#elif defined(__linux__) || defined(__unix__) || defined(__APPLE__)
//
#else
//#   error "Unknown system"
#endif

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
//#include "conio.h"

//#include "locale.h"

#include <direct.h>

#include <fstream>
#include <iostream>
#include <algorithm> //
#include <iterator>
#include <regex>

#include "src/include/def.h"
#include "src/include/config.h"

#include "src/include/cli/cli.h"
//bool reSetDefaultInputFileName_ = 
//strcpy(parameters[INPUT_FILENAME_WITH_EXTENSION_PARAMETER], "../test_programs/file1.cwl")
//!= NULL;
#include "src/include/lexica/lexica.h"

#include "src/include/syntax/syntax.h"
#include "src/include/semantics/semantics.h"
#include "src/include/preparer/preparer.h"
#include "src/include/generator/generator.h"

struct LexemInfo lexemesInfoTableTemp[MAX_WORD_COUNT]; // = { { "", 0, 0, 0 } };
struct LexemInfo* lastLexemInfoInTableTemp = lexemesInfoTableTemp; // first for begin

// unsigned char new_code[8 * 1024 * 1024] = { '\0' }; //

unsigned char tempCodeBuffer[8 * 1024 * 1024] = { '\0' };
unsigned char outCodeBuffer[8 * 1024 * 1024] = { '\0' };

unsigned char errorMessagesPtrToLastBytePtr[8 * 1024 * 1024] = { '\0' };

int main(int argc, char* argv[]) {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	PostMessage(GetForegroundWindow(), WM_INPUTLANGCHANGEREQUEST, 2, (UINT)LoadKeyboardLayoutA("00000409", KLF_ACTIVATE));
#endif

	char valueByGetChar = 'n';
	char path[PATH_NAME_LENGH];
	char temp[2 * PATH_NAME_LENGH];
	char productionOut[MAX_TEXT_SIZE] = { 0 };

	comandLineParser(argc, argv, &mode, parameters);

	char* text;
	size_t sourceSize = loadSource(&text, parameters[INPUT_FILENAME_WITH_EXTENSION_PARAMETER]);
	if (!sourceSize) {
		printf("Empty source . . .\r\n");
#ifdef RERUN_MODE_FOR_INTERACTIVE_MODE
		if (mode & INTERACTIVE_MODE) {
		    (void)getchar();
		    printf("\r\nPress Enter: ");
		    (void)getchar();
			system("CLS");
			fflush(stdin);
			fflush(stdout);
			fflush(stderr);
			//(void)getchar();
			printf("No command line arguments are entered, so you are working in interactive mode.\r\n");
			printf("\nEnter 'y' to rerun compiler (to pass action enter other key): ");
			char valueByGetChar = getchar();
			if (valueByGetChar == 'y' || valueByGetChar == 'Y') {
				system("CLS");
				fflush(stdin);
				fflush(stdout);
				fflush(stderr);
				system((std::string("\"") + argv[0] + "\"").c_str());
			}
			else {
				return 0;
			}
		}
		else {
			return 0;
		}
#else
		return 0;
#endif
	}

	if (!_getcwd(path, PATH_NAME_LENGH))
	{
		printf("getcwd error ...\r\n");
		printf("Press Enter to exit . . .");
		return -1;
	}

	if (mode & INTERACTIVE_MODE && !(mode & SKIP_INTERACTIVE_IN_INTERACTIVE_MODE)) {
		system("CLS");
		fflush(stdin);
		fflush(stdout);
		fflush(stderr);
		printf("No command line arguments are entered, so you are working in step-by-step interactive mode.\r\n");
		printf("ATTENTIOON: The next step is critical, if it is skipped the compilation process will be terminated!\r\n");
		printf("Enter 'y' to lexical analyze action (to pass action process enter 'n' or others key): ");
	}
	fflush(stdin);
	if (mode & INTERACTIVE_MODE && (mode & SKIP_INTERACTIVE_IN_INTERACTIVE_MODE || getchar() == 'y') || mode & LEXICAL_ANALYZE_MODE) {

		if (mode & (DEBUG_MODE | INTERACTIVE_MODE) && mode & VIEW_INPUT_MODE) {
			printf("Original source:\r\n");
			printf("-------------------------------------------------------------------\r\n");
			printf("%s\r\n", text);
			printf("-------------------------------------------------------------------\r\n\r\n");
			printf("\r\nPress Enter: ");
			(void)getchar();
		}

		int commentRemoverResult = commentRemover(text, COMMENT_BEGIN_STR, COMMENT_END_STR);
		if (commentRemoverResult) {
			printf("Comment remover return %d\r\n", commentRemoverResult);
#ifdef RERUN_MODE_FOR_INTERACTIVE_MODE
			if (mode & INTERACTIVE_MODE) {
			    (void)getchar();
			    (void)printf("\r\nPress Enter: ");
			    (void)getchar();
				system("CLS");
				fflush(stdin);
				fflush(stdout);
				fflush(stderr);
				//(void)getchar();
				printf("No command line arguments are entered, so you are working in interactive mode.\r\n");
				printf("\nEnter 'y' to rerun compiler (to pass action enter other key): ");
				char valueByGetChar = getchar();
				if (valueByGetChar == 'y' || valueByGetChar == 'Y') {
					system("CLS");
					fflush(stdin);
					fflush(stdout);
					fflush(stderr);
					system((std::string("\"") + argv[0] + "\"").c_str());
				}
				else {
					return 0;
				}
			}
#else
			return 0;
#endif
		}
		if (mode & (DEBUG_MODE | INTERACTIVE_MODE) && mode & VIEW_INPUT_MODE) {
			printf("Source after comment removing:\r\n");
			printf("-------------------------------------------------------------------\r\n");
			printf("%s\r\n", text);
			printf("-------------------------------------------------------------------\r\n\r\n");
			printf("\r\nPress Enter: ");
			(void)getchar();
		}

		printf("Lexical analysis in progress, please wait...");
		struct LexemInfo ifBadLexemeInfo = tokenize(text, &lastLexemInfoInTable, identifierIdsTable, lexicalAnalyze);
		printf("\r                                                    \r");

		if (ifBadLexemeInfo.tokenType == UNEXPEXTED_LEXEME_TYPE) {
			UNEXPEXTED_LEXEME_TYPE;
			ifBadLexemeInfo.tokenType;
			printf("Lexical analysis detected unexpected lexeme\r\n");
			printLexemes(&ifBadLexemeInfo, 1);
			if (parameters[OUT_LEXEME_ERROR_FILENAME_WITH_EXTENSION_PARAMETER][0] != '\0') {
				printLexemesToFile(lexemesInfoTable, 1, parameters[OUT_LEXEME_ERROR_FILENAME_WITH_EXTENSION_PARAMETER]);
			}
#ifdef RERUN_MODE_FOR_INTERACTIVE_MODE
			if (mode & INTERACTIVE_MODE) {
			    (void)getchar();
			    printf("\r\nPress Enter: ");
			    (void)getchar();
				system("CLS");
				fflush(stdin);
				fflush(stdout);
				fflush(stderr);
				//(void)getchar();
				printf("No command line arguments are entered, so you are working in interactive mode.\r\n");
				printf("\nEnter 'y' to rerun compiler (to pass action enter other key): ");
				char valueByGetChar = getchar();
				if (valueByGetChar == 'y' || valueByGetChar == 'Y') {
					system("CLS");
					fflush(stdin);
					fflush(stdout);
					fflush(stderr);
					system((std::string("\"") + argv[0] + "\"").c_str());
				}
				else {
					return 0;
				}
			}
#else
			return 0;
#endif
		}
		if (parameters[OUT_LEXEMES_SEQUENSE_FILENAME_WITH_EXTENSION_PARAMETER][0] != '\0') {
			printLexemesToFile(lexemesInfoTable, 0, parameters[OUT_LEXEMES_SEQUENSE_FILENAME_WITH_EXTENSION_PARAMETER]);
		}
		if (parameters[OUT_LEXEME_ERROR_FILENAME_WITH_EXTENSION_PARAMETER][0] != '\0') {
			writeBytesToFile(parameters[OUT_LEXEME_ERROR_FILENAME_WITH_EXTENSION_PARAMETER], (unsigned char*)"No error.", strlen("No error."));
		}
		if (mode & (DEBUG_MODE | INTERACTIVE_MODE) && mode & VIEW_LEXEMS_AST_C_ASSEMBLY_NATIVE_OBJ_EXE_MODE) {
			printLexemes(lexemesInfoTable, 0);
		}
		else {
			printf("Lexical analysis complete success\r\n");
		}

		if (mode & INTERACTIVE_MODE && !(mode & SKIP_INTERACTIVE_IN_INTERACTIVE_MODE)) {
			printf("\r\nPress Enter: ");
			(void)getchar();
			(void)getchar();
		}
	}
	else {
#ifdef RERUN_MODE_FOR_INTERACTIVE_MODE
	    if (mode & INTERACTIVE_MODE) {
	    	(void)getchar();
	    	printf("\r\nPress Enter: ");
	    	(void)getchar();
	    	system("CLS");
	    	fflush(stdin);
	    	fflush(stdout);
	    	fflush(stderr);
	    	//(void)getchar();
	    	printf("No command line arguments are entered, so you are working in interactive mode.\r\n");
	    	printf("\nEnter 'y' to rerun compiler (to pass action enter other key): ");
	    	char valueByGetChar = getchar();
	    	if (valueByGetChar == 'y' || valueByGetChar == 'Y') {
	    		system("CLS");
	    		fflush(stdin);
	    		fflush(stdout);
	    		fflush(stderr);
	    		system((std::string("\"") + argv[0] + "\"").c_str());
	    	}
	    	else {
	    		return 0;
	    	}
	    }
#else
	return 0;
#endif
	}

	if (mode & INTERACTIVE_MODE && !(mode & SKIP_INTERACTIVE_IN_INTERACTIVE_MODE)) {
		system("CLS");
		fflush(stdin);
		fflush(stdout);
		fflush(stderr);
		printf("No command line arguments are entered, so you are working in step-by-step interactive mode.\r\n");
		printf("ATTENTIOON: The next step is critical, if it is skipped the compilation process will be terminated!\r\n");
		printf("Enter 'y' to syntax analyze action (to pass action process enter 'n' or others key): ");
	}
	fflush(stdin);
	if (mode & INTERACTIVE_MODE && (mode & SKIP_INTERACTIVE_IN_INTERACTIVE_MODE || getchar() == 'y') || mode & SYNTAX_ANALYZE_MODE) {
		errorMessagesPtrToLastBytePtr[0] = '\0';
		unsigned char* errorMessagesPtrToLastBytePtr_ = errorMessagesPtrToLastBytePtr;
		if (SUCCESS_STATE != syntaxAnalyze(lexemesInfoTable, &grammar, 0, parameters[OUT_AST_FILENAME_WITH_EXTENSION_PARAMETER], (char*)&errorMessagesPtrToLastBytePtr, mode & (DEBUG_MODE | INTERACTIVE_MODE) && mode & VIEW_LEXEMS_AST_C_ASSEMBLY_NATIVE_OBJ_EXE_MODE)) { // TODO: add AST param	
			if (parameters[OUT_SYNTAX_ERROR_FILENAME_WITH_EXTENSION_PARAMETER][0] != '\0') {			
				writeBytesToFile(parameters[OUT_SYNTAX_ERROR_FILENAME_WITH_EXTENSION_PARAMETER], errorMessagesPtrToLastBytePtr, strlen((const char*)errorMessagesPtrToLastBytePtr));		
			}
			if (parameters[OUT_AST_FILENAME_WITH_EXTENSION_PARAMETER][0] != '\0') {
				writeBytesToFile(parameters[OUT_AST_FILENAME_WITH_EXTENSION_PARAMETER], (unsigned char*)"AST build failed.", strlen("AST build failed."));
			}
#ifdef RERUN_MODE_FOR_INTERACTIVE_MODE
			if (mode & INTERACTIVE_MODE) {
			    (void)getchar();
			    printf("\r\nPress Enter: ");
			    (void)getchar();
				system("CLS");
				fflush(stdin);
				fflush(stdout);
				fflush(stderr);
				//(void)getchar();
				printf("No command line arguments are entered, so you are working in interactive mode.\r\n");
				printf("\nEnter 'y' to rerun compiler (to pass action enter other key): ");
				char valueByGetChar = getchar();
				if (valueByGetChar == 'y' || valueByGetChar == 'Y') {
					system("CLS");
					fflush(stdin);
					fflush(stdout);
					fflush(stderr);
					system((std::string("\"") + argv[0] + "\"").c_str());
				}
				else {
					return 0;
				}
			}
#else
			return 0;
#endif
		}

		if (parameters[OUT_SYNTAX_ERROR_FILENAME_WITH_EXTENSION_PARAMETER][0] != '\0') {
			writeBytesToFile(parameters[OUT_SYNTAX_ERROR_FILENAME_WITH_EXTENSION_PARAMETER], (unsigned char*)"No error.", strlen("No error."));
			printf("No error.\r\n");
		}

		if (mode & INTERACTIVE_MODE && !(mode & SKIP_INTERACTIVE_IN_INTERACTIVE_MODE)) {
			printf("\r\nPress Enter: ");
			(void)getchar();
			(void)getchar();
		}
	}
	else {
#ifdef RERUN_MODE_FOR_INTERACTIVE_MODE
		if (mode & INTERACTIVE_MODE) {
		    (void)getchar();
		    printf("\r\nPress Enter: ");
		    (void)getchar();
			system("CLS");
			fflush(stdin);
			fflush(stdout);
			fflush(stderr);
			//(void)getchar();
			printf("No command line arguments are entered, so you are working in interactive mode.\r\n");
			printf("\nEnter 'y' to rerun compiler (to pass action enter other key): ");
			char valueByGetChar = getchar();
			if (valueByGetChar == 'y' || valueByGetChar == 'Y') {
				system("CLS");
				fflush(stdin);
				fflush(stdout);
				fflush(stderr);
				system((std::string("\"") + argv[0] + "\"").c_str());
			}
			else {
				return 0;
			}
		}
#else
		return 0;
#endif
	}

	if (mode & INTERACTIVE_MODE && !(mode & SKIP_INTERACTIVE_IN_INTERACTIVE_MODE)) {
		system("CLS");
		fflush(stdin);
		fflush(stdout);
		fflush(stderr);
		printf("No command line arguments are entered, so you are working in step-by-step interactive mode.\r\n");
		printf("ATTENTIOON: The next step is critical, if it is skipped the compilation process will be terminated!\r\n");
		printf("Enter 'y' to semantix analyze action (to pass action process enter 'n' or others key): ");
	}
	fflush(stdin);
	if (mode & INTERACTIVE_MODE && (mode & SKIP_INTERACTIVE_IN_INTERACTIVE_MODE || getchar() == 'y') || mode & SEMANTIX_ANALYZE_MODE) {
		errorMessagesPtrToLastBytePtr[0] = '\0';
		unsigned char* errorMessagesPtrToLastBytePtr_ = errorMessagesPtrToLastBytePtr;
		if (SUCCESS_STATE != semanticsAnalyze(lexemesInfoTable, &grammar, identifierIdsTable, (char *)errorMessagesPtrToLastBytePtr)) {
			if (parameters[OUT_SEMANTIX_ERROR_FILENAME_WITH_EXTENSION_PARAMETER][0] != '\0') {
				writeBytesToFile(parameters[OUT_SEMANTIX_ERROR_FILENAME_WITH_EXTENSION_PARAMETER], errorMessagesPtrToLastBytePtr, strlen((const char*)errorMessagesPtrToLastBytePtr));
			}
#ifdef RERUN_MODE_FOR_INTERACTIVE_MODE
			if (mode & INTERACTIVE_MODE) {
			    (void)getchar();
			    printf("\r\nPress Enter: ");
			    (void)getchar();
				system("CLS");
				fflush(stdin);
				fflush(stdout);
				fflush(stderr);
				//(void)getchar();
				printf("No command line arguments are entered, so you are working in interactive mode.\r\n");
				printf("\nEnter 'y' to rerun compiler (to pass action enter other key): ");
				char valueByGetChar = getchar();
				if (valueByGetChar == 'y' || valueByGetChar == 'Y') {
					system("CLS");
					fflush(stdin);
					fflush(stdout);
					fflush(stderr);
					system((std::string("\"") + argv[0] + "\"").c_str());
				}
				else {
					return 0;
				}
			}
#else
			return 0;
#endif
		}

		if (parameters[OUT_SEMANTIX_ERROR_FILENAME_WITH_EXTENSION_PARAMETER][0] != '\0') {
			writeBytesToFile(parameters[OUT_SEMANTIX_ERROR_FILENAME_WITH_EXTENSION_PARAMETER], (unsigned char*)"No error.", strlen("No error."));
		}

		if (mode & INTERACTIVE_MODE && !(mode & SKIP_INTERACTIVE_IN_INTERACTIVE_MODE)) {
			printf("\r\nPress Enter: ");
			(void)getchar();
			(void)getchar();
		}
	}
	else {
#ifdef RERUN_MODE_FOR_INTERACTIVE_MODE
		if (mode & INTERACTIVE_MODE) {
		    (void)getchar();
		    (void)printf("\r\nPress Enter: ");
		    (void)getchar();
			system("CLS");
			fflush(stdin);
			fflush(stdout);
			fflush(stderr);
			//(void)getchar();
			printf("No command line arguments are entered, so you are working in interactive mode.\r\n");
			printf("\nEnter 'y' to rerun compiler (to pass action enter other key): ");
			char valueByGetChar = getchar();
			if (valueByGetChar == 'y' || valueByGetChar == 'Y') {
				system("CLS");
				fflush(stdin);
				fflush(stdout);
				fflush(stderr);
				system((std::string("\"") + argv[0] + "\"").c_str());
			}
			else {
				return 0;
			}
		}
#else
		return 0;
#endif
	}

	if (mode & INTERACTIVE_MODE && !(mode & SKIP_INTERACTIVE_IN_INTERACTIVE_MODE)) {
		system("CLS");
		fflush(stdin);
		fflush(stdout);
		fflush(stderr);
		printf("No command line arguments are entered, so you are working in step-by-step interactive mode.\r\n");
		printf("ATTENTIOON: The next step is critical, if it is skipped the compilation process will be terminated!\r\n");
		printf("Enter 'y' for the action to prepare for the compilation process (to pass the action process, enter 'n' or another key): ");
	}
	fflush(stdin);
	if (mode & INTERACTIVE_MODE && (mode & SKIP_INTERACTIVE_IN_INTERACTIVE_MODE || getchar() == 'y') || mode & MAKE_PREPARE) {
//		if (mode & (DEBUG_MODE | INTERACTIVE_MODE) && mode & VIEW_LEXEMS_AST_C_ASSEMBLY_NATIVE_OBJ_EXE_MODE) {
//			printLexemes(lexemesInfoTable, 0);
//		}

		lastLexemInfoInTable = lexemesInfoTable;
		makePrepare(lexemesInfoTable, &lastLexemInfoInTable, &lastLexemInfoInTableTemp);

		if (mode & (DEBUG_MODE | INTERACTIVE_MODE) && mode & VIEW_LEXEMS_AST_C_ASSEMBLY_NATIVE_OBJ_EXE_MODE) {
			printLexemes(lexemesInfoTableTemp, 0);
			if (parameters[OUT_PREPARED_LEXEMES_SEQUENSE_FILENAME_WITH_EXTENSION_PARAMETER][0] != '\0') {
				printLexemesToFile(lexemesInfoTableTemp, 0, parameters[OUT_PREPARED_LEXEMES_SEQUENSE_FILENAME_WITH_EXTENSION_PARAMETER]);
			}
		}
		else {
			printf("Make prepare(expressions separation + creating reverse Polish notation) complete success\r\n");
		}

		if (mode & INTERACTIVE_MODE && !(mode & SKIP_INTERACTIVE_IN_INTERACTIVE_MODE)) {
			//if (parameters[OUT_PREPARED_LEXEMES_SEQUENSE_FILENAME_WITH_EXTENSION_PARAMETER][0] != '\0') {
			//	printf("File \"%s\" saved.\n", parameters[OUT_PREPARED_LEXEMES_SEQUENSE_FILENAME_WITH_EXTENSION_PARAMETER]);
			//}
			printf("\r\nPress Enter: ");
			(void)getchar();
			(void)getchar();
		}
	}
	else {
#ifdef RERUN_MODE_FOR_INTERACTIVE_MODE
		if (mode & INTERACTIVE_MODE) {
		    (void)getchar();
		    (void)printf("\r\nPress Enter: ");
		    (void)getchar();
			system("CLS");
			fflush(stdin);
			fflush(stdout);
			fflush(stderr);
			//(void)getchar();
			printf("No command line arguments are entered, so you are working in interactive mode.\r\n");
			printf("\nEnter 'y' to rerun compiler (to pass action enter other key): ");
			char valueByGetChar = getchar();
			if (valueByGetChar == 'y' || valueByGetChar == 'Y') {
				system("CLS");
				fflush(stdin);
				fflush(stdout);
				fflush(stderr);
				system((std::string("\"") + argv[0] + "\"").c_str());
			}
			else {
				return 0;
			}
		}
#else
		return 0;
#endif
	}

	if (mode & INTERACTIVE_MODE && !(mode & SKIP_INTERACTIVE_IN_INTERACTIVE_MODE)) {
		system("CLS");
		fflush(stdin);
		fflush(stdout);
		fflush(stderr);
		printf("No command line arguments are entered, so you are working in step-by-step interactive mode.\r\n");
		printf("\r\n");
		printf("Enter 'y' to create C-code (to pass action process enter 'n' or others key): ");
	}
	fflush(stdin);
	if (mode & INTERACTIVE_MODE && (mode & SKIP_INTERACTIVE_IN_INTERACTIVE_MODE || getchar() == 'y') || mode & MAKE_C) { // MAKE_ASSEMBLY_MODE
		lastLexemInfoInTableTemp = lexemesInfoTableTemp;// 			printLexemes(lexemesInfoTableTemp, 0);
		//outCodeBuffer[0] = '\0';
		makeCode(&lastLexemInfoInTableTemp, outCodeBuffer, C_CODER_MODE); /*The lexem info table will be changed and will need to be rebuilt. TODO: change the implementation!*/

		if (mode & (DEBUG_MODE | INTERACTIVE_MODE) && mode & VIEW_LEXEMS_AST_C_ASSEMBLY_NATIVE_OBJ_EXE_MODE) {
			printf("\r\n\r\n%s\r\n\r\n", outCodeBuffer);
		}
		else {
			printf("C-code created complete successfully.\r\n\r\n");
		}
		
		if (parameters[OUT_C_FILENAME_WITH_EXTENSION_PARAMETER][0] != '\0') {
			writeBytesToFile(parameters[OUT_C_FILENAME_WITH_EXTENSION_PARAMETER], outCodeBuffer, strlen((const char*)outCodeBuffer));
		}

		if (mode & INTERACTIVE_MODE && !(mode & SKIP_INTERACTIVE_IN_INTERACTIVE_MODE)) {
			printf("\r\nPress Enter: ");
			(void)getchar();
			(void)getchar();
		}
	}

	if (mode & INTERACTIVE_MODE && !(mode & SKIP_INTERACTIVE_IN_INTERACTIVE_MODE)) {
		system("CLS");
		fflush(stdin);
		fflush(stdout);
		fflush(stderr);
		printf("No command line arguments are entered, so you are working in step-by-step interactive mode.\r\n");
		printf("\r\n");
		printf("Enter 'y' to create assembly (to pass action process enter 'n' or others key): ");
	}
	fflush(stdin);
	if (mode & INTERACTIVE_MODE && (mode & SKIP_INTERACTIVE_IN_INTERACTIVE_MODE || getchar() == 'y') || mode & MAKE_ASSEMBLY) { // MAKE_ASSEMBLY_MODE
		lastLexemInfoInTableTemp = lexemesInfoTableTemp;// 			printLexemes(lexemesInfoTableTemp, 0);
		lastLexemInfoInTable = lexemesInfoTable;
		makePrepare(lexemesInfoTable, &lastLexemInfoInTable, &lastLexemInfoInTableTemp); /* Rerun preapare process after previous etap. TODO: change the implementation!*/
		lastLexemInfoInTableTemp = lexemesInfoTableTemp;// 			printLexemes(lexemesInfoTableTemp, 0);
		//outCodeBuffer[0] = '\0';
		makeCode(&lastLexemInfoInTableTemp, outCodeBuffer, ASSEMBLY_X86_WIN32_CODER_MODE);

		if (mode & (DEBUG_MODE | INTERACTIVE_MODE) && mode & VIEW_LEXEMS_AST_C_ASSEMBLY_NATIVE_OBJ_EXE_MODE) {
			printf("\r\n\r\n%s\r\n\r\n", outCodeBuffer);
		}
		else {
			printf("Assembly code created complete successfully.\r\n\r\n");
		}

		if (parameters[OUT_ASSEMBLY_FILENAME_WITH_EXTENSION_PARAMETER][0] != '\0') {
			writeBytesToFile(parameters[OUT_ASSEMBLY_FILENAME_WITH_EXTENSION_PARAMETER], outCodeBuffer, strlen((const char*)outCodeBuffer));
		}

		if (mode & INTERACTIVE_MODE && !(mode & SKIP_INTERACTIVE_IN_INTERACTIVE_MODE)) {
			printf("\r\nPress Enter: ");
			(void)getchar();
			(void)getchar();
		}
	}

	unsigned long long int byteCountWritedToTempCodeBuffer = 0;
	if (mode & INTERACTIVE_MODE && !(mode & SKIP_INTERACTIVE_IN_INTERACTIVE_MODE)) { // BUILD NATIVE CODE
		system("CLS");
		fflush(stdin);
		fflush(stdout);
		fflush(stderr);
		printf("No command line arguments are entered, so you are working in step-by-step interactive mode.\r\n");
		printf("ATTENTIOON: The next step is critical, if it is skipped the compilation process will be terminated!\r\n");
		printf("Enter 'y' to create native code (to pass action process enter 'n' or others key): ");
	}
	fflush(stdin);
	if (mode & INTERACTIVE_MODE && (mode & SKIP_INTERACTIVE_IN_INTERACTIVE_MODE || getchar() == 'y') || mode & (MAKE_C | MAKE_ASSEMBLY | MAKE_OBJECT | MAKE_BINARY)) {
		lastLexemInfoInTableTemp = lexemesInfoTableTemp;// 			printLexemes(lexemesInfoTableTemp, 0);
		lastLexemInfoInTable = lexemesInfoTable;
		makePrepare(lexemesInfoTable, &lastLexemInfoInTable, &lastLexemInfoInTableTemp); /* Rerun preapare process after previous etap. TODO: change the implementation!*/
		lastLexemInfoInTableTemp = lexemesInfoTableTemp;// 			printLexemes(lexemesInfoTableTemp, 0);
		//outCodeBuffer[0] = '\0';
		byteCountWritedToTempCodeBuffer = makeCode(&lastLexemInfoInTableTemp, tempCodeBuffer, MACHINE_X86_WIN32_CODER_MODE) - tempCodeBuffer;

		if (mode & (DEBUG_MODE | INTERACTIVE_MODE) && mode & VIEW_LEXEMS_AST_C_ASSEMBLY_NATIVE_OBJ_EXE_MODE) {
			viewCode(tempCodeBuffer, byteCountWritedToTempCodeBuffer, 16);
			printf("\r\n\r\n");
		}
		else {
			printf("Native code created complete successfully.\r\n\r\n");
		}

		if (mode & INTERACTIVE_MODE && !(mode & SKIP_INTERACTIVE_IN_INTERACTIVE_MODE)) {
			printf("\r\nPress Enter: ");
			(void)getchar();
			(void)getchar();
		}
	}
	else {
#ifdef RERUN_MODE_FOR_INTERACTIVE_MODE
		if (mode & INTERACTIVE_MODE) {
		    (void)getchar();
		    (void)printf("\r\nPress Enter: ");
		    (void)getchar();
			system("CLS");
			fflush(stdin);
			fflush(stdout);
			fflush(stderr);
			//(void)getchar();
			printf("No command line arguments are entered, so you are working in interactive mode.\r\n");
			printf("\nEnter 'y' to rerun compiler (to pass action enter other key): ");
			char valueByGetChar = getchar();
			if (valueByGetChar == 'y' || valueByGetChar == 'Y') {
				system("CLS");
				fflush(stdin);
				fflush(stdout);
				fflush(stderr);
				system((std::string("\"") + argv[0] + "\"").c_str());
			}
			else {
				return 0;
			}
		}
#else
		return 0;
#endif
	}

	if (mode & INTERACTIVE_MODE && !(mode & SKIP_INTERACTIVE_IN_INTERACTIVE_MODE)) {
		system("CLS");
		fflush(stdin);
		fflush(stdout);
		fflush(stderr);
		printf("No command line arguments are entered, so you are working in step-by-step interactive mode.\r\n");
		printf("\r\n");
		printf("Enter 'y' to create obj-file (to pass action process enter 'n' or others key): ");
	}
	fflush(stdin);
	if (mode & INTERACTIVE_MODE && (mode & SKIP_INTERACTIVE_IN_INTERACTIVE_MODE || getchar() == 'y') || mode & MAKE_OBJECT) {
		unsigned long long int objectSize = buildTemplateForCodeObject(outCodeBuffer);
		unsigned char* currBytePtr = getObjectCodeBytePtr(outCodeBuffer, MACHINE_X86_WIN32_CODER_MODE);

		(void)outBytes2Code(currBytePtr, tempCodeBuffer, byteCountWritedToTempCodeBuffer);

		if (mode & (DEBUG_MODE | INTERACTIVE_MODE) && mode & VIEW_LEXEMS_AST_C_ASSEMBLY_NATIVE_OBJ_EXE_MODE) {
			viewCode(outCodeBuffer, objectSize, 16);
			printf("\r\n\r\n");
		}
		else {
			printf("obj-code created complete successfully.\r\n\r\n");
		}

		writeBytesToFile(parameters[OUT_OBJECT_FILENAME_WITH_EXTENSION_PARAMETER], outCodeBuffer, objectSize);

		printf("\r\nTo create an exe file (from obj-file), use the following command in the Visual Studio terminal (no cmd):\r\n"
			   "link /SUBSYSTEM:CONSOLE \"%s\" \"kernel32.lib\" \"user32.lib\""
			   "\r\n\r\n", parameters[OUT_OBJECT_FILENAME_WITH_EXTENSION_PARAMETER]);

		if (mode & INTERACTIVE_MODE && !(mode & SKIP_INTERACTIVE_IN_INTERACTIVE_MODE)) {
			printf("\r\nPress Enter: ");
			(void)getchar();
			(void)getchar();
		}
	}
	else if (mode & INTERACTIVE_MODE && !(mode & SKIP_INTERACTIVE_IN_INTERACTIVE_MODE)) {
		(void)getchar();
	}

	if (mode & INTERACTIVE_MODE && !(mode & SKIP_INTERACTIVE_IN_INTERACTIVE_MODE)) {
		system("CLS");
		fflush(stdin);
		fflush(stdout);
		fflush(stderr);
		printf("No command line arguments are entered, so you are working in step-by-step interactive mode.\r\n");
		printf("\r\n");
		printf("Enter 'y' to create exe-file (to pass action process enter 'n' or others key): ");
	}
	fflush(stdin);
	if (mode & INTERACTIVE_MODE && (mode & SKIP_INTERACTIVE_IN_INTERACTIVE_MODE || getchar() == 'y') || mode & MAKE_BINARY) {
		unsigned long long int imageSize = buildTemplateForCodeImage(outCodeBuffer);
		unsigned char* currBytePtr = getImageCodeBytePtr(outCodeBuffer, MACHINE_X86_WIN32_CODER_MODE);

		(void)outBytes2Code(currBytePtr, tempCodeBuffer, byteCountWritedToTempCodeBuffer);

		if (mode & (DEBUG_MODE | INTERACTIVE_MODE) && mode & VIEW_LEXEMS_AST_C_ASSEMBLY_NATIVE_OBJ_EXE_MODE) {
			viewCode(outCodeBuffer, imageSize, 16);
			printf("\r\n\r\n");
		}
		else {
			printf("exe-code created complete successfully.\r\n\r\n");
		}

		writeBytesToFile(parameters[OUT_BINARY_FILENAME_WITH_EXTENSION_PARAMETER], outCodeBuffer, imageSize);

		(void)printf("\r\nPress Enter: "); // (void)getchar();

		if (mode & INTERACTIVE_MODE && !(mode & SKIP_INTERACTIVE_IN_INTERACTIVE_MODE)) {
			//printf("\r\nPress Enter: ");
			(void)getchar();
			(void)getchar();
		}
	}
	else /*if (mode & INTERACTIVE_MODE)*/ {
#ifdef RERUN_MODE_FOR_INTERACTIVE_MODE
		if (mode & INTERACTIVE_MODE) {
		    (void)getchar();
		    (void)printf("\r\nPress Enter: ");
		    (void)getchar();
			system("CLS");
			fflush(stdin);
			fflush(stdout);
			fflush(stderr);
			//(void)getchar();
			printf("No command line arguments are entered, so you are working in interactive mode.\r\n");
			printf("\nEnter 'y' to rerun compiler (to pass action enter other key): ");
			char valueByGetChar = getchar();
			if (valueByGetChar == 'y' || valueByGetChar == 'Y') {
				system("CLS");
				fflush(stdin);
				fflush(stdout);
				fflush(stderr);
				system((std::string("\"") + argv[0] + "\"").c_str());
			}
			else {
				return 0;
			}
		}
#else
		return 0;
#endif
	}

	if (mode & INTERACTIVE_MODE || mode & RUN_BINARY) {
		if (mode & SKIP_INTERACTIVE_IN_INTERACTIVE_MODE) {
			(void)getchar();
		}
		system("CLS");
		fflush(stdin);
		fflush(stdout);
		fflush(stderr);
	}

	bool firstRun = true;
	while (mode & INTERACTIVE_MODE || mode & RUN_BINARY) {
		if (mode & INTERACTIVE_MODE && firstRun) {
			printf("No command line arguments are entered, so you are working in interactive mode.\r\n");
			printf("\r\n");
		}
		if (firstRun) {
			printf("Enter 'y' to run program action (to pass action process Enter 'n' or others key): ");
			firstRun = false;
		}
		else{
			printf("Enter 'y' to rerun program action (to pass action process Enter 'n' or others key): ");
		}

		fflush(stdin);

		if (valueByGetChar = getchar(), valueByGetChar == 'y' || valueByGetChar == 'Y') {
			system("CLS");
			fflush(stdin);
			fflush(stdout);
			fflush(stderr);
			printf("Run \"%s\":\r\n", parameters[OUT_BINARY_FILENAME_WITH_EXTENSION_PARAMETER]);
			//sprintf(temp, "START /b /wait \"\" /D \"%s\\masm32p\" %s.exe", path, parameters[OUT_BINARY_FILENAME_WITHOUT_EXTENSION_PARAMETER]);
			snprintf(temp, MAX_PARAMETERS_SIZE, "START /b /wait \"\" %s", parameters[OUT_BINARY_FILENAME_WITH_EXTENSION_PARAMETER]);
			fflush(stdin);
			system((char*)temp);
			fflush(stdin);
			printf("\r\n\"%s\" terminated.\r\n\r\n", parameters[OUT_BINARY_FILENAME_WITH_EXTENSION_PARAMETER]);
			(void)getchar();
		}
		else {
			printf("\r\n");
			break;
		}
	}

#ifdef RERUN_MODE_FOR_INTERACTIVE_MODE
	if (mode & INTERACTIVE_MODE) {
		system("CLS");
		fflush(stdin);
		fflush(stdout);
		fflush(stderr);
		(void)getchar();
		printf("No command line arguments are entered, so you are working in interactive mode.\r\n");
		printf("\nEnter 'y' to rerun compiler (to pass action enter other key): ");
		char valueByGetChar = getchar();
		if (valueByGetChar == 'y' || valueByGetChar == 'Y') {
			system("CLS");
			fflush(stdin);
			fflush(stdout);
			fflush(stderr);
			system((std::string("\"") + argv[0] + "\"").c_str());
		}
	}
#endif

//	printf("\r\n\r\nPress Enter to exit . . .");
//	(void)getchar();

	return 0;
}