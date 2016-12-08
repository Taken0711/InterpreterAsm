#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "hashmap.h"

#define MAX_SIZE 10000000
#define KEY_MAX_LENGTH 4
#define _CRT_SECURE_NO_WARNINGS
#define NB_INSTR 16

typedef struct data_struct_s
{
	char key_string[KEY_MAX_LENGTH];
	int number;
} data_struct_t;

map_t instr_table;


void interprete(char *src_path, char *dst_path) {
	FILE* src = NULL;
	FILE* dst = NULL;

	int output[16];

	// Open and check the file
	fopen_s(src, src_path, "r");
	fopen_s(dst , dst_path, "w");
	if (src == NULL) {
		printf("FATAL ERROR: cannot open source file.");
		exit(1);
	} else if (dst == NULL) {
		printf("FATAL ERROR: cannot open destination file.");
		exit(1);
	}
	//assert(src != NULL && dst != NULL);

	// Start translating
	char instruction[4];



	char str[MAX_SIZE] = "";
	fgets(str, MAX_SIZE, src);
	int i = 0;
	for (; str[i] != ' '; i++)
		instruction[i] = str[i];
	instruction[i] = '\0';



}

void print_usage() {
	printf("Transforme les fichiers ASM en fichier qui peuvent etre ouvert par le micro-processeur.\n\
			Usage: interpreter src dst\n");
}

data_struct_t* new_data_struct_t(char instr[], int code) {
	data_struct_t *res = malloc(sizeof(data_struct_t));
	strcpy(res->key_string, instr);
	res->number = code;
	return res;
}

void build_instruction_table() {
	instr_table = hashmap_new();
	data_struct_t *to_add[NB_INSTR];
	to_add[0] = new_data_struct_t("ADD", 0x0100000000);
	for (int i = 0; i < NB_INSTR; i++) {
		hashmap_put(instr_table, to_add[i]->key_string, to_add[i]);
	}
}

int main(int argc, char *argv[]) {
	build_instruction_table();
	if (argc == 3)
		interprete(argv[1], argv[2]);
	else
		print_usage();
	return 0;
}