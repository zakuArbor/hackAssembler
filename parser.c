#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "parser.h"

char *jump_str2bin(char *jmp_str) {
	if (!jmp_str || strlen(jmp_str) == 0) {
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
	if (!dest_str || strlen(dest_str) == 0) {
		return NULL_DEST;
	}
	else if (strcmp(dest_str, "M") == 0) {
		return M_DEST;
	}
	else if (strcmp(dest_str, "D") == 0) {
		return D_DEST;
	}
	else if (strcmp(dest_str, "MD") == 0) {
		return MD_DEST;
	}
	else if (strcmp(dest_str, "A") == 0) {
		return A_DEST;
	}
	else if (strcmp(dest_str, "AM") == 0) {
		return AM_DEST;
	}
	else if (strcmp(dest_str, "AD") == 0) {
		return AD_DEST;
	}
	else if (strcmp(dest_str, "AMD") == 0) {
		return AMD_DEST;
	}
	return NULL;
}

char *comp_str2bin(char *comp_str) {
	if (!comp_str) {
		return NULL;
	}
	else if (strcmp(comp_str, "0") == 0) {
		return ZERO;
	}
	else if (strcmp(comp_str, "1") == 0) {
		return ONE;
	}
	else if (strcmp(comp_str, "-1") == 0) {
		return NEG_ONE;
	}
	else if (strcmp(comp_str, "D") == 0) {
		return D;
	}
	else if (strcmp(comp_str, "A") == 0) {
		return A;
	}
	else if (strcmp(comp_str, "!D") == 0) {
		return NOT_D;
	}
	else if (strcmp(comp_str, "!A") == 0) {
		return NOT_A;
	}
	else if (strcmp(comp_str, "-D") == 0) {
		return MINUS_D;
	}
	else if (strcmp(comp_str, "-A") == 0) {
		return MINUS_A;
	}
	else if (strcmp(comp_str, "D+1") == 0) {
		return D_PLUS_1;
	}
	else if (strcmp(comp_str, "A+1") == 0) {
		return A_PLUS_1;
	}
	else if (strcmp(comp_str, "D-1") == 0) {
		return D_MINUS_1;
	}
	else if (strcmp(comp_str, "A-1") == 0) {
		return A_MINUS_1;
	}
	else if (strcmp(comp_str, "D+A") == 0) {
		return D_PLUS_A;
	}
	else if (strcmp(comp_str, "D-A") == 0) {
		return D_MINUS_A;
	}
	else if (strcmp(comp_str, "A-D") == 0) {
		return A_MINUS_D;
	}
	else if (strcmp(comp_str, "D&A") == 0) {
		return D_AND_A;
	}
	else if (strcmp(comp_str, "D|A") == 0) {
		return D_OR_A;
	}

	//a = 1
	else if (strcmp(comp_str, "M") == 0) {
		return M;
	}
	else if (strcmp(comp_str, "!M") == 0) {
		return NOT_M;
	}
	else if (strcmp(comp_str, "-M") == 0) {
		return MINUS_M;
	}
	else if (strcmp(comp_str, "M+1") == 0) {
		return M_PLUS_1;
	}
	else if (strcmp(comp_str, "M-1") == 0) {
		return M_MINUS_1;
	}
	else if (strcmp(comp_str, "D+M") == 0) {
		return D_PLUS_M;
	}
	else if (strcmp(comp_str, "D-M") == 0) {
		return D_MINUS_M;
	}
	else if (strcmp(comp_str, "M-D") == 0) {
		return M_MINUS_D;
	}
	else if (strcmp(comp_str, "D&M") == 0) {
		return D_AND_M;
	}
	else if (strcmp(comp_str, "D|M") == 0) {
		return D_OR_M;
	}
	return NULL;
}

char *get_addr_bin(struct symbol_entry *table, char *str) {
	int i;
	int val = -1;
	
	if (!str) {
		fprintf(stderr, "get_addr_bin: address is NULL\n");
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
		printf("str: %s\n", str);
	}
	else if (isalpha(str[0])) {
		//check if valid variable or label name
		for (i = 0; i < strlen(str); i++) {
			if (str[i] == ')') {
				str[i] = '\0';
				break;
			}
			if (!isalnum(str[i]) && str[i] != '_' && str[i] != '.') {
				fprintf(stderr, "Not a valid symbol name\n");
				return NULL;
			}
		}

		//check if symbol exists in the symbol table
		if ((val = find_symbol(table, str)) < 0) {
			printf("check val: %d\n", val);
			//enter symbol to the table
			if (!insert_to_table(table, str, -1)) {
				printf("rip\n");	
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

struct instruct_st *parse_instruction_a(struct symbol_entry *table, 
                                        const char *instr_str) 
{
	struct instruct_st *instruct;
	char symbol[SYMBOL_SIZE];
	char *addr;
	int i, len = 0, is_label = 0;

	for (i = 0; i < strlen(instr_str); i++) {
		if (instr_str[i] == ' ' || instr_str[i] == '\r' || 
            instr_str[i] == '\n') 
		{
			break;
		}
        else if (instr_str[i] == ')') {
            is_label = 1;
            break;
        }
		symbol[len] = instr_str[i];
		len++;
	}
	symbol[len] = '\0';

	if (len == 0) {
		fprintf(stderr, "Error: Need a valid symbol or address name\n");
	}

	if ( ! (addr = get_addr_bin(table, symbol)) ) {
		return NULL;
	}

	if ( ! ( instruct = malloc(sizeof(struct instruct_st)) ) ) {
		perror("malloc");
		return NULL;
	}

	if ( ! ( instruct->blob = malloc(sizeof(union instruct_blob)) ) ) {
		free(instruct);
		perror("malloc");
		return NULL;
	}
	
	instruct->type = A_INSTR;
	instruct->header_bin = A_HEADER;
    instruct->blob->blob_a.is_label = is_label;
	strncpy(instruct->blob->blob_a.address, addr, 15);
	return instruct;
}

char *tokenize_instruction(char *instr_str, 
                          int dest_pos,
                          int comp_pos,
                          int jump_pos) 
{
    if (!instr_str || !(*instr_str)) {
        fprintf(stderr, "tokenize_instruction: Failed to tokenize. " \
                        "Instruction is NULL\n");
        return NULL;
    }

    printf("testing: %s\n", instr_str);
    instr_str[dest_pos] = '\0';
    printf("test 2\n");
    instr_str[comp_pos] = '\0';
    printf("test pika: %d\n", jump_pos);
    instr_str[jump_pos] = '\0';

    return instr_str;
}

struct instruct_st *parse_instruction_c(struct symbol_entry *table, 
                                        const char *instr_str_orig) 
{
    struct instruct_st *instruct = NULL;
    int i = 0;
    int dest_pos   = 0,    comp_pos = 0,    jump_pos = 0;
    int dest_start = -1, comp_start = -1, jump_start = -1, tmp_start;
    int state      = 0; //0: dest  1: comp  2: jump 
    char instr_str[INSTR_SIZE];
    char *jump_bin;
    char *dest_bin;
    char *comp_bin;

    if (!instr_str_orig) {
        return NULL;
    }
    strncpy(instr_str, instr_str_orig, strlen(instr_str_orig) % INSTR_SIZE);
    instr_str[strlen(instr_str_orig)] = '\0';

    for (i = 0; i < strlen(instr_str); i++) {
        switch(state) {
            case 0: //search for destination token if exists
                if (instr_str[i] == '=') {
                    dest_pos = i;
                    state = 1; //search for compute token
                }
                else if (dest_start < 0 && isalpha(instr_str[i])) {
                    dest_start = i;
                }
                else if (instr_str[i] == '/') { //Ignore Comments
                    return NULL;
                }
                //no break; destination is optional
            case 1: //search for compute token if exists
                if (instr_str[i] == ';') {
                    comp_pos = i;
                    state = 2; //search for jump token

                    if (state == 0) { //no destination
                        comp_start = tmp_start;
                    }
                }
                else if (comp_start < 0 && isalpha(instr_str[i])) {
                    if (state == 1) {
                        comp_start = i;
                    }
                    else {
                        tmp_start = i;
                    }
                }
                break; //breaks for the dest_post and comp_pos
            case 2: ///search for Jump token
                if (instr_str[i] == ' ' || instr_str[i] == '\r' || instr_str[i] == '\n') {
                    jump_pos = i;
                    state++;
                    i = strlen(instr_str); //force loop to end
                }
                else if (jump_start < 0 && isalpha(instr_str[i])) {
                    jump_start = i;
                }
                else if (i + 1 == strlen(instr_str)) {
                    jump_pos = i+ 1;
                    state++;
                    i = strlen(instr_str); //force loop to end
                }
                break;
            default:
                //should never go here
                jump_pos = i; //force loop to end
                break;
        }
    }

    if (jump_pos < 2) { //2 characters is the shortest the instruction can be
        jump_pos = strlen(instr_str);
        jump_start = jump_pos;
    }

    tokenize_instruction(instr_str, dest_pos, comp_pos, jump_pos);

    if ( !(dest_bin = dest_str2bin(instr_str+dest_start)) ) {
        fprintf(stderr, "parse_instruction_c: destination token is invalid\n");
        return NULL;
    }

    if ( !(comp_bin = comp_str2bin(instr_str+comp_start)) ) {
        fprintf(stderr, "parse_instruction_c: computation token is invalid\n");
        return NULL;
    }

    if ( !(jump_bin = jump_str2bin(instr_str+jump_start)) ) {
        fprintf(stderr, "parse_instruction_c: jump token is invalid\n");
        return NULL;
    }

    if (! (instruct = malloc(sizeof(struct instruct_st))) ) {
        perror("malloc");
        return NULL;
    }

    if (! (instruct->blob = (union instruct_blob *) malloc(sizeof(union instruct_blob))) ) {
        perror("malloc");
        return NULL;
    }
    
    instruct->type                  = C_INSTR;
    instruct->header_bin            = C_HEADER;
    instruct->blob->blob_c.dest_bin = dest_bin;
    instruct->blob->blob_c.comp_bin = comp_bin;
    instruct->blob->blob_c.jump_bin = jump_bin;
    return instruct;
}

struct instruct_st *parse_instruction(struct symbol_entry *table, 
                                      const char *instr_str) {
	int i = 0;
	int start = 0;//keeps track of the first position of the token being parsed
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

	instr_str += start; //move pointer to the first non-blank or the first character of the instruction/symbol

	if (type == A_INSTR) {
		instruct = parse_instruction_a(table, instr_str);
	}
	else if (type == C_INSTR) {
		instruct = parse_instruction_c(table, instr_str);
	}
	else {
		return NULL;
	}
	return instruct;
}

void print_instruct_st(struct instruct_st *instruct) {
	if (!instruct) {
		fprintf(stderr, "print_instruct_st: NULL instruct\n");
		return;
	}
	printf("Instruction type   : %d\n", instruct->type);
	printf("Instruction header : %s\n", instruct->header_bin);
	if (instruct->type == A_INSTR && instruct->blob) {
		printf("Instruction Address: %s\n", instruct->blob->blob_a.address);
	}
}

void destroy_instruct_st(struct instruct_st *instruct) {
	if (!instruct) {
		return;
	}
	if (instruct->blob) {
		free(instruct->blob);
	}
	free(instruct);
}

int main () {
	//printf("%s\n", comp_str2bin("D_MINUS_M"));
    struct instruct_st *instruct = NULL;
	struct symbol_entry *table = init_sym_table();
    instruct = parse_instruction(table, "A=D+1;JMP");
    print_instruct_st(instruct);

    instruct = parse_instruction(table, "A=D+1;");
    print_instruct_st(instruct);
    /*
	printf(get_addr_bin(table, "PIKA"));
	printf("\n");
	instruct = parse_instruction(table, "@21 ");
	print_instruct_st(instruct);

	instruct = parse_instruction(table, "(PIKA)");
	print_instruct_st(instruct);
	//print_sym_table(table);
	destroy_instruct_st(instruct);
	//parse_instruction()
    */

	return 0;
}