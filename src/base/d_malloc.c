#include "base/d_malloc.h"
#include "base/log.h"
#include "base/util.h"
#include <stdlib.h>

void *d_malloc(unsigned int size) {
	void *ptr = malloc(size);

	if(ptr == NULL) {
		ERROR("Memory allocation failed");
		print_trace();
		abort();
	}
	return ptr;
}