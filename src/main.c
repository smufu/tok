#include "tok.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>

unsigned int print_buffer(tok_Buffer buf) {
	unsigned int size = tok_buffer_get_size(buf);
	char* cstr = malloc(size+1);
	unsigned int used = tok_buffer_read(buf, cstr, size);
	cstr[size] = '\0';
	printf("%s(%u)\n", cstr, used);
	free(cstr);
	return used;
}
void dump_buffer(tok_Buffer buf) {
	tok_buffer_remove(buf, print_buffer(buf));
}


int main() {

	
	tok_Lexer l = tok_new_Lexer();
	FILE* f = fopen("file", "rb");
	tok_TokenDef td;

	assert(NULL != f);

	tok_lexer_set_source(l,(tok_SourceFunc)fgetc,f);

	td = tok_new_TokenDef();
	tok_tokendef_set_id(td, 0xE01);
	tok_tokendef_set_label(td, "SPACE");
	tok_lexer_add_tokendef(l, td);

	td = tok_new_TokenDef();
	tok_tokendef_set_id(td, 0xE02);
	tok_tokendef_set_label(td, "NUM");
	tok_lexer_add_tokendef(l, td);

	td = tok_new_TokenDef();
	tok_tokendef_set_id(td, 0xE03);
	tok_tokendef_set_label(td, "STRING");
	tok_lexer_add_tokendef(l, td);

	

	tok_lexer_dump(l);

	tok_lexer_begin(l);

	/* destructor is always virtual on tok_* objects */
	tok_delete(l);
	fclose(f);
	

	/*
	char* cstr = "hallo welt";
	tok_Buffer buf = tok_new_Buffer(12);

	tok_buffer_write(buf, cstr, 5);

	print_buffer(buf);
	tok_buffer_write(buf, cstr+5, 5);

	dump_buffer(buf);
	tok_buffer_push(buf, 'f');
	tok_buffer_push(buf, 'o');
	tok_buffer_push(buf, 'o');
	print_buffer(buf);
	*/
	
	return 0;

}
