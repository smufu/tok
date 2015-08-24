#ifndef BUFFER_H
#define BUFFER_H
#include "tok.h"

struct tok_Buffer_{
	void (*dispose)(tok_Buffer);
	unsigned int size;
	unsigned int read;
	unsigned int write;
	char* buf;
};

#endif