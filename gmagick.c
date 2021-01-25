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

#include "php_gmagick.h"
#include "php_gmagick_macros.h"
#include "php_gmagick_helpers.h"

ZEND_DECLARE_MODULE_GLOBALS(gmagick)

/* handlers */
static zend_object_handlers gmagick_object_handlers;
static zend_object_handlers gmagickdraw_object_handlers;
static zend_object_handlers gmagickpixel_object_handlers;

zend_class_entry *php_gmagick_sc_entry;
zend_class_entry *php_gmagickdraw_sc_entry;
zend_class_entry *php_gmagickpixel_sc_entry;
zend_class_entry *php_gmagick_exception_class_entry;
zend_class_entry *php_gmagickdraw_exception_class_entry;
zend_class_entry *php_gmagickpixel_exception_class_entry;

/* {{{ static void php_gmagick_object_free_storage(void *object TSRMLS_DC)
*/
static void php_gmagick_object_free_storage(zend_object *object TSRMLS_DC)
{
	php_gmagick_object *intern = GMAGICK_FETCH_OBJECT(object);

	if (!intern) {
		return;
	}

	if (intern->magick_wand) {
		DestroyMagickWand(intern->magick_wand);
	}

	zend_object_std_dtor(&intern->zo TSRMLS_CC);
}
/* }}} */


/* {{{ static zend_object *php_gmagick_object_new_ex(zend_class_entry *class_type, zend_bool init_wand)
*/
static zend_object *php_gmagick_object_new_ex(zend_class_entry *class_type, zend_bool init_wand)
{
	/* Allocate memory for it */
	php_gmagick_object *intern = ecalloc(1, sizeof(php_gmagick_object) + zend_object_properties_size(class_type));

	/* Set the magickwand */
	if (init_wand) {
		intern->magick_wand = NewMagickWand();
	} else {
		intern->magick_wand = NULL;
	}

        zend_object_std_init(&(intern->zo), class_type);
        object_properties_init(&intern->zo, class_type);

	intern->zo.handlers = &gmagick_object_handlers;

	return &intern->zo;
}
/* }}} */

/* {{{ static zend_object *php_gmagick_object_new(zend_class_entry *class_type)
*/
static zend_object *php_gmagick_object_new(zend_class_entry *class_type)
{
	return php_gmagick_object_new_ex(class_type, 1);
}
/* }}} */

/* {{{ static zend_object *php_gmagick_clone_gmagick_object(zval *this_ptr TSRMLS_DC)
*/
#if PHP_MAJOR_VERSION < 8
static zend_object *php_gmagick_clone_gmagick_object(zval *this_ptr TSRMLS_DC)
{
	php_gmagick_object *old_obj = Z_GMAGICK_OBJ_P(this_ptr);
	php_gmagick_object *new_obj = GMAGICK_FETCH_OBJECT(php_gmagick_object_new_ex(old_obj->zo.ce, 0));

	zend_objects_clone_members(&new_obj->zo, &old_obj->zo);

	if (new_obj->magick_wand) {
		DestroyMagickWand(new_obj->magick_wand);
	}

	new_obj->magick_wand = CloneMagickWand(old_obj->magick_wand);
	return &new_obj->zo;
}
#else
static zend_object *php_gmagick_clone_gmagick_object(zend_object *this_ptr)
{
	php_gmagick_object *old_obj = GMAGICK_FETCH_OBJECT(this_ptr);
	php_gmagick_object *new_obj = GMAGICK_FETCH_OBJECT(php_gmagick_object_new_ex(this_ptr->ce, 0));

	zend_objects_clone_members(&new_obj->zo, &old_obj->zo);

	if (new_obj->magick_wand) {
		DestroyMagickWand(new_obj->magick_wand);
	}

	new_obj->magick_wand = CloneMagickWand(old_obj->magick_wand);
	return &new_obj->zo;
}
#endif
/* }}} */

/* {{{ static void php_gmagickdraw_object_free_storage(zend_object *object)
*/
static void php_gmagickdraw_object_free_storage(zend_object *object)
{
	php_gmagickdraw_object *intern = GMAGICKDRAW_FETCH_OBJECT(object);

	if (!intern) {
		return;
	}

	if (intern->drawing_wand) {
		DestroyDrawingWand(intern->drawing_wand);
	}

	zend_object_std_dtor(&intern->zo);
}
/* }}} */

/* {{{ static zend_object *php_gmagickdraw_object_new_ex(zend_class_entry *class_type, zend_bool init_wand)
*/
static zend_object *php_gmagickdraw_object_new_ex(zend_class_entry *class_type, zend_bool init_wand)
{
	/* Allocate memory for it */
	php_gmagickdraw_object *intern = ecalloc(1, sizeof(php_gmagickdraw_object) + zend_object_properties_size(class_type));

	/* Set the DrawingWand */
	if (init_wand) {
		intern->drawing_wand = NewDrawingWand();
	} else {
		intern->drawing_wand = NULL;
	}

	zend_object_std_init(&intern->zo, class_type);
	object_properties_init(&intern->zo, class_type );

	intern->zo.handlers = &gmagickdraw_object_handlers;

	return &intern->zo;
}
/* }}} */

/* {{{ static zend_object *php_gmagickdraw_object_new(zend_class_entry *class_type)
*/
static zend_object *php_gmagickdraw_object_new(zend_class_entry *class_type)
{
	return php_gmagickdraw_object_new_ex(class_type, 1);
}
/* }}} */

/* {{{ static void php_gmagickpixel_object_free_storage(zend_object *object TSRMLS_DC)
*/
static void php_gmagickpixel_object_free_storage(zend_object *object)
{
	php_gmagickpixel_object *intern = GMAGICKPIXEL_FETCH_OBJECT(object);

	if (!intern) {
		return;
	}
	
	if(intern->pixel_wand) {
		DestroyPixelWand(intern->pixel_wand);
	}
	
	zend_object_std_dtor(&intern->zo);
}
/* }}} */

/* {{{ static zend_object *php_gmagickpixel_object_new_ex(zend_class_entry *class_type, zend_bool init_wand)
*/
static zend_object *php_gmagickpixel_object_new_ex(zend_class_entry *class_type, zend_bool init_wand)
{
	/* Allocate memory for it */
	php_gmagickpixel_object *intern = ecalloc(1, sizeof(php_gmagickpixel_object) + zend_object_properties_size(class_type));

	/* Set the pixelwand if requested */
	if (init_wand) {
		intern->pixel_wand = (PixelWand *)NewPixelWand();
	} else {
		intern->pixel_wand = NULL;
	}

	/* ALLOC_HASHTABLE(intern->zo.properties); */

	zend_object_std_init(&intern->zo, class_type TSRMLS_CC);
	object_properties_init(&intern->zo, class_type );

	intern->zo.handlers = &gmagickpixel_object_handlers;

	return &intern->zo;
}
/* }}} */

/* {{{ static zend_object *php_gmagickpixel_object_new(zend_class_entry *class_type)
*/
static zend_object *php_gmagickpixel_object_new(zend_class_entry *class_type TSRMLS_DC)
{
	return php_gmagickpixel_object_new_ex(class_type, 1);
}
/* }}} */

/* {{{ static zend_object *php_gmagick_clone_gmagickpixel_object(zval *this_ptr)
*/
#if PHP_MAJOR_VERSION < 8
static zend_object *php_gmagick_clone_gmagickpixel_object(zval *this_ptr)
{
	php_gmagickpixel_object *old_obj = Z_GMAGICKPIXEL_OBJ_P(this_ptr);
	php_gmagickpixel_object *new_obj = GMAGICKPIXEL_FETCH_OBJECT(php_gmagickpixel_object_new_ex(old_obj->zo.ce, 0));

	zend_objects_clone_members(&new_obj->zo, &old_obj->zo);
	GMAGICK_CLONE_PIXELWAND(old_obj->pixel_wand, new_obj->pixel_wand);

	return &new_obj->zo;
}
#else
static zend_object *php_gmagick_clone_gmagickpixel_object(zend_object *this_ptr)
{
	php_gmagickpixel_object *old_obj = GMAGICKPIXEL_FETCH_OBJECT(this_ptr);
	php_gmagickpixel_object *new_obj = GMAGICKPIXEL_FETCH_OBJECT(php_gmagickpixel_object_new_ex(old_obj->zo.ce, 0));

	zend_objects_clone_members(&new_obj->zo, &old_obj->zo);
	GMAGICK_CLONE_PIXELWAND(old_obj->pixel_wand, new_obj->pixel_wand);

	return &new_obj->zo;
}

#endif
/* }}} */

ZEND_BEGIN_ARG_INFO_EX(gmagick_empty_args, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_constructor_args, 0, 0, 0)
	ZEND_ARG_INFO(0, filename)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_addimage_args, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, Gmagick, Gmagick, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_addnoiseimage_args, 0, 0, 1)
	ZEND_ARG_INFO(0, NOISE)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_annotateimage_args, 0, 0, 5)
	ZEND_ARG_OBJ_INFO(0, GmagickDraw, GmagickDraw, 0)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
	ZEND_ARG_INFO(0, angle)
	ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_blurimage_args, 0, 0, 2)
	ZEND_ARG_INFO(0, radius)
	ZEND_ARG_INFO(0, sigma)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_borderimage_args, 0, 0, 3)
	ZEND_ARG_INFO(0, color)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_thresholdimage_args, 0, 0, 1)
	ZEND_ARG_INFO(0, threshold)
	ZEND_ARG_INFO(0, CHANNELTYPE)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_charcoalimage_args, 0, 0, 2)
	ZEND_ARG_INFO(0, radius)
	ZEND_ARG_INFO(0, sigma)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_chopimage_args, 0, 0, 4)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_commentimage_args, 0, 0, 1)
	ZEND_ARG_INFO(0, comment)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_cropthumbnailimage_args, 0, 0, 2)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
	ZEND_ARG_INFO(0, fit)
	ZEND_ARG_INFO(0, legacy)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_cyclecolormapimage_args, 0, 0, 1)
	ZEND_ARG_INFO(0, displace)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_readimage_args, 0, 0, 1)
	ZEND_ARG_INFO(0, filename)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_writeimage_args, 0, 0, 1)
	ZEND_ARG_INFO(0, filename)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_resizeimage_args, 0, 0, 5)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
	ZEND_ARG_INFO(0, filter)
	ZEND_ARG_INFO(0, blur)
	ZEND_ARG_INFO(0, fit)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_thumbnailimage_args, 0, 0, 2)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_cropimage_args, 0, 0, 4)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_compositeimage_args, 0, 0, 4)
	ZEND_ARG_OBJ_INFO(0, source, Gmagick, 0)
	ZEND_ARG_INFO(0, COMPOSE)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_drawimage_args, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, GmagickDraw, GmagickDraw, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_edgeimage_args, 0, 0, 1)
	ZEND_ARG_INFO(0, radius)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_embossimage_args, 0, 0, 2)
	ZEND_ARG_INFO(0, radius)
	ZEND_ARG_INFO(0, sigma)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_frameimage_args, 0, 0, 5)
	ZEND_ARG_INFO(0, color)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
	ZEND_ARG_INFO(0, inner_bevel)
	ZEND_ARG_INFO(0, outer_bevel)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_gammaimage_args, 0, 0, 1)
	ZEND_ARG_INFO(0, gamma)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setimage_args, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, Gmagick, Gmagick, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setimagebackgroundcolor_args, 0, 0, 1)
	ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setimageblueprimary_args, 0, 0, 2)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setimagebordercolor_args, 0, 0, 1)
	ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setimagechanneldepth_args, 0, 0, 2)
	ZEND_ARG_INFO(0, CHANNEL)
	ZEND_ARG_INFO(0, depth)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setimagecolormapcolor_args, 0, 0, 2)
	ZEND_ARG_INFO(0, index)
	ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setimagecolorspace_args, 0, 0, 1)
	ZEND_ARG_INFO(0, COLORSPACE)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setinterlacescheme_args, 0, 0, 1)
	ZEND_ARG_INFO(0, INTERLACE)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setimagecompose_args, 0, 0, 1)
	ZEND_ARG_INFO(0, COMPOSITE)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setimagecompression_args, 0, 0, 1)
		ZEND_ARG_INFO(0, COMPRESSION)
	ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setimagedelay_args, 0, 0, 1)
	ZEND_ARG_INFO(0, delay)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setimagedepth_args, 0, 0, 1)
	ZEND_ARG_INFO(0, depth)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setimagedispose_args, 0, 0, 1)
	ZEND_ARG_INFO(0, DISPOSETYPE)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setfilename_args, 0, 0, 1)
	ZEND_ARG_INFO(0, filename)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setimagefilename_args, 0, 0, 1)
	ZEND_ARG_INFO(0, filename)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setimageformat_args, 0, 0, 1)
	ZEND_ARG_INFO(0, imageFormat)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setcompressionquality_args, 0, 0, 1)
	ZEND_ARG_INFO(0, quality)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setimagegamma_args, 0, 0, 1)
	ZEND_ARG_INFO(0, gamma)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setimagegreenprimary_args, 0, 0, 2)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setimageindex_args, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setimageinterlacescheme_args, 0, 0, 1)
	ZEND_ARG_INFO(0, INTERLACE)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setimageiterations_args, 0, 0, 1)
	ZEND_ARG_INFO(0, iterations)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setimageprofile_args, 0, 0, 2)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, profile)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setimageredprimary_args, 0, 0, 2)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setimagerenderingintent_args, 0, 0, 1)
	ZEND_ARG_INFO(0, RENDERINGINTENT)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setimageresolution_args, 0, 0, 2)
	ZEND_ARG_INFO(0, xResolution)
	ZEND_ARG_INFO(0, yResolution)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setresolution_args, 0, 0, 2)
	ZEND_ARG_INFO(0, xResolution)
	ZEND_ARG_INFO(0, yResolution)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setimagescene_args, 0, 0, 1)
	ZEND_ARG_INFO(0, scene)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setimagetype_args, 0, 0, 1)
	ZEND_ARG_INFO(0, IMGTYPE)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setimagepage_args, 0, 0, 4)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setimageunits_args, 0, 0, 1)
	ZEND_ARG_INFO(0, RESOLUTION)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setimagewhitepoint_args, 0, 0, 2)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setsamplingfactors_args, 0, 0, 1)
	ZEND_ARG_INFO(0, factors)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setsize_args, 0, 0, 2)
	ZEND_ARG_INFO(0, columns)
	ZEND_ARG_INFO(0, rows)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_getimagetotalinkdensity_args, 0, 0, 1)
	ZEND_ARG_INFO(0, radius)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_labelimage_args, 0, 0, 1)
	ZEND_ARG_INFO(0, label)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_levelimage_args, 0, 0, 3)
	ZEND_ARG_INFO(0, blackPoint)
	ZEND_ARG_INFO(0, gamma)
	ZEND_ARG_INFO(0, whitePoint)
	ZEND_ARG_INFO(0, CHANNEL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_mapimage_args, 0, 0, 2)
	ZEND_ARG_OBJ_INFO(0, gmagick, gmagick, 0)
	ZEND_ARG_INFO(0, dither)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_medianfilterimage_args, 0, 0, 1)
	ZEND_ARG_INFO(0, radius)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_negateimage_args, 0, 0, 1)
	ZEND_ARG_INFO(0, gray)
	ZEND_ARG_INFO(0, CHANNEL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_modulateimage_args, 0, 0, 3)
	ZEND_ARG_INFO(0, brightness)
	ZEND_ARG_INFO(0, saturation)
	ZEND_ARG_INFO(0, hue)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_morphimages_args, 0, 0, 1)
	ZEND_ARG_INFO(0, frames)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_motionblurimage_args, 0, 0, 3)
	ZEND_ARG_INFO(0, radius)
	ZEND_ARG_INFO(0, sigma)
	ZEND_ARG_INFO(0, angle)
ZEND_END_ARG_INFO()

 	
ZEND_BEGIN_ARG_INFO_EX(gmagick_newimage_args, 0, 0, 3)
	ZEND_ARG_INFO(0, columns)
	ZEND_ARG_INFO(0, rows)
	ZEND_ARG_INFO(0, background_color)
	ZEND_ARG_INFO(0, format)
ZEND_END_ARG_INFO() 

ZEND_BEGIN_ARG_INFO_EX(gmagick_newpseudoimage_args, 0, 0, 3)
 	ZEND_ARG_INFO(0, columns)
 	ZEND_ARG_INFO(0, rows)
 	ZEND_ARG_INFO(0, pseudoString)
ZEND_END_ARG_INFO() 

ZEND_BEGIN_ARG_INFO_EX(gmagick_getresourcelimit_args, 0, 0, 1)
	ZEND_ARG_INFO(0, resource_type)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setresourcelimit_args, 0, 0, 2)
	ZEND_ARG_INFO(0, RESOURCETYPE)
	ZEND_ARG_INFO(0, limit)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_normalizeimage_args, 0, 0, 0)
	ZEND_ARG_INFO(0, CHANNEL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_oilpaintimage_args, 0, 0, 1)
	ZEND_ARG_INFO(0, radius)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_previewimages_args, 0, 0, 1)
	ZEND_ARG_INFO(0, PREVIEW)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_profileimage_args, 0, 0, 2)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, profile)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_quantizeimage_args, 0, 0, 5)
	ZEND_ARG_INFO(0, numColors)
	ZEND_ARG_INFO(0, COLORSPACE)
	ZEND_ARG_INFO(0, treeDepth)
	ZEND_ARG_INFO(0, dither)
	ZEND_ARG_INFO(0, measureError)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_quantizeimages_args, 0, 0, 5)
	ZEND_ARG_INFO(0, numColors)
	ZEND_ARG_INFO(0, COLORSPACE)
	ZEND_ARG_INFO(0, treeDepth)
	ZEND_ARG_INFO(0, dither)
	ZEND_ARG_INFO(0, measureError)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_queryfonts_args, 0, 0, 1)
	ZEND_ARG_INFO(0, pattern)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_queryfontmetrics_args, 0, 0, 2)
	ZEND_ARG_OBJ_INFO(0, GmagickDraw, GmagickDraw, 0)
	ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_queryformats_args, 0, 0, 1)
	ZEND_ARG_INFO(0, pattern)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_radialblurimage_args, 0, 0, 1)
	ZEND_ARG_INFO(0, angle)
	ZEND_ARG_INFO(0, CHANNEL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_raiseimage_args, 0, 0, 5)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
	ZEND_ARG_INFO(0, raise)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_readimageblob_args, 0, 0, 1)
	ZEND_ARG_INFO(0, imageContents)
	ZEND_ARG_INFO(0, filename)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_readimagefile_args, 0, 0, 1)
	ZEND_ARG_INFO(0, fp)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_reducenoiseimage_args, 0, 0, 1)
	ZEND_ARG_INFO(0, radius)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_removeimageprofile_args, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_resampleimage_args, 0, 0, 4)
	ZEND_ARG_INFO(0, xResolution)
	ZEND_ARG_INFO(0, yResolution)
	ZEND_ARG_INFO(0, FILTER)
	ZEND_ARG_INFO(0, blur)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_rollimage_args, 0, 0, 2)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_rotateimage_args, 0, 0, 2)
	ZEND_ARG_INFO(0, color)
	ZEND_ARG_INFO(0, degrees)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_scaleimage_args, 0, 0, 2)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_separateimagechannel_args, 0, 0, 1)
	ZEND_ARG_INFO(0, CHANNEL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_sharpenimage_args, 0, 0, 2)
    ZEND_ARG_INFO(0, radius)
    ZEND_ARG_INFO(0, sigma)
    ZEND_ARG_INFO(0, CHANNEL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_shearimage_args, 0, 0, 3)
	ZEND_ARG_INFO(0, color)
	ZEND_ARG_INFO(0, xShear)
	ZEND_ARG_INFO(0, yShear)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_solarizeimage_args, 0, 0, 1)
	ZEND_ARG_INFO(0, threshold)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_spreadimage_args, 0, 0, 1)
	ZEND_ARG_INFO(0, radius)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_swirlimage_args, 0, 0, 1)
	ZEND_ARG_INFO(0, degrees)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_trimimage_args, 0, 0, 1)
	ZEND_ARG_INFO(0, fuzz)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_whitethresholdimage_args, 0, 0, 1)
	ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_writeimages_args, 0, 0, 2)
	ZEND_ARG_INFO(0, filename)
	ZEND_ARG_INFO(0, adjoin)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_sampleimage_args, 0, 0, 2)
	ZEND_ARG_INFO(0, columns)
	ZEND_ARG_INFO(0, rows)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_appendimages_args, 0, 0, 1)
	ZEND_ARG_INFO(0, stack)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(gmagick_unsharpmaskimage_args, 0, 0, 4)
	ZEND_ARG_INFO(0, radius)
	ZEND_ARG_INFO(0, sigma)
	ZEND_ARG_INFO(0, amount)
	ZEND_ARG_INFO(0, threshold)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_adaptivethresholdimage_args, 0, 0, 3)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
	ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_affinetransformimage_args, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, GmagickDraw, GmagickDraw, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_blackthresholdimage_args, 0, 0, 1)
	ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_colordecisionlist_args, 0, 0, 1)
	ZEND_ARG_INFO(0, antialias)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_clippathimage_args, 0, 0, 2)
	ZEND_ARG_INFO(0, pathname)
	ZEND_ARG_INFO(0, inside)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_colorfloodfillimage_args, 0, 0, 5)
	ZEND_ARG_INFO(0, fill_color)
	ZEND_ARG_INFO(0, fuzz)
	ZEND_ARG_INFO(0, border_color)
	ZEND_ARG_INFO(0, y)
	ZEND_ARG_INFO(0, x)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_colorizeimage_args, 0, 0, 2)
	ZEND_ARG_INFO(0, colorize_color)
	ZEND_ARG_INFO(0, opacity)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_compareimagechannels_args, 0, 0, 3)
	ZEND_ARG_OBJ_INFO(0, Gmagick, Gmagick, 0)
	ZEND_ARG_INFO(0, channel)
	ZEND_ARG_INFO(0, metric)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_compareimages_args, 0, 0, 2)
	ZEND_ARG_OBJ_INFO(0, Gmagick, Gmagick, 0)
	ZEND_ARG_INFO(0, metric)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_contrastimage_args, 0, 0, 1)
	ZEND_ARG_INFO(0, sharpen)
ZEND_END_ARG_INFO()
ZEND_BEGIN_ARG_INFO_EX(gmagick_convolveimage_args, 0, 0, 1)
	ZEND_ARG_INFO(0, kernel)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_extentimage_args, 0, 0, 4)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_getimageattribute_args, 0, 0, 1)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_getimagechannelextrema_args, 0, 0, 1)
	ZEND_ARG_INFO(0, channel)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_getimagechannelmean_args, 0, 0, 1)
	ZEND_ARG_INFO(0, channel)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_getimagecolormapcolor_args, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_haldclutimage_args, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, Gmagick, Gmagick, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_mattefloodfillimage_args, 0, 0, 5)
	ZEND_ARG_INFO(0, alpha)
	ZEND_ARG_INFO(0, fuzz)
	ZEND_ARG_INFO(0, color)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_montageimage_args, 0, 0, 5)
	ZEND_ARG_OBJ_INFO(0, GmagickDraw, GmagickDraw, 0)
	ZEND_ARG_INFO(0, tile_geometry)
	ZEND_ARG_INFO(0, thumbnail_geometry)
	ZEND_ARG_INFO(0, montageMode)
	ZEND_ARG_INFO(0, frame)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setimageattribute_args, 0, 0, 2)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

#ifdef HAVE_GMAGICK_SET_IMAGE_GRAVITY
ZEND_BEGIN_ARG_INFO_EX(gmagick_setimagegravity_args, 0, 0, 1)
	ZEND_ARG_INFO(0, gravity)
ZEND_END_ARG_INFO()
#endif //HAVE_GMAGICK_SET_IMAGE_GRAVITY

ZEND_BEGIN_ARG_INFO_EX(gmagick_setimagemattecolor_args, 0, 0, 1)
	ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setimagevirtualpixelmethod_args, 0, 0, 1)
	ZEND_ARG_INFO(0, virtual_pixel_method)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_shaveimage_args, 0, 0, 2)
	ZEND_ARG_INFO(0, columns)
	ZEND_ARG_INFO(0, rows)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_steganoimage_args, 0, 0, 2)
	ZEND_ARG_OBJ_INFO(0, Gmagick, Gmagick, 0)
	ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_stereoimage_args, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, Gmagick, Gmagick, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_waveimage_args, 0, 0, 2)
	ZEND_ARG_INFO(0, amplitude)
	ZEND_ARG_INFO(0, waveLength)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_getimageboundingbox_args, 0, 0, 1)
	ZEND_ARG_INFO(0, fuzz)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setdepth_args, 0, 0, 1)
	ZEND_ARG_INFO(0, depth)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setformat_args, 0, 0, 1)
	ZEND_ARG_INFO(0, format)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setimagefuzz_args, 0, 0, 1)
	ZEND_ARG_INFO(0, fuzz)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setimageoption_args, 0, 0, 3)
	ZEND_ARG_INFO(0, format)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setimagesavedtype_args, 0, 0, 1)
	ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_setresolutionunits_args, 0, 0, 2)
	ZEND_ARG_INFO(0, x_resolution)
	ZEND_ARG_INFO(0, y_resolution)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_writeimagefile_args, 0, 0, 1)
	ZEND_ARG_INFO(0, handle)
	ZEND_ARG_INFO(0, format)
ZEND_END_ARG_INFO()


/* {{{ static zend_function_entry php_gmagick_functions[]
*/
static zend_function_entry php_gmagick_functions[] =
{
	{ NULL, NULL, NULL }
};
/* }}} */

/* {{{ static zend_function_entry php_gmagick_functions[]
*/
static zend_function_entry php_gmagick_class_methods[] =
{
	PHP_ME(gmagick,	__construct,		gmagick_constructor_args,	ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(gmagick, __tostring, 		gmagick_empty_args,		ZEND_ACC_PUBLIC)
	PHP_ME(gmagick,	readimage,		gmagick_readimage_args,		ZEND_ACC_PUBLIC)
	PHP_ME(gmagick,	writeimage,		gmagick_writeimage_args,	ZEND_ACC_PUBLIC)
	PHP_ME(gmagick,	resizeimage,		gmagick_resizeimage_args,	ZEND_ACC_PUBLIC)
	PHP_ME(gmagick,	thumbnailimage,		gmagick_thumbnailimage_args,	ZEND_ACC_PUBLIC)
	PHP_ME(gmagick,	clear,			gmagick_empty_args,		ZEND_ACC_PUBLIC)
	PHP_ME(gmagick,	cropimage,		gmagick_cropimage_args,		ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, coalesceimages, gmagick_empty_args, ZEND_ACC_PUBLIC)	
	PHP_ME(gmagick, compositeimage,		gmagick_compositeimage_args,	ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, drawimage,		gmagick_drawimage_args,		ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, annotateimage,		gmagick_annotateimage_args, 	ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, blurimage,		gmagick_blurimage_args, 	ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, addimage,		gmagick_addimage_args,		ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, addnoiseimage,		gmagick_addnoiseimage_args, 	ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, negateimage, gmagick_negateimage_args, ZEND_ACC_PUBLIC)	
	PHP_ME(gmagick, borderimage,		gmagick_borderimage_args,	ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, thresholdimage, gmagick_thresholdimage_args, ZEND_ACC_PUBLIC)	
	PHP_ME(gmagick, charcoalimage,		gmagick_charcoalimage_args,	ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, chopimage,		gmagick_chopimage_args,		ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, commentimage,		gmagick_commentimage_args,	ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, current,		gmagick_empty_args,		ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, cropthumbnailimage, 	gmagick_cropthumbnailimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, cyclecolormapimage,	gmagick_cyclecolormapimage_args,ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, deconstructimages,	gmagick_empty_args,		ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, despeckleimage,		gmagick_empty_args,		ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, destroy,		gmagick_empty_args,		ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, edgeimage,		gmagick_edgeimage_args,		ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, embossimage,		gmagick_embossimage_args,	ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, enhanceimage,		gmagick_empty_args,		ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, equalizeimage,		gmagick_empty_args,		ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, flattenimages, gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, flipimage,		gmagick_empty_args,		ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, flopimage,		gmagick_empty_args,		ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, frameimage,		gmagick_frameimage_args,	ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, gammaimage,		gmagick_gammaimage_args,	ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getcopyright,		gmagick_empty_args,		ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getfilename,		gmagick_empty_args,		ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getimagebackgroundcolor, gmagick_empty_args,		ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setimagebackgroundcolor, gmagick_setimagebackgroundcolor_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getimageblueprimary,	gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getimagebordercolor,	gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getimagechanneldepth,	gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setimageblueprimary,	gmagick_setimageblueprimary_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setimagebordercolor,	gmagick_setimagebordercolor_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getimageblob,	    gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getimagesblob,	    gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setimagechanneldepth,	gmagick_setimagechanneldepth_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setimagecolorspace,	gmagick_setimagecolorspace_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setinterlacescheme, gmagick_setinterlacescheme_args, ZEND_ACC_PUBLIC)	
	PHP_ME(gmagick, getimagecolorspace,	gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getimagecolors,		gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getimagecompose,	gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getimagedelay,		gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getimagedepth,		gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getnumberimages,	gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setimagecompose,	gmagick_setimagecompose_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setimagecompression, gmagick_setimagecompression_args, ZEND_ACC_PUBLIC)	
	PHP_ME(gmagick, getimagecompression, gmagick_empty_args, ZEND_ACC_PUBLIC)		
	PHP_ME(gmagick, setimagedelay,		gmagick_setimagedelay_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setimagedepth,		gmagick_setimagedepth_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getimagedispose,	gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setimagedispose,	gmagick_setimagedispose_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setfilename,		gmagick_setfilename_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getimageextrema,	gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getimagefilename,	gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setimagefilename,	gmagick_setimagefilename_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getimageformat,		gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setimageformat,		gmagick_setimageformat_args, ZEND_ACC_PUBLIC)
#if GMAGICK_LIB_MASK >= 1003007	
    PHP_ME(gmagick, setcompressionquality,	gmagick_setcompressionquality_args, ZEND_ACC_PUBLIC)
#endif    
	PHP_ME(gmagick, getimagegamma,		gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setimagegamma,		gmagick_setimagegamma_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getimagegreenprimary,	gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setimagegreenprimary,	gmagick_setimagegreenprimary_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getimageheight,		gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getimagehistogram,	gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getimageindex,		gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setimageindex,		gmagick_setimageindex_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getimageinterlacescheme,gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setimageinterlacescheme,gmagick_setimageinterlacescheme_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getimageiterations,	gmagick_empty_args, ZEND_ACC_PUBLIC)
#if GMAGICK_LIB_MASK >= 1005000
	PHP_ME(gmagick, getimagematte,		gmagick_empty_args, ZEND_ACC_PUBLIC)
#endif
	PHP_ME(gmagick, getimagemattecolor,	gmagick_empty_args, ZEND_ACC_PUBLIC)
#ifdef GMAGICK_HAVE_SET_IMAGE_PAGE
	PHP_ME(gmagick, getimagepage, gmagick_empty_args, ZEND_ACC_PUBLIC)
#endif // GMAGICK_HAVE_SET_IMAGE_PAGE
	PHP_ME(gmagick, getimageprofile,	gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getimageredprimary,	gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getimagerenderingintent,gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getimageresolution,	gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getimagescene,		gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getimagesignature,	gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getimagetype,		gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setimageiterations,	gmagick_setimageiterations_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setimageprofile,	gmagick_setimageprofile_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setimageredprimary,	gmagick_setimageredprimary_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setimagerenderingintent,gmagick_setimagerenderingintent_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setimageresolution,	gmagick_setimageresolution_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setresolution,          gmagick_setresolution_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setimagescene,		gmagick_setimagescene_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setimagetype,		gmagick_setimagetype_args, ZEND_ACC_PUBLIC)
#ifdef GMAGICK_HAVE_SET_IMAGE_PAGE 
	PHP_ME(gmagick, setimagepage,		gmagick_setimagepage_args, ZEND_ACC_PUBLIC)
#endif //GMAGICK_HAVE_SET_IMAGE_PAGE
	PHP_ME(gmagick, getimageunits,		gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getimagewhitepoint,	gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getimagewidth,		gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getpackagename,		gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getquantumdepth,	gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getreleasedate,		gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getresourcelimit,   gmagick_getresourcelimit_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setresourcelimit,   gmagick_setresourcelimit_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getsamplingfactors,	gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getsize,		gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setimageunits,		gmagick_setimageunits_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setimagewhitepoint,	gmagick_setimagewhitepoint_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setsamplingfactors,	gmagick_setsamplingfactors_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setsize,		gmagick_setsize_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getversion,		gmagick_empty_args, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(gmagick, getimagegeometry, gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getimage, gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setimage, gmagick_setimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, hasnextimage,		gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, haspreviousimage,	gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, implodeimage,		gmagick_getimagetotalinkdensity_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, labelimage,		gmagick_labelimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, levelimage,		gmagick_levelimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, magnifyimage,		gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, mapimage,		gmagick_mapimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, medianfilterimage,	gmagick_medianfilterimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, minifyimage,		gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, modulateimage,		gmagick_modulateimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, motionblurimage,	gmagick_motionblurimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, nextimage,		gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, newimage,		gmagick_newimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, normalizeimage,		gmagick_normalizeimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, oilpaintimage,		gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, previousimage,		gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, profileimage,		gmagick_profileimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, quantizeimage,		gmagick_quantizeimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, quantizeimages,		gmagick_quantizeimages_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, queryfonts,		gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, queryfontmetrics,	gmagick_queryfontmetrics_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, queryformats,		gmagick_queryformats_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, radialblurimage,	gmagick_radialblurimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, raiseimage,		gmagick_raiseimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, readimageblob,		gmagick_readimageblob_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, readimagefile,		gmagick_readimagefile_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, reducenoiseimage,	gmagick_reducenoiseimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, removeimage,		gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, removeimageprofile,	gmagick_removeimageprofile_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, resampleimage,		gmagick_resampleimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, rollimage,		gmagick_rollimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, rotateimage,		gmagick_rotateimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, scaleimage,		gmagick_scaleimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, separateimagechannel,	gmagick_separateimagechannel_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, sharpenimage,	gmagick_sharpenimage_args, ZEND_ACC_PUBLIC)	
	PHP_ME(gmagick, shearimage,		gmagick_shearimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, solarizeimage,		gmagick_solarizeimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, spreadimage,		gmagick_spreadimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, stripimage,		gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, swirlimage,		gmagick_swirlimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, trimimage,		gmagick_trimimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, sampleimage,		gmagick_sampleimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, cloneimage,		gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, appendimages,		gmagick_appendimages_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, unsharpmaskimage,	gmagick_unsharpmaskimage_args, ZEND_ACC_PUBLIC)
	PHP_MALIAS(gmagick, read, readimage,	gmagick_readimage_args,	ZEND_ACC_PUBLIC)
	PHP_MALIAS(gmagick, write, writeimage,	gmagick_writeimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, adaptivethresholdimage, gmagick_adaptivethresholdimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, affinetransformimage, gmagick_affinetransformimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, averageimages, gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, blackthresholdimage, gmagick_blackthresholdimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, colordecisionlist, gmagick_colordecisionlist_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, clipimage, gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, clippathimage, gmagick_clippathimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, colorfloodfillimage, gmagick_colorfloodfillimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, colorizeimage, gmagick_colorizeimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, compareimagechannels, gmagick_compareimagechannels_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, compareimages, gmagick_compareimages_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, contrastimage, gmagick_contrastimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, convolveimage, gmagick_convolveimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, extentimage, gmagick_extentimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getimageattribute, gmagick_getimageattribute_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getimagechannelextrema, gmagick_getimagechannelextrema_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getimagechannelmean, gmagick_getimagechannelmean_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getimagecolormapcolor, gmagick_getimagecolormapcolor_args, ZEND_ACC_PUBLIC)
#ifdef HAVE_GMAGICK_SET_IMAGE_GRAVITY
	PHP_ME(gmagick, getimagegravity, gmagick_empty_args, ZEND_ACC_PUBLIC)
#endif // HAVE_GMAGICK_SET_IMAGE_GRAVITY
	PHP_ME(gmagick, getimagevirtualpixelmethod, gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, haldclutimage, gmagick_haldclutimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, mattefloodfillimage, gmagick_mattefloodfillimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, montageimage, gmagick_montageimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, morphimages, gmagick_morphimages_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, mosaicimages, gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setimageattribute, gmagick_setimageattribute_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setimagecolormapcolor, gmagick_setimagecolormapcolor_args, ZEND_ACC_PUBLIC)
#ifdef HAVE_GMAGICK_SET_IMAGE_GRAVITY
	PHP_ME(gmagick, setimagegravity, gmagick_setimagegravity_args, ZEND_ACC_PUBLIC)
#endif //#ifdef HAVE_GMAGICK_SET_IMAGE_GRAVITY
	PHP_ME(gmagick, setimagemattecolor, gmagick_setimagemattecolor_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setimagevirtualpixelmethod, gmagick_setimagevirtualpixelmethod_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, shaveimage, gmagick_shaveimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, steganoimage, gmagick_steganoimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, stereoimage, gmagick_stereoimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, waveimage, gmagick_waveimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, whitethresholdimage, gmagick_whitethresholdimage_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getimageboundingbox, gmagick_getimageboundingbox_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getimagefuzz, gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, getimagesavedtype, gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setdepth, gmagick_setdepth_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setformat, gmagick_setformat_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setimagefuzz, gmagick_setimagefuzz_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setimageoption, gmagick_setimageoption_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setimagesavedtype, gmagick_setimagesavedtype_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setresolutionunits, gmagickdraw_setresolutionunits_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, writeimagefile, gmagick_writeimagefile_args, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};
/* }}} */

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_zero_args, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_setstrokecolor_args, 0, 0, 1)
	ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_setstrokewidth_args, 0, 0, 1)
	ZEND_ARG_INFO(0, width)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_setfillcolor_args, 0, 0, 1)
	ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_setgravity_args, 0, 0, 1)
	ZEND_ARG_INFO(0, gravity)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_ellipse_args, 0, 0, 6)
		ZEND_ARG_INFO(0, ox)
		ZEND_ARG_INFO(0, oy)
		ZEND_ARG_INFO(0, px)
		ZEND_ARG_INFO(0, py)
		ZEND_ARG_INFO(0, start)
		ZEND_ARG_INFO(0, end)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_affine_args, 0, 0, 1)
	ZEND_ARG_INFO(0, affineMatrix)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_annotate_args, 0, 0, 3)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
	ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_arc_args, 0, 0, 6)
	ZEND_ARG_INFO(0, sx)
	ZEND_ARG_INFO(0, sy)
	ZEND_ARG_INFO(0, ex)
	ZEND_ARG_INFO(0, ey)
	ZEND_ARG_INFO(0, sd)
	ZEND_ARG_INFO(0, ed)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_bezier_args, 0, 0, 1)
	ZEND_ARG_INFO(0, coordinate_array)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_line_args, 0, 0, 4)
	ZEND_ARG_INFO(0, sx)
	ZEND_ARG_INFO(0, sy)
	ZEND_ARG_INFO(0, ex)
	ZEND_ARG_INFO(0, ey)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_point_args, 0, 0, 2)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_polygon_args, 0, 0, 1)
	ZEND_ARG_INFO(0, coordinates)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_polyline_args, 0, 0, 1)
	ZEND_ARG_INFO(0, coordinate_array)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_rectangle_args, 0, 0, 4)
	ZEND_ARG_INFO(0, x1)
	ZEND_ARG_INFO(0, y1)
	ZEND_ARG_INFO(0, x2)
	ZEND_ARG_INFO(0, y2)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_rotate_args, 0, 0, 1)
	ZEND_ARG_INFO(0, degrees)
ZEND_END_ARG_INFO()

	ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_roundrectangle_args, 0, 0, 6)
	ZEND_ARG_INFO(0, x1)
	ZEND_ARG_INFO(0, y1)
	ZEND_ARG_INFO(0, x2)
	ZEND_ARG_INFO(0, y2)
	ZEND_ARG_INFO(0, rx)
	ZEND_ARG_INFO(0, ry)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_scale_args, 0, 0, 2)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_setfillopacity_args, 0, 0, 1)
	ZEND_ARG_INFO(0, fill_opacity)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_setfont_args, 0, 0, 1)
	ZEND_ARG_INFO(0, font)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_setfontsize_args, 0, 0, 1)
	ZEND_ARG_INFO(0, pointsize)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_setfontstyle_args, 0, 0, 1)
	ZEND_ARG_INFO(0, STYLE)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_setfontweight_args, 0, 0, 1)
	ZEND_ARG_INFO(0, weight)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_setstrokeopacity_args, 0, 0, 1)
	ZEND_ARG_INFO(0, stroke_opacity)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_settextdecoration_args, 0, 0, 1)
	ZEND_ARG_INFO(0, DECORATION)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_settextencoding_args, 0, 0, 1)
	ZEND_ARG_INFO(0, encoding)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_setstrokeantialias_args, 0, 0, 1)
	ZEND_ARG_INFO(0, antialias)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_setstrokedashoffset_args, 0, 0, 1)
	ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_setstrokelinecap_args, 0, 0, 1)
	ZEND_ARG_INFO(0, LINECAP)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_setstrokelinejoin_args, 0, 0, 1)
	ZEND_ARG_INFO(0, LINEJOIN)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_setstrokemiterlimit_args, 0, 0, 1)
	ZEND_ARG_INFO(0, miterLimit)
ZEND_END_ARG_INFO()

#if GMAGICK_LIB_MASK >= 1003000 
ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_setstrokedasharray_args, 0, 0, 1)
	ZEND_ARG_INFO(0, dashArray)
ZEND_END_ARG_INFO()
#endif


ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_circle_args, 0, 0, 4)
	ZEND_ARG_INFO(0, ox)
	ZEND_ARG_INFO(0, oy)
	ZEND_ARG_INFO(0, px)
	ZEND_ARG_INFO(0, py)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_setclippath_args, 0, 0, 1)
	ZEND_ARG_INFO(0, clipMask)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_setcliprule_args, 0, 0, 1)
	ZEND_ARG_INFO(0, FILLRULE)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_setclipunits_args, 0, 0, 1)
	ZEND_ARG_INFO(0, PATHUNITS)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_color_args, 0, 0, 3)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
	ZEND_ARG_INFO(0, PAINTMETHOD)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_comment_args, 0, 0, 1)
	ZEND_ARG_INFO(0, comment)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_setfillpatternurl_args, 0, 0, 1)
	ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_setfillrule_args, 0, 0, 1)
	ZEND_ARG_INFO(0, FILLRULE)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_setfontfamily_args, 0, 0, 1)
	ZEND_ARG_INFO(0, fontfamily)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_setfontstretch_args, 0, 0, 1)
	ZEND_ARG_INFO(0, STRETCH)
ZEND_END_ARG_INFO()

//ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_composite_args, 0, 0, 6)
//	ZEND_ARG_INFO(0, COMPOSE)
//	ZEND_ARG_INFO(0, x)
//	ZEND_ARG_INFO(0, y)
//	ZEND_ARG_INFO(0, width)
//	ZEND_ARG_INFO(0, height)
//	ZEND_ARG_OBJ_INFO(0, Gmagick, Gmagick, 0)
//ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_pathcurvetoabsolute_args, 0, 0, 6)
	ZEND_ARG_INFO(0, x1)
	ZEND_ARG_INFO(0, y1)
	ZEND_ARG_INFO(0, x2)
	ZEND_ARG_INFO(0, y2)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_pathcurvetorelative_args, 0, 0, 6)
	ZEND_ARG_INFO(0, x1)
	ZEND_ARG_INFO(0, y1)
	ZEND_ARG_INFO(0, x2)
	ZEND_ARG_INFO(0, y2)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_pathcurvetoquadraticbezierabsolute_args, 0, 0, 4)
	ZEND_ARG_INFO(0, x1)
	ZEND_ARG_INFO(0, y1)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_pathcurvetoquadraticbezierrelative_args, 0, 0, 4)
	ZEND_ARG_INFO(0, x1)
	ZEND_ARG_INFO(0, y1)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_pathcurvetoquadraticbeziersmoothabsolute_args, 0, 0, 2)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_pathcurvetoquadraticbeziersmoothrelative_args, 0, 0, 2)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_pathcurvetosmoothabsolute_args, 0, 0, 4)
	ZEND_ARG_INFO(0, x1)
	ZEND_ARG_INFO(0, y1)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_pathcurvetosmoothrelative_args, 0, 0, 4)
	ZEND_ARG_INFO(0, x1)
	ZEND_ARG_INFO(0, y1)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_pathellipticarcabsolute_args, 0, 0, 7)
	ZEND_ARG_INFO(0, rx)
	ZEND_ARG_INFO(0, ry)
	ZEND_ARG_INFO(0, xAxisRotation)
	ZEND_ARG_INFO(0, largeArc)
	ZEND_ARG_INFO(0, sweep)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_pathellipticarcrelative_args, 0, 0, 7)
	ZEND_ARG_INFO(0, rx)
	ZEND_ARG_INFO(0, ry)
	ZEND_ARG_INFO(0, xAxisRotation)
	ZEND_ARG_INFO(0, largeArc)
	ZEND_ARG_INFO(0, sweep)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_pathlinetoabsolute_args, 0, 0, 2)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_pathlinetorelative_args, 0, 0, 2)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_pathlinetohorizontalabsolute_args, 0, 0, 1)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_pathlinetohorizontalrelative_args, 0, 0, 1)
	ZEND_ARG_INFO(0, x)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_pathlinetoverticalabsolute_args, 0, 0, 1)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_pathlinetoverticalrelative_args, 0, 0, 1)
	ZEND_ARG_INFO(0, x)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_pathmovetoabsolute_args, 0, 0, 2)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_pathmovetorelative_args, 0, 0, 2)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_pushclippath_args, 0, 0, 1)
	ZEND_ARG_INFO(0, clipMask)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_pushpattern_args, 0, 0, 5)
	ZEND_ARG_INFO(0, pattern_id)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
	ZEND_ARG_INFO(0, width)
	ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_skewx_args, 0, 0, 1)
	ZEND_ARG_INFO(0, degrees)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_skewy_args, 0, 0, 1)
	ZEND_ARG_INFO(0, degrees)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_setstrokepatternurl_args, 0, 0, 1)
	ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_settextantialias_args, 0, 0, 1)
	ZEND_ARG_INFO(0, antialias)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_settextundercolor_args, 0, 0, 1)
	ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_translate_args, 0, 0, 2)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickdraw_setviewbox_args, 0, 0, 4)
	ZEND_ARG_INFO(0, sx)
	ZEND_ARG_INFO(0, sy)
	ZEND_ARG_INFO(0, ex)
	ZEND_ARG_INFO(0, ey)
ZEND_END_ARG_INFO()


static zend_function_entry php_gmagickdraw_class_methods[] =
{
	PHP_ME(gmagickdraw, setstrokecolor,	gmagickdraw_setstrokecolor_args,	ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, setstrokewidth, gmagickdraw_setstrokewidth_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, setfillcolor, gmagickdraw_setfillcolor_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, setgravity, gmagickdraw_setgravity_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, ellipse, gmagickdraw_ellipse_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, affine,	gmagickdraw_affine_args,	ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, annotate, gmagickdraw_annotate_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, arc, gmagickdraw_arc_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, bezier, gmagickdraw_bezier_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, getfillcolor, gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, getgravity, gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, getfillopacity, gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, getfont, gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, getfontsize, gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, getfontstyle, gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, getfontweight, gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, getstrokeopacity, gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, getstrokecolor, gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, getstrokewidth, gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, gettextdecoration, gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, gettextencoding, gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, line, gmagickdraw_line_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, point, gmagickdraw_point_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, polygon, gmagickdraw_polygon_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, polyline, gmagickdraw_polyline_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, rectangle, gmagickdraw_rectangle_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, rotate, gmagickdraw_rotate_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, roundrectangle, gmagickdraw_roundrectangle_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, scale, gmagickdraw_scale_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, setfillopacity, gmagickdraw_setfillopacity_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, setfont, gmagickdraw_setfont_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, setfontsize, gmagickdraw_setfontsize_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, setfontstyle, gmagickdraw_setfontstyle_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, setfontweight, gmagickdraw_setfontweight_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, setstrokeopacity, gmagickdraw_setstrokeopacity_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, settextdecoration, gmagickdraw_settextdecoration_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, settextencoding, gmagickdraw_settextencoding_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, setstrokeantialias, gmagickdraw_setstrokeantialias_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, setstrokedashoffset, gmagickdraw_setstrokedashoffset_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, setstrokelinecap, gmagickdraw_setstrokelinecap_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, setstrokelinejoin, gmagickdraw_setstrokelinejoin_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, setstrokemiterlimit, gmagickdraw_setstrokemiterlimit_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, getstrokeantialias, gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, getstrokedashoffset,  gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, getstrokelinecap,  gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, getstrokelinejoin,  gmagick_empty_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, getstrokemiterlimit, gmagick_empty_args, ZEND_ACC_PUBLIC)
#if GMAGICK_LIB_MASK >= 1003000 	
    PHP_ME(gmagickdraw, getstrokedasharray, gmagick_empty_args, ZEND_ACC_PUBLIC)
    PHP_ME(gmagickdraw, setstrokedasharray, gmagickdraw_setstrokedasharray_args, ZEND_ACC_PUBLIC)
#endif

	PHP_ME(gmagickdraw, circle, gmagickdraw_circle_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, getclippath, gmagickdraw_zero_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, setclippath, gmagickdraw_setclippath_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, getcliprule, gmagickdraw_zero_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, setcliprule, gmagickdraw_setcliprule_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, getclipunits, gmagickdraw_zero_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, setclipunits, gmagickdraw_setclipunits_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, color, gmagickdraw_color_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, comment, gmagickdraw_comment_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, setfillpatternurl, gmagickdraw_setfillpatternurl_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, getfillrule, gmagickdraw_zero_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, setfillrule, gmagickdraw_setfillrule_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, getfontfamily, gmagickdraw_zero_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, setfontfamily, gmagickdraw_setfontfamily_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, getfontstretch, gmagickdraw_zero_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, setfontstretch, gmagickdraw_setfontstretch_args, ZEND_ACC_PUBLIC)
//	PHP_ME(gmagickdraw, composite, gmagickdraw_composite_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, pathclose, gmagickdraw_zero_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, pathcurvetoabsolute, gmagickdraw_pathcurvetoabsolute_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, pathcurvetorelative, gmagickdraw_pathcurvetorelative_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, pathcurvetoquadraticbezierabsolute, gmagickdraw_pathcurvetoquadraticbezierabsolute_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, pathcurvetoquadraticbezierrelative, gmagickdraw_pathcurvetoquadraticbezierrelative_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, pathcurvetoquadraticbeziersmoothabsolute, gmagickdraw_pathcurvetoquadraticbeziersmoothabsolute_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, pathcurvetoquadraticbeziersmoothrelative, gmagickdraw_pathcurvetoquadraticbeziersmoothrelative_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, pathcurvetosmoothabsolute, gmagickdraw_pathcurvetosmoothabsolute_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, pathcurvetosmoothrelative, gmagickdraw_pathcurvetosmoothrelative_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, pathellipticarcabsolute, gmagickdraw_pathellipticarcabsolute_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, pathellipticarcrelative, gmagickdraw_pathellipticarcrelative_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, pathfinish, gmagickdraw_zero_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, pathlinetoabsolute, gmagickdraw_pathlinetoabsolute_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, pathlinetorelative, gmagickdraw_pathlinetorelative_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, pathlinetohorizontalabsolute, gmagickdraw_pathlinetohorizontalabsolute_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, pathlinetohorizontalrelative, gmagickdraw_pathlinetohorizontalrelative_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, pathlinetoverticalabsolute, gmagickdraw_pathlinetoverticalabsolute_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, pathlinetoverticalrelative, gmagickdraw_pathlinetoverticalrelative_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, pathmovetoabsolute, gmagickdraw_pathmovetoabsolute_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, pathmovetorelative, gmagickdraw_pathmovetorelative_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, pathstart, gmagickdraw_zero_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, popclippath, gmagickdraw_zero_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, popdefs, gmagickdraw_zero_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, poppattern, gmagickdraw_zero_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, pushclippath, gmagickdraw_pushclippath_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, pushdefs, gmagickdraw_zero_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, pushpattern, gmagickdraw_pushpattern_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, skewx, gmagickdraw_skewx_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, skewy, gmagickdraw_skewy_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, setstrokepatternurl, gmagickdraw_setstrokepatternurl_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, gettextantialias, gmagickdraw_zero_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, settextantialias, gmagickdraw_settextantialias_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, gettextundercolor, gmagickdraw_zero_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, settextundercolor, gmagickdraw_settextundercolor_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, translate, gmagickdraw_translate_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, setviewbox, gmagickdraw_setviewbox_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, popGraphicContext, gmagickdraw_zero_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagickdraw, pushGraphicContext, gmagickdraw_zero_args, ZEND_ACC_PUBLIC)

	{ NULL, NULL, NULL }
};
/* }}} */

ZEND_BEGIN_ARG_INFO_EX(gmagickpixel_constructor_args, 0, 0, 0)
	ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickpixel_zero_args, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickpixel_getcolor_args, 0, 0, 0)
	ZEND_ARG_INFO(0, as_array)
	ZEND_ARG_INFO(0, normalize_array)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickpixel_getcolorvalue_args, 0, 0, 1)
	ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickpixel_getcolorvaluequantum_args, 0, 0, 1)
	ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickpixel_setcolor_args, 0, 0, 1)
	ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickpixel_setcolorcount_args, 0, 0, 1)
    ZEND_ARG_INFO(0, color_count)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickpixel_setcolorvalue_args, 0, 0, 2)
	ZEND_ARG_INFO(0, color)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickpixel_setcolorvaluequantum_args, 0, 0, 2)
	ZEND_ARG_INFO(0, color)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

/* {{{ static zend_function_entry php_gmagickpixel_functions[]
*/
static zend_function_entry php_gmagickpixel_class_methods[] =
{
	PHP_ME(gmagickpixel,	__construct,		gmagickpixel_constructor_args,	ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(gmagickpixel,	setcolor,		gmagickpixel_setcolor_args,		ZEND_ACC_PUBLIC)
	PHP_ME(gmagickpixel,	getcolor,		gmagickpixel_getcolor_args,		ZEND_ACC_PUBLIC)
	PHP_ME(gmagickpixel,	getcolorcount,		gmagickpixel_zero_args,		ZEND_ACC_PUBLIC)
	PHP_ME(gmagickpixel,	setcolorcount,		gmagickpixel_setcolorcount_args,		ZEND_ACC_PUBLIC)
	PHP_ME(gmagickpixel,	getcolorvalue,		gmagickpixel_getcolorvalue_args,	ZEND_ACC_PUBLIC)
	PHP_ME(gmagickpixel,	setcolorvalue,		gmagickpixel_setcolorvalue_args,	ZEND_ACC_PUBLIC)
	PHP_ME(gmagickpixel,	getcolorvaluequantum,		gmagickpixel_getcolorvaluequantum_args,	ZEND_ACC_PUBLIC)
	PHP_ME(gmagickpixel,	setcolorvaluequantum,		gmagickpixel_setcolorvaluequantum_args,	ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};
/* }}} */

PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("gmagick.set_single_thread", "1", PHP_INI_SYSTEM, OnUpdateBool, set_single_thread, zend_gmagick_globals, gmagick_globals)
    STD_PHP_INI_ENTRY("gmagick.shutdown_sleep_count",  "10", PHP_INI_ALL, OnUpdateLong, shutdown_sleep_count, zend_gmagick_globals, gmagick_globals)
PHP_INI_END()

static void php_gmagick_init_globals(zend_gmagick_globals *gmagick_globals)
{
    gmagick_globals->set_single_thread = 1;
    // 10 is magick number, that seems to be enough.
    gmagick_globals->shutdown_sleep_count = 10;
}

/* {{{ PHP_MINIT_FUNCTION(gmagick)
*/
PHP_MINIT_FUNCTION(gmagick)
{
	char *cwd;
	size_t cwd_len;
	
	zend_class_entry ce;

	ZEND_INIT_MODULE_GLOBALS(gmagick, php_gmagick_init_globals, NULL);
	
	/* Exception */
	INIT_CLASS_ENTRY(ce, "GmagickException", NULL);
	php_gmagick_exception_class_entry = zend_register_internal_class_ex(&ce, zend_exception_get_default());
	php_gmagick_exception_class_entry->ce_flags |= ZEND_ACC_FINAL;

	INIT_CLASS_ENTRY(ce, "GmagickPixelException", NULL);
	php_gmagickpixel_exception_class_entry = zend_register_internal_class_ex(&ce, zend_exception_get_default());
	php_gmagickpixel_exception_class_entry->ce_flags |= ZEND_ACC_FINAL;

	/* Class entry */
	INIT_CLASS_ENTRY(ce, "Gmagick", php_gmagick_class_methods);
	php_gmagick_sc_entry = zend_register_internal_class(&ce);
	php_gmagick_sc_entry->create_object = php_gmagick_object_new;
	memcpy(&gmagick_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
        gmagick_object_handlers.offset = XtOffsetOf(php_gmagick_object, zo);
        gmagick_object_handlers.free_obj = php_gmagick_object_free_storage;
	gmagick_object_handlers.clone_obj = php_gmagick_clone_gmagick_object;

	INIT_CLASS_ENTRY(ce, "GmagickDraw", php_gmagickdraw_class_methods);
	php_gmagickdraw_sc_entry = zend_register_internal_class(&ce);
	php_gmagickdraw_sc_entry->create_object = php_gmagickdraw_object_new;
	memcpy(&gmagickdraw_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	gmagickdraw_object_handlers.offset = XtOffsetOf(php_gmagickdraw_object, zo);
	gmagickdraw_object_handlers.free_obj = php_gmagickdraw_object_free_storage;
	gmagickdraw_object_handlers.clone_obj = NULL;
	
	INIT_CLASS_ENTRY(ce, "GmagickPixel", php_gmagickpixel_class_methods);
	php_gmagickpixel_sc_entry = zend_register_internal_class(&ce);
	php_gmagickpixel_sc_entry->create_object = php_gmagickpixel_object_new;
	memcpy(&gmagickpixel_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	gmagickpixel_object_handlers.offset = XtOffsetOf(php_gmagickpixel_object, zo);
	gmagickpixel_object_handlers.free_obj = php_gmagickpixel_object_free_storage;
	gmagickpixel_object_handlers.clone_obj = php_gmagick_clone_gmagickpixel_object;

	/* Initialize GraphicsMagick environment */
	cwd = virtual_getcwd_ex(&cwd_len);
	
	if (!cwd)
		return FAILURE;


	InitializeMagick(cwd);
	efree(cwd);

	/* init constants */
	php_gmagick_initialize_constants();

	REGISTER_INI_ENTRIES();

	if (GMAGICK_G(set_single_thread)) {
	    MagickSetResourceLimit(ThreadsResource, 1);
	}

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION(gmagick) 
*/
PHP_MSHUTDOWN_FUNCTION(gmagick)
{
	DestroyMagick();
#if HAVE_OMP_PAUSE_RESOURCE_ALL
	// Note there is a patch to add omp_pause_resource_all to DestroyMagick()
	// https://sourceforge.net/p/graphicsmagick/patches/63/
	// But it hasn't been accepted
	omp_pause_resource_all(omp_pause_hard);
#else
	for (i = 0; i < 100 && i < GMAGICK_G(shutdown_sleep_count); i += 1) {
		usleep(1000);
	}
#endif
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION(gmagick)
*/
PHP_MINFO_FUNCTION(gmagick)
{
	const char *version;
	unsigned long version_number;
	
	version = MagickGetVersion(&version_number);
	
	php_info_print_table_start();
	php_info_print_table_header(2, "gmagick module", "enabled");
	php_info_print_table_row(2, "gmagick version", PHP_GMAGICK_VERSION);
	php_info_print_table_row(2, "GraphicsMagick version", version);
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}

/* {{{ zend_module_entry gmagick_module_entry
*/
zend_module_entry gmagick_module_entry =
{
	STANDARD_MODULE_HEADER,		/* Standard module header */
	"gmagick",			/* Extension name */
	php_gmagick_functions,		/* Functions */
	PHP_MINIT(gmagick),		/* MINIT */
	PHP_MSHUTDOWN(gmagick),		/* MSHUTDOWN */
	NULL,				/* RINIT */
	NULL,				/* RSHUTDOWN */
	PHP_MINFO(gmagick),		/* MINFO */
	PHP_GMAGICK_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES	/* Standard properties */
};
/* }}} */

/* {{{ ZEND_GET_MODULE(gmagick) */
#ifdef COMPILE_DL_GMAGICK
ZEND_GET_MODULE(gmagick)
#endif
/* }}} */
