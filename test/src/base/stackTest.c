#include "base/stack.h"
#include "../../cutest/CuTest.h"

#define SIZE 10

static d_stack_t stack = NULL;

static void after();

static void before();


void TestBaseStack_new(CuTest* tc) {
	before();
	CuAssertPtrNotNull(tc, stack);
	CuAssertTrue(tc, d_stack_is_empty(stack));
	CuAssertTrue(tc, !d_stack_is_full(stack));
	after();
}

void TestBaseStack_push(CuTest* tc) {
	before();
	CuAssertTrue(tc, d_stack_is_empty(stack));
	void* elem1 = (void*) 0xDEADC0DE;
	void* elem2 = (void*) 0xDEADBEEF;

	d_stack_push(stack, elem1);
	CuAssertTrue(tc, !d_stack_is_empty(stack));
	
	d_stack_push(stack, elem2);
	CuAssertTrue(tc, !d_stack_is_empty(stack));

	CuAssertPtrEquals(tc, elem2, d_stack_pop(stack));
	CuAssertPtrEquals(tc, elem1, d_stack_pop(stack));
	CuAssertTrue(tc, d_stack_is_empty(stack));

	after();
}

void TestBaseStack_full(CuTest* tc) {
	before();
	int i;

	for(i = 0 ; i < SIZE ; i++) {
		long e = i*13;
		d_stack_push(stack, (void *)e);
	}
	CuAssertTrue(tc, d_stack_is_full(stack));
	for(i = (SIZE - 1)  ; i >= 0 ; i--) {
		long e = i*13;
		CuAssertPtrEquals(tc, (void*) e, d_stack_pop(stack));
	}

	CuAssertTrue(tc, d_stack_is_empty(stack));

	after();
}

static void after() {
	d_stack_destroy(stack);
}

static void before() {
	stack = d_stack_new(SIZE);
}
