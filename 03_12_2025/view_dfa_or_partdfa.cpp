#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
/*********************************************************
* N.Kozak // Lviv'2025 //                                *
*                              file: dfa_or_partdfa.cpp  *
*                                            (part impl) *
**********************************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
//#include <filesystem> C++17

#include "built_src/dfa.hpp"
#include "built_src/matcher_by_dfa.hpp"
#include "built_src/file1.hpp"
#include "built_src/file2.hpp"
#include "built_src/file3.hpp"
#include "built_src/file4.hpp"

int buildFSM(int transitionTable[SYMBOL_NUMBER][MAX_STATES], int transitionTableFinitStates[MAX_FINIT_STATES], std::string outFileNameWithoutExtension, bool partDFA = true) {
    unsigned int startStateIndex = 0;
    int maxStateIndex = 0;
    for (int iIndex = 0; iIndex < SYMBOL_NUMBER; ++iIndex)
        for (int jIndex = 0; jIndex < MAX_STATES; ++jIndex)
            if (transitionTable[iIndex][jIndex] > maxStateIndex) // Warning: no suppord zero row!
                maxStateIndex = transitionTable[iIndex][jIndex];
    int deadStateIndex = maxStateIndex; // Warning: conventionality (óìîâí³ñòü)!
    if(partDFA)   
        --maxStateIndex;

    std::string ofsStr;
    if (partDFA) {
        ofsStr = (outFileNameWithoutExtension + ".dot");
    }
    else {
        system("mkdir full_dfa >nul 2>&1"); // by command // std::filesystem::create_directories("full_dfa"); // C++17
        ofsStr = "full_dfa\\" + outFileNameWithoutExtension + ".dot";
    }
    std::ofstream ofs(ofsStr);
    if (!ofs) return -1; // error!

    ofs << "digraph FSM {\n";
    ofs << "  rankdir=LR;\n\n";

    // --- 1. start state
    ofs << "  start [shape=point];\n";
    ofs << "  start -> \"q" << startStateIndex << "\";\n\n";

    // --- 2. dinite states
    ofs << "  node [shape=doublecircle];\n";
    for (unsigned int stateIndex = 0; !stateIndex/* q0 can be final */ || transitionTableFinitStates[stateIndex]; ++stateIndex) {
        ofs << "  \"q" << transitionTableFinitStates[stateIndex] << "\";\n";
    }
    ofs << "  node [shape=circle];\n\n";

    // all states
    for (int stateIndex = 0; stateIndex <= maxStateIndex; ++stateIndex) {
        ofs << "  \"q" << stateIndex << "\";\n";
    }
    ofs << "\n";

    struct Edge { int from, to; std::string label; };
    std::vector<Edge> edges;

    auto find_edge = [&](int u, int v) -> int {
        for (size_t i = 0; i < edges.size(); ++i)
            if (edges[i].from == u && edges[i].to == v) return i;
        return -1;
    };

    for (int sym = 0; sym < SYMBOL_NUMBER; ++sym) {
        for (int from = 0; from <= maxStateIndex; ++from) {
            int to = transitionTable[sym][from];

            if (partDFA && to == deadStateIndex)
                continue;

            int idx = find_edge(from, to);

            std::ostringstream lbl;
            if (sym >= 32 && sym <= 126) {
                if (sym == '\"')
                    lbl << "'\\" << (char)sym << "'";
                else
                    lbl << "'" << (char)sym << "'";
            }
            else
                lbl << "0x" << std::uppercase << std::hex
                << std::setw(2) << std::setfill('0') << sym;

            if (idx >= 0)
                edges[idx].label += "," + lbl.str();
            else
                edges.push_back({ from, to, lbl.str() });
        }
    }

    for (auto& e : edges) {
        ofs << "  \"q" << e.from << "\" -> \"q" << e.to << "\" [label=\"" << e.label << "\"];\n";
    }

    ofs << "}\n";
    ofs.close();

    int returnValue = 0;

    if (partDFA) {
        returnValue |= system(("Graphviz-14.0.5-win32\\bin\\dot -Tsvg " + outFileNameWithoutExtension + ".dot -o " + outFileNameWithoutExtension + ".svg  >nul 2>&1").c_str());
        returnValue |= system(("Graphviz-14.0.5-win32\\bin\\dot -Tpdf " + outFileNameWithoutExtension + ".dot -o " + outFileNameWithoutExtension + ".pdf  >nul 2>&1").c_str());
    }
    else {
        returnValue |= system(("Graphviz-14.0.5-win32\\bin\\dot -Tsvg full_dfa\\" + outFileNameWithoutExtension + ".dot -o full_dfa\\" + outFileNameWithoutExtension + ".svg  >nul 2>&1").c_str());
        returnValue |= system(("Graphviz-14.0.5-win32\\bin\\dot -Tpdf full_dfa\\" + outFileNameWithoutExtension + ".dot -o full_dfa\\" + outFileNameWithoutExtension + ".pdf  >nul 2>&1").c_str());
    }

    return returnValue;
}

int main() {
    int returnValue = 0;

    std::cout << "\r[fsm1__full_dfa]................ please wait\r[fsm1__full_df";
    returnValue |= buildFSM(transitionTable1, transitionTable1FinitStates, "fsm1__full_dfa", false);
    std::cout << "\r[fsm1          ]................ please wait\r[fsm1         ";
    returnValue |= buildFSM(transitionTable1, transitionTable1FinitStates, "fsm1", true);
    std::cout << "\r[fsm2__full_dfa]................ please wait\r[fsm2__full_df";
    returnValue |= buildFSM(transitionTable2, transitionTable2FinitStates, "fsm2__full_dfa", false);
    std::cout << "\r[fsm2          ]................ please wait\r[fsm2         ";
    returnValue |= buildFSM(transitionTable2, transitionTable2FinitStates, "fsm2", true);
    std::cout << "\r[fsm3__full_dfa]................ please wait\r[fsm3__full_df";
    returnValue |= buildFSM(transitionTable3, transitionTable3FinitStates, "fsm3__full_dfa", false);
    std::cout << "\r[fsm3          ]................ please wait\r[fsm3         ";
    returnValue |= buildFSM(transitionTable3, transitionTable3FinitStates, "fsm3", true);
    std::cout << "\r[fsm4__full_dfa]................ please wait\r[fsm4__full_df";
    returnValue |= buildFSM(transitionTable4, transitionTable4FinitStates, "fsm4__full_dfa", false);
    std::cout << "\r[fsm4          ]................ please wait\r[fsm4         ";
    returnValue |= buildFSM(transitionTable4, transitionTable4FinitStates, "fsm4", true);
    if (returnValue)
        std::cout << "\r[      -       ]................ some problems...              ";
    else
        std::cout << "\r[      +       ]................ complete                      ";

    return returnValue;

}
