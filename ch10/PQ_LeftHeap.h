#include "PriorityQueue.h"
#include "../ch5/BinTree.h"

//左式堆
//使用二叉树存储
template <typename T>
class PQ_LeftHeap: public PQ<T>, public BinTree<T>{
    public:
        PQ_LeftHeap(){}
        PQ_LeftHeap(T* E, int n){
            for (int i = 0; i < n; i ++){
                insert(E[i]);
            }
        }

        void insert(T);
        T getMax(){return BinTree<T>::_root->data;}
        T delMax();
};


template <typename T>
static BinNodePosi<T> merge(BinNodePosi<T> a, BinNodePosi<T> b){
    if(! a) return b;
    if(! b) return a;
    if(lt(a->data, b->data)) swap(b, a);
    a->rchild = merge(a->rchild, b); //递归地合并a的右子树与b
    a->rchild->parent = a; //更新父子关系
    if(!(a->lchild) || a->lchild->npl < a->rchild->npl) //局部满足左倾性
        swap(a->lchild, a->rchild);
    a->npl = a->rchild ? a->rchild->npl + 1: 1;
    return a;
}


template <typename T>
void PQ_LeftHeap<T>::insert(T e){
    BinNodePosi<T> v = new BinNode<T>(e);
    BinTree<T>::_root = merge(BinTree<T>::_root, v);
    BinTree<int>::_root->parent = NULL;
    BinTree<T>::_size ++;
}


template <typename T>
T PQ_LeftHeap<T>::delMax(){
    BinNodePosi<T> lheap = BinTree<T>::_root->lchild;
    BinNodePosi<T> rheap = BinTree<T>::_root->rchild;
    T e = BinTree<T>::_root->data;
    delete BinTree<T>::_root;
    BinTree<T>::_size --;
    BinTree<T>::_root = merge(lheap, rheap);
    if(BinTree<T>::_root) BinTree<T>::_root->parent = NULL;
    return e;
}