#ifndef PARSER_H
#define PARSER_H

#include "symbol_table.h"
#include "mnemonic.h"
#include "code.h"


struct instruct_st {
	enum instr_type type; //0 for address type, 1 for instruction type
	char *header_bin;
	union instruct_blob *blob;
};

struct instruct_c_blob {
	char *comp_bin;
	char *dest_bin;
	char *jump_bin;
};

union instruct_blob {
	char address[16];
	struct instruct_c_blob blob;
};

#define PRE_TOKEN   0
#define TOKEN_START 1
#define TOKEN_END   2

/*
* return the machine code of the given jump mnemonic
*
* @param instr: the jump mnemonic string
* @return: the binary code for the given jump mnemonic string
*/
char *jump_str2bin(char *jmp_str);

/*
* return the machine code of the given destination mnemonic
*
* @param instr: the dest mnemonic string
* @return: the binary code for the given dest mnemonic string
*/
char *dest_str2bin(char *dest_str);

/*
* return the machine code of the given compute mnemonic
*
* @param instr: the compute mnemonic string
* @return: the binary code for the given compute mnemonic string
*/
char *comp_str2bin(char *comp_str);

/*
* return the address of the symbol or direct addressing in binary 
*
* Note: Address is fetched from the symbol table and if the symbol does not 
*       exist in the table, it'll assign an address and add the symbol to 
*       the table
* 
* @param table: the symbol table to search the symbol in
* @param str  : the symbol to search for if it's not direct addressing
*               else, just simply convert the address to binary
*/
char *get_addr_bin(struct symbol_entry *table, char *str);

/*
* Break assembly instructions into tokens/fields and generate the instruct_st 
* entry for the given instruction
* 
* @param instr: the assembly language to parse
* @return     : the instruct_st entry that contains all the needed information 
*               to convert the instruction to machine code
*/
struct instruct_st *parse_instruction(struct symbol_entry *table, 
                                      char *instr_str);
#endif