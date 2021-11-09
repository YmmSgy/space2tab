#include "io.h"

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

FILE *fopen_e(char *name, char *mode) {
	errno = 0;
	FILE *ret = fopen(name, mode);
	if (ret == NULL) {
		eprintf(errno, "Error: cannot open file \'%s\'", name);
		exit(EXIT_FAILURE);
	}
	return ret;
}

int fclose_e(FILE *stream) {
	errno = 0;
	int ret = fclose(stream);
	if (ret == EOF) {
		eprintf(errno, "Error: cannot close file");
		exit(EXIT_FAILURE);
	}
	return ret;
}

int remove_e(char *name) {
	errno = 0;
	int ret = remove(name);
	if (ret) {
		eprintf(errno, "Error: cannot remove file \'%s\'", name);
		exit(EXIT_FAILURE);
	}
	return ret;
}

int rename_e(char *oldname, char *newname) {
	errno = 0;
	int ret = rename(oldname, newname);
	if (ret) {
		eprintf(errno, "Error: cannot rename file \'%s\' to \'%s\'", oldname, newname);
		exit(EXIT_FAILURE);
	}
	return ret;
}

int fputc_e(int ch, FILE *stream) {
	errno = 0;
	int ret = fputc(ch, stream);
	if (ret == EOF) {
		eprintf(errno, "Error: cannot write to filestream");
		exit(EXIT_FAILURE);
	}
	return ret;
}

int fgetc_e(FILE *stream) {
	errno = 0;
	int ret = fgetc(stream);
	if (ret == EOF && ferror(stream)) {
		eprintf(errno, "Error: cannot read from filestream");
		exit(EXIT_FAILURE);
	}
	return ret;
}

static void veprintf(int err, char *fmt, va_list args) {
	// print the given format string
	vfprintf(stderr, fmt, args);

	// check if errno was set
	if (err) {
		// construct the additional error message
		// ": " + strerror(err) (+ "\0")
		static char colon[] = ": ";
		static size_t colon_len = sizeof colon - 1;

		char *str = strerror(err);
		size_t str_len = strlen(str);

		// allocate memory for the message
		char *buf = malloc(colon_len + str_len + 1);

		// if memory was allocated
		if (buf != NULL) {
			// construct the message in the allocated buffer
			strcpy(buf, colon);
			strcat(buf, str);

			// print the message buffer
			fprintf(stderr, "%s", buf);
		}

		// deallocate memory
		free(buf);

		// reset errno
		errno = 0;
	} // end if(err)

	// append newline to stderr
	fprintf(stderr, "\n");
}

void eprintf(int err, char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	veprintf(err, fmt, args);
	va_end(args);
}
