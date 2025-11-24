/*
Перевірка РБНФ №2 за допомогою коду
(помістити у файл "EBNF_N2.h")
*/


#define NONTERMINALS program_name, \
value_type, \
array_specify, \
declaration_element, \
array_specify__optional, \
other_declaration_ident, \
declaration, \
other_declaration_ident__iteration, \
index_action, \
unary_operator, \
unary_operation, \
binary_operator, \
binary_action, \
left_expression, \
group_expression, \
index_action__optional, \
expression, \
binary_action__iteration, \
expression_or_cond_block__with_optional_assign, \
assign_to_right, \
assign_to_right__optional, \
if_expression, \
body_for_true, \
false_cond_block_without_else, \
body_for_false, \
cond_block, \
false_cond_block_without_else__iteration, \
body_for_false__optional, \
cycle_begin_expression, \
cycle_end_expression, \
cycle_counter, \
cycle_counter_lr_init, \
cycle_counter_init, \
cycle_counter_last_value, \
cycle_body, \
forto_cycle, \
statement, \
statement__or__block_statements,\
block_statements, \
input_rule, \
argument_for_input, \
output_rule, \
statement__iteration, \
expression__optional, \
program_rule, \
declaration__optional, \
non_zero_digit, \
digit__iteration, \
digit, \
unsigned_value, \
value, \
sign__optional, \
sign, \
ident, \
letter_in_upper_case, \
letter_in_lower_case, \
sign_plus, \
sign_minus
#define TOKENS \
tokenINTEGER16, \
tokenCOMMA, \
tokenNOT, \
tokenAND, \
tokenOR, \
tokenEQUAL, \
tokenNOTEQUAL, \
tokenLESSOREQUAL, \
tokenGREATEROREQUAL, \
tokenPLUS, \
tokenMINUS, \
tokenMUL, \
tokenDIV, \
tokenMOD, \
tokenGROUPEXPRESSIONBEGIN, \
tokenGROUPEXPRESSIONEND, \
tokenLRASSIGN, \
tokenELSE, \
tokenIF, \
tokenDO, \
tokenFOR, \
tokenTO, \
tokenEXIT, \
tokenGET, \
tokenPUT, \
tokenNAME, \
tokenBODY, \
tokenDATA, \
tokenBEGIN, \
tokenEND, \
tokenBEGINBLOCK, \
tokenENDBLOCK, \
tokenLEFTSQUAREBRACKETS, \
tokenRIGHTSQUAREBRACKETS, \
tokenSEMICOLON, \
digit_0, \
digit_1, \
digit_2, \
digit_3, \
digit_4, \
digit_5, \
digit_6, \
digit_7, \
digit_8, \
digit_9, \
tokenUNDERSCORE, \
A, \
B, \
C, \
D, \
E, \
F, \
G, \
H, \
I, \
J, \
K, \
L, \
M, \
N, \
O, \
P, \
Q, \
R, \
S, \
T, \
U, \
V, \
W, \
X, \
Y, \
Z, \
a, \
b, \
c, \
d, \
e, \
f, \
g, \
h, \
i, \
j, \
k, \
l, \
m, \
n, \
o, \
p, \
q, \
r, \
s, \
t, \
u, \
v, \
w, \
x, \
y, \
z
#define COMMENT_BEGIN_STR "#*"
#define COMMENT_END_STR   "*#"




tokenGROUPEXPRESSIONBEGIN = "(" >> BOUNDARIES;
tokenGROUPEXPRESSIONEND = ")" >> BOUNDARIES;
tokenLEFTSQUAREBRACKETS = "[" >> BOUNDARIES;
tokenRIGHTSQUAREBRACKETS = "]" >> BOUNDARIES;
tokenBEGINBLOCK = "{" >> BOUNDARIES;
tokenENDBLOCK = "}" >> BOUNDARIES;
tokenSEMICOLON = ";" >> BOUNDARIES;
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
tokenLRASSIGN = "=:" >> BOUNDARIES;

tokenELSE = "ELSE" >> STRICT_BOUNDARIES;
tokenIF = "IF" >> STRICT_BOUNDARIES;

tokenDO = "DO" >> STRICT_BOUNDARIES;
tokenFOR = "FOR" >> STRICT_BOUNDARIES;
tokenTO = "TO" >> STRICT_BOUNDARIES;
tokenEXIT = "EXIT" >> STRICT_BOUNDARIES;
tokenGET = "GET" >> STRICT_BOUNDARIES;
tokenPUT = "PUT" >> STRICT_BOUNDARIES;
tokenNAME = "NAME" >> STRICT_BOUNDARIES;
tokenBODY = "BODY" >> STRICT_BOUNDARIES;
tokenDATA = "DATA" >> STRICT_BOUNDARIES;
tokenBEGIN = "BEGIN" >> STRICT_BOUNDARIES;
tokenEND = "END" >> STRICT_BOUNDARIES;


program_name = SAME_RULE(ident);
value_type = SAME_RULE(tokenINTEGER16);
array_specify = "[" >> unsigned_value >> "]";
declaration_element = ident >> array_specify__optional;
array_specify__optional = array_specify | "";
other_declaration_ident = tokenCOMMA >> declaration_element;
declaration = value_type >> declaration_element >> other_declaration_ident__iteration;
other_declaration_ident__iteration = other_declaration_ident >> other_declaration_ident__iteration | "";
index_action = tokenLEFTSQUAREBRACKETS >> expression >> tokenRIGHTSQUAREBRACKETS;
unary_operator = SAME_RULE(tokenNOT);
unary_operation = unary_operator >> expression;
binary_operator = tokenAND | tokenOR | tokenEQUAL | tokenNOTEQUAL | tokenLESSOREQUAL | tokenGREATEROREQUAL | tokenPLUS | tokenMINUS | tokenMUL | tokenDIV | tokenMOD;
binary_action = binary_operator >> expression;
left_expression = group_expression | unary_operation | cond_block | value | ident >> index_action__optional;
index_action__optional = index_action | "";
expression = left_expression >> binary_action__iteration;
binary_action__iteration = binary_action >> binary_action__iteration | "";
group_expression = tokenGROUPEXPRESSIONBEGIN >> expression >> tokenGROUPEXPRESSIONEND;
expression_or_cond_block__with_optional_assign = expression >> assign_to_right__optional;
assign_to_right = tokenLRASSIGN >> ident >> index_action__optional;
assign_to_right__optional = assign_to_right | "";
if_expression = SAME_RULE(expression);
body_for_true = SAME_RULE(block_statements);
false_cond_block_without_else = tokenELSE >> tokenIF >> if_expression >> body_for_true;
body_for_false = tokenELSE >> block_statements;
cond_block = tokenIF >> if_expression >> body_for_true >> false_cond_block_without_else__iteration >> body_for_false__optional;
false_cond_block_without_else__iteration = false_cond_block_without_else >> false_cond_block_without_else__iteration | "";
body_for_false__optional = body_for_false | "";
cycle_begin_expression = SAME_RULE(expression);
cycle_end_expression = SAME_RULE(expression);
cycle_counter = SAME_RULE(ident);
cycle_counter_lr_init = cycle_begin_expression >> tokenLRASSIGN >> cycle_counter;
cycle_counter_init = SAME_RULE(cycle_counter_lr_init);
cycle_counter_last_value = SAME_RULE(cycle_end_expression);
cycle_body = tokenDO >> statement__or__block_statements;
forto_cycle = tokenFOR >> cycle_counter_init >> tokenTO >> cycle_counter_last_value >> cycle_body;
statement__or__block_statements = statement | block_statements;
input_rule = tokenGET >> argument_for_input;
argument_for_input = ident >> index_action__optional | tokenGROUPEXPRESSIONBEGIN >> ident >> index_action__optional >> tokenGROUPEXPRESSIONEND;
output_rule = tokenPUT >> expression;
statement = expression_or_cond_block__with_optional_assign | forto_cycle | input_rule | output_rule | tokenSEMICOLON;
statement__iteration = statement >> statement__iteration | "";
block_statements = tokenBEGINBLOCK >> statement__iteration >> tokenENDBLOCK;
expression__optional = expression | "";
program_rule = BOUNDARIES >> tokenNAME >> program_name >> tokenSEMICOLON >> tokenBODY >> tokenDATA >> declaration__optional >> tokenSEMICOLON >> statement__iteration >> tokenEND;
declaration__optional = declaration | "";
value = sign__optional >> unsigned_value >> BOUNDARIES;
sign__optional = sign | "";
sign = sign_plus | sign_minus;
sign_plus = SAME_RULE(tokenPLUS);
sign_minus = SAME_RULE(tokenMINUS);
unsigned_value = (non_zero_digit >> digit__iteration | digit_0) >> BOUNDARIES;
digit__iteration = digit >> digit__iteration | "";
digit_0 = '0';
digit = digit_0 | non_zero_digit;
digit_1 = '1';
digit_2 = '2';
digit_3 = '3';
digit_4 = '4';
digit_5 = '5';
digit_6 = '6';
digit_7 = '7';
digit_8 = '8';
digit_9 = '9';
non_zero_digit = digit_1 | digit_2 | digit_3 | digit_4 | digit_5 | digit_6 | digit_7 | digit_8 | digit_9;
tokenUNDERSCORE = "_";
ident =
!(
	tokenINTEGER16 |
	tokenCOMMA |
	tokenNOT |
	tokenAND |
	tokenOR |
	tokenEQUAL |
	tokenNOTEQUAL |
	tokenLESSOREQUAL |
	tokenGREATEROREQUAL |
	tokenPLUS |
	tokenMINUS |
	tokenMUL |
	tokenDIV |
	tokenMOD |
	tokenGROUPEXPRESSIONBEGIN |
	tokenGROUPEXPRESSIONEND |
	tokenLRASSIGN |
	tokenELSE |
	tokenIF |
	tokenDO |
	tokenFOR |
	tokenTO |
	tokenEXIT |
	tokenGET |
	tokenPUT |
	tokenNAME |
	tokenBODY |
	tokenDATA |
	tokenBEGIN |
	tokenEND |
	tokenBEGINBLOCK |
	tokenENDBLOCK |
	tokenLEFTSQUAREBRACKETS |
	tokenRIGHTSQUAREBRACKETS |
	tokenSEMICOLON
	) >>
	tokenUNDERSCORE >> letter_in_upper_case >> letter_in_upper_case >> letter_in_upper_case >> letter_in_upper_case >> letter_in_upper_case >> letter_in_upper_case >> letter_in_upper_case >> STRICT_BOUNDARIES;
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
letter_in_lower_case = a | b | c | d | e | f | g | h | i | j | k | l | m | n | o | p | q | r | s | t | u | v | w | x | y | z;
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
letter_in_upper_case = A | B | C | D | E | F | G | H | I | J | K | L | M | N | O | P | Q | R | S | T | U | V | W | X | Y | Z;
STRICT_BOUNDARIES = (BOUNDARY >> *(BOUNDARY)) | (!(qi::alpha | qi::char_("_")));
BOUNDARIES = (BOUNDARY >> *(BOUNDARY) | NO_BOUNDARY);
BOUNDARY = BOUNDARY__SPACE | BOUNDARY__TAB | BOUNDARY__VERTICAL_TAB | BOUNDARY__FORM_FEED | BOUNDARY__CARRIAGE_RETURN | BOUNDARY__LINE_FEED | BOUNDARY__NULL;
BOUNDARY__SPACE = " ";
BOUNDARY__TAB = "\t";
BOUNDARY__VERTICAL_TAB = "\v";
BOUNDARY__FORM_FEED = "\f";
BOUNDARY__CARRIAGE_RETURN = "\r";
BOUNDARY__LINE_FEED = "\n";
BOUNDARY__NULL = "\0";
NO_BOUNDARY = "";
#define WHITESPACES \
STRICT_BOUNDARIES, \
BOUNDARIES, \
BOUNDARY, \
BOUNDARY__SPACE, \
BOUNDARY__TAB, \
BOUNDARY__VERTICAL_TAB, \
BOUNDARY__FORM_FEED, \
BOUNDARY__CARRIAGE_RETURN, \
BOUNDARY__LINE_FEED, \
BOUNDARY__NULL, \
NO_BOUNDARY

