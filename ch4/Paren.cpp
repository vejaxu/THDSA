//栈的应用--栈混洗,括号匹配
#include <iostream>
#include "MyStack.h"

void paren(const char exp[], int lo, int hi){
    Stack<char> S;
    for (int i = lo; i <= hi; i ++){
        switch(exp[i]){
            case '(': case '[': case '{' : S.push(exp[i]); break;
            case ')': if((S.empty()) || ('(' != S.pop())); break;
            case ']': if((S.empty()) || ('[' != S.pop())); break;
            case '}': if((S.empty()) || ('{' != S.pop())); break;
            default: break;
        }
    }
    if(S.empty()){
        std::cout << "匹配成功" << std::endl;
    }
    else
        std::cout << "匹配不成功" << std::endl;
}


int main(){
    char s[] = {'(', '[', '{', '}', ']', ')'};
    int lo = 0;
    int hi = 5;
    paren(s, lo, hi);
}