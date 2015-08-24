#include "buffer.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h> /* for debuging */

void
Buffer_(tok_Buffer self) {
	free(self->buf);
	free(self);
}

tok_Buffer
tok_new_Buffer(unsigned int size) {
	tok_Buffer self = create(sizeof(struct tok_Buffer_),(void(*)(void*))Buffer_);
	self->size = size+1;
	self->buf = malloc(self->size);
	return self;
}
void
tok_buffer_resize(tok_Buffer self, unsigned int size) {
	OBJECT_CHECK(self);
	printf("not implement jet!\n");
	/* TODO: implement buffer_resize */
}
unsigned int
tok_buffer_get_size(tok_Buffer self) {
	OBJECT_CHECK(self);
	if(self->read > self->write) {
		return self->size + self->write - self->read;
	} else {
		return self->write - self->read;
	}
}
unsigned int
tok_buffer_get_max_size(tok_Buffer self) {
	OBJECT_CHECK(self);
	return self->size;
}
int
tok_buffer_is_full(tok_Buffer self) {
	OBJECT_CHECK(self);
	return self->read == (self->write +1) % self->size; 
}
int
tok_buffer_is_empty(tok_Buffer self) {
	OBJECT_CHECK(self);
	return self->read == self->write;
}
char
tok_buffer_pop(tok_Buffer self) {
	char c = self->buf[self->read];
	self->read = (self->read + 1) % self->size;
	return c;
}
void
tok_buffer_push(tok_Buffer self, char c) {
	self->buf[self->write] = c;
	self->write = (self->write + 1) % self->size;	
}
void
tok_buffer_write(tok_Buffer self, char* wb, unsigned int size) {
	unsigned int i=0;
	for(;i<size;++i)
		tok_buffer_push(self, wb[i]);
}
unsigned int
tok_buffer_read(tok_Buffer self, char* rb, unsigned int size) {
	unsigned int available = tok_buffer_get_size(self);
	unsigned int to_read = available < size ? available : size;
	unsigned int i = 0;
	for(;i<size;++i) {
		//printf("reading at position %u\n",(self->read+i)%self->size);
		rb[i] = self->buf[(self->read+i)%self->size];
	}
	return to_read;
}
void
tok_buffer_remove(tok_Buffer self, unsigned int item_count) {
	OBJECT_CHECK(self);
	self->read = (self->read + item_count) % (self->size);
}