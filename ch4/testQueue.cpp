#include <iostream>
#include "MyQueue.h"


template <typename T>
void traverseQ(T e){
    std::cout << e << ' ';
}
template <typename T>
void output(Queue<T> Q){
    std::cout << "current Queue size: " << Q.size() << std::endl;
    std::cout << "current Queue content: " << std::endl;
    Q.traverse(traverseQ);
    std::cout << std::endl;
}


main(){
    Queue<int> myQueue = Queue<int>();
    for (int i = 0; i < 10; i ++){
        myQueue.enqueue(i);
    }
    output(myQueue);
    std::cout << "队首出队: " << std::endl;
    std::cout << "出队元素为: " << myQueue.dequeue() << std::endl;
    output(myQueue);
    std::cout << "队尾入队" << std::endl;
    myQueue.enqueue(10);
    output(myQueue);
}