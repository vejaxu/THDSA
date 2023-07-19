#include <iostream>

#include "myList.h"
using namespace std;


template <typename T>
void traverseL(T e){
    std::cout << e << ' ';
}


//遍历打印
template <typename T>
void output(List<T> L){
    std::cout << "current List size = " << L.size() << std::endl;
    L.traverse(traverseL);
    std::cout << std::endl;
}


int main(){
    using namespace std;
    List<int> myList = List<int>();
    for (int i = 0; i < 20; i ++){
        myList.insertAsLast(rand()% 20);
    }
    output(myList);

    List<int> sortList = List<int>(myList);
    cout << "有序列表: " << endl;
    output(sortList);

    cout << "首节点插入20: " << endl;
    myList.insertAsFirst(20);
    output(myList);

    cout << "末节点插入21: " << endl;
    myList.insertAsLast(21);
    output(myList);

    cout << "查找值为0的节点: " << endl;
    cout << myList.find(0) << " = " << myList.find(0)->data << endl;
    output(myList);

    cout << "删除值为0的节点: " << endl;
    myList.remove(myList.find(0));
    output(myList);

    myList.deduplicate(); //取rank最大的一项保留
    output(myList);

    cout << endl;
    cout << "sortList: " << endl;

    cout << "有序列表排序: " << endl;
    sortList.selectionSort(sortList.first(), sortList.size());
    output(sortList);


    cout << "有序列表末尾插入19: " << endl;
    sortList.insertAsLast(19);
    output(sortList);

    cout << "有序列表唯一化: " << endl;
    sortList.uniquify();
    output(sortList);

    cout << "有序列表查找0: " << endl;
    cout << "查找到的节点的值为: " << sortList.search(0)->data << endl;
    output(sortList);

/*     for(int i = 0; i < myList.size(); i ++){
        cout << &myList[i] << ' ';
        cout << sizeof(&myList[i]) << endl;
    }

    cout << sizeof(int) << endl;

    for(int i = 0; i < sortList.size(); i ++){
        cout << &sortList[i] << ' ';
        cout << sizeof(&sortList[i]) << endl;
    } */
}