/**
 * @mainpage tok Lexer
 * 
 * @section nameing conventions
 * 1) Every symbol begins with the namespace tok_.\n
 * 2) All type begin with a capitalised letter like tok_Buffer.\n
 * 3) all member functions of a type are written in lowercase like:
 *    void tok_buffer_get_stuff(tok_Buffer self);\n
 * 4) execpt the constructor wo is named like tok_new_<Type> : tok_new_Buffer(128)
 * 5) every private symbol ends with _ like struct tok_Buffer_.
 *    you can use them wenn they are exposed, but the internals of these structs will change!\n
 * 6) the destructor goes like this tok_delete(<obj>);\n
 * 7) you may want to create factory functions like:
 *    tok_SomeUglyType someuglytype_factory(void* a, void* loot, void* of, void* args);\n
 *
 */

#ifndef TOK_H
#define TOK_H
/**
 * @file tok.h
 * @brief contans everything you need to use the api.
 * @details this file contains all public class members, and class types.
 *          note that every class witout a constructor does NOT have a public destructor
 *          they will be given to you by out system and destroyed afterwards.
 *          Also note that every class with a constructor like tok_new_<TypeName>(void);
 *          uses tok_delete(<tok_object>); to delete the object.
 *          if we had the following types:
 *          	tok_ObjectX
 *          	tok_ObjectY (extends tok_ObjectX)
 *          the code would look like this:
 *          
 *          tok_ObjectY obj = tok_new_ObjectY();
 *         
 *          // ... do stuff with obj:
 *          tok_objecty_some_function(obj, "foobar"); // functions are always lowercase except the construtor.
 *          
 *          tok_delete(obj);
 *          
 *          // you could even do:
 *          tok_delete( (tok_ObjectX)obj );
 *          // because the destructor is always virtual.
 * 
 */


/**
 * @class Lexer
 * @brief This class does all the magic
 */
struct tok_Lexer_;
typedef struct tok_Lexer_* tok_Lexer;
/**
 * @class Buffer
 * @brief A simple ring buffer 
 */
struct tok_Buffer_;
typedef struct tok_Buffer_* tok_Buffer;
struct tok_TokenDef_;
typedef struct tok_TokenDef_* tok_TokenDef;
struct tok_ExprData_;
typedef struct tok_ExprData_* tok_ExprData;
struct tok_Token_;
typedef struct tok_Token_* tok_Token;

typedef int (*tok_SourceFunc)(void*);
typedef unsigned int (*tok_Expr)(tok_ExprData);

unsigned int tok_expr_strcmp(tok_ExprData arg);
unsigned int tok_expr_only(tok_ExprData arg);
unsigned int tok_expr_not(tok_ExprData arg);

/**
 * @brief call expr for debuing
 */
unsigned int tok_expr_call(tok_Expr func, const char* buffer, void* payload);

/**
 * @memberof Lexer
 */
tok_Lexer
tok_new_Lexer();
/**
 * @memberof Lexer
 * @brief sets SourceFunc and payload.
 * 
 * @param func function pointer of type SourceFunc as callback.
 * @param file payload, this pointer fill be given to func.
 */
void
tok_lexer_set_source(tok_Lexer self, tok_SourceFunc func, void* file);
void
/**
 * @memberof Lexer
 * @brief sets SourceFunc see set_source...
 * @details [long description]
 * 
 * @param func function pointer of type SourceFunc as callback.
 */
tok_lexer_set_source_function(tok_Lexer self, tok_SourceFunc func);
/**
 * @memberof Lexer
 * @brief sets payload for SourceFunc see set_source...
 * @details [long description]
 * 
 * @param file payload, this pointer fill be given to SourceFunc.
 */
void
tok_lexer_set_source_pointer(tok_Lexer self, void* file);
/**
 * @memberof Lexer
 * @brief returns SourceFunc function
 */
tok_SourceFunc
tok_lexer_get_source_function(tok_Lexer self);
/**
 * @memberof Lexer
 * @brief returns SourceFunc paiload
 */
void*
tok_lexer_get_source_pointer(tok_Lexer self);
/**
 * @memberof Lexer
 */
void
tok_lexer_add_tokendef(tok_Lexer self, tok_TokenDef td);
/**
 * @memberof Lexer
 * @brief dumps all TokenDef's
 */
void
tok_lexer_dump(tok_Lexer self);
/**
 * @memberof Lexer
 * @brief begins parsing
 */
void
tok_lexer_begin(tok_Lexer self);



/**
 * @memberof Buffer
 * @param int size of buffer in bytes
 */
tok_Buffer
tok_new_Buffer(unsigned int size);
/**
 * @memberof Buffer
 * @brief resizes the buffer
 * @details argument size bust be bigger or equal get_size();
 * 
 * @param int size in bytes
 */
void
tok_buffer_resize(tok_Buffer self, unsigned int size);
/**
 * @memberof Buffer
 * @brief returns current buffer size.
 * @details to get absolut buffer size use get_max_size
 *          you can shrink buffer to current size with resize(get_size());
 */
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
tok_buffer_write(tok_Buffer self, const char*, unsigned int size);
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
tok_tokendef_set_expr(tok_TokenDef self, tok_Expr expr);
void
tok_tokendef_set_payload(tok_TokenDef self, void* payload);

tok_Buffer
tok_exprdata_get_buffer(tok_ExprData self);
void*
tok_exprdata_get_token(tok_ExprData self);
void*
tok_exprdata_get_data(tok_ExprData self);

void
tok_delete(void*);

#endif