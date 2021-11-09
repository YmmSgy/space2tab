#ifndef ARGS_H
#define ARGS_H

#include <stdbool.h>

// represents a collection of argument values
struct Args {
	// options
	bool verbose;
	char *tabsize;

	// non-option args
	char **nonopts;
	int nonoptcnt;
};

// tidy up the cmdline args into a struct
extern void parseargs(struct Args *args, int argc, char **argv);

#endif // ARGS_H
