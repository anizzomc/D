#include "base/stack.h"
#include "../../cutest/CuTest.h"

#define SIZE 10

static d_stack_t stack = NULL;

static void after();

static void before();


void TestBaseStack_new(CuTest *tc) {
	before();
	CuAssertPtrNotNull(tc, stack);
	CuAssertTrue(tc, d_stack_is_empty(stack));
	CuAssertTrue(tc, !d_stack_is_full(stack));
	after();
}

static void after() {
	d_stack_destroy(stack);
}

static void before() {
	stack = d_stack_new(SIZE);
}
