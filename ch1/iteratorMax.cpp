#include <iostream>
using namespace std;

void max(int A[], int lo, int hi, int& x1, int& x2){
    if (A[x1 = lo] < A[x2 = lo + 1])
        swap(x1, x2);
    for (int i = lo + 2; i < hi; i ++){
        if (A[x2] < A[i]){
            if (A[x1] < A[x2 = i]){
                swap(x1, x2);
            }            
        }
    }

}

int main(){
    int A[] = {1, 2, 3, 4, 5, 6, 7};
    int lo = 0;
    int hi = 7;
    int x1, x2 = 0;
    max(A, lo, hi, x1, x2);
    cout << A[x1] << endl;
    cout << A[x2] << endl;
    return 0;
}