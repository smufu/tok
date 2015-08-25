#ifndef TOKENDEF_H
#define TOKENDEF_H
#include "tok.h"

struct tok_TokenDef_ {
	void (*dispose)(tok_TokenDef);
	unsigned int id;
	const char* label;
	/*int (*match)(const tok_Buffer, void* this_will_be_a_token);*/
};

#endif