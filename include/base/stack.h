#ifndef __D_STACK_H_
#define __D_STACK_H_

#include "base/stack.h"
#include <stddef.h> 

typedef struct d_stackCDT *d_stack_t;


d_stack_t d_stack_new(size_t size);

size_t d_stack_size(d_stack_t stack);

void d_stack_push(d_stack_t stack, void* elem);

void* d_stack_pop(d_stack_t stack);

int d_stack_is_empty(d_stack_t stack);

int d_stack_is_full(d_stack_t stack);

void d_stack_destroy(d_stack_t stack);



#endif