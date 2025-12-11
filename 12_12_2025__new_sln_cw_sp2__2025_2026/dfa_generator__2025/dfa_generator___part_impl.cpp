#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
/************************************************************************
* N.Kozak // Lviv'2025 //                                               *
*                              file: dfa_generator___part_impl.cpp      *
*                                                           (part impl) *
*************************************************************************/
#include <stdio.h>
#include <string.h>

#include <stdlib.h>

#define USE_DFA_MINIMIZATION

#define FILE1_A "../built_src/file1.hpp"
#define FILE1_B "../built_src/file1.txt"
#define TABLE1 "transitionTable1"
#define RN1 TOKENS_RN

#define FILE2_A "../built_src/file2.hpp"
#define FILE2_B "../built_src/file2.txt"
#define TABLE2 "transitionTable2"
#define RN2 KEYWORDS_RN

#define FILE3_A "../built_src/file3.hpp"
#define FILE3_B "../built_src/file3.txt"
#define TABLE3 "transitionTable3"
#define RN3 IDENTIFIERS_RN

#define FILE4_A "../built_src/file4.hpp"
#define FILE4_B "../built_src/file4.txt"
#define TABLE4 "transitionTable4"
#define RN4 UNSIGNEDVALUES_RN


//#define MAX_STATES 128
#define MAX_STATES 1024
//#define MAX_SYMBOLS 26
#define SYMBOL_NUMBER 256
#define EPSILON -1

#define ND -1

struct Transition {
    int from;
    int to;
    int symbolCode; // -1 = EPSILON
};

Transition transitions[1024];
int transition_count = 0;

int finit_states[1024]; // MAX_STATES
int finit_states_count = 0;
//int dead_state = 0;

struct NFA {
    int start;
    int end;
};

void add_transition(int from, int to, int symbolCode) {
    transitions[transition_count++] = { from, to, symbolCode };
}

int transition_table[MAX_STATES][SYMBOL_NUMBER];

void epsilon_closure(bool closure[], int state) {
    if (closure[state]) return;
    closure[state] = true;
    for (int i = 0; i < transition_count; ++i) {
        if (transitions[i].from == state && transitions[i].symbolCode == EPSILON)
            epsilon_closure(closure, transitions[i].to);
    }
}

void generate_transition_table(int state_counter) {
    memset(transition_table, -1, sizeof(transition_table));
    for (int s = 0; s < state_counter; ++s) {
        for (int sym = 0; sym < SYMBOL_NUMBER; ++sym) {
            bool closure[MAX_STATES] = { 0 };
            epsilon_closure(closure, s);
            for (int i = 0; i < transition_count; ++i) {
                if (closure[transitions[i].from] && transitions[i].symbolCode == sym) {
                    transition_table[s][sym] = transitions[i].to;
                }
            }
        }
    }
}

void print_transition_table(int state_counter, int dead_state) {
    if (dead_state != -1) {
        for (int stateIndex = 0; stateIndex < state_counter; ++stateIndex) {
            printf("#define Q%03d %d\n", stateIndex, stateIndex);
        }
    }
    printf("int transition_table[%d][%d] = {\n", SYMBOL_NUMBER, state_counter);
    printf("//          ");

    for (int i = 0; i < state_counter; ++i) {
        printf(" Q%03d  ", i);
    }

    printf("\n");
    for (int j = 0; j < SYMBOL_NUMBER; ++j) {
        if (j >= 32 && j <= 126) {
            printf("/*  '%c' */ {", j);
        }
        else {
            printf("/* \\x%02X */ {", j);
        }

        for (int i = 0; i < state_counter; ++i) {
            if (transition_table[i][j] != ND) {
                printf(" Q%03d", transition_table[i][j]);
            }
            else if (dead_state == -1) {
                printf("  ND ");
            }
            else {
                printf(" Q%03d", dead_state);
            }
            if (i < state_counter - 1) {
                printf(", ");
            }

        }
        printf(" }%s\n", j < SYMBOL_NUMBER - 1 ? "," : "");
    }
    printf("};\n");
}

void print_transition_table_to_file(char* fileName, char* tableName, int state_counter, int dead_state) {
    FILE* f = fopen(fileName, "w");
    if (!f) {
        perror("fopen");
        return;
    }

    fprintf(f, "#define _CRT_SECURE_NO_WARNINGS\n\n");
    fprintf(f, "#define SYMBOL_NUMBER 256\n");
    //fprintf(f, "#define STATE_NUMBER %d\n\n", state_counter);
    fprintf(f, "#define MAX_STATES 1024\n");
    fprintf(f, "#define MAX_FINIT_STATES 1024\n");

    fprintf(f, "\n");

    if (dead_state != -1) {
        for (int stateIndex = 0; stateIndex < state_counter; ++stateIndex) {
            fprintf(f, "#define Q%03d %d\n", stateIndex, stateIndex);
        }
    }

    fprintf(f, "\n");

    fprintf(f, "int %s[SYMBOL_NUMBER][MAX_STATES] = {\n", tableName);
    fprintf(f, "//          ");

    for (int i = 0; i < state_counter; ++i) {
        fprintf(f, " Q%03d  ", i);
    }

    fprintf(f, "\n");
    for (int j = 0; j < SYMBOL_NUMBER; ++j) {
        if (j >= 32 && j <= 126) {
            fprintf(f, "/*  '%c' */ {", j);
        }
        else {
            fprintf(f, "/* \\x%02X */ {", j);
        }

        for (int i = 0; i < state_counter; ++i) {
            if (transition_table[i][j] != ND) {
                fprintf(f, " Q%03d", transition_table[i][j]);
            }
            else if (dead_state == -1) {
                fprintf(f, "  ND ");
            }
            else {
                fprintf(f, " Q%03d", dead_state);
            }
            if (i < state_counter - 1) {
                fprintf(f, ", ");
            }
        }
        fprintf(f, " }%s\n", j < SYMBOL_NUMBER - 1 ? "," : "");
    }
    fprintf(f, "};\n");

    fprintf(f, "\n");

    fprintf(f, "int %sFinitStates[MAX_FINIT_STATES] = { ", tableName);
    for (int finitStatesIndex = 0; finitStatesIndex < finit_states_count; ++finitStatesIndex) {
        fprintf(f, "Q%03d%s", finit_states[finitStatesIndex], finitStatesIndex + 1 == finit_states_count ? " " : ", ");
    }
    fprintf(f, "};\n");

    fclose(f);
}

char* process_alternation(char* inputStr, int baseState, int* lastFreeState);

char* process_term(char* inputStr, int startState, int* nextFreeState) {
    while ((inputStr[0] != ')' || inputStr[1] == ')')
        && (inputStr[0] != '|' || inputStr[1] == '|')
        && (inputStr[-1] == '|' || inputStr[0] != '|' || inputStr[1] != '|' || inputStr[2] != '|') // ! functionally incomplete implementation
        && inputStr[0] != '\0') {

        if (inputStr[0] == '~' && inputStr[1] != '~' ||
            inputStr[0] == '^' && inputStr[1] != '^') {
            ++inputStr;
            continue;
        }

        if (inputStr[0] == '(' && inputStr[1] != '(') {
            inputStr = process_alternation(++inputStr, startState, nextFreeState);
        }
        else {
            add_transition(startState, *nextFreeState, (unsigned char)*inputStr);
            if (inputStr[0] == '(' && inputStr[1] == '(' ||
                inputStr[0] == ')' && inputStr[1] == ')' ||
                inputStr[0] == '|' && inputStr[1] == '|' ||
                inputStr[0] == '~' && inputStr[1] == '~' ||
                inputStr[0] == '^' && inputStr[1] == '^') {
                ++inputStr;
            }
            ++inputStr;
            ++* nextFreeState;
        }

        startState = *nextFreeState - 1;

    }

    if (inputStr[0] == '|' && inputStr[1] != '|' ||
        inputStr[-1] != '|' && inputStr[0] == '|' && inputStr[1] == '|' && inputStr[2] == '|' // ! functionally incomplete implementation
        ) {
        ++inputStr;
    }

    return inputStr;
}

char* process_alternation(char* inputStr, int baseState, int* nextFreeState) {
    int alternation_outs_counter = 0;
    int alternation_outs[1024] = { 0 };
    int alternation_outs_pass_and_iteration_and_finit[1024] = { 0 };

    while ((inputStr[0] != ')' || inputStr[1] == ')')
        && inputStr[0] != '\0') {
        if (inputStr[0] == '~' && inputStr[1] != '~') {
            ++inputStr;
            continue;
        }
        if (inputStr[0] == '^' && inputStr[1] == '|') {
            finit_states[finit_states_count++] = baseState;
            inputStr += 2;
            continue;
        }

        inputStr = process_term(inputStr, baseState, nextFreeState);

        if (inputStr[0] != '\0' && inputStr[0] == ')' && inputStr[1] == '~' && inputStr[2] != '~') {
            alternation_outs_pass_and_iteration_and_finit[alternation_outs_counter] = 1;
        }
        alternation_outs[alternation_outs_counter++] = transition_count - 1;
    }

    for (int index = 0; index < alternation_outs_counter; ++index) {
        int enclosedState = transitions[alternation_outs[index] % 1024].to;
        int notFinitEnclosedState = 1;
        for (int finitStatesIndex = 0; finitStatesIndex < finit_states_count; ++finitStatesIndex) {
            if (finit_states[finitStatesIndex] == enclosedState) {
                notFinitEnclosedState = 0;
                break;
            }
        }

        if (notFinitEnclosedState) {
            transitions[alternation_outs[index] % 1024].to = *nextFreeState;

            for (int transitionIndex = 0; transitionIndex < transition_count; ++transitionIndex) {
                if (transitions[transitionIndex].to == enclosedState) {
                    transitions[transitionIndex].to = *nextFreeState;
                }
            }

            if (alternation_outs_pass_and_iteration_and_finit[alternation_outs_counter - 1] == 1) {
                add_transition(*nextFreeState, *nextFreeState, (unsigned char)transitions[alternation_outs[index] % 1024].symbolCode);
            }
        }

        if (alternation_outs_pass_and_iteration_and_finit[index] == 1) { // !
            finit_states[finit_states_count++] = *nextFreeState;
        }
    }

    ++* nextFreeState;

    if (inputStr[0] == ')' && inputStr[1] != ')') {
        ++inputStr;
    }
    if (inputStr[0] == '~' && inputStr[1] != '~') {
        ++inputStr;
    }

    return inputStr;
}

#ifdef USE_DFA_MINIMIZATION
void removing_unreachable_DFA_states(int* dead_state, int* nextFreeState) {
    int state_counter = *nextFreeState;
    int old2NewStates[MAX_STATES] = { 0 }; // always 0 -> 0
    int old2NewStateCount = 1;

    int new_finit_states[MAX_STATES]; // MAX_STATES
    int new_finit_states_count = 0;
    int new_dead_state = 0;

    for (int state = 1/*0 is start state*/; state < state_counter; ++state) {
        int old2NewStateIndex = old2NewStateCount - 1;
        while (--old2NewStateIndex >= 0) if (old2NewStates[old2NewStateIndex] == state) break;
        for (int transitionIndex = 0; transitionIndex < transition_count; ++transitionIndex) {
            if (transitions[transitionIndex].to == state) {
                if (old2NewStateIndex == -1) {
                    old2NewStateIndex = old2NewStateCount++;
                }
                old2NewStates[old2NewStateIndex] = state;
            }
        }
    }

    // new dead state
    old2NewStates[old2NewStateCount++] = *dead_state;
    new_dead_state = old2NewStateCount - 1;


    for (int old2NewStateIndex = 0; old2NewStateIndex < old2NewStateCount; ++old2NewStateIndex) {
        // new finit states
        for (int finitStatesIndex = 0; finitStatesIndex < finit_states_count; ++finitStatesIndex) {
            if (finit_states[finitStatesIndex] == old2NewStates[old2NewStateIndex]) {
                new_finit_states[new_finit_states_count++] = old2NewStateIndex;
            }
        }
    }

    for (int transitionIndex = 0; transitionIndex < transition_count; ++transitionIndex) {
        for (int old2NewStateIndex = 0; old2NewStateIndex < old2NewStateCount; ++old2NewStateIndex) {
            if (old2NewStates[old2NewStateIndex] == transitions[transitionIndex].from) {
                transitions[transitionIndex].from = old2NewStateIndex;
            }
            if (old2NewStates[old2NewStateIndex] == transitions[transitionIndex].to) {
                transitions[transitionIndex].to = old2NewStateIndex;
            }
        }
    }

    for (int newFinitStateIndex = 0; newFinitStateIndex < new_finit_states_count; ++newFinitStateIndex)
        finit_states[newFinitStateIndex] = new_finit_states[newFinitStateIndex];
    finit_states_count = new_finit_states_count;

    *dead_state = new_dead_state;
    *nextFreeState = old2NewStateCount;
}
#endif

#define TOKENS_RE         ";|:=|=:|\\+|-|\\*|,|==|!=|:|\\[|\\]|\\(|\\)|\\{|\\}|<=|>=|[_0-9A-Za-z]+|[^ \t\r\f\v\n]"
#define KEYWORDS_RE       ";|:=|=:|\\+|-|\\*|,|==|!=|:|\\[|\\]|\\(|\\)|\\{|\\}|NAME|DATA|BODY|END|BREAK|CONTINUE|GET|PUT|IF|ELSE|FOR|TO|DOWNTO|DO|WHILE|REPEAT|UNTIL|GOTO|DIV|MOD|<=|>=|NOT|AND|OR|INTEGER16"
#define IDENTIFIERS_RE    "_[A-Z][A-Z][A-Z][A-Z][A-Z][A-Z][A-Z]"
#define UNSIGNEDVALUES_RE "0|[1-9][0-9]*"

// RN_SPEC (, ), |, ~, ^

#define TOKENS_RN         "("\
                          ";"\
                          "|:(^|=)"\
                          "|=(:|=)"\
                          "|+"\
                          "|-"\
                          "|*"\
                          "|,"\
                          "|!="\
                          "|["\
                          "|]"\
                          "|(("\
                          "|))"\
                          "|{"\
                          "|}"\
                          "|<="\
                          "|>="\
                          "|"\
                          "(_|0|1|2|3|4|5|6|7|8|9|A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z|a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z)~"\
                          "|"\
                          "\x01|\x02|\x03|\x04|\x05|\x06|\x07|\x08|\x0E|\x0F|\x10|\x11|\x12|\x13|\x14|\x15|\x16|\x17|\x18|\x19|\x1A|\x1B|\x1C|\x1D|\x1E|\x1F|\"|#|$|%|&|\'|.|/|?|@|\\|^^|`||||~~|\x7F|\x80|\x81|\x82|\x83|\x84|\x85|\x86|\x87|\x88|\x89|\x8A|\x8B|\x8C|\x8D|\x8E|\x8F|\x90|\x91|\x92|\x93|\x94|\x95|\x96|\x97|\x98|\x99|\x9A|\x9B|\x9C|\x9D|\x9E|\x9F|\xA0|\xA1|\xA2|\xA3|\xA4|\xA5|\xA6|\xA7|\xA8|\xA9|\xAA|\xAB|\xAC|\xAD|\xAE|\xAF|\xB0|\xB1|\xB2|\xB3|\xB4|\xB5|\xB6|\xB7|\xB8|\xB9|\xBA|\xBB|\xBC|\xBD|\xBE|\xBF|\xC0|\xC1|\xC2|\xC3|\xC4|\xC5|\xC6|\xC7|\xC8|\xC9|\xCA|\xCB|\xCC|\xCD|\xCE|\xCF|\xD0|\xD1|\xD2|\xD3|\xD4|\xD5|\xD6|\xD7|\xD8|\xD9|\xDA|\xDB|\xDC|\xDD|\xDE|\xDF|\xE0|\xE1|\xE2|\xE3|\xE4|\xE5|\xE6|\xE7|\xE8|\xE9|\xEA|\xEB|\xEC|\xED|\xEE|\xEF|\xF0|\xF1|\xF2|\xF3|\xF4|\xF5|\xF6|\xF7|\xF8|\xF9|\xFA|\xFB|\xFC|\xFD|\xFE|\xFF"\
                          //\0

#define KEYWORDS_RN__     "("\
                          ";"\
                          "|:="\
                          "|=:"\
                          "|+"\
                          "|-"\
                          "|*"\
                          "|,"\
                          "|=="\
                          "|!="\
                          "|:"\
                          "|["\
                          "|]"\
                          "|(("\
                          "|))"\
                          "|{"\
                          "|}"\
                          "|NAME"\
                          "|DATA"\
                          "|BODY"\
                          "|END"\
                          "|BREAK"\
                          "|CONTINUE"\
                          "|GET"\
                          "|PUT"\
                          "|IF"\
                          "|ELSE"\
                          "|FOR"\
                          "|TO"\
                          "|DOWNTO"\
                          "|DO"\
                          "|WHILE"\
                          "|REPEAT"\
                          "|UNTIL"\
                          "|GOTO"\
                          "|DIV"\
                          "|MOD"\
                          "|<="\
                          "|>="\
                          "|NOT"\
                          "|AND"\
                          "|OR"\
                          "|INTEGER16"\
                          //\0

#define KEYWORDS_RN_      "("\
                          ";"\
                          "|:="\
                          "|:"\
                          "|=:"\
                          "|=="\
                          "|+"\
                          "|-"\
                          "|*"\
                          "|,"\
                          "|!="\
                          "|["\
                          "|]"\
                          "|(("\
                          "|))"\
                          "|{"\
                          "|}"\
                          "|NAME"\
                          "|DATA"\
                          "|BODY"\
                          "|END"\
                          "|BREAK"\
                          "|CONTINUE"\
                          "|GET"\
                          "|PUT"\
                          "|IF"\
                          "|ELSE"\
                          "|FOR"\
                          "|TO"\
                          "|DOWNTO"\
                          "|DO"\
                          "|WHILE"\
                          "|REPEAT"\
                          "|UNTIL"\
                          "|GOTO"\
                          "|DIV"\
                          "|MOD"\
                          "|<="\
                          "|>="\
                          "|NOT"\
                          "|AND"\
                          "|OR"\
                          "|INTEGER16"\
                          //\0

#define KEYWORDS_RN       "("\
                          ";"\
                          "|:(^|=)"\
                          "|=(:|=)"\
                          "|+"\
                          "|-"\
                          "|*"\
                          "|,"\
                          "|!="\
                          "|["\
                          "|]"\
                          "|(("\
                          "|))"\
                          "|{"\
                          "|}"\
                          "|N(AME|OT)"\
                          "|D(ATA|O(^|WNTO)|IV)"\
                          "|B(ODY|REAK)"\
                          "|E(ND|LSE)"\
                          "|CONTINUE"\
                          "|G(ET|OTO)"\
                          "|PUT"\
                          "|I(F|NTEGER16)"\
                          "|FOR"\
                          "|TO"\
                          "|WHILE"\
                          "|REPEAT"\
                          "|UNTIL"\
                          "|MOD"\
                          "|<="\
                          "|>="\
                          "|AND"\
                          "|OR"\
                          //\0

#define IDENTIFIERS_RN    "("\
                          "_"\
                          "(A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z)"\
                          "(A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z)"\
                          "(A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z)"\
                          "(A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z)"\
                          "(A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z)"\
                          "(A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z)"\
                          "(A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z)"\
                          //\0

#define UNSIGNEDVALUES_RN "("\
                          "0"\
                          "|"\
                          "(1|2|3|4|5|6|7|8|9)"\
                          "(^|0|1|2|3|4|5|6|7|8|9)~"\
                          //\0


void generatorB(char* rn, char * fileNameA, char* fileNameB, char* tableName) { // "C"
    printf("\nNOT FULLY IMPLEMENTED!\n\n");

    int dead_state = -1;
    int baseState = 0;
    int nextFreeState = baseState + 1;

    if (*rn != '\0' && *rn == '(') {
        rn = process_alternation(++rn, baseState, &nextFreeState);
        finit_states[finit_states_count++] = nextFreeState - 1;
        dead_state = nextFreeState++;
    }

    printf("Transitions (%s):\n", tableName);
    for (int transitionIndex = 0; transitionIndex < transition_count; ++transitionIndex) {
        if (transitions[transitionIndex].symbolCode >= 32 && transitions[transitionIndex].symbolCode <= 126)
            printf(" Q%03d ---('%c')--> Q%03d \n", transitions[transitionIndex].from, transitions[transitionIndex].symbolCode, transitions[transitionIndex].to);
        else
            printf(" Q%03d ---(\\x%02X)--> Q%03d \n", transitions[transitionIndex].from, 0xFF & transitions[transitionIndex].symbolCode, transitions[transitionIndex].to);
    }
    printf(".\n");

    printf("Finit states (%s): ", tableName);
    for (int finitStatesIndex = 0; finitStatesIndex < finit_states_count; ++finitStatesIndex) {
        printf("Q%03d%s", finit_states[finitStatesIndex], finitStatesIndex + 1 == finit_states_count ? " " : ", ");
    }
    printf(".\n");
    printf("  Dead state (%s): Q%03d .\n", tableName, dead_state);

#ifdef USE_DFA_MINIMIZATION
    removing_unreachable_DFA_states(&dead_state, &nextFreeState);
#endif

    printf("NEW:\n\n");

    printf("Transitions (%s):\n", tableName);
    for (int transitionIndex = 0; transitionIndex < transition_count; ++transitionIndex) {
        if (transitions[transitionIndex].symbolCode >= 32 && transitions[transitionIndex].symbolCode <= 126)
            printf(" Q%03d ---('%c')--> Q%03d \n", transitions[transitionIndex].from, transitions[transitionIndex].symbolCode, transitions[transitionIndex].to);
        else
            printf(" Q%03d ---(\\x%02X)--> Q%03d \n", transitions[transitionIndex].from, 0xFF & transitions[transitionIndex].symbolCode, transitions[transitionIndex].to);
    }
    printf(".\n");

    printf("Finit states (%s): ", tableName);
    for (int finitStatesIndex = 0; finitStatesIndex < finit_states_count; ++finitStatesIndex) {
        printf("Q%03d%s", finit_states[finitStatesIndex], finitStatesIndex + 1 == finit_states_count ? " " : ", ");
    }
    printf(".\n");
    printf("  Dead state (%s): Q%03d .\n", tableName, dead_state);
    
    int state_counter = nextFreeState;

    generate_transition_table(state_counter);

    if (state_counter <= 28) {       
        printf("Transition table (%s) of a quasi-deterministic finite state machine (QFA):\n", tableName);
        print_transition_table(state_counter, -1);
    }
    else {
        printf("Transition table (%s) of a quasi-deterministic finite state machine (QFA) print to file only. Display will take too long.\n", tableName);
    }
    print_transition_table_to_file(fileNameB, tableName, state_counter, -1);

    if (state_counter <= 28) {
        printf("Transition table (%s) of a deterministic finite state machine (DFA):\n", tableName);
        print_transition_table(state_counter, dead_state);
    }
    else {
        printf("Transition table (%s) of a deterministic finite state machine (DFA) print to file only. Display will take too long.\n", tableName);
    }
    print_transition_table_to_file(fileNameA, tableName, state_counter, dead_state);
}

void printAlternationSymbol(char * exludedSymbols) {
    char printAlternationSeparator = 0;
    for (unsigned int symbols = 1; symbols <= 255; ++symbols){
        char* exludedSymbols_ = exludedSymbols;
        for (; *exludedSymbols_; ++exludedSymbols_) {
            if (*exludedSymbols_ == symbols) {
                break;
            }
        }

        if (!*exludedSymbols_) {
            if (printAlternationSeparator) {
                printf("|");
            }
            else {
                printAlternationSeparator = 1;
            }
            if (symbols >= 32 && symbols <= 126) {
                if (symbols == '\\' ||
                    symbols == '\'' ||
                    symbols == '\"') {
                    printf("\\%c", symbols);
                }
                else if (symbols == '('  ||
                    symbols == ')'  ||
                    symbols == '|'  ||
                    symbols == '~'  ||
                    symbols == '^' ) {
                    printf("%c%c", symbols, symbols);
                }
                else {
                    printf("%c", symbols);
                }
            }
            else {
                printf("\\x%02X", symbols);
            }

        }
    }
}

//#define PRINT_ALTERNATION_SYMBOL
int main() {
#ifndef PRINT_ALTERNATION_SYMBOL
    transition_count = 0;
    finit_states_count = 0;
    generatorB((char*)RN1, (char*)FILE1_A, (char*)FILE1_B, (char*)TABLE1);
    transition_count = 0;
    finit_states_count = 0;
    generatorB((char*)RN2, (char*)FILE2_A, (char*)FILE2_B, (char*)TABLE2);
    transition_count = 0;
    finit_states_count = 0;
    generatorB((char*)RN3, (char*)FILE3_A, (char*)FILE3_B, (char*)TABLE3);
    transition_count = 0;
    finit_states_count = 0;
    generatorB((char*)RN4, (char*)FILE4_A, (char*)FILE4_B, (char*)TABLE4);

    return 0;
#else
    //";|:=|=:|\\+|-|\\*|,|==|!=|:|\\[|\\]|\\(|\\)|\\{|\\}|<=|>=|[_0-9A-Za-z]+|[^ \t\r\f\v\n]"
    //;|:=|=:|\\+|-|\\*|,|==|!=|:|\\[|\\]|\\(|\\)|\\{|\\}|<=|>=|[_0-9A-Za-z]+|[^ \t\r\f\v\n]
    ";:=+-*,!:[](){}<>"
    "_0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
    " \t\r\f\v\n";
    printAlternationSymbol((char*)
        ";:=+-*,!:[](){}<>"
        "_0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
        " \t\r\f\v\n"   
    );
    (void)getchar();
#endif
}