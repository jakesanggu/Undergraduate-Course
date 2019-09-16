/*
 * stack.h
 *
 *  Created on: 2019. 5. 6.
 *      Author: »ó±¸
 */

#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _MAX_STACK_LENGTH       100


struct element{

	int type; //type0 ->op , type1 -> int , type2->double
	union{
		char c_data;
		int i_data;
		double d_data;
		}val;
};


typedef struct _stack{
        int top;
        struct element data[_MAX_STACK_LENGTH];
} stack;


void stack_init(stack*s);
int stack_is_empty(stack* s);
int stack_is_full(stack*s);
int stack_length(stack* s);
int stack_push(stack* s,struct element e);
struct element* stack_pop(stack* s);
struct element* stack_peek(stack* s);

#endif /* STACK_H_ */





