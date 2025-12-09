/****************************
* N.Kozak // Lviv'2025      *
*    file: dpda1forll2.hpp  *
****************************/
#include "stdio.h"

//#define DEBUG_DFA_STATE

#define LL2_SYMBOL_NUMBER 256 // dup
#define LL2_MAX_STATES /*LL2_SYMBOL_NUMBER*/ 256 // 1024 // dup

//#define BUILD_C2P_AST_TYPE_BY_DPDA1
#ifndef BUILD_C2P_AST_TYPE_BY_DPDA1
#define	BUILD_P2C_AST_TYPE_BY_DPDA1 // TODO: no default
#endif

//#define NO_ACTION 0xFFFF

//#define NO_RULE {NO_ACTION, NO_ACTION, NO_ACTION}
//#define NO_RULE {NO_ACTION, NO_ACTION}            // NEW

//#define S 0
//#define R 1

typedef enum {
    NO_SCROLL,
	SCROLL_TO_RIGHT
} TapeAction;

typedef enum {
	NOTHING, // STACK_NOTHING
	PUSH,    // STACK_PUSH // REMOVE ???
	POP,     // STACK_POP
	STACK_POP_AND_MULTIPLIPUSH
} StackAction;

#define MAX_RHSCONTEINER_COUNT 3 // syntax.h
#define MAX_RHSCONTEINER_COUNT_IN_PDA (MAX_RHSCONTEINER_COUNT + 1)

#define MAX_RTOKEN_COUNT 12 // 16
typedef struct {
	StackAction stackAction;
	unsigned int stackAddon[MAX_RHSCONTEINER_COUNT_IN_PDA][MAX_RTOKEN_COUNT];
} StackUpdate;

//typedef int INSTRUCTION_PDA[2/*3, but a single state is used*/];
typedef struct { 
	char rhsVariantAddonIndexMask;// NEW 08.2025
	TapeAction tapeAction; // (1)
	StackUpdate stackUpdate; // (2)
	//int newState; // (3) // one state
} PDAInstruction /* Praecursor */;
typedef PDAInstruction DPDA1Program[LL2_SYMBOL_NUMBER][LL2_MAX_STATES];

//#define EMPTY_PDA_INSTRUCTION { NO_SCROLL, {PUSH, {123, 123, 4, 0}}}
#define PDA_DEAD_STATE_INSTRUCTION { 0, NO_SCROLL, {NOTHING, {-1, -1, -1, -1}}} // -1 => ?

typedef unsigned char DPDA1IndexingForSecondElement[LL2_SYMBOL_NUMBER][LL2_MAX_STATES];
DPDA1IndexingForSecondElement dpdaIndexingForSecondElement;

// TODO: USE MEMSET !

DPDA1Program dpdaProgram = { /* default pass */
	//                       {q0, a0}                    {q0, 0}                                   {q0, 1}                                   {q0, ^}                                   {q0, NT123}
	/* a0 */{ {0, NO_SCROLL, {PUSH, {123, 123, 4, 0}}},  PDA_DEAD_STATE_INSTRUCTION,               PDA_DEAD_STATE_INSTRUCTION,               PDA_DEAD_STATE_INSTRUCTION,               {0, NO_SCROLL, {POP                   }}  },
	/* 0  */{ {0, NO_SCROLL, {PUSH, {123, 123, 4, 0}}},  {0, NO_SCROLL, {PUSH, {123, 123, 4, 0}}}, {0, NO_SCROLL, {PUSH, {123, 123, 4, 0}}}, {0, NO_SCROLL, {PUSH, {123, 123, 4, 0}}}, {0, NO_SCROLL, {PUSH, {123, 123, 4, 0}}}, },
	/* 1  */{ {0, NO_SCROLL, {PUSH, {123, 123, 4, 0}}},  {0, NO_SCROLL, {PUSH, {123, 123, 4, 0}}}, {0, NO_SCROLL, {PUSH, {123, 123, 4, 0}}}, {0, NO_SCROLL, {PUSH, {123, 123, 4, 0}}}, {0, NO_SCROLL, {PUSH, {123, 123, 4, 0}}}, },
	/* ^  */{ {0, NO_SCROLL, {PUSH, {123, 123, 4, 0}}},  {0, NO_SCROLL, {PUSH, {123, 123, 4, 0}}}, {0, NO_SCROLL, {PUSH, {123, 123, 4, 0}}}, {0, NO_SCROLL, {PUSH, {123, 123, 4, 0}}}, {0, NO_SCROLL, {PUSH, {123, 123, 4, 0}}}, }
};

//typedef char Stack[8192] STATCK;
//STATCK stack = {'\0'};

#define STACK_TOP_STATE(STACK) STACK[0]

#define STACK_EMPTY_STATE(STACK) (stackSize == 0)

#define SAVE_OFFSET 0
typedef struct StructDPDA1{
	char * data;
	DPDA1Program * dpdaProgram;
	DPDA1IndexingForSecondElement* dpdaIndexingForSecondElement; // by sevond element!!!!!
	void(*run)(struct StructDPDA1 * dpda1);
	// int state; // one state

	unsigned int* stack_above_top;
	unsigned int stack[8192 + SAVE_OFFSET]; // STATCK;

} DPDA1;

void runner3(DPDA1 * dpda1){
#ifdef	BUILD_P2C_AST_TYPE_BY_DPDA1 // TODO: no default
	printf("Don't use BUILD_P2C_AST_TYPE_BY_DPDA1, use BUILD_2C2P_AST_TYPE_BY_DPDA1!\r\n");
	printf("TODO: need to use an additional stack of parent elements!\r\n");
	exit(0);
#endif
	for (; *dpda1->data != '\0'; ++dpda1->data){
		//StackAction *stackAction = (*dpda1->dpdaProgram)[*dpda1->data][*dpda1->stack_top].stackUpdate.stackAction;
		StackUpdate * stackUpdate = &(*dpda1->dpdaProgram)[*dpda1->data][*dpda1->stack_above_top + SAVE_OFFSET - 1].stackUpdate;
		//TapeAction * tapeAction = &(*dpda1->dpdaProgram)[*dpda1->data][*dpda1->stack_above_top + SAVE_OFFSET - 1].tapeAction;

		//switch (stackUpdate->stackAction) {
		//case PUSH:
		//	int* stackAddonLastElementPtr = stackUpdate->stackAddon;
		//	while (*(stackAddonLastElementPtr++));
		//	++stackAddonLastElementPtr;
		//	for (; stackAddonLastElementPtr < stackUpdate->stackAddon; --stackAddonLastElementPtr) {
		//		*(dpda1->stack_above_top++) = *stackAddonLastElementPtr;
		//	}
		//	break;
		//case POP:		
		//	--dpda1->stack_above_top;
		//	break;
		//case NOTHING: break;
		//defult: // break;
		//}
#define SECOND_ELEMENT_INDEX 1
		char rhsConteinerIndex = (*dpda1->dpdaIndexingForSecondElement)[dpda1->data[SECOND_ELEMENT_INDEX]][*dpda1->stack_above_top + SAVE_OFFSET - 1]; // 
		unsigned int* stackAddonLastElementPtr = stackUpdate->stackAddon[rhsConteinerIndex];
			// = stackUpdate->stackAddon[DPDA1IndexingForSecondElement[][]];
		switch (stackUpdate->stackAction) {
		case NOTHING: break;
		case PUSH:
			while (*(stackAddonLastElementPtr++));
			++stackAddonLastElementPtr;
			for (; stackAddonLastElementPtr < stackUpdate->stackAddon[rhsConteinerIndex]; --stackAddonLastElementPtr) {
				*(dpda1->stack_above_top++) = *stackAddonLastElementPtr;
			}
			break;
		case POP:		
			--dpda1->stack_above_top;
			break;
		default:; // break;
		}
			
		switch ((*dpda1->dpdaProgram)[*dpda1->data][*dpda1->stack_above_top + SAVE_OFFSET - 1].tapeAction) {
		case NO_SCROLL: break;
		case SCROLL_TO_RIGHT:
			++dpda1->data;
			break;
		default:; // break;
		}
	}
}

//#define SET_STACK_123

#ifdef SET_STACK_123
#pragma warning(push)
#pragma warning(disable : 6262)

//#pragma comment(linker, "/STACK:16777216")
#pragma comment(linker, "/STACK:16777000,16777000")
#endif
DPDA1 dpda1;// = { data, dpdaProgram, runner3/*, 0*//*Q000*/ /*...*/, dpda1.stack + SAVE_OFFSET };
char tryToAcceptDPDA(DPDA1Program * dpdaProgram, DPDA1IndexingForSecondElement* dpdaIndexingForSecondElement, int * finitStates, char * data){
	//DPDA1
	//dpda1 = { data, dpdaProgram, runner3/*, 0*//*Q000*/ /*...*/, dpda1.stack + SAVE_OFFSET };

	dpda1.data = data;
	dpda1.dpdaProgram = dpdaProgram;
	dpda1.dpdaIndexingForSecondElement = dpdaIndexingForSecondElement;
	dpda1.run = runner3;
	dpda1.stack_above_top = dpda1.stack + SAVE_OFFSET;


	*dpda1.stack_above_top = '\0';
	dpda1.run(&dpda1);

	if (dpda1.stack == dpda1.stack_above_top + SAVE_OFFSET) { // define in macro
#ifdef DEBUG_DFA_STATE
		printf("DFA: finit state\r\n");
#endif
		return 1;
	}
//	if (false) if (finitStates) for (; *finitStates; ++finitStates) {
//		if (dfa.state == *finitStates) {
//#ifdef DEBUG_DFA_STATE
//			printf("DFA: finit state\r\n");
//#endif
//			return 1;
//		}
//	}
#ifdef DEBUG_DFA_STATE
	printf("DFA: no finit state\r\n");
#endif
	return 0;
}
#ifdef SET_STACK_123
#pragma warning(pop)
#endif