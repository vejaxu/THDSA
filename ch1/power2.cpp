//O(2^n)
#include <iostream>
using namespace std;
__int64 power2BF_I(int n){
    __int64 pow = 1;
    while (0 < n--){
        pow <<= 1;
    }
    return pow;
}
int main(){
    int n = 10;
    cout << power2BF_I(n) << endl;
}