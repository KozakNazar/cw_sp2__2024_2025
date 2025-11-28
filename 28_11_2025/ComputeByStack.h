#ifndef COMPUTE_BY_STACK_H 
#define COMPUTE_BY_STACK_H 
enum ElementType {
    VARIABLE,
    VALUE,
    OPERATION
};

union ElementData {
    int* variablePtr;
    int value;
    char operation;

    ElementData(int* ptr);
    ElementData(int val);
    ElementData(char op);
    ElementData();
};

struct Element {
    ElementType type;
    ElementData data;
};

int assignFunction(int* arg1, int arg2);
void assign(MyStack<Element>& operandsStack, int(*assignFunctionWithReturn)(int*, int));

int sumFunction(int arg1, int arg2);
int subFunction(int arg1, int arg2);
int divFunction(int arg1, int arg2);
int mulFunction(int arg1, int arg2);
int modFunction(int arg1, int arg2);
void binary(MyStack<Element>& operandsStack, int(*binaryFunction)(int, int));

int notFunction(int arg);
void unary(MyStack<Element>& operandsStack, int(*unaryFunction)(int));
#include "ComputeByStack.hpp"
#endif
