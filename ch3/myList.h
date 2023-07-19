#include <iostream>
#include "listNode.h"


template <typename T>
class List{
    private:
        int _size; //规模
        ListNodePosi<T> header; //头节点，哨兵节点
        ListNodePosi<T> trailer; //尾节点,哨兵节点
    
    protected:
        void init(); //列表初始化
        void copyNode(ListNodePosi<T>, int); //从位置p开始复制n项
        int clear(); //清空列表
        void merge(ListNodePosi<T>&, int, List<T>&, ListNodePosi<T>, int);
        ListNodePosi<T> selectMax(ListNodePosi<T> p, int n);

    public:
        List() {init();} //构造函数
        List(List<T> const& L); //整体复制
        List(List<T> const& L, Rank r, int n); //区间复制
        List(ListNodePosi<T> p, int n);
        ~List();

        //基本操作
        Rank size() const {return _size;}
        bool empty() const {return _size <= 0;}
        ListNodePosi<T> first() const {return header->succ;} //首节点
        ListNodePosi<T> last() const {return trailer->pred;} //末节点

        //插入
        ListNodePosi<T> insertAsFirst(T const& e); //作为首节点
        ListNodePosi<T> insertAsLast(T const& e); //作为末节点
        ListNodePosi<T> insertA(ListNodePosi<T> p, T const& e); //作为p的后继
        ListNodePosi<T> insertB(ListNodePosi<T> p, T const& e); //作为p的前驱

        //删除
        T remove(ListNodePosi<T> p); //删除合法位置p处的节点,并返回被删除节点

        //唯一化
        int deduplicate();
        //有序列表唯一化
        int uniquify();

        //排序统一接口
        void sort(ListNodePosi<T> p, int n); //区间排序
        void sort() {sort(first(), _size);} //整体排序

        //mergeSort
        void mergeSort(ListNodePosi<T> p, int n);
        void selectionSort(ListNodePosi<T> p, int n);
        void insertSort(ListNodePosi<T> p, int n);

        //查找
        ListNodePosi<T> find(T const& e, int n, ListNodePosi<T> p) const; //区间查找
        ListNodePosi<T> find(T const& e) const {
            return find(e, _size, trailer);
        }

        //有序列表查找
        ListNodePosi<T> search(T const& e, int n, ListNodePosi<T> p) const; //区间查找
        ListNodePosi<T> search(T const& e) const {
            return search(e, _size, trailer);
        }

        //遍历
        void traverse(void (*visit) (T&));

        template <typename VST>
        void traverse(VST& visit);

        //支持 寻秩访问
        T& operator[](Rank r) const;
        //小于
        bool lt(T& a, T& b);
};


//初始化
template <typename T>
void List<T>::init(){
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->succ = trailer;
    trailer->pred = header;
    header->pred = NULL;
    trailer->succ = NULL;
    _size = 0;
}


//节点复制
template <typename T>
void List<T>::copyNode(ListNodePosi<T> p, int n){
    init();
    while(n --){
        insertAsLast(p->data); //p节点作为末节点插入
        p = p->succ; //依次插入
    }
}
//基于复制的构造
template <typename T>
List<T>::List(ListNodePosi<T> p, int n){
    copyNode(p, n);
}
template <typename T>
List<T>::List(List<T> const& L){
    copyNode(L.first(), L.size());
}
template <typename T>
List<T>::List(List<T> const& L, int r, int n){
    copyNode(L[r], n);
}


//析构
template <typename T>
int List<T>::clear(){
    int oldSize = _size;
    while (0 < _size){
        remove(header->succ); //从首节点依次删除
    }
    return oldSize;
}
template <typename T>
List<T>::~List(){
    clear();
    delete header;
    delete trailer;
}


//插入
template <typename T>
ListNodePosi<T> List<T>::insertAsFirst(T const& e){ //作为首节点
    _size ++;
    return header->insertAsSucc(e);
}
template <typename T>
ListNodePosi<T> List<T>::insertAsLast(T const& e){
    _size ++;
    return trailer->insertAsPred(e);
}
template <typename T> //作为后继
ListNodePosi<T> List<T>::insertA(ListNodePosi<T> p, T const& e){
    _size ++;
    return p->insertAsSucc(e);
}
template <typename T> //作为前驱
ListNodePosi<T> List<T>::insertB(ListNodePosi<T> p, T const& e){
    _size ++;
    return p->insertAsPred(e);
}
template <typename T>
ListNodePosi<T> ListNode<T>::insertAsSucc(T const& e){
    ListNodePosi<T> x = new ListNode(e, this, succ);
    succ->pred = x;
    succ = x;
    return x;
}
template <typename T>
ListNodePosi<T> ListNode<T>::insertAsPred(T const& e){
    ListNodePosi<T> x = new ListNode(e, pred, this);
    pred->succ = x; //当前节点前驱的后继为新节点
    pred = x; //当前节点的前驱变为新节点
    return x;
}


//删除
template <typename T>
T List<T>::remove(ListNodePosi<T> p){
    T e = p->data;
    p->pred->succ = p->succ; //前驱的后继为当前的后继 
    p->succ->pred = p->pred; //后继的前驱为当前的前驱
    delete p; _size --;
    return e;
}


//唯一化
template <typename T>
int List<T>::deduplicate(){
    if (_size < 2)
        return 0;
    int oldSize = _size;
    ListNodePosi<T> p = header;
    Rank r = 0;
    while(trailer != (p = p->succ)){
        ListNodePosi<T> q = find(p->data, r, p); //寻找当前节点之前是否有重复的
        q ? remove(q) : r++;
/*         if (q)
            remove(q);
        else
            r++; */
    }
    return oldSize - _size;
}
//有序列表唯一化
template <typename T>
int List<T>::uniquify(){
    if (_size < 2)
        return 0;
    int oldSize = _size;
    ListNodePosi<T> p = first();
/*     ListNodePosi<T> q;
    while(trailer != (q = p->succ)){
        if (p->data != q->data)
            p = q;
        else
            remove(q);
    } */
    ListNodePosi<T> q = p->succ;
    while(q != trailer){
        if (q->data != p->data){
            p = q;
            q = p->succ;
        }
        else{
            remove(q);
            q = p->succ;
        }
    }
    return oldSize - _size;
}


//排序,统一接口
/* template <typename T>
void List<T>::sort(ListNodePosi<T> p, int n){
    switch ((rand()% 3)){
        case 1: mergeSort(ListNodePosi<T> p, int n); break;
        case 2: selectionSort(ListNodePosi<T> p, int n); break;
        case 3: insertSort(ListNodePosi<T> p, int n); break;
    }
} */


//插入排序,poker card
//就地算法
template <typename T>
void List<T>::insertSort(ListNodePosi<T> p, int n){
    for (int r = 0; r < n; r ++){ //可以看作是有序部分的长度
        insertA(search(p->data, r, p), p->data); //p总是无序部分的首节点,首先查找有序序列中不大于P的最大的节点(稳定算法),然后将p的值插入到最大节点的后面,insert会产生一个新节点
        p = p->succ;
        remove(p->pred); //所以要删除p节点
    }
}


//选择排序,起始于p的连续n个元素
//从前缀中选择最大的插入到后缀作为最小的
//起泡排序与选择排序原理相同,但是起泡排序效率低 
template <typename T>
void List<T>::selectionSort(ListNodePosi<T> p, int n){
    ListNodePosi<T>  head = p->pred; //head是p的前驱节点
    ListNodePosi<T> tail = p; //tailer是p的后继节点,即从p开始的第n个节点
    for (int i = 0; i < n; i ++){
        tail = tail->succ;
    }
    while(1 < n){
        ListNodePosi<T> max = selectMax(head->succ, n); //寻找最大节点
        insertB(tail, remove(max)); //将找到的最大节点插入到tailer的前驱,O(1),相对于bubblesort节点的移动只需要两个节点之间的移动
        //insert与remove使用到动态内存分配new delete,其耗时是基本操作的百倍,需要尽可能少的使用
        tail = tail->pred; //并将tailer指向当前的最大节点
        n --;
    }
}
template <typename T>
ListNodePosi<T> List<T>::selectMax(ListNodePosi<T> p, int n){
    ListNodePosi<T> max = p; //最大节点
    for (ListNodePosi<T> cur = p; 1 < n; n --){
        if (! lt((cur = cur->succ)->data, max->data)) //当前节点不小于最大节点,更新,那么同等大小情况下会选择靠后的元素,则是稳定排序
            max = cur;
    }
    return max;
}
//'<''='操作符重载
template <typename T>
bool List<T>::lt(T& a, T& b){
    return a < b;
}


//mergeSort
template <typename T>
void List<T>::merge(ListNodePosi<T>& p, int n, List<T>& L, ListNodePosi<T> q, int m){
    ListNodePosi<T> pp = p->pred;
    while (0 < m){
        if ((0 < n) && (p->data <= q->data)){
            if (q == (p = p->succ))
                break;
            n --;
        }
        else{
            insertB(p, L.remove((q = q->succ)->pred));
            m --;
        }
    }
    p = pp->succ;
}
template <typename T>
void List<T>::mergeSort(ListNodePosi<T> p, int n){
    if (n < 2)
        return;
    int m = n >> 1;
    ListNodePosi<T> q = p;
    for (int i = 0; i < m; i ++){
         q = q->succ;
    }
    mergeSort(p, m);
    mergeSort(q, n-m);
    merge(p, m, *this, q, n-m); //归并
}


//无序列表区间查找
template <typename T>
ListNodePosi<T> List<T>::find(T const& e, int n, ListNodePosi<T> p) const { //节点p的n个前驱中,找到等于e的最后一个
/*     while (0 < n--)
        if (e == (p = p->pred)->data) return p; */
    while (0 < n--){
        p = p->pred;
        if (e == p->data)
            return p;
    }
    return NULL;
}


//有序列表区间查找,p节点往n个真前驱
template <typename T>
ListNodePosi<T> List<T>::search(T const& e, int n, ListNodePosi<T> p) const {
    while(0 <= n){
        p = p->pred;
        if (p->data > e){
            n --;
            continue;
        }
        break;
    }
    return p;
}


//遍历
template <typename T>
void List<T>::traverse(void (*visit) (T&)){
    for (ListNodePosi<T> p = header->succ; p != trailer; p = p->succ)
        visit(p->data);
}
template <typename T>
template <typename VST>
void List<T>::traverse(VST& visit){
    for (ListNodePosi<T> p = header->succ; p != trailer; p = p->succ){
        visit(p->data);
    }
}


//寻秩访问
template <typename T>
T& List<T>::operator[](Rank r) const{
    ListNodePosi<T> p = first(); //从首节点出发
    while(0 < r --)
        p = p->succ;
    return p->data;
}