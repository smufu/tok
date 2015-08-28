#ifndef TOKENDEF_H
#define TOKENDEF_H
#include "tok.h"

struct tok_TokenDef_ {
	void (*dispose)(tok_TokenDef);
	unsigned int id;
	const char* label;
	tok_Expr expr;
	void* payload;
};

#endif