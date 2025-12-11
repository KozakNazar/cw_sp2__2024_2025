/***********************
* N.Kozak // Lviv'2025 *
*    file: dfa.hpp     *
************************/
#include "stdio.h"

//#define DEBUG_DFA_STATE

#define SYMBOL_NUMBER 256 // dup
#define MAX_STATES 1024   // dup

typedef int INSTRUCTION;
typedef INSTRUCTION PROGRAM[SYMBOL_NUMBER][MAX_STATES];

typedef struct StructDFA{
	char * data;
	PROGRAM * program;
	void(*run)(struct StructDFA * dfa);
	int state;
} DFA;

void runner(DFA * dfa){
	for (; *dfa->data != '\0'; ++dfa->data){
		dfa->state = (*dfa->program)[*dfa->data][dfa->state];
	}
}

char tryToAccept(PROGRAM * program, int * finitStates, char * data){
	DFA dfa = { data, program, runner, 0/*Q000*/ };
	dfa.run(&dfa);

	if (finitStates) for (; *finitStates; ++finitStates) {
		if (dfa.state == *finitStates) {
#ifdef DEBUG_DFA_STATE
			printf("DFA: finit state\r\n");
#endif
			return 1;
		}
	}
#ifdef DEBUG_DFA_STATE
	printf("DFA: no finit state\r\n");
#endif
	return 0;
}
