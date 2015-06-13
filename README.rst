===============
 yawa |travis|
===============

.. |travis| image:: https://img.shields.io/travis/yabok/yawa.svg?style=flat-square
   :alt: Travis Build Status
   :target: https://travis-ci.org/yabok/yawa

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
* clang
* libbsd_ (strlcpy)
* sphinx (man page)

.. _libbsd: http://libbsd.freedesktop.org/


Building
========
::

    <git clone>
    mkdir yawa/build
    cd yawa/build
    cmake ..
    make
    sudo make install


Debugging
=========

When trying to debug yawa, run the `cmake` command with the
`-DCMAKE_BUILD_TYPE=DEBUG` arguments so that the binary is built with debug
symbols for meaningful backtraces.

License
=======

Every file in this repository, except for as otherwise specified in the file
itself or in this README if not possible, is licensed under version 2 of the
GNU GPL license
