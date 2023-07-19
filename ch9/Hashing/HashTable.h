#include "../Dictionary.h"
#include "../Entry.h"
#include "Bitmap/Bitmap.h"

template <typename K, typename V>
class HashTable: public Dictionary<K, V>{
    private:
        Entry<K, V>** ht; //桶数组
        int M; //容量
        int N; //词条数
        Bitmap* lazyRemoval; //懒惰删除标记
    #define lazilyRemoved(x)(lazyRemoval->test(x))
    #define markRemoved(x)(lazyRemoval->set(x))
    protected:
        int probe4Hit(const K& k); //沿关键码k对应的查找链，找到词条匹配的桶
        int probe4Free(const K& k); //沿关键码k对应的查找链，找到首个可用空桶
        void rehash();
    public:
        HashTable(int c = 5); //创建容量不小于c的散列表
        ~HashTable();
        int size() const{return N;}
        bool put(K, V);
        V* get(K k);
        bool remove(K k);
};


template <typename K, typename V>
HashTable<K, V>::HashTable(int c){
    M = primeNLT(c, 1048576, "../../_input/prime-1048576-bitmap.txt");
    N = 0; ht = new Entry<K, V>*[M];
    memset(ht, 0, sizeof(Entry<K, V>*) *M);
    lazyRemoval = new Bitmap(M);
}

int primeNLT(int c, int n, char* file){
    Bitmap B(file, n);
    while(c < n){
        if(B.test(c)) c++;
        else return c;
    }
    return c;
}


template <typename K, typename V>
HashTable<K, V>::~HashTable(){
    for(int i = 0; i < M; i ++){
        if(ht[i]) release(ht[i]);
    }
    release(ht);
    release(lazyRemoval);
}