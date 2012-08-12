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

#ifndef HAVE_PHP_GMAGICK_MACROS_H
# define HAVE_PHP_GMAGICK_MACROS_H

/* {{{ GMAGICK_CHAIN_METHOD */
#define GMAGICK_CHAIN_METHOD RETURN_ZVAL(getThis(), 1, 0);
	
/* }}} */

/* Define a set of macros to throw exceptions */
#define GMAGICK_THROW_EXCEPTION_WITH_MESSAGE(type, description, code) \
{ \
	switch(type) { \
		case 1: \
			zend_throw_exception(php_gmagick_exception_class_entry, description, (long)code TSRMLS_CC); \
			RETURN_NULL(); \
		break; \
		case 2: \
			zend_throw_exception(php_gmagickdraw_exception_class_entry, description, (long)code TSRMLS_CC); \
			RETURN_NULL(); \
		break; \
		case 3: \
			zend_throw_exception(php_gmagickpixel_exception_class_entry, description, (long)code TSRMLS_CC); \
			RETURN_NULL(); \
		break; \
	} \
} \
/* }}} */



/* {{{ GMAGICK_REGISTER_CONST_LONG(const_name, value)
*/
#define GMAGICK_REGISTER_CONST_LONG(const_name, value) \
	zend_declare_class_constant_long(php_gmagick_sc_entry, const_name, sizeof(const_name)-1, (long)value TSRMLS_CC);
/* }}} */

/* {{{ GMAGICK_FREE_MEMORY(type, value)
*/
#define GMAGICK_FREE_MEMORY(type, value) \
	if (value != (type) NULL) { \
		MagickRelinquishMemory(value); \
		value = (type)NULL; \
	}
/* }}} */

/* {{{ GMAGICK_THROW_GMAGICK_EXCEPTION(magick_wand, fallback)
*/
#define GMAGICK_THROW_GMAGICK_EXCEPTION(magick_wand, fallback) \
{ \
	ExceptionType severity; \
	char *description; \
	description = MagickGetException(magick_wand, &severity); \
	if (description && strlen(description) == 0) { \
		GMAGICK_FREE_MEMORY(char *, description); \
        description = NULL; \
	} \
	if (!description) { \
		zend_throw_exception(php_gmagick_exception_class_entry, fallback, 1 TSRMLS_CC); \
		return; \
	} else { \
		zend_throw_exception(php_gmagick_exception_class_entry, description, (long)severity TSRMLS_CC); \
		GMAGICK_FREE_MEMORY(char *, description); \
		return; \
	} \
}
/* }}} */

/* {{{ GMAGICK_CALCULATE_THUMBNAIL_SIDES(magick_wand, desired_width, desired_height, fit)
*/
#define GMAGICK_CALCULATE_THUMBNAIL_SIDES(magick_wand, desired_width, desired_height, fit) \
{ \
	long orig_width = MagickGetImageWidth(magick_wand);\
	long orig_height = MagickGetImageHeight(magick_wand);\
	double ratio;\
	if (fit) { \
		if ((desired_width <= 0) || (desired_height <= 0)) { \
			GMAGICK_THROW_GMAGICK_EXCEPTION(magick_wand, "Invalid image geometry"); \
		} \
		if ((orig_width <= desired_width) && (orig_height <= desired_height)) { \
			RETURN_TRUE; \
		} \
		if ((orig_width - desired_width) > (orig_height - desired_height)) { \
			ratio = (double)orig_width / (double)desired_width; \
			desired_height = (double)orig_height / ratio; \
		} else { \
			ratio = (double)orig_height / (double)desired_height; \
			desired_width = (double)orig_width / ratio; \
		} \
		if (desired_width < 1) { \
			desired_width = 1; \
		} \
		if (desired_height < 1) { \
			desired_height = 1; \
		} \
	} else { \
		if ((desired_width <= 0) && (desired_height <= 0)) { \
			GMAGICK_THROW_GMAGICK_EXCEPTION(magick_wand, "Invalid image geometry");  \
		} \
		if (desired_width <= 0) { \
			ratio = (double)orig_height / (double)desired_height; \
			desired_width = orig_width / ratio; \
		} else if (desired_height <= 0) { \
			ratio = (double)orig_width / (double)desired_width; \
			desired_height = orig_height / ratio; \
		} \
	}\
}
/* }}} */

/* {{{ GMAGICK_CHECK_NOT_EMPTY(magick_wand, type, code)
*/
#define GMAGICK_CHECK_NOT_EMPTY(magick_wand, type, code)\
	if(MagickGetNumberImages(magick_wand) == 0) { \
		GMAGICK_THROW_EXCEPTION_WITH_MESSAGE(GMAGICK_CLASS, "Can not process empty Gmagick object", (long)code); \
	} \
/* }}} */

/* {{{ GMAGICK_REPLACE_MAGICKWAND(intern, new_wand)
*/
#define GMAGICK_REPLACE_MAGICKWAND(intern, new_wand)\
	if(intern->magick_wand != (MagickWand *)NULL) {\
		DestroyMagickWand(intern->magick_wand);\
		intern->magick_wand = NULL; \
		intern->magick_wand = new_wand;\
	} else {\
		intern->magick_wand = new_wand;\
	} \
/* }}} */

/* {{{ GMAGICKPIXEL_REPLACE_PIXELWAND(intern, new_wand)
*/
#define GMAGICKPIXEL_REPLACE_PIXELWAND(intern, new_wand)\
	if(intern->pixel_wand != (PixelWand *)NULL) {\
		DestroyPixelWand(intern->pixel_wand);\
		intern->pixel_wand = NULL; \
		intern->pixel_wand = new_wand;\
	} else {\
		intern->pixel_wand = new_wand;\
	} \
/* }}} */

/* {{{ GMAGICK_CLONE_PIXELWAND(source, target) */
#define GMAGICK_CLONE_PIXELWAND(source, target) \
	target = (PixelWand *)NewPixelWand(); \
	PixelSetColorCount(target, PixelGetColorCount(source)); \
	PixelSetRed(target, PixelGetRed(source)); \
	PixelSetGreen(target, PixelGetGreen(source)); \
	PixelSetBlue(target, PixelGetBlue(source)); \
	PixelSetOpacity(target, PixelGetOpacity(source));
/* }}} */

/* GraphicsMagick 1.3.3 is missing PixelGetException */
#define GMAGICK_THROW_GMAGICKPIXEL_EXCEPTION(pixel_wand, fallback) \
{ \
	zend_throw_exception(php_gmagickpixel_exception_class_entry, fallback, 2 TSRMLS_CC); \
	RETURN_NULL(); \
}
/* }}} */

#if GMAGICK_LIB_MASK < 1002000

/* GraphicsMagick 1.1.x is missing DrawGetException */
#define GMAGICK_THROW_GMAGICKDRAW_EXCEPTION(drawing_wand, fallback, code) \
{ \
	zend_throw_exception(php_gmagickdraw_exception_class_entry, fallback, 2 TSRMLS_CC); \
	RETURN_NULL(); \
}
/* }}} */

#else

/* {{{ GMAGICK_THROW_GMAGICKDRAW_EXCEPTION(drawing_wand, fallback, code) */
#define GMAGICK_THROW_GMAGICKDRAW_EXCEPTION(drawing_wand, fallback, code) \
{ \
	ExceptionType severity; \
	char *description; \
	description = DrawGetException(drawing_wand, &severity); \
	if (strlen(description) == 0) { \
		GMAGICK_FREE_MEMORY(char *, description); \
	} \
	if (!description) { \
		zend_throw_exception(php_gmagickdraw_exception_class_entry, fallback, (long)code TSRMLS_CC); \
		RETURN_NULL(); \
	} else { \
		zend_throw_exception(php_gmagickdraw_exception_class_entry, description, (long)severity TSRMLS_CC); \
		GMAGICK_FREE_MEMORY(char *, description); \
		DrawClearException(drawing_wand); \
		RETURN_NULL(); \
	} \
} \
/* }}} */

#endif

/* {{{ GMAGICK_CLONE_PIXELWAND(source, target) */
#define GMAGICK_CAST_PARAMETER_TO_COLOR(param, internp, caller) \
	switch (Z_TYPE_P(param)) { \
		case IS_STRING: \
		{ \
			zval *object; \
			PixelWand *pixel_wand = NewPixelWand(); \
			if (!PixelSetColor(pixel_wand, Z_STRVAL_P(param))) { \
				GMAGICK_THROW_GMAGICKPIXEL_EXCEPTION(pixel_wand, "Unrecognized color string"); \
				return; \
			} \
			MAKE_STD_ZVAL(object); \
			object_init_ex(object, php_gmagickpixel_sc_entry); \
			internp = (php_gmagickpixel_object *)zend_object_store_get_object(object TSRMLS_CC); \
			efree(object); \
			GMAGICKPIXEL_REPLACE_PIXELWAND(internp, pixel_wand); \
		} \
		break; \
		case IS_OBJECT: \
			if (instanceof_function_ex(Z_OBJCE_P(param), php_gmagickpixel_sc_entry, 0 TSRMLS_CC)) { \
				internp = (php_gmagickpixel_object *)zend_object_store_get_object(param TSRMLS_CC); \
			} else { \
				GMAGICK_THROW_EXCEPTION_WITH_MESSAGE(caller, "The parameter must be an instance of GmagickPixel or a string", (long)caller); \
			} \
		break; \
		default: \
			GMAGICK_THROW_EXCEPTION_WITH_MESSAGE(caller, "Invalid parameter provided", (long)caller); \
		break; \
	} \
/* }}} */

/* {{{ GMAGICK_CLONE_PIXELWAND(source, target) */
#if PHP_VERSION_ID > 50399
#define GMAGICK_SAFE_MODE_CHECK(filename, status)\
	if (filename) { \
		if (strlen(filename) > MAXPATHLEN) { \
			status = GMAGICK_READ_WRITE_FILENAME_TOO_LONG; \
		} \
		if (php_check_open_basedir_ex(filename, 0 TSRMLS_CC)) { \
			status = GMAGICK_READ_WRITE_OPEN_BASEDIR_ERROR; \
		} \
	} \

#else
#define GMAGICK_SAFE_MODE_CHECK(filename, status)\
	if (filename) { \
		if (strlen(filename) > MAXPATHLEN) { \
			status = GMAGICK_READ_WRITE_FILENAME_TOO_LONG; \
		} \
		if (PG(safe_mode) && (!php_checkuid_ex(filename, NULL, CHECKUID_CHECK_FILE_AND_DIR, CHECKUID_NO_ERRORS))) { \
			status = GMAGICK_READ_WRITE_SAFE_MODE_ERROR; \
		} \
		if (php_check_open_basedir_ex(filename, 0 TSRMLS_CC)) { \
			status = GMAGICK_READ_WRITE_OPEN_BASEDIR_ERROR; \
		} \
	} \

#endif
/* }}} */

#define GMAGICKDRAW_CHECK_READ_OR_WRITE_ERROR(internd, filename, error, free)\
	switch (error) {\
		default:\
		case 0:\
			/* No error */\
		break;\
		case 1:\
			zend_throw_exception_ex(php_gmagickdraw_exception_class_entry, 1 TSRMLS_CC, "Safe mode restricts user to read file: %s", filename);\
			if (free == GMAGICK_FREE_FILENAME) { \
				 efree(filename); \
			}\
			RETURN_NULL();\
		break;\
		case 2:\
			zend_throw_exception_ex(php_gmagickdraw_exception_class_entry, 1 TSRMLS_CC, "open_basedir restriction in effect. File(%s) is not within the allowed path(s)", filename);\
			if (free == GMAGICK_FREE_FILENAME) { \
				 efree(filename); \
			}\
			RETURN_NULL();\
		break;\
		case 3:\
			GMAGICK_THROW_GMAGICKDRAW_EXCEPTION(internd->drawing_wand, "Unable to read file", 1);\
			if (free == GMAGICK_FREE_FILENAME) { \
				 efree(filename); \
			}\
			RETURN_NULL();\
		break;\
	} \
/* }}} */

#define GMAGICK_CAST_PARAMETER_TO_OPACITY(param, internp, caller) \
	switch (Z_TYPE_P(param)) { \
		case IS_LONG: \
		case IS_DOUBLE: \
		{ \
			zval *object; \
			PixelWand *pixel_wand = NewPixelWand(); \
			PixelSetOpacity(pixel_wand, Z_DVAL_P(param)); \
			MAKE_STD_ZVAL(object); \
			object_init_ex(object, php_gmagickpixel_sc_entry); \
			internp = (php_gmagickpixel_object *)zend_object_store_get_object(object TSRMLS_CC); \
			efree(object); \
			GMAGICKPIXEL_REPLACE_PIXELWAND(internp, pixel_wand); \
		} \
		break; \
		case IS_OBJECT: \
			if (instanceof_function_ex(Z_OBJCE_P(param), php_gmagickpixel_sc_entry, 0 TSRMLS_CC)) { \
				internp = (php_gmagickpixel_object *)zend_object_store_get_object(param TSRMLS_CC); \
			} else { \
				GMAGICK_THROW_EXCEPTION_WITH_MESSAGE(caller, "The parameter must be an instance of GmagickPixel or a string", (long)caller); \
			} \
		break; \
		default: \
			GMAGICK_THROW_EXCEPTION_WITH_MESSAGE(caller, "Invalid parameter provided", (long)caller); \
		break; \
	} \
/* }}} */

/* {{{ GMAGICK_SAFEMODE_OPENBASEDIR_CHECK(filename) */
#if PHP_VERSION_ID > 50399
#define GMAGICK_SAFEMODE_OPENBASEDIR_CHECK(filename) \
	if (php_check_open_basedir_ex(filename, 0 TSRMLS_CC)) { \
		zend_error(E_WARNING, "open_basedir restriction in effect "); \
		return;	\
	}\

#else
#define GMAGICK_SAFEMODE_OPENBASEDIR_CHECK(filename) \
	if (PG(safe_mode) && (!php_checkuid_ex(filename, NULL, CHECKUID_CHECK_FILE_AND_DIR, CHECKUID_NO_ERRORS))) { \
		zend_error(E_WARNING, "SAFE MODE restriction in effect "); \
		return; \
	} \
	if (php_check_open_basedir_ex(filename, 0 TSRMLS_CC)) { \
		zend_error(E_WARNING, "open_basedir restriction in effect "); \
		return;	\
	}\

#endif
/* }}} */

/* {{{ GMAGICK_SAFEMODE_OPENBASEDIR_CONFIRMACCESS(filename) */
#define GMAGICK_SAFEMODE_OPENBASEDIR_CONFIRMACCESS(filename) \
    	ExceptionInfo exception_info; \
    	GetExceptionInfo(&exception_info); \
	(void) MagickSetConfirmAccessHandler(SafeModeMonitor); \
	if (MagickConfirmAccess(FileReadConfirmAccessMode, filename, &exception_info) \
	== MagickFail) \
 	{ \
		DestroyExceptionInfo(&exception_info); \
		zend_error(E_WARNING, "SAFE MODE Restriction in effect "); \
		return; \
      	} \
	(void) MagickSetConfirmAccessHandler(OpenBaseDirMonitor); \
	if (MagickConfirmAccess(FileReadConfirmAccessMode, filename, &exception_info) \
	== MagickFail) \
 	{ \
		DestroyExceptionInfo(&exception_info); \
		zend_error(E_WARNING, "open_basedir restriction in effect "); \
		return; \
      	} \
/* }}} */

/* {{{ GMAGICK_HAS_FORMAT(buffer, magick_wand, free_buffer) */
#define GMAGICK_HAS_FORMAT(buffer, magick_wand, free_buffer)\
	buffer = MagickGetImageFormat(magick_wand);\
	if(buffer == (char *)NULL || *buffer == '\0') {\
		GMAGICK_FREE_MEMORY(char *, buffer); GMAGICK_THROW_EXCEPTION_WITH_MESSAGE(GMAGICK_CLASS, "Image has no format", 1); \
	} else { \
		if (free_buffer) GMAGICK_FREE_MEMORY(char *, buffer); \
	} \
/* }}} */

#endif
