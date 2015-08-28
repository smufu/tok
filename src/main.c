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

tok_TokenDef TokenDef_factory(unsigned int id, const char* label, tok_Expr expr, void* payload) {
	tok_TokenDef td = tok_new_TokenDef();
	tok_tokendef_set_id(td, id);
	tok_tokendef_set_label(td, label);
	tok_tokendef_set_expr(td, expr);
	tok_tokendef_set_payload(td, payload);
	return td;
}

int main() {

	
	tok_Lexer l = tok_new_Lexer();
	FILE* f = fopen("file", "rb");
	tok_TokenDef td;

	assert(NULL != f);

	tok_lexer_set_source(l,(tok_SourceFunc)fgetc,f);

	tok_lexer_add_tokendef(l, TokenDef_factory(0xE01, "SPACE", tok_expr_only, " \t\n\r"));
	tok_lexer_add_tokendef(l, TokenDef_factory(0xE02, "NUM", NULL, NULL));
	tok_lexer_add_tokendef(l, TokenDef_factory(0xE03, "DOUBLE", NULL, NULL));
	tok_lexer_add_tokendef(l, TokenDef_factory(0xE04, "STRING", NULL, NULL));
	tok_lexer_add_tokendef(l, TokenDef_factory(0xE04, "EQUAL", tok_expr_strcmp, "="));

	/*tok_lexer_dump(l);*/

	tok_lexer_begin(l);

	printf("expr call: %u\n", tok_expr_call(tok_expr_strcmp, "1234598000", "12345980"));
	printf("expr call: %u\n", tok_expr_call(tok_expr_only, "\n   1234", " \n\t\r"));
	
	/*
	tok_TokenDef tokdef01 = tok_new_TokenDef();
	tok_tokendef_set_expr(tok_expr_expr);
	tok_tokendef_set_payload("#1:#2;;");
	*/

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
