#ifndef UTILS_H
#define UTILS_H
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
