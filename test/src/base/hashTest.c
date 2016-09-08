
#include "base/hash.h"
#include "../../cutest/CuTest.h"

static int hash_same_fn(void *key);

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
	
	after();
}

static void before() {
	hash = hash_new(hash_same_fn);	
}

static void after() {
	hash_destroy(hash);
}


static int hash_same_fn(void *key) {
	return (int) key;
}