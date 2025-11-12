#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // lexica__2025                 *
*                         file: syntax_one.cpp              *
*                                                  (draft!) *
*************************************************************/

#define ARRAY_INTERVAL 128


#define COMMENT_BEGIN_STR "#*"
#define COMMENT_END_STR   "*#"


#define TOKENS_RE         ";|:=|=:|\\+|-|\\*|,|==|!=|:|\\[|\\]|\\(|\\)|\\{|\\}|<=|>=|[_0-9A-Za-z]+|[^ \t\r\f\v\n]"
#define KEYWORDS_RE       ";|:=|=:|\\+|-|\\*|,|==|!=|:|\\[|\\]|\\(|\\)|\\{|\\}|NAME|DATA|BODY|END|BREAK|CONTINUE|GET|PUT|IF|ELSE|FOR|TO|DOWNTO|DO|WHILE|REPEAT|UNTIL|GOTO|DIV|MOD|<=|>=|NOT|AND|OR|INTEGER16"
#define IDENTIFIERS_RE    "_[A-Z][A-Z][A-Z][A-Z][A-Z][A-Z][A-Z]"
#define UNSIGNEDVALUES_RE "0|[1-9][0-9]*"


#define USE_REVERSE_ASSIGNMENT
#define USE_COMPARE_WITH_EQUAL


#ifdef USE_REVERSE_ASSIGNMENT
#define IF_USE_REVERSE_ASSIGNMENT(...) __VA_ARGS__
#define IF_NONUSE_REVERSE_ASSIGNMENT(...)
#else
#define IF_USE_REVERSE_ASSIGNMENT(...)
#define IF_NONUSE_REVERSE_ASSIGNMENT(...) __VA_ARGS__
#endif

#ifdef USE_COMPARE_WITH_EQUAL
#define IF_USE_COMPARE_WITH_EQUAL(...) __VA_ARGS__
#define IF_NONUSE_COMPARE_WITH_EQUAL(...)
#else
#define IF_USE_COMPARE_WITH_EQUAL(...)
#define IF_NONUSE_COMPARE_WITH_EQUAL(...) __VA_ARGS__
#endif


#define T_NAME_0 "NAME"
#define T_NAME_1 ""
#define T_NAME_2 ""
#define T_NAME_3 ""
#define T_BODY_0 "BODY"
#define T_BODY_1 ""
#define T_BODY_2 ""
#define T_BODY_3 ""
#define T_DATA_0 "DATA"
#define T_DATA_1 ""
#define T_DATA_2 ""
#define T_DATA_3 ""
#define T_DATA_TYPE_0 "INTEGER16"
#define T_DATA_TYPE_1 ""
#define T_DATA_TYPE_2 ""
#define T_DATA_TYPE_3 ""
//
#define T_BITWISE_NOT_0 "~"
#define T_BITWISE_NOT_1 ""
#define T_BITWISE_NOT_2 ""
#define T_BITWISE_NOT_3 ""
#define T_BITWISE_AND_0 "&"
#define T_BITWISE_AND_1 ""
#define T_BITWISE_AND_2 ""
#define T_BITWISE_AND_3 ""
#define T_BITWISE_OR_0 "|"
#define T_BITWISE_OR_1 ""
#define T_BITWISE_OR_2 ""
#define T_BITWISE_OR_3 ""
#define T_NOT_0 "NOT"
#define T_NOT_1 ""
#define T_NOT_2 ""
#define T_NOT_3 ""
#define T_AND_0 "AND"
#define T_AND_1 ""
#define T_AND_2 ""
#define T_AND_3 ""
#define T_OR_0 "OR"
#define T_OR_1 ""
#define T_OR_2 ""
#define T_OR_3 ""
//
#define T_EQUAL_0 "=="
#define T_EQUAL_1 ""
#define T_EQUAL_2 ""
#define T_EQUAL_3 ""
#define T_NOT_EQUAL_0 "!="
#define T_NOT_EQUAL_1 ""
#define T_NOT_EQUAL_2 ""
#define T_NOT_EQUAL_3 ""
#define T_LESS_0 "<"
#define T_LESS_1 ""
#define T_LESS_2 ""
#define T_LESS_3 ""
#define T_GREATER_0 ">"
#define T_GREATER_1 ""
#define T_GREATER_2 ""
#define T_GREATER_3 ""
#define T_LESS_OR_EQUAL_0 "<="
#define T_LESS_OR_EQUAL_1 ""
#define T_LESS_OR_EQUAL_2 ""
#define T_LESS_OR_EQUAL_3 ""
#define T_GREATER_OR_EQUAL_0 ">="
#define T_GREATER_OR_EQUAL_1 ""
#define T_GREATER_OR_EQUAL_2 ""
#define T_GREATER_OR_EQUAL_3 ""
//
#define T_ADD_0 "+"
#define T_ADD_1 ""
#define T_ADD_2 ""
#define T_ADD_3 ""
#define T_SUB_0 "-"
#define T_SUB_1 ""
#define T_SUB_2 ""
#define T_SUB_3 ""
#define T_MUL_0 "*"
#define T_MUL_1 ""
#define T_MUL_2 ""
#define T_MUL_3 ""
#define T_DIV_0 "DIV"
#define T_DIV_1 ""
#define T_DIV_2 ""
#define T_DIV_3 ""
#define T_MOD_0 "MOD"
#define T_MOD_1 ""
#define T_MOD_2 ""
#define T_MOD_3 ""
//
#define T_COMA_0 ","
#define T_COMA_1 ""
#define T_COMA_2 ""
#define T_COMA_3 ""
#define T_COLON_0 ":"
#define T_COLON_1 ""
#define T_COLON_2 ""
#define T_COLON_3 ""
#define T_GOTO_0 "GOTO"
#define T_GOTO_1 ""
#define T_GOTO_2 ""
#define T_GOTO_3 ""
//
#define T_IF_0 "IF"
#define T_IF_1 ""
#define T_IF_2 ""
#define T_IF_3 ""
#define T_ELSE_IF_0 "ELSE"
#define T_ELSE_IF_1 "IF"
#define T_ELSE_IF_2 ""
#define T_ELSE_IF_3 ""
#define T_THEN_BLOCK_0 "{"
#define T_THEN_BLOCK_1 ""
#define T_THEN_BLOCK_2 ""
#define T_THEN_BLOCK_3 ""
#define T_ELSE_BLOCK_0 "ELSE"
#define T_ELSE_BLOCK_1 "{"
#define T_ELSE_BLOCK_2 ""
#define T_ELSE_BLOCK_3 ""
//
#define T_FOR_0 "FOR"
#define T_FOR_1 ""
#define T_FOR_2 ""
#define T_FOR_3 ""
#define T_TO_0 "TO"
#define T_TO_1 ""
#define T_TO_2 ""
#define T_TO_3 ""
#define T_DOWNTO_0 "DOWNTO"
#define T_DOWNTO_1 ""
#define T_DOWNTO_2 ""
#define T_DOWNTO_3 ""
#define T_DO_0 "DO"
#define T_DO_1 ""
#define T_DO_2 ""
#define T_DO_3 ""
//
#define T_WHILE_0 "WHILE"
#define T_WHILE_1 ""
#define T_WHILE_2 ""
#define T_WHILE_3 ""
#define T_CONTINUE_WHILE_0 "CONTINUE"
#define T_CONTINUE_WHILE_1 ""
#define T_CONTINUE_WHILE_2 ""
#define T_CONTINUE_WHILE_3 ""
#define T_EXIT_WHILE_0 "BREAK"
#define T_EXIT_WHILE_1 "" 
#define T_EXIT_WHILE_2 "" 
#define T_EXIT_WHILE_3 ""
//
#define T_REPEAT_0 "REPEAT"
#define T_REPEAT_1 ""
#define T_REPEAT_2 ""
#define T_REPEAT_3 ""
#define T_UNTIL_0 "UNTIL"
#define T_UNTIL_1 ""
#define T_UNTIL_2 ""
#define T_UNTIL_3 ""
//
#define T_INPUT_0 "GET"
#define T_INPUT_1 ""
#define T_INPUT_2 ""
#define T_INPUT_3 ""
#define T_OUTPUT_0 "PUT"
#define T_OUTPUT_1 ""
#define T_OUTPUT_2 ""
#define T_OUTPUT_3 ""
//
#define T_BEGIN_GROUPEXPRESSION_0 "("
#define T_BEGIN_GROUPEXPRESSION_1 ""
#define T_BEGIN_GROUPEXPRESSION_2 ""
#define T_BEGIN_GROUPEXPRESSION_3 ""
#define T_END_GROUPEXPRESSION_0 ")"
#define T_END_GROUPEXPRESSION_1 ""
#define T_END_GROUPEXPRESSION_2 ""
#define T_END_GROUPEXPRESSION_3 ""
//
#define T_LEFT_SQUAREBRACKETS_0 "["
#define T_LEFT_SQUAREBRACKETS_1 ""
#define T_LEFT_SQUAREBRACKETS_2 ""
#define T_LEFT_SQUAREBRACKETS_3 ""
#define T_RIGHT_SQUAREBRACKETS_0 "]"
#define T_RIGHT_SQUAREBRACKETS_1 ""
#define T_RIGHT_SQUAREBRACKETS_2 ""
#define T_RIGHT_SQUAREBRACKETS_3 ""
//
#define T_RLBIND_0 ":="
#define T_RLBIND_1 ""
#define T_RLBIND_2 ""
#define T_RLBIND_3 ""
#define T_LRBIND_0 "=:"
#define T_LRBIND_1 ""
#define T_LRBIND_2 ""
#define T_LRBIND_3 ""
//
#define T_BEGIN_0 "BEGIN"
#define T_BEGIN_1 ""
#define T_BEGIN_2 ""
#define T_BEGIN_3 ""
#define T_END_0 "END"
#define T_END_1 ""
#define T_END_2 ""
#define T_END_3 ""
//
#define T_BEGIN_BLOCK_0 "{"
#define T_BEGIN_BLOCK_1 ""
#define T_BEGIN_BLOCK_2 ""
#define T_BEGIN_BLOCK_3 ""
#define T_END_BLOCK_0 "}"
#define T_END_BLOCK_1 ""
#define T_END_BLOCK_2 ""
#define T_END_BLOCK_3 ""
//
#define T_SEMICOLON_0 ";"
#define T_SEMICOLON_1 ""
#define T_SEMICOLON_2 ""
#define T_SEMICOLON_3 ""
//
#define T_NULL_STATEMENT_0 "NULL"
#define T_NULL_STATEMENT_1 "STATEMENT"
#define T_NULL_STATEMENT_2 ""
#define T_NULL_STATEMENT_3 ""


#define LA_IS  2
#define LA_NOT 4 


#define GRAMMAR_LL2__2025 {\
{ LA_IS, {"ident_terminal"}, { "labeled_point",{\
    { LA_IS, {""}, 2, {"ident", T_COLON_0}}\
}}},\
{ LA_IS, {T_GOTO_0}, { "goto_label",{\
    { LA_IS, {""}, 2, {T_GOTO_0, "ident"}}\
}}},\
{ LA_IS, {"ident_terminal"}, { "program_name",{\
    { LA_IS, {""}, 1, {"ident"}}\
}}},\
{ LA_IS, {T_DATA_TYPE_0}, { "value_type",{\
    { LA_IS, {""}, 1, {T_DATA_TYPE_0}}\
}}},\
{ LA_IS, {"["}, { "array_specify",{\
    { LA_IS, {""}, 3, {"[", "unsigned_value", "]"}}\
}}},\
{ LA_IS, {"ident_terminal"}, { "declaration_element",{\
    { LA_IS, {""}, 2, {"ident", "array_specify_optional"}}\
}}},\
{ LA_IS, {"["}, { "array_specify_optional",{\
    { LA_IS, {""}, 1, {"array_specify"}}\
}}},\
{ LA_NOT, {"["}, { "array_specify_optional",{\
    { LA_IS, {""}, 0, {""}}\
}}},\
{ LA_IS, {T_COMA_0}, { "other_declaration_ident",{\
    { LA_IS, {""}, 2, {T_COMA_0, "declaration_element"}}\
}}},\
{ LA_IS, {T_DATA_TYPE_0}, { "declaration",{\
    { LA_IS, {""}, 3, {"value_type", "declaration_element", "other_declaration_ident__iteration"}}\
}}},\
{ LA_IS, { T_COMA_0 }, { "other_declaration_ident__iteration",{\
    { LA_IS, {""}, 2, { "other_declaration_ident", "other_declaration_ident__iteration" }}\
}}},\
{ LA_NOT, { T_COMA_0 }, { "other_declaration_ident__iteration",{\
    { LA_IS, {""}, 0, { "" }}\
}}},\
{ LA_IS, { "[" }, { "index_action",{\
    { LA_IS, {""}, 3, { "[", "expression", "]" }}\
}}},\
{ LA_IS, { T_NOT_0 }, { "unary_operator",{\
    { LA_IS, {""}, 1, { T_NOT_0 }}\
}}},\
{ LA_IS, { T_NOT_0 }, { "unary_operation",{\
    { LA_IS, {""}, 2, { "unary_operator", "expression" }}\
}}},\
{ LA_IS, { T_AND_0 }, { "binary_operator",{\
    { LA_IS, {""}, 1, { T_AND_0 }}\
}}},\
{ LA_IS, { T_OR_0 }, { "binary_operator",{\
    { LA_IS, {""}, 1, { T_OR_0 }}\
}}},\
{ LA_IS, { T_EQUAL_0 }, { "binary_operator",{\
    { LA_IS, {""}, 1, { T_EQUAL_0 }}\
}}},\
{ LA_IS, { T_NOT_EQUAL_0 }, { "binary_operator",{\
    { LA_IS, {""}, 1, { T_NOT_EQUAL_0 }}\
}}},\
IF_NONUSE_COMPARE_WITH_EQUAL(\
{ LA_IS, { T_LESS_0 }, { "binary_operator",{\
    { LA_IS, {""}, 1, { T_LESS_0 }}\
}}},\
{ LA_IS, { T_GREATER_0 }, { "binary_operator",{\
    { LA_IS, {""}, 1, { T_GREATER_0 }}\
}}},\
)\
IF_USE_COMPARE_WITH_EQUAL(\
{ LA_IS, { T_LESS_OR_EQUAL_0 }, { "binary_operator",{\
    { LA_IS, {""}, 1, { T_LESS_OR_EQUAL_0 }}\
}}},\
{ LA_IS, { T_GREATER_OR_EQUAL_0 }, { "binary_operator",{\
    { LA_IS, {""}, 1, { T_GREATER_OR_EQUAL_0 }}\
}}},\
)\
{ LA_IS, { T_ADD_0 }, { "binary_operator",{\
    { LA_IS, {""}, 1, { T_ADD_0 }}\
}}},\
{ LA_IS, { T_SUB_0 }, { "binary_operator",{\
    { LA_IS, {""}, 1, { T_SUB_0 }}\
}}},\
{ LA_IS, { T_MUL_0 }, { "binary_operator",{\
    { LA_IS, {""}, 1, { T_MUL_0 }}\
}}},\
{ LA_IS, { T_DIV_0 }, { "binary_operator",{\
    { LA_IS, {""}, 1, { T_DIV_0 }}\
}}},\
{ LA_IS, { T_MOD_0 }, { "binary_operator",{\
    { LA_IS, {""}, 1, { T_MOD_0 }}\
}}},\
IF_NONUSE_COMPARE_WITH_EQUAL(\
{ LA_IS, { T_AND_0, T_OR_0, T_EQUAL_0, T_NOT_EQUAL_0, T_LESS_0, T_GREATER_0, T_ADD_0, T_SUB_0, T_MUL_0, T_DIV_0, T_MOD_0 }, { "binary_action",{\
    { LA_IS, {""}, 2, { "binary_operator", "expression" }}\
}}},\
)\
IF_USE_COMPARE_WITH_EQUAL(\
{ LA_IS, { T_AND_0, T_OR_0, T_EQUAL_0, T_NOT_EQUAL_0, T_LESS_OR_EQUAL_0, T_GREATER_OR_EQUAL_0, T_ADD_0, T_SUB_0, T_MUL_0, T_DIV_0, T_MOD_0 }, { "binary_action",{\
    { LA_IS, {""}, 2, { "binary_operator", "expression" }}\
}}},\
)\
{LA_IS, { "(" }, { "left_expression",{\
    {LA_IS, { "" }, 1, { "group_expression" }}\
}}},\
{LA_IS, { T_NOT_0 }, { "left_expression",{\
    {LA_IS, { "" }, 1, { "unary_operation" }}\
}}},\
{LA_IS, { T_ADD_0, T_SUB_0 }, { "left_expression",{\
    {LA_IS,  { "unsigned_value_terminal"}, 1, { "value" }},\
    {LA_NOT, { "unsigned_value_terminal" }, 1, { "unary_operation" }}\
}}},\
{LA_IS, { "ident_terminal" }, { "left_expression",{\
    {LA_IS, {""}, 2, { "ident", "index_action_optional" }}\
}}},\
{LA_IS, { "unsigned_value_terminal" }, { "left_expression",{\
    {LA_IS, {""}, 1, { "value" }}\
}}},\
{LA_IS, { "[" }, { "index_action_optional",{\
    {LA_IS, {""}, 1, { "index_action" }}\
}}},\
{LA_NOT, { "[" }, { "index_action_optional",{\
    {LA_IS, {""}, 0, { "" }}\
}}},\
{LA_IS, { "(", T_NOT_0, T_ADD_0, T_SUB_0, "ident_terminal", "unsigned_value_terminal" }, { "expression",{\
    {LA_IS, {""}, 2, { "left_expression", "binary_action__iteration" }}\
}}},\
IF_NONUSE_COMPARE_WITH_EQUAL(\
{LA_IS, { T_AND_0, T_OR_0, T_EQUAL_0, T_NOT_EQUAL_0, T_LESS_0, T_GREATER_0, T_ADD_0, T_SUB_0, T_MUL_0, T_DIV_0, T_MOD_0 }, { "binary_action__iteration",{\
    {LA_IS, {""}, 2, { "binary_action", "binary_action__iteration" }}\
}}},\
{LA_NOT, { T_AND_0, T_OR_0, T_EQUAL_0, T_NOT_EQUAL_0, T_LESS_0, T_GREATER_0, T_ADD_0, T_SUB_0, T_MUL_0, T_DIV_0, T_MOD_0 }, { "binary_action__iteration",{\
    {LA_IS, {""}, 0, { "" }}\
}}},\
)\
IF_USE_COMPARE_WITH_EQUAL(\
{LA_IS, { T_AND_0, T_OR_0, T_EQUAL_0, T_NOT_EQUAL_0, T_LESS_OR_EQUAL_0, T_GREATER_OR_EQUAL_0, T_ADD_0, T_SUB_0, T_MUL_0, T_DIV_0, T_MOD_0 }, { "binary_action__iteration",{\
    {LA_IS, {""}, 2, { "binary_action", "binary_action__iteration" }}\
}}},\
{LA_NOT, { T_AND_0, T_OR_0, T_EQUAL_0, T_NOT_EQUAL_0, T_LESS_OR_EQUAL_0, T_GREATER_OR_EQUAL_0, T_ADD_0, T_SUB_0, T_MUL_0, T_DIV_0, T_MOD_0 }, { "binary_action__iteration",{\
    {LA_IS, {""}, 0, { "" }}\
}}},\
)\
{LA_IS, { "(" }, { "group_expression",{\
    {LA_IS, {""}, 3, { "(", "expression", ")" }}\
}}},\
IF_NONUSE_REVERSE_ASSIGNMENT(\
{LA_IS, { "ident_terminal" }, { "bind_right_to_left",{\
    {LA_IS, {""}, 4, { "ident", "index_action_optional", T_RLBIND_0, "expression" }}\
}}},\
)\
IF_USE_REVERSE_ASSIGNMENT(\
{LA_IS, { "(", T_NOT_0, T_ADD_0, T_SUB_0, "ident_terminal", "unsigned_value_terminal" }, { "bind_left_to_right",{\
    {LA_IS, {""}, 4, { "expression", T_LRBIND_0, "ident", "index_action_optional" }}\
}}},\
)\
{LA_IS, { "(", T_NOT_0, T_ADD_0, T_SUB_0, "ident_terminal", "unsigned_value_terminal" }, { "if_expression",{\
    {LA_IS, {""}, 1, { "expression" }}\
}}},\
{LA_IS, { T_BEGIN_BLOCK_0 }, { "body_for_true",{\
    {LA_IS, {""}, 1, { "block_statements_in_while_and_if_body" }}\
}}},\
{LA_IS, { T_ELSE_IF_0 }, { "false_cond_block_without_else",{\
    {LA_IS, {""}, 4, { T_ELSE_IF_0, T_ELSE_IF_1, "if_expression", "body_for_true" }}\
}}},\
{LA_IS, { T_ELSE_BLOCK_0 }, { "body_for_false",{\
    {LA_IS, {""}, 2, { T_ELSE_BLOCK_0, "block_statements_in_while_and_if_body" }}\
}}},\
{LA_IS, { T_IF_0 }, { "cond_block",{\
    {LA_IS, {""}, 5, { T_IF_0, "if_expression", "body_for_true", "false_cond_block_without_else__iteration", "body_for_false_optional" }}\
}}},\
{LA_IS, { T_ELSE_IF_0 }, { "false_cond_block_without_else__iteration",{\
    {LA_IS, {T_ELSE_IF_1}, 2, { "false_cond_block_without_else", "false_cond_block_without_else__iteration" }},\
    {LA_NOT, { T_ELSE_IF_1 }, 0, { "" }}\
}}},\
{LA_NOT, { T_ELSE_IF_0 }, { "false_cond_block_without_else__iteration",{\
    {LA_IS, {""}, 0, { "" }}\
}}},\
{LA_IS, { T_ELSE_BLOCK_0 }, { "body_for_false_optional",{\
    {LA_IS, {""}, 1, { "body_for_false" }}\
}}},\
{LA_NOT, { T_ELSE_BLOCK_0 }, { "body_for_false_optional",{\
    {LA_IS, {""}, 0, { "" }}\
}}},\
{LA_IS, { "(", T_NOT_0, T_ADD_0, T_SUB_0, "ident_terminal", "unsigned_value_terminal" }, { "cycle_begin_expression",{\
    {LA_IS, {""}, 1, { "expression" }}\
}}},\
{LA_IS, { "(", T_NOT_0, T_ADD_0, T_SUB_0, "ident_terminal", "unsigned_value_terminal" }, { "cycle_end_expression",{\
    {LA_IS, {""}, 1, { "expression" }}\
}}},\
{LA_IS, { "ident_terminal" }, { "cycle_counter",{\
    {LA_IS, {""}, 1, { "ident" }}\
}}},\
IF_NONUSE_REVERSE_ASSIGNMENT(\
{LA_IS, { "ident_terminal" }, { "cycle_counter_rl_init",{\
    {LA_IS, {""}, 3, { "cycle_counter", T_RLBIND_0, "cycle_begin_expression" }}\
}}},\
)\
IF_USE_REVERSE_ASSIGNMENT(\
{LA_IS, { "(", T_NOT_0, T_ADD_0, T_SUB_0, "ident_terminal", "unsigned_value_terminal" }, { "cycle_counter_lr_init",{\
    {LA_IS, {""}, 3, { "cycle_begin_expression", T_LRBIND_0, "cycle_counter" }}\
}}},\
)\
{LA_IS, { "ident_terminal" }, { "cycle_counter_init",{\
    IF_NONUSE_REVERSE_ASSIGNMENT({LA_IS, { T_RLBIND_0 }, 1, { "cycle_counter_rl_init" }})\
    IF_USE_REVERSE_ASSIGNMENT({LA_NOT, { T_RLBIND_0 }, 1, { "cycle_counter_lr_init" }})\
}}},\
IF_USE_REVERSE_ASSIGNMENT(\
{LA_IS, { "(", T_NOT_0, T_ADD_0, T_SUB_0, "unsigned_value_terminal" }, { "cycle_counter_init",{\
    {LA_IS, {""}, 1, { "cycle_counter_lr_init" }}\
}}},\
)\
{LA_IS, { "(", T_NOT_0, T_ADD_0, T_SUB_0, "ident_terminal", "unsigned_value_terminal" }, { "cycle_counter_last_value",{\
    {LA_IS, {""}, 1, { "cycle_end_expression" }}\
}}},\
{LA_IS, { T_DO_0 }, { "cycle_body",{\
    {LA_IS, {""}, 2, { T_DO_0, "statements__or__block_statements" }}\
}}},\
{LA_IS, { T_TO_0 }, { "forto_direction",{\
    {LA_IS, {""}, 1, { T_TO_0 }}\
}}},\
{LA_IS, { T_DOWNTO_0 }, { "forto_direction",{\
    {LA_IS, {""}, 1, { T_DOWNTO_0 }}\
}}},\
{LA_IS, { T_FOR_0 }, { "forto_cycle",{\
    {LA_IS, {""}, 5, { T_FOR_0, "cycle_counter_init", "forto_direction", "cycle_counter_last_value", "cycle_body" }}\
}}},\
{LA_IS, { "ident_terminal", "(", T_NOT_0, "unsigned_value_terminal", T_ADD_0, T_SUB_0, T_IF_0, T_FOR_0, T_WHILE_0, T_REPEAT_0, T_GOTO_0, T_INPUT_0, T_OUTPUT_0, T_SEMICOLON_0 }, { "statement_in_while_and_if_body",{\
    {LA_IS, {""}, 1, { "statement" }}\
}}},\
{LA_IS, { T_CONTINUE_WHILE_0 }, { "statement_in_while_and_if_body",{\
    {LA_IS, {""}, 1, { T_CONTINUE_WHILE_0 }}\
}}},\
{LA_IS, { T_EXIT_WHILE_0 }, { "statement_in_while_and_if_body",{\
    {LA_IS, {""}, 1, { T_EXIT_WHILE_0 }}\
}}},\
{LA_IS, { T_BEGIN_BLOCK_0 }, { "block_statements_in_while_and_if_body",{\
    {LA_IS, {""}, 3, { T_BEGIN_BLOCK_0, "statement_in_while_and_if_body__iteration", T_END_BLOCK_0 }}\
}}},\
{LA_IS, { "ident_terminal", "(", T_NOT_0, "unsigned_value_terminal", T_ADD_0, T_SUB_0, T_IF_0, T_FOR_0, T_WHILE_0, T_REPEAT_0, T_GOTO_0, T_INPUT_0, T_OUTPUT_0, T_SEMICOLON_0, T_CONTINUE_WHILE_0, T_EXIT_WHILE_0 }, { "statement_in_while_and_if_body__iteration",{\
    {LA_IS, {""}, 2, { "statement_in_while_and_if_body", "statement_in_while_and_if_body__iteration" }}\
}}},\
{LA_NOT, { "ident_terminal", "(", T_NOT_0, "unsigned_value_terminal", T_ADD_0, T_SUB_0, T_IF_0, T_FOR_0, T_WHILE_0, T_REPEAT_0, T_GOTO_0, T_INPUT_0, T_OUTPUT_0, T_SEMICOLON_0, T_CONTINUE_WHILE_0, T_EXIT_WHILE_0 }, { "statement_in_while_and_if_body__iteration",{\
    {LA_IS, {""}, 0, { "" }}\
}}},\
{LA_IS, { "(", T_NOT_0, T_ADD_0, T_SUB_0, "ident_terminal", "unsigned_value_terminal" }, { "while_cycle_head_expression",{\
    {LA_IS, {""}, 1, { "expression" }}\
}}},\
{LA_IS, { T_WHILE_0 }, { "while_cycle",{\
    {LA_IS, {""}, 3, { T_WHILE_0, "while_cycle_head_expression", "block_statements_in_while_and_if_body" }}\
}}},\
{LA_IS, { "(", T_NOT_0, T_ADD_0, T_SUB_0, "ident_terminal", "unsigned_value_terminal" }, { "repeat_until_cycle_cond",{\
    {LA_IS, {""}, 1, { "expression" }}\
}}},\
{LA_IS, { T_REPEAT_0 }, { "repeat_until_cycle",{\
    {LA_IS, {""}, 4, { T_REPEAT_0, "statements__or__block_statements", T_UNTIL_0, "repeat_until_cycle_cond" }}\
}}},\
{LA_IS, { "ident_terminal", "(", T_NOT_0, "unsigned_value_terminal", T_ADD_0, T_SUB_0, T_IF_0, T_FOR_0, T_WHILE_0, T_REPEAT_0, T_GOTO_0, T_INPUT_0, T_OUTPUT_0, T_SEMICOLON_0 }, { "statements__or__block_statements",{\
    {LA_IS, {""}, 1, { "statement__iteration" }}\
}}},\
{LA_IS, { T_BEGIN_BLOCK_0 }, { "statements__or__block_statements",{\
    {LA_IS, {""}, 1, { "block_statements" }}\
}}},\
{LA_IS, { T_INPUT_0 }, { "input_rule",{\
    {LA_IS, {""}, 2, { T_INPUT_0, "argument_for_input" }}\
}}},\
{LA_IS, { "ident_terminal" }, { "argument_for_input",{\
    {LA_IS, {""}, 2, { "ident", "index_action_optional" }}\
}}},\
{LA_IS, { "(" }, { "argument_for_input",{\
    {LA_IS, {""}, 4, { "(", "ident", "index_action_optional", ")" }}\
}}},\
{LA_IS, { T_OUTPUT_0 }, { "output_rule", {\
    {LA_IS, { "" }, 2, {T_OUTPUT_0, "expression"} }\
}}},\
{LA_IS, { "ident_terminal" }, { "statement", {\
    IF_NONUSE_REVERSE_ASSIGNMENT({ LA_IS, { T_RLBIND_0, "[" }, 1, {"bind_right_to_left"}},)\
    { LA_IS, { T_COLON_0 }, 1, {"labeled_point"}},\
    IF_USE_REVERSE_ASSIGNMENT({ LA_NOT, { T_COLON_0 }, 1, {"bind_left_to_right"}})\
}}},\
IF_USE_REVERSE_ASSIGNMENT(\
{LA_IS, { "(", T_NOT_0, "unsigned_value_terminal", T_ADD_0, T_SUB_0 }, { "statement", {\
    { LA_IS, {""}, 1, {"bind_left_to_right"}}\
}}},\
)\
{LA_IS, { T_IF_0 }, { "statement",{\
    {LA_IS, {""}, 1, {"cond_block"}}\
}}},\
{LA_IS, { T_FOR_0 }, { "statement",{\
    {LA_IS, {""}, 1, {"forto_cycle"}}\
}}},\
{LA_IS, { T_WHILE_0 }, { "statement",{\
    {LA_IS, {""}, 1, {"while_cycle"}}\
}}},\
{LA_IS, { T_REPEAT_0 }, { "statement",{\
    {LA_IS, {""}, 1, {"repeat_until_cycle"}}\
}}},\
{LA_IS, { T_GOTO_0 }, { "statement",{\
    {LA_IS, {""}, 1, {"goto_label"}}\
}}},\
{LA_IS, { T_INPUT_0 }, { "statement",{\
    {LA_IS, {""}, 1, {"input_rule"}}\
}}},\
{LA_IS, { T_OUTPUT_0 }, { "statement",{\
    {LA_IS, {""}, 1, {"output_rule"}}\
}}},\
{LA_IS, { T_SEMICOLON_0 }, { "statement",{\
    {LA_IS, {""}, 1, {";"}}\
}}},\
{ LA_IS, { T_BEGIN_BLOCK_0 }, { "block_statements",{\
    { LA_IS, {""}, 3, { T_BEGIN_BLOCK_0, "statement__iteration", T_END_BLOCK_0 }}\
}}},\
{ LA_IS, { "ident_terminal", "(", T_NOT_0, "unsigned_value_terminal", T_ADD_0, T_SUB_0, T_IF_0, T_FOR_0, T_WHILE_0, T_REPEAT_0, T_GOTO_0, T_INPUT_0, T_OUTPUT_0, T_SEMICOLON_0 }, { "statement__iteration",{\
    { LA_IS, {""}, 2, { "statement", "statement__iteration" }}\
}}},\
{ LA_NOT, { "ident_terminal", "(", T_NOT_0, "unsigned_value_terminal", T_ADD_0, T_SUB_0, T_IF_0, T_FOR_0, T_WHILE_0, T_REPEAT_0, T_GOTO_0, T_INPUT_0, T_OUTPUT_0, T_SEMICOLON_0 }, { "statement__iteration",{\
    { LA_IS, {""}, 0, { "" }}\
}}},\
{ LA_IS, { T_NAME_0 }, { "program_rule",{\
    { LA_IS, {""}, 9, { T_NAME_0, "program_name", T_SEMICOLON_0, T_BODY_0, T_DATA_0, "declaration_optional", T_SEMICOLON_0, "statement__iteration", T_END_0 }}\
}}},\
{ LA_IS, { T_DATA_TYPE_0 }, { "declaration_optional",{\
    { LA_IS, {""}, 1, { "declaration" }}\
}}},\
{ LA_NOT, { T_DATA_TYPE_0 }, { "declaration_optional",{\
    { LA_IS, {""}, 0, { "" }}\
}}},\
{LA_IS, { "unsigned_value_terminal" }, { "unsigned_value", {\
    {LA_IS, { "" }, 1, { "unsigned_value_terminal" }}\
}}},\
{LA_IS, { "unsigned_value_terminal", T_ADD_0, T_SUB_0 }, { "value", {\
    {LA_IS, { "" }, 2, { "sign_optional", "unsigned_value" }}\
}}},\
{LA_IS, { T_ADD_0, T_SUB_0 }, { "sign_optional", {\
    {LA_IS, { "" }, 1, { "sign" }}\
}}},\
{LA_NOT, { T_ADD_0, T_SUB_0 }, { "sign_optional",{\
    {LA_IS, { "" }, 0, { "" }}\
}}},\
{LA_IS, { "ident_terminal" }, { "ident", {\
    {LA_IS, {""}, 1, {"ident_terminal"} }\
}}},\
{LA_IS, { T_ADD_0 }, { "sign", {\
    {LA_IS, {""}, 1, {T_ADD_0}}\
}}},\
{LA_IS, { T_SUB_0 }, { "sign", {\
    {LA_IS, {""}, 1, {T_SUB_0} }\
}}},\
\
\
\
{ LA_IS, { T_NAME_0 }, { "program____part1",{\
    { LA_IS, {""}, 7, { T_NAME_0, "program_name", T_SEMICOLON_0, T_BODY_0, T_DATA_0, "declaration_optional", T_SEMICOLON_0 }}\
}}},\
\
},\
103,\
"program_rule"
// TODO:
//{ LA_IS, { T_NAME_0 }, { "program____part1",{
//    { LA_IS, {""}, 7, { T_NAME_0, "program_name", T_SEMICOLON_0, T_BODY_0, T_DATA_0, "declaration_optional", T_SEMICOLON_0 }} // !!!
//} }},

//#define DECLENUM(NAME, ...) typedef enum {__VA_ARGS__, size##NAME} NAME;
#define DECLENUM(NAME, ...) enum NAME {__VA_ARGS__, size##NAME};
#define GET_ENUM_SIZE(NAME) size##NAME
#define SET_QUADRUPLE_STR_MACRO_IN_ARRAY(ARRAY, NAME)\
ARRAY[MULTI_TOKEN_##NAME][0] = (char*)T_##NAME##_0;\
ARRAY[MULTI_TOKEN_##NAME][1] = (char*)T_##NAME##_1;\
ARRAY[MULTI_TOKEN_##NAME][2] = (char*)T_##NAME##_2;\
ARRAY[MULTI_TOKEN_##NAME][3] = (char*)T_##NAME##_3;

#define INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(ARRAY, NAME) {(char*)T_##NAME##_0, (char*)T_##NAME##_1, (char*)T_##NAME##_2, (char*)T_##NAME##_3}

DECLENUM(TokenStructName,
	MULTI_TOKEN_BITWISE_NOT,
	MULTI_TOKEN_BITWISE_AND,
	MULTI_TOKEN_BITWISE_OR,
	MULTI_TOKEN_NOT,
	MULTI_TOKEN_AND,
	MULTI_TOKEN_OR,

	MULTI_TOKEN_EQUAL,
	MULTI_TOKEN_NOT_EQUAL,
	MULTI_TOKEN_LESS,
	MULTI_TOKEN_GREATER,
	MULTI_TOKEN_LESS_OR_EQUAL,
	MULTI_TOKEN_GREATER_OR_EQUAL,

	MULTI_TOKEN_ADD,
	MULTI_TOKEN_SUB,
	MULTI_TOKEN_MUL,
	MULTI_TOKEN_DIV,
	MULTI_TOKEN_MOD,

	MULTI_TOKEN_COLON,
	MULTI_TOKEN_GOTO,

	MULTI_TOKEN_IF,
	MULTI_TOKEN_ELSE_IF,
	MULTI_TOKEN_THEN_BLOCK,
	MULTI_TOKEN_ELSE_BLOCK,

	MULTI_TOKEN_FOR,
	MULTI_TOKEN_TO,
	MULTI_TOKEN_DOWNTO,
	MULTI_TOKEN_DO,

	//
	MULTI_TOKEN_WHILE,
	/*while special statement*/MULTI_TOKEN_CONTINUE_WHILE,
	/*while special statement*/MULTI_TOKEN_EXIT_WHILE,
	//

	//
	MULTI_TOKEN_REPEAT,
	MULTI_TOKEN_UNTIL,
	//

	//
	MULTI_TOKEN_INPUT,
	MULTI_TOKEN_OUTPUT,
	//

	//
	MULTI_TOKEN_BEGIN_GROUPEXPRESSION,
	MULTI_TOKEN_END_GROUPEXPRESSION,
	//

	//
	MULTI_TOKEN_LEFT_SQUAREBRACKETS,
	MULTI_TOKEN_RIGHT_SQUAREBRACKETS,
	//

	//
	MULTI_TOKEN_RLBIND,
	MULTI_TOKEN_LRBIND,
	//

	//
	MULTI_TOKEN_BEGIN,
	MULTI_TOKEN_END,
	//

	//
	MULTI_TOKEN_BEGIN_BLOCK,
	MULTI_TOKEN_END_BLOCK,
	//

	MULTI_TOKEN_SEMICOLON,

	MULTI_TOKEN_NULL_STATEMENT
);

#define INIT_TOKEN_STRUCT_NAME() static void intitTokenStruct(){\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, BEGIN_BLOCK)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, END_BLOCK)\
\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, BITWISE_NOT)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, BITWISE_AND)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, BITWISE_OR)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, NOT)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, AND)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, OR)\
\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, EQUAL)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, NOT_EQUAL)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, LESS)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, GREATER)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, LESS_OR_EQUAL)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, GREATER_OR_EQUAL)\
\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, ADD)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, SUB)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, MUL)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, DIV)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, MOD)\
\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, COLON)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, GOTO)\
\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, IF)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, ELSE_IF)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, THEN_BLOCK)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, ELSE_BLOCK)\
\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, FOR)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, TO)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, DOWNTO)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, DO)\
\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, WHILE)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, CONTINUE_WHILE)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, EXIT_WHILE)\
\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, REPEAT)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, UNTIL)\
\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, INPUT)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, OUTPUT)\
\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, BEGIN_GROUPEXPRESSION)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, END_GROUPEXPRESSION)\
\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, LEFT_SQUAREBRACKETS)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, RIGHT_SQUAREBRACKETS)\
\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, RLBIND)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, LRBIND)\
\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, BEGIN)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, END)\
\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, BEGIN_BLOCK)\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, END_BLOCK)\
\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, SEMICOLON)\
\
SET_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, NULL_STATEMENT)\
} char intitTokenStruct_ = (intitTokenStruct(), 0);
#define MAX_TOKEN_STRUCT_ELEMENT_COUNT GET_ENUM_SIZE(TokenStructName)
#define MAX_TOKEN_STRUCT_ELEMENT_PART_COUNT 4

char* tokenStruct[MAX_TOKEN_STRUCT_ELEMENT_COUNT][MAX_TOKEN_STRUCT_ELEMENT_PART_COUNT] = {
    INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, BITWISE_NOT),
    INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, BITWISE_AND),
    INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, BITWISE_OR),
    INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, NOT),
    INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, AND),
    INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, OR),
    //
	INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, EQUAL),
	INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, NOT_EQUAL),
	INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, LESS),
	INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, GREATER),
	INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, LESS_OR_EQUAL),
	INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, GREATER_OR_EQUAL),
    //
	INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, ADD),
	INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, SUB),
	INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, MUL),
	INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, DIV),
	INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, MOD),
    //
	INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, COLON),
	INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, GOTO),
    //
	INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, IF),
	INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, ELSE_IF),
	INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, THEN_BLOCK),
	INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, ELSE_BLOCK),
    //
	INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, FOR),
	INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, TO),
	INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, DOWNTO),
	INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, DO),
    //
	INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, WHILE),
	INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, CONTINUE_WHILE),
	INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, EXIT_WHILE),
    //
	INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, REPEAT),
	INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, UNTIL),
    //
	INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, INPUT),
	INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, OUTPUT),
    //
	INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, BEGIN_GROUPEXPRESSION),
	INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, END_GROUPEXPRESSION),
    //
	INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, LEFT_SQUAREBRACKETS),
	INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, RIGHT_SQUAREBRACKETS),
    //
	INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, RLBIND),
	INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, LRBIND),
    //
	INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, BEGIN),
	INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, END),
    //
	INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, BEGIN_BLOCK),
	INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, END_BLOCK),
    //
	INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, SEMICOLON),
    //
	INIT_QUADRUPLE_STR_MACRO_IN_ARRAY(tokenStruct, NULL_STATEMENT)
};

//INIT_TOKEN_STRUCT_NAME();

#define MAX_RULES 356

#define MAX_TOKEN_SIZE 128
#define MAX_RTOKEN_COUNT 16

#define MAX_RHSCONTEINER_COUNT 3

#define MAX_MARK_COUNT 16

typedef struct {
	char secondMarksType;
	char secondMarks[MAX_MARK_COUNT][MAX_TOKEN_SIZE];
	int rhs_count;
	char rhs[MAX_RTOKEN_COUNT][MAX_TOKEN_SIZE];
} RHSConteiner;

typedef struct {
	char lhs[MAX_TOKEN_SIZE];
	RHSConteiner rhss[MAX_RHSCONTEINER_COUNT];
} Rule;

typedef struct {
	char firstMarksType;
	char firstMarks[MAX_MARK_COUNT][MAX_TOKEN_SIZE];
	Rule rule;
} MarkedRule;

typedef struct {
	MarkedRule multiRules[MAX_RULES];
	int rule_count;
	char start_symbol[MAX_TOKEN_SIZE];
} Grammar;

Grammar grammar = {
	GRAMMAR_LL2__2025
};

bool getIndexAfterFragmentSyntax(char* ruleName, int& lexemIndex, struct LexemInfo* lexemInfoTable, Grammar* grammar, int depth/* not used */);

//int syntaxAnalyze(       LexemInfo* lexemInfoTable, Grammar* grammar, char syntaxlAnalyzeMode, char* astFileName, char* errorMessagesPtrToLastBytePtr, bool viewAST);
//int syntaxAnalyze(struct LexemInfo* lexemInfoTable, Grammar* grammar, char syntaxlAnalyzeMode/* not used */, char* astFileName, char* errorMessagesPtrToLastBytePtr, bool viewAST);

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>
#include <set>

#include "stdlib.h" // for exit() // TODO:...
#include "string.h"

//#define DEFAULT_INPUT_FILE "../base_test_programs_2025/file1.k03"
// #define AST_OUTPUT_FILE "../base_test_programs_2025/ast.txt"
//#define DEFAULT_INPUT_FILE "../other_test_programs_2025/file4.k03"
//#define AST_OUTPUT_FILE "../base_test_programs_2025/ast.txt"
#define DEFAULT_INPUT_FILE "file1.k03"
#define AST_OUTPUT_FILE "ast.txt"

unsigned char errorMessagesPtrToLastBytePtr[8 * 1024 * 1024] = { '\0' };

#define SUCCESS_STATE 0

#define DEBUG_MODE 4096

#define RERUN_MODE

#define VALUE_SIZE 4

#define MAX_TEXT_SIZE 8192
#define MAX_WORD_COUNT (MAX_TEXT_SIZE / 5)
#define MAX_LEXEM_SIZE 1024
#define MAX_VARIABLES_COUNT 256
#define MAX_KEYWORD_COUNT 64

#define KEYWORD_LEXEME_TYPE 1
#define IDENTIFIER_LEXEME_TYPE 2 // #define LABEL_LEXEME_TYPE 8
#define VALUE_LEXEME_TYPE 4
#define UNEXPEXTED_LEXEME_TYPE 127

#ifndef LEXEM_INFO_
#define LEXEM_INFO_
struct NonContainedLexemInfo;
struct LexemInfo {
public:
	char lexemStr[MAX_LEXEM_SIZE];
	unsigned long long int lexemId;
	unsigned long long int tokenType;
	unsigned long long int ifvalue;
	unsigned long long int row;
	unsigned long long int col;
	// TODO: ...

	LexemInfo();
	LexemInfo(const char* lexemStr, unsigned long long int lexemId, unsigned long long int tokenType, unsigned long long int ifvalue, unsigned long long int row, unsigned long long int col);
	LexemInfo(const NonContainedLexemInfo& nonContainedLexemInfo);
};
#endif

#ifndef NON_CONTAINED_LEXEM_INFO_
#define NON_CONTAINED_LEXEM_INFO_
struct LexemInfo;
struct NonContainedLexemInfo {
	//char lexemStr[MAX_LEXEM_SIZE]; 
	char* lexemStr;
	unsigned long long int lexemId;
	unsigned long long int tokenType;
	unsigned long long int ifvalue;
	unsigned long long int row;
	unsigned long long int col;
	// TODO: ...

	NonContainedLexemInfo();
	NonContainedLexemInfo(const LexemInfo& lexemInfo);
};
#endif

void printLexemes(struct LexemInfo* lexemInfoTable, char printBadLexeme/* = 0*/);
void printLexemesToFile(struct LexemInfo* lexemInfoTable, char printBadLexeme, const char* filename);
unsigned int getIdentifierId(char(*identifierIdsTable)[MAX_LEXEM_SIZE], char* str);
unsigned int tryToGetIdentifier(struct LexemInfo* lexemInfoInTable, char(*identifierIdsTable)[MAX_LEXEM_SIZE]);
unsigned int tryToGetUnsignedValue(struct LexemInfo* lexemInfoInTable);
int commentRemover(char* text, const char* openStrSpc/* = "//"*/, const char* closeStrSpc/* = "\n"*/);
void prepareKeyWordIdGetter(char* keywords_, char* keywords_re);
unsigned int getKeyWordId(char* keywords_, char* lexemStr, unsigned int baseId);
char tryToGetKeyWord(struct LexemInfo* lexemInfoInTable);
void setPositions(const char* text, struct LexemInfo* lexemInfoTable);
struct LexemInfo lexicalAnalyze(struct LexemInfo* lexemInfoInPtr, char(*identifierIdsTable)[MAX_LEXEM_SIZE]);
struct LexemInfo tokenize(char* text, struct LexemInfo** lastLexemInfoInTable, char(*identifierIdsTable)[MAX_LEXEM_SIZE], struct LexemInfo(*lexicalAnalyzeFunctionPtr)(struct LexemInfo*, char(*)[MAX_LEXEM_SIZE]));

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include <fstream>
#include <iostream>
//#include <algorithm>
#include <iterator>
#include <regex>

//struct LexemInfo {
//	char lexemStr[MAX_LEXEM_SIZE];
//	unsigned int lexemId;
//	unsigned int tokenType;
//	unsigned int ifvalue;
//	unsigned int row;
//	unsigned int col;
//	// TODO: ...
//};

#define MAX_ACCESSORY_STACK_SIZE_123 128

char tempStrFor_123[MAX_TEXT_SIZE/*?TODO:... MAX_ACCESSORY_STACK_SIZE_123 * 64*/] = {'\0'};
unsigned long long int tempStrForCurrIndex = 0;

struct LexemInfo lexemesInfoTable[MAX_WORD_COUNT];// = { { "", 0, 0, 0 } };
struct LexemInfo* lastLexemInfoInTable = lexemesInfoTable; // first for begin

char identifierIdsTable[MAX_WORD_COUNT][MAX_LEXEM_SIZE] = { "" };

LexemInfo::LexemInfo() {
	lexemStr[0] = '\0';
	lexemId = 0;
	tokenType = 0;
	ifvalue = 0;
	row = ~0;
	col = ~0;
}
LexemInfo::LexemInfo(const char * lexemStr, unsigned long long int lexemId, unsigned long long int tokenType, unsigned long long int ifvalue, unsigned long long int row, unsigned long long int col) {
	strncpy(this->lexemStr, lexemStr, MAX_LEXEM_SIZE);
	this->lexemId = lexemId;
	this->tokenType = tokenType;
	this->ifvalue = ifvalue;
	this->row = row;
	this->col = col;
}
LexemInfo::LexemInfo(const NonContainedLexemInfo& nonContainedLexemInfo){
	strncpy(lexemStr, nonContainedLexemInfo.lexemStr, MAX_LEXEM_SIZE);
	lexemId = nonContainedLexemInfo.lexemId;
	tokenType = nonContainedLexemInfo.tokenType;
	ifvalue = nonContainedLexemInfo.ifvalue;
	row = nonContainedLexemInfo.row;
	col = nonContainedLexemInfo.col;
}

NonContainedLexemInfo::NonContainedLexemInfo() {
	(lexemStr = tempStrFor_123 + tempStrForCurrIndex)[0] = '\0';
	tempStrForCurrIndex += 32;// MAX_LEXEM_SIZE;
	lexemId = 0;
	tokenType = 0;
	ifvalue = 0;
	row = ~0;
	col = ~0;
}
NonContainedLexemInfo::NonContainedLexemInfo(const LexemInfo& lexemInfo) {
	//strncpy(lexemStr, lexemInfo.lexemStr, MAX_LEXEM_SIZE); // 
	lexemStr = (char*)lexemInfo.lexemStr;
	lexemId = lexemInfo.lexemId;
	tokenType = lexemInfo.tokenType;
	ifvalue = lexemInfo.ifvalue;
	row = lexemInfo.row;
	col = lexemInfo.col;
}

void printLexemes(struct LexemInfo* lexemInfoTable, char printBadLexeme) {
	if (printBadLexeme) {
		printf("Bad lexeme:\r\n");
	}
	else {
		printf("Lexemes table:\r\n");
	}
	printf("-------------------------------------------------------------------\r\n");
	//printf("index\t\tlexeme\t\tid\ttype\tifvalue\trow\tcol\r\n");
	printf("index           lexeme          id      type    ifvalue row     col\r\n");
	printf("-------------------------------------------------------------------\r\n");
	for (unsigned long long int index = 0; (!index || !printBadLexeme) && lexemInfoTable[index].lexemStr[0] != '\0'; ++index) {
		printf("%5llu%17s%12llu%10llu%11llu%4lld%8lld\r\n", index, lexemInfoTable[index].lexemStr, lexemInfoTable[index].lexemId, lexemInfoTable[index].tokenType, lexemInfoTable[index].ifvalue, lexemInfoTable[index].row, lexemInfoTable[index].col);
	}
	printf("-------------------------------------------------------------------\r\n\r\n");

	return;
}

void printLexemesToFile(struct LexemInfo* lexemInfoTable, char printBadLexeme, const char* filename) {
	FILE* file = fopen(filename, "wb");
	if (!file) {
		perror("Failed to open file");
		return;
	}

	if (printBadLexeme) {
		fprintf(file, "Bad lexeme:\r\n");
	}
	else {
		fprintf(file, "Lexemes table:\r\n");
	}
	fprintf(file, "-------------------------------------------------------------------\r\n");
	//fprintf(file, "index\t\tlexeme\t\tid\ttype\tifvalue\trow\tcol\r\n");
	fprintf(file, "index           lexeme          id      type    ifvalue row     col\r\n");
	fprintf(file, "-------------------------------------------------------------------\r\n");

	for (unsigned long long int index = 0; (!index || !printBadLexeme) && lexemInfoTable[index].lexemStr[0] != '\0'; ++index) {
		fprintf(file, "%5llu%17s%12llu%10llu%11llu%4lld%8lld\r\n",
			index,
			lexemInfoTable[index].lexemStr,
			lexemInfoTable[index].lexemId,
			lexemInfoTable[index].tokenType,
			lexemInfoTable[index].ifvalue,
			lexemInfoTable[index].row,
			lexemInfoTable[index].col);
	}
	fprintf(file, "-------------------------------------------------------------------\r\n\r\n");

	fclose(file);
}

// get identifier id
unsigned int getIdentifierId(char(*identifierIdsTable)[MAX_LEXEM_SIZE], char* str) {
	unsigned int index = 0;
	for (; identifierIdsTable[index][0] != '\0'; ++index) {
		if (!strncmp(identifierIdsTable[index], str, MAX_LEXEM_SIZE)) {
			return index;
		}
	}
	strncpy(identifierIdsTable[index], str, MAX_LEXEM_SIZE);
	identifierIdsTable[index + 1][0] = '\0'; // not necessarily for zero-init identifierIdsTable
	return index;
}

// try to get identifier
unsigned int tryToGetIdentifier(struct LexemInfo* lexemInfoInTable, char(*identifierIdsTable)[MAX_LEXEM_SIZE]) {
	char * identifiers_re = (char*) IDENTIFIERS_RE;
	//char identifiers_re[] = "_[A-Z][A-Z][A-Z][A-Z][A-Z][A-Z][A-Z]";

	if (std::regex_match(std::string(lexemInfoInTable->lexemStr), std::regex(identifiers_re))) {
		lexemInfoInTable->lexemId = getIdentifierId(identifierIdsTable, lexemInfoInTable->lexemStr);
		lexemInfoInTable->tokenType = IDENTIFIER_LEXEME_TYPE;
		return SUCCESS_STATE;
	}

	return ~SUCCESS_STATE;
}

// try to get value
unsigned int tryToGetUnsignedValue(struct LexemInfo* lexemInfoInTable) {
	char * unsignedvalues_re = (char*) UNSIGNEDVALUES_RE;
	//char unsignedvalues_re[] = "0|[1-9][0-9]*";

	if (std::regex_match(std::string(lexemInfoInTable->lexemStr), std::regex(unsignedvalues_re))) {
		lexemInfoInTable->ifvalue = atoi(lastLexemInfoInTable->lexemStr);
		lexemInfoInTable->lexemId = MAX_VARIABLES_COUNT + MAX_KEYWORD_COUNT;
		lexemInfoInTable->tokenType = VALUE_LEXEME_TYPE;
		return SUCCESS_STATE;
	}

	return ~SUCCESS_STATE;
}

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

void prepareKeyWordIdGetter(char* keywords_, char* keywords_re) {
	if (keywords_ == NULL || keywords_re == NULL) {
		return;
	}

	for (char* keywords_re_ = keywords_re, *keywords__ = keywords_; (*keywords_re_ != '\0') ? 1 : (*keywords__ = '\0', 0); (*keywords_re_ != '\\' || (keywords_re_[1] != '+' && keywords_re_[1] != '*' && keywords_re_[1] != '|')) ? *keywords__++ = *keywords_re_ : 0, ++keywords_re_);
}

unsigned int getKeyWordId(char* keywords_, char* lexemStr, unsigned int baseId) {
	if (keywords_ == NULL || lexemStr == NULL) {
		return ~0;
	}
	char* lexemInKeywords_ = keywords_;
	size_t lexemStrLen = strlen(lexemStr);
	if (!lexemStrLen) {
		return ~0;
	}

	for (; lexemInKeywords_ = strstr(lexemInKeywords_, lexemStr), lexemInKeywords_ != NULL && lexemInKeywords_[lexemStrLen] != '|' && lexemInKeywords_[lexemStrLen] != '\0'; ++lexemInKeywords_);

	return lexemInKeywords_ - keywords_ + baseId;
}

// try to get KeyWord
char tryToGetKeyWord(struct LexemInfo* lexemInfoInTable) {
	char * keywords_re = (char*) KEYWORDS_RE;
	//char keywords_re[] = ";|<<|>>|\\+|-|\\*|,|==|!=|:|\\(|\\)|NAME|DATA|BODY|END|EXIT|CONTINUE|GET|PUT|IF|ELSE|FOR|TO|DOWNTO|DO|WHILE|REPEAT|UNTIL|GOTO|DIV|MOD|<=|>=|NOT|AND|OR|INTEGER16";
	//char keywords_re[] = ";|<<|\\+\\+|--|\\*\\*|==|\\(|\\)|!=|:|name|data|body|end|get|put|for|to|downto|do|while|continue|exit|repeat|until|if|goto|div|mod|le|ge|not|and|or|long|int";
	char keywords_[sizeof(KEYWORDS_RE)] = { '\0' };
	prepareKeyWordIdGetter(keywords_, keywords_re);

	if (std::regex_match(std::string(lexemInfoInTable->lexemStr), std::regex(keywords_re))) {
		lexemInfoInTable->lexemId = getKeyWordId(keywords_, lexemInfoInTable->lexemStr, MAX_VARIABLES_COUNT);
		lexemInfoInTable->tokenType = KEYWORD_LEXEME_TYPE;
		return SUCCESS_STATE;
	}

	return ~SUCCESS_STATE;
}

void setPositions(const char* text, struct LexemInfo* lexemInfoTable) {
	unsigned long long int line_number = 1;
	const char* pos = text, * line_start = text;

	if (lexemInfoTable) while (*pos != '\0' && lexemInfoTable->lexemStr[0] != '\0') {
		const char* line_end = strchr(pos, '\n');
		if (!line_end) {
			line_end = text + strlen(text);
		}

		char line_[4096], * line = line_; //!! TODO: ...
		strncpy(line, pos, line_end - pos);
		line[line_end - pos] = '\0';

		for (char* found_pos; lexemInfoTable->lexemStr[0] != '\0' && (found_pos = strstr(line, lexemInfoTable->lexemStr)); line += strlen(lexemInfoTable->lexemStr), ++lexemInfoTable) {
			lexemInfoTable->row = line_number;
			lexemInfoTable->col = found_pos - line_ + 1ull;
		}
		line_number++;
		pos = line_end;
		if (*pos == '\n') {
			pos++;
		}
	}
}

struct LexemInfo lexicalAnalyze(struct LexemInfo* lexemInfoInPtr, char(*identifierIdsTable)[MAX_LEXEM_SIZE]) {
	struct LexemInfo ifBadLexemeInfo; // = { 0 };

	if (tryToGetKeyWord(lexemInfoInPtr) == SUCCESS_STATE);
	else if (tryToGetIdentifier(lexemInfoInPtr, identifierIdsTable) == SUCCESS_STATE);
	else if (tryToGetUnsignedValue(lexemInfoInPtr) == SUCCESS_STATE);
	else {
		ifBadLexemeInfo.tokenType = UNEXPEXTED_LEXEME_TYPE;
	}

	return ifBadLexemeInfo;
}

struct LexemInfo tokenize(char* text, struct LexemInfo** lastLexemInfoInTable, char(*identifierIdsTable)[MAX_LEXEM_SIZE], struct LexemInfo(*lexicalAnalyzeFunctionPtr)(struct LexemInfo*, char(*)[MAX_LEXEM_SIZE])) {
	char * tokens_re = (char*) TOKENS_RE;
	//char tokens_re[] = ";|<<|>>|\\+|-|\\*|,|==|!=|:|\\(|\\)|<=|>=|[_0-9A-Za-z]+|[^ \t\r\f\v\n]";
	//char tokens_re[] = "<<|\\+\\+|--|\\*\\*|==|\\(|\\)|!=|[_0-9A-Za-z]+|[^ \t\r\f\v\n]";
	std::regex tokens_re_(tokens_re);
	struct LexemInfo ifBadLexemeInfo; // = { 0 };
	std::string stringText(text);

	for (std::sregex_token_iterator end, tokenIterator(stringText.begin(), stringText.end(), tokens_re_); tokenIterator != end; ++tokenIterator, ++ * lastLexemInfoInTable) {
		std::string str = *tokenIterator;
		strncpy((*lastLexemInfoInTable)->lexemStr, str.c_str(), MAX_LEXEM_SIZE);
		if ((ifBadLexemeInfo = (*lexicalAnalyzeFunctionPtr)(*lastLexemInfoInTable, identifierIdsTable)).tokenType == UNEXPEXTED_LEXEME_TYPE) {
			break;
		}
	}

	setPositions(text, lexemesInfoTable);

	if (ifBadLexemeInfo.tokenType == UNEXPEXTED_LEXEME_TYPE) {
		strncpy(ifBadLexemeInfo.lexemStr, (*lastLexemInfoInTable)->lexemStr, MAX_LEXEM_SIZE);
		ifBadLexemeInfo.row = (*lastLexemInfoInTable)->row;
		ifBadLexemeInfo.col = (*lastLexemInfoInTable)->col;
	}

	return ifBadLexemeInfo;
}

// after using this function use free(void *) function to release text buffer
size_t loadSource(char** text, char* fileName) {
	if (!fileName) {
		printf("No input file name\r\n");
		return 0;
	}

	FILE* file = fopen(fileName, "rb");

	if (file == NULL) {
		printf("File not loaded\r\n");
		return 0;
	}

	fseek(file, 0, SEEK_END);
	long fileSize_ = ftell(file);
	if (fileSize_ >= MAX_TEXT_SIZE) {
		printf("the file(%ld bytes) is larger than %d bytes\r\n", fileSize_, MAX_TEXT_SIZE);
		fclose(file);
		exit(2); // TODO: ...
		//return 0;
	}
	size_t fileSize = fileSize_;
	rewind(file);

	if (!text) {
		printf("Load source error\r\n");
		return 0;
	}
	*text = (char*)malloc(sizeof(char) * (fileSize + 1));
	if (*text == NULL) {
		fputs("Memory error", stderr);
		fclose(file);
		exit(2); // TODO: ...
		//return 0;
	}

	size_t result = fread(*text, sizeof(char), fileSize, file);
	if (result != fileSize) {
		fputs("Reading error", stderr);
		fclose(file);
		exit(3); // TODO: ...
		//return 0;
	}
	(*text)[fileSize] = '\0';

	fclose(file);

	return fileSize;
}

void writeBytesToFile(const char* output_file, unsigned char* byteImage, unsigned long long int imageSize);
int syntaxAnalyze(struct LexemInfo* lexemInfoTable, Grammar* grammar, char syntaxlAnalyzeMode/* not used */, char* astFileName, char* errorMessagesPtrToLastBytePtr, bool viewAST);

int main(int argc, char* argv[]) {
	char* text;
	char fileName[128] = DEFAULT_INPUT_FILE;
	char choice[2] = { fileName[0], fileName[1] };
	system("CLS");
	std::cout << "Enter file name(Enter \"" << choice[0] << "\" to use default \"" DEFAULT_INPUT_FILE "\"):";
	std::cin >> fileName;
	if (fileName[0] == choice[0] && fileName[1] == '\0') {
		fileName[1] = choice[1];
	}
	size_t sourceSize = loadSource(&text, fileName);
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
	printf("%s\r\n", text);
	printf("-------------------------------------------------------------------\r\n\r\n");
	int commentRemoverResult = commentRemover(text, "#*", "*#");
	if (commentRemoverResult) {
		printf("Comment remover return %d\r\n", commentRemoverResult);
		printf("Press Enter to exit . . .");
		(void)getchar();
		return 0;
	}
	printf("Source after comment removing:\r\n");
	printf("-------------------------------------------------------------------\r\n");
	printf("%s\r\n", text);
	printf("-------------------------------------------------------------------\r\n\r\n");

	struct LexemInfo ifBadLexemeInfo = tokenize(text, &lastLexemInfoInTable, identifierIdsTable, lexicalAnalyze);

	if (ifBadLexemeInfo.tokenType == UNEXPEXTED_LEXEME_TYPE) {
		UNEXPEXTED_LEXEME_TYPE;
		ifBadLexemeInfo.tokenType;
		printf("Lexical analysis detected unexpected lexeme\r\n");
		printLexemes(&ifBadLexemeInfo, 1);
	}
	else {
		printLexemes(lexemesInfoTable, 0);




		errorMessagesPtrToLastBytePtr[0] = '\0';
		unsigned char* errorMessagesPtrToLastBytePtr_ = errorMessagesPtrToLastBytePtr;
		if (SUCCESS_STATE != syntaxAnalyze(lexemesInfoTable, &grammar, 0, (char*)AST_OUTPUT_FILE, (char*)&errorMessagesPtrToLastBytePtr, true)) {

			return 0;
		}




	}

	free(text);

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

void writeBytesToFile(const char* output_file, unsigned char* byteImage, unsigned long long int imageSize) {
	if (!output_file || !byteImage) {
		perror("Error in write image to file");
		exit(EXIT_FAILURE);
	}

	FILE* outfile = fopen(output_file, "wb");
	if (!outfile) {
		perror("Error opening output file");
		exit(EXIT_FAILURE);
	}

	if (imageSize) {
		fwrite(byteImage, 1, imageSize, outfile);
	}

	fclose(outfile);
	printf("File \"%s\" saved.\n", output_file);
}

using namespace std;


struct ASTNode {
	std::string value;
	bool isTerminal;
	std::vector<ASTNode*> childrens;
	ASTNode* parent;

	ASTNode(const std::string& val, bool isTerminal) : isTerminal(isTerminal), value(val), parent(NULL) {}
	static void redirectLinks(std::vector<ASTNode*>& terminalChildrens) {
		for (ASTNode* node : terminalChildrens) {
			if (node == NULL /*!node->isTerminal*/) continue;
			//node->parent->childrens.push_back(node);
			//ASTNode_* parentNode = node->parent;
			//node->parent = NULL;
			//node = parentNode;
			while (node->parent != NULL) {
				node->parent->childrens.push_back(node);
				ASTNode* parentNode = node->parent;
				node->parent = NULL;
				node = parentNode;
			}
		}
	}
	~ASTNode() { // use redirectLinks
		for (ASTNode* child : childrens) {
			delete child;
		}
	}
};
std::vector<ASTNode*> terminalChildrens;

ASTNode* addASTNodeToParent/*printStepAST*/(ASTNode* parent, char* lexemStr, char isTerminal) {

	if (lexemStr == NULL) {
		printf("Error: no lexem\n");
		exit(0); // TODO:...
	}

	ASTNode* node = new(std::nothrow) ASTNode(lexemStr, false); // std::string(lexemStr)
	if (node == nullptr) { // if (!node)
		printf("Error: no parent\n");
		exit(0); // TODO:...
	}

	node->parent = parent;

	return node;
}

void printAST(struct LexemInfo* lexemInfoTable, const ASTNode* node, int depth = 0) {
	static int lexemInfoTableIndexForPrintAST = 0; // ATTENTION: multithreading is not supported for this!
	if (!node) {
		return;
	}
	if (!depth) {
		lexemInfoTableIndexForPrintAST = 0;
	}

	for (unsigned int depthIndex = 0; depthIndex <= depth; ++depthIndex) {
		std::cout << "    " << "|";
	}

	std::cout << "--";
	if (node->isTerminal) {
		std::cout << "\"" << lexemInfoTable[lexemInfoTableIndexForPrintAST++].lexemStr << "\"";
	}
	else {
		std::cout << node->value;
	}
	std::cout << "\n";

	for (const ASTNode* child : node->childrens) {
		printAST(lexemInfoTable, child, depth + 1);
	}
}

void printASTToFile(struct LexemInfo* lexemInfoTable, const ASTNode* node, std::ofstream& outFile, int depth = 0) {
	static int lexemInfoTableIndexForPrintAST = 0; // ATTENTION: multithreading is not supported for this!
	if (!node) {
		return;
	}
	if (!depth) {
		lexemInfoTableIndexForPrintAST = 0;
	}

	for (unsigned int depthIndex = 0; depthIndex <= depth; ++depthIndex) {
		outFile << "    |";
	}
	outFile << "--";

	if (node->isTerminal) {
		outFile << "\"" << lexemInfoTable[lexemInfoTableIndexForPrintAST++].lexemStr << "\"";
	}
	else {
		outFile << node->value;
	}
	outFile << "\n";

	for (const ASTNode* child : node->childrens) {
		printASTToFile(lexemInfoTable, child, outFile, depth + 1);
	}
}

#define MAX_STRSTACK_SIZE 2048

char strStack[MAX_STRSTACK_SIZE][MAX_TOKEN_SIZE] = { '\0' };
ASTNode* nodeStack[MAX_STRSTACK_SIZE] = { NULL };

int strStackFirstFreeElementIndex = 0; // TODO: use reinit

void resetStack() {
	strStack[0][0] = '\0';
	strStackFirstFreeElementIndex = 0;
}

char isEmptyStack() { // FINIT STATE 0
	if (strStackFirstFreeElementIndex < 1) {
		return 0;
	}

	return 1;
}

void stackPush(char* stackNewElement, ASTNode* node) {
	if (stackNewElement == NULL) {
		printf("Error\n");
		exit(0); // TODO:...
	}

	if (strStackFirstFreeElementIndex < MAX_STRSTACK_SIZE) {
		nodeStack[strStackFirstFreeElementIndex] = node;
		strncpy(strStack[strStackFirstFreeElementIndex++], stackNewElement, MAX_TOKEN_SIZE);
		return;
	}

	printf("Stack error\n");
	exit(0); // TODO:...
}

ASTNode* stackPop() {
	if (strStackFirstFreeElementIndex) {
		return nodeStack[--strStackFirstFreeElementIndex];
	}

	printf("Stack error\n");
	exit(0); // TODO:...

	return NULL;
}

RHSConteiner* getActualRHSConteinerRHS(Grammar* grammar, struct LexemInfo* currTapeLexemInfoElement, struct LexemInfo* nextTapeLexemInfoElement, char* currStackElement) {
	if (grammar == NULL || currTapeLexemInfoElement == NULL || nextTapeLexemInfoElement == NULL || currStackElement == NULL) {
		printf("Error\n");
		exit(0); // TODO:...
	}

	for (MarkedRule* multiRule = grammar->multiRules; multiRule->firstMarksType; ++multiRule) {
		if (strcmp(multiRule->rule.lhs, currStackElement)) {
			continue;
		}

		for (int firstMarksIndex = 0; multiRule->firstMarks[firstMarksIndex][0] != '\0'; ++firstMarksIndex) {
			if (currTapeLexemInfoElement->tokenType == IDENTIFIER_LEXEME_TYPE && !strcmp(multiRule->firstMarks[firstMarksIndex], "ident_terminal")
				|| currTapeLexemInfoElement->tokenType == VALUE_LEXEME_TYPE && !strcmp(multiRule->firstMarks[firstMarksIndex], "unsigned_value_terminal")
				|| !strcmp(currTapeLexemInfoElement->lexemStr, multiRule->firstMarks[firstMarksIndex])) {
				if (multiRule->firstMarksType == LA_NOT) {
					continue;
				}
			}
			else {
				if (multiRule->firstMarksType == LA_IS) {
					continue;
				}
			}

			for (int rhsVariantIndex = 0; multiRule->rule.rhss[rhsVariantIndex].secondMarksType; ++rhsVariantIndex) {
				if (multiRule->rule.rhss[rhsVariantIndex].secondMarks[0][0] == '\0') {
					return multiRule->rule.rhss + rhsVariantIndex;
				}
				for (int secondMarksIndex = 0; multiRule->rule.rhss[rhsVariantIndex].secondMarks[secondMarksIndex][0] != '\0'; ++secondMarksIndex) {
					if (nextTapeLexemInfoElement->tokenType == IDENTIFIER_LEXEME_TYPE && !strcmp(multiRule->rule.rhss[rhsVariantIndex].secondMarks[secondMarksIndex], "ident_terminal")
						|| nextTapeLexemInfoElement->tokenType == VALUE_LEXEME_TYPE && !strcmp(multiRule->rule.rhss[rhsVariantIndex].secondMarks[secondMarksIndex], "unsigned_value_terminal")
						|| !strcmp(nextTapeLexemInfoElement->lexemStr, multiRule->rule.rhss[rhsVariantIndex].secondMarks[secondMarksIndex])) {
						if (multiRule->rule.rhss[rhsVariantIndex].secondMarksType == LA_NOT) {
							continue;
						}
					}
					else {
						if (multiRule->rule.rhss[rhsVariantIndex].secondMarksType == LA_IS) {
							continue;
						}
					}

					return multiRule->rule.rhss + rhsVariantIndex;
				}
			}
		}
	}

	return NULL;
}

void scrollTapeOneStep(struct LexemInfo** currLexemInfoElement, struct LexemInfo** nextLexemInfoElement) {
	++* currLexemInfoElement;
	*nextLexemInfoElement = *currLexemInfoElement + 1;
}

struct LexemInfo* syntaxLL2(Grammar* grammar, char* ruleName, struct LexemInfo* lexemInfoTable, ASTNode** baseASTNode, struct LexemInfo** badLexemInfo) {
	struct LexemInfo* currTapeElement, * nextTapeElement;

	if (grammar == NULL || ruleName == NULL || lexemInfoTable == NULL || baseASTNode == NULL) {
		printf("Error\n");
		exit(0); // TODO:...
	}

	terminalChildrens.resize(0);

	// start state
	currTapeElement = lexemInfoTable;
	nextTapeElement = lexemInfoTable + 1;
#define CURRENT_STACK_TOP_ELEMENT strStack[strStackFirstFreeElementIndex - 1] // ( strStack[strStackFirstFreeElementIndex - 1] )
	resetStack();
	stackPush(ruleName, *baseASTNode = addASTNodeToParent(NULL, ruleName, false));

	while (isEmptyStack()) {
		//II
		if (currTapeElement->tokenType == IDENTIFIER_LEXEME_TYPE && !strcmp(CURRENT_STACK_TOP_ELEMENT, "ident_terminal")
			|| currTapeElement->tokenType == VALUE_LEXEME_TYPE && !strcmp(CURRENT_STACK_TOP_ELEMENT, "unsigned_value_terminal")
			|| !strcmp(currTapeElement->lexemStr, CURRENT_STACK_TOP_ELEMENT)) {
			// printf("Processed: \"%s\"\n", currTapeElement->lexemStr); // out // debug
			scrollTapeOneStep(&currTapeElement, &nextTapeElement);
			ASTNode* node = stackPop();
			if (node) {
				node->isTerminal = true;
			}
			terminalChildrens.push_back(node);
		}

		//I
		else {
			RHSConteiner* rhsConteiner = getActualRHSConteinerRHS(grammar, currTapeElement, nextTapeElement, CURRENT_STACK_TOP_ELEMENT);
			if (rhsConteiner == NULL) {
				//printf("Error: no rule\n");
				//exit(0);
				if (badLexemInfo != NULL) {
					*badLexemInfo = currTapeElement;
				}
				return currTapeElement;
			}

			ASTNode* parent = stackPop();
			for (int rhsElementIndex = rhsConteiner->rhs_count - 1; rhsElementIndex >= 0; --rhsElementIndex) {
				stackPush(rhsConteiner->rhs[rhsElementIndex], addASTNodeToParent(parent, rhsConteiner->rhs[rhsElementIndex], false));
			}
		}
	}

	isEmptyStack(); // TODO: ... finite state

	ASTNode::redirectLinks(terminalChildrens);
	//printAST(lexemInfoTable, *baseASTNode);

	return currTapeElement;
}

//#define MAX_STACK_DEPTH 256
//#define MAX_AST_NODE_COUNT 65536

bool getIndexAfterFragmentSyntax(char* ruleName, int& lexemIndex, struct LexemInfo* lexemInfoTable, Grammar* grammar, int depth/* not used */) {
	struct LexemInfo* unexpectedLexemfailedTerminal = NULL;
	if (ruleName == NULL) {
		printf("Error: no start rule.\r\n");
		exit(0); // TODO:...
	}

	if (lexemInfoTable == NULL || grammar == NULL) {
		printf("Error\r\n");
		exit(0); // TODO:...
	}
	struct ASTNode* baseASTNode;
	struct LexemInfo* lastLexemInfo = syntaxLL2(grammar, ruleName, lexemInfoTable, &baseASTNode, &unexpectedLexemfailedTerminal);
	delete baseASTNode;
	lexemIndex = lastLexemInfo - lexemInfoTable;

	return unexpectedLexemfailedTerminal == NULL;
}

int syntaxAnalyze(struct LexemInfo* lexemInfoTable, Grammar* grammar, char syntaxlAnalyzeMode/* not used */, char* astFileName, char* errorMessagesPtrToLastBytePtr, bool viewAST) {
	struct ASTNode* astRoot = NULL;
	struct LexemInfo* unexpectedLexemfailedTerminal = NULL; // TODO: ...

	struct LexemInfo* lastLexemInfo = syntaxLL2(grammar, grammar->start_symbol, lexemInfoTable, &astRoot, &unexpectedLexemfailedTerminal);

	if (lastLexemInfo->lexemStr[0] == '\0') {
		if (viewAST) {
			printAST(lexemInfoTable, astRoot);
		}
		std::ofstream astOFStream(astFileName, std::ofstream::out);
		printASTToFile(lexemInfoTable, astRoot, astOFStream);
		astOFStream.close();
		return SUCCESS_STATE;
	}
	else {
		unexpectedLexemfailedTerminal = lastLexemInfo; // TODO: ...
		printf("Parse failed.\r\n");
		printf("    (The predicted terminal does not match the expected one.\r\n    Unexpected terminal \"%s\" on line %lld at position %lld.)\r\n", unexpectedLexemfailedTerminal->lexemStr, unexpectedLexemfailedTerminal->row, unexpectedLexemfailedTerminal->col);
		errorMessagesPtrToLastBytePtr += sprintf(errorMessagesPtrToLastBytePtr, "Parse failed.\r\n");
		errorMessagesPtrToLastBytePtr += snprintf(errorMessagesPtrToLastBytePtr, MAX_LEXEM_SIZE + 128 + strlen("    (The predicted terminal does not match the expected one.\r\n    Unexpected terminal \"#\" on line # at position #.)\r\n"), "    (The predicted terminal does not match the expected one.\r\n    Unexpected terminal \"%s\" on line %lld at position %lld.)\r\n", unexpectedLexemfailedTerminal->lexemStr, unexpectedLexemfailedTerminal->row, unexpectedLexemfailedTerminal->col);
		//exit(0);
		return ~SUCCESS_STATE;
	}
}