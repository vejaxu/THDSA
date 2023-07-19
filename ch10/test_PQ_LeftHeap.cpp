#include <iostream>
#include "PQ_LeftHeap.h"

class Visit{
    public:
        template<typename T>
        void operator()(T value){
            std::cout << value << "  ";
        }
};


int main(){
    PQ_LeftHeap<int> a = PQ_LeftHeap<int>();
    PQ_LeftHeap<int> b = PQ_LeftHeap<int>();
    a.insert(5);
    b.insert(4);
    a.insert(10);
    a.insert(20);

    Visit visit;
    a.BinTree<int>::travLevel(a.root(), visit);
    std::cout << std::endl;
    b.BinTree<int>::travLevel(b.root(), visit);
    std::cout << std::endl;
    merge(a.root(), b.root());
    a.travLevel(a.root(), visit);
    std::cout << std::endl;
    b.travLevel(b.root(), visit);
    std::cout << std::endl;
    a.insert(100);
    a.travLevel(a.root(), visit);
    std::cout << std::endl;
    a.delMax();
    a.travLevel(a.root(), visit);
    std::cout << std::endl;
}