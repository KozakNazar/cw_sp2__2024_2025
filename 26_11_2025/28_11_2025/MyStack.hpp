//#ifndef MAIN_SAVITCH_STACK1_HPP 
//#define MAIN_SAVITCH_STACK1_HPP 

#include "MyStack.h"
#include <cassert>

template <class Item>
MyStack<Item>::MyStack() {
    used = 0; 
}

template <class Item>
void MyStack<Item>::push(const Item& entry){
    assert(size() < CAPACITY);
    data[used] = entry;
    ++used;
}

template <class Item>
void MyStack<Item>::pop(){
    assert(!empty());
    --used;
}

template <class Item>
bool MyStack<Item>::empty() const {
    return (used == 0);
}

template <class Item>
size_t MyStack<Item>::size() const {
    return used; 
}

template <class Item>
Item MyStack<Item>::top() const {
    assert(!empty());
    return data[used - 1];
}

//#endif MAIN_SAVITCH_STACK1_HPP