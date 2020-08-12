#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "parser.h"

char *jump_str2bin(char *jmp_str) {
	if (!jmp_str) {
		return NULL;
	}
	else if (strcmp(jmp_str, "NULL_J") == 0) {
		return NULL_J;
	}
	else if (strcmp(jmp_str, "JGT") == 0) {
		return JGT;
	}
	else if (strcmp(jmp_str, "JEQ") == 0) {
		return JEQ;
	}
	else if (strcmp(jmp_str, "JGE") == 0) { 
		return JGE;
	}
	else if (strcmp(jmp_str, "JLT") == 0) {
		return JLT;
	}
	else if (strcmp(jmp_str, "JNE") == 0) {
		return JNE;
	}
	else if (strcmp(jmp_str, "JLE") == 0) {
		return JLE;
	}
	else if (strcmp(jmp_str, "JMP") == 0) {
		return JMP;
	}
	return NULL;
}

char *dest_str2bin(char *dest_str) {
	if (!dest_str) {
		return NULL;
	}
	else if (strcmp(dest_str, "NULL_DEST") == 0) {
		return NULL_DEST;
	}
	else if (strcmp(dest_str, "M_DEST") == 0) {
		return M_DEST;
	}
	else if (strcmp(dest_str, "D_DEST") == 0) {
		return D_DEST;
	}
	else if (strcmp(dest_str, "MD_DEST") == 0) {
		return MD_DEST;
	}
	else if (strcmp(dest_str, "A_DEST") == 0) {
		return A_DEST;
	}
	else if (strcmp(dest_str, "AM_DEST") == 0) {
		return AM_DEST;
	}
	else if (strcmp(dest_str, "AD_DEST") == 0) {
		return AD_DEST;
	}
	else if (strcmp(dest_str, "AMD_DEST") == 0) {
		return AMD_DEST;
	}
	return NULL;
}

char *comp_str2bin(char *comp_str) {
	if (!comp_str) {
		return NULL;
	}
	else if (strcmp(comp_str, "ZERO") == 0) {
		return ZERO;
	}
	else if (strcmp(comp_str, "ONE") == 0) {
		return ONE;
	}
	else if (strcmp(comp_str, "NEG_ONE") == 0) {
		return NEG_ONE;
	}
	else if (strcmp(comp_str, "D") == 0) {
		return D;
	}
	else if (strcmp(comp_str, "A") == 0) {
		return A;
	}
	else if (strcmp(comp_str, "NOT_D") == 0) {
		return NOT_D;
	}
	else if (strcmp(comp_str, "NOT_A") == 0) {
		return NOT_A;
	}
	else if (strcmp(comp_str, "MINUS_D") == 0) {
		return MINUS_D;
	}
	else if (strcmp(comp_str, "MINUS_A") == 0) {
		return MINUS_A;
	}
	else if (strcmp(comp_str, "D_PLUS_1") == 0) {
		return D_PLUS_1;
	}
	else if (strcmp(comp_str, "A_PLUS_1") == 0) {
		return A_PLUS_1;
	}
	else if (strcmp(comp_str, "D_MINUS_1") == 0) {
		return D_MINUS_1;
	}
	else if (strcmp(comp_str, "A_MINUS_1") == 0) {
		return A_MINUS_1;
	}
	else if (strcmp(comp_str, "D_PLUS_A") == 0) {
		return D_PLUS_A;
	}
	else if (strcmp(comp_str, "D_MINUS_A") == 0) {
		return D_MINUS_A;
	}
	else if (strcmp(comp_str, "A_MINUS_D") == 0) {
		return A_MINUS_D;
	}
	else if (strcmp(comp_str, "D_AND_A") == 0) {
		return D_AND_A;
	}
	else if (strcmp(comp_str, "D_OR_A") == 0) {
		return D_OR_A;
	}

	//a = 1
	else if (strcmp(comp_str, "M") == 0) {
		return M;
	}
	else if (strcmp(comp_str, "NOT_M") == 0) {
		return NOT_M;
	}
	else if (strcmp(comp_str, "MINUS_M") == 0) {
		return MINUS_M;
	}
	else if (strcmp(comp_str, "M_PLUS_1") == 0) {
		return M_PLUS_1;
	}
	else if (strcmp(comp_str, "M_MINUS_1") == 0) {
		return M_MINUS_1;
	}
	else if (strcmp(comp_str, "D_PLUS_M") == 0) {
		return D_PLUS_M;
	}
	else if (strcmp(comp_str, "D_MINUS_M") == 0) {
		return D_MINUS_M;
	}
	else if (strcmp(comp_str, "M_MINUS_D") == 0) {
		return M_MINUS_D;
	}
	else if (strcmp(comp_str, "D_AND_M") == 0) {
		return D_AND_M;
	}
	else if (strcmp(comp_str, "D_OR_M") == 0) {
		return D_OR_M;
	}
	return NULL;
}

char *get_addr_bin(struct symbol_entry *table, char *str) {
	int i;
	int val = -1;
	
	if (!str) {
		return NULL;
	}

	if (isdigit(str[0])) {
		//check if valid decimal address
		for (i = 0; i < strlen(str); i++) {
			if (!isdigit(str[i])) {
				fprintf(stderr, "In line: %s\nNot a valid numeric address\n",
					str);
				return NULL;
			}
		}
		val = strtol(str, NULL, 10);
	}
	else if (isalpha(str[0])) {
		//check if valid variable or label name
		for (i = 0; i < strlen(str); i++) {
			if (!isalnum(str[i]) && str[i] != '_' && str[i] != '.') {
				printf("test %c - %d\n", str[i], !isalnum(str[i])&& str[i] != '_' && str[i] != '.');
				return NULL;
			}
		}

		//check if symbol exists in the symbol table
		if ((val = find_symbol(table, str)) < 0) {
			//enter symbol to the table
			if (!insert_to_table(table, str, -1)) {
				return NULL;
			}
			val = find_symbol(table, str);
		}
	}
	printf("val: %d\n", val);
	if (val > 0) {
		return dec_to_bin(val);
	}
	return NULL;
}

struct instruct *parse_instruction_a(struct symbol_entry *table, char *instr_str) {
	struct instruct_st *instruct;
	char symbol[SYMBOL_SIZE];
	int i, len = 0;
	for (i = 0; i < strlen(instr_str); i++) {
		if (instr_str[i] == ' ' || instr_str[i] == ')') {
			break;
		}
		symbol[len] = instr_str[i];
		len++;
	}
	symbol[len] = '\0';

	if (len == 0) {
		fprintf(stderr, "Error: Need a valid symbol or address name\n");
	}

	if ( ! ( instruct = malloc(sizeof(struct instruct_st)) ) ) {
		perror("malloc");
		return NULL;
	}

	if ( ! ( instruct->blob = malloc(sizeof(union instruct_blob)) ) ) {
		perror("malloc");
		return NULL;
	}

	char *addr;
	addr = get_addr_bin(table, symbol);

	if (addr) {
		printf("%s\n", addr);
	}
	return NULL;

	//instruct->type = type;
	//instruct->header_bin = A_HEADER;
	//strncpy(instruct->blob->address, , 15);
}

struct instruct_st *parse_instruction(struct symbol_entry *table, char *instr_str) {
	int i = 0;
	int start = 0;//keeps track of the first position of the token being parsed
	//int state = PRE_TOKEN;
	enum instr_type type = INVALID;
	struct instruct_st *instruct = NULL;
	
	//find what type of instruction
	for (i = 0; i < strlen(instr_str); i++) {
		if (instr_str[i] == ' ') {
			continue;
		}
		else if (instr_str[i] == '@' || instr_str[i] == '(') {
			start = i + 1;
			type = A_INSTR;
			break;
		}
		else {
			start = i;
			type  = C_INSTR;
			break;
		}
	}

	if (type == A_INSTR) {
		parse_instruction_a(table, instr_str+start);
	}
	else if (type == C_INSTR) {
		//instruct = parse_c_instr(instr_str);
	}
	else {
		return NULL;
	}
	return instruct;
}

int main () {
	//printf("%s\n", comp_str2bin("D_MINUS_M"));
	printf(get_addr_bin(init_sym_table(), "PIKA"));
	return 0;
}