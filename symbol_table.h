#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#define BUS_SIZE 16
#define SYMBOL_SIZE 50
#define PREDEF_SYMBOL_NUM 22

struct symbol_entry {
	char symbol[SYMBOL_SIZE];
	int val;
	struct symbol_entry *next;
};

struct symbol_entry *table;

/*
* Convert decimal to a 15 bit binary number
*
* @param symbol: the address in base 10 we wish to convert to binary
* @return: returns a binary representation of the decimal number. Else NULL
*    Note: allocates a 16 character string
*/
char *dec_to_bin(int dec_num);

/*
* Display all entries in the symbol table
* @param entry: the first entry in the symbol table
*/
void print_sym_table(struct symbol_entry *entry);

/*
* Destroys (frees) all entries in the table
*
* @param: an entry of the symbol table
*/
void destroy_table (struct symbol_entry *entry);

/*
* Creates an entry to add to the symbol table
*
* Note: You are responsible to add the entry to the symbol table. This function
*       does not add the symbol to the table, it just creates an entry in which
*       can be plugged into the table
*
* @param symbol: the name of the symbol
* @param val   : the address of the symbol
* @return      : returns the pointer of the new entry
* @error       : returns NULL
*
*/
struct symbol_entry *create_sym_entry(char *symbol, int val);

/*
* Return the decimal address value associated with the symbol if it exists.
* Else return -1
*
* @param entry : the head of the symbol table
* @param symbol: the symbol to find in the table 
* @return      : return the decimal address value associated with the symbol 
*                if it exists. Else return -1
*/
int find_symbol(struct symbol_entry *entry, char *symbol);

/*
* Inserts a non predefined symbol to the symbol table
*
* @param table : the symbol table
* @param symbol: the symbol to add to the table
* @param val   : the value (address) to assign to the symbol
*                if no value is given (i.e. val = -1), the next free address
*                will be assigned to the symbol
* @return      : returns the pointer of the symbol table if success
* @error       : return NULL and the symbol table will be destroyed.
*                The programmer is expected to terminate the program since the
*                assembler cannot continue assembling the machine code 
*/
struct symbol_entry *insert_to_table(struct symbol_entry *table, 
                                     char *symbol, 
                                     int val);

/*
* Initializes all the pre-defined tables to the symbol table
*
* Note: It is the programmer's responsibility to free the table using 
*       destroy_table when the table is no longer needed
*
* @return: the first entry in the symbol table
* @error : returns NULL and frees up the symbol table
*/
struct symbol_entry *init_sym_table();
#endif