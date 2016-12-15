#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define MAX_SIZE 10000000
#define SEPARATORS  " ,"

char *DATA_PROCESS[16] = { "AND", "EOR", "LSL", "LSR", "ASR", "ADC", "SBC", "ROR",
"TST", "RSB", "CMP", "CMN", "ORR", "MUL", "BIC", "MVN" };

int line_index = 0;

char* next_token(char str[]) {
	char *res = malloc(sizeof(char)*10);
	int i = 0;
	for (int i=0; str[line_index] != ' ' || str[line_index] != '\n'; line_index++,i++) {
		res[i] = str[line_index];
	}
	res[i] = '\0';
	line_index++;
	return res;
}

char* data_process(char *line) {
	char *token;
	char *instruction = strtok(line, SEPARATORS);
	int codeInstr;
	int arg1 = atoi(strtok(line, SEPARATORS));
	int arg2 = atoi(strtok(line, SEPARATORS));
	return (codeInstr << 6) + (arg2 << 3) + arg1;
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
	while (fgets(str, sizeof(str), src)) {
		char *line;
		int start_line = 1;
		for (line = strtok(str, "\n"); line; line = strtok(NULL, "\n")) {
			char *instruction = strtok(line, SEPARATORS);
			if (is_in(instruction, DATA_PROCESS)) {
				int codeInstr; // mettre au bon endroit
				int arg1 = atoi(strtok(line, SEPARATORS));
				int arg2 = atoi(strtok(line, SEPARATORS));
				return (codeInstr << 6) + (arg2 << 3) + arg1;
			}
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