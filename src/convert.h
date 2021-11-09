#ifndef CONVERT_H
#define CONVERT_H

#include <stdio.h>

struct Args;

// sets up conversion environment. call this before the first call to convert()
extern void init_convert(struct Args *opts);

// converts spaces to tabs for a file
extern void convert(FILE *infile, FILE *outfile);

#endif // CONVERT_H
