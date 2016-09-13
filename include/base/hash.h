#ifndef _HASH_H_
#define _HASH_H_

typedef struct d_hashCDT *d_hash_t;
typedef unsigned int (*d_hash_fnc_t)(void*);

d_hash_t d_hash_new(d_hash_fnc_t fnc);

int d_hash_insert(d_hash_t hash, void *key, void *elem);

int d_hash_size(d_hash_t hash);

void* d_hash_fetch(d_hash_t hash, void *key);

void* d_hash_delete(d_hash_t hash, void *key);

void d_hash_destroy(d_hash_t hash);

#endif