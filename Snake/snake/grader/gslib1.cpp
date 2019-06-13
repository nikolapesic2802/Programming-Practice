#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "snakelib.h"
#include "gslib.h"

#include "mt19937ar.h"

double mp;
extern int numCalls;
int P, L, K = 1;
extern int history[MAXCALL2][2];

FILE* out = NULL;

void log(char const* Message) {
	fprintf((out == NULL ? stderr : out), "%s\n", Message);
}

void report(int Score, char const* Message) {
	char reportline[200];
	sprintf(reportline, "POINTS %d MESSAGE %s", Score, Message);
	log(reportline);
	if (out != NULL) {
		fclose(out);
	}
}

void die(char const* Message) {
	report(0, Message);
	exit(1);
}

void initialize() {
	out = fopen("snake.out", "w");
	
	if (out == NULL) {
		die("could not open output file");
	}

	FILE* in = fopen("snake.in", "r");
	if (in == NULL)
		die("could not open input file");
	int seed;
	if (fscanf(in, "%d %d %d %d %lf ", &P, &L, &K, &seed, &mp) != 5)
		die("could not read input file");
	init_genrand(seed);
	fclose(in);
}

int get_speed() {
	return K;
}

char getAnswer(int Position) {
	if (Position < P)
		return 'b';
	if (Position >= P + L)
		return 'f';
	return 's';
}

void ask_snake(int P1, int P2, char *A1, char *A2) {
	if (P + L - 1 + K <= MAXPOS) {
		if ((mp == -1 && ((numCalls & 1) == 0)) || (genrand_real2() < mp))
			P += K; 
	}

	history[numCalls - 1][0] = P;
	history[numCalls - 1][1] = P + L - 1;

	*A1 = getAnswer(P1);
	*A2 = getAnswer(P2);
}

void generate_history() {
}

void tell_length(int guess) {
	char logline[200];

	print_history();
	if (verify_history())
		log("history verified");
		
	if (abs(guess - L) > K) {
		sprintf(logline, "your estimate differs too much (%d units)", abs(guess - L));
		report(0, logline);
	} else {
		sprintf(logline, "estimate ok. %d calls needed", numCalls);
		report((numCalls <= MAXCALL1 ? 2 : 1), logline);
	}
}

