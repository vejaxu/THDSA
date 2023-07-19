//线性递归
//数组求和
#include <iostream>
using namespace std;
int sum(int A[], int n){
    return (n < 1) ? 0: sum(A, n-1) + A[n-1];
}

int main(){
    int A[] = {1, 2, 3, 4, 5};
    cout << sum(A, 5) << endl;
    return 0;
}