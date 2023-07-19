//快速排序
//分治算法
#include "../ch2/MyVector.h"

template <typename T>
void Vector<T>::quickSort(Rank lo, Rank hi){
    if(hi - lo < 2){
        return;
    }
    Rank mi = partitionB(lo, hi-1);
    quickSort(lo, mi);
    quickSort(mi+1, hi);
}


template <typename T>
Rank Vector<T>::partitionA(Rank lo, Rank hi){ //从两端交替地向中间扫描，彼此靠拢
    swap(_elem[lo], _elem[lo + rand()%(hi - lo + 1)]);
    T pivot = _elem[lo];
    while(lo < hi){
        while((lo < hi) && (pivot <= _elem[hi])) hi--;
        _elem[lo] = _elem[hi];
        while((lo < hi) && (_elem[lo] <= pivot)) lo++;
        _elem[hi] = _elem[lo];
    }
    _elem[lo] = pivot;
    return lo;
}
//不稳定性：相同大小元素必定会被颠倒
    //假设元素小于Pivot，那么在自左向右扫描时，靠后的元素必然先被发现进而先被交换到前面的子序列
//就地算法
//子问题划分不能保证规模为原问题一半，最坏情况n^2，最好情况n*logn


template <typename T>
Rank Vector<T>::partitionB(Rank lo, Rank hi){
    swap(_elem[lo], _elem[lo + rand()%(hi - lo + 1)]);
    T pivot = _elem[lo];
    while(lo < hi){
        while(lo < hi){
            if(pivot < _elem[hi]){hi --;}
            else{_elem[lo ++] = _elem[hi]; break;}
        }
        while(lo < hi){
            if(_elem[lo] < pivot){lo ++;}
            else{_elem[hi--] = _elem[lo]; break;}
        }
    }
    _elem[lo] = pivot;
    return lo;
}


template <typename T>
Rank Vector<T>::partitionC(Rank lo, Rank hi){
    swap(_elem[lo], _elem[lo + rand()%(hi - lo + 1)]);
    T pivot = _elem[lo];
    int mi = lo; //从头开始遍历，pivot已经存储O(1)
    for(int k = lo+1; k <= hi; k++){ //lo是pivot无需比较
        if(_elem[k] < pivot){
            swap(_elem[++mi], _elem[k]);//mi是较小子数组的index
        }//暗含k是较大子数组的index
    }
    swap(_elem[lo], _elem[mi]);
    return mi;
}
