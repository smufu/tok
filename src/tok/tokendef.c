#include "tokendef.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

/*void
TokenDef_(tok_TokenDef self) {
	free(self);
}*/

tok_TokenDef
tok_new_TokenDef() {
	tok_TokenDef self = create(sizeof(struct tok_TokenDef_), free);
}
void
tok_tokendef_set_id(tok_TokenDef self, unsigned int id) {
	OBJECT_CHECK(self);
	self->id = id;
}
unsigned int
tok_tokendef_get_id(tok_TokenDef self) {
	OBJECT_CHECK(self);
	return self->id;
}
void
tok_tokendef_set_label(tok_TokenDef self, const char* label) {
	OBJECT_CHECK(self);
	self->label = label;
}
const char*
tok_tokendef_get_label(tok_TokenDef self) {
	OBJECT_CHECK(self);
	return self->label;
}
void
tok_tokendef_dump(tok_TokenDef self) {
	printf("ID:    %u\n", self->id);
	printf("LABEL: %s\n", self->label);
}
void
tok_tokendef_set_expr(tok_TokenDef self, tok_Expr expr) {
	OBJECT_CHECK(self);
	self->expr = expr;

}
void
tok_tokendef_set_payload(tok_TokenDef self, void* payload) {
	OBJECT_CHECK(self);
	self->payload = payload;
}