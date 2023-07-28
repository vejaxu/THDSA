#include "BST.h"
#define Balanced(x) (stature((x).lchild) == stature((x).rchild)) //是否平衡
#define BalFax(x) (stature((x).lchild) - stature((x).rchild)) //平衡因子
#define AvlBalanced(x) ((-2 < BalFax(x)) && (BalFax(x) < 2)) //平衡因子是否小于1
#define tallerChild(x) (\
    stature((x)->lchild) > stature((x)->rchild) ? (x)->lchild:(\
    stature((x)->rchild) > stature((x)->lchild) ? (x)->rchild:(\
    IsLChild(*(x)) ? (x)->lchild: (x)->rchild\
    )\
    )\
)


template <typename T>
class AVL: public BST<T>{
    public:
        BinNodePosi<T> insert(const T& e);
        //插入节点发生失衡，则一定是较高的子树被插入了节点，则（几乎所有）祖先的高度会发生变化
        bool remove(const T& e);
        //删除如果发生失衡，则一定是较矮的子树节点被删除，则祖先的高度不会发生改变
};


//34连接
template <typename T>
BinNodePosi<T> BST<T>::connect34(
    BinNodePosi<T> a, BinNodePosi<T> b, BinNodePosi<T> c,
    BinNodePosi<T> T0, BinNodePosi<T> T1, BinNodePosi<T> T2, BinNodePosi<T> T3
){
    a->lchild = T0;
    if(T0){T0->parent = a;}
    a->rchild = T1;
    if(T1){
        T1->parent = a;
        BinTree<T>::updateHeight(a);
    }
    c->lchild = T2;
    if(T2){T2->parent = c;}
    c->rchild = T3;
    if(T3){
        T3->parent = c;
        BinTree<T>::updateHeight(c);
    }
    b->lchild = a;
    a->parent = b;
    b->rchild = c;
    c->parent = b;
    BinTree<T>::updateHeight(b);
    return b;
}


//旋转操作
//四种情况，我们直接实现其最后的结果即可
template <typename T>
BinNodePosi<T> BST<T>::rotateAt(BinNodePosi<T> v){
    BinNodePosi<T> p = v->parent;
    BinNodePosi<T> g = p->parent;
    if(IsLChild(*p)){
        if(IsLChild(*v)){
            p->parent = g->parent;
            return connect34(v, p, g, v->lchild, v->rchild, p->rchild, g->rchild);
        }
        else{
            v->parent = g->parent;
            return connect34(p, v, g, p->lchild, v->lchild, v->rchild, g->rchild);
        }
    }
    else{
        if(IsRChild(*v)){
            p->parent = g->parent;
            return connect34(g, p, v, g->lchild, p->lchild, v->lchild, v->rchild);
        }
        else{ //zig-zag，先顺时针p，再逆时针v
            v->parent = g->parent;
            return connect34(g, v, p, g->lchild, v->lchild, v->rchild, p->lchild);
        }
    }
}


template <typename T>
BinNodePosi<T> AVL<T>::insert(const T& e){
    BinNodePosi<T>& x = BST<T>::search(e);
    if(x) return x;
    BinNodePosi<T> xx = x = new BinNode<T>(e, BST<T>::_hot);
    BinTree<T>::_size ++;
    for(BinNodePosi<T> g = BST<T>::_hot; g; g->parent){
        if(!AvlBalanced(*g)){ //一旦失衡，必然是失衡祖先中的最低者
            FromParentTo(*g) = BST<T>::rotateAt(tallerChild(tallerChild(g))); //祖父节点g，g更高的孩子p，p更高的孩子v
            break; //插入失衡修复后，只要最矮的祖先重平衡，则整棵树重平衡，则直接退出
        }else{
            BinTree<T>::updateHeight(g);
        }
    }
    return x;
}


template <typename T>
bool AVL<T>::remove(const T& e){
    BinNodePosi<T>& x = BST<T>::search(e);
    if(!x) return false;
    removeAt(x, BST<T>::_hot);
    BinTree<T>::_size --;
    for(BinNodePosi<T> g = BST<T>::_hot; g; g = g->parent){
        if(!AvlBalanced(*g)){
            g = FromParentTo(*g) = BST<T>::rotateAt(tallerChild(tallerChild(g)));
        }
       BinTree<T>::updateHeight(g);
    }
    return true;
}