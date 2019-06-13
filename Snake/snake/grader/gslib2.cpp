#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "snakelib.h"
#include "gslib.h"
#include "mt19937ar.h"

#define MAXLEN 10

using namespace std;

int minlength = 1, maxlength = MAXLEN;
int firststart = MINPOS, laststart = MAXPOS;

typedef long long ll;

ll f[MAXPOS + 1][MAXLEN + 1];
int lengths[MAXLEN + 1];

extern int history[MAXCALL2][2];

extern int numCalls;
int K = 1;

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
	int P, L, seed;
	if (fscanf(in, "%d %d %d %d", &P, &L, &K, &seed) != 4)
		die("could not read input file");
	fclose(in);

	memset(f, 0, sizeof(f));
	
	for (int i = 0; i <= MAXPOS; i++)
		for (int j = minlength; j <= maxlength && i + j - 1 <= MAXPOS; j++)
			f[i][j] = 1;
	
	init_genrand(seed);
}

int get_speed() {
	return K;
}

int ok(int SnakePos, int SnakeLength, int Position, char Answer) {
	if (Answer == 'b') {
		return (Position < SnakePos);
	}
	if (Answer == 's') {
		return (Position >= SnakePos && Position <= SnakePos + SnakeLength - 1);
	}
	if (Answer == 'f') {
		return (Position > SnakePos + SnakeLength - 1);
	}
	
	die("internal library error!\n");
}

void simulate_answer(int Position1, int Position2, char Answer1, char Answer2, bool simulateOnly) {
	for (int i = firststart; i <= laststart; i++) {
		for (int j = minlength; j <= maxlength; j++) {
			if (!f[i][j])
				continue;
			
			if (ok(i, j, Position1, Answer1) && ok(i, j, Position2, Answer2)) {
				if (simulateOnly) {
					lengths[j] = 1;
				}
			} else {
				if (!simulateOnly) {
					f[i][j] = 0;
				}
			}
		}
	}
}

void ask_snake(int Position1, int Position2, char* Answer1, char* Answer2) {
	laststart += K;
	if (laststart > MAXPOS)
		laststart = MAXPOS;

	for (int i = laststart; i >= firststart; i--) {
		for (int j = minlength; j <= maxlength; j++) {
			f[i][j] <<= 1;
			if (f[i][j] != 0 && i + K + j - 1 <= MAXPOS) {
				f[i + K][j] = f[i][j] | 1;
			}
		}
	}

	bool swap = false;
	if (Position1 > Position2) {
		swap = true;
		int temp = Position2; Position2 = Position1; Position1 = temp;
	}
	
	char const* answers[] = { "bb", "bs", "bf", "ss", "sf", "ff" };
	
	int Max = -1;
	int MaxNr;

	int offset = (int)(genrand_real2() * 6);
//	fprintf(stderr, "-> %d\n", offset);
//	f[MAXLEN + 1][0] = 1;
	for (int b = 0; b < 6; b++) {
		int anr = (b + offset) % 6;
//		fprintf(stderr, "%d\n", anr);
		memset(lengths, 0, sizeof(lengths));
		simulate_answer(Position1, Position2, answers[anr][0], answers[anr][1], true);	
		int result = 0;
		for (int j = minlength; j <= maxlength; j++) {
			result += lengths[j];
		}
		
		if (result > Max) {
			Max = result;
			MaxNr = anr;
		}
	}
	simulate_answer(Position1, Position2, answers[MaxNr][0], answers[MaxNr][1], false);
	
	*Answer1 = answers[MaxNr][(swap ? 1 : 0)];
	*Answer2 = answers[MaxNr][(swap ? 0 : 1)];
	//fprintf(stderr, "%c %c\n", *Answer1, *Answer2);

	int firststartnew = MAXPOS, laststartnew = 0;
	int minlengthnew = maxlength, maxlengthnew = minlength;

	for (int i = firststart; i <= laststart; i++)
		for (int j = minlength; j <= maxlength; j++)
			if (f[i][j] != 0) {
				if (i < firststartnew)
					firststartnew = i;
				if (i > laststartnew)
					laststartnew = i;
				if (j < minlengthnew)
					minlengthnew = j;
				if (j > maxlengthnew)
					maxlengthnew = j;
			}

	firststart = firststartnew;
	laststart = laststartnew;
	minlength = minlengthnew;
	maxlength = maxlengthnew;
	//fprintf(stderr, "%d %d %d %d\n", firststart, laststart, minlength, maxlength);
	
#ifdef DEBUG
	fprintf(stderr, "lib_annoy => %d lengths remaining\n", Max);
#endif
}


void generate_history() {
	memset(lengths, 0, sizeof(lengths));

	int rcpos, rclength;
	ll rchistory;
	
	
	for (int i = firststart; i <= laststart; i++) {
		for (int j = minlength; j <= maxlength; j++) {
			if (f[i][j]) {
					rcpos = i; rclength = j; rchistory = f[i][j];
			}
		}
	}

	for (int pos = numCalls - 1; pos >= 0; pos--)
		if ((rchistory >> pos) & 1)
			rcpos -= K;
	
	for (int pos = numCalls - 1; pos >= 0; pos--) {
		if ((rchistory >> pos) & 1)
			rcpos += K;
		history[numCalls - 1 - pos][0] = rcpos;
		history[numCalls - 1 - pos][1] = rcpos + rclength - 1;
	}
}


void tell_length(int guess) {
	char logline[200];
	memset(lengths, 0, sizeof(lengths));

	int rcpos, rclength;
	ll rchistory;
	
	bool score = true;
	
	for (int i = firststart; i <= laststart; i++) {
		for (int j = minlength; j <= maxlength; j++) {
			if (f[i][j]) {
				lengths[j] = 1;
				if (score) {
					rcpos = i; rclength = j; rchistory = f[i][j];
				}
				if (abs(j - guess) > K) {
					score = false;
				}
			}
		}
	}

#ifdef DEBUG
	fprintf(stderr, "lib_annoy => Given answer: %d\n", guess);
	fprintf(stderr, "lib_annoy => The following lengths were still possible: ");
	for (int j = minlength; j <= maxlength; j++)
		if (lengths[j])
			fprintf(stderr, "%d ", j);
	fprintf(stderr, "\n");
#endif

	for (int pos = numCalls - 1; pos >= 0; pos--)
		if ((rchistory >> pos) & 1)
			rcpos -= K;
	
	for (int pos = numCalls - 1; pos >= 0; pos--) {
		if ((rchistory >> pos) & 1)
			rcpos += K;
		history[numCalls - 1 - pos][0] = rcpos;
		history[numCalls - 1 - pos][1] = rcpos + rclength - 1;
	}

	print_history();
	if (verify_history())
		log("history verified");

	if (!score) {
		sprintf(logline, "your estimate differs too much (%d units)", abs(guess - rclength));
		report(0, logline);
	} else {
		sprintf(logline, "estimate ok. %d calls needed", numCalls);
		report((numCalls <= MAXCALL1 ? 2 : 1), logline);
	}
}


