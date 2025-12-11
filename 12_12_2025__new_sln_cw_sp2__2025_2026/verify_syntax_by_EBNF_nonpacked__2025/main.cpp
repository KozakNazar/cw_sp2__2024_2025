#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
/************************************************************************
* N.Kozak // Lviv'2024-2025 // example syntax analysis by boost::spirit *
*                              file: one_file__x86_Debug.cpp            *
*                                                (0.04v/draft version ) *
*************************************************************************/
#include "stdio.h"
#include <iostream>
#include <sstream>  // for std::ostringstream
#include <string>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp> //

#define CW_GRAMMAR cwgrammar

//#define DEBUG__IF_ERROR

#define RERUN_MODE

#define DEFAULT_INPUT_FILE "../base_test_programs_2025/file1.k03"
//#define DEFAULT_INPUT_FILE "../other_test_programs_2025/file4.k03"

#define MAX_TEXT_SIZE 8192

namespace qi = boost::spirit::qi;
namespace phx = boost::phoenix;

#define SAME_RULE(RULE) ((RULE) | (RULE))
template <typename Iterator>
struct cwgrammar : qi::grammar<Iterator> {
    cwgrammar(std::ostringstream& error_stream) : cwgrammar::base_type(program), error_stream_(error_stream) {
        //
        labeled_point = ident >> tokenCOLON;
        goto_label = tokenGOTO >> ident;
        program_name = SAME_RULE(ident);
        value_type = SAME_RULE(tokenINTEGER16);
        declaration_element = ident >> -(tokenLEFTSQUAREBRACKETS >> unsigned_value >> tokenRIGHTSQUAREBRACKETS);// Semantic array size check required.
        other_declaration_ident = tokenCOMMA >> declaration_element;
        declaration = value_type >> declaration_element >> *other_declaration_ident;
        //
        index_action = tokenLEFTSQUAREBRACKETS >> expression >> tokenRIGHTSQUAREBRACKETS;
        //
        unary_operator = SAME_RULE(tokenNOT);
        unary_operation = unary_operator >> expression;
        binary_operator = tokenAND | tokenOR | tokenEQUAL | tokenNOTEQUAL | tokenLESSOREQUAL | tokenGREATEROREQUAL | tokenLESS | tokenGREATER | tokenPLUS | tokenMINUS | tokenMUL | tokenDIV | tokenMOD;
        binary_action = binary_operator >> expression;
        //
        left_expression = group_expression | unary_operation | ident >> -index_action | value | cond_block__with_optionally_return_value;
        expression = left_expression >> *binary_action;
        //
        group_expression = tokenGROUPEXPRESSIONBEGIN >> expression >> tokenGROUPEXPRESSIONEND;
        //
        bind_left_to_right = expression >> tokenLRBIND >> ident >> -index_action;
        //
        if_expression = SAME_RULE(expression);
        body_for_true__with_optionally_return_value = SAME_RULE(block_statements__with_optionally_return_value); //tokenBEGINBLOCK >> *statement_in_while_and_if_body >> tokenENDBLOCK; // block_statements_in_while_and_if_body;
        //false_cond_block = tokenELSE >> cond_block; // without else ! ==> tokenIF >> if_expression >> body_for_true
        false_cond_block_without_else__with_optionally_return_value = tokenELSE >> tokenIF >> if_expression >> body_for_true__with_optionally_return_value;
        body_for_false__with_optionally_return_value = tokenELSE >> block_statements__with_optionally_return_value;
        cond_block__with_optionally_return_value = tokenIF >> if_expression >> body_for_true__with_optionally_return_value >> *false_cond_block_without_else__with_optionally_return_value >> (-body_for_false__with_optionally_return_value);
        cond_block__with_optionally_return_value_and_optionally_bind = cond_block__with_optionally_return_value >> -(tokenLRBIND >> ident >> -index_action);
        //
        cycle_begin_expression = SAME_RULE(expression);
        cycle_end_expression = SAME_RULE(expression);
        cycle_counter = SAME_RULE(ident);
        cycle_counter_lr_init = cycle_begin_expression >> tokenLRBIND >> cycle_counter;
        cycle_counter_init = SAME_RULE(cycle_counter_lr_init);
        cycle_counter_last_value = SAME_RULE(cycle_end_expression);
        cycle_body = tokenDO >> (statement | block_statements);
        forto_cycle = tokenFOR >> cycle_counter_init >> (tokenTO | tokenDOWNTO) >> cycle_counter_last_value >> cycle_body;
        //
        continue_while = SAME_RULE(tokenCONTINUE);
        break_while = SAME_RULE(tokenBREAK);
        statement_in_while_and_if_body = statement | continue_while | break_while;
        block_statements_in_while_and_if_body = tokenBEGINBLOCK >> *statement_in_while_and_if_body >> tokenENDBLOCK;
        while_cycle_head_expression = SAME_RULE(expression);
        while_cycle = tokenWHILE >> while_cycle_head_expression >> block_statements_in_while_and_if_body;
        //
        repeat_until_cycle_cond = SAME_RULE(expression);
        repeat_until_cycle = tokenREPEAT >> (*statement | block_statements) >> tokenUNTIL >> repeat_until_cycle_cond;
        //
        input =
#ifdef DEBUG__IF_ERROR
            qi::eps >
#endif
            tokenGET >> (ident >> -index_action | tokenGROUPEXPRESSIONBEGIN >> ident >> -index_action >> tokenGROUPEXPRESSIONEND);
#ifdef DEBUG__IF_ERROR
        input.name("input");
        tokenGET.name("tokenGET");
        tokenGROUPEXPRESSIONBEGIN.name("tokenGROUPEXPRESSIONBEGIN");
        ident.name("ident");
        index_action.name("index_action");
        tokenGROUPEXPRESSIONEND.name("tokenGROUPEXPRESSIONEND");
#endif
        output = tokenPUT >> expression;
        statement = bind_left_to_right | cond_block__with_optionally_return_value_and_optionally_bind | forto_cycle | while_cycle | repeat_until_cycle | labeled_point | goto_label | input | output | tokenSEMICOLON;
        block_statements = tokenBEGINBLOCK >> *statement >> tokenENDBLOCK;
        block_statements__with_optionally_return_value = tokenBEGINBLOCK >> *statement_in_while_and_if_body >> -expression >> tokenENDBLOCK;
        program = BOUNDARIES >> tokenNAME >> program_name >> tokenSEMICOLON >> tokenBODY >> tokenDATA >> (-declaration) >> tokenSEMICOLON >> *statement >> tokenEND;
        //
        digit = digit_0 | digit_1 | digit_2 | digit_3 | digit_4 | digit_5 | digit_6 | digit_7 | digit_8 | digit_9;
        non_zero_digit = digit_1 | digit_2 | digit_3 | digit_4 | digit_5 | digit_6 | digit_7 | digit_8 | digit_9;
        unsigned_value = ((non_zero_digit >> *digit) | digit_0) >> BOUNDARIES;
        value = (-sign) >> unsigned_value >> BOUNDARIES;
        letter_in_lower_case = a | b | c | d | e | f | g | h | i | j | k | l | m | n | o | p | q | r | s | t | u | v | w | x | y | z;
        letter_in_upper_case = A | B | C | D | E | F | G | H | I | J | K | L | M | N | O | P | Q | R | S | T | U | V | W | X | Y | Z;
        ident = tokenUNDERSCORE >> letter_in_upper_case >> letter_in_upper_case >> letter_in_upper_case >> letter_in_upper_case >> letter_in_upper_case >> letter_in_upper_case >> letter_in_upper_case >> STRICT_BOUNDARIES;
        //label = letter_in_lower_case >> *letter_in_lower_case >> STRICT_BOUNDARIES;
        //
        sign = sign_plus | sign_minus;
        sign_plus = SAME_RULE(tokenPLUS); // '+' >> BOUNDARIES;
        sign_minus = SAME_RULE(tokenMINUS); // '-' >> BOUNDARIES;
        //
        digit_0 = '0';
        digit_1 = '1';
        digit_2 = '2';
        digit_3 = '3';
        digit_4 = '4';
        digit_5 = '5';
        digit_6 = '6';
        digit_7 = '7';
        digit_8 = '8';
        digit_9 = '9';
        //
        tokenCOLON = ":" >> BOUNDARIES;
        tokenGOTO = "GOTO" >> STRICT_BOUNDARIES;
        tokenINTEGER16 = "INTEGER16" >> STRICT_BOUNDARIES;
        tokenCOMMA = "," >> BOUNDARIES;
        tokenNOT = "NOT" >> STRICT_BOUNDARIES;
        tokenAND = "AND" >> STRICT_BOUNDARIES;
        tokenOR = "OR" >> STRICT_BOUNDARIES;
        tokenEQUAL = "==" >> BOUNDARIES;
        tokenNOTEQUAL = "!=" >> BOUNDARIES;
        tokenLESSOREQUAL = "<=" >> BOUNDARIES;
        tokenGREATEROREQUAL = ">=" >> BOUNDARIES;
        tokenLESS = "<" >> BOUNDARIES;
        tokenGREATER = ">" >> BOUNDARIES;
        tokenPLUS = "+" >> BOUNDARIES;
        tokenMINUS = "-" >> BOUNDARIES;
        tokenMUL = "*" >> BOUNDARIES;
        tokenDIV = "DIV" >> STRICT_BOUNDARIES;
        tokenMOD = "MOD" >> STRICT_BOUNDARIES;
        tokenGROUPEXPRESSIONBEGIN = "(" >> BOUNDARIES;
        tokenGROUPEXPRESSIONEND = ")" >> BOUNDARIES;
        tokenLRBIND = "=:" >> BOUNDARIES;
        tokenELSE = "ELSE" >> STRICT_BOUNDARIES;
        tokenIF = "IF" >> STRICT_BOUNDARIES;
        tokenDO = "DO" >> STRICT_BOUNDARIES;
        tokenFOR = "FOR" >> STRICT_BOUNDARIES;
        tokenTO = "TO" >> STRICT_BOUNDARIES;
        tokenDOWNTO = "DOWNTO" >> STRICT_BOUNDARIES;
        tokenWHILE = "WHILE" >> STRICT_BOUNDARIES;
        tokenCONTINUE = "CONTINUE" >> STRICT_BOUNDARIES;
        tokenBREAK = "BREAK" >> STRICT_BOUNDARIES;
        tokenEXIT = "EXIT" >> STRICT_BOUNDARIES;
        tokenREPEAT = "REPEAT" >> STRICT_BOUNDARIES;
        tokenUNTIL = "UNTIL" >> STRICT_BOUNDARIES;
        tokenGET = "GET" >> STRICT_BOUNDARIES;
        tokenPUT = "PUT" >> STRICT_BOUNDARIES;
        tokenNAME = "NAME" >> STRICT_BOUNDARIES;
        tokenBODY = "BODY" >> STRICT_BOUNDARIES;
        tokenDATA = "DATA" >> STRICT_BOUNDARIES;
        tokenBEGIN = "BEGIN" >> STRICT_BOUNDARIES;
        tokenEND = "END" >> STRICT_BOUNDARIES;
        tokenBEGINBLOCK = "{" >> BOUNDARIES; // or STRICT_BOUNDARIES for keyword;
        tokenENDBLOCK = "}" >> BOUNDARIES;   // or STRICT_BOUNDARIES for keyword;
        tokenLEFTSQUAREBRACKETS = "[" >> BOUNDARIES; // or STRICT_BOUNDARIES for keyword;
        tokenRIGHTSQUAREBRACKETS = "]" >> BOUNDARIES; // or STRICT_BOUNDARIES for keyword;
        tokenSEMICOLON = ";" >> BOUNDARIES;
        // 
        //
        STRICT_BOUNDARIES = (BOUNDARY >> *(BOUNDARY)) | (!(qi::alpha | qi::char_("_")));
        BOUNDARIES = (BOUNDARY >> *(BOUNDARY) | NO_BOUNDARY);
        BOUNDARY = BOUNDARY_SPACE | BOUNDARY_TAB | BOUNDARY_CARRIAGE_RETURN | BOUNDARY_LINE_FEED | BOUNDARY_NULL;
        BOUNDARY_SPACE = " ";
        BOUNDARY_TAB = "\t";
        BOUNDARY_CARRIAGE_RETURN = "\r";
        BOUNDARY_LINE_FEED = "\n";
        BOUNDARY_NULL = "\0";
        NO_BOUNDARY = "";
        //
        tokenUNDERSCORE = "_";
        //
        A = "A";
        B = "B";
        C = "C";
        D = "D";
        E = "E";
        F = "F";
        G = "G";
        H = "H";
        I = "I";
        J = "J";
        K = "K";
        L = "L";
        M = "M";
        N = "N";
        O = "O";
        P = "P";
        Q = "Q";
        R = "R";
        S = "S";
        T = "T";
        U = "U";
        V = "V";
        W = "W";
        X = "X";
        Y = "Y";
        Z = "Z";
        //
        a = "a";
        b = "b";
        c = "c";
        d = "d";
        e = "e";
        f = "f";
        g = "g";
        h = "h";
        i = "i";
        j = "j";
        k = "k";
        l = "l";
        m = "m";
        n = "n";
        o = "o";
        p = "p";
        q = "q";
        r = "r";
        s = "s";
        t = "t";
        u = "u";
        v = "v";
        w = "w";
        x = "x";
        y = "y";
        z = "z";
        //
#ifdef DEBUG__IF_ERROR
        qi::on_error<qi::fail>(input,
            phx::ref(error_stream_) << "Error expecting " << qi::_4 << " here: \n"
            << phx::construct<std::string>(qi::_3, qi::_2) << "\n\n"
            );
#endif
    }
    std::ostringstream& error_stream_;

    qi::rule<Iterator>
        labeled_point,
        goto_label,
        program_name,
        value_type,
        declaration_element,
        other_declaration_ident,
        declaration,
        index_action,
        unary_operator,
        unary_operation,
        binary_operator,
        binary_action,
        left_expression,
        expression,
        group_expression,
        bind_left_to_right,
        if_expression,
        body_for_true,
        body_for_true__with_optionally_return_value,
        false_cond_block_without_else__with_optionally_return_value,
        body_for_false__with_optionally_return_value,
        cond_block__with_optionally_return_value,
        cond_block__with_optionally_return_value_and_optionally_bind,
        cycle_begin_expression,
        cycle_end_expression,
        cycle_counter,
        cycle_counter_lr_init,
        cycle_counter_init,
        cycle_counter_last_value,
        cycle_body,
        forto_cycle,
        while_cycle_head_expression,
        while_cycle,
        continue_while,
        break_while,
        statement_in_while_and_if_body,
        block_statements_in_while_and_if_body,
        repeat_until_cycle_cond,
        repeat_until_cycle,
        input,
        output,
        statement,
        block_statements,
        block_statements__with_optionally_return_value,
        program,
        //
        tokenCOLON, tokenGOTO, tokenINTEGER16, tokenCOMMA, tokenNOT, tokenAND, tokenOR, tokenEQUAL, tokenNOTEQUAL,
        tokenLESSOREQUAL,
        tokenGREATEROREQUAL,
        tokenLESS,
        tokenGREATER,
        tokenPLUS, tokenMINUS, tokenMUL, tokenDIV, tokenMOD, tokenGROUPEXPRESSIONBEGIN, tokenGROUPEXPRESSIONEND, tokenLRBIND,
        tokenELSE, tokenIF, tokenDO, tokenFOR, tokenTO, tokenDOWNTO, tokenWHILE, tokenCONTINUE, tokenBREAK, tokenEXIT, tokenREPEAT, tokenUNTIL, tokenGET, tokenPUT, tokenNAME, tokenBODY, tokenDATA, tokenBEGIN, tokenEND, tokenBEGINBLOCK, tokenENDBLOCK, tokenLEFTSQUAREBRACKETS, tokenRIGHTSQUAREBRACKETS, tokenSEMICOLON,
        //
        STRICT_BOUNDARIES, BOUNDARIES, BOUNDARY, BOUNDARY_SPACE, BOUNDARY_TAB, BOUNDARY_CARRIAGE_RETURN, BOUNDARY_LINE_FEED, BOUNDARY_NULL,
        NO_BOUNDARY,
        //
        sign, sign_plus, sign_minus,
        digit_0, digit_1, digit_2, digit_3, digit_4, digit_5, digit_6, digit_7, digit_8, digit_9,
        digit, non_zero_digit, value, unsigned_value,
        letter_in_upper_case, letter_in_lower_case, ident,
        //label,
        tokenUNDERSCORE,
        a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z,
        A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z;
};

template <typename Iterator>
struct cwgrammar_2 : qi::grammar<Iterator> {
#define ADDON_RULES_LIST \
value_type__ident,\
other_declaration_ident____iteration_after_one,\
input__first_part,\
input__second_part,\
output__first_part,\
output__second_part,\
unsigned_value__non_terminal,\
\
statement____iteration_after_two,\
tokenNAME__program_name,\
tokenSEMICOLON__tokenBODY,\
tokenDATA__declaration,\
tokenNAME__program_name__tokenSEMICOLON__tokenBODY,\
program____part1,\
statement__tokenEND,\
statement____iteration_after_two__tokenEND,\
block_statements____part1,/*+ NEW2025*/\
program____part2,\
\
tokenUNTIL__group_expression,\
tokenREPEAT__statement____iteration_after_two,\
tokenREPEAT__statement,\
\
statement_in_while_body_and_if_body____iteration_after_two,\
block_statements_in_while_body_and_if_body____part1,/*+ NEW2025*/\
tokenWHILE__expression,\
tokenEND__tokenWHILE,\
tokenWHILE__expression__statement_in_while_body_and_if_body,\
tokenWHILE__expression__statement_in_while_body_and_if_body____iteration_after_two,\
tokenFOR__cycle_counter_init,\
tokenTO_tokenDOWNTO__cycle_counter_last_value,\
tokenFOR__cycle_counter_init__tokenTO_tokenDOWNTO__cycle_counter_last_value,\
/*cycle_body__tokenSEMICOLON,*/\
\
/*tokenELSE__statement_in_while_body_and_if_body,*/\
/*tokenELSE__statement_in_while_body_and_if_body____iteration_after_two,*/\
/*tokenIF__tokenGROUPEXPRESSIONBEGIN,*/\
/*expression__tokenGROUPEXPRESSIONEND,*/\
/*tokenIF__tokenGROUPEXPRESSIONBEGIN__expression__tokenGROUPEXPRESSIONEND,*/\
/*body_for_true__body_for_false,*/\
tokenIF__expression,\
tokenIF__expression__body_for_true,\
false_cond_block_without_else,\
false_cond_block_without_else____iteration_after_two,\
tokenIF__expression__body_for_true__false_cond_block_without_else_iteration_after_one,\
\
tokenGROUPEXPRESSIONBEGIN__expression,\
binary_action____iteration_after_two
    cwgrammar_2(std::ostringstream& error_stream) : cwgrammar_2::base_type(program), error_stream_(error_stream) {
        //
        labeled_point = ident >> tokenCOLON;                                                                                       // +
        goto_label = tokenGOTO >> ident;                                                                                           // +
        program_name = SAME_RULE(ident);                                                                                           // + (!)
        value_type = SAME_RULE(tokenINTEGER16);                                                                                    // + (!)
        other_declaration_ident = (tokenCOMMA >> ident);                                                                           // + (!)
        other_declaration_ident____iteration_after_one = other_declaration_ident >> other_declaration_ident____iteration_after_one // + (!)
            | tokenCOMMA >> ident;                                                                                                 // + (!)
        value_type__ident = value_type >> ident;                                                                                   // + (!)
        declaration = value_type__ident >> other_declaration_ident____iteration_after_one                                          // +
            | value_type >> ident;                                                                                         // + (!)
//
        unary_operator = SAME_RULE(tokenNOT);  // + (!)
        binary_operator = tokenAND             // + (!)
            | tokenOR                          // + (!)
            | tokenEQUAL                       // + (!)
            | tokenNOTEQUAL                    // + (!)
            | tokenLESSOREQUAL                 // + (!)
            | tokenGREATEROREQUAL              // + (!)
            | tokenPLUS                        // + (!)
            | tokenMINUS                       // + (!)
            | tokenMUL                         // + (!)
            | tokenDIV                         // + (!)
            | tokenMOD;                        // + (!)
        binary_action = binary_operator >> expression; // +
        //
        left_expression = tokenGROUPEXPRESSIONBEGIN__expression >> tokenGROUPEXPRESSIONEND            // + (!)
            | unary_operator >> expression                                                // + (!)
            | ident                                                                       // +
            | value;                                                                      // +
        binary_action____iteration_after_two = binary_action >> binary_action____iteration_after_two  // +
            | binary_action >> binary_action;                        // +
        expression = left_expression >> binary_action____iteration_after_two                          // +
            | left_expression >> binary_action                                                // +
            | tokenGROUPEXPRESSIONBEGIN__expression >> tokenGROUPEXPRESSIONEND                // + (!)
            | unary_operator >> expression                                                    // + (!)
            | ident                                                                           // +
            | value;                                                                          // +
//
        tokenGROUPEXPRESSIONBEGIN__expression = tokenGROUPEXPRESSIONBEGIN >> expression;     // + (!)
        group_expression = tokenGROUPEXPRESSIONBEGIN__expression >> tokenGROUPEXPRESSIONEND; // + (!)
        //
        bind_right_to_left = ident >> rl_expression; // + (!)
        bind_left_to_right = lr_expression >> ident; // + (!)
        //
#if 0 // OLD
        (-)body_for_true = statement_in_while_body_and_if_body____iteration_after_two >> tokenSEMICOLON                                                                                   // + (!) ( tokenSEMICOLON as nonterminal ! )
            | statement_in_while_body_and_if_body >> tokenSEMICOLON                                                                                                          // + (!) ( tokenSEMICOLON as nonterminal ! )
            | tokenSEMICOLON;                                                                                                                      // + (!) ( tokenSEMICOLON as    terminal ! )
        (-)tokenELSE__statement_in_while_body_and_if_body = tokenELSE >> statement_in_while_body_and_if_body;                                                                                                       // + (!)
        (-)tokenELSE__statement_in_while_body_and_if_body____iteration_after_two = tokenELSE >> statement_in_while_body_and_if_body____iteration_after_two;                                                         // + (!)
        (+)body_for_false = tokenELSE__statement_in_while_body_and_if_body____iteration_after_two >> tokenSEMICOLON                                                                       // + (!)
            | tokenELSE__statement_in_while_body_and_if_body >> tokenSEMICOLON                                                                                              // + (!)
            | tokenELSE >> tokenSEMICOLON;                                                                                                        // + (!)
        (-)tokenIF__tokenGROUPEXPRESSIONBEGIN = tokenIF >> tokenGROUPEXPRESSIONBEGIN;                                                                           // + (!)
        (-)expression__tokenGROUPEXPRESSIONEND = expression >> tokenGROUPEXPRESSIONEND;                                                                         // +
        (-)tokenIF__tokenGROUPEXPRESSIONBEGIN__expression__tokenGROUPEXPRESSIONEND = tokenIF__tokenGROUPEXPRESSIONBEGIN >> expression__tokenGROUPEXPRESSIONEND; // +
        (-)body_for_true__body_for_false = body_for_true >> body_for_false;                                                                                     // +
        (+)cond_block = tokenIF__tokenGROUPEXPRESSIONBEGIN__expression__tokenGROUPEXPRESSIONEND >> body_for_true__body_for_false                                // +
            | tokenIF__tokenGROUPEXPRESSIONBEGIN__expression__tokenGROUPEXPRESSIONEND >> body_for_true;                                               // +
#endif
//NEW2025{//
        tokenIF__expression = tokenIF >> expression;                                                                                                    // + NEW2025
        tokenIF__expression__body_for_true = tokenIF__expression >> block_statements_in_while_body_and_if_body;                                         // + NEW2025
        false_cond_block_without_else = tokenELSE >> cond_block;                                                                                                     // + NEW2025
        false_cond_block_without_else____iteration_after_two = false_cond_block_without_else >> false_cond_block_without_else____iteration_after_two                                                  // + NEW2025
                                                | false_cond_block_without_else >> false_cond_block_without_else;                                                                 // + NEW2025
        tokenIF__expression__body_for_true__false_cond_block_without_else_iteration_after_one = tokenIF__expression__body_for_true >> false_cond_block_without_else____iteration_after_two
                                                                       | tokenIF__expression__body_for_true >> false_cond_block_without_else;                        // + NEW2025
        body_for_false = tokenELSE >> block_statements_in_while_body_and_if_body;                                                                       // + NEW2025
        cond_block = tokenIF__expression__body_for_true__false_cond_block_without_else_iteration_after_one >> body_for_false
                   | tokenIF__expression__body_for_true >> false_cond_block_without_else____iteration_after_two
                   | tokenIF__expression__body_for_true >> false_cond_block_without_else
                   | tokenIF__expression__body_for_true >> body_for_false
                   | tokenIF__expression >> block_statements_in_while_body_and_if_body;                                                                 // + NEW2025


        // cond_block__P1 = tokenIF__expression >> B        
        // B = Bo >>
        // B = Bl >>
        // Bo =
        // Bl = 
        // B = block_statements_in_while_body_and_if_body(:)

//}NEW2025//
        cycle_counter = SAME_RULE(ident);                                                                                                    // + (!)
        rl_expression = tokenRLBIND >> expression;                                                                                           // + (!)
        lr_expression = expression >> tokenLRBIND;                                                                                           // + (!)
        cycle_counter_init = cycle_counter >> rl_expression                                                                                  // +
            | lr_expression >> cycle_counter;                                                                                 // +
        //cycle_counter_last_value = SAME_RULE(value);                                                                                         // + (!)
        cycle_body = tokenDO >> block_statements // + NEW2025 // statement____iteration_after_two                                                               // + (!)
            | tokenDO >> statement;                                                                                                  // + (!)
        tokenFOR__cycle_counter_init = tokenFOR >> cycle_counter_init;                                                                       // + (!)
        tokenTO_tokenDOWNTO__cycle_counter_last_value = tokenTO >> expression      // + NEW2025 (last value as any expression)                                                         // + (!)
                                                      | tokenDOWNTO >> expression; // + NEW2025 (last value as any expression)  
		tokenFOR__cycle_counter_init__tokenTO_tokenDOWNTO__cycle_counter_last_value = tokenFOR__cycle_counter_init >> tokenTO_tokenDOWNTO__cycle_counter_last_value; // +
        // cycle_body__tokenSEMICOLON = cycle_body >> tokenSEMICOLON;  // + NEW2025                                                                          // + (!)
        forto_cycle = tokenFOR__cycle_counter_init__tokenTO_tokenDOWNTO__cycle_counter_last_value >> cycle_body; // + NEW2025                       // +
        //
        continue_while = tokenCONTINUE >> tokenWHILE;                                                                                                       // + (!)
        exit_while = tokenEXIT >> tokenWHILE;                                                                                                               // + (!) 
        tokenWHILE__expression = tokenWHILE >> expression;                                                                                                  // + (!) NEW
        tokenEND__tokenWHILE = tokenEND >> tokenWHILE;                                                                                                      // + (!) NEW
        tokenWHILE__expression__statement_in_while_body_and_if_body = tokenWHILE__expression >> statement_in_while_body_and_if_body;                                                // + NEW
        tokenWHILE__expression__statement_in_while_body_and_if_body____iteration_after_two = tokenWHILE__expression >> statement_in_while_body_and_if_body____iteration_after_two;  // + NEW
        while_cycle = tokenWHILE__expression__statement_in_while_body_and_if_body____iteration_after_two >> tokenEND__tokenWHILE                                        // + NEW
            | tokenWHILE__expression__statement_in_while_body_and_if_body >> tokenEND__tokenWHILE                                                            // + NEW
            | tokenWHILE__expression >> tokenEND__tokenWHILE;                                                                                      // + NEW
//
        tokenUNTIL__group_expression = tokenUNTIL >> expression;                                     // + (!)
        tokenREPEAT__statement____iteration_after_two = tokenREPEAT >> statement____iteration_after_two;   // + (!)
        tokenREPEAT__statement = tokenREPEAT >> statement;                                                 // + (!)
        repeat_until_cycle = tokenREPEAT__statement____iteration_after_two >> tokenUNTIL__group_expression // +
            | tokenREPEAT__statement >> tokenUNTIL__group_expression                       // +
            | tokenREPEAT >> tokenUNTIL__group_expression;                                 // + (!)
//
        input__first_part = tokenGET >> tokenGROUPEXPRESSIONBEGIN;          // + (!)
        input__second_part = ident >> tokenGROUPEXPRESSIONEND;              // + (!)
        input =
#ifdef DEBUG__IF_ERROR
            qi::eps >
#endif
            input__first_part >> input__second_part;                        // +
#ifdef DEBUG__IF_ERROR
        input.name("input");
        input__first_part.name("input__first_part");
        input__second_part.name("input__second_part");
#endif
        output__first_part = tokenPUT >> tokenGROUPEXPRESSIONBEGIN;         // + (!)
        output__second_part = expression >> tokenGROUPEXPRESSIONEND;        // + (!)
        output = output__first_part >> output__second_part;                 // +
        statement = ident >> rl_expression
            | lr_expression >> ident
            | tokenIF__expression__body_for_true__false_cond_block_without_else_iteration_after_one >> body_for_false        // + NEW2025
            | tokenIF__expression__body_for_true >> false_cond_block_without_else____iteration_after_two                     // + NEW2025
            | tokenIF__expression__body_for_true >> false_cond_block_without_else                                            // + NEW2025
            | tokenIF__expression__body_for_true >> body_for_false                                              // + NEW2025
            | tokenIF__expression >> block_statements_in_while_body_and_if_body                                 // + NEW2025
            | tokenFOR__cycle_counter_init__tokenTO_tokenDOWNTO__cycle_counter_last_value >> cycle_body/*__tokenSEMICOLON*/
            | tokenWHILE__expression__statement_in_while_body_and_if_body____iteration_after_two >> tokenEND__tokenWHILE                                        // + NEW
            | tokenWHILE__expression__statement_in_while_body_and_if_body >> tokenEND__tokenWHILE                                                            // + NEW
            | tokenWHILE__expression >> tokenEND__tokenWHILE                                                                                      // + NEW
            | tokenREPEAT__statement____iteration_after_two >> tokenUNTIL__group_expression // +
            | tokenREPEAT__statement >> tokenUNTIL__group_expression                       // +
            | tokenREPEAT >> tokenUNTIL__group_expression                                 // + (!)
            | ident >> tokenCOLON                                                                                        // + 
            | tokenGOTO >> ident                                                                                            // + 
            | input__first_part >> input__second_part                         // + 
            | output__first_part >> output__second_part                 // +
            | block_statements____part1 >> tokenENDBLOCK // + NEW2025
            | tokenBEGINBLOCK >> tokenENDBLOCK; // + NEW2025
        statement____iteration_after_two = statement >> statement____iteration_after_two// + NEW
            | statement >> statement;  // + NEW
        //
        statement_in_while_body_and_if_body = ident >> rl_expression
            | lr_expression >> ident
            | tokenIF__expression__body_for_true__false_cond_block_without_else_iteration_after_one >> body_for_false        // + NEW2025
            | tokenIF__expression__body_for_true >> false_cond_block_without_else____iteration_after_two                     // + NEW2025
            | tokenIF__expression__body_for_true >> false_cond_block_without_else                                            // + NEW2025
            | tokenIF__expression__body_for_true >> body_for_false                                              // + NEW2025
            | tokenIF__expression >> block_statements_in_while_body_and_if_body                                 // + NEW2025
            | tokenFOR__cycle_counter_init__tokenTO_tokenDOWNTO__cycle_counter_last_value >> cycle_body/*__tokenSEMICOLON*/
            | tokenWHILE__expression__statement_in_while_body_and_if_body____iteration_after_two >> tokenEND__tokenWHILE                                        // + NEW
            | tokenWHILE__expression__statement_in_while_body_and_if_body >> tokenEND__tokenWHILE                                                            // + NEW
            | tokenWHILE__expression >> tokenEND__tokenWHILE                                                                                      // + NEW
            | tokenREPEAT__statement____iteration_after_two >> tokenUNTIL__group_expression // +
            | tokenREPEAT__statement >> tokenUNTIL__group_expression                       // +
            | tokenREPEAT >> tokenUNTIL__group_expression                                 // + (!)
            | ident >> tokenCOLON                                                                                        // +
            | tokenGOTO >> ident                                                                                            // +
            | input__first_part >> input__second_part                         // +
            | output__first_part >> output__second_part                  // +
            | block_statements_in_while_body_and_if_body____part1 >> tokenENDBLOCK // + NEW2025
            | tokenBEGINBLOCK >> tokenENDBLOCK                                     // + NEW2025
            | tokenCONTINUE >> tokenWHILE                                                                                                        // + (!)
            | tokenEXIT >> tokenWHILE;                                                                                                               // + (!)             
        ;
        statement_in_while_body_and_if_body____iteration_after_two = statement_in_while_body_and_if_body >> statement_in_while_body_and_if_body____iteration_after_two                          // + NEW
            | statement_in_while_body_and_if_body >> statement_in_while_body_and_if_body;                                                                                           // + NEW 
        //
        tokenNAME__program_name = tokenNAME >> program_name;  // + NEW
        tokenSEMICOLON__tokenBODY = tokenSEMICOLON >> tokenBODY;  // + NEW
        tokenDATA__declaration = tokenDATA >> declaration;  // + NEW
        tokenNAME__program_name__tokenSEMICOLON__tokenBODY = tokenNAME__program_name >> tokenSEMICOLON__tokenBODY;  // + NEW

        program____part1 = tokenNAME__program_name__tokenSEMICOLON__tokenBODY >> tokenDATA__declaration  // + NEW
            | tokenNAME__program_name__tokenSEMICOLON__tokenBODY >> tokenDATA;  // + NEW

        statement__tokenEND = statement >> tokenEND;  // + NEW
        statement____iteration_after_two__tokenEND = statement____iteration_after_two >> tokenEND;  // + NEW
        block_statements____part1 = tokenBEGINBLOCK >> statement____iteration_after_two
            | tokenBEGINBLOCK >> statement;  // + NEW2025
        block_statements = block_statements____part1 >> tokenENDBLOCK
        | tokenBEGINBLOCK >> tokenENDBLOCK;  // + NEW2025
        statement____iteration_after_two__tokenEND = statement____iteration_after_two >> tokenEND;  // + NEW
        block_statements_in_while_body_and_if_body____part1 = tokenBEGINBLOCK >> statement_in_while_body_and_if_body____iteration_after_two
            | tokenBEGINBLOCK >> statement_in_while_body_and_if_body;  // + NEW2025
        block_statements_in_while_body_and_if_body = block_statements_in_while_body_and_if_body____part1 >> tokenENDBLOCK
            | tokenBEGINBLOCK >> tokenENDBLOCK;  // + NEW2025
        program____part2 = tokenSEMICOLON >> statement____iteration_after_two__tokenEND  // + NEW
            | tokenSEMICOLON >> statement__tokenEND  // + NEW
            | tokenSEMICOLON >> tokenEND;  // + NEW

        program = BOUNDARIES >> program____part1 >> program____part2;  // + NEW
        //
        digit = digit_0 | digit_1 | digit_2 | digit_3 | digit_4 | digit_5 | digit_6 | digit_7 | digit_8 | digit_9;
        non_zero_digit = digit_1 | digit_2 | digit_3 | digit_4 | digit_5 | digit_6 | digit_7 | digit_8 | digit_9;
        unsigned_value = ((non_zero_digit >> *digit) | digit_0) >> BOUNDARIES;
        unsigned_value__non_terminal = SAME_RULE(unsigned_value);
        value = sign >> unsigned_value__non_terminal >> BOUNDARIES // + (!) A->BC
            | unsigned_value >> BOUNDARIES; // + (!) A->a
        letter_in_lower_case = a | b | c | d | e | f | g | h | i | j | k | l | m | n | o | p | q | r | s | t | u | v | w | x | y | z;
        letter_in_upper_case = A | B | C | D | E | F | G | H | I | J | K | L | M | N | O | P | Q | R | S | T | U | V | W | X | Y | Z;
        ident = tokenUNDERSCORE >> letter_in_upper_case >> letter_in_upper_case >> letter_in_upper_case >> letter_in_upper_case >> letter_in_upper_case >> letter_in_upper_case >> letter_in_upper_case >> STRICT_BOUNDARIES;
        //label = letter_in_lower_case >> *letter_in_lower_case >> STRICT_BOUNDARIES; // !
        //
        sign = sign_plus           // + (!)
            | sign_minus;         // + (!)
        sign_plus = SAME_RULE(tokenPLUS); // '+' >> BOUNDARIES;
        sign_minus = SAME_RULE(tokenMINUS); // '-' >> BOUNDARIES;
        //
        digit_0 = '0';
        digit_1 = '1';
        digit_2 = '2';
        digit_3 = '3';
        digit_4 = '4';
        digit_5 = '5';
        digit_6 = '6';
        digit_7 = '7';
        digit_8 = '8';
        digit_9 = '9';
        //
        tokenCOLON = ":" >> BOUNDARIES;
        tokenGOTO = "GOTO" >> STRICT_BOUNDARIES;
        tokenINTEGER16 = "INTEGER16" >> STRICT_BOUNDARIES;
        tokenCOMMA = "," >> BOUNDARIES;
        tokenNOT = "NOT" >> STRICT_BOUNDARIES;
        tokenAND = "AND" >> STRICT_BOUNDARIES;
        tokenOR = "OR" >> STRICT_BOUNDARIES;
        tokenEQUAL = "==" >> BOUNDARIES;
        tokenNOTEQUAL = "!=" >> BOUNDARIES;
        tokenLESSOREQUAL = "<=" >> BOUNDARIES;
        tokenGREATEROREQUAL = ">=" >> BOUNDARIES;
        tokenPLUS = "+" >> BOUNDARIES;
        tokenMINUS = "-" >> BOUNDARIES;
        tokenMUL = "*" >> BOUNDARIES;
        tokenDIV = "DIV" >> STRICT_BOUNDARIES;
        tokenMOD = "MOD" >> STRICT_BOUNDARIES;
        tokenGROUPEXPRESSIONBEGIN = "(" >> BOUNDARIES;
        tokenGROUPEXPRESSIONEND = ")" >> BOUNDARIES;
        tokenRLBIND = ":=" >> BOUNDARIES;
        tokenLRBIND = "=:" >> BOUNDARIES;
        tokenELSE = "ELSE" >> STRICT_BOUNDARIES;
        tokenIF = "IF" >> STRICT_BOUNDARIES;
        tokenDO = "DO" >> STRICT_BOUNDARIES;
        tokenFOR = "FOR" >> STRICT_BOUNDARIES;
        tokenTO = "TO" >> STRICT_BOUNDARIES;
        tokenDOWNTO = "DOWNTO" >> STRICT_BOUNDARIES;
        tokenWHILE = "WHILE" >> STRICT_BOUNDARIES;
        tokenCONTINUE = "CONTINUE" >> STRICT_BOUNDARIES;
        tokenEXIT = "EXIT" >> STRICT_BOUNDARIES;
        tokenREPEAT = "REPEAT" >> STRICT_BOUNDARIES;
        tokenUNTIL = "UNTIL" >> STRICT_BOUNDARIES;
        tokenGET = "GET" >> STRICT_BOUNDARIES;
        tokenPUT = "PUT" >> STRICT_BOUNDARIES;
        tokenNAME = "NAME" >> STRICT_BOUNDARIES;
        tokenBODY = "BODY" >> STRICT_BOUNDARIES;
        tokenDATA = "DATA" >> STRICT_BOUNDARIES;
        tokenBEGIN = "BEGIN" >> STRICT_BOUNDARIES;
        tokenEND = "END" >> STRICT_BOUNDARIES;
        tokenBEGINBLOCK = "{" >> BOUNDARIES; // or STRICT_BOUNDARIES for keyword;
        tokenENDBLOCK = "}" >> BOUNDARIES;   // or STRICT_BOUNDARIES for keyword;
        tokenLEFTSQUAREBRACKETS = "[" >> BOUNDARIES; // or STRICT_BOUNDARIES for keyword;
        tokenRIGHTSQUAREBRACKETS = "]" >> BOUNDARIES; // or STRICT_BOUNDARIES for keyword;
        tokenSEMICOLON = ";" >> BOUNDARIES;
        // 
        //
        STRICT_BOUNDARIES = (BOUNDARY >> *(BOUNDARY)) | (!(qi::alpha | qi::char_("_")));
        BOUNDARIES = (BOUNDARY >> *(BOUNDARY) | NO_BOUNDARY);
        BOUNDARY = BOUNDARY_SPACE | BOUNDARY_TAB | BOUNDARY_CARRIAGE_RETURN | BOUNDARY_LINE_FEED | BOUNDARY_NULL;
        BOUNDARY_SPACE = " ";
        BOUNDARY_TAB = "\t";
        BOUNDARY_CARRIAGE_RETURN = "\r";
        BOUNDARY_LINE_FEED = "\n";
        BOUNDARY_NULL = "\0";
        NO_BOUNDARY = "";
        //
        tokenUNDERSCORE = "_";
        //
        A = "A";
        B = "B";
        C = "C";
        D = "D";
        E = "E";
        F = "F";
        G = "G";
        H = "H";
        I = "I";
        J = "J";
        K = "K";
        L = "L";
        M = "M";
        N = "N";
        O = "O";
        P = "P";
        Q = "Q";
        R = "R";
        S = "S";
        T = "T";
        U = "U";
        V = "V";
        W = "W";
        X = "X";
        Y = "Y";
        Z = "Z";
        //
        a = "a";
        b = "b";
        c = "c";
        d = "d";
        e = "e";
        f = "f";
        g = "g";
        h = "h";
        i = "i";
        j = "j";
        k = "k";
        l = "l";
        m = "m";
        n = "n";
        o = "o";
        p = "p";
        q = "q";
        r = "r";
        s = "s";
        t = "t";
        u = "u";
        v = "v";
        w = "w";
        x = "x";
        y = "y";
        z = "z";
        //
#ifdef DEBUG__IF_ERROR
        qi::on_error<qi::fail>(input,
            phx::ref(error_stream_) << "Error expecting " << qi::_4 << " here: \n"
            << phx::construct<std::string>(qi::_3, qi::_2) << "\n\n"
            );
#endif
    }
    std::ostringstream& error_stream_;

    qi::rule<Iterator>
        ADDON_RULES_LIST,
        labeled_point,
        goto_label,
        program_name,
        value_type,
        other_declaration_ident,
        declaration,
        unary_operator,
        binary_operator,
        binary_action,
        left_expression,
        expression,
        group_expression,
        bind_right_to_left,
        bind_left_to_right,
        //body_for_true,
        body_for_false,
        cond_block,
        cycle_counter,
        rl_expression,
        lr_expression,
        cycle_counter_init,
        //cycle_counter_last_value,
        cycle_body,
        forto_cycle,
        while_cycle,
        continue_while,
        exit_while,
        statement_in_while_body_and_if_body,
        block_statements_in_while_body_and_if_body,
        repeat_until_cycle_cond,
        repeat_until_cycle,
        input,
        output,
        statement,
        block_statements,
        program,
        //
        tokenCOLON, tokenGOTO, tokenINTEGER16, tokenCOMMA, tokenNOT, tokenAND, tokenOR, tokenEQUAL, tokenNOTEQUAL, tokenLESSOREQUAL,
        tokenGREATEROREQUAL, tokenPLUS, tokenMINUS, tokenMUL, tokenDIV, tokenMOD, tokenGROUPEXPRESSIONBEGIN, tokenGROUPEXPRESSIONEND, tokenRLBIND, tokenLRBIND,
        tokenELSE, tokenIF, tokenDO, tokenFOR, tokenTO, tokenDOWNTO, tokenWHILE, tokenCONTINUE, tokenEXIT, tokenREPEAT, tokenUNTIL, tokenGET, tokenPUT, tokenNAME, tokenBODY, tokenDATA, tokenBEGIN, tokenEND, tokenBEGINBLOCK, tokenENDBLOCK, tokenLEFTSQUAREBRACKETS, tokenRIGHTSQUAREBRACKETS, tokenSEMICOLON,
        //
        STRICT_BOUNDARIES, BOUNDARIES, BOUNDARY, BOUNDARY_SPACE, BOUNDARY_TAB, BOUNDARY_CARRIAGE_RETURN, BOUNDARY_LINE_FEED, BOUNDARY_NULL,
        NO_BOUNDARY,
        //
        sign, sign_plus, sign_minus,
        digit_0, digit_1, digit_2, digit_3, digit_4, digit_5, digit_6, digit_7, digit_8, digit_9,
        digit, non_zero_digit, value, unsigned_value,
        letter_in_upper_case, letter_in_lower_case, ident,
        //label,
        tokenUNDERSCORE,
        a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z,
        A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z;
};

size_t loadSource(char** text, char* fileName) {
    if (!fileName) {
        printf("No input file name\r\n");
        return 0;
    }

    FILE* file = fopen(fileName, "rb");

    if (file == 0) {
        printf("File not loaded\r\n");
        return 0;
    }

    fseek(file, 0, 2);
    long fileSize_ = ftell(file);
    if (fileSize_ >= 8192) {
        printf("the file(%ld bytes) is larger than %d bytes\r\n", fileSize_, 8192);
        fclose(file);
        exit(2);

    }
    size_t fileSize = fileSize_;
    rewind(file);

    if (!text) {
        printf("Load source error\r\n");
        return 0;
    }
    *text = (char*)malloc(sizeof(char) * (fileSize + 1));
    if (*text == 0) {
        fputs("Memory error", (__acrt_iob_func(2)));
        fclose(file);
        exit(2);

    }

    size_t result = fread(*text, sizeof(char), fileSize, file);
    if (result != fileSize) {
        fputs("Reading error", (__acrt_iob_func(2)));
        fclose(file);
        exit(3);

    }
    (*text)[fileSize] = '\0';

    fclose(file);

    return fileSize;
}

#define MAX_LEXEM_SIZE 1024
int commentRemover(char* text, const char* openStrSpc, const char* closeStrSpc) {
    bool eofAlternativeCloseStrSpcType = false;
    bool explicitCloseStrSpc = true;
    if (!strcmp(closeStrSpc, "\n")) {
        eofAlternativeCloseStrSpcType = true;
        explicitCloseStrSpc = false;
    }

    unsigned int commentSpace = 0;

    unsigned int textLength = strlen(text);               // strnlen(text, MAX_TEXT_SIZE);
    unsigned int openStrSpcLength = strlen(openStrSpc);   // strnlen(openStrSpc, MAX_TEXT_SIZE);
    unsigned int closeStrSpcLength = strlen(closeStrSpc); // strnlen(closeStrSpc, MAX_TEXT_SIZE);
    if (!closeStrSpcLength) {
        return -1; // no set closeStrSpc
    }
    unsigned char oneLevelComment = 0;
    if (!strncmp(openStrSpc, closeStrSpc, MAX_LEXEM_SIZE)) {
        oneLevelComment = 1;
    }

    for (unsigned int index = 0; index < textLength; ++index) {
        if (!strncmp(text + index, closeStrSpc, closeStrSpcLength) && (explicitCloseStrSpc || commentSpace)) {
            if (commentSpace == 1 && explicitCloseStrSpc) {
                for (unsigned int index2 = 0; index2 < closeStrSpcLength; ++index2) {
                    text[index + index2] = ' ';
                }
            }
            else if (commentSpace == 1 && !explicitCloseStrSpc) {
                index += closeStrSpcLength - 1;
            }
            oneLevelComment ? commentSpace = !commentSpace : commentSpace = 0;
        }
        else if (!strncmp(text + index, openStrSpc, openStrSpcLength)) {
            oneLevelComment ? commentSpace = !commentSpace : commentSpace = 1;
        }

        if (commentSpace && text[index] != ' ' && text[index] != '\t' && text[index] != '\r' && text[index] != '\n') {
            text[index] = ' ';
        }

    }

    if (commentSpace && !eofAlternativeCloseStrSpcType) {
        return -1;
    }

    return 0;
}
#include <fstream>
int main(int argc, char* argv[]) {
    char* text_;
    char fileName[128] = DEFAULT_INPUT_FILE;
    char choice[2] = { fileName[0], fileName[1] };
    system("CLS");
    std::cout << "Enter file name(Enter \"" << choice[0] << "\" to use default \"" DEFAULT_INPUT_FILE "\"):";
    std::cin >> fileName;
    if (fileName[0] == choice[0] && fileName[1] == '\0') {
        fileName[1] = choice[1];
    }
    size_t sourceSize = loadSource(&text_, fileName);
    if (!sourceSize) {
#ifdef RERUN_MODE
        (void)getchar();
        printf("\nEnter 'y' to rerun program action(to pass action enter other key): ");
        char valueByGetChar = getchar();
        if (valueByGetChar == 'y' || valueByGetChar == 'Y') {
            system((std::string("\"") + argv[0] + "\"").c_str());
        }
        return 0;
#else
        printf("Press Enter to exit . . .");
        (void)getchar();
        return 0;
#endif
    }
    printf("Original source:\r\n");
    printf("-------------------------------------------------------------------\r\n");
    printf("%s\r\n", text_);
    printf("-------------------------------------------------------------------\r\n\r\n");
    int commentRemoverResult = commentRemover(text_, "#*", "*#");
    if (commentRemoverResult) {
        printf("Comment remover return %d\r\n", commentRemoverResult);
        printf("Press Enter to exit . . .");
        (void)getchar();
        return 0;
    }
    printf("Source after comment removing:\r\n");
    printf("-------------------------------------------------------------------\r\n");
    printf("%s\r\n", text_);    
    printf("-------------------------------------------------------------------\r\n\r\n");

    std::string text(text_);

    typedef std::string     str_t;
    typedef str_t::iterator str_t_it;

    std::ostringstream error_stream;
    CW_GRAMMAR<str_t_it> cwg(error_stream);

    str_t_it begin = text.begin(), end = text.end();


    bool success = qi::parse(begin, end, cwg);

    if (!success) {
        std::cout << "\nParsing failed!\n";
        std::cout << "Error message: " << error_stream.str();
    }
    else if (begin != end) {
        std::cout << "\nUnknown fragment ofter successs parse at: \"" << str_t(begin, end) << "\"\n";
    }
    else {
        std::cout << "\nParsing success!\n";
    }

    free(text_);

    (void)getchar();

#ifdef RERUN_MODE
    printf("\nEnter 'y' to rerun program action(to pass action enter other key): ");
    char valueByGetChar = getchar();
    if (valueByGetChar == 'y' || valueByGetChar == 'Y') {
        system((std::string("\"") + argv[0] + "\"").c_str());
    }
#endif

    return 0;
}