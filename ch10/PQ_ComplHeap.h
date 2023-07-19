#include "PriorityQueue.h"
#include "../ch2/MyVector.h"

#define InHeap(n, i) (((-1) < (i)) && ((i) < (n))) //判断PQ[i]是否合法
#define Parent(i) ((i-1) >> 1) //PQ[i]的父节点
#define LastInternal(n) Parent(n-1) //末节点的父亲
#define LChild(i) (1 + ((i) << 1))
#define RChild(i) ((1 + (i)) << 1)
#define ParentValid(i) (0 < i) //判断是否有父亲
#define LChildValid(n, i) InHeap(n, LChild(i)) //判断PQ[i]是否有左孩子
#define RChildValid(n, i) InHeap(n, RChild(i))
#define Bigger(PQ, i, j) (lt(PQ[i], PQ[j]) ? j: i)
#define ProperParent(PQ, n, i) (RChildValid(n, i) ? Bigger(PQ, Bigger(PQ, i, LChild(i)), RChild(i)): (LChildValid(n, i) ? Bigger(PQ, i, LChild(i)): i)) //相等时父节点有限，如此可以避免不必要的交换


template <typename T>
class PQ_ComplHeap: public PQ<T>, public Vector<T>{ //接口标准，物理存储
    protected:
        Rank percolateDown (Rank n, Rank i);
        Rank percolateDown_improve2 (Rank n, Rank i);
        Rank percolataUp(Rank i);
        Rank percolataUp_improve2(Rank i);
        void heapify(Rank n); //flody建堆算法

    public:
        PQ_ComplHeap(){}
        PQ_ComplHeap(T* A, Rank n){Vector<T>::copyfrom(A, 0, n); heapify(n);} //以任意数组A为蓝本建堆
        void insert(T);
        T getMax();
        T delMax();
};


template <typename T>
T PQ_ComplHeap<T>::getMax(){
    return Vector<T>::_elem[0];
}


template <typename T> //O(logn)
void PQ_ComplHeap<T>::insert(T e){
    Vector<T>::insert(e);
    percolataUp(Vector<T>::_size - 1); //只要e于其父节点违反堆序性，就不断地交换位置,至多交换O(logn)c次，即树高
}
template <typename T>
Rank PQ_ComplHeap<T>::percolataUp(Rank i){ //从底部开始向上爬
    while(ParentValid(i)){
        Rank j = Parent(i);
        if (lt(Vector<T>::_elem[i], Vector<T>::_elem[j])) break;
        Vector<T>::swap(Vector<T>::_elem[i], Vector<T>::_elem[j]); //需要三次赋值操作,可以先将这个值备份，只是不断地下移父节点
        i = j; //上升一层
    }
    return i;
}
template <typename T>
Rank PQ_ComplHeap<T>::percolataUp_improve2(Rank i){ //仅需最后到达最后一步时赋值，避免重复交换赋值
    T temp;
    while(ParentValid(i)){
        Rank j = Parent(i);
        if (lt(Vector<T>::_elem[i], Vector<T>::_elem[j])) break;
        temp = Vector<T>::_elem[j];
        i = j; //上升一层
    }
    Vector<T>::_elem[i] = temp;
    return i;
}


template <typename T>
T PQ_ComplHeap<T>::delMax(){
    T maxElem = Vector<T>::_elem[0];
    Vector<T>::_elem[0] = Vector<T>::_elem[--Vector<T>::_size];
    percolateDown(Vector<T>::_size, 0);
    return maxElem;
}
template <typename T>
Rank PQ_ComplHeap<T>::percolateDown(Rank n, Rank i){ //从顶部向下走
    Rank j;
    while(i != (j = ProperParent(Vector<T>::_elem, n, i))){
        Vector<T>::swap(Vector<T>::_elem[i], Vector<T>::_elem[j]);
        i = j;
    }
    return i;
}
template <typename T>
Rank PQ_ComplHeap<T>::percolateDown_improve2(Rank n, Rank i){ //从顶部向下走
    Rank j;
    T temp;
    while(i != (j = ProperParent(Vector<T>::_elem, n, i))){
        temp = Vector<T>::_elem[j];
        i = j;
    }
    Vector<T>::_elem[i] = temp;
    return i;
}


template <typename T>
void PQ_ComplHeap<T>::heapify(Rank n){ //逐层合并，规模不断增加
    for (int i = LastInternal(n); i >= 0; i --){ //从最后一个父节点开始不断完善小子树
        percolateDown(n, i);
    }
}
//自上而下的上滤：使用深度作为指标，越靠近底层节点越多，深度越大
//自下而上的下滤：使用高度作为指标，越靠近底层节点越多，高度越小
//所以建堆时采用自下而上的下滤


template <typename T>
void Vector<T>::heapSort(Rank lo, Rank hi){
    PQ_ComplHeap<T> H(_elem+lo, hi - lo);
    while(!H.empty()){
        _elem[--hi] = H.delMax();
    }
}