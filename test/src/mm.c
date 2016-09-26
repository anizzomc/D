/* mm.c */

#include "../cutest/CuTest.h"
#include "mm.h"

static unsigned init = 0; 

typedef struct {
	int* i;
} zombie_t;

static void free_zombie(zombie_t* z);

static zombie_t* new_zombie(int* ptr);

static void after();
static void before();


void TestMM_alloc(CuTest *tc) {
	before();
	void* ptr = D_mm_alloc(32, NULL);

	CuAssertPtrNotNull(tc, ptr);
	CuAssertIntEquals(tc, 1, D_mm_retain_count(ptr));

	after();
}

void TestMM_relase(CuTest *tc) {
	before();
	int i = 1;

	zombie_t* z = new_zombie(&i);

	CuAssertPtrNotNull(tc, z);
	CuAssertPtrNotNull(tc, z->i);
	CuAssertIntEquals(tc, i, *(z->i));	
	
	CuAssertIntEquals(tc, 1, D_mm_retain_count(z));	
	D_mm_release(z);
	CuAssertIntEquals(tc, 0, i);	

	after();
}

static void free_zombie(zombie_t* z) {
	z->i = 0;
}

static zombie_t* new_zombie(int* i) {
	zombie_t* zombie = D_mm_alloc(sizeof(zombie_t), (D_free_fnc_t)free_zombie);
	zombie->i = i;
	return zombie;
}

static void after() {
	if(init) {
		D_mm_clean();
		D_mm_destroy();
		init = !init;
	}
}


static void before() {
	if(!init) {
		D_mm_init();
		init = !init;
	}
}

