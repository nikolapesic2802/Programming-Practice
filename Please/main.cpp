#include <stdio.h>
#include <stdlib.h>

#define fail(s, x...) do { \
		fprintf(stderr, s "\n", ## x); \
		exit(1); \
	} while(0)

#define MAX_A 50000
#define MAX_B 50000
#define MAX_T 500000

static int X[MAX_A];
static int Y[MAX_B];
static int W[MAX_T];
static int S[MAX_T];


int putaway(int A, int B, int T, int X[], int Y[], int W[], int S[]) {

    return 42;
}

int main() {
    int A, B, T, i;
	int res;

	FILE *f = fopen("sample1.in", "r");
	if (!f)
		fail("Failed to open input file.");

	res = fscanf(f, "%d", &A);
	if (res != 1)
		fail("Failed to read A from input file.");
	if (A < 0 || A > MAX_A)
		fail("A is out of bounds.");

	res = fscanf(f, "%d", &B);
	if (res != 1)
		fail("Failed to read B from input file.");
	if (B < 0 || B > MAX_B)
		fail("B is out of bounds.");

	res = fscanf(f, "%d", &T);
	if (res != 1)
		fail("Failed to read T from input file.");
	if (T < 1 || T > MAX_T)
		fail("T is out of bounds.");

	for (i = 0; i < A; i++) {
		res = fscanf(f, "%d", &X[i]);
		if (res != 1)
		    fail("Failed to read data from input file.");
    }
	for (i = 0; i < B; i++) {
        res = fscanf(f, "%d", &Y[i]);
        if (res != 1)
            fail("Failed to read data from input file.");
    }
	for (i = 0; i < T; i++) {
        res = fscanf(f, "%d%d", &W[i], &S[i]);
        if (res != 2)
            fail("Failed to read data from input file.");
    }
	fclose(f);

	int answer = putaway(A, B, T, X, Y, W, S);

	printf("%d\n", answer);

	return 0;
}
