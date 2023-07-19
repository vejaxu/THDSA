//数组倒置,多递归基递归版
#include <iostream>
using namespace std;
void reverse(int* A, int lo, int hi){
    if (lo < hi){
        swap(A[lo], A[hi]);
        reverse(A, lo+1, hi-1);
    }
}
int main(){
    int A[5] = {1, 2, 3, 4, 5};
    reverse(A, 0, 4);
    for(int i = 0; i < 5; i ++){
        cout << A[i] << " ";
    }
    cout << endl;
    return 0;
}