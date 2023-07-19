//栈应用1--逆序输出-进制转换
#include <iostream>
#include "MyStack.h"


//递归版
void convertRecur(Stack<char>& S, __int64 n, int base){
    static char digit[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    if (0 < n){
        S.push(digit[n % base]);
        convertRecur(S, n/base, base);
    }
}

//迭代版
void convertIter(Stack<char>& S, __int64 n, int base){
    static char digit[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    while (0 < n){
        int remainder = (int) (n % base); //余数入栈
        S.push(digit[remainder]);
        n /= base;
    }
}

main(){
    using namespace std;
    Stack<char> S2 = Stack<char>();
    Stack<char> S16 = Stack<char>();
    __int64 n = 16;
    int base = 2;
    int base16 = 16;
    convertRecur(S2, n, base);
    convertIter(S16, n, base16);
    while(! S2.empty())
        std::cout << S2.pop();
    std::cout << std::endl;
    while(! S16.empty())
        std::cout << S16.pop();
}