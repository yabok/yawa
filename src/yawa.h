#ifndef YAWA_H
#define YAWA_H
#include <Imlib2.h>
#include <argp.h>

#include "config.h"

typedef struct
{
	signed r, g, b, a;
} Color;

typedef enum
{
	Full, Fill, Center, Tile
} ImageMode;

/// Prototypes

signed
set_root_atoms(Pixmap pixmap);

signed
load_image(ImageMode mode, const char *arg, signed rootW, signed rootH,
           signed alpha, Imlib_Image rootimg);


/// Argument parsing

static signed num_add_colors = 0;
static signed num_distances = 0;
struct arguments {
	char *image;
	char *write_file;

	char   add_color[8][8];
	signed distance[8];

	char *solid_color;
	char *tint_color;

	signed   angle;
	unsigned blur_radius;
	unsigned sharpen_radius;
	double   contrast_amount;
	double   brightness_amount;
	double   gamma_amount;
	unsigned alpha_amount;

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
static struct argp_option options[] = {
	{0,              0,          0, 0, "Gradients:", 1},
	{"add",        'a',    "COLOR", 0, "Add color to range", 1},
	{"distance",   'd', "DISTANCE", 0, "Distance to use for adding color to range. "
	                                   "Defaults to 1 for each color", 1},
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
	{"blur",       'b',   "RADIUS", 0, "Blur the current image", 4},
	{"sharpen",    'S',   "RADIUS", 0, "Sharpen the current image", 4},
	{"contrast",   'o',   "AMOUNT", 0, "Adjust the contrast of the current image", 4},
	{"brightness", 'B',   "AMOUNT", 0, "Adjust the bightness of the current image", 4},
	{"gamma",      'G',   "AMOUNT", 0, "Adjust the gamma level of the current image", 4},
	{"flipv",        1,          0, 0, "Flip the current image vertically", 4},
	{"fliph",        2,          0, 0, "Flip the current image horizontally", 4},
	{"flipd",        3,          0, 0, "Flip the current image diagonally", 4},

	{0,              0,          0, 0, "Misc:", -1},
	{"alpha",      'A',   "AMOUNT", 0, "Adjust alpha level for colors and images", -1},
	{"write",      'w', "FILENAME", 0, "Write the current image to a file", -1},
	{0,              0,          0, 0,                                   0,  0}
};

#endif
