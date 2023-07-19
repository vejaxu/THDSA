#include "../ch3/myList.h"
#include "Entry.h"
#include "Dictionary.h"
#include "QuadList/QuadList.h"


template <typename K, typename V>
class SkipList: public Dictionary<K, V>, public List<QuadList<Entry<K, V>>*>{
    protected:
        bool skipSearch(ListNode<QuadList<Entry<K, V>>*>* &qlist, QuadlistNode<Entry<K, V>>* &p, K& k);
    public:
        int size() const{return empty() ? 0 : last()->data->size();}
        int level(){return List::size();}
        V* get(K k);
        bool put(K, V)
        bool remove(K k);
};


template <typename K, typename V> 
bool SkipList<K, V>::skipSearch(ListNode<QuadList<Entry<K, V>>*>* &qlist, QuadlistNode<Entry<K, V>>* &p, K& k){ //qlist初始为最上层
    while(true){
        while(p->succ && (p->entry.key <= k)){
            p = p->succ;
        }
        p = p->pred;
        if(p->pred && (k == p->entry.key)) return true;
        qlist = qlist->succ; //转入下一层;
        if(!qlist->succ) return false;
        p = (p->pred) ? p->below : qlist->data->first();
    }
}


template <typename K, typename V>
V* SkipList<K, V>::get(K k){
    if(empty()) return NULL;
    ListNode<QuadList<Entry<K, V>>*>* qlist = first(); //从顶层开始
    QuadlistNode<Entry<K, V>>* p = qlist->data->first();
    return skipSearch(qlist, p, k) ? &(p->entry.value): NULL;
}


template <typename K, typename V>
bool SkipList<K, V>::put(K k, V v){
    Entry<K, V> e = Entry<K, V>(k, v);
    if(empty()){
        List<QuadList<Entry<K, V>>*>::insertAsFirst(new QuadList<Entry<K, V>>);
    }
    ListNode<QuadList<Entry<K, V>>*>* qlist = first();
    QuadlistNode<Entry<K, V>>* p = qlist->data->first();
    if(skipSearch(qlist, p, k)){
        while(p->below){
            p = p->below;
        }
    }
    qlist = last();
    QuadlistNode<Entry<K, V>>* b = qlist->data->insertAfterAbove(e, p);
    while(rand() & 1){
        while(qlist->data->valid(p) && !p->above) p = p->pred;
        if(!qlist->data->valid(p)){
            if(qlist == first()){
                insertAsFirst(new QuadList<Entry<K, V>>);
            }
            p = qlist->pred->data->first()->pred;
        }
        else{
            p = p->above;
        }
        qlist = qlist->pred;
        b = qlist->data->insertAfterAbove(e, p, b);
    }
    return true;
}