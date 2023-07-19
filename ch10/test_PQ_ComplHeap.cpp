#include <iostream>
#include "PQ_ComplHeap.h"
using namespace std;
//遍历输出
template <typename T>
void traverseV(T e){
    std::cout << e << ' ';
}


template <typename T>
void output(PQ_ComplHeap<T> V){
    std::cout << "current Heap content: " << std::endl;
    V.traverse(traverseV);
    std::cout << std::endl;
}
template <typename T>
void output(Vector<T> V){
    std::cout << "current Vector content: " << std::endl;
    V.traverse(traverseV);
    std::cout << std::endl;
}


int main(){
    int A[10] = {10, 2, 4, 5, 6, 22, 33, 444, 666, 99};
    PQ_ComplHeap<int> myHeap = PQ_ComplHeap<int>(A, 10);
    Vector<int> myvector = Vector<int>(myHeap);
    output(myHeap);
    myHeap.delMax();
    output(myHeap);
    myvector.heapSort(0, myvector.size());
    output(myvector);
    myHeap.insert(10000);
    output(myHeap);
    myHeap.insert(777);
    output(myHeap);
    myHeap.delMax();
    output(myHeap);
}