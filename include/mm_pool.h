#ifndef __MM_POOL_H_
#define __MM_POOL_H_

typedef struct {
	size_t pools;
	size_t pool_length;
} D_mm_pool_conf;

void D_mm_pool_init(D_mm_pool_conf config);

void D_mm_pool_add(void* ptr);

#endif