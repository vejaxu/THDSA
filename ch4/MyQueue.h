#include "../ch3/myList.h"
template <typename T>
class Queue: public List<T>{
    public:
        void enqueue(T const& e){List<T>::insertAsLast(e);} //入队
        T dequeue(){return List<T>::remove(List<T>::first());} //出队
        T& front(){return List<T>::first()->data;} //队首
        //可以将列表的首末节点颠倒
};