//队列--循环分配器
//银行服务模拟
#include "MyQueue.h"
#include <iostream>


struct Customer{
    int window; //服务窗口
    unsigned int time; //服务时长
};

//服务函数
void stimulate(int nWin, int serveTime){
    Queue<Customer>* windows = new Queue<Customer>[nWin]; //每一个窗口创建一个队列
    for (int now = 0; now < serveTime; now++){
        if (rand() % (1 + nWin)){
            Customer c;
            c.time = 1 + rand() % 98;
            c.window = bestWindow(windows, nWin);
            windows[c.window].enqueue(c);
        }
        for (int i = 0; i < nWin; i ++){
            if (!windows[i].empty()){
                if (--windows[i].front().time <= 0){
                    windows[i].dequeue();
                }
            }
        }
    }
    delete[] windows;
}


int bestWindow(Queue<Customer> windows[], int nWin){
    int minSize = windows[0].size();
    int optiWin = 0;
    for (int i = 1; i < nWin; i ++){
        if (minSize > windows[i].size()){
            minSize = windows[i].size();
            optiWin = i;
        }
    }
    return optiWin;
}