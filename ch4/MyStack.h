#include "../ch2/MyVector.h"


//子类调用父类函数需要::
template <typename T>
class Stack: public Vector<T>{
    public:
        void push(T const& e) {Vector<T>::insert(Vector<T>::size(), e);};
        T pop() {return Vector<T>::remove(Vector<T>::size() - 1);}
        T& top() {return (*this)[Vector<T>::size() - 1];}
};