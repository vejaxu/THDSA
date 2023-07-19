typedef int Rank;
template <typename T> struct ListNode;
template <typename T> using ListNodePosi = ListNode<T>*;


template <typename T> struct ListNode{
    T data;
    ListNodePosi<T> pred; //前驱
    ListNodePosi<T> succ; //后继

    ListNode(){}; //构造函数
    ListNode(T e, ListNodePosi<T> p = NULL, ListNodePosi<T> s = NULL)
        : data(e), pred(p), succ(s) {};
    ListNodePosi<T> insertAsPred(T const& e); //紧靠当前节点之前插入新节点
    ListNodePosi<T> insertAsSucc(T const& e); //紧靠当前节点之后插入新节点
};