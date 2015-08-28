CC=gcc
#or clang-3.5
CFLAGS=

build/proc: build/libtok.a src/main.c
	$(CC) $(CFLAGS) src/main.c -Lbuild -ltok -o build/proc

build/libtok.a: build/tok.o build/tok_lexer.o build/tok_buffer.o build/tok_tokendef.o build/tok_expr.o build/tok_exprdata.o
	ar -cr build/libtok.a  build/tok.o build/tok_lexer.o build/tok_buffer.o build/tok_tokendef.o build/tok_expr.o build/tok_exprdata.o

build/tok_lexer.o: build src/tok.h src/tok/tok.h src/tok/lexer.c
	$(CC) $(CFLAGS) -c src/tok/lexer.c -o build/tok_lexer.o

build/tok_buffer.o: build src/tok.h src/tok/tok.h src/tok/buffer.c
	$(CC) $(CFLAGS) -c src/tok/buffer.c -o build/tok_buffer.o

build/tok_tokendef.o: build src/tok.h src/tok/tok.h src/tok/tokendef.c
	$(CC) $(CFLAGS) -c src/tok/tokendef.c -o build/tok_tokendef.o

build/tok_expr.o: build src/tok.h src/tok/tok.h src/tok/expr.c
	$(CC) $(CFLAGS) -c src/tok/expr.c -o build/tok_expr.o

build/tok_exprdata.o: build src/tok.h src/tok/tok.h src/tok/exprdata.c
	$(CC) $(CFLAGS) -c src/tok/exprdata.c -o build/tok_exprdata.o



build/tok.o: build src/tok.h src/tok/tok.h src/tok/tok.c
	$(CC) $(CFLAGS) -c src/tok/tok.c -o build/tok.o

build:
	mkdir build

.PHONY: clean all help

clean:
	-@rm -fr build

help:
	@echo "targets:"
	@echo " - all"
	@echo " - clean"
	@echo " - proc"

proc: build/proc

all: build/proc