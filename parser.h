#ifndef PARSER_H
#define PARSER_H

#include "mnemonic.h"
#include "code.h"

struct instruct {
	enum instr_type type; //0 for address type, 1 for instruction type
	char *header_bin;
	struct instruct_blob *blob;
};

struct instruct_blob {
	char *comp_bin;
	char *dest_bin;
	char *jump_bin;
};

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
#endif