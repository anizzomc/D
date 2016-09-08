
#include "base/hash.h"
#include "../../cutest/CuTest.h"

#define LIMIT_STRESS 10000

static unsigned int hash_same_fn(void *key);

static hash_t hash = NULL;

static void after();

static void before();

void TestBaseHash_new(CuTest *tc) {
	before();
	CuAssertPtrNotNull(tc, hash);
	after();
}

void TestBaseHash_insert(CuTest *tc) {
	before();
	void *key = (void*) 0xDEADBEEF;
	void *value = (void *) 0xDEADC0DE;

	CuAssertIntEquals(tc, 0, hash_size(hash));

	CuAssertTrue(tc, hash_insert(hash, key, value));

	CuAssertIntEquals(tc, 1, hash_size(hash));

	CuAssertPtrEquals(tc, value, hash_fetch(hash, key));

	after();
}

void TestBaseHash_insert_over(CuTest *tc) {
	before();
	void *key = (void*) 0xDEADBEEF;
	void *value = (void*) 0xDEADC0DE;
	void *value2 = (void*) 0xFA137ED0;

	CuAssertTrue(tc, hash_insert(hash, key, value));
	CuAssertPtrEquals(tc, value, hash_fetch(hash, key));
	CuAssertIntEquals(tc, 1, hash_size(hash));

	CuAssertTrue(tc, hash_insert(hash, key, value2));
	CuAssertPtrEquals(tc, value2, hash_fetch(hash, key));
	CuAssertIntEquals(tc, 1, hash_size(hash));

	after();
} 

void TestBaseHash_delete(CuTest *tc) {
	before();
	void *key = (void*) 0xDEADBEEF;
	void *value = (void *) 0xDEADC0DE;

	CuAssertTrue(tc, hash_insert(hash, key, value));

	CuAssertPtrEquals(tc, value, hash_delete(hash, key));
	CuAssertPtrEquals(tc, NULL, hash_fetch(hash, key));
	CuAssertPtrEquals(tc, NULL, hash_delete(hash, key));


	after();

}

void TestBashHash_stress(CuTest *tc) {
	before();

	int i;

	for(i = 1; i <= LIMIT_STRESS ; i++) {
		long key = i * 13;
		long value = key - 1;
		CuAssertTrue(tc, hash_insert(hash, (void*) key, (void*) value));
	}

	CuAssertIntEquals(tc, LIMIT_STRESS, hash_size(hash));

	for(i = 1 ; i <= LIMIT_STRESS ; i++) {
		long key = i * 13;
		CuAssertPtrEquals(tc, (void*) key - 1, hash_fetch(hash, (void*)key));
	}

	for(; i <= LIMIT_STRESS*2 ; i++) {
		long key = i * 13;
		long value = key - 1;
		CuAssertTrue(tc, hash_insert(hash, (void*) key, (void*) value));
	}

	CuAssertIntEquals(tc, LIMIT_STRESS*2, hash_size(hash));

	for(i = 1 ; i <= LIMIT_STRESS ; i++) {
		long key = i * 13;
		CuAssertPtrEquals(tc, (void*) key - 1, hash_delete(hash, (void*)key));
	}

	CuAssertIntEquals(tc, LIMIT_STRESS, hash_size(hash));

	for(i = 1; i <= LIMIT_STRESS ; i++) {
		long key = i * 7;
		long value = key - 1;
		CuAssertTrue(tc, hash_insert(hash, (void*) key, (void*) value));
	}

	CuAssertIntEquals(tc, LIMIT_STRESS*2, hash_size(hash));

	after();
}

static void before() {
	hash = hash_new(hash_same_fn);	
}

static void after() {
	hash_destroy(hash);
}

static unsigned int hash_same_fn(void *key) {
	return (unsigned int) key;
}