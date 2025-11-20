//#define WIN_M
#ifdef WIN_M
#include <windows.h>
#endif
#include "stdio.h"	

extern int call_main_spirit(int argc, char* argv[]);
extern int call_main_syntax(int argc, char* argv[]);

int main(int argc, char* argv[]) {
#ifdef WIN_M
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode = 0;
	GetConsoleMode(hConsole, &dwMode);
	SetConsoleMode(hConsole, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif
	printf("\x1b[2J\x1b[H"); // Use ANSI escape code to clear the screen
	printf("Enter 'y' to verify by EBNF (to verify by LL2 prototype enter other key): ");
	char valueByGetChar = getchar();
	if (valueByGetChar == 'y' || valueByGetChar == 'Y') {
		return call_main_spirit(argc, argv);
	}
	
	return call_main_syntax(argc, argv);
}