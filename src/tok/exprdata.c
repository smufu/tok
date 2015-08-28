#include "exprdata.h"
#include <stdlib.h>
#include <assert.h>

void
ExprData_(tok_ExprData self) {
	free(self);
}

tok_ExprData
tok_new_ExprData() {
	tok_ExprData ed = create(sizeof(struct tok_ExprData_), (void (*)(void*))ExprData_);
	return ed;
}

tok_Buffer
tok_exprdata_get_buffer(tok_ExprData self) {
	OBJECT_CHECK(self);
	return self->buffer;
}

void*
tok_exprdata_get_data(tok_ExprData self) {
	OBJECT_CHECK(self);
	return self->custom;
}

void*
tok_exprdata_get_token(tok_ExprData self) {
	OBJECT_CHECK(self);
	return self->token;
}