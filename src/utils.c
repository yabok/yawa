#define _GNU_SOURCE
#include <bsd/string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#include "yawa.h"
#include "utils.h"

int
parse_int(char *string, char *arg)
{
	errno = 0;
	char *endptr;
	long val = strtol(string, &endptr, 10);
	if (errno != 0)
	{
		char *errormsg;
		asprintf(&errormsg, "parse_int: failed to parse %s", arg);

		perror(errormsg);
		free(errormsg);
		exit(-2);
	}

	if (endptr == string)
	{
		fprintf(stderr, "Valid %s not found\n", arg);
		exit(-2);
	}
	return (int)val;
}
