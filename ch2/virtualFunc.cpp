#include <iostream>
//基类虚函数使得基类实例在调用函数时可以调用子类函数
//纯虚函数则是规定一个规范的接口
class A{
    public:
        virtual void foo(){
            std::cout << "A::foo() is called." << std::endl;
        }
};
class B: public A{
    public:
        void foo(){
            std::cout << "B::foo() is called." << std::endl;
        }
};
int main(){
    A* a = new B();
    a->foo();
    return 0;
}