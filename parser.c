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

char *get_addr_bin(struct symbol_entry *table, char *str, const int new_val) {
	int i;
	int val;
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
	}
	else if (isalpha(str[0])) {
		//check if symbol exists in the symbol table
		if ((val = find_symbol(table, str)) < 0) {
			//enter symbol to the table
			if (!insert_to_table(table, str, new_val)) {
				return NULL;
			}
			val = find_symbol(table, str);
		}
	}
	if (val >= 0) {
		return dec_to_bin(val);
	}
	return NULL;
}

int parse_address_asm(const char *instr_str, char *symbol, int *is_label) {
    if (!instr_str || symbol == NULL) {
        return 0;
    }

    int i, len = 0;
    for (i = 0; i < strlen(instr_str); i++) {
        if (instr_str[i] == '\r' || instr_str[i] == '\n') 
        {
            break;
        }
        else if (instr_str[i] == ')') {
            *is_label = 1;
            break;
        }
        else if (instr_str[i] == '(' || instr_str[i] == ' ') {
            continue;
        }
        //printf("char: %c\n", instr_str[i]);
        symbol[len] = instr_str[i];
        len++;
    }
    symbol[len] = '\0';
    if (len == 0) {
        fprintf(stderr, "Error: Need a valid symbol or address name\n");
    }
    return len;
}

struct instruct_st *parse_instruction_a(struct symbol_entry *table, 
                                        struct instruct_st *instruct,
                                        const char *instr_str) 
{
	char symbol[SYMBOL_SIZE];
	char *addr;
	int is_label = 0;
    
	if (parse_address_asm(instr_str, symbol, &is_label) == 0) {
        return NULL;
	}

	if ( ! (addr = get_addr_bin(table, symbol, -1)) ) {
		return NULL;
	}
	
	instruct->type = A_INSTR;
	instruct->header_bin = A_HEADER;
    instruct->blob->blob_a.is_label = is_label;
	strncpy(instruct->blob->blob_a.address, addr, 15);
    instruct->blob->blob_a.address[15] = '\0';
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

    instr_str[dest_pos] = '\0';
    instr_str[comp_pos] = '\0';
    instr_str[jump_pos] = '\0';

    return instr_str;
}

struct instruct_st *parse_instruction_c(struct symbol_entry *table, 
                                        struct instruct_st *instruct,    
                                        const char *instr_str_orig) 
{
    int i = 0;
    int dest_end   = 0,    comp_end = 0,    jump_end = 0;
    int dest_start = -1, comp_start = -1, jump_start = -1, tmp_start = -1;
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
            case 0:
                if (tmp_start < 0 && isalnum(instr_str[i])) {
                    tmp_start = i;
                    break;
                }
                else if (instr_str[i] == '=') {
                    dest_end   = i;
                    dest_start = tmp_start;
                    comp_start = i + 1;
                    state++; //search for computation instruction
                    break;
                }
                else if (instr_str[i] == '/' || instr_str[i] == ' ') {
                    return NULL;
                }
                //no break
            case 1:
                if (instr_str[i] == ';') {
                    comp_end = i;
                    state = 2; //search for JUMP instruction
                    jump_start = i + 1;
                    if (dest_start < 0) {
                        comp_start = tmp_start;
                    }
                    break;
                }
                else if (instr_str[i] == '\r' || instr_str[i] == '\n' ||
                         instr_str[i] == '/'  || instr_str[i] == ' ') 
                {
                    comp_end = i;
                    i = strlen(instr_str);
                    break;
                }
            case 2:
                if (instr_str[i] == '\r' || instr_str[i] == '\n' ||
                    instr_str[i] == ' ') 
                {
                    jump_end = i;
                    i = strlen(instr_str);
                }
                break;
            default:
                //do nothing
                break;
        }
    }

    if (comp_end == 0) {
        return NULL;
    }

    if (dest_end < 1) {
        dest_end = strlen(instr_str);
        dest_start = dest_end;
    }

    if (jump_start < 1) {
        jump_end = strlen(instr_str);
        jump_start = jump_end;
    }

    tokenize_instruction(instr_str, dest_end, comp_end, jump_end);

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

    instruct->type                  = C_INSTR;
    instruct->header_bin            = C_HEADER;
    strncpy(instruct->blob->blob_c.dest_bin, dest_bin, DEST_SIZE);
    instruct->blob->blob_c.dest_bin[DEST_SIZE] = '\0';
    //+1 for the a-bit
    strncpy(instruct->blob->blob_c.comp_bin, comp_bin, COMP_SIZE + 1);
    instruct->blob->blob_c.comp_bin[COMP_SIZE + 1] = '\0';
    strncpy(instruct->blob->blob_c.jump_bin, jump_bin, JUMP_SIZE);
    instruct->blob->blob_c.jump_bin[COMP_SIZE] = '\0';

    return instruct;    
}

struct instruct_st *parse_instruction(struct symbol_entry *table,
                                      struct instruct_st *instruct,
                                      const char *instr_str) {
	int i = 0;
	int start = 0;//keeps track of the first position of the token being parsed
	enum instr_type type = INVALID;
	
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
		else if (isalnum(instr_str[i])) {
			start = i;
			type  = C_INSTR;
            break;
		}
        else if (instr_str[i] == '/') {
            return NULL;
        }
	}

    /*
    move pointer to the first non-blank or the first character of the 
    instruction/symbol
    */
	instr_str += start;

	if (type == A_INSTR) {
		instruct = parse_instruction_a(table, instruct, instr_str);
	}
	else if (type == C_INSTR) {
		instruct = parse_instruction_c(table, instruct, instr_str);
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
	//printf("Instruction type   : %d\n", instruct->type);
	printf("Instruction header : %s\n", instruct->header_bin);
	if (instruct->type == A_INSTR && instruct->blob) {
		printf("Instruction Address: %s\n", instruct->blob->blob_a.address);
	}
    else if (instruct->type == C_INSTR && instruct->blob) {
        printf("COMP: %s\n", instruct->blob->blob_c.comp_bin);
        printf("DEST: %s\n", instruct->blob->blob_c.dest_bin);
        printf("JUMP: %s\n", instruct->blob->blob_c.jump_bin);
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

char *assemble_instruct(struct instruct_st *instruct, char *instruct_bin) {
    if (!instruct || !instruct_bin) {
        return NULL;
    }
    
    if (instruct->type == A_INSTR && instruct->blob && 
        instruct->blob->blob_a.is_label == 0)
    {
        snprintf(instruct_bin, BUS_SIZE + 1,
            "%s%s", instruct->header_bin, instruct->blob->blob_a.address
        );
    }
    else if (instruct->type == C_INSTR) {
        snprintf(instruct_bin,
            C_HEADER_SIZE + DEST_SIZE + COMP_SIZE + 1 + JUMP_SIZE + 1,
            "%s%s%s%s",
            instruct->header_bin, instruct->blob->blob_c.comp_bin,
            instruct->blob->blob_c.dest_bin, instruct->blob->blob_c.jump_bin
        );
    }
    else {
        return NULL;
    }
    return instruct_bin;
}

void destroy_instructions(struct instruct_bin_entry *instr) {
    if (!instr) {
        return;
    }
    struct instruct_bin_entry *next = instr->next;
    free(instr);
    destroy_instructions(next);
}

struct instruct_bin_entry *parse_instructions(struct symbol_entry *table, 
                                              FILE *fp) 
{
    struct instruct_bin_entry * instr_list = NULL;
    struct instruct_bin_entry * curr_instr = NULL;
    struct instruct_st instruct_info;
    char instruct_bin[BUS_SIZE + 1];
    char line[INSTR_SIZE];

    if ( ! ( instruct_info.blob = malloc(sizeof(union instruct_blob)) ) ) {
        free(instr_list);
        perror("malloc");
        return NULL;
    }

    while (fgets(line, sizeof(line), fp)) {
        if ((parse_instruction(table, &instruct_info, line))) {
            if (! (assemble_instruct(&instruct_info, instruct_bin)) ) {
                continue;
            }

            if (!instr_list) {
                if (! (
                    instr_list = malloc(sizeof(struct instruct_bin_entry))
                    ) ) 
                {
                    perror("malloc");
                    return NULL;
                }
                curr_instr = instr_list;
                strncpy(curr_instr->instr, instruct_bin, BUS_SIZE);
                curr_instr->instr[BUS_SIZE] = '\0';
                continue;
            }
            
            if ( ! (
                curr_instr->next = malloc(sizeof(struct instruct_bin_entry))
               ) ) 
            {
                perror("malloc");
                destroy_instructions(instr_list);
                free(instruct_info.blob);
                return NULL;
            }

            strncpy(curr_instr->next->instr, instruct_bin, BUS_SIZE);
            curr_instr->next->instr[BUS_SIZE] = '\0';

            curr_instr = curr_instr->next;
            curr_instr->next = NULL;
        }
    }
    free(instruct_info.blob);
    return instr_list;
}
