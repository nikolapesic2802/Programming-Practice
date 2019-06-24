/* Simulate Reverse Machine (TOM) */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

/*
  reverse.in: input file
  reverse.key: minimum S-operation count possible
  standard input: competitor's solution
 */

int reg[9];

int
line_end(char c) {
	if (c == '\0') return 1;
	if (c == '\r') return 1;
	if (c == '\n') return 1;
	return 0;
}

int
main(int argc, char **argv) {
	char line[100];
	char *cp;
	int r1, r2;
	int lv;
	int ocnt;
	int mocnt = -1;
	int lastout=-1;
	int start = -1;
	int nxt;
	FILE *fout = stdout;
	int opt;
	int input;
	int score;
	int output=0;
	FILE *tmp;

	if (argc > 1 && strcasecmp(argv[1], "-output") == 0) {
		output = 1;
	}

	if (!output) {
		tmp = fopen("reverse.in", "r");
		assert(tmp);
		fscanf (tmp, "%d", &nxt);
		fscanf (tmp, "%d", &nxt);
		start = nxt;
		fclose(tmp);

		tmp = fopen("reverse.key", "r");
		assert(tmp);
		fscanf (tmp, "%d", &opt);
		fclose(tmp);
	}

	if (!fgets(line, sizeof(line), stdin)) {
		fprintf (fout, "Wrong: early eof\n");
		exit(1);
	}
	if (!strchr(line, '\n')) {
		fprintf (fout, "Wrong: line too long\n");
		exit(1);
	}
	cp = line;
	while (*cp != ' ' && *cp) cp++; /* FILE */
	if (*cp == ' ') cp++;
	while (*cp != ' ' && *cp) cp++; /* reverse */
	if (*cp == ' ') cp++;
	input = -1;
	while (*cp >= '0' && *cp <= '9') {
		if (input == -1) input = 0;
		input = 10*input + *cp++ - '0';
		if (input > 1000) input = 1000;
	}
	if (input == -1) {
		fprintf (fout, "Wrong: illegal output number\n");
		exit(1);
	}
	if (!line_end(*cp)) {
		fprintf (fout, "Wrong: characters after input number\n");
		exit(1);
	}

	if (!fgets(line, sizeof(line), stdin)) {
		fprintf (fout, "Wrong: early eof\n");
		exit(1);
	}
	if (!strchr(line, '\n')) {
		fprintf (fout, "Wrong: line too long\n");
		exit(1);
	}
	cp = line;

	for (lv = 0; lv < 9; lv++) {
		reg[lv] = -1;
		while (*cp >= '0' && *cp <= '9') {
			if (reg[lv] == -1) reg[lv] = 0;
			reg[lv] = 10*reg[lv] + *cp++ - '0';
			if (reg[lv] > 1000) reg[lv] = 1000;
		}
		if (reg[lv] == -1) {
			fprintf (fout, "Wrong: illegal reg line (no reg value)\n");
			exit(1);
		}
		if (lv < 8) {
			if (*cp != ' ') {
				fprintf (fout, "Wrong: illegal reg line (lv %i, not space)\n", lv);
				exit(1);
			}
			cp++;
		} else if (*cp != '\0' && *cp != '\r' && *cp != '\n') {
			fprintf (fout, "Wrong: characters after register data\n");
			exit(1);
		}
	}

	ocnt = 0;

	while (fgets(line, sizeof(line), stdin)) {
		if (nxt == -1) {
			fprintf (fout, "WRONG\nProgram continues execution after printing 0.\n");
			exit(0);
		}
		if (!strchr(line, '\n')) {
			fprintf (fout, "Wrong: line too long\n");
			exit(1);
		}

		if (line[1] == '\0') r1 = -1;
		else r1 = line[2] - '0';
		if (line[3] == '\0') r2 = -1;
		else r2 = line[4] - '0';

		if (line[0] == 'P') {
			assert (r1 >= 1 && r1 <= 9);
			r1--;
			if (!line_end(line[3])) {
				fprintf (fout, "Wrong: data after P command\n");
				exit(1);
			}
			if (start == -1) {
				start = reg[r1];
				// fprintf (fout, "Start at %i\n", start);
				nxt = start - 1;
			} else {
				if (reg[r1] != nxt) {
fprintf (fout, "WRONG\nYour TOP program printed %d when it should have printed %d.\n", reg[r1], nxt);
					exit(0);
				}
				nxt--;
			}
#ifdef WATCH
			fprintf (stdout, "%d\n", reg[r1]);
#endif
			if (ocnt > mocnt) mocnt = ocnt;
			ocnt = 0;
			lastout = reg[r1];
		} else if (line[0] == 'S') {
			assert (r1 >= 1 && r1 <= 9);
			assert (r2 >= 1 && r2 <= 9);
			r1--; r2--;
/*
			if (nxt == start) {
				fprintf (fout, "Wrong: operating before first P command\n");
				exit(1);
			}
*/
			if (!line_end(line[5])) {
				fprintf (fout, "Wrong: data after P command\n");
				exit(1);
			}
			reg[r2] = reg[r1] + 1;
			if(reg[r2] > 1000){
				fprintf(fout, "WRONG\nYour program overflowed register %d.\n", r2+1);
				exit(0);
			}
			ocnt++;
			if (ocnt > 131) {
fprintf(fout, "WRONG\nYour program has too many consecutive S-operations.\n");
				exit(0);
			}

		}
	}
	if (lastout != 0) {
		if(lastout == -1)
fprintf(fout, "WRONG\nYour program did not print anything.\n");
		else
fprintf(fout, "WRONG\nYour program stopped after printing %d.\n", lastout);
		exit(0);
	}

	if (!output) {
		if (mocnt < opt){
			printf("WRONG\nStudent thinks he is better than us.\n");
			exit(0);
		}
		score = 10;
		if (mocnt > opt) score -= 2;
		if (mocnt > opt+1) score -= 2;
		if (mocnt > opt+2) score--;
		if (mocnt > opt+4) score--;
		if (mocnt > opt+7) score--;
		if (mocnt > opt+10) score--;
		if (score == 10) printf ("OK\n");
		else printf ("OK %d\n", score);
	} else {
		printf ("%d\n", mocnt);
	}

	return 0;
}
