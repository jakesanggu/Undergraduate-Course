
/*
 * math_express.h
 *
 *  Created on: 2019. 5. 6.
 *      Author: »ó±¸
 */

#ifndef MATH_EXPRESS_H_
#define MATH_EXPRESS_H_

#include "stack.h"

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

#define STRING(X) #X
#define MAX_EQUATION_LEN	200
#define _TYPE_OPERAND	0
#define	_TYPE_OPERATOR	1
#define _TYPE_UNNARY	2

#define	_TYPE_SPACE	1
#define _TYPE_NO_SPACE	0

#define __TYPE_CHAR _TYPE_CHAR
#define __TYPE_DOUBLE _TYPE_DOUBLE
#define __TYPE_INT _TYPE_INT

#define _TYPE_NULL	0
#define _TYPE_CHAR	1
#define _TYPE_INT	2
#define _TYPE_DOUBLE	3

#define _MODE_INT	1 //integer mode
#define	_MODE_DOUBLE	2 //double mode



#define _ERROR_EQUATION_TOO_SHORT	0
#define _ERROR_EQUATION_CHAR_NOT_VALID	2
#define _ERROR_EQUATION_ORDER_NOT_CRR	3
#define _ERROR_EQUATION_PAREN_NOT_CRR	4
#define	_ERROR_STACK_UNDERFLOW		5
#define _ERROR_STACK_RESULT_ERR		6
#define _ERROR_DIVE_ZERO_		7


#define	get_cdata(op) ((op)->val.c_data)
#define get_idata(op) ((op)->val.i_data)
#define get_ddata(op) ((op)->val.d_data)
#define get_type(op) ((op)->type)

#define	set_cdata(op,v) do{					\
				((op).val.c_data) = (char) (v);	\
				((op).type = __TYPE_CHAR );	\
				}while(0)

#define	set_idata(op,v) do{					\
				((op).val.i_data) = (int) (v);	\
				((op).type = __TYPE_INT );	\
				}while(0)

#define	set_ddata(op,v) do{					\
				((op).val.d_data) = (double) (v);	\
				((op).type = __TYPE_DOUBLE );	\
				}while(0)





struct ret{
	int success;
	int err_code;
	union{
	int iret;
	double dret;
	}val;

};


int calculate(char* equ, int mode, struct ret* rt ); //public
int equation_length(char * equation);
static int count_char(char*eq, char ch);
static void convert_unaryop(char *eq);
static void delete_enter(char* eq);
void change_symbol(char* equ, char* match, char* replace);
static void set_positive_polarity(struct element* e);
static struct element* equation_parse(char* equation, int mode);
static int priority_compare(struct element* a , struct element* b);
static int convert2postfix(char* equ, int mode, stack* stk);
static int check_parenthesis(char* equation);
static int check_order(char* eq);
static int check_valid_char(char* eq);
static int check_validity(char* equ);
static void convert_string(char* eq);






#endif /* MATH_EXPRESS_H_ */
