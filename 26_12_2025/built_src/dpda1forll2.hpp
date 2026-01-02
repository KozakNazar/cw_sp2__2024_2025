/****************************
* N.Kozak // Lviv'2025      *
*    file: dpda1forll2.hpp  *
****************************/
#include "stdio.h"

//#define DEBUG_DFA_STATE

#define LL2_SYMBOL_NUMBER 256 // dup
#define LL2_MAX_STATES /*LL2_SYMBOL_NUMBER*/ 256 // 1024 // dup
#define LL2_PRECURSOR_COUNT 256

#define USE_PRE_ORDER_MARKER

#define USE_DPDA1_MODEL
#ifndef USE_DPDA1_MODEL
#define	USE_DPDA2_MODEL
#endif

//#define NO_ACTION 0xFFFF

//#define NO_RULE {NO_ACTION, NO_ACTION, NO_ACTION}
//#define NO_RULE {NO_ACTION, NO_ACTION} // NEW

//#define S 0
//#define R 1

typedef enum {
    NO_SCROLL,
	SCROLL_TO_RIGHT
} TapeAction;

typedef enum {
#ifdef USE_DPDA1_MODEL
	POP_AND_MULTIPLIPUSH
#endif
#if defined(USE_DPDA1_MODEL) && defined(USE_DPDA2_MODEL)
	,
#endif
#ifdef USE_DPDA2_MODEL
	NOTHING, // STACK_NOTHING // REMOVE ?
	PUSH,    // STACK_PUSH
	POP      // STACK_POP
#endif
} StackAction;

#define MAX_RHSCONTEINER_COUNT 3 // syntax.h
#define MAX_RHSCONTEINER_COUNT_IN_PDA (MAX_RHSCONTEINER_COUNT + 1)

#define MAX_RTOKEN_COUNT 12 // 16 // syntax.h ?
typedef struct {
	StackAction stackAction;
	unsigned char stackAddon[MAX_RHSCONTEINER_COUNT_IN_PDA][MAX_RTOKEN_COUNT]; // TODO: unsigned char
} StackUpdate;

//typedef int INSTRUCTION_PDA[2/*3, but a single state is used*/];
typedef struct { 
	unsigned char rhsVariantAddonIndexMask;// NEW 08.2025
	TapeAction tapeAction; // (1)
	StackUpdate stackUpdate; // (2)
	//int newState; // (3) // one state
} PDAInstruction /* Praecursor */;
typedef PDAInstruction DPDA1Instructions[LL2_PRECURSOR_COUNT];

typedef PDAInstruction PDAReverseInstruction;
typedef PDAReverseInstruction DPDA1ReverseInstructions[LL2_PRECURSOR_COUNT];

//DPDA1Instructions dpda1Instructions;
//DPDA1ReverseInstructions dpda1ReverseInstructions;
typedef PDAInstruction DPDA1Program[LL2_SYMBOL_NUMBER][LL2_MAX_STATES];

typedef unsigned char PrecursorIds[LL2_SYMBOL_NUMBER][LL2_MAX_STATES];
//PrecursorIds precursorIds;

//#define EMPTY_PDA_INSTRUCTION { NO_SCROLL, {PUSH, {123, 123, 4, 0}}}
//#define PDA_DEAD_STATE_INSTRUCTION { 0, NO_SCROLL, {NOTHING, {-1, -1, -1, -1}}} // -1 => ?

typedef unsigned char DPDA1IndexingForSecondElement[LL2_SYMBOL_NUMBER][LL2_MAX_STATES];
//DPDA1IndexingForSecondElement dpdaIndexingForSecondElement;

// TODO: USE MEMSET !

//DPDA1Program dpdaProgram; 
//= { /* default pass */
//	//                       {q0, a0}                    {q0, 0}                                   {q0, 1}                                   {q0, ^}                                   {q0, NT123}
//	/* a0 */{ {0, NO_SCROLL, {POP_AND_MULTIPLIPUSH, {123, 123, 4, 0}}},  PDA_DEAD_STATE_INSTRUCTION,               PDA_DEAD_STATE_INSTRUCTION,               PDA_DEAD_STATE_INSTRUCTION,               {0, NO_SCROLL, {POP_AND_MULTIPLIPUSH                   }}  },
//	/* 0  */{ {0, NO_SCROLL, {POP_AND_MULTIPLIPUSH, {123, 123, 4, 0}}},  {0, NO_SCROLL, {POP_AND_MULTIPLIPUSH, {123, 123, 4, 0}}}, {0, NO_SCROLL, {POP_AND_MULTIPLIPUSH, {123, 123, 4, 0}}}, {0, NO_SCROLL, {POP_AND_MULTIPLIPUSH, {123, 123, 4, 0}}}, {0, NO_SCROLL, {POP_AND_MULTIPLIPUSH, {123, 123, 4, 0}}}, },
//	/* 1  */{ {0, NO_SCROLL, {POP_AND_MULTIPLIPUSH, {123, 123, 4, 0}}},  {0, NO_SCROLL, {POP_AND_MULTIPLIPUSH, {123, 123, 4, 0}}}, {0, NO_SCROLL, {POP_AND_MULTIPLIPUSH, {123, 123, 4, 0}}}, {0, NO_SCROLL, {POP_AND_MULTIPLIPUSH, {123, 123, 4, 0}}}, {0, NO_SCROLL, {POP_AND_MULTIPLIPUSH, {123, 123, 4, 0}}}, },
//	/* ^  */{ {0, NO_SCROLL, {POP_AND_MULTIPLIPUSH, {123, 123, 4, 0}}},  {0, NO_SCROLL, {POP_AND_MULTIPLIPUSH, {123, 123, 4, 0}}}, {0, NO_SCROLL, {POP_AND_MULTIPLIPUSH, {123, 123, 4, 0}}}, {0, NO_SCROLL, {POP_AND_MULTIPLIPUSH, {123, 123, 4, 0}}}, {0, NO_SCROLL, {POP_AND_MULTIPLIPUSH, {123, 123, 4, 0}}}, }
//};

//typedef char Stack[8192] STATCK;
//STATCK stack = {'\0'};

#define STACK_TOP_STATE(STACK) STACK[0]

#define STACK_EMPTY_STATE(STACK) (stackSize == 0)

#define SAVE_OFFSET 0
typedef struct StructDPDA1{
	unsigned char * data_in;
	unsigned char * data_out;
	//DPDA1Program * dpdaProgram; // REMOVE!
	DPDA1ReverseInstructions * dpda1ReverseInstructions;
	PrecursorIds * precursorIds;
	DPDA1IndexingForSecondElement* dpdaIndexingForSecondElement; // by second element!!!!!
	void(*run)(struct StructDPDA1 * dpda1);
	// int state; // one state

	unsigned char* stack_above_top;
	unsigned char stack[8192 + SAVE_OFFSET]; // STATCK;


	// unsigned char stackForParentElement³[8192 + SAVE_OFFSET]; // STATCK; // TODO: add to list translator

	// TODO: add outTape

} DPDA1;

void runner3(DPDA1 * dpda1){
#ifndef USE_PRE_ORDER_MARKER
	printf("Mode without USE_PRE_ORDER_MARKER is not support.\r\n");
	printf("Define macro USE_PRE_ORDER_MARKER.\r\n");
	exit(0);
#endif
	unsigned int v__MAX_ITERATION_COUNT_FOR_SAFEGUARD_DPDA1 = 32768;
#define SAFEGUARD_DPDA1 (v__MAX_ITERATION_COUNT_FOR_SAFEGUARD_DPDA1--)
	while (dpda1->stack != dpda1->stack_above_top + SAVE_OFFSET && SAFEGUARD_DPDA1){
#ifdef USE_DPDA1_MODEL
		//StackUpdate* stackUpdate = &(*dpda1->dpdaProgram)[*dpda1->data_in][*(dpda1->stack_above_top + SAVE_OFFSET - 1)].stackUpdate;
		unsigned char precursorId__DEBUG = (*dpda1->precursorIds)[*dpda1->data_in][*(dpda1->stack_above_top + SAVE_OFFSET - 1)];
		PDAInstruction* dpda1ReverseInstruction = &(*dpda1->dpda1ReverseInstructions)[
			(*dpda1->precursorIds)[*dpda1->data_in][*(dpda1->stack_above_top + SAVE_OFFSET - 1)]
		];
		//dpda1->precursorIds[*dpda1->data_in][*(dpda1->stack_above_top + SAVE_OFFSET - 1)];
#elif defined(USE_DPDA2_MODEL)
		//StackAction *stackAction = (*dpda1->dpdaProgram)[*dpda1->data_in][*dpda1->stack_top].stackUpdate.stackAction;
		StackUpdate* stackUpdate = &(*dpda1->dpdaProgram)[*dpda1->data_in][*(dpda1->stack_above_top + SAVE_OFFSET - 1)].stackUpdate;
		//TapeAction * tapeAction = &(*dpda1->dpdaProgram)[*dpda1->data_in][*dpda1->stack_above_top + SAVE_OFFSET - 1].tapeAction;
#endif

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

		//bool divergencePointFromToOutTape = false;
#ifdef USE_DPDA1_MODEL
		switch (dpda1ReverseInstruction->tapeAction) {
#elif defined(USE_DPDA2_MODEL)
			switch ((*dpda1->dpdaProgram)[*dpda1->data_in][*(dpda1->stack_above_top + SAVE_OFFSET - 1)].tapeAction) {
#endif
		case NO_SCROLL: break;
		case SCROLL_TO_RIGHT:
			//divergencePointToOutTape = true;
			++dpda1->data_in;
			break;
		default:
			printf("ERROR.\r\n.");
			exit(0);
			; // break;
		}

#define SECOND_ELEMENT_INDEX 1
#ifdef USE_DPDA1_MODEL
		char rhsConteinerIndex = (*dpda1->dpdaIndexingForSecondElement)[dpda1->data_in[SECOND_ELEMENT_INDEX]][*(dpda1->stack_above_top + SAVE_OFFSET - 1)]; // 
#elif defined(USE_DPDA2_MODEL)
		...
#endif		
		//NEW//unsigned char* stackAddonLastElementPtr = stackUpdate->stackAddon[rhsConteinerIndex];
			// = stackUpdate->stackAddon[DPDA1IndexingForSecondElement[][]];
		switch (dpda1ReverseInstruction->stackUpdate.stackAction) {

#ifdef USE_DPDA1_MODEL
		case POP_AND_MULTIPLIPUSH: // 

			//if ((*dpda1->dpdaProgram)[*dpda1->data_in][*dpda1->stack_above_top + SAVE_OFFSET - 1].tapeAction
			//	== SCROLL_TO_RIGHT) {			
			//}

			*dpda1->data_out++ = *dpda1->stack_above_top--; // POP for first
			
			// multi push
#define SAFEGUARD_STACK_ADDON (stackAddonElementIndex < MAX_RTOKEN_COUNT)
			for (unsigned char stackAddonElementIndex = 0; dpda1ReverseInstruction->stackUpdate.stackAddon[rhsConteinerIndex][stackAddonElementIndex] != EMPTY_TOKEN_LEXEM_ID && SAFEGUARD_STACK_ADDON; ++stackAddonElementIndex) {
				*(dpda1->stack_above_top++) = dpda1ReverseInstruction->stackUpdate.stackAddon[rhsConteinerIndex][stackAddonElementIndex];
			}
#undef SAFEGUARD_STACK_ADDON

			// parrent id stack
			// int out
			//
			// new [] + index
			//
			break;
#endif			
#ifdef USE_DPDA1_MODEL
			//case NOTHING: // DELETE
			//	break;
			//case PUSH: // DELETE
			//	while (*(stackAddonLastElementPtr++));
			//	++stackAddonLastElementPtr;
			//	for (; stackAddonLastElementPtr < stackUpdate->stackAddon[rhsConteinerIndex]; --stackAddonLastElementPtr) {
			//		*(dpda1->stack_above_top++) = *stackAddonLastElementPtr;
			//	}
			//	break;
			//case POP: // DELETE	
			//	--dpda1->stack_above_top;
			//	break;
#endif
		default:
			printf("ERROR.\r\n.");
			exit(0);
			; // break;
		}
	}
#undef SAFEGUARD_DPDA1
}

//#define SET_STACK_123

#ifdef SET_STACK_123
#pragma warning(push)
#pragma warning(disable : 6262)

//#pragma comment(linker, "/STACK:16777216")
#pragma comment(linker, "/STACK:16777000,16777000")
#endif
DPDA1 dpda1;// = { data, dpdaProgram, runner3/*, 0*//*Q000*/ /*...*/, dpda1.stack + SAVE_OFFSET };
char tryToAcceptDPDA(/*DPDA1Program * dpdaProgram, */PrecursorIds* precursorIds, DPDA1ReverseInstructions* dpda1ReverseInstructions, DPDA1IndexingForSecondElement* dpdaIndexingForSecondElement, unsigned char startState, unsigned char* data_in, unsigned char* data_out){
	//DPDA1
	//dpda1 = { data, dpdaProgram, runner3/*, 0*//*Q000*/ /*...*/, dpda1.stack + SAVE_OFFSET };

	dpda1.data_in = data_in;
	dpda1.data_out = data_out;
//	dpda1.dpdaProgram = dpdaProgram;
	dpda1.dpda1ReverseInstructions = dpda1ReverseInstructions;
	dpda1.precursorIds = precursorIds;
	dpda1.dpdaIndexingForSecondElement = dpdaIndexingForSecondElement;
	dpda1.run = runner3;
	dpda1.stack_above_top = dpda1.stack + SAVE_OFFSET;

	*dpda1.stack_above_top++ = startState; // init by start symbol
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