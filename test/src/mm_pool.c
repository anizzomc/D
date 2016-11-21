#include <mm_pool.h>
#include <mm.h>

#include "../cutest/CuTest.h"

typedef struct {
  int* i;
} zombie_t;

static unsigned init = 0; 
static D_mm_pool_conf config = {1, 2};

static void free_zombie(zombie_t* z);
static zombie_t* new_zombie(int* ptr);


static void after();
static void before();



void TestPool_adds_doesnt_change_retain(CuTest *tc) {
  before();
  void* ptr = D_mm_alloc(8, NULL);

  CuAssertPtrNotNull(tc, ptr);

  D_mm_pool_add(ptr);

  CuAssertIntEquals(tc, 1, D_mm_retain_count(ptr));
  after();
}


void TestPool_fill_pool(CuTest *tc) {
  before();
  // Alloc 2 references, and add it to the pools.
  void* ptr1 = D_mm_pool_add(D_mm_retain(D_mm_alloc(8, NULL)));
  void* ptr2 = D_mm_pool_add(D_mm_retain(D_mm_alloc(8, NULL)));

  CuAssertIntEquals(tc, 2, D_mm_retain_count(ptr1));
  CuAssertIntEquals(tc, 2, D_mm_retain_count(ptr2));

  // Force the current be pushed to the pool
  D_mm_pool_add(D_mm_alloc(8, NULL));
  D_mm_pool_add(D_mm_alloc(8, NULL));

  // Force the pool to relase the older references.
  D_mm_pool_add(D_mm_alloc(8, NULL));

  CuAssertIntEquals(tc, 1, D_mm_retain_count(ptr1));
  CuAssertIntEquals(tc, 1, D_mm_retain_count(ptr2));  

  after();
}

void TestPool_fill_pool_free(CuTest *tc) {
    before();
  int i = 10;
  // Alloc 2 references, and add it to the pools.
  void* ptr1 = D_mm_pool_add(new_zombie(&i));
  void* ptr2 = D_mm_pool_add(D_mm_alloc(8, NULL));

  CuAssertIntEquals(tc, 1, D_mm_retain_count(ptr1));
  CuAssertIntEquals(tc, 1, D_mm_retain_count(ptr2));

  // Force the current be pushed to the pool
  D_mm_pool_add(D_mm_alloc(8, NULL));
  D_mm_pool_add(D_mm_alloc(8, NULL));

  // Force the pool to relase the older references.
  D_mm_pool_add(D_mm_alloc(8, NULL));

  CuAssertIntEquals(tc, 0, i);

  after();
}



static void after() {
  if(init) {
    D_mm_pool_destroy();
    D_mm_destroy();
    init = !init;
  }
}


static void before() {
  if(!init) {
    D_mm_init();
    D_mm_pool_init(config);
    init = !init;
  }
}





static void free_zombie(zombie_t* z) {
  *(z->i) = 0;
}

static zombie_t* new_zombie(int* i) {
  zombie_t* zombie = D_mm_alloc(sizeof(zombie_t), (D_free_fnc_t)free_zombie);
  zombie->i = i;
  return zombie;
}