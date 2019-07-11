#include "cycle.h"

void escape(int n) {
	if(n == 10) {
		if(jump(3) == true) {
			jump(2);
			jump(3);
			jump(1);
			jump(6);
		}
	}
}
