#include <base/d_malloc.h>
#include <base/clist.h>
#include <mm.h>
#include <mm_pool.h>


static d_clist pools = NULL;
static d_clist current = NULL;

static D_mm_pool_conf current_config;

static void release_pool(d_clist pool);
static void add_to_current(void* ptr);
static void set_next_current();
static int is_current_full();

void D_mm_pool_init(D_mm_pool_conf config) {
	current_config = config;
	pools = d_clist_new(current_config.pools);
	current = d_clist_new(current_config.pool_length);
}

void D_mm_pool_add(void *ptr) {

	if(is_current_full()) {
		set_next_current();
	}

	add_to_current(ptr);
}

static int is_current_full() {
	return d_clist_is_full(current);
}

static void set_next_current() {

	if(d_clist_is_full(pools)) {
		release_pool(d_clist_take(pools));
	}

	d_clist_put(pools, current);

	current = d_clist_new(current_config.pool_length);	
}

static void add_to_current(void* ptr) {
	d_clist_put(current, ptr);
}

static void release_pool(d_clist pool) {
	while(!d_clist_is_empty(pool)) {
		D_mm_release(d_clist_take(pool));
	}

	d_clist_destroy(pool);
}

