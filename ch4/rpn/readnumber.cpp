#include "rpn.h"

void readNumber(char*& p, Stack<float>& stk ) {
   stk.push((float)(*p - '0'));
   while(isdigit(*(++p))) 
      stk.push(stk.pop() * 10 + (*p - '0')); 
   if ('.' != *p ) return;
   float fraction = 1;
   while (isdigit(*(++p)))
      stk.push(stk.pop() + (*p - '0' ) * (fraction /= 10));
}