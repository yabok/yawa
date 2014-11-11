yawa
====

Synopsis
--------

**yawa** [*options*]

Description
-----------

:program:`yawa` is Yet Another Wallpaper Application, and a cleaned up fork of hsetroot

Options
-------

Gradients:
~~~~~~~~~~

-a COLOR, --add COLOR
        Add the specified hex color to range

-d DISTANCE, --distance DISTANCE
        Distance to use for adding color to range (Specify multiple times for
        successive distances). Defaults to 1 for each color.

-c, --clear
        Clear the color range

-g ANGLE, --gradient ANGLE
        Render gradient using the specified angle

Solid:
~~~~~~

-s COLOR, --solid COLOR
        Render a solid background using the specified color

Image files:
~~~~~~~~~~~~

-C IMAGE, --center IMAGE
        Render the specified image centered on the screen

-f IMAGE, --full IMAGE
        Render the specified image using the maximum aspect ratio

-F IMAGE, --fill IMAGE
        Render the specified image stretched out

-t IMAGE, --tile IMAGE
        Render the specified image tiled

Manipulations:
~~~~~~~~~~~~~~

-b RADIUS, --blur RADIUS
        Blur the current image using the specified radius

-B AMOUNT, --brightness AMOUNT
        Adjust the brightness of the current image with the specified amount of
        brightness

-G AMOUNT, --gamma AMOUNT
        Adjust the gamma level of the current image with the specifed amount

-o AMOUNT, --contrast AMOUNT
        Adjust the constrast of the current image with the specified amount

-S RADIUS, --sharpen RADIUS
        Sharpen the current image

-T COLOR, --tint COLOR
        Tint the current image using the specified hex color

--fliph
        Flip the current image horizontally

--flipv
        Flip the current image vertically

--flipd
        Flip the current image diagonally

Misc:
~~~~~

-A AMOUNT, --alpha AMOUNT
        Adjust the alpha level for colors and images

-w FILENAME, --write FILENAME
        Write the current image to the specified file. The filename specifies
        the out-format

-h, --help
        Show this help message and exit

--usage
        Print a short usage message

-?, --version
        Print program version

Examples
--------

Set the background to a nice blue to yellow horizontal gradient

        :program:`yawa --add "#ffb301" --add "#00ffff" --gradient 100`
