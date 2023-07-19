#include "rpn.h"

Operator optr2rank ( char op ) {
   switch ( op ) {
      case '+' : return ADD;
      case '-' : return SUB;
      case '*' : return MUL;
      case '/' : return DIV; 
      case '^' : return POW;
      case '!' : return FAC;
      case '(' : return L_P;
      case ')' : return R_P;
      case '\0': return EOE;
      default  : exit ( -1 );
   }
}

char orderBetween ( char op1, char op2 ){ 
    return pri[optr2rank ( op1 ) ][optr2rank ( op2 ) ];
}