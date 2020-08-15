#include <limits.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symbol_table.h"
#include "parser.h"

/*
* Extract the filename without the extension
*
* @param char *file: the file name with the extension
* @return: 
*    * the file name without the extension (allocates memory)
*     * NULL iff file is not a valid assembly file        
*/
char *extractFileName(const char *file) {
    char *file_token;
    char *ext_token;
    char *filename;
    char *bname;
    char file_cpy[NAME_MAX];
    char *path;

    if (!file) {
        return NULL;
    }

    if (strlen(file) > NAME_MAX) {
        fprintf(stderr, "File name exceeds %d characters\n", NAME_MAX);
        return NULL;
    }

    if ( ! (path = strndup(file, strlen(file))) ) {
        return NULL;
    }

    if ( ! (bname = basename(path)) ) {
        free(path);
        return NULL;
    }
    
    strncpy(file_cpy, bname, strlen(bname));
    file_cpy[strlen(file)] = '\0';

    free(path);
    
    file_token = strtok(file_cpy, ".");
    ext_token  = strtok(NULL, ".");

    if (file_token && ext_token && strncmp(ext_token, "asm", 3) == 0) {
        if (!(filename = (char *)malloc(sizeof(char) * strlen(file_token) + 1))) {
            
            return NULL;
        }
        if (!strncpy(filename, file_token, strlen(file_token))) {
            perror("strcpy");
            free(filename);
            
            return NULL;
        }
        filename[strlen(file_token)] = '\0';
        
        return filename;
    }
    fprintf(stderr, "File must have .asm extension\n");
    return NULL;
}

int write_binary_instructions(char *filename, struct instruct_bin_entry *instructions) {
    struct instruct_bin_entry *instruction = instructions;
    FILE *fp;
    int name_size = strlen(filename) + 5 + 1;
    char *fileout_name;

    if ( ! (fileout_name = malloc(sizeof(char) * name_size)) ) {
        perror("malloc");
        return 0;
    }

    strncpy(fileout_name, filename, strlen(filename));
    fileout_name[strlen(filename)] = '\0';
    strncat(fileout_name, ".hack", 5);
    printf("after strncat: %s\tname_size: %d\n", fileout_name, name_size);
    fileout_name[strlen(filename) + 5] = '\0';
    printf("%s\n", fileout_name);

    if (! (fp = fopen(fileout_name, "w")) ) {
        free(fileout_name);
    }
    while (instruction) {
        printf("test\n");
        fprintf(fp, "%s\n", instruction->instr);
        instruction = instruction->next;
    }
    free(fileout_name);
    fclose(fp);
    return 1;
}


int main (int argc, char **argv) {
    FILE *fp = NULL;
    char *filename;
    int status = 0;
    char line[INSTR_SIZE];
    struct symbol_entry *table = NULL;
    struct instruct_bin_entry *instructions = NULL;

    printf("Hello World\n");

    if (argc < 2) {
        fprintf(stderr, "usage: %s file.asm\n", argv[0]);
        status = 1;
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

    if (! (table = init_sym_table()) ) {
        status = 1;
        goto cleanup;
    }

    if ( ! (instructions = parse_instructions(fp)) ) {
        status = 1;
        goto cleanup;
    }
    printf("after parse_instructions\n");
    fclose(fp);
    fp = NULL;
    status = write_binary_instructions(filename, instructions);

cleanup:
    if (fp) {
        fclose(fp);
    }

    if (filename) {
        free(filename);
    }

    if (table) {
        destroy_table(table);
    }
    return status;
}