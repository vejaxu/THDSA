#include <iostream>
#include "MyQueue.h"
#include "../Visit.h"


template <typename T>
void output(Queue<T> Q){
    Visit visit;
    Q.traverse(visit);
    std::cout << std::endl;
}


int main(){
    Queue<int> myQueue = Queue<int>();
    for (int i = 0; i < 10; i ++){
        myQueue.enqueue(i);
    }
    output(myQueue);
    myQueue.enqueue(10);
    output(myQueue);
    myQueue.dequeue();
    output(myQueue);
    std::cout << myQueue.front() << std::endl;
}