/* clist.h */
#ifndef __CLIST_H_
#define __CLIST_H_

#include <stddef.h> 

typedef struct d_clistCDT *d_clist;

d_clist d_clist_new(size_t max_size);

void d_clist_put(d_clist list, void *elem);

void* d_clist_take(d_clist list);

unsigned d_clist_is_full(d_clist list);

unsigned d_clist_is_empty(d_clist list);

void d_clist_destroy(d_clist list);

#endif