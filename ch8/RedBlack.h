#include "../ch7/BST.h"

template <typename T>
class RedBlack: public BST<T>{
    protected:
        void solveDoubleRed(BinNodePosi<T> x);
        void solveDoubleBlack(BinNodePosi<T> x);
        int updateHeight(BinNodePosi<T> x);

    public:
        BST::search(const T& e);
        BinNodePosi<T> insert(const T& e);
        bool remove(const T& e);
};