#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {
	srand(time(NULL));
	if (argc != 2) {
		printf("Usage: %s <length>\n", argv[0]);
		exit(1);
	}
	int n = atoi(argv[1]);
	FILE *fout = fopen("test.in", "w");
	fprintf(fout, "%i ", n);
	for (int i = 0; i < n; ++i)
		fprintf(fout, "%i ", rand() % (n * 10));
	fprintf(fout, "\n");
	return 0;
}
