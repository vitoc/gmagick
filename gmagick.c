/*
   +----------------------------------------------------------------------+
   | PHP Version 5 / Gmagick                                              |
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
   |         Vito Chin <vito@php.net>                                     |
   +----------------------------------------------------------------------+
*/

#include "php_gmagick.h"
#include "php_gmagick_macros.h"
#include "php_gmagick_helpers.h"
#include "gmagick_arginfo.h"

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

PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("gmagick.shutdown_sleep_count",  "10", PHP_INI_ALL, OnUpdateLong, shutdown_sleep_count, zend_gmagick_globals, gmagick_globals)
PHP_INI_END()

static void php_gmagick_init_globals(zend_gmagick_globals *gmagick_globals)
{
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
	INIT_CLASS_ENTRY(ce, "Gmagick", class_Gmagick_methods);
	php_gmagick_sc_entry = zend_register_internal_class(&ce);
	php_gmagick_sc_entry->create_object = php_gmagick_object_new;
	memcpy(&gmagick_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
        gmagick_object_handlers.offset = XtOffsetOf(php_gmagick_object, zo);
        gmagick_object_handlers.free_obj = php_gmagick_object_free_storage;
	gmagick_object_handlers.clone_obj = php_gmagick_clone_gmagick_object;

	INIT_CLASS_ENTRY(ce, "GmagickDraw", class_GmagickDraw_methods);
	php_gmagickdraw_sc_entry = zend_register_internal_class(&ce);
	php_gmagickdraw_sc_entry->create_object = php_gmagickdraw_object_new;
	memcpy(&gmagickdraw_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	gmagickdraw_object_handlers.offset = XtOffsetOf(php_gmagickdraw_object, zo);
	gmagickdraw_object_handlers.free_obj = php_gmagickdraw_object_free_storage;
	gmagickdraw_object_handlers.clone_obj = NULL;

	INIT_CLASS_ENTRY(ce, "GmagickPixel", class_GmagickPixel_methods);
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

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION(gmagick)
*/
PHP_MSHUTDOWN_FUNCTION(gmagick)
{
#ifndef HAVE_OMP_PAUSE_RESOURCE_ALL
	int i;
#endif

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
	NULL,		/* Functions */
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
