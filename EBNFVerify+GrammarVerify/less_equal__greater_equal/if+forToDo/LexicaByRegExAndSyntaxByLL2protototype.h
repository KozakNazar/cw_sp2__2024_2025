/*
Перевірки прототипу LL(2)-синтаксичного аналізатора (спеціальна структура) та прототипу лексичного аналізатора (регулярні вирази) за допомогою коду. Лексеми для синтаксичного аналізатора обробляються лексичним аналізатором, тому синтаксичний аналізатор не аналізує їх повторно (як показано в РБНФ).
(помістити у файл "LexicaByRegExAndSyntaxByLL2protototype.h")
УВАГА: при копіюванні зважайте, щоб у кожному рядку після символу «\» не містилось жодних інших символів.
*/




#define COMMENT_BEGIN_STR "#*"
#define COMMENT_END_STR   "*#"
#define TOKENS_RE         ";|:=|=:|\\+|-|\\*|,|==|!=|:|\\[|\\]|\\(|\\)|\\{|\\}|<=|>=|[_0-9A-Za-z]+|[^ \t\r\f\v\n]"
#define KEYWORDS_RE       ";|:=|=:|\\+|-|\\*|,|==|!=|\\[|\\]|\\(|\\)|\\{|\\}|NAME|DATA|BODY|END|GET|PUT|IF|ELSE|FOR|TO|DO|DIV|MOD|<=|>=|NOT|AND|OR|INTEGER16"
#define IDENTIFIERS_RE    "_[A-Z][A-Z][A-Z][A-Z][A-Z][A-Z][A-Z]"
#define UNSIGNEDVALUES_RE "0|[1-9][0-9]*"
#define T_BEGIN_GROUPEXPRESSION_0 "("
#define T_BEGIN_GROUPEXPRESSION_1 ""
#define T_BEGIN_GROUPEXPRESSION_2 ""
#define T_BEGIN_GROUPEXPRESSION_3 ""
#define T_END_GROUPEXPRESSION_0 ")"
#define T_END_GROUPEXPRESSION_1 ""
#define T_END_GROUPEXPRESSION_2 ""
#define T_END_GROUPEXPRESSION_3 ""
#define T_LEFT_SQUAREBRACKETS_0 "["
#define T_LEFT_SQUAREBRACKETS_1 ""
#define T_LEFT_SQUAREBRACKETS_2 ""
#define T_LEFT_SQUAREBRACKETS_3 ""
#define T_RIGHT_SQUAREBRACKETS_0 "]"
#define T_RIGHT_SQUAREBRACKETS_1 ""
#define T_RIGHT_SQUAREBRACKETS_2 ""
#define T_RIGHT_SQUAREBRACKETS_3 ""
#define T_BEGIN_BLOCK_0 "{"
#define T_BEGIN_BLOCK_1 ""
#define T_BEGIN_BLOCK_2 ""
#define T_BEGIN_BLOCK_3 ""
#define T_END_BLOCK_0 "}"
#define T_END_BLOCK_1 ""
#define T_END_BLOCK_2 ""
#define T_END_BLOCK_3 ""
#define T_SEMICOLON_0 ";"
#define T_SEMICOLON_1 ""
#define T_SEMICOLON_2 ""
#define T_SEMICOLON_3 ""
#define T_DATA_TYPE_0 "INTEGER16"
#define T_DATA_TYPE_1 ""
#define T_DATA_TYPE_2 ""
#define T_DATA_TYPE_3 ""
#define T_COMA_0 ","
#define T_COMA_1 ""
#define T_COMA_2 ""
#define T_COMA_3 ""
#define T_BITWISE_NOT_0 "~"
#define T_BITWISE_NOT_1 ""
#define T_BITWISE_NOT_2 ""
#define T_BITWISE_NOT_3 ""
#define T_NOT_0 "NOT"
#define T_NOT_1 ""
#define T_NOT_2 ""
#define T_NOT_3 ""
#define T_BITWISE_AND_0 "&"
#define T_BITWISE_AND_1 ""
#define T_BITWISE_AND_2 ""
#define T_BITWISE_AND_3 ""
#define T_AND_0 "AND"
#define T_AND_1 ""
#define T_AND_2 ""
#define T_AND_3 ""
#define T_BITWISE_OR_0 "|"
#define T_BITWISE_OR_1 ""
#define T_BITWISE_OR_2 ""
#define T_BITWISE_OR_3 ""
#define T_OR_0 "OR"
#define T_OR_1 ""
#define T_OR_2 ""
#define T_OR_3 ""
#define T_EQUAL_0 "=="
#define T_EQUAL_1 ""
#define T_EQUAL_2 ""
#define T_EQUAL_3 ""
#define T_NOT_EQUAL_0 "!="
#define T_NOT_EQUAL_1 ""
#define T_NOT_EQUAL_2 ""
#define T_NOT_EQUAL_3 ""
#define T_LESS_OR_EQUAL_0 "<="
#define T_LESS_OR_EQUAL_1 ""
#define T_LESS_OR_EQUAL_2 ""
#define T_LESS_OR_EQUAL_3 ""
#define T_GREATER_OR_EQUAL_0 ">="
#define T_GREATER_OR_EQUAL_1 ""
#define T_GREATER_OR_EQUAL_2 ""
#define T_GREATER_OR_EQUAL_3 ""
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
#define T_LRASSIGN_0 "=:"
#define T_LRASSIGN_1 ""
#define T_LRASSIGN_2 ""
#define T_LRASSIGN_3 ""
#define T_THEN_BLOCK_0 "{"
#define T_THEN_BLOCK_1 ""
#define T_THEN_BLOCK_2 ""
#define T_THEN_BLOCK_3 ""
#define T_ELSE_BLOCK_0 "ELSE"
#define T_ELSE_BLOCK_1 T_BEGIN_BLOCK_0
#define T_ELSE_BLOCK_2 ""
#define T_ELSE_BLOCK_3 ""
#define T_IF_0 "IF"
#define T_IF_1 ""
#define T_IF_2 ""
#define T_IF_3 ""
#define T_ELSE_IF_0 "ELSE"
#define T_ELSE_IF_1 T_IF_0
#define T_ELSE_IF_2 ""
#define T_ELSE_IF_3 ""
#define T_DO_0 "DO"
#define T_DO_1 ""
#define T_DO_2 ""
#define T_DO_3 ""
#define T_FOR_0 "FOR"
#define T_FOR_1 ""
#define T_FOR_2 ""
#define T_FOR_3 ""
#define T_TO_0 "TO"
#define T_TO_1 ""
#define T_TO_2 ""
#define T_TO_3 ""
#define T_EXIT_0 "EXIT"
#define T_EXIT_1 "" 
#define T_EXIT_2 "" 
#define T_EXIT_3 ""
#define T_INPUT_0 "GET"
#define T_INPUT_1 ""
#define T_INPUT_2 ""
#define T_INPUT_3 ""
#define T_OUTPUT_0 "PUT"
#define T_OUTPUT_1 ""
#define T_OUTPUT_2 ""
#define T_OUTPUT_3 ""
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
#define T_BEGIN_0 "BEGIN"
#define T_BEGIN_1 ""
#define T_BEGIN_2 ""
#define T_BEGIN_3 ""
#define T_END_0 "END"
#define T_END_1 ""
#define T_END_2 ""
#define T_END_3 ""
#define T_NULL_STATEMENT_0 "NULL"
#define T_NULL_STATEMENT_1 "STATEMENT"
#define T_NULL_STATEMENT_2 ""
#define T_NULL_STATEMENT_3 ""
#define GRAMMAR_LL2__2025 {\
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
    { LA_IS, {""}, 2, {"ident", "array_specify__optional"}}\
}}},\
{ LA_IS, {"["}, { "array_specify__optional",{\
    { LA_IS, {""}, 1, {"array_specify"}}\
}}},\
{ LA_NOT, {"["}, { "array_specify__optional",{\
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
{ LA_IS, { T_LESS_OR_EQUAL_0 }, { "binary_operator",{\
    { LA_IS, {""}, 1, { T_LESS_OR_EQUAL_0 }}\
}}},\
{ LA_IS, { T_GREATER_OR_EQUAL_0 }, { "binary_operator",{\
    { LA_IS, {""}, 1, { T_GREATER_OR_EQUAL_0 }}\
}}},\
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
{ LA_IS, { T_AND_0, T_OR_0, T_EQUAL_0, T_NOT_EQUAL_0, T_LESS_OR_EQUAL_0, T_GREATER_OR_EQUAL_0, T_ADD_0, T_SUB_0, T_MUL_0, T_DIV_0, T_MOD_0 }, { "binary_action",{\
    { LA_IS, {""}, 2, { "binary_operator", "expression" }}\
}}},\
{LA_IS, { "(" }, { "left_expression",{\
    {LA_IS, { "" }, 1, { "group_expression" }}\
}}},\
{LA_IS, { T_NOT_0 }, { "left_expression",{\
    {LA_IS, { "" }, 1, { "unary_operation" }}\
}}},\
{LA_IS, { T_IF_0 }, { "left_expression",{\
    {LA_IS, { "" }, 1, { "cond_block" }}\
}}},\
{LA_IS, { "unsigned_value_terminal" }, { "left_expression",{\
    {LA_IS, {""}, 1, { "value" }}\
}}},\
{LA_IS, { T_ADD_0, T_SUB_0 }, { "left_expression",{\
    {LA_IS,  { "unsigned_value_terminal"}, 1, { "value" }},\
    /*{LA_NOT, { "unsigned_value_terminal" }, 1, { "unary_operation" }}*/\
}}},\
{LA_IS, { "ident_terminal" }, { "left_expression",{\
    {LA_IS, {""}, 2, { "ident", "index_action__optional" }}\
}}},\
{LA_IS, { "[" }, { "index_action__optional",{\
    {LA_IS, {""}, 1, { "index_action" }}\
}}},\
{LA_NOT, { "[" }, { "index_action__optional",{\
    {LA_IS, {""}, 0, { "" }}\
}}},\
{LA_IS, { "(", T_NOT_0, T_ADD_0, T_SUB_0, "ident_terminal", "unsigned_value_terminal", T_IF_0 }, { "expression",{\
    {LA_IS, {""}, 2, { "left_expression", "binary_action__iteration" }}\
}}},\
{LA_IS, { T_AND_0, T_OR_0, T_EQUAL_0, T_NOT_EQUAL_0, T_LESS_OR_EQUAL_0, T_GREATER_OR_EQUAL_0, T_ADD_0, T_SUB_0, T_MUL_0, T_DIV_0, T_MOD_0 }, { "binary_action__iteration",{\
    {LA_IS, {""}, 2, { "binary_action", "binary_action__iteration" }}\
}}},\
{LA_NOT, { T_AND_0, T_OR_0, T_EQUAL_0, T_NOT_EQUAL_0, T_LESS_OR_EQUAL_0, T_GREATER_OR_EQUAL_0, T_ADD_0, T_SUB_0, T_MUL_0, T_DIV_0, T_MOD_0 }, { "binary_action__iteration",{\
    {LA_IS, {""}, 0, { "" }}\
}}},\
{LA_IS, { "(" }, { "group_expression",{\
    {LA_IS, {""}, 3, { "(", "expression", ")" }}\
}}},\
{LA_IS, { "(", T_NOT_0, T_ADD_0, T_SUB_0, "ident_terminal", "unsigned_value_terminal", T_IF_0 }, { "expression_or_cond_block__with_optional_assign",{\
    {LA_IS, {""}, 2, { "expression", "assign_to_right__optional" }}\
}}},\
{LA_IS, { T_LRASSIGN_0 }, { "assign_to_right",{\
    {LA_IS, {""}, 3, { T_LRASSIGN_0, "ident", "index_action__optional" }}\
}}},\
{ LA_IS, { T_LRASSIGN_0 }, { "assign_to_right__optional",{\
    { LA_IS, {""}, 1, { "assign_to_right" }}\
}}},\
{ LA_NOT, { T_LRASSIGN_0 }, { "assign_to_right__optional",{\
    { LA_IS, {""}, 0, { "" }}\
}}},\
{LA_IS, { "(", T_NOT_0, T_ADD_0, T_SUB_0, "ident_terminal", "unsigned_value_terminal", T_IF_0 }, { "if_expression",{\
    {LA_IS, {""}, 1, { "expression" }}\
}}},\
{LA_IS, { T_BEGIN_BLOCK_0 }, { "body_for_true",{\
    {LA_IS, {""}, 1, { "block_statements" }}\
}}},\
{LA_IS, { T_ELSE_IF_0 }, { "false_cond_block_without_else",{\
    {LA_IS, {""}, 4, { T_ELSE_IF_0, T_ELSE_IF_1, "if_expression", "body_for_true" }}\
}}},\
{LA_IS, { T_ELSE_BLOCK_0 }, { "body_for_false",{\
    {LA_IS, {""}, 2, { T_ELSE_BLOCK_0, "block_statements" }}\
}}},\
{LA_IS, { T_IF_0 }, { "cond_block",{\
    {LA_IS, {""}, 5, { T_IF_0, "if_expression", "body_for_true", "false_cond_block_without_else__iteration", "body_for_false__optional" }}\
}}},\
{LA_IS, { T_ELSE_IF_0 }, { "false_cond_block_without_else__iteration",{\
    {LA_IS, {T_ELSE_IF_1}, 2, { "false_cond_block_without_else", "false_cond_block_without_else__iteration" }},\
    {LA_NOT, { T_ELSE_IF_1 }, 0, { "" }}\
}}},\
{LA_NOT, { T_ELSE_IF_0 }, { "false_cond_block_without_else__iteration",{\
    {LA_IS, {""}, 0, { "" }}\
}}},\
{LA_IS, { T_ELSE_BLOCK_0 }, { "body_for_false__optional",{\
    {LA_IS, {""}, 1, { "body_for_false" }}\
}}},\
{LA_NOT, { T_ELSE_BLOCK_0 }, { "body_for_false__optional",{\
    {LA_IS, {""}, 0, { "" }}\
}}},\
{LA_IS, { "(", T_NOT_0, T_ADD_0, T_SUB_0, "ident_terminal", "unsigned_value_terminal", T_IF_0 }, { "cycle_begin_expression",{\
    {LA_IS, {""}, 1, { "expression" }}\
}}},\
{LA_IS, { "(", T_NOT_0, T_ADD_0, T_SUB_0, "ident_terminal", "unsigned_value_terminal", T_IF_0 }, { "cycle_end_expression",{\
    {LA_IS, {""}, 1, { "expression" }}\
}}},\
{LA_IS, { "ident_terminal" }, { "cycle_counter",{\
    {LA_IS, {""}, 1, { "ident" }}\
}}},\
{LA_IS, { "(", T_NOT_0, T_ADD_0, T_SUB_0, "ident_terminal", "unsigned_value_terminal", T_IF_0 }, { "cycle_counter_lr_init",{\
    {LA_IS, {""}, 3, { "cycle_begin_expression", T_LRASSIGN_0, "cycle_counter" }}\
}}},\
{LA_IS, { "(", T_NOT_0, T_ADD_0, T_SUB_0, "ident_terminal", "unsigned_value_terminal", T_IF_0 }, { "cycle_counter_init",{\
    {LA_IS, { "" }, 1, { "cycle_counter_lr_init" }}\
}}},\
{LA_IS, { "(", T_NOT_0, T_ADD_0, T_SUB_0, "ident_terminal", "unsigned_value_terminal", T_IF_0 }, { "cycle_counter_last_value",{\
    {LA_IS, {""}, 1, { "cycle_end_expression" }}\
}}},\
{LA_IS, { T_DO_0 }, { "cycle_body",{\
    {LA_IS, {""}, 2, { T_DO_0, "statement__or__block_statements" }}\
}}},\
{LA_IS, { T_FOR_0 }, { "forto_cycle",{\
    {LA_IS, {""}, 5, { T_FOR_0, "cycle_counter_init",  T_TO_0, "cycle_counter_last_value", "cycle_body" }}\
}}},\
{LA_IS, { "ident_terminal", "(", T_NOT_0, "unsigned_value_terminal", T_ADD_0, T_SUB_0, T_IF_0, T_FOR_0, T_INPUT_0, T_OUTPUT_0, T_SEMICOLON_0 }, { "statement__or__block_statements",{\
    {LA_IS, {""}, 1, { "statement" }}\
}}},\
{LA_IS, { T_BEGIN_BLOCK_0 }, { "statement__or__block_statements",{\
    {LA_IS, {""}, 1, { "block_statements" }}\
}}},\
{LA_IS, { T_INPUT_0 }, { "input_rule",{\
    {LA_IS, {""}, 2, { T_INPUT_0, "argument_for_input" }}\
}}},\
{LA_IS, { "ident_terminal" }, { "argument_for_input",{\
    {LA_IS, {""}, 2, { "ident", "index_action__optional" }}\
}}},\
{LA_IS, { "(" }, { "argument_for_input",{\
    {LA_IS, {""}, 4, { "(", "ident", "index_action__optional", ")" }}\
}}},\
{LA_IS, { T_OUTPUT_0 }, { "output_rule", {\
    {LA_IS, { "" }, 2, {T_OUTPUT_0, "expression"} }\
}}},\
{LA_IS, { "(", T_NOT_0, "ident_terminal", "unsigned_value_terminal", T_ADD_0, T_SUB_0, T_IF_0 }, { "statement", {\
    { LA_IS, {""}, 1, {"expression_or_cond_block__with_optional_assign"}}\
}}},\
{LA_IS, { T_FOR_0 }, { "statement",{\
    {LA_IS, {""}, 1, {"forto_cycle"}}\
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
{ LA_IS, { "ident_terminal", "(", T_NOT_0, "unsigned_value_terminal", T_ADD_0, T_SUB_0, T_IF_0, T_FOR_0, T_INPUT_0, T_OUTPUT_0, T_SEMICOLON_0 }, { "statement__iteration",{\
    { LA_IS, {""}, 2, { "statement", "statement__iteration" }}\
}}},\
{ LA_NOT, { "ident_terminal", "(", T_NOT_0, "unsigned_value_terminal", T_ADD_0, T_SUB_0, T_IF_0, T_FOR_0, T_INPUT_0, T_OUTPUT_0, T_SEMICOLON_0 }, { "statement__iteration",{\
    { LA_IS, {""}, 0, { "" }}\
}}},\
{ LA_IS, { T_BEGIN_BLOCK_0 }, { "block_statements",{\
    { LA_IS, {""}, 3, { T_BEGIN_BLOCK_0, "statement__iteration", T_END_BLOCK_0 }}\
}}},\
{LA_IS, { "(", T_NOT_0, T_ADD_0, T_SUB_0, "ident_terminal", "unsigned_value_terminal", T_IF_0 }, { "expression__optional",{\
    {LA_IS, {""}, 1, { "expression" }}\
}}},\
{LA_NOT, { "(", T_NOT_0, T_ADD_0, T_SUB_0, "ident_terminal", "unsigned_value_terminal", T_IF_0 }, { "expression__optional",{\
    {LA_IS, {""}, 0, { "" }}\
}}},\
{ LA_IS, { T_NAME_0 }, { "program_rule",{\
    { LA_IS, {""}, 9, { T_NAME_0, "program_name", T_SEMICOLON_0, T_BODY_0, T_DATA_0, "declaration__optional", T_SEMICOLON_0, "statement__iteration", T_END_0 }}\
}}},\
{ LA_IS, { T_DATA_TYPE_0 }, { "declaration__optional",{\
    { LA_IS, {""}, 1, { "declaration" }}\
}}},\
{ LA_NOT, { T_DATA_TYPE_0 }, { "declaration__optional",{\
    { LA_IS, {""}, 0, { "" }}\
}}},\
{LA_IS, { "unsigned_value_terminal", T_ADD_0, T_SUB_0 }, { "value", {\
    {LA_IS, { "" }, 2, { "sign__optional", "unsigned_value" }}\
}}},\
{LA_IS, { T_ADD_0, T_SUB_0 }, { "sign__optional", {\
    {LA_IS, { "" }, 1, { "sign" }}\
}}},\
{LA_NOT, { T_ADD_0, T_SUB_0 }, { "sign__optional",{\
    {LA_IS, { "" }, 0, { "" }}\
}}},\
{LA_IS, { T_ADD_0 }, { "sign", {\
    {LA_IS, {""}, 1, { "sign_plus" }}\
}}},\
{LA_IS, { T_SUB_0 }, { "sign", {\
    {LA_IS, {""}, 1, { "sign_minus" } }\
}}},\
{LA_IS, { T_ADD_0 }, { "sign_plus", {\
    {LA_IS, {""}, 1, {T_ADD_0}}\
}}},\
{LA_IS, { T_SUB_0 }, { "sign_minus", {\
    {LA_IS, {""}, 1, {T_SUB_0} }\
}}},\
/* unsigned_value_token represents unsigned_value in lexical analyzer */\
{LA_IS, { "unsigned_value_terminal" }, { "unsigned_value", {\
    {LA_IS, { "" }, 1, { "unsigned_value_terminal" }}\
}}},\
\
\
\
/* ident_token represents ident in lexical analyzer */\
{LA_IS, { "ident_terminal" }, { "ident", {\
    {LA_IS, {""}, 1, {"ident_terminal"} }\
}}},\
\
\
\
\
\
\
{ LA_IS, { T_NAME_0 }, { "program____part1",{\
    { LA_IS, {""}, 7, { T_NAME_0, "program_name", T_SEMICOLON_0, T_BODY_0, T_DATA_0, "declaration_optional", T_SEMICOLON_0 }}\
}}},\
\
},\
"program_rule"
