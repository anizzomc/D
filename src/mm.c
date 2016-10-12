/* mm.c */
#include "mm.h"
#include "base/hash.h"
#include "base/log.h"
#include "base/util.h"
#include "base/d_malloc.h"
#include <stdlib.h>

#define INITIAL_SIZE 337

static d_hash_t references = NULL;

typedef struct {
	D_free_fnc_t free_fnc;
	unsigned count;
} slot_t;

static slot_t* assert_slot(void* ptr);
static void free_slot(void* ptr);


void D_mm_init() {
	if(references != NULL) {
		ERROR("Memory Manager already initialized!");
		print_trace();
		abort();
	}
	references = d_hash_new(NULL, NULL);
}

void* D_mm_alloc(size_t size, D_free_fnc_t free_fnc) {
	void *ret = d_malloc(size);
	slot_t* slot = d_malloc(sizeof(slot_t));

	slot->count = 1;
	slot->free_fnc = free_fnc;

	d_hash_insert(references, ret, slot);

	return ret;
}

unsigned D_mm_retain(void* ptr) {
	slot_t* slot = assert_slot(ptr);

	return ++slot->count;
}

unsigned D_mm_release(void* ptr) {
	slot_t* slot = assert_slot(ptr);
	
	if (slot->count == 1) {
		free_slot(ptr);
		return 0;
	}
	return --slot->count;
}

unsigned D_mm_retain_count(void* ptr) {
	slot_t* slot = assert_slot(ptr);
	return slot->count;
}

unsigned D_mm_references_count() {
	return d_hash_size(references);
}

unsigned D_mm_is_valid(void* ptr) {
	return d_hash_fetch(references, ptr) != NULL;
}

void D_mm_clean() {
	int lost_references, i;
	if((lost_references = d_hash_size(references)) != 0) {
		void **refs = d_hash_keys(references);

		for (i = 0 ; i < lost_references ; i++) {
			//char stringbuff[128];
			//slot_t *slot = d_hash_fetch(references, refs[i]);
			//sprintf(stringbuff,"Reference lost at %p with retain count %d", refs[i], slot->count);
			//ERROR(stringbuff);
			slot_t* slot = d_hash_delete(references, refs[i]);
			free(slot);
			free(refs[i]);	
		}
		free(refs);
	}
}

void D_mm_destroy() {
	D_mm_clean();
	references = NULL;
	free(references);
}

static void free_slot(void* ptr) {
	slot_t* slot = d_hash_delete(references, ptr);

	if(slot->free_fnc != NULL) {
		slot->free_fnc(ptr);
	} else {
		free(ptr);
	}
	free(slot);
}
static slot_t* assert_slot(void* ptr) {
	slot_t* slot = d_hash_fetch(references, ptr);
	if(slot == NULL) {
		char buffer[128];
		sprintf(buffer, "Querying an Invalid Reference 0x%p\n", ptr);
		ERROR(buffer);
		print_trace();
		abort();
	}
	return slot;
}
