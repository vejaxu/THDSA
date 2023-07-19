#include <iostream>
using namespace std;
void bubblesort(int A[], int n){
    bool sorted = false;
    while (! sorted){
        sorted = true;
        for (int i = 1; i < n; i ++){
            if (A[i-1] > A[i]){
                swap(A[i-1], A[i]);
                sorted = false;
            }
        }
    n --;
    }
}

int main(){
    int A[] = {4, 2, 5, 6, 8, 1, 0};
    bubblesort(A, 7);
    for(int i = 0; i < 7; i ++){
        cout << A[i] << ' ';
    }
    cout << endl;
    return 0;
}