CC = gcc
CFLAGS += -std=gnu11 -Wall -Werror -DNDEBUG -g
LIB_OBJ = symbol_table.o parser.o


all: assembler

parser: parser.c symbol_table.c
	$(CC) -o $@ $^ $(CFLAGS) -fsanitize=address

assembler: assembler.c symbol_table.c parser.c
	$(CC) -o $@ $^ $(CGLAGS) -fsanitize=address -lasan

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o *.gch assembler parser
