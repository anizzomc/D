/* mm.c */

#include "../cutest/CuTest.h"
#include "mm.h"

#define COUNT 124

static unsigned init = 0; 


typedef struct {
	int* i;
} zombie_t;

typedef struct {
	zombie_t **zombies;
	int size;
} swarm_t;

static void free_zombie(zombie_t* z);

static zombie_t* new_zombie(int* ptr);

static swarm_t* new_swarm(int *is, int size);
static void free_swarm(swarm_t* swarm);


static void after();
static void before();


void TestMM_alloc(CuTest *tc) {
	before();
	void* ptr = D_mm_alloc(32, NULL);

	CuAssertPtrNotNull(tc, ptr);
	CuAssertIntEquals(tc, 1, D_mm_retain_count(ptr));

	after();
}

void TestMM_retain(CuTest *tc) {
	before();
	int i = 1;

	zombie_t* z = new_zombie(&i);

	CuAssertPtrNotNull(tc, z);
	CuAssertIntEquals(tc, 1, D_mm_retain_count(z));
	int j;
	for(j = 0 ; j < COUNT ; j++) {
		D_mm_retain(z);
		CuAssertIntEquals(tc, j+2, D_mm_retain_count(z));
	}

	CuAssertIntEquals(tc, COUNT+1, D_mm_retain_count(z));

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


void TestMM_stress(CuTest *tc) {
	before();

	int j;
	int i[COUNT] = {1};

	swarm_t* s = new_swarm(i, COUNT);

	CuAssertIntEquals(tc, COUNT+2, D_mm_references_count());	

	D_mm_release(s);

	for(j = 0 ; j < COUNT ; j++) {
		CuAssertIntEquals(tc, 0, i[j]);
	}

	CuAssertIntEquals(tc, 0, D_mm_references_count());	

	after();
}



static void free_zombie(zombie_t* z) {
	*(z->i) = 0;
}

static zombie_t* new_zombie(int* i) {
	zombie_t* zombie = D_mm_alloc(sizeof(zombie_t), (D_free_fnc_t)free_zombie);
	zombie->i = i;
	return zombie;
}

static swarm_t* new_swarm(int *is, int size) {
	swarm_t* swarm = D_mm_alloc(sizeof(swarm_t), (D_free_fnc_t) free_swarm);

	swarm->size = size;
	swarm->zombies = D_mm_alloc(sizeof(zombie_t*)*size, NULL);
	int i;
	for(i = 0 ; i < size ; i++) {
		swarm->zombies[i] = new_zombie(&is[i]);
	}
	return swarm;
}

static void free_swarm(swarm_t* swarm) {
	int i;
	for(i = 0 ; i < swarm->size ; i++) {
		D_mm_release(swarm->zombies[i]);
	}
	D_mm_release(swarm->zombies);
}


static void after() {
	if(init) {
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

