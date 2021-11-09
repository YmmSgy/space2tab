#include "vers.h"

#include <stdio.h>

void printvers(void) {
	printf(
	"%s version %s\n"
	"Made by %s.\n"
	"Source: %s\n"
	"Last compiled %s %s.\n",
	VERS_PRGNAM, VERS_VRSNUM,
	VERS_CRE8OR,
	VERS_SOURCE,
	__DATE__, __TIME__);
}
