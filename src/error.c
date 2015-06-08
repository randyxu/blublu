/*******************************
  print error information
  Reference: CSAPP
********************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"

void unix_error(char *msg) /* Unix-style error */
{
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

void posix_error(int code, char *msg) /* Posix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(code));
    exit(0);
}
