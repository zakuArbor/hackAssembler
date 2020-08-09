#include <stdio.h>
#include <stdlib.h>

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

int main () {
	printf("%s\n", comp_str2bin("D_MINUS_M"));
}