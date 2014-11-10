/*
 * Copyright (C) 2003, Hyriand <hyriand@thegraveyard.org>
 * Copyright (C) 2014, Johannes Löthberg <johannes@kyriasis.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#define _GNU_SOURCE
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <Imlib2.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <argp.h>
#include <bsd/string.h>

#include "yawa.h"
#include "config.h"


/* Order of parameters: KEY, ARG, STATE. */
static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
	struct arguments *arguments = state->input;
	char *endptr;
	long val;
	errno = 0;

	switch (key) {
		case 'a':
			arguments->add = true;
			strncpy(arguments->add_color[num_add_colors], arg,
			        sizeof(arguments->add_color[0]) - 1);
			num_add_colors += 1;
			break;
		case 'g':
			arguments->gradient = true;
			val = strtol(arg, &endptr, 10);
			arguments->angle = (int)val;

			if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
			    || (errno != 0 && val == 0))
			{
				perror("strtol");
				exit(-2);
			}

			if (endptr == arg)
			{
				fprintf(stderr, "Valid gradiant angle not found\n");
				exit(-2);
			}
			break;
		case 'c':
			arguments->clear = true;
			break;
		case 's':
			arguments->solid = true;
			arguments->color = arg;
			break;
		case 'C':
			arguments->center = true;
			arguments->image = arg;
			break;
		case 't':
			arguments->tile = true;
			arguments->image = arg;
			break;
		case 'f':
			arguments->full = true;
			arguments->image = arg;
			break;
		case 'F':
			arguments->fill = true;
			arguments->image = arg;
			break;
		case 'T':
			arguments->tint = true;
			arguments->color = arg;
			break;

		case 'v':
			arguments->flipv = true;
			break;
		case 'h':
			arguments->fliph = true;
			break;
		case 'd':
			arguments->flipd = true;
			break;

		case 'A':
			arguments->alpha = true;
			val = strtol(arg, &endptr, 10);
			arguments->alpha_amount = (int)val;

			if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
			    || (errno != 0 && val == 0)) {
				perror("strtol");
				exit(-2);
			}

			if (endptr == arg) {
				fprintf(stderr, "Valid alpha amount not found\n");
				exit(-2);
			}
			break;
		default:
			return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

/* The ARGP structure itself. */
static struct argp argp = {options, parse_opt, "", doc, NULL, NULL, 0};

// Globals:
static Display *display;
static int screen;

// Adapted from fluxbox' bsetroot
int
set_root_atoms (Pixmap pixmap)
{
	Atom atom_root, atom_eroot, type;
	unsigned char *data_root, *data_eroot;
	int format;
	unsigned long length, after;

	atom_root = XInternAtom(display, "_XROOTMAP_ID", True);
	atom_eroot = XInternAtom(display, "ESETROOT_PMAP_ID", True);

	// doing this to clean up after old background
	if (atom_root != None && atom_eroot != None)
	{
		XGetWindowProperty(display, RootWindow(display, screen),
		                   atom_root, 0L, 1L, False, AnyPropertyType,
		                   &type, &format, &length, &after, &data_root);
		if (type == XA_PIXMAP)
		{
			XGetWindowProperty(display, RootWindow(display, screen),
			                   atom_eroot, 0L, 1L, False, AnyPropertyType,
			                   &type, &format, &length, &after, &data_eroot);
			if (data_root && data_eroot && type == XA_PIXMAP &&
			    *(data_root) == *(data_eroot))
			{
				XKillClient(display, *(data_root));
			}
		}
	}

	atom_root = XInternAtom(display, "_XROOTPMAP_ID", False);
	atom_eroot = XInternAtom(display, "ESETROOT_PMAP_ID", False);

	if (atom_root == None || atom_eroot == None)
	{
		return 0;
	}

	// setting new background atoms
	XChangeProperty(display, RootWindow(display, screen),
	                atom_root, XA_PIXMAP, 32, PropModeReplace,
	                (unsigned char *) &pixmap, 1);
	XChangeProperty(display, RootWindow(display, screen), atom_eroot,
	                XA_PIXMAP, 32, PropModeReplace, (unsigned char *) &pixmap,
	                1);

	return 1;
}

int
parse_color (char *hex, PColor c, int a)
{
	if ((strlen(hex) != 7) && (strlen(hex) != 9))
		return 0;

	int len;
	if (strlen(hex) == 9) {
		len = 4;
	} else {
		len = 3;
	}

	hex++;
	int colors[4];
	for (int i = 0; i < len; hex += 2, i++) {
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

		colors[i] = (int)val;
	}

	c->r = colors[0];
	c->g = colors[1];
	c->b = colors[2];
	if (len == 4) {
		c->a = colors[3];
	} else {
		c->a = a;
	}

	return 1;
}

int
load_image (ImageMode mode, const char *arg, int rootW, int rootH,
            int alpha, Imlib_Image rootimg)
{
	int imgW, imgH, o;
	Imlib_Image buffer = imlib_load_image(arg);

	if (!buffer)
		return 0;

	imlib_context_set_image(buffer);
	imgW = imlib_image_get_width(), imgH = imlib_image_get_height();

	if (alpha < 255)
	{
		// Create alpha-override mask
		imlib_image_set_has_alpha(1);
		Imlib_Color_Modifier modifier = imlib_create_color_modifier();
		imlib_context_set_color_modifier(modifier);

		DATA8 red[256], green[256], blue[256], alph[256];
		imlib_get_color_modifier_tables(red, green, blue, alph);
		for (o = 0; o < 256; o++)
			alph[o] = (DATA8) alpha;
		imlib_set_color_modifier_tables(red, green, blue, alph);

		imlib_apply_color_modifier();
		imlib_free_color_modifier();
	}

	imlib_context_set_image(rootimg);
	if (mode == Fill)
	{
		imlib_blend_image_onto_image(buffer, 0, 0, 0, imgW, imgH,
		                             0, 0, rootW, rootH);
	}
	else if (mode == Full)
	{
		double aspect = ((double) rootW) / imgW;
		int top, left;
		if ((int) (imgH * aspect) > rootH)
			aspect = (double) rootH / (double) imgH;
		top = (rootH - (int) (imgH * aspect)) / 2;
		left = (rootW - (int) (imgW * aspect)) / 2;
		imlib_blend_image_onto_image(buffer, 0, 0, 0, imgW, imgH,
		                             left, top, (int) (imgW * aspect),
		                             (int) (imgH * aspect));
	}
	else
	{
		int left = (rootW - imgW) / 2, top = (rootH - imgH) / 2;

		if (mode == Tile)
		{
			int x, y;
			for (; left > 0; left -= imgW);
			for (; top > 0; top -= imgH);

			for (x = left; x < rootW; x += imgW)
				for (y = top; y < rootH; y += imgH)
					imlib_blend_image_onto_image(buffer, 0, 0, 0, imgW, imgH,
					                              x, y, imgW, imgH);
		}
		else
		{
			imlib_blend_image_onto_image(buffer, 0, 0, 0, imgW, imgH,
			                             left, top, imgW, imgH);
		}
	}

	imlib_context_set_image(buffer);
	imlib_free_image();

	imlib_context_set_image(rootimg);

	return 1;
}

int
main (int argc, char **argv)
{
	struct arguments arguments = {
	    "", "", 0, 0, false, false, false, false, false,
	    false, false, false, false, false, false, false,
	    false, false, false, false, false, false, false,
	    {{0}} // add_color array
	};

	/* Where the magic happens */
	argp_parse(&argp, argc, argv, 0, 0, &arguments);

	Visual *vis;
	Colormap cm;
	Display *_display;
	Imlib_Context *context;
	Imlib_Image image;
	int width, height, depth, alpha;
	int i = 0;
	Pixmap pixmap;
	Imlib_Color_Modifier modifier = NULL;
	_display = XOpenDisplay(NULL);

	for (screen = 0; screen < ScreenCount(_display); screen++)
	{
		display = XOpenDisplay(NULL);

		context = imlib_context_new();
		imlib_context_push(context);

		imlib_context_set_display(display);
		vis = DefaultVisual(display, screen);
		cm = DefaultColormap(display, screen);
		width = DisplayWidth(display, screen);
		height = DisplayHeight(display, screen);
		depth = DefaultDepth(display, screen);

		pixmap =
			XCreatePixmap(display, RootWindow(display, screen),
			              (unsigned int) width, (unsigned int) height,
			              (unsigned int) depth);

		imlib_context_set_visual(vis);
		imlib_context_set_colormap(cm);
		imlib_context_set_drawable(pixmap);
		imlib_context_set_color_range(imlib_create_color_range());

		image = imlib_create_image(width, height);
		imlib_context_set_image(image);

		imlib_context_set_color(0, 0, 0, 255);
		imlib_image_fill_rectangle(0, 0, width, height);

		imlib_context_set_dither(1);
		imlib_context_set_blend(1);

		if (arguments.alpha)
			alpha = arguments.alpha;
		else
			alpha = 255;

		if (modifier != NULL)
		{
			imlib_apply_color_modifier();
			imlib_free_color_modifier();
		}
		modifier = imlib_create_color_modifier();
		imlib_context_set_color_modifier(modifier);

		if (arguments.solid)
		{
			Color c;
			if (parse_color(arguments.color, &c, alpha) == 0)
			{
				fprintf(stderr, "Bad color (%s)\n", arguments.color);
				exit(-2);
			}
			imlib_context_set_color(c.r, c.g, c.b, c.a);
			imlib_image_fill_rectangle(0, 0, width, height);
		}
		if (arguments.clear)
		{
			imlib_free_color_range();
			imlib_context_set_color_range(imlib_create_color_range());
		}
		// TODO: Add back -addd
		if (arguments.add)
		{
			for (i = 0; i < num_add_colors; i++)
			{
				Color c;
				if (parse_color(arguments.add_color[i], &c, alpha) == 0)
				{
					fprintf(stderr, "Bad color (%s)\n", arguments.add_color[i]);
					exit(-2);
				}
				imlib_context_set_color(c.r, c.g, c.b, c.a);
				imlib_add_color_to_color_range(1);
			}
		}
		if (arguments.gradient)
		{
			imlib_image_fill_color_range_rectangle(0, 0, width, height, arguments.angle);
		}
		if (arguments.fill)
		{
			if (load_image(Fill, arguments.image, width, height, alpha, image) == 0)
			{
				fprintf(stderr, "Bad image (%s)\n", arguments.image);
				continue;
			}
		}
		if (arguments.full)
		{
			if (load_image(Full, arguments.image, width, height, alpha, image) == 0)
			{
				fprintf(stderr, "Bad image (%s)\n", arguments.image);
				continue;
			}
		}
		if (arguments.tile)
		{
			if (load_image(Tile, arguments.image, width, height, alpha, image) == 0)
			{
				fprintf(stderr, "Bad image (%s)\n", arguments.image);
				continue;
			}
		}
		if (arguments.center)
		{
			if (load_image(Center, arguments.image, width, height, alpha, image) == 0)
			{
				fprintf(stderr, "Bad image (%s)\n", arguments.image);
				continue;
			}
		}

		if (arguments.tint)
		{
			Color c;
			DATA8 r[256], g[256], b[256], a[256];
			int j;

			if (parse_color(arguments.color, &c, 255) == 0)
			{
				fprintf(stderr, "Bad color\n");
				exit(-2);
			}

			imlib_get_color_modifier_tables(r, g, b, a);

			for (j = 0; j < 256; j++)
			{
				r[j] = (DATA8) (((double) r[j] / 255.0) * (double) c.r);
				g[j] = (DATA8) (((double) g[j] / 255.0) * (double) c.g);
				b[j] = (DATA8) (((double) b[j] / 255.0) * (double) c.b);
			}

			imlib_set_color_modifier_tables(r, g, b, a);
		}
		if (arguments.blur)
		{
			int intval;
			if (sscanf(argv[i], "%i", &intval) == 0)
			{
				fprintf(stderr, "Bad value (%s)\n", argv[i]);
				continue;
			}

			imlib_image_blur(intval);
		}
		if (arguments.sharpen)
		{
			int intval;
			if (sscanf(argv[i], "%i", &intval) == 0)
			{
				fprintf(stderr, "Bad value (%s)\n", argv[i]);
				continue;
			}
			imlib_image_sharpen(intval);
		}
		if (arguments.contrast)
		{
			double dblval;
			if (sscanf(argv[i], "%lf", &dblval) == 0)
			{
				fprintf(stderr, "Bad value (%s)\n", argv[i]);
				continue;
			}
			imlib_modify_color_modifier_contrast(dblval);
		}
		if (arguments.brightness)
		{
			double dblval;
			if (sscanf(argv[i], "%lf", &dblval) == 0)
			{
				fprintf(stderr, "Bad value (%s)\n", argv[i]);
				continue;
			}
			imlib_modify_color_modifier_brightness(dblval);
		}
		if (arguments.gamma)
		{
			double dblval;
			if (sscanf(argv[i], "%lf", &dblval) == 0)
			{
				fprintf(stderr, "Bad value (%s)\n", argv[i]);
				continue;
			}
			imlib_modify_color_modifier_gamma(dblval);
		}

		if (arguments.flipv)
		{
			imlib_image_flip_vertical();
		}
		if (arguments.fliph)
		{
			imlib_image_flip_horizontal();
		}
		if (arguments.flipd)
		{
			imlib_image_flip_diagonal();
		}

		if (arguments.write)
		{
			imlib_save_image(argv[i]);
		}

		if (modifier != NULL)
		{
			imlib_context_set_color_modifier(modifier);
			imlib_apply_color_modifier();
			imlib_free_color_modifier();
			modifier = NULL;
		}
		imlib_render_image_on_drawable(0, 0);
		imlib_free_image();
		imlib_free_color_range();

		if (set_root_atoms(pixmap) == 0)
			fprintf(stderr, "Couldn't create atoms...\n");

		XKillClient(display, AllTemporary);
		XSetCloseDownMode(display, RetainTemporary);

		XSetWindowBackgroundPixmap(display, RootWindow(display, screen),
		                            pixmap);
		XClearWindow(display, RootWindow(display, screen));

		XFlush(display);
		XSync(display, False);

		imlib_context_pop();
		imlib_context_free(context);
	}

	return 0;
}
