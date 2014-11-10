#ifndef UTILS_H
#define UTILS_H
#include <stdbool.h>

int parse_int(char *string, char *arg);
unsigned int parse_uint(char *string, char *arg);
bool parse_color(char *arg, Color *c, int a);

#endif
