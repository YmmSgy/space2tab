#ifndef IO_H
#define IO_H

#include <stdlib.h>
#include <stdio.h>

FILE *fopen_e(char *name, char *mode);
int fclose_e(FILE *stream);
int remove_e(char *name);
int rename_e(char *oldname, char *newname);
int fputc_e(int ch, FILE *stream);
int fgetc_e(FILE *stream);

// prints fmt to stderr, appending strerror if err != 0
// then appends \n regardless of err
void eprintf(int err, char *fmt, ...);

#endif // IO_H
