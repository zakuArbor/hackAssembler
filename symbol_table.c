#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"

int symbol_num = 0;

char *dec_to_bin(int n) 
{
	char *bin;
	int i = 0, b;

	if (!(bin = malloc(sizeof(char) * BUS_SIZE))) {
		perror("malloc");
		return NULL;
	}

	for (b = 14; b >= 0; b--) {
	    int bit = n >> b;

	    if (bit & 1) {
	    	bin[i] = '1';
	    }
	    else {
	     	bin[i] = '0';
	    }
	    i++;
  	}
  	return bin;
}

struct symbol_entry *create_sym_entry(char *symbol, int val) 
{
	struct symbol_entry *entry;
	if (! ( entry = malloc(sizeof(struct symbol_entry)) ) ) {
		perror("malloc");
		return NULL;
	}
	if (!symbol || strlen(symbol) > SYMBOL_SIZE) {
		fprintf(stderr, 
			"create_sym_entry: symbol is empty or exceeds over %d character " \
			"limit\n", 
			SYMBOL_SIZE);
		return NULL;
	}

	strncpy(entry->symbol, symbol, strlen(symbol));
	entry->symbol[strlen(symbol)] = '\0';
	entry->val = val;
	entry->next = NULL;

	return entry;
}

struct symbol_entry *insert_to_table(struct symbol_entry *table, 
                                     char * symbol, 
                                     int val) 
{
	struct symbol_entry *entry = table;
	int i = 0;

	if (!table) {
		fprintf(stderr, "insert_to_table: table cannot be NULL\n");
		return NULL;
	}

	while (entry->next) {
		entry = entry->next;
		i++;
	}

	if (i < PREDEF_SYMBOL_NUM) {
		fprintf(stderr, 
			"insert_to_table: Table is missing pre-defined symbols\n");
		goto terminate;
	}

	//if address needs to be dynamically allocated
	if (val < 0) {
		val = 16 + symbol_num;
		symbol_num++;
	}

	if ( ! (entry->next = create_sym_entry(symbol, val)) ) {
		goto terminate;
	}
	return table;

terminate:
	destroy_table(table);
	return NULL;	
}

void destroy_table (struct symbol_entry *entry) {
	if (!entry) {
		return;
	}
	struct symbol_entry *next = entry->next;
	free(entry);
	destroy_table(next);
}

void print_sym_table(struct symbol_entry *entry) {
	while (entry) {
		printf("sym: %-3s\t val: %d\n", entry->symbol, entry->val);
		entry = entry->next;
	}
}

int find_symbol(struct symbol_entry *entry, char *symbol) {
	while (entry) {
		if (strncmp(entry->symbol, symbol, strlen(symbol)) == 0) {
			return entry->val;
		}
		entry = entry->next;
	}
	return -1;
}


struct symbol_entry *init_sym_table() {
	struct symbol_entry *table = create_sym_entry("R0", 0);
	struct symbol_entry *entry = table;
	int i, n;

	char *symbols[7] = {"SCREEN", "KBD", "SP", "LCL", "ARG", "THIS","THAT"};
	int values[7] = {16384, 24576, 0, 1, 2, 3, 4};

	char sym[7];

	//Add Register 1-15 to symbol table
	for(i = 1; i < 16; i++) {
		if (i < 10 ) {
			n = 3; //'Rx' + '\0'
		}
		else {
			n = 4; //'Rxx' + '\0'
		}
		snprintf(sym, n, "R%d", i);
		if ( !(entry->next = create_sym_entry(sym, i)) ) {
			destroy_table(table);
			return NULL;
		}
		entry = entry->next;
	}

	//Add Screen and Keyboard and special pre-defined symbols
	for (i = 0; i < 7; i++) {
		if ( !(entry->next = create_sym_entry(symbols[i], values[i])) ) {
			destroy_table(table);
			return NULL;
		}
		entry = entry->next;
	}
	return table;
}