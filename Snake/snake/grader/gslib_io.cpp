#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "gslib.h"
#include "snakelib.h"

int numCalls = 0;
int history[MAXCALL2][2];
int questions[MAXCALL2][2];
char answers[MAXCALL2][2];

void print_history() {
	char logline[200];
    sprintf(logline, "snake has length %d and moved like this:", history[0][1] - history[0][0] + 1);
    log(logline);
    for (int x = 0; x < numCalls; x++) {
        sprintf(logline, "%2d: covered units %d - %d", x + 1, history[x][0], history[x][1]);
        log(logline);
    }
}

bool isok(int call, int position, char reply) {
	if (reply == 'b' && position < history[call][0])
		return true;
	if (reply == 's' && position >= history[call][0] && position <= history[call][1])
		return true;
	if (reply == 'f' && position > history[call][1])
		return true;
	return false;
}

bool verify_history() {
	for (int call = 0; call < numCalls; call++) {
		if (!isok(call, questions[call][0], answers[call][0]) || !isok(call, questions[call][1], answers[call][1]))
			return false;
	}
	return true;
}

int main(int argc, char const* argv[]) {
	initialize();

	bool gotspeed = false;

	char inputline[200], logline[200];
	for (;;) {
		fgets(inputline, 200, stdin);
		if (!strcmp(inputline, "get_speed\n")) {
			if (gotspeed) {
				die("only one call of get_speed allowed");
			}
			gotspeed = true;
			sprintf(logline, "get_speed(). reply: %d", get_speed());
			log(logline);
			printf("%d\n", get_speed());
			fflush(stdout);
		} else if (!strcmp(inputline, "ask_snake\n")) {
			if (!gotspeed) {
				die("call of ask_snake without former call of get_speed");
			}

			int p1, p2;
			char c1, c2;
			fgets(inputline, 200, stdin);
			if (sscanf(inputline, "%d", &p1) != 1)
				die("parse error");
			fgets(inputline, 200, stdin);
			if (sscanf(inputline, "%d", &p2) != 1)
				die("parse error");
			if (p1 < MINPOS || p2 < MINPOS || p1 > MAXPOS || p2 > MAXPOS) {
				sprintf(logline, "call of ask_snake with invalid units (%d, %d)", p1, p2);
				die(logline);
			}

			if (numCalls == MAXCALL2 - 1) {
				sprintf(logline, "%2d: ask_snake(%d, %d)", numCalls + 1, p1, p2);
				log(logline);
				generate_history();
				print_history();
				if (verify_history())
					log("history verified");
				die("too many calls of ask_snake");
			}
			numCalls++;

			ask_snake(p1, p2, &c1, &c2);
			sprintf(logline, "%2d: ask_snake(%d, %d). reply: %c %c", numCalls, p1, p2, c1, c2);
			log(logline);
			questions[numCalls - 1][0] = p1; questions[numCalls - 1][1] = p2;
			answers[numCalls - 1][0] = c1; answers[numCalls - 1][1] = c2;
			printf("%c\n%c\n", c1, c2);
			fflush(stdout);
		} else if (!strcmp(inputline, "tell_length\n")) {
			if (!gotspeed) {
				die("call of tell_length without former call to get_speed");
			}
			int length;
			fgets(inputline, 200, stdin);
			if (sscanf(inputline, "%d", &length) != 1)
				die("parse error");
			sprintf(logline, "tell_length(%d)", length);
			log(logline);
			
			tell_length(length);
			printf("0\n");
			fflush(stdout);
			return 0;
		} else {
			sprintf(logline, "invalid input");
			die(logline);
		}
	}
}

