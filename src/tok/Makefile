CC=gcc
CFLAGS=-shared -fPIC
LFLAGS=
DIR=..
OBJ=$(DIR)/tok/buffer.o $(DIR)/tok/lexer.o $(DIR)/tok/tok.o

.PHONY: clean help

static:	$(DIR)/libtok.a
shared: $(DIR)/libtok.so
all: static shared

$(DIR)/libtok.so: $(OBJ)
	@echo -n "[L]  libtok.so: "
	$(CC) -Wl,$(LFLAGS:=,) -o $(DIR)/libtok.so $(OBJ)

$(DIR)/libtok.a: $(OBJ)
	@echo -n "[A]  libtok.a: "
	ar -cr $(DIR)/libtok.a $(OBJ)

$(DIR)/tok/buffer.o: buffer.c
	@echo -n "[C]  buffer.o: "
	$(CC) -c $(CFLAGS) buffer.c -o $(DIR)/tok/buffer.o

$(DIR)/tok/lexer.o: lexer.c
	@echo -n "[C]  lexer.o: "
	$(CC) -c $(CFLAGS) lexer.c -o $(DIR)/tok/lexer.o

$(DIR)/tok/tok.o: tok.c
	@echo -n "[C]  tok.o: "
	$(CC) -c $(CFLAGS) tok.c -o $(DIR)/tok/tok.o

clean:
	-@rm -fr $(DIR)/tok/*.o $(DIR)/libtok.a $(DIR)/libtok.so
help:
	@echo "targets:"
	@echo " - clean"
	@echo " - shared"
	@echo " - static"
	@echo " - all"
