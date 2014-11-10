#ifndef YAWA_H
#define YAWA_H
#include <Imlib2.h>
#include <argp.h>

#include "config.h"

typedef struct
{
	int r, g, b, a;
} Color;

typedef enum
{
	Full, Fill, Center, Tile
} ImageMode;

/// Prototypes

signed
set_root_atoms(Pixmap pixmap);

signed
load_image(ImageMode mode, const char *arg, int rootW, int rootH,
           int alpha, Imlib_Image rootimg);


/// Argument parsing

static int num_add_colors;
struct arguments {
	char *image;
	char *write_file;

	char add_color[8][8];
	char *solid_color;
	char *tint_color;

	int angle;
	unsigned int blur_radius;
	unsigned int sharpen_radius;
	unsigned int contrast_amount;
	unsigned int brightness_amount;
	unsigned int gamma_amount;
	unsigned int alpha_amount;

	bool add: 1;
	bool gradient: 1;
	bool clear: 1;
	bool solid: 1;
	bool center: 1;
	bool tile: 1;
	bool full: 1;
	bool fill: 1;
	bool tint;
	bool blur;
	bool sharpen;
	bool contrast;
	bool brightness;
	bool gamma;
	bool flipv;
	bool fliph;
	bool flipd;
	bool alpha;
	bool write;
};

// Order of fields: {NAME, KEY, ARG, FLAGS, DOC, GROUP}.
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
	{"brightness", 'B',   "AMOUNT", 0, "Adjust the bightness of the current image", 4},   // Not implemented
	{"gamma",      'G',   "AMOUNT", 0, "Adjust the gamma level of the current image", 4}, // Not implemented
	{"flipv",      'v',          0, 0, "Flip the current image vertically", 4},
	{"fliph",      'h',          0, 0, "Flip the current image horizontally", 4},
	{"flipd",      'd',          0, 0, "Flip the current image diagonally", 4},

	{0,              0,          0, 0, "Misc:", -1},
	{"alpha",      'A',   "AMOUNT", 0, "Adjust alpha level for colors and images", -1},
	{"write",      'w', "FILENAME", 0, "Write the current image to a file", -1},          // Not implemented
	{0,              0,          0, 0,                                   0,  0}
};
#endif
