#include <iostream>
#include "BinTree.h"


class Visit{
    public:
        template<typename T>
        void operator()(T value){
            std::cout << value << "  ";
        }
};

main(){
    BinTree<int> myTree = BinTree<int>();
    myTree.insertAsRoot(0);
    std::cout << myTree.size() << std::endl;
    BinNodePosi<int> x = myTree.root();
    myTree.insertAsLC(x, 1);
    myTree.insertAsRC(x, 2);
    myTree.insertAsLC(x->lchild, 3);
    myTree.insertAsRC(x->lchild, 4);
    myTree.insertAsLC(x->rchild, 5);
    myTree.insertAsRC(x->rchild, 6);
    std::cout << myTree.size() << std::endl;
    Stack<BinNodePosi<int>> S;
    Visit visit;
    myTree.travPre_R(myTree.root(), visit);
    std::cout << std::endl;
    myTree.travPre_I1(myTree.root(), visit);
    std::cout << std::endl;
    myTree.travPre_I2(myTree.root(), visit);
    std::cout << std::endl;
    myTree.travIn_R(myTree.root(), visit);
    std::cout << std::endl;
    myTree.travIn_I(myTree.root(), visit);
    std::cout << std::endl;
    myTree.travIn_I2(myTree.root(), visit);
    std::cout << std::endl;
    myTree.travIn_I3(myTree.root(), visit);
    std::cout << std::endl;
    myTree.travPost_R(myTree.root(), visit);
    std::cout << std::endl;
    myTree.travPost_I(myTree.root(), visit);
    std::cout << std::endl;
    myTree.travLevel(myTree.root(), visit);
    std::cout << std::endl;
    BinNodePosi<int> m, n;
    m = myTree.root()->lchild;
    std::cout << m->data << m->success()->data << std::endl;
    n = myTree.root()->rchild;
    std::cout << n->data << n->pred()->data << std::endl;
}