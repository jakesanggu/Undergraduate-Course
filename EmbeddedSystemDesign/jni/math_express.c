
#include "./include/math_express.h"
#include "./include/debug.h"



#ifdef __DEBUG__
extern int debug_fd;
extern char mseg[150];
#endif

int equation_length(char * equation){
int i = 0;

while(equation[i] !=0)
	i++;


return i;
}

static int count_char(char*eq, char ch){
int i = 0;
int cnt =0;

while(eq[i] != 0){

if(ch == eq[i++])
	cnt++;
}
return cnt;
}


static void convert_unaryop(char *eq){

int i = 0;
char before= _TYPE_OPERATOR;

while(eq[i] != 0){

	switch(eq[i]){

		case '-':
			if((before == _TYPE_OPERATOR) || (before ==_TYPE_UNNARY)){
				eq[i] = '_';
			before = _TYPE_UNNARY;


			}
		break;

		case '1': case '2': case '3': case '4': case '5':
		case '6': case '7': case '8': case '9': case '0':
		before = _TYPE_OPERAND;
		break;

		case '&': case '|': case '~': case '@': case '+': case '?':
		case '/': case '^': case '*': case '<':	case '>': case '%':
		case '=':
		before = _TYPE_OPERATOR;


		}
i++;

}
}

static void delete_enter(char* eq){

int i = 0,k =0;

while(eq[i] != 0 )
{
        if(eq[i] =='\n')
	{
                k = i;
                while(eq[k]!= 0)
		{
                        eq[k] = eq[k+1];
                        k++;
              	}//end while
	i--;
 	}
i++;
}//endfunc


}


void change_symbol(char* equ, char* match, char* replace){ //match > replace
int i =0, j=0,k=0,u;

while(equ[i] != 0){

        if(equ[i] == match[j])
        { k = i;
                while(( match[j] != 0) && (equ[i] !=0 )){
                        if(match[j] != equ[i]){
                                j=0;
                                break;
                        }
                        j++; i++;
                }

                if(match[j] == 0)
                {
                        strcpy(&(equ[k]),replace);
                        for(u = 0; u < strlen(match) - strlen(replace); u++)
                        {
                                equ[u+k+1]='\n';
                        }
                j=0;
                }

        }
        i++;
}

delete_enter(equ);

}

static void set_positive_polarity(struct element* e){
int i = 0, c= 0;
while(1){
	c = get_type(e+i);
	if(c == 0)
		break;
	else{
		if(c == _TYPE_CHAR){
			if( get_cdata(e+i) == '-')
				{
				if( get_type(e+i+1) ==_TYPE_DOUBLE ){
					set_ddata(e[i+1],-1*get_ddata(e+i+1));
					set_cdata(e[i],'+');
				}
				else{
					set_idata(e[i+1],-1*get_idata(e+i+1));
					set_cdata(e[i],'+');
					}
				}


		} //endif
	} //end else
	i++;
	} //endwhile

}


static struct element* equation_parse(char* equation, int mode){
//mode [ double mode (2) , int mode (1)]
/*SYMBOL CHANGE

change
>> , >
<< , <
sqrt_xxxx -> @_xxxx
*/

change_symbol(equation,">>",">");
change_symbol(equation,"sqrt_","@");
change_symbol(equation,"<<","<");
change_symbol(equation,"exp_","?");




int len = equation_length(equation);

char* nospace_equation = malloc(len*sizeof(char));

int i=0, j =0;
while(equation[i] != 0){

	if(equation[i] == ' ')
		i++;
	else
		nospace_equation[j++]=equation[i++];

}
nospace_equation[j] = 0;



#ifdef __DEBUG__
__DEBUG_WRITE__("Equation without Space:%s\n",nospace_equation);
#endif

convert_unaryop(nospace_equation);

#ifdef __DEBUG__
__DEBUG_WRITE__("After unary Conversion:%s\n",nospace_equation);
#endif


len = equation_length(nospace_equation);
struct element* op = malloc(len*sizeof(struct element));

//digits to double

i =0; j=0;
int k=0, neg =0;
char temp[20];

while(i != len+1){



	switch(nospace_equation[i]){

	case '-': case '_': case '+': case '<':
	case '>': case '%': case '~': case '@':
	case '*': case '/': case '^': case '&':
	case '|': case  0 : case '?': case '=':

	case '(': case '[': case '{':
	case ']': case ')': case '}':


		if(j !=0 ){
			temp[j] = 0;
			if(mode ==_MODE_DOUBLE)
				set_ddata(op[k], atof(temp));
			else if(mode ==_MODE_INT)
				set_idata(op[k], atof(temp));

			k++;
			j= 0;
		}

		set_cdata(op[k] ,nospace_equation[i++]);
		k++;


	break;

	default: temp[j++] = nospace_equation[i++];

	break;
	}


}
op[k-1].type = _TYPE_NULL;
//set_positive_polarity(op);

#ifdef __DEBUG__
i = 0;
__DEBUG_WRITE__("----Element Stack----%c \n",'-');
while(get_type(op+i) != _TYPE_NULL ){

if(get_type(op+i) == _TYPE_CHAR){
	__DEBUG_WRITE__("%dth element:",i);
	__DEBUG_WRITE__("%c ",get_cdata(op+i));
	__DEBUG_WRITE__("ASC: %d \n",get_cdata(op+i));
}

else if(get_type(op+i) == _TYPE_INT){
	__DEBUG_WRITE__("%dth element:",i);
	__DEBUG_WRITE__("%d \n",get_idata(op+i));
}

else if(get_type(op+i) == _TYPE_DOUBLE){
	__DEBUG_WRITE__("%dth element:",i);
	__DEBUG_WRITE__("%lf \n",get_ddata(op+i));
}


i++;

}
#endif



free(nospace_equation);
return op;
}


static int priority_compare(struct element* a , struct element* b){


int ret=0;
switch(get_cdata(a)){
	case '@': case '?':
		switch(get_cdata(b)){
			case '@':case '?':
			case '^':
			case '_': case '~':
			case '%': case '/': case '*':
			case '+': case '-':
			case '<': case '>': case '&': case '|': case '=':
			ret = 1; break;
			default : ret = 0; break;
			}
		break;
	case '^':
		switch(get_cdata(b)){
			case '@':case '?':ret = 0; break;
			case '^':
			case '_': case '~':
			case '%': case '/': case '*':
			case '+': case '-':
			case '<': case '>': case '&': case '|': case '=':
			ret = 1; break;
			default : ret = 0; break;
			}
		break;
	case '_':
		switch(get_cdata(b)){
			case '@':case '?':
			case '^':ret = 0; break;
			case '_': case '~':
			case '%': case '/': case '*':
			case '+': case '-':
			case '<': case '>': case '&': case '|':case '=':
			ret = 1; break;
			default : ret = 0; break;
			}
		break;

	case '%': case '/': case '*':
		switch(get_cdata(b)){
			case '@':case '?':
			case '^':
			case '_': case '~': ret = 0; break;
			case '%': case '/': case '*':
			case '+': case '-':
			case '<': case '>':case '&': case '|':case '=':
			ret = 1;  break;
			default : ret = 0; break;
			}
		break;
	case '+': case '-':
		switch(get_cdata(b)){
			case '@':case '?':
			case '^':
			case '_': case '~':
			case '%': case '/': case '*': ret = 0; break;
			case '+': case '-':
			case '<': case '>': case '&': case '|':case '=':
			ret = 1; break;
			default : ret = 0; break;
			}
		break;

	case '<': case '>': case '&': case '|':case '=':
		switch(get_cdata(b)){
			case '@':case '?':
			case '^':
			case '_': case '~':
			case '%': case '/': case '*':
			case '+': case '-': ret = 0; break;
			case '<': case '>': case '&': case '|':case '=':
			ret = 1; break;
			default : ret = 0; break;
			}
		break;

	default : ret = 0; break;


}
#ifdef __DEBUG__
__DEBUG_WRITE__("Comparing Priority : [ '%c' ",get_cdata(a));
__DEBUG_WRITE__(", '%c' ]",get_cdata(b));
__DEBUG_WRITE__("= %d \n",ret);
#endif

return ret;


}

static int convert2postfix(char* equ, int mode, stack* stk){
//returns the length of the stack
stack tmp; stack_init(&tmp);

struct element* top , *cop, *op  = equation_parse(equ, mode);
cop = op;
char c;




while(get_type(cop) != _TYPE_NULL ){

	if( !stack_is_full(&tmp) && !stack_is_full(stk)){

		if(get_type(cop) == _TYPE_CHAR ){
			switch(get_cdata(cop)){

				case '_': case '^':case '/':case '*':
				case '%': case '-':case '&':case '+':
				case '~': case '>':case '<':case '@':
				case '?': case '|':case '=':

				if(!stack_is_empty(&tmp))
					while(   (priority_compare(stack_peek(&tmp), cop))  ){
					stack_push(stk, *(stack_pop(&tmp)));
						if(stack_is_empty(&tmp))
							break;
					}
				stack_push(&tmp,*cop);
				break;


				case '(': case '[': case '{':
				stack_push(&tmp,*cop);
				break;


				case ')':
					while(1){
						c = get_cdata((top=stack_pop(&tmp)));
						if(c != '(')
							stack_push(stk, *top);
						else
							break;

					}

				break;

				case ']':
					while(1){
						c = get_cdata((top=stack_pop(&tmp)));
						if(c != '[')
							stack_push(stk, *top);
						else
							break;

					}
				break;

				case '}':
					while(1){
						c = get_cdata((top=stack_pop(&tmp)));
						if(c != '{')
							stack_push(stk, *top);
						else
							break;

					}
				break;


			}//switch

		cop++;
		}//end if


		else{
		stack_push(stk,*cop);
		cop++;
		}




	}//end if

else{

#ifdef __DEBUG__
__DEBUG_WRITE__("Error: Stack is full ! %c",'!');
#endif

}

}//end while

	while(1){
		if(!stack_is_empty(&tmp))
			stack_push(stk, *(stack_pop(&tmp)));
		else
			break;


	}


free(op);
return stk->top+1;
}

int calculate(char* equ, int mode, struct ret* rt ){

//Check Validity
//--------------------------------------------------
int c = check_validity(equ);

if( c ==_ERROR_EQUATION_TOO_SHORT){
	rt->success = 0;
	rt->err_code =_ERROR_EQUATION_TOO_SHORT;
	return -1;
}
else if( c ==_ERROR_EQUATION_CHAR_NOT_VALID){
	rt->success = 0;
	rt->err_code = _ERROR_EQUATION_CHAR_NOT_VALID;
	return -1;
}
else if( c ==_ERROR_EQUATION_ORDER_NOT_CRR){
	rt->success = 0;
	rt->err_code = _ERROR_EQUATION_ORDER_NOT_CRR;
	return -1;
}

else if( c ==_ERROR_EQUATION_PAREN_NOT_CRR){
	rt->success = 0;
	rt->err_code = _ERROR_EQUATION_PAREN_NOT_CRR;
	return -1;
}

//----------------------------------------------------

stack stk,tk,calc;
stack_init(&stk); stack_init(&calc);

int length = convert2postfix(equ,mode,&stk);

struct element* op;
struct element result={1,};

#ifdef __DEBUG__
struct element* dop;
int idx = 0;
__DEBUG_WRITE__("----To postfix ----%c\n",'-');
#endif

while(!stack_is_empty(&stk)){

#ifndef __DEBUG__
	stack_push(&tk,*(stack_pop(&stk)));
#endif

#ifdef __DEBUG__
stack_push(&tk,*( dop=stack_pop(&stk)));

if(get_type(dop) == _TYPE_CHAR){
	__DEBUG_WRITE__("%c ",get_cdata(dop+idx));
}

else if(get_type(dop) == _TYPE_INT){
	__DEBUG_WRITE__("%d ",get_idata(dop+idx));
}

else if(get_type(dop) == _TYPE_DOUBLE){
	__DEBUG_WRITE__("%lf ",get_ddata(dop+idx));
}
__DEBUG_WRITE__("%c",'\n');


#endif
} // reverse stack


#ifdef __DEBUG__
__DEBUG_WRITE__("Calculating...%s \n","Equation...");
int step = 1;
#endif

while(!stack_is_empty(&tk)){

op = stack_pop(&tk);

if( get_type(op) == _TYPE_CHAR ){//operator


	if(( get_cdata(op) != '_') && (get_cdata(op) !='@') && (get_cdata(op) !='~') && (get_cdata(op) !='?') ){

		if( mode ==_MODE_DOUBLE){
				double op1,op2;

			if(stack_length(&calc) > 1){
				 op2 = get_ddata(stack_pop(&calc));
				 op1 = get_ddata(stack_pop(&calc));
			}
			else{
				#ifdef __DEBUG__
				__DEBUG_WRITE__("Equation Error!%s","error from double mode");
				#endif
				rt->success = 0;
				rt->err_code = _ERROR_STACK_UNDERFLOW;
				return -1;
			}

			result.type = _TYPE_DOUBLE;
			switch(get_cdata(op)){
				case '<': set_ddata(result,((int)op1 << (int)op2));	break;
				case '>': set_ddata(result,((int)op1 >> (int)op2));	break;
				case '%': set_ddata(result,((int)op1 % (int)op2)); 	break;
				case '=': set_ddata(result,(op1 == op2)); 		break;
				case '*': set_ddata(result,(op1 * op2));	 	break;
				case '&': set_ddata(result,((int)op1 & (int)op2));	break;
				case '|': set_ddata(result,((int)op1 | (int)op2));	break;
				case '+': set_ddata(result,(op1 + op2));		break;
				case '/':
					if((int)op2 != 0)
						set_ddata(result,(op1 / op2));
					else{
						rt->success = 0;
						rt->err_code = _ERROR_DIVE_ZERO_;
						return -1;
					}
					break;
				case '-': set_ddata(result,(op1 - op2));		break;
				case '^': set_ddata(result,(pow(op1,op2)));		break;
			}//end switch

		#ifdef __DEBUG__
		__DEBUG_WRITE__("%dst calculation: ",step);
		__DEBUG_WRITE__("[ %lf", op1);
		__DEBUG_WRITE__(" %c" , get_cdata(op));
		__DEBUG_WRITE__(" %lf ]", op2);
		__DEBUG_WRITE__(" = %lf \n", result.val.d_data);
		step++;
		#endif
		}//end if

		else if( mode ==_MODE_INT){
			int op1,op2;
			if(stack_length(&calc) > 1){
				 op2 = get_idata(stack_pop(&calc));
				 op1 = get_idata(stack_pop(&calc));
			}
			else{
				#ifdef __DEBUG__
				__DEBUG_WRITE__("Equation Error!%s","error from int mode");
				#endif
				rt->success = 0;
				rt->err_code = _ERROR_STACK_UNDERFLOW;
				return -1;
			}

			result.type = _TYPE_INT;
			switch(get_cdata(op)){
				case '<': set_idata(result,(op1 << op2));		break;
				case '>': set_idata(result,(op1 >> op2));		break;
				case '%': set_idata(result,(op1 % op2)); 		break;
				case '=': set_idata(result,(op1 == op2)); 		break;
				case '*': set_idata(result,(op1 * op2));	 	break;
				case '&': set_idata(result,(op1 & op2));		break;
				case '|': set_idata(result,(op1 | op2));		break;
				case '+': set_idata(result,(op1 + op2));		break;
				case '/': set_idata(result,(op1 / op2));
				if(op2 != 0){
				set_idata(result,(op1 / op2));
				}
				else{
#ifdef __DEBUG__
		__DEBUG_WRITE__("Equation zero!%d ",3);
#endif
										rt->success = 0;
										rt->err_code = _ERROR_DIVE_ZERO_;
										return -1;
									}
				break;
				case '-': set_idata(result,(op1 - op2));		break;
				case '^': set_idata(result,(pow(op1,op2)));		break;
			}//end switch

		#ifdef __DEBUG__
		__DEBUG_WRITE__("%dst calculation: ",step);
		__DEBUG_WRITE__("[ %d", op1);
		__DEBUG_WRITE__(" %c" , get_cdata(op));
		__DEBUG_WRITE__(" %d ]", op2);
		__DEBUG_WRITE__(" = %d \n", result.val.i_data);
		step++;
		#endif
		}//end if


	}//if(( get_cdata(op) != '_') && (get_cdata(op) !='@') && (get_cdata(op) !='~') ){
	else  //unary operation
	{

		if( mode ==_MODE_DOUBLE){
			double op1;

			if(stack_length(&calc) > 0){
				 op1 = get_ddata(stack_pop(&calc));
			}
			else{
				#ifdef __DEBUG__
				__DEBUG_WRITE__("Equation Error!%s","error from double mode unary");
				#endif
				rt->success = 0;
				rt->err_code = _ERROR_STACK_UNDERFLOW;
				return -1;
			}

			result.type = _TYPE_DOUBLE;
			switch(get_cdata(op)){
				case '_': set_ddata(result,(op1* -1));		break;
				case '~': set_ddata(result, (~(int)op1));	break;
				case '@': set_ddata(result,sqrt(op1));		break;
				case '?': set_ddata(result,(exp(op1)));		break;
				default:					break;
			}//end switch
		#ifdef __DEBUG__
		__DEBUG_WRITE__("%dst calculation: ",step);
		__DEBUG_WRITE__(" %c" , get_cdata(op));
		__DEBUG_WRITE__("unary: %lf", op1);
		__DEBUG_WRITE__(" = %lf \n", result.val.d_data);
		step++;
		#endif
		}


		else if( mode ==_MODE_INT){
			int op1;

			if(stack_length(&calc) > 0){
				 op1 = get_idata(stack_pop(&calc));
			}
			else{
				#ifdef __DEBUG__
				__DEBUG_WRITE__("Equation Error!%s","error from int mode unary");
				#endif
				rt->success = 0;
				rt->err_code = _ERROR_STACK_UNDERFLOW;
				return -1;
			}
			result.type = _TYPE_INT;
			switch(get_cdata(op)){
				case '_': set_idata(result,(op1* -1));		break;
				case '~': set_idata(result, (~op1));		break;
				case '@': set_idata(result,sqrt(op1));		break;
				case '?': set_idata(result,(exp(op1)));		break;
				default:					break;
			}//end switch
		#ifdef __DEBUG__
		__DEBUG_WRITE__("%dst calculation: ",step);
		__DEBUG_WRITE__(" %c" , get_cdata(op));
		__DEBUG_WRITE__("unary: %d", op1);
		__DEBUG_WRITE__(" = %d \n", result.val.i_data);
		step++;
		#endif
		}
	}


	stack_push(&calc,result);



}//end if
else if( get_type(op) != _TYPE_NULL )
	stack_push(&calc,*op);

}//end while



if(stack_length(&calc) == 1 ){
	rt->success = 1;
#ifdef __DEBUG__
__DEBUG_WRITE__("Caculation %s: \n","ok");

#endif

	if(mode == _MODE_DOUBLE)
		rt->val.dret = get_ddata(stack_pop(&calc));
	else
		rt->val.iret  = get_idata(stack_pop(&calc));
}
else{

#ifdef __DEBUG__
__DEBUG_WRITE__("Calculation Failed: Stack Len %d: \n",stack_length(&calc));
#endif
	rt->success = 0;
	rt->err_code = _ERROR_STACK_RESULT_ERR;
	return -1;

}
return 0;
}

static int check_parenthesis(char* equation){

stack stk;
stack_init(&stk);

int i = 0;
struct element c;

while( (c.val.c_data = equation[i++]) != 0 ){
	switch(c.val.c_data){
	 	case '(': case '[': case '{':
			stack_push(&stk,c);
			break;
		case ')': case ']': case '}':

			if(stack_is_empty(&stk))
				return i;
			else{
				switch(stack_pop(&stk)->val.c_data){
					case '(' :    if(  c.val.c_data != ')' ) return i; break;
					case '[' :    if(  c.val.c_data != ']' ) return i; break;
					case '{' :    if(  c.val.c_data != '}' ) return i; break;

			    		} //end sw
			} //end else

			     }//end sw

	} //end while


if(!stack_is_empty(&stk))
	return i;
else
	return 0;

}//end func

static int check_order(char* eq){

int i = 0;
char before= _TYPE_OPERATOR;
int is_spaced = _TYPE_NO_SPACE;

while(eq[i] != 0){

	switch(eq[i]){

//-------------------------------------------------------------------------------------
		case ' ':
		is_spaced = _TYPE_SPACE;
		break;

//-------------------------------------------------------------------------------------
		case '~': case '@':
		case '?':

		is_spaced =_TYPE_NO_SPACE;

		break;
//-------------------------------------------------------------------------------------
		case '-': if( (i>1) && (eq[i-1] == '^'))
				return 1;
		case '&': case '|':
		case '+':
		case '/': case '^': case '*': case '<':
		case '>': case '%':

			if( (before != _TYPE_OPERAND) && (eq[i] != '-'))
				return 1;
			else{
				before = _TYPE_OPERATOR;
				is_spaced =_TYPE_NO_SPACE;
			}
		break;
//------------------------------------------------------------------------------------

		case '1': case '2': case '3': case '4': case '5':
		case '6': case '7': case '8': case '9': case '0':

			if( (before != _TYPE_OPERATOR) && is_spaced )
				return i;
			else{
				before = _TYPE_OPERAND;
				is_spaced = 0;
			}
		break;
//-------------------------------------------------------------------------------------

		default:
		break;
	}

	i++;
}
if(before != _TYPE_OPERAND)
	return i;
else
	return 0;
}

static int check_valid_char(char* eq){

#ifdef __DEBUG__
	__DEBUG_WRITE__("Equation in ASC%s ",":");
#endif


//String Identifier///
struct{
	int pattern;
	int complete;
}
sqrt ={.pattern= 0 , .complete = 1},
exp  ={.pattern= 0 , .complete = 1};


//end String Identifier



int i =0;

while(eq[i] != 0){



	switch(eq[i]){


//String sqrt_----------------------------------------------
		case 's': sqrt.pattern = 1; sqrt.complete = 0;
		i++;
		break;

		case 'q':
			if(!sqrt.pattern)
				return 1;
		i++;
		break;

		case 'r':
			if(!sqrt.pattern)
				return 1;
		i++;
		break;

		case 't':
			if(!sqrt.pattern)
				return 1;
		i++;
		break;


//String sqrt_----------------------------------------------

//String exp_----------------------------------------------
		case 'e': exp.pattern = 1; exp.complete = 0;
		i++;
		break;

		case 'x':
			if(!exp.pattern)
				return 1;
		i++;
		break;

		case 'p':
			if(!exp.pattern)
				return 1;
		i++;
		break;

//String exp_----------------------------------------------


		case '_':
			if(sqrt.pattern){
				sqrt.pattern= 0;
				sqrt.complete =1;
			}
			else if(exp.pattern){
				exp.pattern= 0;
				exp.complete =1;
			}
			else
				return 1;
		i++;
		break;



		case ' ':
		case '&': case '|':	case '~': case '@':  // @??sqrt
		case '?':		//? exp()

		case '+': case '-':
		case '/': case '^': case '*': case '<':
		case '>': case '%':
		case '=':

		case '[': case ']': case '(':
		case ')': case '{': case '}':

		case '.':
		case '1': case '2': case '3': case '4': case '5':
		case '6': case '7': case '8': case '9': case '0':
		i++;
		sqrt.pattern=  0 ;
		break;


		default : return 1;
	}

	}//while

#ifdef __DEBUG__
	__DEBUG_WRITE__("%s","\n");
#endif

if((sqrt.complete != 1) || (exp.complete != 1))
	return 1;
else
	return 0;
}

static int check_validity(char* equ){

int len = equation_length(equ);
char* equation = malloc(len*sizeof(char));
strcpy(equation,equ);

change_symbol(equation,">>",">");
change_symbol(equation,"sqrt_","@");
change_symbol(equation,"<<","<");
change_symbol(equation,"exp_","?");


if(strlen(equation) == 0)
	return _ERROR_EQUATION_TOO_SHORT;

int err_pos;
if(err_pos = check_valid_char(equation)){
#ifdef __DEBUG__
	__DEBUG_WRITE__("SYNTAX ERROR: Operator/Number not valid : ..%s\n",&equation[err_pos]);
#endif
	free(equation);
	return _ERROR_EQUATION_CHAR_NOT_VALID;
}
else if(err_pos = check_order(equation)){

#ifdef __DEBUG__
	__DEBUG_WRITE__("SYNTAX ERROR: Operator/Number not in order : ..%s\n",&equation[err_pos]);
#endif
	free(equation);
	return _ERROR_EQUATION_ORDER_NOT_CRR;
}

else if(err_pos = check_parenthesis(equation)){

#ifdef __DEBUG__
	__DEBUG_WRITE__("SYNTAX ERROR: Parenthesis not in order  : ..%s\n",&equation[err_pos]);
#endif
	free(equation);
	return _ERROR_EQUATION_PAREN_NOT_CRR;
}
else{
	free(equation);
	return 1;
}

}

void convert_string(char* eq)
{
int i =0 ;
while( eq[i] != '\n')
	i++;

eq[i] = 0;

}



