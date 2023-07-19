//选取selection
//众数与中位数

template <typename T>
bool majEleCheck(Vector<T> A, T maj);
template <typename T>
//频繁数
T majEleCandidate(Vector<T> A);


//如果是众数，则一定是中位数
template <typename T>
bool majority(Vector<T> A, T& maj){
    maj = majEleCandidate(A); //先选一个候选者
    return majEleCheck(A, maj);
}


template <typename T>
bool majEleCheck(Vector<T> A, T maj){
    int occurrence = 0;
    for(int i = 0; i < A.size(); i++){
        if(A[i] == maj){occurrence++;}
    }
    return 2 * occurrence > A.size();
}


template <typename T>
T majEleCandidate(Vector<T> A){
    T maj;
    for(int c = 0, i = 0; i < A.size(); i++){
        if(0 == c){ //每当c归零，意味着前缀p可以剪除
            maj = A[i];
            c = 1;
        }
        else{
            maj == A[i] ? c++ : c --;
        }
    }
    return maj;
}


template <typename T>
void quickSelect(Vector<T>& A, Rank k){
    for(Rank lo = 0, hi = A.size()-1; lo < hi;){
        Rank i = lo, j = hi;
        T pivot = A[lo];
        while(i < j){
            while((i < j) && (pivot <= A[j])){
                j --;
                A[i] = A[j];
            }
            while((i < j) && (A[i] <= pivot)){
                i ++;
                A[j] = A[i];
            }
        }
        A[i] = pivot;
        if(k <= i) hi = i-1;
        if(i <= k) lo = i + 1;
    }
}