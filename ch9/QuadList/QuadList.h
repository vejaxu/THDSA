#include "QuadListNode.h"
template <typename T> class QuadList{
    private:
        int _size;
        QlistNodePosi(T) header;
        QlistNodePosi(T) trailer;
    protected:
        void init();
        int clear();
    public:
        QuadList(){init();}
        ~QuadList(){clear(); delete header; delete trailer;}


        Rank size() const{return _size;}
        bool empty() const{return _size <= 0;}
        QlistNodePosi(T) first() const{return header->succ;}
        QlistNodePosi(T) last() const{return trailer->pred;}
        bool valid(QlistNodePosi(T) p){
            return p && (trailer != p) && (header != p);
        }
        T remove(QlistNodePosi(T) p);
        QlistNodePosi(T) insertAfterAbove(T const& e, QlistNodePosi(T) p, QlistNodePosi(T) b = NULL);


        void traverse(void(*) (T&));
        template <typename VST>
        void tracerse(VST&);
};


template <typename T> void QuadList<T>::init(){
    header = new QuadlistNode<T>;
    trailer = new QuadlistNode<T>;
    header->succ = trailer;
    header->pred = NULL;
    trailer->pred = header;
    trailer->succ = NULL;
    header->above = trailer->above = NULL;
    header->below = trailer->below = NULL;
    _size = 0;
}


template <typename T> QlistNodePosi(T) QuadList<T>::insertAfterAbove(T const& e, QlistNodePosi(T) p, QlistNodePosi(T) b = nullptr){
    _size ++;
    return p->insertAsSuccAbove(e, b);
}