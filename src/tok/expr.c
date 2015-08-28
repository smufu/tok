#include "tok.h"
#include "buffer.h"
#include "exprdata.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int oneof(char c, const char* cstr) {
	do {
		if(*cstr == c) return 1;
	} while('\0' != *++cstr);
	return 0;
}

unsigned int tok_expr_strcmp(tok_ExprData arg) {
	
	tok_Buffer buf = tok_exprdata_get_buffer(arg);

	char* bufstr;
	char* compare = tok_exprdata_get_data(arg);
	unsigned int size = tok_buffer_get_size(buf);
	unsigned int slen = strlen(compare);
	unsigned int i=0;


	if(size < slen)
		return 0;
	if(slen < size)
		size = slen;

	bufstr = malloc(size+1);
	bufstr[tok_buffer_read(buf, bufstr, size)] = '\0';

	for(;i<size && bufstr[i] == compare[i];++i);
	free(bufstr);

	if(i < size)
		return 0;
	return i;

}


unsigned int tok_expr_not(tok_ExprData arg) {
	
}

unsigned int tok_expr_only(tok_ExprData arg) {
	tok_Buffer buf = tok_exprdata_get_buffer(arg);
	char* custom = tok_exprdata_get_data(arg);
	
	char c;
	unsigned int count = 0;
	while( '\0' != (c=tok_buffer_pop(buf)) ) {
		if(!oneof(c, custom))
			return count;
		++count;
	}
	return count;
}




unsigned int tok_expr_call(tok_Expr func, const char* buffer, void* payload) {
	tok_Buffer buf = tok_new_Buffer(strlen(buffer));
	unsigned int r;
	tok_buffer_write(buf, buffer, strlen(buffer));
	tok_ExprData ed = tok_new_ExprData();
	ed->buffer = buf;
	ed->custom = payload;
	r = func(ed);
	tok_delete(ed);
	return r;
}