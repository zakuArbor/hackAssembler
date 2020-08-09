#include <stdlib.h>

#define BUS_SIZE 16
#define SYMBOL_SIZE 25

struct symbol_table {
	char symbol[SYMBOL_SIZE];
	int val;
	struct symbol_table *next;
};

struct symbol_table *table;

/*
* Convert decimal to a 15 bit binary number
*
* @return: returns a binary representation of the decimal number. Else NULL
* 	Note: allocates a 16 character string
*/
char *dec_to_bin(struct symbol_table *symbol);

/*
* Display all entries in the symbol table
* @param entry: the first entry in the symbol table
*/
void print_sym_table(struct symbol_table *entry)

/*
* Destroys (frees) all entries in the table
*
* @param: an entry of the symbol table
*/
void destroy_table (struct symbol_table *entry);

/*
* Initializes all the pre-defined tables to the symbol table
*
* @return: the first entry in the symbol table
* @error: returns NULL and frees up the symbol table
*/
struct symbol_table *init_sym_table();
