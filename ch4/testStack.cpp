#include <iostream>
#include "MyStack.h"
#include "../Visit.h"


template <typename T>
void output(Stack<T> stack){
    Visit visit;
    stack.traverse(visit);
    std::cout << std::endl;
}


int main(){
        Visit visit;
    Stack<int> myStack = Stack<int>();
    for (Rank i = 0; i < 10; i ++)
        myStack.push(i);
    output(myStack);
    std::cout << myStack.pop();
    std::cout << std::endl;
    output(myStack);
    myStack.push(9);
    output(myStack);
    std::cout << myStack.top() << std::endl;
}