/******************************
* N.Kozak // Lviv'2025        *
*    file: matcher_by_dfa.hpp *
*    use with file: dfa.hpp   *
/******************************/

#define OUT_F_FINITE_STATE(FINITE_STATE_LATCH, OUT_SYMBOL, OUT_SYMBOL_VALUE, MAX_SYMBOL_DOWN_COUNT) --MAX_SYMBOL_DOWN_COUNT; FINITE_STATE_LATCH = 1; OUT_SYMBOL = OUT_SYMBOL_VALUE;
#define OUT_F_NOT_FINITE_STATE(FINITE_STATE_LATCH, OUT_SYMBOL, OUT_SYMBOL_VALUE, MAX_SYMBOL_DOWN_COUNT) --MAX_SYMBOL_DOWN_COUNT;

int* finitStates = NULL;
int finiteStateLatch = 0;
char * outSymbol;
int maxSymbolDownCount;

void runner2(DFA * dfa){
	finiteStateLatch = 0;
	for (; *dfa->data != '\0' && maxSymbolDownCount > 0; ++dfa->data){
		dfa->state = (*dfa->program)[*dfa->data][dfa->state];

		int fintState = 0;
		if (finitStates) for (int* finitStates_ = finitStates; *finitStates_; ++finitStates_) if (dfa->state == *finitStates_) fintState = 1;

		if (fintState) {
			OUT_F_FINITE_STATE(finiteStateLatch, outSymbol, dfa->data, maxSymbolDownCount);
		}
		else {
			OUT_F_NOT_FINITE_STATE(finiteStateLatch, outSymbol, dfa->data, maxSymbolDownCount);
		}

	}
}

char getFirstEntry(PROGRAM * program, int maxSymbolDownCount_, int * finitStates_, char ** data){
	maxSymbolDownCount = maxSymbolDownCount_;
	finitStates = finitStates_;
	DFA dfa = { *data, program, runner2, 0/*Q000*/ };
	dfa.run(&dfa);

	*data = outSymbol;

	return finiteStateLatch;
}
