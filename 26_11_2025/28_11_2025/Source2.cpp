#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <stdio.h>
#define bool int
#define false 0
#define true 1

// operators
// precedence   operators       associativity
// 1            !               right to left
// 2            * / %           left to right
// 3            + -             left to right
// 4            =                right to left
int op_preced(const char c)
{
    switch (c) {
    case '!':
        return 4;
    case '*':  case '/': case '%':
        return 3;
    case '+': case '-':
        return 2;
    case '=':
        return 1;
    }
    return 0;
}

bool op_left_assoc(const char c)
{
    switch (c) {
        // left to right
    case '*': case '/': case '%': case '+': case '-':
        return true;
        // right to left
    case '=': case '!':
        return false;
    }
    return false;
}

unsigned int op_arg_count(const char c)
{
    switch (c) {
    case '*': case '/': case '%': case '+': case '-': case '=':
        return 2;
    case '!':
        return 1;
    default:
        return c - 'A';
    }
    return 0;
}

#define is_operator(c)  (c == '+' || c == '-' || c == '/' || c == '*' || c == '!' || c == '%' || c == '=')
#define is_function(c)  (c >= 'A' && c <= 'Z')
#define is_ident(c)     ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z'))

bool shunting_yard(const char* input, char* output)
{
    const char* strpos = input, * strend = input + strlen(input);
    char c, * outpos = output;

    char stack[32];       // operator stack
    unsigned int sl = 0;  // stack length
    char     sc;          // used for record stack element

    while (strpos < strend) {
        // read one token from the input stream
        c = *strpos;
        if (c != ' ') {
            // If the token is a number (identifier), then add it to the output queue.
            if (is_ident(c)) {
                *outpos = c; ++outpos;
            }
            // If the token is a function token, then push it onto the stack.
            else if (is_function(c)) {
                stack[sl] = c;
                ++sl;
            }
            // If the token is a function argument separator (e.g., a comma):
            else if (c == ',') {
                bool pe = false;
                while (sl > 0) {
                    sc = stack[sl - 1];
                    if (sc == '(') {
                        pe = true;
                        break;
                    }
                    else {
                        // Until the token at the top of the stack is a left parenthesis,
                        // pop operators off the stack onto the output queue.
                        *outpos = sc;
                        ++outpos;
                        sl--;
                    }
                }
                // If no left parentheses are encountered, either the separator was misplaced
                // or parentheses were mismatched.
                if (!pe) {
                    printf("Error: separator or parentheses mismatched\n");
                    return false;
                }
            }
            // If the token is an operator, op1, then:
            else if (is_operator(c)) {
                while (sl > 0) {
                    sc = stack[sl - 1];
                    // While there is an operator token, o2, at the top of the stack
                    // op1 is left-associative and its precedence is less than or equal to that of op2,
                    // or op1 is right-associative and its precedence is less than that of op2,
                    if (is_operator(sc) &&
                        ((op_left_assoc(c) && (op_preced(c) <= op_preced(sc))) ||
                            (!op_left_assoc(c) && (op_preced(c) < op_preced(sc))))) {
                        // Pop o2 off the stack, onto the output queue;
                        *outpos = sc;
                        ++outpos;
                        sl--;
                    }
                    else {
                        break;
                    }
                }
                // push op1 onto the stack.
                stack[sl] = c;
                ++sl;
            }
            // If the token is a left parenthesis, then push it onto the stack.
            else if (c == '(') {
                stack[sl] = c;
                ++sl;
            }
            // If the token is a right parenthesis:
            else if (c == ')') {
                bool pe = false;
                // Until the token at the top of the stack is a left parenthesis,
                // pop operators off the stack onto the output queue
                while (sl > 0) {
                    sc = stack[sl - 1];
                    if (sc == '(') {
                        pe = true;
                        break;
                    }
                    else {
                        *outpos = sc;
                        ++outpos;
                        sl--;
                    }
                }
                // If the stack runs out without finding a left parenthesis, then there are mismatched parentheses.
                if (!pe) {
                    printf("Error: parentheses mismatched\n");
                    return false;
                }
                // Pop the left parenthesis from the stack, but not onto the output queue.
                sl--;
                // If the token at the top of the stack is a function token, pop it onto the output queue.
                if (sl > 0) {
                    sc = stack[sl - 1];
                    if (is_function(sc)) {
                        *outpos = sc;
                        ++outpos;
                        sl--;
                    }
                }
            }
            else {
                printf("Unknown token %c\n", c);
                return false; // Unknown token
            }
        }
        ++strpos;
    }
    // When there are no more tokens to read:
    // While there are still operator tokens in the stack:
    while (sl > 0) {
        sc = stack[sl - 1];
        if (sc == '(' || sc == ')') {
            printf("Error: parentheses mismatched\n");
            return false;
        }
        *outpos = sc;
        ++outpos;
        --sl;
    }
    *outpos = 0; // Null terminator
    return true;
}

bool execution_order(const char* input) {
    printf("order: (arguments in reverse order)\n");
    const char* strpos = input, * strend = input + strlen(input);
    char c, res[4];
    unsigned int sl = 0, sc, stack[32], rn = 0;
    // While there are input tokens left
    while (strpos < strend) {
        // Read the next token from input.
        c = *strpos;
        // If the token is a value or identifier
        if (is_ident(c)) {
            // Push it onto the stack.
            stack[sl] = c;
            ++sl;
        }
        // Otherwise, the token is an operator  (operator here includes both operators, and functions).
        else if (is_operator(c) || is_function(c)) {
            sprintf(res, "_%02d", rn);
            printf("%s = ", res);
            ++rn;
            // It is known a priori that the operator takes n arguments.
            unsigned int nargs = op_arg_count(c);
            // If there are fewer than n values on the stack
            if (sl < nargs) {
                // (Error) The user has not input sufficient values in the expression.
                return false;
            }
            // Else, Pop the top n values from the stack.
            // Evaluate the operator, with the values as arguments.
            if (is_function(c)) {
                printf("%c(", c);
                while (nargs > 0) {
                    sc = stack[sl - 1];
                    sl--;
                    if (nargs > 1) {
                        printf("%s, ", (char*)&sc);
                    }
                    else {
                        printf("%s)\n", (char*)&sc);
                    }
                    --nargs;
                }
            }
            else {
                if (nargs == 1) {
                    sc = stack[sl - 1];
                    sl--;
                    printf("%c %s;\n", c, (char*)&sc);
                }
                else {
                    sc = stack[sl - 1];
                    sl--;
                    printf("%s %c ", (char*)&sc, c);
                    sc = stack[sl - 1];
                    sl--;
                    printf("%s;\n", (char*)&sc);
                }
            }
            // Push the returned results, if any, back onto the stack.
            stack[sl] = *(unsigned int*)res;
            ++sl;
        }
        ++strpos;
    }
    // If there is only one value in the stack
    // That value is the result of the calculation.
    if (sl == 1) {
        sc = stack[sl - 1];
        sl--;
        printf("%s is a result\n", (char*)&sc);
        return true;
    }
    // If there are more values in the stack
    // (Error) The user input has too many values.
    return false;
}

bool execution_order__arguments_in_forward_order(const char* input) {
    const char* strpos = input, * strend = input + strlen(input);
    char c, res[4];
    unsigned long long int sl = 0, sc, stack[32], rn = 0;
    // While there are input tokens left
    while (strpos < strend) {
        // Read the next token from input.
        c = *strpos;
        // If the token is a value or identifier
        if (is_ident(c)) {
            // Push it onto the stack.
            stack[sl] = c;
            ++sl;
        }
        // Otherwise, the token is an operator  (operator here includes both operators, and functions).
        else if (is_operator(c) || is_function(c)) {
            sprintf(res, "_%02d", (int)rn);
            printf("%s = ", res);
            ++rn;
            // It is known a priori that the operator takes n arguments.
            unsigned long long int nargs = op_arg_count(c);
            // If there are fewer than n values on the stack
            if (sl < nargs) {
                // (Error) The user has not input sufficient values in the expression.
                return false;
            }
            // Else, Pop the top n values from the stack.
            // Evaluate the operator, with the values as arguments.
            if (is_function(c)) {
                printf("%c(", c);
                while (nargs > 0) {
                    sc = stack[sl - nargs];
                    if (nargs > 1) {
                        printf("%s, ", (char*)&sc);
                    }
                    else {
                        printf("%s)\n", (char*)&sc);
                    }
                    --nargs;
                }
                sl -= op_arg_count(c);
            }
            else {
                if (nargs == 1) {
                    sc = stack[sl - 1];
                    sl--;
                    printf("%c %s;\n", c, (char*)&sc);
                }
                else {
                    sc = stack[sl - 2];
                    printf("%s %c ", (char*)&sc, c);
                    sc = stack[sl - 1];
                    sl -= 2;
                    printf("%s;\n", (char*)&sc);
                }
            }
            // Push the returned results, if any, back onto the stack.
            stack[sl] = *(unsigned long long int*)res;
            ++sl;
        }
        ++strpos;
    }
    // If there is only one value in the stack
    // That value is the result of the calculation.
    if (sl == 1) {
        sc = stack[sl - 1];
        sl--;
        printf("%s is a result\n", (char*)&sc);
        return true;
    }
    // If there are more values in the stack
    // (Error) The user input has too many values.
    return false;
}

bool genCModelOfSSA(const char* input) {
    const char* strpos = input, * strend = input + strlen(input);
    char c, res[4], outputData[2048], *currentOutputDataPosition = outputData;
    unsigned long long int sl = 0, sc, stack[32], rn = 0;
    // While there are input tokens left
    while (strpos < strend) {
        // Read the next token from input.
        c = *strpos;
        // If the token is a value or identifier
        if (is_ident(c)) {
            // Push it onto the stack.
            stack[sl] = c;
            ++sl;
        }
        // Otherwise, the token is an operator  (operator here includes both operators, and functions).
        else if (is_operator(c) || is_function(c)) {
            sprintf(res, "_%02d", (int)rn);
            currentOutputDataPosition += sprintf(currentOutputDataPosition, "int %s = ", res);
            ++rn;
            // It is known a priori that the operator takes n arguments.
            unsigned long long int nargs = op_arg_count(c);
            // If there are fewer than n values on the stack
            if (sl < nargs) {
                // (Error) The user has not input sufficient values in the expression.
                return false;
            }
            // Else, Pop the top n values from the stack.
            // Evaluate the operator, with the values as arguments.
            if (is_function(c)) {
                currentOutputDataPosition += sprintf(currentOutputDataPosition, "%c(", c);
                while (nargs > 0) {
                    sc = stack[sl - nargs];
                    if (nargs > 1) {
                        currentOutputDataPosition += sprintf(currentOutputDataPosition, "%s, ", (char*)&sc);
                    }
                    else {
                        currentOutputDataPosition += sprintf(currentOutputDataPosition, "%s)\n", (char*)&sc);
                    }
                    --nargs;
                }
                sl -= op_arg_count(c);
            }
            else {
                if (nargs == 1) {
                    sc = stack[sl - 1];
                    sl--;
                    currentOutputDataPosition += sprintf(currentOutputDataPosition, "%c %s;\n", c, (char*)&sc);
                }
                else {
                    sc = stack[sl - 2];
                    currentOutputDataPosition += sprintf(currentOutputDataPosition, "%s %c ", (char*)&sc, c);
                    sc = stack[sl - 1];
                    sl -= 2;
                    currentOutputDataPosition += sprintf(currentOutputDataPosition, "%s;\n", (char*)&sc);
                }
            }
            // Push the returned results, if any, back onto the stack.
            stack[sl] = *(unsigned long long int*)res;
            ++sl;
        }
        ++strpos;
    }
    // If there is only one value in the stack
    // That value is the result of the calculation.
    if (sl == 1) {
        printf("#include \"stdio.h\"\n");
        printf("int main() {\n");
        for (const char * input_ = input; *input_; ++input_) {
            if (*input_ >= 'a' && *input_ <= 'z') {
                printf("int %c = %d;\n", *input_, input_ - input);
            }
        }
        sc = stack[sl - 1];
        sl--;
        printf("\n%s\nprintf(\"Result: is %%d.\", %s);\n", outputData, (char*)&sc); 
        printf("(void)getchar();\n");
        printf("\nreturn 0;\n");
        printf("}\n");
        return true;
    }
    // If there are more values in the stack
    // (Error) The user input has too many values.
    return false;
}

void genCModelOfRPN(const char* input) {
    printf("#include \"stdio.h\"\n");
    printf("#include \"stdlib.h\"\n");
    printf("#include \"MyStack.h\"\n");
    printf("#include \"ComputeByStack.h\"\n");
    printf("\n");
    printf("int main() {\n");
    printf("// Compute implementation in files: \"MyStack.h\", \"MyStack.hpp\", \"ComputeByStack.h\" and \"ComputeByStack.hpp\"\n");
    printf("MyStack<Element> operandsStack;\n");
    for (const char* input_ = input; *input_; ++input_) {
        if (*input_ >= 'a' && *input_ <= 'z') {
            printf("int %c = %d;\n", *input_, input_ - input);
        }
    }

    printf("    Element elements[] = {\n");
for (const char* input_ = input; *input_; ++input_) {
    if (*input_ >= 'a' && *input_ <= 'z') { 
        printf("        {VARIABLE, &%c},\n", *input_);
    }
    else     if (*input_ >= '0' && *input_ <= '9') {
        printf("        {VALUE, &%c},\n", *input_);
    }
    else     if (*input_ == '=' || *input_ == '+' || *input_ == '-' || *input_ == '*' || *input_ == '/' || *input_ == '%' || *input_ == '!') {
        printf("        {OPERATION, \'%c\'},\n", *input_);
    }
}
printf("        {VARIABLE, NULL}\n");
printf("    };\n");

printf(
    "    for (unsigned int index = 0; elements[index].type != VARIABLE || elements[index].data.variablePtr != NULL; ++index) {\n"
    "        if (elements[index].type == VARIABLE || elements[index].type == VALUE) {\n"
    "            operandsStack.push(elements[index]);\n"
    "        }\n"
    "        else if (elements[index].type == OPERATION) {\n"
    "            switch (elements[index].data.operation) {\n"
    "            case '=':\n"
    "                assign(operandsStack, assignFunction);\n"
    "                break;\n"
    "            case '-':\n"
    "                binary(operandsStack, subFunction);\n"
    "                break;\n"
    "            case '+':\n"
    "                binary(operandsStack, sumFunction);\n"
    "                break;\n"
    "            case '/':\n"
    "                binary(operandsStack, divFunction);\n"
    "                break;\n"
    "            case '*':\n"
    "                binary(operandsStack, mulFunction);\n"
    "                break;\n"
    "            case '%%':\n"
    "                binary(operandsStack, modFunction);\n"
    "                break;\n"
    "            case '!':\n"
    "                unary(operandsStack, notFunction);\n"
    "                break;\n"
    "            default:\n"
    "                break;\n"
    "            }\n"
    "        }\n"
    "    }\n"
);


printf("    printf(\"Result: is %%d.\", operandsStack.top().data.value\);\n");
printf("    (void)getchar();\n");
printf("\n");
printf("    return 0;\n");
printf("}\n");

}

int oldMain() {
    // functions: A() B(a) C(a, b), D(a, b, c) ...
    // identifiers: 0 1 2 3 ... and a b c d e ...
    // operators: = - + / * % !
    const char* input = "a = D(f - b * c + d, !e, g)";
    //const char* input = "a = 1 + 2 * ((3 * 4) + (1/5))"; 
    char output[128];
    printf("input: %s\n", input);
    if (shunting_yard(input, output)) {
        printf("output: %s\n", output);
        if (!execution_order__arguments_in_forward_order(output))
            printf("\nInvalid input\n");
    }
    return 0;
}

int main() {
    // functions: A() B(a) C(a, b), D(a, b, c) ...
    // identifiers: 0 1 2 3 ... and a b c d e ...
    // operators: = - + / * % !
    //const char* input = "a = D(f - b * c + d, !e, g)";
    //const char* input = "x = 1 + 2 * ((3 * 4) + (1/5))"; 
    const char* input = "x = a + b * (c * d + e/f)";
    char output[128];
    printf("#define _CRT_SECURE_NO_WARNINGS\n");

    printf("// input: %s\n", input);
    if (shunting_yard(input, output)) {
        printf("// output: %s\n", output);
        printf("\n");
        printf("#define USE_C_MODEL_OF_SSA\n");
        printf("#ifdef USE_C_MODEL_OF_SSA\n");
        if (!genCModelOfSSA(output))
            printf("\n// Invalid input\n");
        printf("#else\n");
        genCModelOfRPN(output);
        printf("#endif\n");
    }
    return 0;
}