/*
 * yawa - Yet Another Wallpaper Application
 * Copyright (C) 2014, The YAWA Developers
 *
 * This file is part of yawa.  yawa is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, version 2.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#define _GNU_SOURCE
#include <bsd/string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#include "yawa.h"
#include "utils.h"

signed
parse_int(char *string, const char *arg)
{
	errno = 0;
	char *endptr;
	long val = strtol(string, &endptr, 10);
	if (errno != 0) {
		char *errormsg;
		asprintf(&errormsg, "parse_int: failed to parse %s", arg);

		perror(errormsg);
		free(errormsg);
		exit(-2);
	}

	if (endptr == string) {
		fprintf(stderr, "Valid %s not found\n", arg);
		exit(-2);
	}
	return (signed)val;
}

unsigned
parse_uint(char *string, const char *arg)
{
	errno = 0;
	char *endptr;
	unsigned long val = strtoul(string, &endptr, 10);
	if (errno != 0) {
		char *errormsg;
		asprintf(&errormsg, "parse_uint: failed to parse %s", arg);

		perror(errormsg);
		free(errormsg);
		exit(-2);
	}

	if (endptr == string) {
		fprintf(stderr, "Valid %s not found\n", arg);
		exit(-2);
	}
	return (unsigned)val;
}

double
parse_double(char *string, const char *arg)
{
	errno = 0;
	char *endptr;
	double val = strtod(string, &endptr);
	if (errno != 0) {
		char *errormsg;
		asprintf(&errormsg, "parse_double: failed to parse %s", arg);

		perror(errormsg);
		free(errormsg);
		exit(-2);
	}

	if (endptr == string) {
		fprintf(stderr, "Valid %s not found\n", arg);
		exit(-2);
	}
	return val;
}

bool
parse_color(char *hex, Color *c, signed alpha)
{
	if ((strlen(hex) != 7) && (strlen(hex) != 9)) {
		return false;
	}

	signed len;
	if (strlen(hex) == 9) {
		len = 4;
	} else {
		len = 3;
	}

	hex++;
	signed colors[4];
	for (signed i = 0; i < len; hex += 2, i++) {
		char color[3];
		strlcpy(color, hex, 3);

		char *endptr;
		errno = 0;
		long val = strtol(color, &endptr, 16);
		if (errno != 0) {
			perror("strtol");
			exit(-2);
		}
		if (endptr == color) {
			fprintf(stderr, "No valid hex color found\n");
			exit(-2);
		}

		colors[i] = (signed)val;
	}

	c->r = colors[0];
	c->g = colors[1];
	c->b = colors[2];
	if (len == 4) {
		c->a = colors[3];
	} else {
		c->a = alpha;
	}

	return true;
}
