#include "MyVector.h"
#include <iostream>

template <typename T>
void swap(T& a, T& b){
    T temp = a;
    a = b;
    b = temp;
}
template <typename T>
//向量置乱算法
void permute(Vector<T>& V){
    for (int i = V.size(); i > 0; i --)
        swap(V[i - 1], V[rand() % i]); //V[i-1]与[0,i)之间任一元素交换
}


//遍历输出
template <typename T>
void traverseV(T e){
    std::cout << e << ' ';
}
template <typename T>
void output(Vector<T> V){
    V.traverse(traverseV);
    std::cout << std::endl;
}


class Visit{
    public:
        template <typename T>
        void operator()(T value){
            std::cout << value << "  ";
        }
};
class Visit_add{
    public:
        template <typename T>
        void operator()(T& value){
            value++;
            std::cout << value << "  ";
        }
};

int main(){
    Visit visit;
    Visit_add visit_add;
    Vector<int> myVector = Vector<int>();
    for (Rank r = 0; r < 10; r++)
        myVector.insert(r, rand()%20);
    std::cout << "无序向量初始化: " << std::endl;
    myVector.traverse(visit);
    std::cout << std::endl;
    myVector.traverse(visit_add);
    std::cout << std::endl;
    std::cout << "当前向量逆序对数: " << myVector.disordered() << std::endl;
    std::cout << "The Rank of 18 is: "<< myVector.find(18) << std::endl;
    std::cout << "当前向量末尾插入50,末尾元素Rank为: " << myVector.insert(50) << std::endl;
    output(myVector);
    std::cout << "当前向量末尾插入80,末尾元素Rank为: " << myVector.insert(80) << std::endl;
    output(myVector);
    std::cout << "当前向量Rank为4插入60: " << myVector.insert(4, 60) << std::endl;
    output(myVector);
    std::cout << "删除Rank为5的元素 " << myVector.remove(5) << std::endl;
    output(myVector);
    std::cout << "随机置乱向量: " << std::endl;
    permute(myVector);
    output(myVector);
    std::cout << "bubbleSort" << std::endl;
    myVector.bubbleSort(0, myVector.size());
    output(myVector);
    std::cout << "随机置乱" << std::endl;
    myVector.unsort();
    output(myVector);
    std::cout << "mergeSort" << std::endl;
    myVector.mergeSort(0, myVector.size());
    output(myVector);

    for(Rank i = 0; i < myVector.size(); i ++){
        std::cout << &myVector[i] << ' ';
    }
    return 0;
}