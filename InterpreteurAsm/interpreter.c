#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 100


void interprete(char *src_path, char *dst_path) {
	FILE* src = NULL;
	FILE* dst = NULL;

	// Open and check the file
	src = fopen(src_path, "r");
	dst = fopen(dst_path, "w");
	if (src == NULL) {
		printf("FATAL ERROR: cannot open source file.");
		exit(1);
	} else if (dst == NULL) {
		printf("FATAL ERROR: cannot open destination file.");
		exit(1);
	}
	assert(src != NULL && dst != NULL);

	// Start translating
	char line[MAX_SIZE] = "";
	while ()

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