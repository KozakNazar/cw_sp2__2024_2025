keyword =
tokenCOLON |
tokenGOTO |
tokenINTEGER16 |
tokenCOMMA |
tokenNOT |
tokenAND |
tokenOR |
tokenEQUAL |
tokenNOTEQUAL |
tokenLESSOREQUAL |
tokenGREATEROREQUAL |
tokenLESS |
tokenGREATER |
tokenPLUS |
tokenMINUS |
tokenMUL |
tokenDIV |
tokenMOD |
tokenGROUPEXPRESSIONBEGIN |
tokenGROUPEXPRESSIONEND |
tokenLRBIND |
tokenELSE |
tokenIF |
tokenDO |
tokenFOR |
tokenTO |
tokenDOWNTO |
tokenWHILE |
tokenCONTINUE |
tokenBREAK |
tokenEXIT |
tokenREPEAT |
tokenUNTIL |
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
tokenSEMICOLON;
tokens_in_program = SAME_RULE(token_iteration);
token = keyword | ident | value;
token_iteration = token >> token_iteration | "";
digit = digit_0 | non_zero_digit;
digit_optional = digit | "";
non_zero_digit = digit_1 | digit_2 | digit_3 | digit_4 | digit_5 | digit_6 | digit_7 | digit_8 | digit_9;
unsigned_value = (non_zero_digit >> digit_optional | digit_0) >> BOUNDARIES;

value = sign_optional >> unsigned_value >> BOUNDARIES;
letter_in_lower_case = a | b | c | d | e | f | g | h | i | j | k | l | m | n | o | p | q | r | s | t | u | v | w | x | y | z;
letter_in_upper_case = A | B | C | D | E | F | G | H | I | J | K | L | M | N | O | P | Q | R | S | T | U | V | W | X | Y | Z;
ident = tokenUNDERSCORE >> letter_in_upper_case >> letter_in_upper_case >> letter_in_upper_case >> letter_in_upper_case >> letter_in_upper_case >> letter_in_upper_case >> letter_in_upper_case >> STRICT_BOUNDARIES;
sign = sign_plus | sign_minus;
sign_optional = sign | "";
sign_plus = SAME_RULE(tokenPLUS);
sign_minus = SAME_RULE(tokenMINUS);
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
tokenBEGINBLOCK = "{" >> BOUNDARIES;
tokenENDBLOCK = "}" >> BOUNDARIES;
tokenLEFTSQUAREBRACKETS = "[" >> BOUNDARIES;
tokenRIGHTSQUAREBRACKETS = "]" >> BOUNDARIES;
tokenSEMICOLON = ";" >> BOUNDARIES;
STRICT_BOUNDARIES = (BOUNDARY >> *(BOUNDARY)) | (!(qi::alpha | qi::char_("_")));
BOUNDARIES = (BOUNDARY >> *(BOUNDARY) | NO_BOUNDARY);
BOUNDARY = BOUNDARY_SPACE | BOUNDARY_TAB | BOUNDARY_CARRIAGE_RETURN | BOUNDARY_LINE_FEED | BOUNDARY_NULL;
BOUNDARY_SPACE = " ";
BOUNDARY_TAB = "\t";
BOUNDARY_CARRIAGE_RETURN = "\r";
BOUNDARY_LINE_FEED = "\n";
BOUNDARY_NULL = "\0";
NO_BOUNDARY = "";
tokenUNDERSCORE = "_";
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