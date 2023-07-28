#include <iostream>
#include "AVL.h"
#include "../Visit.h"


int main(){
    Visit visit;
    AVL<int> avl = AVL<int>();
    avl.insertAsRoot(100);
    avl.travLevel(avl.root(), visit);
    std::cout << std::endl;
    avl.insertAsLC(avl.root(), 80);
    avl.travLevel(avl.root(), visit);
    std::cout << std::endl;
    avl.insertAsRC(avl.root(), 120);
    avl.travLevel(avl.root(), visit);
    std::cout << std::endl;
/*     avl.insert(140);
    avl.travLevel(avl.root(), visit);
    std::cout << std::endl; */
    avl.remove(100);
    avl.travLevel(avl.root(), visit);
    std::cout << std::endl;
    return 0;
}