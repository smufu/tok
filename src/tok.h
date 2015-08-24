#ifndef TOK_H
#define TOK_H

struct tok_Lexer_;
typedef struct tok_Lexer_* tok_Lexer;
struct tok_Buffer_;
typedef struct tok_Buffer_* tok_Buffer;
struct tok_TokenDef_;
typedef struct tok_TokenDef_* tok_TokenDef;

typedef int (*tok_SourceFunc)(void*);


/* LEXER */
tok_Lexer
tok_new_Lexer();
void
tok_lexer_set_source(tok_Lexer self, tok_SourceFunc, void* file);
void
tok_lexer_set_source_function(tok_Lexer self, tok_SourceFunc);
void
tok_lexer_set_source_pointer(tok_Lexer self, void* file);
tok_SourceFunc
tok_lexer_get_source_function(tok_Lexer self);
void*
tok_lexer_get_source_pointer(tok_Lexer self);
void
tok_lexer_add_tokendef(tok_Lexer self, tok_TokenDef td);
void
tok_lexer_dump(tok_Lexer self);
void
tok_lexer_begin(tok_Lexer self);

/* BUFFER */
tok_Buffer
tok_new_Buffer(unsigned int size);
void
tok_buffer_resize(tok_Buffer self, unsigned int size);
unsigned int
tok_buffer_get_size(tok_Buffer self);
int
tok_buffer_is_full(tok_Buffer self);
int
tok_buffer_is_empty(tok_Buffer self);
unsigned int
tok_buffer_get_max_size(tok_Buffer self);
char
tok_buffer_pop(tok_Buffer self);
void
tok_buffer_push(tok_Buffer self, char c);
void
tok_buffer_write(tok_Buffer self, char*, unsigned int size);
unsigned int
tok_buffer_read(tok_Buffer self, char*, unsigned int size);
void
tok_buffer_remove(tok_Buffer self, unsigned int item_count);

tok_TokenDef
tok_new_TokenDef();
void
tok_tokendef_set_id(tok_TokenDef self, unsigned int id);
unsigned int
tok_tokendef_get_id(tok_TokenDef self);
void
tok_tokendef_set_label(tok_TokenDef self, const char* label);
const char*
tok_tokendef_get_label(tok_TokenDef self);
void
tok_tokendef_dump(tok_TokenDef self);


void
tok_delete(void*);

#endif