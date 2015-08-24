#include "tok.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>


void*
create(unsigned int size, void (*dispose_func)(void*)) {
	void* ptr = malloc(size);
	assert(NULL != ptr);
	memset(ptr,0,size);
	((Disposable)ptr)->dispose = dispose_func;
	return ptr;
}

void
tok_delete(void* ptr) {
	if(NULL == ptr) return;
	((Disposable)ptr)->dispose(ptr);
}