#include <stdlib.h>
#include <string.h>
#include "io.h"		// stdio functions with error handling
#include "args.h"	// parse args and return them as a struct
#include "convert.h"	// conversion algorithm and associated options
#include "msgs.h"	// messages printed by the program

static void convertfiles(char **filenames, int filecnt, struct Args *opts) {
	// throw error if no input files
	if (filecnt == 0) {
		eprintf(0, ERR_NOFILE);
		fprintf(stderr, MSG_SHTHLP);
		exit(EXIT_FAILURE);
	}

	// initialize convert()
	init_convert(opts);

	// convert all provided files in a loop
	for (int i = 0; i < filecnt; ++i) {
		// open input file, then open output file with temporary name
		FILE *infile = fopen_e(filenames[i], "rb");

		FILE *outfile;

		static char prefix[] = "s2t_";
		static size_t prefix_len = sizeof prefix - 1;
		size_t filename_len = strlen(filenames[i]);

		char *tmpfnam = malloc(prefix_len + filename_len + 1);
		if (tmpfnam != NULL) {
			strcpy(tmpfnam, prefix);
			strcat(tmpfnam, filenames[i]);

			outfile = fopen_e(tmpfnam, "wb");

			// do the conversion
			convert(infile, outfile);

			// close output file, then close input file
			fclose_e(outfile);
			fclose_e(infile);

			// delete input file and rename output file to original
			// input file
			remove_e(filenames[i]);
			rename_e(tmpfnam, filenames[i]);
		}
		free(tmpfnam);

		if (opts->verbose) {
			printf(VRB_SUCCES);
		}
	}
}

int main(int argc, char **argv) {
	static struct Args args;
	parseargs(&args, argc, argv);

	// treat every non-opt arg as a file to convert
	convertfiles(args.nonopts, args.nonoptcnt, &args);

	return EXIT_SUCCESS;
}
