#include <stdio.h>
//version finale
void clearConsole() {
	printf("\x1b[2J");
	fflush(stdout);
}
