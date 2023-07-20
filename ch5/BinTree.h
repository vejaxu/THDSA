#pragma once

#include "../ch4/MyStack.h"
#include "../ch4/MyQueue.h"
#include "BinNode.h"

#define max(a, b) ( (a) > (b) ? (a) : (b))
using namespace std;


template <typename T> 
class BinTree{
protected:
	int _size;
	BinNodePosi<T> _root; //根节点
	
	virtual int updateHeight(BinNodePosi<T> x){ //更新节点x的高度,各种派生类进行重写
		return x->height = 1 + max(stature(x->lchild), stature(x->rchild));
	}

	void updateHeightAbove(BinNodePosi<T> x){ //自底向上
		while (x){
			updateHeight(x);
			x = x->parent;
		}
	}

public:
	BinTree():_size(0), _root(nullptr){};

	virtual ~BinTree(){
		if (_size > 0) remove(_root);
	}
	
	int size() const{
		return _size;
	}

	bool empty(){return !_root;}

	BinNodePosi<T> root() { return _root;}

/* 	BinNodePosi<T> insertAsRoot(T const& e){
		_size = 1; return _root = new BinNode<T>(e);
	} */
	BinNodePosi<T> insertAsRoot(T const& e);
	
	BinNodePosi<T> insertAsLC(BinNodePosi<T> x, T const& e){
		x->insertAsLC(e); //一个是Tree的函数,一个是Node的函数
		updateHeightAbove(x); //及时地更新高度
		_size ++;
		return x->lchild;
	}
	
	BinNodePosi<T> insertAsRC(BinNodePosi<T> x, T const& e){
		x->insertAsRC(e);
		updateHeightAbove(x);
		_size ++;
		return x->rchild;
	}

	int remove(BinNode<T>* x){
		FromParentTo(*x) = nullptr;
		updateHeightAbove(x->parent);
		int n = removeAt(x);
		_size -= n;
		return n;
	}

	static int removeAt(BinNode<T>* x){
		if (!x) return 0;
		int n = 1 + removeAt(x->lchild) + removeAt(x->rchild);
		release(x);
		return n;
	}

	//先序遍历递归版
	template <typename VST>
	void travPre_R(BinNodePosi<T> x, VST& visit);

	template <typename VST>
	void travPre_I1(BinNodePosi<T> x, VST& visit);

	template <typename VST>
	void travPre_I2(BinNodePosi<T> x, VST& visit);

	template <typename VST>
	void travIn_R(BinNodePosi<T> x, VST& visit);

	template <typename VST>
	void travIn_I(BinNodePosi<T> x, VST& visit);

	template <typename VST>
	void travIn_I2(BinNodePosi<T> x, VST& visit);

	template <typename VST>
	void travIn_I3(BinNodePosi<T> x, VST& visit);

	template <typename VST>
	void travPost_R(BinNodePosi<T> x, VST& visit);

	template <typename VST>
	void travPost_I(BinNodePosi<T> x, VST& visit);

	//层次遍历
	template <typename VST>
	void travLevel(BinNodePosi<T> x,VST& visit);

	bool operator<(BinTree<T> const& t){
		return _root && t.root && lt(_root, t._root);
	}
	bool operator==(BinTree<T> const& t){
		return _root && t._root && _root == t._root;
	}
};


template <typename T>
BinNodePosi<T> BinTree<T>::insertAsRoot(T const& e){
	_size = 1;
	return _root = new BinNode<T>(e);
}


//先序遍历递归版
template <typename T>
template <typename VST>
void BinTree<T>::travPre_R(BinNodePosi<T> x, VST& visit){
	if (!x)
		return;
	visit(x->data);
	travPre_R(x->lchild, visit);
	travPre_R(x->rchild, visit);
}


//先序遍历迭代版1
template <typename T>
template <typename VST>
void BinTree<T>::travPre_I1(BinNodePosi<T> x, VST& visit){
	Stack<BinNodePosi<T>> S;
	if (x){
		S.push(x);
	}
	while(! S.empty()){
		x = S.pop();
		visit(x->data);
		if (HasRChild(*x))
			S.push(x->rchild); //右孩子先入后出
		if (HasLChild(*x))
			S.push(x->lchild); //左孩子后入先出
	}
}


template <typename T, typename VST>
//遍历的顺序为沿着左侧链不断地下行
//遍历的过程为先自顶向下地访问左孩子节点
//等到左孩子为空时,再自底向上地访问右子树
static void visitAlongLeftBranch(BinNodePosi<T> x, VST& visit, Stack<BinNodePosi<T>>& S){
	while(x){
		visit(x->data); //访问当前节点
		S.push(x->rchild); //将右子树入栈,以后会逆序访问出栈
		x = x->lchild; //左侧链
	}
}
template <typename T>
template <typename VST>
void BinTree<T>::travPre_I2(BinNodePosi<T> x, VST& visit){
	Stack<BinNodePosi<T>> S;
	while(true){
		visitAlongLeftBranch(x, visit, S); //不断地访问左侧链,将右子树入栈缓冲
		if (S.empty()) break;
		x = S.pop(); //访问下一子树的跟
	}
}


//中序遍历递归版
template <typename T>
template <typename VST>
void BinTree<T>::travIn_R(BinNodePosi<T> x, VST& visit){
	if (!x) return;
	travIn_R(x->lchild, visit);
	visit(x->data);
	travIn_R(x->rchild, visit);
}


template <typename T>
static void goAlongLeftBranch(BinNodePosi<T> x, Stack<BinNodePosi<T>>& S){
	while(x){
		S.push(x);
		x = x->lchild; //沿着左分支入栈,然后逆序的出栈访问
	}
}
template <typename T>
template <typename VST>
void BinTree<T>::travIn_I(BinNodePosi<T> x, VST& visit){
	Stack<BinNodePosi<T>> S;
	while(true){
		goAlongLeftBranch(x, S);
		if (S.empty()) break;	
		x = S.pop();
		visit(x->data); //最左节点开始访问
		x = x->rchild; //然后访问右孩子,要是右孩子访问玩或者没有,则逆序跳转到上一个根	
	}
}


template <typename T>
template <typename VST>
void BinTree<T>::travIn_I2(BinNodePosi<T> x, VST& visit){
	Stack<BinNodePosi<T>> S;
	while(true){
		if (x){
			S.push(x);
			x = x->lchild;
		}
		else if(!S.empty()){
			x = S.pop();
			visit(x->data);
			x = x->rchild;
		}
		else{
			break;
		}
	}
}


template <typename T>
template <typename VST>
void BinTree<T>::travIn_I3(BinNodePosi<T> x, VST& visit){
	while(true){
		if(HasLChild(*x)){
			x = x->lchild;
		}
		else{
			visit(x->data);
			while(!HasRChild(*x)){
				if(!(x = x->success())) return;
				else visit(x->data);
			}
			x = x->rchild;
		}
	}
}


template <typename T>
template <typename VST>
void BinTree<T>::travPost_R(BinNodePosi<T> x, VST& visit){
	if (!x) return;
	travPost_R(x->lchild, visit);
	travPost_R(x->rchild, visit);
	visit(x->data);
}


template <typename T>
void gotoLeftmostLeaf(Stack<BinNodePosi<T>>& S){
	while(BinNodePosi<T> x = S.top()){
		if (HasLChild(*x)){
			if (HasRChild(*x)){
				S.push(x->rchild);
			}
			S.push(x->lchild);
		}
		else{
			S.push(x->rchild);
		}
	}
	S.pop();
}
template <typename T>
template <typename VST>
void BinTree<T>::travPost_I(BinNodePosi<T> x, VST& visit){
	Stack<BinNodePosi<T>> S;
	if (x) S.push(x);
	while(!S.empty()){
		if (S.top() != x->parent){
			gotoLeftmostLeaf(S);
		}
		x = S.pop();
		visit(x->data);
	}
}


template <typename T>
template <typename VST>
void BinTree<T>::travLevel(BinNodePosi<T> x ,VST& visit){
	Queue<BinNodePosi<T>> Q;
	Q.enqueue(x); //root节点入队
	while(!Q.empty()){
		BinNodePosi<T> x = Q.dequeue();
		visit(x->data);
		if(HasLChild(*x))
			Q.enqueue(x->lchild); //先左后右,先进后出
		if(HasRChild(*x))
			Q.enqueue(x->rchild);
	}
}