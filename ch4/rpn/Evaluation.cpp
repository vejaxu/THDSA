//延迟缓冲
//表达式求值
#include <iostream>
#include "../MyStack.h"
#include "rpn.h"
using namespace std;



//对表达式s求值
float evaluate(char* S, char*& RPN){
    Stack<float> opnd; 
    Stack<char> optr; //运算数与运算符
    optr.push('\0'); //表达式结束字符
    while(!optr.empty()){ //运算符栈非空
        if (isdigit(*S)){
            readNumber(S, opnd); //读入可能是多位的数
        }
        else{
            switch(orderBetween(optr.pop(), *S)){ //运算符优先级比较
                case '<': //栈顶优先级低
                    optr.push(*S); 
                    S ++;
                    break;
                case '=': //运算符为)或者\0
                    optr.pop(); //(出栈
                    S ++;
                    break;
                case '>':{ //栈顶优先级更高
                    char op = optr.pop(); //取出栈顶运算符
                    //append(RPN, op);
                    if ('!' == op){
                        float pOpnd = opnd.pop();
                        opnd.push(calcu(op, pOpnd)); //一元运算符,只需取出一个数据进行运算,阶乘
                        //计算的结果推回操作数栈中
                    }
                    else{
                        float pOpnd2 = opnd.pop(), pOpnd1 = opnd.pop(); //p1是先入栈的
                        opnd.push(calcu(pOpnd1, op, pOpnd2));
                        //为什么不可以写成opnd.push(calcu(opnd.pop(), op, opnd.pop()))
                    }
                    break;
                }
                default: exit(-1);
            }

        }
    }
    return opnd.pop();
}


char* removeSpace ( char* s ){
   char* p = s, *q = s;
   while ( true ) {
      while ( isspace ( *q ) ) q++;
      if ( '\0' == *q ) { *p = '\0'; return s; }
      *p++ = *q++;
   }
}

int main ( int argc, char* argv[] ) {
   for ( int i = 1; i < argc; i++ ) {
      /*DSA*/system ( "cls" ); printf ( "\nPress any key to evaluate: [%s]\a\n", argv[i] ); getchar();
      char* rpn = ( char* ) malloc ( sizeof ( char ) * 1 );   rpn[0] = '\0'; 
      float value = evaluate ( removeSpace ( argv[i] ), rpn ); 
      /*DSA*/printf ( "EXPR\t: %s\n", argv[i] ); 
      /*DSA*/printf ( "RPN\t: [ %s]\n", rpn ); 
      /*DSA*/printf ( "Value\t= %.1f = %d\n", value, ( int ) value ); 
      free ( rpn );   rpn = NULL;
      /*DSA*/getchar();
   }
   return 0;
}