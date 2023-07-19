#include <cstddef>

//#define BinNodePosi<T> BinNode<T>* //节点位置,是一个指针,指向节点,我们将这个类型称为BinNodePosi(T)
template <typename T> struct BinNode;
template <typename T> using BinNodePosi = BinNode<T>*;

#define stature(p) ( (p) ? (p)->height : -1 ) //节点高度

#define IsRoot(x) (!((x).parent))
#define IsLChild(x) ( !IsRoot(x) && ( &(x) == (x).parent->lchild ) )
#define IsRChild(x) ( !IsRoot(x) && ( &(x) == (x).parent->rchild ) )
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lchild)
#define HasRChild(x) ((x).rchild)
#define HasChild(x) (HasLChild(x) || HasRChild(x))
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))
#define IsLeaf(x) (!HasChild(x) )
#define sibling(p) (IsLChild( *(p) ) ? (p)->parent->rchild : (p)->lchild)
#define uncle(p) (IsLChild( *((p)->parent) ) ? (x)->parent->rchild : (x)->parent->lchild)
#define FromParentTo(x) ( \
			IsRoot(x) ? this->_root : \
			( IsLChild(x) ? (x).parent->lchild : (x).parent->rchild ) \
			)
#define release(p) {if(p) delete p;}
typedef enum {RB_RED, RB_BLACK} RBColor; //红黑树s

template <typename T> struct BinNode{
public:
	T data;
	//通过引用指向其他节点
	BinNode* parent; //父节点
	BinNode* lchild; //左孩子
	BinNode* rchild; //右孩子
	int height; //当前节点高度
	int npl; //左式堆
	RBColor color; //颜色

   //构造函数
	BinNode(): parent(NULL), lchild(NULL), rchild(NULL), height(0), npl(1), color(RB_RED)
	{}

	BinNode(T e, BinNode<T>* p = NULL, BinNode<T>* lc = NULL, BinNode<T>* rc = NULL,
		int h = 0, int l = 1, RBColor c = RB_RED) :
		data(e), parent(p), lchild(lc), rchild(rc), height(h), npl(l), color(c)
	{}

	int size(); //包括本身在内所有节点总数
	BinNodePosi<T> insertAsLC(T const& e);
	BinNodePosi<T> insertAsRC(T const& e);
	
	//中序遍历情况下节点的直接后继
	BinNodePosi<T> success(){
		BinNodePosi<T> s = this;
		if (rchild){
			s = rchild;
			while (HasLChild(*s)) s = s->lchild;
		}
		else{
			while (IsRChild(*s)) s = s->parent;
			s = s->parent;
		}
		return s;
	}

	//中序遍历情况下节点的直接前驱
	BinNodePosi<T> pred(){
		BinNodePosi<T> s = this;
		if(rchild){
			s = lchild;
			while(HasRChild(*s)) s = s->rchild;
		}
		else{
			if(IsRChild(*s)){
				if(HasLChild(* s->parent))
					s = s->parent->lchild;
					while(HasRChild(*s))
						s = s->rchild;
			}
		}
		return s;
	}

	bool operator<(BinNode const& bn) { return data < bn.data; }
	bool operator==(BinNode const& bn) { return data == bn.data; }

};


//作为左孩子插入
template <typename T>
BinNodePosi<T> BinNode<T>::insertAsLC(T const& e){
	return lchild = new BinNode(e, this); //初始时this.lc == NULL;
}
template <typename T>
BinNodePosi<T> BinNode<T>::insertAsRC(T const& e){
	return rchild = new BinNode(e, this);
}


template <typename T>
int BinNode<T>::size(){
	int s = 1; //包括当前节点
	if (lchild) //递归实现
		s += lchild->size();
	if (rchild)	
		s += rchild->size();
	return s;
}