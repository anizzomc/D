#ifndef _HASH_H_
#define _HASH_H_

typedef struct hashCDT *hash_t;
typedef unsigned int (*hash_fnc_t)(void*);

hash_t hash_new(hash_fnc_t fnc);

int hash_insert(hash_t hash, void *key, void *elem);

int hash_size(hash_t hash);

void* hash_fetch(hash_t hash, void *key);

void* hash_delete(hash_t hash, void *key);

void hash_destroy(hash_t hash);

#endif