#ifndef COMMON__H
#define COMMON__H

#include <errno.h>

/* ERROR CODES */
#define OK 0

#define EOUTOFRANGE 1
#define EDATOKFAIL  2
#define EDATAFOUND  3

/* Optional Compiler options */
#ifndef CHECK_OK
#define CHECK_OK 0
#endif

/* Data structure Validation Responses */
#define DATASTRUCT_OK 1
#define DATASTRUCT_ERROR 0
#endif
