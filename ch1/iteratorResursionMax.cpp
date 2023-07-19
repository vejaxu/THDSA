#include <iostream>
using namespace std;

void max(int A[], int lo, int hi, int& x1, int& x2){
    if (lo + 2 == hi){
        if (A[0] < A[1]){
            x1 = 1;
            x2 = 0;
        }
        else{
            x1 = 0;
            x2 = 1;
        }
    }
    if (lo + 3 == hi){
        return;
    }
    int mi = (lo + hi) / 2;

    int x1L, x2L;
    max(A, lo, mi, x1L, x2L); //segmention fault
    int x1R, x2R;
    max(A, mi, hi, x1R, x2R);
    if (A[x1R] > A[x1L]){
        x1 = x1R;
        x2 = (A[x2R] > A[x1L]) ? x2R: x1L;
    }
    else{
        x1 = x1L;
        x2 = (A[x2L] > A[x1R]) ? x2L: x1R;
    }
}

int main(){
    int A[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int lo = 0;
    int hi = 8;
    int x1;
    int x2;
    max(A, lo, hi, x1, x2);
    cout << A[x1] << endl;
    cout << A[x2] << endl;
    return 0;
}