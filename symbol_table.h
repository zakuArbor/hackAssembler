#include <stdlib.h>

#define BUS_SIZE 16

struct symbol_table {
	char symbol[25];
	int val;
	struct symbol_table *next;
};

/*
* Convert decimal to a 15 bit binary number
*
* @return: returns a binary representation of the decimal number. Else NULL
* 	Note: allocates a 16 character string
*/
char *dec_to_bin(struct symbol_table *symbol);