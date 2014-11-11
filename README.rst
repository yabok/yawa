======
 yawa
======
-----------------------------------
 Yet another wallpaper application
-----------------------------------

yawa is a now feature-complete fork of hsetroot, because there hasn't been
a release in over 10 years, because the upsteam website has been down for
years, and for one because I dislike how it handled option parsing.

So here is yawa with rewritten option parsing using glibc’s argp, all
warnings fixed and more argument checking, and hopefully also more
readable. (God I don’t know how upstream fucked the formating up so badly)

Dependencies
============

* glibc (argp argument parsing)
* imlib2
* libx11

Building
========
::

    <git clone>
    cmake -g 'Unix Makefiles' .
    make
    sudo make install
