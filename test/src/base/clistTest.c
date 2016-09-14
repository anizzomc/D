/* clistTest.c */
#include "base/clist.h"
#include "../../cutest/CuTest.h"

#define SIZE 10

static d_clist list = NULL;

static void after();

static void before();


void TestBaseClist_new(CuTest *tc) {
	before();
	CuAssertPtrNotNull(tc, list);
	CuAssertTrue(tc, d_clist_is_empty(list));
	CuAssertTrue(tc, !d_clist_is_full(list));
	after();
}

void TestBaseClist_add(CuTest *tc){
	before();
	void* elem = (void *) 0xDEADBEEF;

	d_clist_put(list, elem);

	CuAssertTrue(tc, !d_clist_is_empty(list));

	after();
}

void TestBaseClist_takeOne(CuTest *tc) {
	before();
	void* elem = (void *) 0xDEADBEEF;

	d_clist_put(list, elem);
	CuAssertPtrEquals(tc, elem, d_clist_take(list));
	CuAssertTrue(tc, d_clist_is_empty(list));

	after();
}

void TestBaseClist_takeTwo(CuTest *tc) {
	before();
	void* elem1 = (void *) 0xDEADBEEF;
	void* elem2 = (void *) 0xDEADC0DE;

	d_clist_put(list, elem1);
	d_clist_put(list, elem2);

	CuAssertPtrEquals(tc, elem1, d_clist_take(list));
	CuAssertPtrEquals(tc, elem2, d_clist_take(list));

	CuAssertTrue(tc, d_clist_is_empty(list));

	after();
}

void TestBaseClist_full(CuTest *tc) {
	before();
	int i;

	void* elem1 = (void *) 0xDEADBEEF;
	void* elem2 = (void *) 0xDEADC0DE;

	d_clist_put(list, elem1);
	d_clist_put(list, elem2);

	CuAssertPtrEquals(tc, elem1, d_clist_take(list));
	CuAssertPtrEquals(tc, elem2, d_clist_take(list));

	CuAssertTrue(tc, d_clist_is_empty(list));

	for(i = 0 ; i < SIZE ; i++) {
		long elem = ((i+1)*3337);
		CuAssertTrue(tc, !d_clist_is_full(list));
		d_clist_put(list, (void*) elem);
	}

	CuAssertTrue(tc, d_clist_is_full(list));

	for(i = 0 ; i < SIZE ; i++) {
		long elem = (i+1)*3337;
		CuAssertTrue(tc, !d_clist_is_empty(list));
		CuAssertPtrEquals(tc, (void*) elem, d_clist_take(list));
	}

	CuAssertTrue(tc, d_clist_is_empty(list));

	after();
}


static void before() {
	list = d_clist_new(SIZE);	
}

static void after() {
	d_clist_destroy(list);
}