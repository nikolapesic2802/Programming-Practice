#include <stdio.h>
#include <stdlib.h>

static int initialized = 0;

static FILE *in, *out;

static void initialize() {
	in = fopen("gslibIN", "r");
	out = fopen("gslibOUT", "w");

	if (in == NULL || out == NULL) {
		printf("i/o error (gslib_iface)\n");
		exit(1);
	}

	initialized = 1;
}

int get_speed() {
	if (!initialized)
		initialize();

	fprintf(out, "get_speed\n");
	fflush(out);
	int res;
	fscanf(in, "%d", &res);
	return res;
}

void ask_snake(int Position1, int Position2, char* Answer1, char* Answer2) {
	if (!initialized)
		initialize();

	fprintf(out, "ask_snake\n%d\n%d\n", Position1, Position2);
	fflush(out);
	fscanf(in, " %c", Answer1);
	fscanf(in, " %c", Answer2);
}

int tell_length(int Length) {
	if (!initialized)
		initialize();

	fprintf(out, "tell_length\n%d\n", Length);
	fflush(out);
	int temp;
	fscanf(in, " %d", &temp);
	exit(0);
}

