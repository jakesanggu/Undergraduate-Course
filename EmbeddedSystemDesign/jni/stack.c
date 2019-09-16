
#include "./include/stack.h"

/*
stack* stack_create(void)
int stack_is_empty(stack *s)
int stack_length(stack *s)
int stack_push(stack *s,element e)
element* stack_pop(stack *s)
element* stack_peek(stack *s)
*/


void stack_init(stack *s){
	s->top = -1;
}

int stack_is_empty(stack* s){
	return (s->top == -1 ? 1 : 0);
}
int stack_is_full(stack* s){
	return (s->top == (_MAX_STACK_LENGTH-1) ? 1 : 0);
}

int stack_length(stack* s){
	return s->top + 1 ;
}

int stack_push(stack* s,struct element e){

if(stack_length(s) != _MAX_STACK_LENGTH){
	memcpy(&(s->data[++s->top]),&e,sizeof(struct element));
	return 0;
}

else{
	return 1; //when err return 1
	}

}

struct element* stack_pop(stack* s){

if(!stack_is_empty(s))
	return &(s->data[s->top--]);

else{
	return NULL;
}

}


struct element* stack_peek(stack* s){

if( !stack_is_empty(s) )
	return &(s->data[s->top]);

else{
	return NULL;

}
}














