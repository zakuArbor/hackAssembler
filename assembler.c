#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* Extract the filename without the extension
*
* @param char *file: the file name with the extension
* @return: 
*	* the file name without the extension (allocates memory)
* 	* NULL iff file is not a valid assembly file		
*/
char *extractFileName(const char *file) {
	char *file_token;
	char *ext_token;
	char *filename;
	char file_cpy[NAME_MAX];

	if (!file) {
		return NULL;
	}

	if (strlen(file) > NAME_MAX) {
		fprintf(stderr, "File name exceeds %d characters\n", NAME_MAX);
		return NULL;
	}

	if (!strncpy(file_cpy, file, strlen(file))) {
		perror("strcpy");
		return NULL;
	}

	file_token = strtok(file_cpy, ".");
	ext_token  = strtok(NULL, ".");

	if (file_token && ext_token && strncmp(ext_token, "asm", 3) == 0) {
		if (!(filename = (char *)malloc(sizeof(char) * strlen(file_token)))) {
			return NULL;
		}
		if (!strncpy(filename, file_token, strlen(file))) {
			perror("strcpy");
			return NULL;
		}		
		return filename;
	}
	return NULL;
}

int main (int argc, char **argv) {
	FILE *fp = NULL;
	char *filename;
	int status = 0;

	printf("Hello World\n");

	if (argc < 2) {
		fprintf(stderr, "usage: %s file.asm\n", argv[0]);
		return 1;
	}

	if (!(filename = extractFileName(argv[1]))) {
		fprintf(stderr, "%s is an invalid filename\n", argv[1]);
		status = 1;
		goto cleanup;
	}
	printf("filename: %s\n", filename);

	if (!(fp = fopen(argv[1], "r"))) {
		fprintf(stderr, "Failed to open file: %s\n", argv[1]);
		perror("fopen");
		status = 1;
		goto cleanup;
	}

cleanup:
	if (fp) {
		fclose(fp);
	}

	if (filename) {
		free(filename);
	}
	return status;
}