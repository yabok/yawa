#ifndef UTILS_H
#define UTILS_H
#include <stdbool.h>

/// Prototypes

signed
parse_int(char *string, const char *arg);

unsigned
parse_uint(char *string, const char *arg);

double
parse_double(char *string, const char *arg);

bool
parse_color(char *hex, Color *color, signed alpha);

#endif
