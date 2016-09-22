
#include "base/hash.h"
#include "../../cutest/CuTest.h"
#include <stdlib.h>

#define LIMIT_STRESS 10000

static unsigned int hash_same_fn(void *key);

static d_hash_t hash = NULL;

static void after();

static void before();

static int find(void** keys, void* key, int size);

void TestBaseHash_new(CuTest *tc) {
	before();
	CuAssertPtrNotNull(tc, hash);
	after();
}

void TestBaseHash_insert(CuTest *tc) {
	before();
	void *key = (void*) 0xDEADBEEF;
	void *value = (void *) 0xDEADC0DE;

	CuAssertIntEquals(tc, 0, d_hash_size(hash));

	CuAssertTrue(tc, d_hash_insert(hash, key, value));

	CuAssertIntEquals(tc, 1, d_hash_size(hash));

	CuAssertPtrEquals(tc, value, d_hash_fetch(hash, key));

	after();
}

void TestBaseHash_insert_over(CuTest *tc) {
	before();
	void *key = (void*) 0xDEADBEEF;
	void *value = (void*) 0xDEADC0DE;
	void *value2 = (void*) 0xFA137ED0;

	CuAssertTrue(tc, d_hash_insert(hash, key, value));
	CuAssertPtrEquals(tc, value, d_hash_fetch(hash, key));
	CuAssertIntEquals(tc, 1, d_hash_size(hash));

	CuAssertTrue(tc, d_hash_insert(hash, key, value2));
	CuAssertPtrEquals(tc, value2, d_hash_fetch(hash, key));
	CuAssertIntEquals(tc, 1, d_hash_size(hash));

	after();
} 

void TestBaseHash_delete(CuTest *tc) {
	before();
	void *key = (void*) 0xDEADBEEF;
	void *value = (void *) 0xDEADC0DE;

	CuAssertTrue(tc, d_hash_insert(hash, key, value));

	CuAssertPtrEquals(tc, value, d_hash_delete(hash, key));
	CuAssertPtrEquals(tc, NULL, d_hash_fetch(hash, key));
	CuAssertPtrEquals(tc, NULL, d_hash_delete(hash, key));


	after();

}

void TestBashHash_stress(CuTest *tc) {
	before();

	int i;

	for(i = 1; i <= LIMIT_STRESS ; i++) {
		long key = i * 13;
		long value = key - 1;
		CuAssertTrue(tc, d_hash_insert(hash, (void*) key, (void*) value));
	}

	CuAssertIntEquals(tc, LIMIT_STRESS, d_hash_size(hash));

	for(i = 1 ; i <= LIMIT_STRESS ; i++) {
		long key = i * 13;
		CuAssertPtrEquals(tc, (void*) key - 1, d_hash_fetch(hash, (void*)key));
	}

	for(; i <= LIMIT_STRESS*2 ; i++) {
		long key = i * 13;
		long value = key - 1;
		CuAssertTrue(tc, d_hash_insert(hash, (void*) key, (void*) value));
	}

	CuAssertIntEquals(tc, LIMIT_STRESS*2, d_hash_size(hash));

	for(i = 1 ; i <= LIMIT_STRESS ; i++) {
		long key = i * 13;
		CuAssertPtrEquals(tc, (void*) key - 1, d_hash_delete(hash, (void*)key));
	}

	CuAssertIntEquals(tc, LIMIT_STRESS, d_hash_size(hash));

	for(i = 1; i <= LIMIT_STRESS ; i++) {
		long key = i * 7;
		long value = key - 1;
		CuAssertTrue(tc, d_hash_insert(hash, (void*) key, (void*) value));
	}

	CuAssertIntEquals(tc, LIMIT_STRESS*2, d_hash_size(hash));

	after();
}


void TestBashHash_keys(CuTest *tc) {
	before();
	void *key1 = (void*) 0xDEADBEEF;
	void *key2 = (void*) 0xDEADC0DE;
	void *key3 = (void*) 0xBEEFC0DE;

	d_hash_insert(hash, key1, (void*)0);
	d_hash_insert(hash, key2, (void*)1);
	d_hash_insert(hash, key3, (void*)2);

	int size = d_hash_size(hash);
	void **keys = d_hash_keys(hash);

	CuAssertPtrEquals(tc, key1, keys[find(keys, key1, size)]);
	CuAssertPtrEquals(tc, key2, keys[find(keys, key2, size)]);
	CuAssertPtrEquals(tc, key3, keys[find(keys, key3, size)]);

	free(keys);

	after();
}

static int find(void** keys, void* key, int size){
	int i;
	for(i = 0 ; i < size ; i++) {
		if(keys[i] == key) {
			return i;
		}
	}
	return -1;
}

static void before() {
	hash = d_hash_new(hash_same_fn);	
}

static void after() {
	d_hash_destroy(hash);
}

static unsigned int hash_same_fn(void *key) {
	return (unsigned int) key;
}