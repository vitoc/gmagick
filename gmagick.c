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
static void php_gmagick_object_free_storage(void *object TSRMLS_DC)
{
	php_gmagick_object *intern = (php_gmagick_object *)object;

	if (!intern) {
		return;
	}

	if (intern->magick_wand) {
		DestroyMagickWand(intern->magick_wand);
	}

	zend_object_std_dtor(&intern->zo TSRMLS_CC);

	efree(intern);
}
/* }}} */


/* {{{ static zend_object_value php_gmagick_object_new_ex(zend_class_entry *class_type, php_gmagick_object **ptr, zend_bool init_wand TSRMLS_DC)
*/
static zend_object_value php_gmagick_object_new_ex(zend_class_entry *class_type, php_gmagick_object **ptr, zend_bool init_wand TSRMLS_DC)
{
#if PHP_VERSION_ID < 50399
	zval *tmp;
#endif
	zend_object_value retval;
	php_gmagick_object *intern;

	/* Allocate memory for it */
	intern = (php_gmagick_object *) emalloc(sizeof(php_gmagick_object));
	memset(&intern->zo, 0, sizeof(zend_object));

	if (ptr) {
		*ptr = intern;
	}

	/* Set the magickwand */
	if (init_wand) {
		intern->magick_wand = NewMagickWand();
	} else {
		intern->magick_wand = NULL;
	}

	zend_object_std_init(&intern->zo, class_type TSRMLS_CC);
#if PHP_VERSION_ID < 50399
	zend_hash_copy(intern->zo.properties, &class_type->default_properties, (copy_ctor_func_t) zval_add_ref,(void *) &tmp, sizeof(zval *));
#else
        object_properties_init( (zend_object*)intern, class_type );
#endif

	retval.handle = zend_objects_store_put(intern, NULL, (zend_objects_free_object_storage_t) php_gmagick_object_free_storage, NULL TSRMLS_CC);
	retval.handlers = (zend_object_handlers *) &gmagick_object_handlers;
	return retval;
}
/* }}} */

/* {{{ static zend_object_value php_gmagick_object_new(zend_class_entry *class_type TSRMLS_DC)
*/
static zend_object_value php_gmagick_object_new(zend_class_entry *class_type TSRMLS_DC)
{
	return php_gmagick_object_new_ex(class_type, NULL, 1 TSRMLS_CC);
}
/* }}} */

/* {{{ static zend_object_value php_gmagick_clone_gmagick_object(zval *this_ptr TSRMLS_DC)
*/
static zend_object_value php_gmagick_clone_gmagick_object(zval *this_ptr TSRMLS_DC)
{
	php_gmagick_object *new_obj = NULL;
	php_gmagick_object *old_obj = (php_gmagick_object *) zend_object_store_get_object(this_ptr TSRMLS_CC);
	zend_object_value new_ov = php_gmagick_object_new_ex(old_obj->zo.ce, &new_obj, 0 TSRMLS_CC);
	 
	zend_objects_clone_members(&new_obj->zo, new_ov, &old_obj->zo, Z_OBJ_HANDLE_P(this_ptr) TSRMLS_CC);
	
	if (new_obj->magick_wand) {
		DestroyMagickWand(new_obj->magick_wand);
	}
	
	new_obj->magick_wand = CloneMagickWand(old_obj->magick_wand);
	return new_ov;
}
/* }}} */

/* {{{ static void php_gmagickdraw_object_free_storage(void *object TSRMLS_DC)
*/
static void php_gmagickdraw_object_free_storage(void *object TSRMLS_DC)
{
	php_gmagickdraw_object *intern = (php_gmagickdraw_object *)object;

	if (!intern) {
		return;
	}

	if (intern->drawing_wand) {
		DestroyDrawingWand(intern->drawing_wand);
	}

	zend_object_std_dtor(&intern->zo TSRMLS_CC);
	efree(intern);
}
/* }}} */

/* {{{ static zend_object_value php_gmagickdraw_object_new_ex(zend_class_entry *class_type, php_gmagickdraw_object **ptr TSRMLS_DC)
*/
static zend_object_value php_gmagickdraw_object_new_ex(zend_class_entry *class_type, php_gmagickdraw_object **ptr, zend_bool init_wand TSRMLS_DC)
{
#if PHP_VERSION_ID < 50399
	zval *tmp;
#endif
	zend_object_value retval;
	php_gmagickdraw_object *intern;

	/* Allocate memory for it */
	intern = (php_gmagickdraw_object *) emalloc(sizeof(php_gmagickdraw_object));
	memset(&intern->zo, 0, sizeof(zend_object));

	if (ptr) {
		*ptr = intern;
	}

	/* Set the DrawingWand */
	if (init_wand) {
		intern->drawing_wand = NewDrawingWand();
	} else {
		intern->drawing_wand = NULL;
	}

	/* ALLOC_HASHTABLE(intern->zo.properties); */

	zend_object_std_init(&intern->zo, class_type TSRMLS_CC);
#if PHP_VERSION_ID < 50399
	zend_hash_copy(intern->zo.properties, &class_type->default_properties, (copy_ctor_func_t) zval_add_ref,(void *) &tmp, sizeof(zval *));
#else
        object_properties_init( (zend_object*)intern, class_type );
#endif

	retval.handle = zend_objects_store_put(intern, NULL, (zend_objects_free_object_storage_t) php_gmagickdraw_object_free_storage, NULL TSRMLS_CC);
	retval.handlers = (zend_object_handlers *) &gmagickdraw_object_handlers;
	return retval;
}
/* }}} */

/* {{{ static zend_object_value php_gmagickdraw_object_new(zend_class_entry *class_type TSRMLS_DC)
*/
static zend_object_value php_gmagickdraw_object_new(zend_class_entry *class_type TSRMLS_DC)
{
	return php_gmagickdraw_object_new_ex(class_type, NULL, 1 TSRMLS_CC);
}
/* }}} */

/* {{{ static void php_gmagickpixel_object_free_storage(void *object TSRMLS_DC)
*/
static void php_gmagickpixel_object_free_storage(void *object TSRMLS_DC)
{
	php_gmagickpixel_object *intern = (php_gmagickpixel_object *)object;

	if (!intern) {
		return;
	}
	
	if(intern->pixel_wand != (PixelWand *)NULL) {
		DestroyPixelWand(intern->pixel_wand);
	}
	
	zend_object_std_dtor(&intern->zo TSRMLS_CC);
	efree(intern);
}
/* }}} */

/* {{{ static zend_object_value php_gmagickpixel_object_new_ex(zend_class_entry *class_type, php_gmagickpixel_object **ptr, zend_bool init_wand TSRMLS_DC)
*/
static zend_object_value php_gmagickpixel_object_new_ex(zend_class_entry *class_type, php_gmagickpixel_object **ptr, zend_bool init_wand TSRMLS_DC)
{
#if PHP_VERSION_ID < 50399
	zval *tmp;
#endif
	zend_object_value retval;
	php_gmagickpixel_object *intern;

	/* Allocate memory for it */
	intern = (php_gmagickpixel_object *) emalloc(sizeof(php_gmagickpixel_object));
	memset(&intern->zo, 0, sizeof(zend_object));

	if (ptr) {
		*ptr = intern;
	}

	/* Set the pixelwand if requested */
	if (init_wand) {
		intern->pixel_wand = (PixelWand *)NewPixelWand();
	} else {
		intern->pixel_wand = NULL;
	}

	/* ALLOC_HASHTABLE(intern->zo.properties); */

	zend_object_std_init(&intern->zo, class_type TSRMLS_CC);
#if PHP_VERSION_ID < 50399
	zend_hash_copy(intern->zo.properties, &class_type->default_properties, (copy_ctor_func_t) zval_add_ref,(void *) &tmp, sizeof(zval *));
#else
        object_properties_init( (zend_object*)intern, class_type );
#endif

	retval.handle = zend_objects_store_put(intern, NULL, (zend_objects_free_object_storage_t) php_gmagickpixel_object_free_storage, NULL TSRMLS_CC);
	retval.handlers = (zend_object_handlers *) &gmagickpixel_object_handlers;
	return retval;
}
/* }}} */

/* {{{ static zend_object_value php_gmagickpixel_object_new(zend_class_entry *class_type TSRMLS_DC)
*/
static zend_object_value php_gmagickpixel_object_new(zend_class_entry *class_type TSRMLS_DC)
{
	return php_gmagickpixel_object_new_ex(class_type, NULL, 1 TSRMLS_CC);
}
/* }}} */

/* {{{ static zend_object_value php_gmagick_clone_gmagick_object(zval *this_ptr TSRMLS_DC)
*/
static zend_object_value php_gmagick_clone_gmagickpixel_object(zval *this_ptr TSRMLS_DC)
{
	php_gmagickpixel_object *new_obj = NULL;
	php_gmagickpixel_object *old_obj = (php_gmagickpixel_object *) zend_object_store_get_object(this_ptr TSRMLS_CC);
	zend_object_value new_ov = php_gmagickpixel_object_new_ex(old_obj->zo.ce, &new_obj, 0 TSRMLS_CC);

	zend_objects_clone_members(&new_obj->zo, new_ov, &old_obj->zo, Z_OBJ_HANDLE_P(this_ptr) TSRMLS_CC);
	GMAGICK_CLONE_PIXELWAND(old_obj->pixel_wand, new_obj->pixel_wand);

	return new_ov;
}
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

ZEND_BEGIN_ARG_INFO_EX(gmagick_setimagescene_args, 0, 0, 1)
	ZEND_ARG_INFO(0, scene)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagick_setimagetype_args, 0, 0, 1)
	ZEND_ARG_INFO(0, IMGTYPE)
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

ZEND_BEGIN_ARG_INFO_EX(gmagick_tintimage_args, 0, 0, 2)
	ZEND_ARG_INFO(0, tint_color)
	ZEND_ARG_INFO(0, opacity)
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
	PHP_ME(gmagick, frameimage,		gmagick_frameimage_args,        ZEND_ACC_PUBLIC)
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
	PHP_ME(gmagick, setimagescene,		gmagick_setimagescene_args, ZEND_ACC_PUBLIC)
	PHP_ME(gmagick, setimagetype,		gmagick_setimagetype_args, ZEND_ACC_PUBLIC)
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
	PHP_ME(gmagick, getversion,		gmagick_empty_args, ZEND_ACC_PUBLIC)
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
	{ NULL, NULL, NULL }
};
/* }}} */

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

ZEND_BEGIN_ARG_INFO_EX(gmagickpixel_setcolor_args, 0, 0, 1)
	ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(gmagickpixel_setcolorvalue_args, 0, 0, 2)
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
	PHP_ME(gmagickpixel,	getcolorvalue,		gmagickpixel_getcolorvalue_args,	ZEND_ACC_PUBLIC)
	PHP_ME(gmagickpixel,	setcolorvalue,		gmagickpixel_setcolorvalue_args,	ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};
/* }}} */

/* {{{ PHP_MINIT_FUNCTION(gmagick)
*/
PHP_MINIT_FUNCTION(gmagick)
{
	char *cwd;
	size_t cwd_len;
	
	zend_class_entry ce;
	memcpy(&gmagick_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	memcpy(&gmagickdraw_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	memcpy(&gmagickpixel_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	
	/* Exception */
	INIT_CLASS_ENTRY(ce, "GmagickException", NULL);
	php_gmagick_exception_class_entry = zend_register_internal_class_ex(&ce, zend_exception_get_default(TSRMLS_C), NULL TSRMLS_CC);
	php_gmagick_exception_class_entry->ce_flags |= ZEND_ACC_FINAL;

	INIT_CLASS_ENTRY(ce, "GmagickPixelException", NULL);
	php_gmagickpixel_exception_class_entry = zend_register_internal_class_ex(&ce, zend_exception_get_default(TSRMLS_C), NULL TSRMLS_CC);
	php_gmagickpixel_exception_class_entry->ce_flags |= ZEND_ACC_FINAL;

	/* Class entry */
	INIT_CLASS_ENTRY(ce, "Gmagick", php_gmagick_class_methods);
	ce.create_object = php_gmagick_object_new;
	gmagick_object_handlers.clone_obj = php_gmagick_clone_gmagick_object;
	php_gmagick_sc_entry = zend_register_internal_class(&ce TSRMLS_CC);

	INIT_CLASS_ENTRY(ce, "GmagickDraw", php_gmagickdraw_class_methods);
	ce.create_object = php_gmagickdraw_object_new;
	gmagickdraw_object_handlers.clone_obj = NULL;
	php_gmagickdraw_sc_entry = zend_register_internal_class(&ce TSRMLS_CC);
	
	INIT_CLASS_ENTRY(ce, "GmagickPixel", php_gmagickpixel_class_methods);
	ce.create_object = php_gmagickpixel_object_new;
	gmagickpixel_object_handlers.clone_obj = php_gmagick_clone_gmagickpixel_object;
	php_gmagickpixel_sc_entry = zend_register_internal_class(&ce TSRMLS_CC);

	/* Initialize GraphicsMagick environment */
	cwd = virtual_getcwd_ex(&cwd_len TSRMLS_CC);
	
	if (!cwd)
		return FAILURE;
	
	InitializeMagick(cwd);
	free(cwd);

	/* init constants */
	php_gmagick_initialize_constants();
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION(gmagick) 
*/
PHP_MSHUTDOWN_FUNCTION(gmagick)
{
	DestroyMagick();
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
}

/* {{{ zend_module_entry gmagick_module_entry
*/
zend_module_entry gmagick_module_entry =
{
	STANDARD_MODULE_HEADER,         /* Standard module header */
	"gmagick",                      /* Extension name */
	php_gmagick_functions,          /* Functions */
	PHP_MINIT(gmagick),             /* MINIT */
	PHP_MSHUTDOWN(gmagick),         /* MSHUTDOWN */
	NULL,                           /* RINIT */
	NULL,                           /* RSHUTDOWN */
	PHP_MINFO(gmagick),             /* MINFO */
	PHP_GMAGICK_VERSION,            /* Version */
	STANDARD_MODULE_PROPERTIES      /* Standard properties */
};
/* }}} */

/* {{{ ZEND_GET_MODULE(gmagick) */
#ifdef COMPILE_DL_GMAGICK
ZEND_GET_MODULE(gmagick)
#endif
/* }}} */
