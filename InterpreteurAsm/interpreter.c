#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define MAX_SIZE 1000
#define SEPARATORS  " ,R#[]"
#define MAX_ARGS 3
#define MAX_SIZE_ARGS 5

typedef struct Label {
	char name[50];
	int line;
};

char *DATA_PROCESS[16] = { "AND", "EOR", "LSL", "LSR", "ASR", "ADC", "SBC", "ROR", "TST", "RSB", "CMP", "CMN", "ORR", "MUL", "BIC", "MVN" };
char *SASM[6] = { "LSL", "LSR", "ASR", "ADD", "SUB", "MOV" };
char *LS[2] = { "STR", "LDR" };
char *BR[14] = { "BEQ", "BNE", "BCS", "BCC", "BMI", "BPL", "BVS", "BVC", "BHI", "BLS", "BGE", "BLT", "BGT", "BLE" };

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

	// Open and check the file
	src = fopen(src_path, "r");
	dst = fopen(dst_path, "w");
	if (src == NULL) {
		printf("FATAL ERROR: cannot open source file.\n");
		exit(1);
	}
	else if (dst == NULL) {
		printf("FATAL ERROR: cannot open destination file.\n");
		exit(1); 
	}
	assert(src != NULL && dst != NULL);

	char str[MAX_SIZE];
	int lblCount = 0;
	struct Label labels[256];
	int lineCount = 0;

	// Parse once to save label positions and names
	while (fgets(str, MAX_SIZE, src) && lineCount < 256) {
		lineCount++;
		if (!strchr(str, ' ')) {
			strcpy(labels[lblCount].name, strtok(str, "\n"));
			labels[lblCount].line = lineCount;
			lblCount++;
		}
	}

	// Close and open the file to parse again
	if (fclose(src)) {
		printf("Error: could not close source file.\n");
	}
	src = fopen(src_path, "r");
	if (src == NULL) {
		printf("FATAL ERROR: cannot open source file.\n");
		exit(1);
	}

	// Start translating
	while (fgets(str, MAX_SIZE, src)) {
		char *line;
		char args[MAX_ARGS][MAX_SIZE_ARGS];
		int nb_args = 0;
		int code_instr;
		int output = 0;
		for (line = strtok(str, "\n"); line; line = strtok(NULL, "\n")) {
			printf("%s\n", line);
			char instruction[4];
			decode_line(line, &instruction, &args, &nb_args);
			if (!nb_args)
				continue;
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
					int imm = atoi(args[1]);
					output = (0b00100 << 11) + (arg1 << 9) + (0b0 << 8) + (imm << 6) + 0b000000;
				}
			}
			else if ((code_instr = search(instruction, LS, 2)) != -1) {
			    int arg1 = atoi(args[0]);
				int arg2 = atoi(args[1]);
				int imm = atoi(args[2]);
				output = (0b011 << 13) + (code_instr << 11) + (imm << 6) + (arg2 << 3) + arg1;
			}
			else if ((code_instr = search(instruction, BR, 14)) != -1) {
				int imm = 0;
				for (int i = 0; i < lblCount; i++) {
					if (strcmp(labels[i].name, args[0])) {
						imm = labels[i].line;
						break;
					}
				}
				output = (0b1101 << 12) + (code_instr << 8) + imm;
			}
			char s_output[4];
			print_binary(output);
			putchar('\n');
			sprintf(s_output, "%x", output);
			fputs(s_output, dst);
		}
	}
	if (fclose(src)) {
		printf("Error: could not close source file.\n");
	}
	if (fclose(dst)) {
		printf("Error: could not close destination file.\n");
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
