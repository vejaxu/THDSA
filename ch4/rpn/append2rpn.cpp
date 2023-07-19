#include "rpn.h"

void append ( char*& rpn, float opnd ) { 
   int n = strlen ( rpn );
   char buf[64];
   if ( opnd != ( float ) ( int ) opnd ) sprintf ( buf, "%.2f \0", opnd ); 
   else                          sprintf ( buf, "%d \0", ( int ) opnd );
   rpn = ( char* ) realloc ( rpn, sizeof ( char ) * ( n + strlen ( buf ) + 1 ) ); 
   strcat ( rpn, buf );
}

void append ( char*& rpn, char optr ) {
   int n = strlen ( rpn );
   rpn = ( char* ) realloc ( rpn, sizeof ( char ) * ( n + 3 ) ); 
   sprintf ( rpn + n, "%c ", optr ); rpn[n + 2] = '\0'; 
}