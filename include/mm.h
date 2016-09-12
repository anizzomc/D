/* mm.h */
#ifndef 

void (*D_free_fnc_t)(void *);

void *D_alloc(unsigned int size, D_free_fnc_t free_fnc);

void D_retain(void* ptr);

void D_release(void *ptr);
