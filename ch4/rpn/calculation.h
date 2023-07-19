#include "rpn.h"
float calcu ( float a, char op, float b ) {
   switch ( op ) {
      case '+' : return a + b;
      case '-' : return a - b;
      case '*' : return a * b;
      case '/' : if ( 0==b ) exit ( -1 ); return a/b;
      case '^' : return pow ( a, b );
      default  : exit ( -1 );
   }
}

float calcu ( char op, float b ) {
   switch ( op ) {
      case '!' : return ( float ) facI ( ( int ) b );
      default  : exit ( -1 );
   }
}