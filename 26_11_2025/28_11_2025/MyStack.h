#ifndef MAIN_STACK_H 
#define MAIN_STACK_H 
//#include <cstdlib>
template <class Item>
class MyStack {
public:
    static const size_t CAPACITY = 30;
    MyStack();
    void push(const Item& entry);
    void pop();
    bool empty() const;
    size_t size() const;
    Item top() const;
private:
    Item data[CAPACITY]; 
    size_t used;
}; 
#include "MyStack.hpp"
#endif

