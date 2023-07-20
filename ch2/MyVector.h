#include <iostream>
#include "Fib.h"


typedef int Rank;
#define DEFAULT_CAPACITY 10


template <typename T>
class Vector{
    protected:
        Rank _size; //当前规模
        int _capacity; //容量
        T* _elem; //数据区

        //向量扩容
        void expand();
        //向量缩容
        void shrink();

        //vecotr复制函数
        void copyfrom(T const* A, Rank lo, Rank hi);

    public:
        Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0){
            _elem = new T[_capacity = c];
            for (_size = 0; _size < s; _elem[_size++] = v);
        }

        //数组整体复制
        Vector(T const* A, Rank n){
            copyfrom(A, 0, n);
        }

        //区间复制
        Vector(T const* A, Rank lo, Rank hi){
            copyfrom(A, lo, hi);
        }

        //向量整体复制
        Vector(Vector<T> const& V){
            copyfrom(V._elem, 0, V._size);
        }

        //向量区间复制
        Vector(Vector<T> const& V, Rank lo, Rank hi){
            copyfrom(V._elem, lo, hi);
        }

        //析构函数
        ~Vector(){
            delete[] _elem;
        }

        //交换
        void swap(T& a, T& b);
        //返回向量规模
        Rank size() const {return _size;}
        //向量最大容量
        int capacity() const {return _capacity;}
        //判空
        bool empty() const {return !_size;}
        //判断是否排序
        int disordered() const;

        //插入
        Rank insert(Rank r, T const& e);
        //默认作为尾元素插入
        Rank insert(T const& e) {return insert(_size, e);}

        //删除Rank在[lo,hi)的元素
        int remove(Rank lo, Rank hi);
        //删除Rank为r的元素
        T remove(Rank r);

        //无序向量去重
        int deduplicate();
        //有序向量去重,低效版
        int uniquify_low();
        //有序向量去重,高效版
        int uniquify();

        //区间置乱,[lo,hi)
        void unsort(Rank lo, Rank hi);
        //整体置乱
        void unsort(){unsort(0, _size);}

        //区间排序
        void sort(Rank lo, Rank hi);
        //整体排序
        void sort() {sort(0, _size);}
        //排序
        bool bubble(Rank lo, Rank hi);
        Rank bubbleB(Rank lo, Rank hi);
        void bubbleSort(Rank lo, Rank hi); //起泡排序,稳定算法
        void bubbleSortB(Rank lo, Rank hi);
        void merge(Rank lo, Rank mi, Rank hi);
        void mergeSort(Rank lo, Rank hi); //归并排序
        Rank max(Rank lo, Rank hi);
        void selectionSort(Rank lo, Rank hi);
        Rank partitionA(Rank lo, Rank hi); //轴点构造
        Rank partitionB(Rank lo, Rank hi);
        Rank partitionC(Rank lo, Rank hi);
        void quickSort(Rank lo, Rank hi);
        void heapSort(Rank lo, Rank hi);

        //无序向量区间查找
        Rank find(T const& e, Rank lo, Rank hi) const;
        //无序向量整体查找
        Rank find(T const& e) const {return find(e, 0, _size);}
        //有序向量区间查找
        Rank search(T const& e,  Rank lo, Rank hi) const;
        //有序向量整体查找;
        Rank search(T const& e) const {return (0 >= _size) ? -1 : search(e, 0, _size);}

        //搜索
        //binSearch,二分搜索版本A,分割点为中间分割点
        Rank binSearchA(T* A, T const& e, Rank lo, Rank hi) const;
        Rank binSearchB(T* A, T const& e, Rank lo, Rank hi) const;
        Rank binSearchC(T* A, T const& e, Rank lo, Rank hi) const;
        Rank fibSearch(T* A, T const& e, Rank lo, Rank hi) const;

        //运算符'='重载,拷贝构造，返回向量
        Vector<T>& operator=(Vector<T> const& );
        //运算符'[]'重载,下标访问,返回元素
        T& operator[](Rank r) const;

        //遍历操作
        void traverse(void(*visit) (T&)); //只读或局部性修改

        template<typename VST>
        void traverse(VST& visit); //使用函数对象，可全局性修改
};


//基于复制的构造方法
template <typename T>
inline void Vector<T>::copyfrom(T const* A, Rank lo, Rank hi){
    _elem = new T[_capacity = 2 * (hi - lo)];
    _size = 0;
    while (lo < hi){ //[lo,hi)逐一复制
        _elem[_size ++] = A[lo ++];
    }
}


//扩容
template <typename T>
inline void Vector<T>::expand(){
    if (_size < _capacity)
        return ; 
    if (_capacity < DEFAULT_CAPACITY)
        _capacity = DEFAULT_CAPACITY;
    T* oldElem = _elem;
    _elem = new T[_capacity <<= 1];
    for (int i = 0; i < _size; i ++)
        _elem[i] = oldElem[i];
    delete[] oldElem;
}
//当_size << _capacity时，向量缩容
template <typename T>
inline void Vector<T>::shrink(){
    if (_capacity < DEFAULT_CAPACITY << 1) return;
    if (_size << 2 > _capacity) return; //25%临界值
    T* oldElem = _elem;
    _elem = new T[_capacity >> 1]; //容量减半
    for (int i = 0; i < _size; i ++)
        _elem[i] = oldElem[i];
    delete[] oldElem;
}


//插入元素
template <typename T>
inline Rank Vector<T>::insert(Rank r, T const& e){
    expand(); //插入时检查是否上溢需要扩容
    for (int i = _size; i > r; i --)
        _elem[i] = _elem[i-1]; //自后向前,后继元素顺次后移
    _elem[r] = e;
    _size ++;
    return r;
}


//删除Rank在[lo,hi)的元素
template <typename T>
inline int Vector<T>::remove(Rank lo, Rank hi){
    if (lo == hi) return 0;
    while (hi < _size) _elem[lo ++] = _elem[hi ++];
    _size = lo; //更新规模，直接丢弃[lo,_size=hi)区间
    shrink();
    return hi-lo;
}
//删除Rank为r的元素
template <typename T>
inline T Vector<T>::remove(Rank r){
    T e = _elem[r];
    remove(r, r+1);
    return e;
}


//无序向量去重
template <typename T>
inline int Vector<T>::deduplicate(){
    int oldSize = _size; //记录原规模
    Rank i = 1;
/*     while(i < _size)
        (find(_elem[i], 0, i) < 0) ? //寻找前缀是否有雷同者
            i++ : remove(i); //没有则向后寻找，有的话则删除当前元素
    return oldSize - _size; */
    while(i < _size){
        Rank t = find(_elem[i], 0, i);
        if(t < 0){
            i ++;
        }else{
            remove(i);
        }
    }
    return oldSize-_size;
}
//有序向量去重,低效版
template <typename T>
inline int Vector<T>::uniquify_low(){
    int oldSize = _size;
    int i = 1;
    while(i < _size){ //从前向后,逐一对比各相邻元素
        _elem[i - 1] == _elem[i] ? remove(i) : i ++;
    }
    return oldSize - _size;
}
//有序向量去重,高效版
template <typename T>
inline int Vector<T>::uniquify(){
    Rank i = 0, j = 0;
    while(++j < _size){
        if (_elem[i] != _elem[j]){
            _elem[++i] = _elem[j];
        } //[0, i)的元素为去重后
    }
    _size = ++ i;
    shrink();
    return j - i;
}


//交换
template <typename T>
inline void Vector<T>::swap(T& a, T& b){
    T temp = a;
    a = b;
    b = temp;
}


//区间置乱
template <typename T>
inline void Vector<T>::unsort(Rank lo, Rank hi){
    T* V = _elem + lo; //将子向量[lo,hi)视作一个新向量[0, hi-lo)
    for (Rank i = hi - lo; i > 0; i --){
        swap(V[i-1], V[rand() % i]); //V[i-1]与[0,i)区间任意元素交换
    }
}


//无序向量区间查找
template <typename T>
inline Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const{
    //从后向前，顺序查找，因为当找到多个目标时，取Rank最大者所以从后向前查找
/*     while ((lo < hi--) && (e != _elem[hi]));
    return hi; */
    while (lo < hi){
        if (e != _elem[hi])
            hi --;
        else
            return hi;
    }
    return -1;
}
//有序向量区间查找
template <typename T>
inline Rank Vector<T>::search(T const& e, Rank lo, Rank hi) const {
    return binSearchC(_elem, e, lo, hi);
/*     int k = rand() % 2;
    if (k)
        return binSearchC(_elem, e, lo, hi);
    else
        return fibSearch(_elem, e, lo, hi); */
/*     return (rand() % 2) ? 
            binSearchC(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi); //随机使用两种之一的方法进行搜索 */
}
//binSearch,二分搜索版本A,分割点为中间分割点
template <typename T>
inline Rank Vector<T>::binSearchA(T* A, T const& e, Rank lo, Rank hi) const {
    while (lo < hi){
        Rank mi = (lo + hi) >> 1;
        if (e < A[mi])
            hi = mi;
        else if (A[mi] < e) //都用<,良好的编程习惯
            lo = mi + 1;
        else
            return mi;
    }
    return -1;
}
//二分搜索版本B
template <typename T>
inline Rank Vector<T>::binSearchB(T* A, T const& e, Rank lo, Rank hi) const {
    while (1 < hi - lo){
        Rank mi = (hi - lo) >> 1;
        (e < A[mi]) ? hi = mi : lo = mi;
    }
    return (e == A[lo] ? lo : -1);
}
//二分搜索版本C
template <typename T>
inline Rank Vector<T>::binSearchC(T* A, T const& e, Rank lo, Rank hi) const {
    while (lo < hi){
        Rank mi = (lo + hi) >> 1;
        (e < A[mi]) ? hi = mi : lo = mi + 1;
    }
    return --lo;
}
//fibSearch,版本A,分割点为黄金分割点
template <typename T>
inline Rank Vector<T>::fibSearch(T* A, T const& e, Rank lo, Rank hi) const {
    Fib fib(hi - lo);
    while (lo < hi){
        while (hi - lo < fib.get()) fib.prev();
        Rank mi = lo + fib.get() - 1;
        if (e < A[mi]) hi = mi;
        else if (A[mi] < e) lo = mi + 1;
        else return mi;
    }
    return -1;
}


//判断向量是否有序
template <typename T>
inline int Vector<T>::disordered() const{
    int n = 0; //计数器
    for (int i = 1; i < _size; i ++){
        if (_elem[i -1] > _elem[i])
            n ++;
    }
    return n;
}


//区间排序
template <typename T>
inline void Vector<T>::sort(Rank lo, Rank hi){
    switch (rand() % 5){
        case 1: bubbleSort(lo, hi); break;
        case 2: selectionSort(lo, hi); break;
        case 3: mergeSort(lo, hi); break;
        case 4: heapSort(lo, hi); break;
        default: quickSort(lo, hi); break; 
    }
}
//bubbleSort
template <typename T>
inline void Vector<T>::bubbleSort(Rank lo, Rank hi){
    while(!bubble(lo, hi--)); //逐趟扫描
}
template <typename T>
inline bool Vector<T>::bubble(Rank lo, Rank hi){
    bool sorted = true;
    while (++lo < hi){
        if (_elem[lo - 1] > _elem[lo]){
            sorted = false;
            swap(_elem[lo - 1], _elem[lo]);
        }
    }
    return sorted;
}
//实际上，每一趟扫描，都会多余扫描后面已经排序的序列
template <typename T>
inline Rank Vector<T>::bubbleB(Rank lo, Rank hi){
    Rank last = lo;
    while(++lo < hi){
        if(_elem[lo-1] > _elem[lo]){ //严格大于，因此stable
            last = lo; //记录最后一次发生交换的位置，则last后面的元素无需扫描
            swap(_elem[lo-1], _elem[lo]);
        }
    }
    return last;
}
template <typename T>   
void Vector<T>::bubbleSortB(Rank lo, Rank hi){
    while(lo < (hi = bubbleB(lo, hi))); //每一趟扫描长度都递减
}


//mergeSort
template <typename T>
inline void Vector<T>::mergeSort(Rank lo, Rank hi){
    if (hi - lo < 2) return;
    int mi = (lo + hi) / 2; //单元素区间自然有序,否则继续进行
    mergeSort(lo, mi);
    mergeSort(mi, hi);
    merge(lo, mi, hi); //归并
}
//有序向量二路归并
template <typename T>
inline void Vector<T>::merge(Rank lo, Rank mi, Rank hi){
    T* A = _elem + lo; //向量依然是原向量,只不过我们用新的区间形式来表示,即用A指向lo的起点
    int lb = mi - lo;
    T* B = new T[mi - lo];
    /* for (Rank i = 0; i < lb; B[i] = A[i ++]); */
    for (Rank i = 0; i < lb; i ++)
        B[i] = A[i];
    int lc = hi - mi; //后子向量[0, lc)=_elem[mi,hi)
    T* C = _elem + mi; //C不需要另辟空间,与A类似
    for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc); ){
        if ((j < lb) && (! (k < lc) || (B[j] <= C[k]))) A[i ++] = B[j ++]; //要么C为空,要么C>B,语法采用短路求值
        if ((k < lc) && (! (j < lb) || (C[k] < B[j]))) A[i ++] = C[k ++]; //同理
    }
    delete[] B;
}


//向量赋值'='运算符重载
template <typename T> 
inline Vector<T>& Vector <T>::operator=(Vector <T> const& V){
    if (_elem) delete[] _elem;
    copyfrom(V._elem, 0, V.size());
    return *this;
}
//元素访问'[]'运算符重载
template <typename T>
inline T& Vector<T>::operator[](Rank r) const{
    return _elem[r];
}
//'<''='操作符重载
template <typename T>
static bool lt(T* a, T* b) {return lt(*a, *b);}
template <typename T>
static bool lt(T& a, T& b) {return a < b;}
template <typename T>
static bool eq(T* a, T* b) {return eq(*a, *b);}
template <typename T>
static bool eq(T& a, T& b) {return eq(a == b);}


//遍历,借助指针
template <typename T>
inline void Vector<T>::traverse(void(*visit) (T&)){
    for (int i = 0; i < _size; i ++)
        visit(_elem[i]);
}


//遍历,借助函数对象机制
template <typename T>
template <typename VST>
inline void Vector<T>::traverse(VST& visit){
    for (int i = 0; i < _size; i ++)
        visit(_elem[i]);
}