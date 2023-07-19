#pragma once
#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../MyStack.h"
#include "priority.h"

__int64 facI ( int n );
float calcu ( float a, char op, float b );
float calcu ( char op, float b );
void displayProgress ( char*, char*, Stack<float>&, Stack<char>&, char* );
void readNumber ( char*&, Stack<float>& );
Operator optr2rank ( char );
char orderBetween ( char, char );
void append ( char*&, float );
void append ( char*&, char );
float evaluate ( char* expr, char*& rpn );