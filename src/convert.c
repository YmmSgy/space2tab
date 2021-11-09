#include "convert.h"

#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "io.h"
#include "args.h"
#include "msgs.h"

static bool verbose;
static unsigned int tabsize;

static void settabsize(char *sizestr) {
	// convert from string to unsigned integer
	char *end;
	unsigned long num = strtoul(sizestr, &end, 10);
	int err = errno;

	// if nothing was converted, end pointer does not change
	if (end == sizestr) {
		eprintf(err, ERR_NOTSIZ, sizestr);
		exit(EXIT_FAILURE);
	}

	// error if tabsize exceeds max
	if (num > UINT_MAX) {
		eprintf(err, ERR_BIGSIZ, UINT_MAX);
		exit(EXIT_FAILURE);
	}

	// error if tabsize is zero
	if (num == 0) {
		eprintf(err, ERR_ZEROSZ);
		exit(EXIT_FAILURE);
	}

	// if no errors, set actual tabsize
	tabsize = num;
}

void init_convert(struct Args *opts) {
	verbose = opts->verbose;
	settabsize(opts->tabsize);
}

static unsigned int spacecount;

static void incspacecount(void) {
	// check if about to exceed max spaces in a line
	if (spacecount == UINT_MAX) {
		// when about to overflow
		eprintf(0, ERR_BIGSPC, UINT_MAX);
		exit(EXIT_FAILURE);
	}
	++spacecount;
}

static void inserttabs(FILE *outfile) {
	// find number of tabs to insert and insert them in a loop
	unsigned int numtabs = spacecount / tabsize;
	for (unsigned int i = 0; i < numtabs; ++i) {
		fputc_e('\t', outfile);
	}

	// just insert remaining spaces
	unsigned int rem = spacecount % tabsize;
	for (unsigned int i = 0; i < rem; ++i) {
		fputc_e(' ', outfile);
	}
}

void convert(FILE *infile, FILE *outfile) {
	// loop through every char in file
	spacecount = 0;
	bool isfirst = true;
	bool isrecording;
	for (int c; (c = fgetc_e(infile)) != EOF; isfirst = c == '\n') {
		// record for possible replacement only if it's the first char in the
		// file, or if it's the first character after a newline
		if (isfirst) {
			isrecording = true;
		}

		if (isrecording) {
			// record the space if any, then skip to the next char
			if (c == ' ') {
				incspacecount();
				continue;
			}
			else {
				// if non-space char encountered, convert spaces
				inserttabs(outfile);

				// reset space count and turn off recording
				spacecount = 0;
				isrecording = false;
			}
		}

		// insert source char
		fputc_e(c, outfile);
	} // end for loop

	// convert all excess spaces once eof reached
	inserttabs(outfile);
}
