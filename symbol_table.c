#include <stdio.h>
#include <stdlib.h>
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

int main () {
	struct symbol_table s;
	s.val = 21;
	printf("\n%s\n", dec_to_bin(&s));
	return 0;
}