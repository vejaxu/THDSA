#include <iostream>
#include "BST.h"
#include "../Visit.h"


int main(){
    Visit visit;
    BST<int> myBst = BST<int>();
    myBst.insertAsRoot(10);
    myBst.travPre_I1(myBst.root(), visit);
    std::cout << std::endl;
    myBst.insert(20);
    myBst.travPre_I1(myBst.root(), visit);
    std::cout << std::endl;
    myBst.insert(5);
    myBst.travPre_I1(myBst.root(), visit);
    std::cout << std::endl;
    myBst.remove(20);
    myBst.travPre_I1(myBst.root(), visit);
    std::cout << std::endl;
}