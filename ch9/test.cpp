#include <iostream>

int main(){
    char c = '5';
    int num = (int) c;
    int num2 = c - '0';

    int a = 0x1011;
    int b = 0x0100;
    a = a ^ b;
    b = b ^ a;
    a = a ^ b;
    int i = 3;
    i = i << 2;
    i = i << 1;
    std::cout << num << std::endl;
    std::cout << num2 << std::endl;
    std::cout << a << " , " << b << std::endl;
    std::cout << i << std::endl;
    return 0;
}