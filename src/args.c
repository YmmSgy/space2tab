#include "args.h"

#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include "io.h"
#include "msgs.h"
#include "vers.h"

static void resetopts(struct Args *args) {
	args->verbose = false;
	args->tabsize = "8";
}

void parseargs(struct Args *args, int argc, char **argv) {
	// reset option arguments to default values
	resetopts(args);

	// parse every option
	int c; errno = 0;
	while ((c = getopt(argc, argv, ":hVvs:")) != -1) {
		switch (c) {
			case 'h':
				// display help message and exit with success
				printf(MSG_LNGHLP);
				exit(EXIT_SUCCESS);
			case 'V':
				// display version info and exit with success
				printvers();
				exit(EXIT_SUCCESS);
			case 'v':
				args->verbose = true;
				break;
			case 's':
				args->tabsize = optarg;
				break;
			case ':':
				eprintf(errno, ERR_OPTARG);
				exit(EXIT_FAILURE);
			default:
				eprintf(errno, ERR_BADOPT);
				exit(EXIT_FAILURE);
		}
		errno = 0;
	} // end while loop

	// parse non-option args

	// optind is index of first non-opt arg, so argv + optind is the start
	// of non-opt args
	args->nonopts = argv + optind;

	// argc == no of opts + no of non-opts + 1
	// optind == no of opts + 1
	// no of non-opts == argc - optind
	args->nonoptcnt = argc - optind;
}
