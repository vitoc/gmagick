Gmagick
=======
Copyright (c) 2009 Vito Chin, Mikko Koppanen

PHP extension that wraps the GraphicsMagick library. Access GraphicsMagick's capabilities via PHP.

[![Build Status](https://travis-ci.org/vitoc/gmagick.svg?branch=master)](https://travis-ci.org/vitoc/gmagick)

Getting Started
===============

1. Install GraphicsMagick

Download the stable from from http://www.graphicsmagick.org and build with --enable-shared option. If you do not need to work with perl, --without-perl.

Remember to run ldconfig after building GraphicsMagick to update shared library cache for immediate use.

2. Install Gmagick

Typically, as with most extensions:

$ phpize
$ ./configure
$ make
$ make install
