#include <iostream>
#include "Graph.h"
#include "../ch2/MyVector.h"
#include "../ch4/MyQueue.h"


template <typename Tv> struct Vertex{
    Tv data;
    int inDegree;
    int outDegree;
    VStatus status;
    int dTime, fTime; //标签时间
    int parent;
    int priority; //优先级遍历算法优先级数
    Vertex(Tv const& d = (Tv) 0):
        data(d), inDegree(0), outDegree(0), status(UNDISCOVERED), 
        dTime(-1), fTime(-1), parent(-1), priority(INT_MAX){}
};


template <typename Te> struct Edge{
    Te data;
    int weight;
    EType type;
    Edge(Te const& d, int w):
        data(d), weight(w), type(UNDETERMINED){}
};


template <typename Tv, typename Te>
class GraphMatrix: public Graph<Tv, Te>{
    private:
        Vector< Vertex <Tv > > V; //顶点集
        Vector< Vector <Edge<Te>* > > E; //边集
    
    public:
        GraphMatrix(){Graph<Tv, Te>::n = e = 0;}

        ~GraphMatrix(){
            for (int j = 0; j < n; j++){
                for (int k = 0; k < n; k ++){
                    delete E[j][k];
                }
            }
        }

        virtual Tv& vertex(int i){return V[i].data;}
        virtual int inDgree(int i ){return V[i].inDegree;}
        virtual int outDgree(int i){return V[i].outDegree;}
        virtual int firstNbr(int i){return nextNbr(i, n);} //第一个有效的邻居
        virtual int nextNbr(int i, int j){ //顶点i已经枚举到邻居j,则转向下一邻居,逆序的寻找
            while((-1 < j) && (!exists(i, --j)))
                return j;
        }
        virtual VStatus& status(int i){return V[i].status;}
        virtual int& dTime(int i){return V[i].dTime;}
        virtual int& fTime(int i){return V[i].fTime;}
        virtual int& parent(int i){return V[i].parent;}
        virtual int& priority(int i){return V[i].priority;}

        virtual int insert(Tv const& vertex){
            //插入顶点,返回编号
            for(int j = 0; j < n; j ++){
                E[j].insert(NULL); //每一行末尾增加一个空单位
            }
            n++;
            E.insert(Vector<Edge<Te>*> (n, n, (Edge<Te>*) NULL));
            return V.insert(Vertex<Tv> (vertex));
        }

        virtual Tv remove(int i){
            for(int j = 0; j < n; j ++){
                if(exists(i, j)){ //删除所有边信息
                    delete E[i][j];
                    V[j].outDegree--;
                }
            }
            E.remove(i); n--;
            for (int j = 0; j < n; j ++){
                if(exists(j, i){
                    delete E[j].remove(i);
                    V[j].outDegree --;
                })
            }
            Tv vBak = vertex(i);
            V.remove(i); //删除顶点i
            return vBak;
        }

        virtual bool exists(int i, int j){
            return (0 <= i) && (i < n) && (0 <= j) && (j < n) && E[i][j] != NULL;
        }

        virtual EType& type(int i, int j){
            return E[i][j]->type;
        }

        virtual Te& edge(int i, int j){return E[i][j]->data;}

        virtual int& weight(int i, int j){return E[i][j]->weight;}

        virtual void insert(Te const& edge, int w, int i, int j){
            if(exists(i, j)) return;
            E[i][j] = new Edge<Te>(edge, w);
            e ++;
            V[i].ouotDegree++;
            V[j].inDegree++;
        }

        virtual Te remove(int i, int j){
            Te eBak = edge(i, j); //备份边的信息
            delete E[i][j];
            E[i][j] = NULL; //将引用置为空
            e --;
            V[i].outDegree --;
            V[j].inDegree --;
            return eBak;
        }
};


template <typename Tv, typename Te>
void Graph<Tv, Te>::bfs(int s){
    reset();
    int clock = 0;
    int v = s;
    do{
        if (UNDISCOVERED == status(v)){
            BFS(v, clock);
        }
    }
    while(s != (v = (++v % n)));
}
template <typename Tv, typename Te>
void Graph<Tv, Te>::BFS(int v, int& clock){
    Queue<int> Q;
    status(v) = DISCOVERED;
    Q.enqueue(v);
    while(! Q.empty()){
        int v = Q.dequeue();
        dTime(v) = ++ clock;
        for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)){
            if(UNDISCOVERED == status(u)){
                status(u) = DISCOVERED;
                Q.enqueue(u);
                type(u, v) = TREE;
                patent(u) = v;
            }
            else{
                type(u, v) = CROSS;
            }
        }
        status(v) = VISITED;
    }
}


template <typename Tv, typename Te>
void Graph<Tv, Te>::dfs(int s){
    reset();
    int clock = 0;
    int v = s;
    do
        if(UNDISCOVERED == status(v)){
            DFS(v, clock);
        }
    while(s != (v = (++v % n)));
}
template <typename Tv, typename Te>
void Graph<Tv, Te>::DFS(int v, int& clock){
    dTime(v) = ++clock;
    statue(v) = DISCOVERED;
    for(int u = firstNbr(v); -1 < u; u = nextNbr(v, u)){
        switch(status(u)){
            case UNDISCOVERED:
                type(v, u) = TREE;
                parent(u) = v;
                DFS(u, clock);
                break;
            case DISCOVERED: //u比v先发现但是还没被访问完,则u是v的祖先
                type(v, u) = BACKWARD;
                break;
            default: //v比u先发现并且u被访问完,那么为forward,否则为cross
                type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
                break;
        }
    }
    status(v) = VISITED;
    fTime(v) = ++clock;
}