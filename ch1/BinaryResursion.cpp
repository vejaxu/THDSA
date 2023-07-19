#include <iostream>
using namespace std;

int sum(int A[], int lo, int hi){
    if (lo == hi)
        return A[lo];
    int mi = (lo + hi) >> 1;
    return sum(A, lo, mi) + sum(A, mi+1, hi);
}

int main(){
    int A[] = {1, 2, 3, 4, 10};
    int lo = 0;
    int hi = 4;
    cout << sum(A, lo, hi);
    return 0;

}