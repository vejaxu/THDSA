//二叉搜索树
#include "../ch5/BinTree.h"

template <typename T>
class BST: public BinTree<T>{
    protected:
        BinNodePosi<T> _hot; //命中的父节点
        BinNodePosi<T> connect34( //3+4接口,联接三个节点与四棵子树
            BinNodePosi<T>, BinNodePosi<T>, BinNodePosi<T>,
            BinNodePosi<T>, BinNodePosi<T>, BinNodePosi<T>, BinNodePosi<T>
        );
        BinNodePosi<T> rotateAt(BinNodePosi<T> x); //对x及其父亲，祖父做统一旋转调整
    public: //虚函数，强制要求所有继承的子类重写
        virtual BinNodePosi<T> & search(const T& e);
        virtual BinNodePosi<T> insert(const T& e);
        virtual bool remove(const T& e);
};


template <typename T>
BinNodePosi<T> &BST<T>::search(const T& e){
    return searchIn(BinTree<T>::_root, e, _hot = NULL);
}

template <typename T>
static BinNodePosi<T> & searchIn(BinNodePosi<T> &v, const T& e, BinNodePosi<T> & hot){
    if(!v || (e == v->data)) return v;
    hot = v;
    return searchIn(((e < v->data) ? v->lchild: v->rchild), e, hot);
}


template <typename T>
BinNodePosi<T> BST<T>::insert(const T& e){
    BinNodePosi<T> x = search(e);
    if(x) return x;
    x = new BinNode<T>(e, _hot);
    BinTree<T>::_size++;
    BinTree<T>::updateHeightAbove(x);
    return x;   
}


template <typename T>
bool BST<T>::remove(const T& e){
    BinNodePosi<T> &x = search(e);
    if (!x){
        return false;
    }
    removeAt(x, _hot);
    BinTree<T>::_size --;
    BinTree<T>::updateHeightAbove(_hot);
    return true;
}

template <typename T>
static BinNodePosi<T> removeAt(BinNodePosi<T> &x, BinNodePosi<T> &hot){
    BinNodePosi<T> w = x; //实际被删除的节点
    BinNodePosi<T> succ = NULL;
    if(!HasLChild(*x)){ //单分支
        succ = x = x->rchild;
    }
    else if(!HasRChild(*x)){ //单分支
        succ = x = x->rchild;
    }
    else{
        w = w->success(); //此时w是被删除节点x的直接后继
        swap(x->data, w->data); //交换值，此时被删除节点x的值为原来后继的值，而后继w的值为被删除节点的值，即BST在这里短暂的失衡
        BinNodePosi<T> u = w->parent;
        ((u == x)? u->rchild: u->lchild) = succ = w->rchild;
    }
    hot = w->parent;
    if(succ) succ->parent = hot; //被删除的后继联接被删除的父亲
    //release(w->data);
    release(w);
    return succ;
}