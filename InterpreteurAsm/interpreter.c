#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define MAX_SIZE 10000000

int line_index = 0;

char* next_token(char str[]) {
	char *res = malloc(sizeof(char)*10);
	int i;
	for (i = 0; str[line_index] != ',' || str[line_index] != ' ' || str[line_index] != '\n'; line_index++, i++) {
		res[i] = str[line_index];
	}
	res[i] = '\0';
	line_index++;
	return res;
}

void interprete(char *src_path, char *dst_path) {
	FILE* src = NULL;
	FILE* dst = NULL;

	int output;

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
	assert(src != NULL && dst != NULL);

	// Start translating
	

	char str[MAX_SIZE];
	fgets(str, MAX_SIZE, src);
	char instruction[] = next_token(str);

	// Data Processing

	if (strcmp(instruction, "AND")) {
		int arg1 = atoi(next_token(str));
		int arg2 = atoi(next_token(str));
		output = (0x0100000000 << 6) + (arg2 << 3) + arg1;
	}
	else if (strcmp(instruction, "EOR")) {
		int arg1 = atoi(next_token(str));
		int arg2 = atoi(next_token(str));
		output = (0x0100000001 << 6) + (arg2 << 3) + arg1;
	}
	else if (strcmp(instruction, "LSL")) {
		int arg1 = atoi(next_token(str));
		int arg2 = atoi(next_token(str));
		output = (0x0100000010 << 6) + (arg2 << 3) + arg1;
	}
	else if (strcmp(instruction, "LSR")) {
		int arg1 = atoi(next_token(str));
		int arg2 = atoi(next_token(str));
		output = (0x0100000011 << 6) + (arg2 << 3) + arg1;
	}
	else if (strcmp(instruction, "ASR")) {
		int arg1 = atoi(next_token(str));
		int arg2 = atoi(next_token(str));
		output = (0x0100000100 << 6) + (arg2 << 3) + arg1;
	}
	else if (strcmp(instruction, "ADC")) {
		int arg1 = atoi(next_token(str));
		int arg2 = atoi(next_token(str));
		output = (0x0100000101 << 6) + (arg2 << 3) + arg1;
	}
	else if (strcmp(instruction, "SBC")) {
		int arg1 = atoi(next_token(str));
		int arg2 = atoi(next_token(str));
		output = (0x0100000110 << 6) + (arg2 << 3) + arg1;
	}
	else if (strcmp(instruction, "ROR")) {
		int arg1 = atoi(next_token(str));
		int arg2 = atoi(next_token(str));
		output = (0x0100000111 << 6) + (arg2 << 3) + arg1;
	}
	else if (strcmp(instruction, "TST")) {
		int arg1 = atoi(next_token(str));
		int arg2 = atoi(next_token(str));
		output = (0x0100001000 << 6) + (arg2 << 3) + arg1;
	}
	else if (strcmp(instruction, "RSB")) {
		int arg1 = atoi(next_token(str));
		int arg2 = atoi(next_token(str));
		output = (0x0100001001 << 6) + (arg2 << 3) + arg1;
	}
	else if (strcmp(instruction, "CMP")) {
		int arg1 = atoi(next_token(str));
		int arg2 = atoi(next_token(str));
		output = (0x0100001010 << 6) + (arg2 << 3) + arg1;
	}
	else if (strcmp(instruction, "CMN")) {
		int arg1 = atoi(next_token(str));
		int arg2 = atoi(next_token(str));
		output = (0x0100001011 << 6) + (arg2 << 3) + arg1;
	}
	else if (strcmp(instruction, "ORR")) {
		int arg1 = atoi(next_token(str));
		int arg2 = atoi(next_token(str));
		output = (0x0100001100 << 6) + (arg2 << 3) + arg1;
	}
	else if (strcmp(instruction, "MUL")) {
		int arg1 = atoi(next_token(str));
		int arg2 = atoi(next_token(str));
		next_token(str);
		output = (0x0100001101 << 6) + (arg2 << 3) + arg1;
	}
	else if (strcmp(instruction, "BIC")) {
		int arg1 = atoi(next_token(str));
		int arg2 = atoi(next_token(str));
		output = (0x0100001110 << 6) + (arg2 << 3) + arg1;
	}
	else if (strcmp(instruction, "MVN")) {
		int arg1 = atoi(next_token(str));
		int arg2 = atoi(next_token(str));
		output = (0x0100001111 << 6) + (arg2 << 3) + arg1;
	}

	// Shift, add, sub, move
}

void print_usage() {
	printf("Transforme les fichiers ASM en fichier qui peuvent etre ouvert par le micro-processeur.\n\
			Usage: interpreter src dst\n");
}

int main(int argc, char *argv[]) {
	if (argc == 3)
		interprete(argv[1], argv[2]);
	else
		print_usage();
	return 0;
}