#include "queen.h"
#include <iostream>
#include "../MyStack.h"
using namespace std;


void placeQueen(int N){
    Stack<Queen> solu = Stack<Queen>();
    Queen q(0, 0);
    do{
        if (N < solu.size() || N < q.y){
            q = solu.pop();
            q.y ++;
        }else{
            while((q.y < N) && (0 <= solu.find(q))){
                q.y ++;

            }
        }
    }
}