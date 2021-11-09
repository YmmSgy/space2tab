#ifndef MSGS_H
#define MSGS_H

#define MSG_HUSAGE							\
"Usage: space2tab [OPTIONS] FILE...\n"

// short help
#define MSG_SHTHLP							\
MSG_HUSAGE								\
"Type space2tab -h for help.\n"

// help message
#define MSG_LNGHLP							\
MSG_HUSAGE								\
"Converts start-of-line spaces in the specified files to tabs.\n"	\
"\n"									\
"Options:\n"								\
"  -h		Display this help message\n"				\
"  -V		Display version info\n"					\
"  -v		Enable verbose mode\n"					\
"  -s N		Change tabsize to N, default is 8\n"

// verbose mode messages
#define VRB_SUCCES							\
"File converted successfully.\n"

// error messages
// NOTE: error messages don't have \n appended, for conditional printing of
// strerr where applicable
#define ERR_PREFIX							\
"Error: "

#define ERR_NOFILE							\
ERR_PREFIX "no input files"						\

#define ERR_OPTARG							\
ERR_PREFIX "missing option argument"

#define ERR_BADOPT							\
ERR_PREFIX "unknown option"

#define ERR_NOTSIZ							\
ERR_PREFIX "invalid tabsize \'%s\'"

#define ERR_BIGSIZ							\
ERR_PREFIX "tabsize too large (max %u)"

#define ERR_ZEROSZ							\
ERR_PREFIX "tabsize cannot be zero"

#define ERR_BIGSPC							\
ERR_PREFIX "line contains too many spaces (max %u)"

#endif // MSGS_H
