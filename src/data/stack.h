#ifndef __STACK_H
#define __STACK_H

// Initial implementation can be found at https://www.techiedelight.com/stack-implementation/

// Data structure for stack
typedef struct stack {
	int maxsize;	// define max capacity of stack
	int top;		
	void **items;
} *Stack;

struct stack* new_stack(int capacity);
int stack_size(struct stack *pt);
int is_stack_empty(struct stack *pt);
int is_stack_full(struct stack *pt);
void stack_push(struct stack *pt, void *x);
void *stack_peek(struct stack *pt);
void *stack_pop(struct stack *pt);

#endif