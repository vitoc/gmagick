/*
   +----------------------------------------------------------------------+
   | PHP Version 5 / Gmagick	                                          |
   +----------------------------------------------------------------------+
   | Copyright (c) 2009 Vito Chin, Mikko Koppanen                         |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Author: Mikko Kopppanen <mkoppanen@php.net>                          |
   |         Vito Chin <vito@php.net>		                          |
   +----------------------------------------------------------------------+
*/

#ifndef HAVE_PHP_GMAGICK_H
#define HAVE_PHP_GMAGICK_H

/* Define Extension Properties */
#define PHP_GMAGICK_EXTNAME    "gmagick"
#define PHP_GMAGICK_VERSION    "2.0.1RC1"
#define PHP_GMAGICK_EXTNUM     00001
#define MAX_BUFFER_SIZE        1024

/* Include GraphicsMagick header */
#include <stdio.h>
#include <sys/types.h>
#if defined(PHP_WIN32) && !defined(ssize_t)
/* XXX actually wand_api.h should be included after php.h,
	ssize_t were there with much more probability. */
# ifdef _WIN64
typedef __int64 ssize_t;
# else 
typedef long ssize_t;
# endif
#endif
#include <wand/wand_api.h>

/* Include some required php headers */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "Zend/zend_exceptions.h"
#include "Zend/zend_interfaces.h"
#include "ext/standard/php_string.h"
#include "ext/standard/info.h"
#include "ext/standard/php_filestat.h"

#if GMAGICK_LIB_MASK >= 1003018
	#define HAVE_GMAGICK_SET_IMAGE_PAGE 1
#endif

#if GMAGICK_LIB_MASK >= 1003020
	#define HAVE_GMAGICK_SET_IMAGE_GRAVITY 1
#endif

/* Objects */
typedef struct _php_gmagick_object  {
	MagickWand *magick_wand;
	int next_out_of_bound;
	zend_object zo;
} php_gmagick_object;

/* Structure for GmagickDraw object. */
typedef struct _php_gmagickdraw_object  {
	DrawingWand *drawing_wand;
	zend_object zo;
} php_gmagickdraw_object;

typedef struct _php_gmagickpixel_object  {
	PixelWand *pixel_wand;
	zend_object zo;
} php_gmagickpixel_object;

extern zend_module_entry gmagick_module_entry;
#define phpext_gmagick_ptr &gmagick_module_entry

/* Colors */
#define GMAGICK_COLOR_BLACK 11
#define GMAGICK_COLOR_BLUE 12
#define GMAGICK_COLOR_CYAN 13
#define GMAGICK_COLOR_GREEN 14
#define GMAGICK_COLOR_RED 15
#define GMAGICK_COLOR_YELLOW 16
#define GMAGICK_COLOR_MAGENTA 17
#define GMAGICK_COLOR_OPACITY 18
#define GMAGICK_COLOR_ALPHA 19
#define GMAGICK_COLOR_FUZZ 20

/* Internal constants */
#define GMAGICK_READ_IMAGE 1
#define GMAGICK_WRITE_IMAGE 2

/* Class enum */
#define GMAGICK_CLASS 1
#define GMAGICKDRAW_CLASS 2
#define GMAGICKPIXEL_CLASS 3

/* Free filename constants */
#define GMAGICK_DONT_FREE_FILENAME 0
#define GMAGICK_FREE_FILENAME 1

/* Read / write constants */
#define GMAGICK_READ_WRITE_NO_ERROR 0
#define GMAGICK_READ_WRITE_SAFE_MODE_ERROR 1
#define GMAGICK_READ_WRITE_OPEN_BASEDIR_ERROR 2
#define GMAGICK_READ_WRITE_UNDERLYING_LIBRARY 3
#define GMAGICK_READ_WRITE_PERMISSION_DENIED 4
#define GMAGICK_READ_WRITE_FILENAME_TOO_LONG 5
#define GMAGICK_READ_WRITE_PATH_DOES_NOT_EXIST 6

#ifndef DefaultChannels
# define DefaultChannels (AllChannels &~ OpacityChannel)
#endif

/* Class entries */
extern zend_class_entry *php_gmagick_sc_entry;
extern zend_class_entry *php_gmagickdraw_sc_entry;
extern zend_class_entry *php_gmagickpixel_sc_entry;
extern zend_class_entry *php_gmagick_exception_class_entry;
extern zend_class_entry *php_gmagickdraw_exception_class_entry;
extern zend_class_entry *php_gmagickpixel_exception_class_entry;

/* Forward declarations */
PHP_METHOD(gmagick, __construct);
PHP_METHOD(gmagick, __tostring);
PHP_METHOD(gmagick, readimage);
PHP_METHOD(gmagick, writeimage);
PHP_METHOD(gmagick, resizeimage);
PHP_METHOD(gmagick, thumbnailimage);
PHP_METHOD(gmagick, clear);
PHP_METHOD(gmagick, cropimage);
PHP_METHOD(gmagick, cropthumbnailimage);
PHP_METHOD(gmagick, compositeimage);
PHP_METHOD(gmagick, drawimage);
PHP_METHOD(gmagick, addimage);
PHP_METHOD(gmagick, addnoiseimage);
PHP_METHOD(gmagick, annotateimage);
PHP_METHOD(gmagick, blurimage);
PHP_METHOD(gmagick, borderimage);
PHP_METHOD(gmagick, thresholdimage);
PHP_METHOD(gmagick, charcoalimage);
PHP_METHOD(gmagick, chopimage);
PHP_METHOD(gmagick, coalesceimages);
PHP_METHOD(gmagick, commentimage);
PHP_METHOD(gmagick, current);
PHP_METHOD(gmagick, cyclecolormapimage);
PHP_METHOD(gmagick, deconstructimages);
PHP_METHOD(gmagick, despeckleimage);
PHP_METHOD(gmagick, destroy);
PHP_METHOD(gmagick, edgeimage);
PHP_METHOD(gmagick, embossimage);
PHP_METHOD(gmagick, enhanceimage);
PHP_METHOD(gmagick, equalizeimage);
PHP_METHOD(gmagick, flattenimages);
PHP_METHOD(gmagick, flipimage);
PHP_METHOD(gmagick, flopimage);
PHP_METHOD(gmagick, frameimage);
PHP_METHOD(gmagick, gammaimage);
PHP_METHOD(gmagick, getcopyright);
PHP_METHOD(gmagick, getfilename);
PHP_METHOD(gmagick, getimagebackgroundcolor);
PHP_METHOD(gmagick, getimageblob);
PHP_METHOD(gmagick, getimagesblob);
PHP_METHOD(gmagick, setimagebackgroundcolor);
PHP_METHOD(gmagick, getimageblueprimary);
PHP_METHOD(gmagick, getimagebordercolor);
PHP_METHOD(gmagick, getimagechanneldepth);
PHP_METHOD(gmagick, setimageblueprimary);
PHP_METHOD(gmagick, setimagebordercolor);
PHP_METHOD(gmagick, setimagechanneldepth);
PHP_METHOD(gmagick, setimagecolorspace);
PHP_METHOD(gmagick, setinterlacescheme);
PHP_METHOD(gmagick, getimagecolorspace);
PHP_METHOD(gmagick, getimagecolors);
PHP_METHOD(gmagick, getimagecompose);
PHP_METHOD(gmagick, getimagedelay);
PHP_METHOD(gmagick, getimagedepth);
PHP_METHOD(gmagick, getnumberimages);
PHP_METHOD(gmagick, setimagecompose);
PHP_METHOD(gmagick, setimagecompression);
PHP_METHOD(gmagick, getimagecompression);
PHP_METHOD(gmagick, setimagedelay);
PHP_METHOD(gmagick, setimagedepth);
PHP_METHOD(gmagick, getimagedispose);
PHP_METHOD(gmagick, setimagedispose);
PHP_METHOD(gmagick, setfilename);
PHP_METHOD(gmagick, getimage);
PHP_METHOD(gmagick, setimage);
PHP_METHOD(gmagick, getimageextrema);
PHP_METHOD(gmagick, getimagefilename);
PHP_METHOD(gmagick, setimagefilename);
PHP_METHOD(gmagick, getimageformat);
PHP_METHOD(gmagick, setimageformat);
#if GMAGICK_LIB_MASK >= 1003007
PHP_METHOD(gmagick, setcompressionquality);
#endif
PHP_METHOD(gmagick, getimagegamma);
PHP_METHOD(gmagick, setimagegamma);
PHP_METHOD(gmagick, getimagegreenprimary);
PHP_METHOD(gmagick, setimagegreenprimary);
PHP_METHOD(gmagick, getimageheight);
PHP_METHOD(gmagick, getimagehistogram);
PHP_METHOD(gmagick, getimageindex);
PHP_METHOD(gmagick, setimageindex);
PHP_METHOD(gmagick, getimageinterlacescheme);
PHP_METHOD(gmagick, setimageinterlacescheme);
PHP_METHOD(gmagick, getimageiterations);
#if GMAGICK_LIB_MASK >= 1005000
PHP_METHOD(gmagick, getimagematte);
#endif
PHP_METHOD(gmagick, getimagegeometry);
PHP_METHOD(gmagick, getimagemattecolor);
#ifdef GMAGICK_HAVE_SET_IMAGE_PAGE
PHP_METHOD(gmagick, getimagepage);
#endif // GMAGICK_HAVE_SET_IMAGE_PAGE
PHP_METHOD(gmagick, getimageprofile);
PHP_METHOD(gmagick, getimageredprimary);
PHP_METHOD(gmagick, getimagerenderingintent);
PHP_METHOD(gmagick, getimageresolution);
PHP_METHOD(gmagick, getimagescene);
PHP_METHOD(gmagick, getimagesignature);
PHP_METHOD(gmagick, getimagetype);
PHP_METHOD(gmagick, setimageiterations);
PHP_METHOD(gmagick, setimageprofile);
PHP_METHOD(gmagick, setimageredprimary);
PHP_METHOD(gmagick, setimagerenderingintent);
PHP_METHOD(gmagick, setimageresolution);
PHP_METHOD(gmagick, setresolution);
PHP_METHOD(gmagick, setimagescene);
PHP_METHOD(gmagick, setimagetype);
#ifdef GMAGICK_HAVE_SET_IMAGE_PAGE
PHP_METHOD(gmagick, setimagepage);
#endif
PHP_METHOD(gmagick, getimageunits);
PHP_METHOD(gmagick, getimagewhitepoint);
PHP_METHOD(gmagick, getimagewidth);
PHP_METHOD(gmagick, getpackagename);
PHP_METHOD(gmagick, getquantumdepth);
PHP_METHOD(gmagick, getreleasedate);
PHP_METHOD(gmagick, getresourcelimit);
PHP_METHOD(gmagick, setresourcelimit);
PHP_METHOD(gmagick, getsamplingfactors);
PHP_METHOD(gmagick, getsize);
PHP_METHOD(gmagick, setimageunits);
PHP_METHOD(gmagick, setimagewhitepoint);
PHP_METHOD(gmagick, setsamplingfactors);
PHP_METHOD(gmagick, setsize);
PHP_METHOD(gmagick, getversion);
PHP_METHOD(gmagick, hasnextimage);
PHP_METHOD(gmagick, haspreviousimage);
PHP_METHOD(gmagick, implodeimage);
PHP_METHOD(gmagick, levelimage);
PHP_METHOD(gmagick, labelimage);
PHP_METHOD(gmagick, magnifyimage);
PHP_METHOD(gmagick, mapimage);
PHP_METHOD(gmagick, medianfilterimage);
PHP_METHOD(gmagick, negateimage);
PHP_METHOD(gmagick, minifyimage);
PHP_METHOD(gmagick, modulateimage);
PHP_METHOD(gmagick, motionblurimage);
PHP_METHOD(gmagick, nextimage);
PHP_METHOD(gmagick, newimage);
PHP_METHOD(gmagick, normalizeimage);
PHP_METHOD(gmagick, oilpaintimage);
PHP_METHOD(gmagick, previousimage);
PHP_METHOD(gmagick, profileimage);
PHP_METHOD(gmagick, quantizeimage);
PHP_METHOD(gmagick, quantizeimages);
PHP_METHOD(gmagick, queryfonts);
PHP_METHOD(gmagick, queryfontmetrics);
PHP_METHOD(gmagick, queryformats);
PHP_METHOD(gmagick, radialblurimage);
PHP_METHOD(gmagick, raiseimage);
PHP_METHOD(gmagick, readimageblob);
PHP_METHOD(gmagick, readimagefile);
PHP_METHOD(gmagick, reducenoiseimage);
PHP_METHOD(gmagick, removeimage);
PHP_METHOD(gmagick, removeimageprofile);
PHP_METHOD(gmagick, resampleimage);
PHP_METHOD(gmagick, rollimage);
PHP_METHOD(gmagick, rotateimage);
PHP_METHOD(gmagick, scaleimage);
PHP_METHOD(gmagick, separateimagechannel);
PHP_METHOD(gmagick, sharpenimage);
PHP_METHOD(gmagick, shearimage);
PHP_METHOD(gmagick, solarizeimage);
PHP_METHOD(gmagick, spreadimage);
PHP_METHOD(gmagick, stripimage);
PHP_METHOD(gmagick, swirlimage);
PHP_METHOD(gmagick, trimimage);
PHP_METHOD(gmagick, sampleimage);
PHP_METHOD(gmagick, cloneimage);
PHP_METHOD(gmagick, appendimages);
PHP_METHOD(gmagick, unsharpmaskimage);
PHP_METHOD(gmagick, adaptivethresholdimage);
PHP_METHOD(gmagick, affinetransformimage);
PHP_METHOD(gmagick, averageimages);
PHP_METHOD(gmagick, blackthresholdimage);
PHP_METHOD(gmagick, colordecisionlist);
PHP_METHOD(gmagick, clipimage);
PHP_METHOD(gmagick, clippathimage);
PHP_METHOD(gmagick, colorfloodfillimage);
PHP_METHOD(gmagick, colorizeimage);
PHP_METHOD(gmagick, compareimagechannels);
PHP_METHOD(gmagick, compareimages);
PHP_METHOD(gmagick, contrastimage);
PHP_METHOD(gmagick, convolveimage);
PHP_METHOD(gmagick, extentimage);
PHP_METHOD(gmagick, fximage);
PHP_METHOD(gmagick, getimageattribute);
PHP_METHOD(gmagick, getimagechannelextrema);
PHP_METHOD(gmagick, getimagechannelmean);
PHP_METHOD(gmagick, getimagecolormapcolor);
#ifdef HAVE_GMAGICK_SET_IMAGE_GRAVITY
PHP_METHOD(gmagick, getimagegravity);
#endif // #ifdef HAVE_GMAGICK_SET_IMAGE_GRAVITY
PHP_METHOD(gmagick, getimagevirtualpixelmethod);
PHP_METHOD(gmagick, haldclutimage);
PHP_METHOD(gmagick, mattefloodfillimage);
PHP_METHOD(gmagick, montageimage);
PHP_METHOD(gmagick, morphimages);
PHP_METHOD(gmagick, mosaicimages);
PHP_METHOD(gmagick, setimageattribute);
PHP_METHOD(gmagick, setimagecolormapcolor);
#ifdef HAVE_GMAGICK_SET_IMAGE_GRAVITY
PHP_METHOD(gmagick, setimagegravity);
#endif //HAVE_GMAGICK_SET_IMAGE_GRAVITY
PHP_METHOD(gmagick, setimagemattecolor);
PHP_METHOD(gmagick, setimagevirtualpixelmethod);
PHP_METHOD(gmagick, shaveimage);
PHP_METHOD(gmagick, steganoimage);
PHP_METHOD(gmagick, stereoimage);
PHP_METHOD(gmagick, waveimage);
PHP_METHOD(gmagick, whitethresholdimage);
PHP_METHOD(gmagick, getimageboundingbox);
PHP_METHOD(gmagick, getimagefuzz);
PHP_METHOD(gmagick, getimagesavedtype);
PHP_METHOD(gmagick, setdepth);
PHP_METHOD(gmagick, setformat);
PHP_METHOD(gmagick, setimagefuzz);
PHP_METHOD(gmagick, setimageoption);
PHP_METHOD(gmagick, setimagesavedtype);
PHP_METHOD(gmagick, setresolutionunits);
PHP_METHOD(gmagick, setformat);
PHP_METHOD(gmagick, writeimagefile);

/* draw */
PHP_METHOD(gmagickdraw, setstrokecolor);
PHP_METHOD(gmagickdraw, setstrokewidth);
PHP_METHOD(gmagickdraw, setfillcolor);
PHP_METHOD(gmagickdraw, setgravity);
PHP_METHOD(gmagickdraw, getgravity);
PHP_METHOD(gmagickdraw, ellipse);
PHP_METHOD(gmagickdraw, annotate);
PHP_METHOD(gmagickdraw, affine);
PHP_METHOD(gmagickdraw, arc);
PHP_METHOD(gmagickdraw, bezier);
PHP_METHOD(gmagickdraw, getfillcolor);
PHP_METHOD(gmagickdraw, getfillopacity);
PHP_METHOD(gmagickdraw, getfont);
PHP_METHOD(gmagickdraw, getfontsize);
PHP_METHOD(gmagickdraw, getfontstyle);
PHP_METHOD(gmagickdraw, getfontweight);
PHP_METHOD(gmagickdraw, getstrokeopacity);
PHP_METHOD(gmagickdraw, getstrokecolor);
PHP_METHOD(gmagickdraw, getstrokewidth);
PHP_METHOD(gmagickdraw, gettextdecoration);
PHP_METHOD(gmagickdraw, gettextencoding);
PHP_METHOD(gmagickdraw, line);
PHP_METHOD(gmagickdraw, point);
PHP_METHOD(gmagickdraw, polygon);
PHP_METHOD(gmagickdraw, polyline);
PHP_METHOD(gmagickdraw, rectangle);
PHP_METHOD(gmagickdraw, rotate);
PHP_METHOD(gmagickdraw, roundrectangle);
PHP_METHOD(gmagickdraw, scale);
PHP_METHOD(gmagickdraw, setfillopacity);
PHP_METHOD(gmagickdraw, setfont);
PHP_METHOD(gmagickdraw, setfontsize);
PHP_METHOD(gmagickdraw, setfontstyle);
PHP_METHOD(gmagickdraw, setfontweight);
PHP_METHOD(gmagickdraw, setstrokeopacity);
PHP_METHOD(gmagickdraw, settextdecoration);
PHP_METHOD(gmagickdraw, settextencoding);
PHP_METHOD(gmagickdraw, setstrokeantialias);
PHP_METHOD(gmagickdraw, setstrokedashoffset);
PHP_METHOD(gmagickdraw, setstrokelinecap);
PHP_METHOD(gmagickdraw, setstrokelinejoin);
PHP_METHOD(gmagickdraw, setstrokemiterlimit);
PHP_METHOD(gmagickdraw, getstrokeantialias);
PHP_METHOD(gmagickdraw, getstrokedashoffset);
PHP_METHOD(gmagickdraw, getstrokelinecap);
PHP_METHOD(gmagickdraw, getstrokelinejoin);
PHP_METHOD(gmagickdraw, getstrokemiterlimit);
#if GMAGICK_LIB_MASK >= 1003000 
PHP_METHOD(gmagickdraw, setstrokedasharray);
PHP_METHOD(gmagickdraw, getstrokedasharray);
#endif
/* pixel */
PHP_METHOD(gmagickpixel, __construct);
PHP_METHOD(gmagickpixel, setcolor);
PHP_METHOD(gmagickpixel, getcolor);
PHP_METHOD(gmagickpixel, getcolorcount);
PHP_METHOD(gmagickpixel, getcolorvalue);
PHP_METHOD(gmagickpixel, setcolorvalue);
#endif
