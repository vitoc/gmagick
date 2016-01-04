Gmagick
=======
Copyright (c) 2009 Vito Chin, Mikko Koppanen

PHP extension that wraps the GraphicsMagick library. Access GraphicsMagick's capabilities via PHP.

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


Functions not supported
=======================

The functions listed below are deliberately not part of the Gmagick extension. Other functions that are present in the GraphicsMagick library but not exposed by Gmagick are likely to be added in the future.

MagickDisplayImage - only useful with X terminals.
MagickDisplayImages - only useful with X terminals.
MagickGetConfigureInfo - not implemented in GraphicsMagick
MagickFxImage - not implemented in GraphicsMagick
MagickFxImageChannel - not implemented in GraphicsMagick
MagickGetImageSize - just get the image a string and do strlen
MagickPreviewImages - not implemented in GraphicsMagick
MagickSetPassphrase - use real encryption if you need to protect data
MagickTintImage - not implemented in GraphicsMagick
MagickTransformImage - this is a 'helper' function which duplicates other easier to use functions.
