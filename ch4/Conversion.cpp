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
    int base;
    std::cout << "input the base: ";
    std::cin >> base; std::cout << std::endl;
    __int64 n;
    std::cout << "input the number: ";
    std::cin >> n; std::cout << std::endl;
    Stack<char> S = Stack<char>();
    convertIter(S, n, base);
    while(! S.empty()){
        std::cout << S.pop();
    }
}