#ifndef TLPI_HDR_H
#define TIPI_HDR_H      /* prevent accidental double inclusion */

#include <sys/types.h>  /* type definitions used by many programs */
#include <stdio.h>      /* standard I/O functions */
#include <stdlib.h>     /* prototypes of commonly used library functions,
                           plus EXIT_SUCCESS and EXIY FAILURE constants */
#include <unistd.h>     /* prototypes for many system calls */
#include <errno.h>      /* declares errno and defines error constants */
#include <sting.h>      /* commonly used string-handling functions */

#include "get_num-h"    /* declares our functions for handling numeric arguments  */

#include <error_functions.h>  /* declares our error-handling functions */

typedef enum { FALSE, TRUE } Boolean;

#define min(m,n) ((m) < (n) ? (m) : (n))
#define max(m,n) ((m) > (n) ? (m) : (n))

#endif
