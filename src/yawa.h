#ifndef YAWA_H
#define YAWA_H
#include "config.h"

typedef struct
{
	int r, g, b, a;
} Color, *PColor;

typedef enum
{ Full, Fill, Center, Tile } ImageMode;

int set_root_atoms (Pixmap pixmap);
int parse_color (char *arg, PColor c, int a);
int load_image (ImageMode mode, const char *arg, int rootW, int rootH, int alpha,
                Imlib_Image rootimg);

static char doc[] = "yawa -- Yet Another Wallpaper Application";
const char *argp_program_version = PACKAGE_STRING;
const char *argp_program_bug_address = "<" PACKAGE_BUGREPORT ">";

static int num_add_colors;
struct arguments {
	char *image;
	char *color;
	int angle;
	int alpha_amount;

	bool add: 1;
	bool gradient: 1;
	bool clear: 1;
	bool solid: 1;
	bool center: 1;
	bool tile: 1;
	bool full: 1;
	bool fill: 1;
	bool tint: 1;
	bool blur: 1;
	bool sharpen: 1;
	bool contrast: 1;
	bool brightness: 1;
	bool gamma: 1;
	bool flipv: 1;
	bool fliph: 1;
	bool flipd;
	bool alpha;
	bool write;
	char add_color[9][9];
};

/* Order of fields: {NAME, KEY, ARG, FLAGS, DOC, GROUP}. */
static struct argp_option options[] =
{
	{0,              0,          0, 0, "Gradients:", 1},
	{"add",        'a',    "COLOR", 0, "Add color to range using distance 1", 1},
	// TODO: Figure out what to do about `-addd <color> <distance>
	{"gradient",   'g',    "ANGLE", 0, "Render gradient using specified angle", 1},
	{"clear",      'c',          0, 0, "Clear the color range", 1},

	{0,              0,          0, 0, "Solid:", 2},
	{"solid",      's',    "COLOR", 0, "Render a solid using the specified color", 2},

	{0,              0,          0, 0, "Image files:", 3},
	{"center",     'C',    "IMAGE", 0, "Render an image centered on the screen", 3},
	{"tile",       't',    "IMAGE", 0, "Render an image tiled", 3},
	{"full",       'f',    "IMAGE", 0, "Render an image maximum aspect", 3},
	{"fill",       'F',    "IMAGE", 0, "Render an image stretched", 3},

	{0,              0,          0, 0, "Manipulations:", 4},
	{"tint",       'T',    "COLOR", 0, "Tint current image", 4},
	{"blur",       'b',   "RADIUS", 0, "Blur the current image", 4},                      // Not implemented
	{"sharpen",    'S',   "RADIUS", 0, "Sharpen the current image", 4},                   // Not implemented
	{"contrast",   'o',   "AMOUNT", 0, "Adjust the contrast of the current image", 4},    // Not implemented
	{"brightness", 'G',   "AMOUNT", 0, "Adjust the bightness of the current image", 4},   // Not implemented
	{"gamma",      'G',   "AMOUNT", 0, "Adjust the gamma level of the current image", 4}, // Not implemented
	{"flipv",      'v',          0, 0, "Flip the current image vertically", 4},           // Not implemented
	{"fliph",      'h',          0, 0, "Flip the current image horizontally", 4},         // Not implemented
	{"flipd",      'd',          0, 0, "Flip the current image diagonally", 4},           // Not implemented

	{0,              0,          0, 0, "Misc:", -1},
	{"alpha",      'A',   "AMOUNT", 0, "Adjust alpha level for colors and images", -1},
	{"write",      'w', "FILENAME", 0, "Write the current image to a file", -1},          // Not implemented
	{0,              0,          0, 0,                                   0,  0}
};
#endif
