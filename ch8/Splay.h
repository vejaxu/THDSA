#include "../ch7/BST.h"


template <typename NodePosi>
inline void attachAsLchild(NodePosi x, NodePosi y){
    x->lchild = y;
    if(y) y->parent = x;
}
template <typename NodePosi>
inline void attachAsRchild(NodePosi x, NodePosi y){
    x->rchild = y;
    if(y) y->parent = x;
}


template <typename T>
class Splay: public BST<T>{
    protected:
        BinNodePosi<T> splay(BinNodePosi<T> v);
    public:
        BinNodePosi<T>& search(const T& e); //每一次查找，都需将查找到的节点移动到树根处
        BinNodePosi<T> insert(const T& e);
        bool remove(const T& e);
};


template <typename T>
BinNodePosi<T> Splay<T>::splay(BinNodePosi<T> v){
    if(!v) return NULL;
    BinNodePosi<T> p;
    BinNodePosi<T> g; //父亲与祖父节点
    while((p == v->parent) && (g == p->parent)){
        BinNodePosi<T> gg = g->parent;
        //模仿connect34思想
        //保持中序遍历不变
        //对于zig-zag与zag-zig，与connect34一致
        //对于zig-zig与zag-zag，区别在于做完一次zig/zag后，再做一次zig/zag，则v节点可以上升两层
        if(IsLChild(*v)){
            if(IsLChild(*p)){
                attachAsLchild(g, p->rchild);
                attachAsLchild(p, v->rchild);
                attachAsRchild(p, g);
                attachAsRchild(v, p);
            }
            else{
                attachAsLchild(p, v->rchild);
                attachAsRchild(g, v->lchild);
                attachAsLchild(v, g);
                attachAsRchild(v, p);
            }
        }
        else{
            if(IsRChild(*p)){
                attachAsRchild(g, p->lchild); 
                attachAsRchild(p, v->lchild); 
                attachAsLchild(p, g);
                attachAsRchild(v, p);
            }
            else{
                attachAsRchild(p, v->lchild);
                attachAsLchild(g, v->rchild);
                attachAsRchild(v, g);
                attachAsLchild(v, p);
            }
        }
        if(!gg) v->parent = NULL;
        else{
            (g == gg->lchild) ? attachAsLchild(gg, v): attachAsRchild(gg, v); 
        }
        BinTree<T>::updateHeight(g);
        BinTree<T>::updateHeight(p);
        BinTree<T>::updateHeight(v);
    }
    if(p = v->parent){
        if(IsLChild(*v)){
            attachAsLchild(p, v->rchild);
            attachAsRchild(v, p);
        }
        else{
            attachAsRchild(p, v->lchild);
            attachAsLchild(v, p);
        }
        BinTree<T>::updateHeight(p);
        BinTree<T>::updateHeight(v);
    }
    v->parent = NULL;
    return v;
}


template <typename T>
BinNodePosi<T>& Splay<T>::search(const T& e){
    BinNodePosi<T> p = searchIn(BinTree<T>::_root, e, BST<T>::_hot = NULL);
    BinTree<T>::_root = splay(p ? p: BST<T>::_hot);
    return BinTree<T>::_root;
}


template <typename T>
BinNodePosi<T> Splay<T>::insert(const T& e){
    if(!BinTree<T>::_root){
        BinTree<T>::_size ++;
        return BinTree<T>::_root = new BinNode<T>(e);
    }
    if(e == search(e)->data){
        return BinTree<T>::_root;
    }
    BinTree<T>::_size ++;
    BinNodePosi<T> t = BinTree<T>::_root;
    if(BinTree<T>::_root->data < e){
        t->parent = BinTree<T>::_root = new BinNode<T>(e, NULL, t, t->rchild);
        if(HasRChild(*t)){
            t->rchild->parent = BinTree<T>::_root;
            t->rchild =  NULL;
        }
    }
    else{
        t->parent = BinTree<T>::_root = new BinNode<T>(e, NULL, t->lchild, t);
        if(HasRChild(*t)){
            t->lchild->parent = BinTree<T>::_root;
            t->lchild = NULL;
        }
    }
    BinTree<T>::updateHeightAbove(t);
    return BinTree<T>::_root;
}


template <typename T>
bool Splay<T>::remove(const T& e){
    if(! BinTree<T>::_root || (e != search(e)->data)){
        return false;
    }
    BinNodePosi<T> w = BinTree<T>::_root;
    if(!HasLChild(* BinTree<T>::_root)){
        BinTree<T>::_root = BinTree<T>::_root->rchild;
        if(BinTree<T>::_root){
            BinTree<T>::_root->parent = NULL;
        }
    }
    else if(! HasRChild(* BinTree<T>::_root)){
        BinTree<T>::_root = BinTree<T>::_root->lchild;
        if(BinTree<T>::_root){
            BinTree<T>::_root->parent = NULL;
        }
    }
    else{
        BinNodePosi<T> lTree = BinTree<T>::_root->lchild;
        lTree->parent = NULL;
        BinTree<T>::_root->lchild = NULL;
        BinTree<T>::_root  = BinTree<T>::_root->rchild;
        BinTree<T>::_root->parent = NULL;
        search(w->data);
        BinTree<T>::_root->lchild = lTree;
        lTree->parent = BinTree<T>::_root;
    }
    release(w->data);
    release(w);
    BinTree<T>::_size--;
    if(BinTree<T>::_root){
        BinTree<T>::updateHeight(BinTree<T>::_root);
    }
    return true;
}