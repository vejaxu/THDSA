//O(logn)
#include <iostream>
using namespace std;
int countOnes(unsigned int n){
    int ones = 0;
    while (n > 0){
        ones += (1 & n);
        n >> 1;
    }
    return ones;
}

int main(){
    unsigned int n = 110111001;
    cout << countOnes(n) << endl;
    return 0;
}