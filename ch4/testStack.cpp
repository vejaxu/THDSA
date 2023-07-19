#include <iostream>
#include "MyStack.h"
using namespace std;


//遍历输出
template <typename T>
void traverseV(T e){
    std::cout << e << ' ';
}


template <typename T>
void output(Stack<T> V){
    std::cout << "current Stack size: " << V.size() << std::endl;
    std::cout << "current Stack capacity: " << V.capacity() << std::endl;
    std::cout << "current Stack content: " << std::endl;
    V.traverse(traverseV);
    std::cout << std::endl;
}


int main(){
    Stack<int> myStack = Stack<int>();
    for (Rank i = 0; i < 10; i ++)
        myStack.push(i);
    output(myStack);
    cout << "删除栈顶元素为: " << myStack.pop() << endl;
    output(myStack);
    cout << "删除栈顶元素: " << myStack.top() << endl;

    Stack<int> reverseStack = Stack<int>();
    int mystack_size = myStack.size();
    for (Rank i = 0; i < mystack_size; i ++){
        reverseStack.push(myStack.pop());
    }
    cout << "栈的逆序: " << endl;
    output(reverseStack);
}