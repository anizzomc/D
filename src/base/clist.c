/* clist.c */
#include "base/clist.h"
#include "base/util.h"
#include "base/d_malloc.h"
#include "base/log.h"
#include <stdlib.h>


struct d_clistCDT {
	void **elements;
	size_t max_size;
	unsigned head;
	unsigned tail;  
};


d_clist d_clist_new(size_t max_size) {
	d_clist list = d_malloc(sizeof(struct d_clistCDT));
	list->elements = d_malloc(sizeof(void*)*(max_size+1));

	list->max_size = max_size + 1;
	list->head = list->tail = 0;

	return list;

}

void d_clist_put(d_clist list, void *elem){
	if(d_clist_is_full(list)) {
		ERROR("list is full");
		print_trace();
		abort();
	}

	list->elements[list->head++ % list->max_size] = elem;
}

void* d_clist_take(d_clist list) {
	if(d_clist_is_empty(list)) {
		ERROR("list is empty");
		print_trace();
		abort();
	}

	return list->elements[list->tail++ % list->max_size];
}


unsigned d_clist_is_empty(d_clist list) {
	return (list->head % list->max_size) == (list->tail % list->max_size);
}


unsigned d_clist_is_full(d_clist list) {
	return ((list->head + 1) % list->max_size) == (list->tail % list->max_size);
}

void d_clist_destroy(d_clist list) {
	free(list->elements);
	free(list);
}
