/* stack.c */
#include "base/stack.h"
#include "base/d_malloc.h"
#include "base/util.h"
#include "base/log.h"
#include <stdlib.h>

struct d_stackCDT {
	void **elements;
	size_t max_size;
	unsigned int top;
};


d_stack_t d_stack_new(size_t size) {
	d_stack_t stack = d_malloc(sizeof(struct d_stackCDT));
	stack->elements = d_malloc(sizeof(void*)*size);


	stack->max_size = size;
	stack->top = 0;

	return stack;
}

size_t d_stack_size(d_stack_t stack) {
	return stack->top;
}

void d_stack_push(d_stack_t stack, void *elem) {
	if(d_stack_is_full(stack)) {
		ERROR("stack is full");
		print_trace();
		abort();
	}
	stack->elements[stack->top++] = elem;
}

void* d_stack_pop(d_stack_t stack) {
	if(d_stack_is_full(stack)) {
		ERROR("stack is full");
		print_trace();
		abort();
	}
	return stack->elements[stack->top--];
}

int d_stack_is_empty(d_stack_t stack) {
	return stack->top == 0;
}

int d_stack_is_full(d_stack_t stack) {
	return !(stack->top < stack->max_size); 
}

void d_stack_destroy(d_stack_t stack) {
	free(stack->elements);
	free(stack);
}

