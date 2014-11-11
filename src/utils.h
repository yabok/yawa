#ifndef UTILS_H
#define UTILS_H
#include <stdbool.h>

/// Prototypes

signed
parse_int(char *string, char *arg);

unsigned
parse_uint(char *string, char *arg);

double
parse_double(char *string, char *arg);

bool
parse_color(char *hex, Color *color, signed alpha);

#endif
