#include "stdio.h"
#include "stdlib.h"
#include "MyStack.h"
#include "ComputeByStack.h"

ElementData::ElementData(int* ptr) : variablePtr(ptr) {}
ElementData::ElementData(int val)  : value(val) {}
ElementData::ElementData(char op)  : operation(op) {}
ElementData::ElementData()         : value(0) {}

int assignFunction(int* arg1, int arg2) {
    return *arg1 = arg2;
}

void assign(MyStack<Element>& operandsStack, int(*assignFunctionWithReturn)(int*, int)) {
    int* arg1 = NULL, arg2 = 0;
    if (operandsStack.top().type == VARIABLE) {
        arg2 = *operandsStack.top().data.variablePtr;
    }
    else if (operandsStack.top().type == VALUE) {
        arg2 = operandsStack.top().data.value;
    }
    else {
        printf("error");
        exit(0);
    }
    operandsStack.pop();

    if (operandsStack.top().type == VARIABLE)
        arg1 = operandsStack.top().data.variablePtr;
    else {
        printf("error");
        exit(0);
    }
    operandsStack.pop();

    Element result;
    result.type = VALUE;
    result.data.value = assignFunctionWithReturn(arg1, arg2);
    operandsStack.push(result);
}

int sumFunction(int arg1, int arg2) {
    return arg1 + arg2;
}

int subFunction(int arg1, int arg2) {
    return arg1 - arg2;
}

int divFunction(int arg1, int arg2) {
    return arg1 / arg2;
}

int mulFunction(int arg1, int arg2) {
    return arg1 * arg2;
}

int modFunction(int arg1, int arg2) {
    return arg1 % arg2;
}

void binary(MyStack<Element>& operandsStack, int(*binaryFunction)(int, int)) {
    int arg1 = 0, arg2 = 0;
    if (operandsStack.top().type == VARIABLE) {
        arg2 = *operandsStack.top().data.variablePtr;
    }
    else if (operandsStack.top().type == VALUE) {
        arg2 = operandsStack.top().data.value;
    }
    else {
        printf("error");
        exit(0);
    }
    operandsStack.pop();

    if (operandsStack.top().type == VARIABLE) {
        arg1 = *operandsStack.top().data.variablePtr;
    }
    else if (operandsStack.top().type == VALUE) {
        arg1 = operandsStack.top().data.value;
    }
    else {
        printf("error");
        exit(0);
    }
    operandsStack.pop();

    Element result;
    result.type = VALUE;
    result.data.value = binaryFunction(arg1, arg2);
    operandsStack.push(result);
}

int notFunction(int arg) {
    return !arg;
}

void unary(MyStack<Element>& operandsStack, int(*unaryFunction)(int)) {
    int arg = 0;
    if (operandsStack.top().type == VARIABLE) {
        arg = *operandsStack.top().data.variablePtr;
    }
    else if (operandsStack.top().type == VALUE) {
        arg = operandsStack.top().data.value;
    }
    else {
        printf("error");
        exit(0);
    }
    operandsStack.pop();

    Element result;
    result.type = VALUE;
    result.data.value = unaryFunction(arg);
    operandsStack.push(result);
}
