#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define MAX_SIZE 1000
#define SEPARATORS  " ,R#"
#define MAX_ARGS 3
#define MAX_SIZE_ARGS 5


char *DATA_PROCESS[16] = { "AND", "EOR", "LSL", "LSR", "ASR", "ADC", "SBC", "ROR",
"TST", "RSB", "CMP", "CMN", "ORR", "MUL", "BIC", "MVN" };
char *SASM[6] = { "LSL", "LSR", "ASR", "ADD", "SUB", "MOV" };


void print_binary(int n) {
	for (int c = 15; c >= 0; c--) {
		int k = n >> c;
		if (k & 1)
			printf("1");
		else
			printf("0");
	}

}

void decode_line(char *line, char(*instruction)[4], char(*args)[MAX_ARGS][MAX_SIZE_ARGS], int *nb_args) {
	*nb_args = 0;
	char *token = strtok(line, SEPARATORS);
	strcpy(*instruction, token);
	while ((token = strtok(NULL, SEPARATORS)) != NULL) {
		strcpy((*args)[(*nb_args)++], token);
	}
}

int search(char *val, char **arr, int size) {
	for (int i = 0; i < size; i++) {
		if (!strcmp(val, arr[i]))
			return i;
	}
	return -1;
}

void interprete(char *src_path, char *dst_path) {
	FILE* src = NULL;
	FILE* dst = NULL;

	int output;

	// Open and check the file
	src = fopen(src_path, "r");
	dst = fopen(dst_path, "w");
	if (src == NULL) {
		printf("FATAL ERROR: cannot open source file.");
		exit(1);
	}
	else if (dst == NULL) {
		printf("FATAL ERROR: cannot open destination file.");
		exit(1);
	}
	assert(src != NULL && dst != NULL);

	// Start translating
	char str[MAX_SIZE];
	while (fgets(str, sizeof(str), src)) {
		char *line;
		char args[MAX_ARGS][MAX_SIZE_ARGS];
		int nb_args = 0;
		int code_instr;
		int start_line = 1;
		for (line = strtok(str, "\n"); line; line = strtok(NULL, "\n")) {
			printf("%s\n", line);
			char instruction[4];
			decode_line(line, &instruction, &args, &nb_args);
			if ((code_instr = search(instruction, DATA_PROCESS, 16)) != -1 && nb_args == 2) {
				int arg1 = atoi(args[0]);
				int arg2 = atoi(args[1]);
				output = (code_instr << 6) + (arg2 << 3) + arg1;
			}
			else if ((code_instr = search(instruction, SASM, 6)) != -1) {
				if (code_instr < 3) {
					int arg1 = atoi(args[0]);
					int arg2 = atoi(args[1]);
					int imm = atoi(args[2]);
					output = (code_instr << 11) + (imm << 9) + (0 << 6) + (arg2 << 3) + arg1;
				}
				else if (code_instr < 5) {
					int arg1 = atoi(args[0]);
					int arg2 = atoi(args[1]);
					int arg3 = atoi(args[2]);
					output = (0b00011 << 11) + ((code_instr % 3) << 9) + (arg3 << 8) + (0 << 6) + (arg2 << 3) + arg1;
				}
				else {
					int arg1 = atoi(args[0]);
					int arg2 = atoi(args[1]);
					output = (0b00100 << 11) + (arg1 << 9) + (0b0 << 8) + (arg2 << 6) + 0b000000;
				}
			}
			start_line++;
			char s_output[4];
			print_binary(output);
			putchar('\n');
			sprintf(s_output, "%x", output);
			fputs(s_output, dst);
		}

	}

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
