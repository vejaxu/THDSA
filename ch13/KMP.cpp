#include <string.h>
#include <iostream>


int* buildNext(char* P){
    size_t m = strlen(P), j = 0;
    int* N = new int[m];
    int t = N[0] = - 1;
    while(j < m - 1){
        if(0 > t || P[j] == P[t]){
            j ++;
            t ++;
            //N[j] = t;
            N[j] = (P[j] != P[t] ? t: N[t]);
        }else{
            t = N[t];
        }
    }
    return N;
}
int match(char* P, char* T){
    int* next = buildNext(P);
    int n = (int) strlen(T), i = 0;
    int m = (int) strlen(P), j = 0;

    while(i < n && j < m){
        if(0 > j || T[i] == P[j]){
            i ++;
            j ++;
        }else{
            j = next[j];
        }
    }

    delete [] next;

    return (i - j);
}


int main(){
/*     char T[] = {'a', 'a', 'd', 'a', 'a', 'b', 'a', 'a', 'f'};
    char P[] = {'a', 'a', 'b', 'a', 'a', 'f'};

    int result = match(P, T);

    std::cout << result << std::endl; */

    char X[] = {'0', '0', '0', '1', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0'};
    char Y[] = {'0', '0', '0', '0', '0'};

    int result1 = match(Y, X);

    std::cout << result1 << std::endl;

    return 0;

}