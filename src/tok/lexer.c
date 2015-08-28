#include "lexer.h"
#include "tokendef.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

TokenDefList
new_TokenDefList() {
	TokenDefList tdl = malloc(sizeof(struct TokenDefList_));
	memset(tdl,0,sizeof(struct TokenDefList_));
	return tdl;
}
void
dispose_TokenDefList(TokenDefList self) {
	TokenDefList tdl_ptr1 = self;
	TokenDefList tdl_ptr2;
	while(NULL != tdl_ptr1) {
		tdl_ptr2 = tdl_ptr1->next;
		free(tdl_ptr1);
		tdl_ptr1 = tdl_ptr2;
	}
}

void Lexer_(tok_Lexer self) {
	printf("destructor for Lexer\n");
	dispose_TokenDefList(self->tdl);
	free(self);
}

tok_Lexer
tok_new_Lexer() {
	tok_Lexer self = create(sizeof(struct tok_Lexer_),(void(*)(void*))Lexer_);
	self->buffer_size = 1024;
	printf("constructor for Lexer\n");
	return self;
}

void
tok_lexer_set_source(tok_Lexer self, tok_SourceFunc f, void* p) {
	printf("setting input stream\n");
	tok_lexer_set_source_function(self, f);
	tok_lexer_set_source_pointer(self, p);
}
void
tok_lexer_set_source_function(tok_Lexer self, tok_SourceFunc f) {
	OBJECT_CHECK(self);
	self->source_func = f;
}
void
tok_lexer_set_source_pointer(tok_Lexer self, void* p) {
	OBJECT_CHECK(self);
	self->source_ptr = p;
}
tok_SourceFunc
tok_lexer_get_source_function(tok_Lexer self) {
	OBJECT_CHECK(self);
	return self->source_func;
}
void*
tok_lexer_get_source_pointer(tok_Lexer self) {
	OBJECT_CHECK(self);
	return self->source_ptr;
}
void
tok_lexer_add_tokendef(tok_Lexer self, tok_TokenDef td) {
	TokenDefList tdl = self->tdl;
	if(NULL == self->tdl) {
		self->tdl = new_TokenDefList();
		self->tdl->td = td;
	} else {
		while(NULL != tdl->next)
			tdl = tdl->next;
		tdl->next = new_TokenDefList();
		tdl->next->td = td;
	}
}
void
tok_lexer_dump(tok_Lexer self) {
	TokenDefList tdl;
	OBJECT_CHECK(self);
	tdl = self->tdl;
	printf("BEGIN TOKENDEF:\n\n");
	while(NULL != tdl) {
		tok_tokendef_dump(tdl->td);
		tdl = tdl->next;
		if(NULL != tdl)
			printf("------------\n");
	}
	printf("\n:END TOKENDEF\n");
}
void
tok_lexer_begin(tok_Lexer self) {
	/*OBJECT_CHECK(self);*/
	self->buffer_size = 32;
	tok_Buffer buf = tok_new_Buffer(self->buffer_size);
	char c, *cstr;
	cstr = malloc(self->buffer_size+1);
	unsigned int read;
	assert(NULL != cstr);
	do {
		while(!tok_buffer_is_full(buf) && EOF != (c=self->source_func(self->source_ptr))) {
			/*printf("reading %c\n",c);/**/
			tok_buffer_push(buf, c);
		}
		if(tok_buffer_is_empty(buf))
			break;

		read = tok_buffer_read(buf, cstr, tok_buffer_get_size(buf));
		cstr[read] = '\0';

		printf("buffer content: %s (%u)\n", cstr, read);

		tok_buffer_remove(buf,read);
	} while(EOF != c);
}