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


struct instruct_a_blob {
	char address[BUS_SIZE];
	int  is_label;
};

struct instruct_c_blob {
	char comp_bin[COMP_SIZE + 2]; //+1 for the a-bit to indicate whether it
                                  // tries to use the M register
	char dest_bin[DEST_SIZE + 1];
	char jump_bin[JUMP_SIZE + 1];
};

union instruct_blob {
	struct instruct_a_blob blob_a;
	struct instruct_c_blob blob_c;
};

struct instruct_bin_entry {
	char instr[BUS_SIZE + 1];
	struct instruct_bin_entry *next;
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
* @param val  : the value to assign to the symbol if symbol does not
                presently exist in the table
*/
char *get_addr_bin(struct symbol_entry *table, char *str, int val);


/*
* Parse instruction as an address instruction and return the needed information
* to be able to construct the machine code instruction
*
* @param table    : the symbol table to search or insert the symbol into
* @param instr_str: the address instruction but stripped of the character that
*                   identifies the instruction as an address type 
*                   (i.e. rm '@'' or '(' character). Though if instruction is
                    a label, it'll end with a ')'
* @return         : allocates an instruct struct and populate it with the 
*                   appropriate information to be able to construct the
*                   machine code later
* @return         : returns NULL if there is an error that occurs
*/
struct instruct_st *parse_instruction_a(struct symbol_entry *table, 
                                        struct instruct_st * instruct, 
                                        const char *instr_str);

/*
* Parse instruction as compute instruction and return the needed information
* to be able to construct the machine code instruction
*
* @param table    : the symbol table to search or insert the symbol into
* @param instr_str: the address instruction
* @return         : allocates an instruct struct and populate it with the 
*                   appropriate information to be able to construct the
*                   machine code later
* @return         : returns NULL if there is an error that occurs
*/
struct instruct_st *parse_instruction_c(struct symbol_entry *table, 
                                        struct instruct_st * instruct,
                                        const char *instr_str);


/*
* Break assembly instructions into tokens/fields and generate the instruct_st 
* entry for the given instruction
* 
* @param instr: the assembly language to parse
* @return     : the instruct_st entry that contains all the needed information 
*               to convert the instruction to machine code
*/
struct instruct_st *parse_instruction(struct symbol_entry *table, 
                                      struct instruct_st * instruct,
                                      const char *instr_str);

/*
* Destroy (free) instruct and its associated information
* @param instruct: a struct that contains all the information about the
*                  instruction to construct the machine code
*/
void destroy_instruct_st(struct instruct_st *instruct);

/*
* Display the instruction details
* 
* @param instruct: a struct that contains all the information about the
*                  instruction to construct the machine code
*/
void print_instruct_st(struct instruct_st *instruct);

/*
*
*/
char *assemble_instruct(struct instruct_st *instruct, char *instruct_bin);

/*
*
*/
void destroy_instructions(struct instruct_bin_entry *instr);


/*
*
*/
struct instruct_bin_entry *parse_instructions(struct symbol_entry *table, 
                                              FILE *fp);

#endif