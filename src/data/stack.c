#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

// Utility function to initialize stack
struct stack* new_stack(int capacity)
{
	struct stack *pt = (struct stack*)malloc(sizeof(struct stack));

	pt->maxsize = capacity;
	pt->top = -1;
	pt->items = malloc(sizeof(void *) * capacity);

	return pt;
}

// Utility function to return the size of the stack
int stack_size(struct stack *pt)
{
	return pt->top + 1;
}

// Utility function to check if the stack is empty or not
int is_stack_empty(struct stack *pt)
{
	return pt->top == -1;	// or return size(pt) == 0;
}

// Utility function to check if the stack is full or not
int is_stack_full(struct stack *pt)
{
	return pt->top == pt->maxsize - 1;	// or return size(pt) == pt->maxsize;
}

// Utility function to add an element x in the stack
void stack_push(struct stack *pt, void *x)
{
	// check if stack is already full. Then inserting an element would 
	// lead to stack overflow
	if (is_stack_full(pt)) {
		exit(EXIT_FAILURE);
	}
	
	// add an element and increments the top index
	pt->items[++pt->top] = x;
}

// Utility function to return top element in a stack
void *stack_peek(struct stack *pt) {
	// check for empty stack
	if (!is_stack_empty(pt))
		return pt->items[pt->top];
	else
		exit(EXIT_FAILURE);
}

// Utility function to pop top element from the stack
void *stack_pop(struct stack *pt) {
	// check for stack underflow
	if (is_stack_empty(pt)) {
		exit(EXIT_FAILURE);
	}

	// decrement stack size by 1 and (optionally) return the popped element
	return pt->items[pt->top--];
}