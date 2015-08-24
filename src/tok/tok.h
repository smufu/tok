#ifndef TOK_H
#include "../tok.h"
#define OBJECT_CHECK(obj) assert(NULL != ((Disposable)(obj))->dispose)

struct Disposable_ {
	void (*dispose)(void*);
};
typedef struct Disposable_* Disposable;

void*
create(unsigned int size, void (*dispose_func)(void*));
void
tok_delete(void* ptr);

#endif