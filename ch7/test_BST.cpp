#include <iostream>
#include "BST.h"

class Visit{
    public:
        template<typename T>
        void operator()(T value){
            std::cout << value << "  ";
        }
};


int main(){
    Visit visit;
    BST<int> myBst = BST<int>();
}