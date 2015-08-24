#ifndef LEXER_H
#include "tok.h"
#include "tokendef.h"

struct TokenDefList_ {
	tok_TokenDef td;
	struct TokenDefList_* next;
};
typedef struct TokenDefList_* TokenDefList;

struct tok_Lexer_ {
	void (*dispose)(tok_Lexer);
	int (*source_func)(void*);
	void* source_ptr;
	unsigned int buffer_size;
	TokenDefList tdl;
};

TokenDefList
new_TokenDefList();
void
dispose_TokenDefList(TokenDefList);

#endif