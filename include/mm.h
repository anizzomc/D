/* mm.h */
#ifndef __MM_H_
#define __MM_H_

#include <stddef.h>

typedef void (*D_free_fnc_t)(void*);

void D_mm_init();

void* D_alloc(size_t size, D_free_fnc_t free_fnc);

unsigned D_retain(void* ptr);

unsigned D_release(void* ptr);

unsigned D_retain_count(void* ptr);

void D_mm_destroy();

#endif
