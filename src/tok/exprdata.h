#ifndef EXPRDATA_H
#define EXPRDATA_H
#include "tok.h"

struct tok_ExprData_ {
	void (*dispose)(tok_ExprData);
	tok_Buffer buffer;
	void* token; /* this should be tok_Token */
	void* custom;
};

tok_ExprData
tok_new_ExprData(); /* private constructor! */

#endif