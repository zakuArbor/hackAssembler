#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"

char *dec_to_bin(struct symbol_table *symbol) {
	char *bin;
	int n = symbol->val;
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

struct symbol_table *create_sym_entry(char *symbol, int val) {
	struct symbol_table *entry;
	if (! ( entry = malloc(sizeof(struct symbol_table)) ) ) {
		perror("malloc");
		return NULL;
	}
	if (!symbol || strlen(symbol) > SYMBOL_SIZE) {
		fprintf(stderr, "create_sym_entry: symbol is empty or exceeds over %d charact limit\n", SYMBOL_SIZE);
		return NULL;
	}

	strncpy(entry->symbol, symbol, strlen(symbol));
	entry->symbol[strlen(symbol)] = '\0';
	entry->val = val;
	entry->next = NULL;

	return entry;
}

void destroy_table (struct symbol_table *entry) {
	if (!entry) {
		return;
	}
	struct symbol_table *next = entry->next;
	free(entry);
	destroy_table(next);
}

void print_sym_table(struct symbol_table *entry) {
	while (entry) {
		printf("sym: %-3s\t val: %d\n", entry->symbol, entry->val);
		entry = entry->next;
	}
}

struct symbol_table *init_sym_table() {
	struct symbol_table *first_entry = create_sym_entry("R0", 0);
	struct symbol_table *entry = first_entry;
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
			destroy_table(first_entry);
			return NULL;
		}
		entry = entry->next;
	}

	//Add Screen and Keyboard and special pre-defined symbols
	for (i = 0; i < 7; i++) {
		if ( !(entry->next = create_sym_entry(symbols[i], values[i])) ) {
			destroy_table(first_entry);
			return NULL;
		}
		entry = entry->next;
	}
	//print_sym_table(first_entry);
	return table;
}

int main () {
	init_sym_table();
	return 0;
}