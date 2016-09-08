
#include "base/hash.h"
#include "../../cutest/CuTest.h"

static int hash_same_fn(void *key);

void TestBaseHash_new(CuTest *tc) {
	hash_t hash = hash_new(hash_same_fn);
	CuAssertPtrNotNull(tc, hash);
}

static int hash_same_fn(void *key) {
	return (int) key;
}